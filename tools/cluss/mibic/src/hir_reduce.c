#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "compile.h"
#include "hir.h"
#include "lir.h"
#include "util.h"

static void hir_reduce_function(hir_func_t *func);
static void hir_write_func_start(hir_func_t *func);
static void hir_init_variable(hir_var_t *var);
static void hir_reduce_block(hir_block_t *block);
static void hir_reduce_expr(hir_expr_t *expr, int is_root);
static void hir_reduce_binary(hir_binary_op_t *expr, int is_root);
static void hir_reduce_binary_rvalues(hir_binary_op_t *expr);
static void hir_reduce_binary_assignment(hir_binary_op_t *expr, int is_root);
static void hir_reduce_unary(hir_unary_op_t *expr, int is_root);
static void hir_reduce_term(hir_terminal_t *expr);
static void hir_reduce_call(hir_call_t *expr, int is_root);
static void hir_reduce_ifelse(hir_ifelse_t *expr, int is_root);
static void hir_reduce_loop(hir_loop_t *expr, int is_root);
static void hir_reduce_abort(hir_abort_t *expr);

static int hir_is_lvalue(hir_expr_t *expr);
static int hir_is_terminal(hir_expr_t *expr);
static int hir_get_lvalue(hir_expr_t *expr);
static void hir_eval_lvalue(hir_expr_t *expr);
static void hir_load_lvalue(hir_expr_t *expr);
static void hir_save_lvalue(hir_expr_t *expr);

static void write_deref_sized(int size);

static void push_break_target(id_handle_t target);
static id_handle_t get_break_target(int depth);
static void pop_break_target(void);

static void push_continue_target(id_handle_t target);
static id_handle_t get_continue_target(int depth);
static void pop_continue_target(void);

//{{{
void hir_reduce(void)
{
	int i;
	
	hir_reduce_pointers();
	
	for(i=0; i<functions_num; i++)
		hir_reduce_function(&global_functions[i]);
}
//}}}
//{{{
static void hir_reduce_function(hir_func_t *func)
{
	if(!func->has_body)
		return;
	
	hir_write_func_start(func);
	hir_reduce_block(&func->body);
	lir_write_inst(LIR_RET);
}
//}}}
//{{{
static void hir_write_func_start(hir_func_t *func)
{
	int ii;
	const char *name = get_identifier_string(func->identifier);
	
	lir_write_inst_immediate(LIR_SPLITPOINT, 0);
	
	lir_write_inst_immediate(LIR_CHAR, 0);
	if(debug_info) // Write function name before the function itself
	{
		for(ii=0; name[ii] != '\0'; ii++)
			lir_write_inst_immediate(LIR_CHAR, name[ii]);
	}
	lir_write_inst_immediate(LIR_CHAR, 0);
	
	lir_write_label(func->identifier);
	lir_write_inst_immediate(LIR_LINK, func->vars_num);
	
	// Initialize variables
	for(ii=0; ii<func->vars_num; ii++)
		hir_init_variable(&func->vars[ii]);
}
//}}}
//{{{
static void hir_init_variable(hir_var_t *var)
{
	if(var->initializer.type == HIR_INIT_NONE)
		return;
	
	hir_reduce_expr(var->initializer.value, 0);
	lir_write_inst_reg(LIR_STR, var->index);
}
//}}}
//{{{
static void hir_reduce_block(hir_block_t *block)
{
	int i;
	
	for(i=0; i<block->code_lines; i++)
		hir_reduce_expr(&block->code[i], 1);
}
//}}}
//{{{
static void hir_reduce_expr(hir_expr_t *expr, int is_root)
{
	yylineno = expr->lineno;
	input_filename = expr->filename;
	
	switch(expr->type)
	{
		case HIR_EXPR_BINOP:
			hir_reduce_binary(expr->data.binary, is_root);
			break;
		case HIR_EXPR_UNARYOP:
			hir_reduce_unary(expr->data.unary, is_root);
			break;
		case HIR_EXPR_TERM:
			if(!is_root)
				hir_reduce_term(expr->data.terminal);
			break;
		case HIR_EXPR_CALL:
			hir_reduce_call(expr->data.call, is_root);
			break;
		case HIR_EXPR_IFELSE:
			hir_reduce_ifelse(expr->data.ifelse, is_root);
			break;
		case HIR_EXPR_LOOP:
			hir_reduce_loop(expr->data.loop, is_root);
			break;
		case HIR_EXPR_ABORT:
			hir_reduce_abort(expr->data.abort);
			break;
	}
}
//}}}
//{{{
static void hir_reduce_binary(hir_binary_op_t *expr, int is_root)
{
	switch(expr->type)
	{
		case HIR_BINOP_ADD:    case HIR_BINOP_SUB:
		case HIR_BINOP_MUL:    case HIR_BINOP_DIV:
		case HIR_BINOP_MOD:    case HIR_BINOP_LSHIFT:
		case HIR_BINOP_RSHIFT: case HIR_BINOP_LT:
		case HIR_BINOP_LTEQ:   case HIR_BINOP_GT:
		case HIR_BINOP_GTEQ:   case HIR_BINOP_EQEQ:
		case HIR_BINOP_NEQ:    case HIR_BINOP_AND:
		case HIR_BINOP_XOR:    case HIR_BINOP_OR:
		case HIR_BINOP_ANDAND: case HIR_BINOP_OROR:
		case HIR_BINOP_COMMA:  case HIR_BINOP_ARRAY:
			if(!is_root)
				hir_reduce_binary_rvalues(expr);
			break;
		case HIR_BINOP_EQ:    case HIR_BINOP_ADDEQ:
		case HIR_BINOP_SUBEQ: case HIR_BINOP_MULEQ:
		case HIR_BINOP_DIVEQ: case HIR_BINOP_MODEQ:
		case HIR_BINOP_ANDEQ: case HIR_BINOP_XOREQ:
		case HIR_BINOP_OREQ:  case HIR_BINOP_LSFTEQ:
		case HIR_BINOP_RSFTEQ:
			hir_reduce_binary_assignment(expr, is_root);
			break;
		default:
			fprintf(stderr, "Internal Error: Invalid operator: %i\n", expr->type);
			return;
	}
}
//}}}
//{{{
static void hir_reduce_binary_rvalues(hir_binary_op_t *expr)
{
	hir_reduce_expr(expr->left, 0);
	hir_reduce_expr(expr->right, 0);
	
	switch(expr->type)
	{
		case HIR_BINOP_ADD:    lir_write_inst(LIR_ADD); break;
		case HIR_BINOP_SUB:    lir_write_inst(LIR_SUB); break;
		case HIR_BINOP_MUL:    lir_write_inst(LIR_MUL); break;
		case HIR_BINOP_DIV:    lir_write_inst(LIR_DIV); break;
		case HIR_BINOP_MOD:    lir_write_inst(LIR_MOD); break;
		case HIR_BINOP_LSHIFT: lir_write_inst(LIR_ASL); break;
		case HIR_BINOP_RSHIFT: lir_write_inst(LIR_ASR); break;
		case HIR_BINOP_LT:     lir_write_inst(LIR_TLT); break;
		case HIR_BINOP_LTEQ:   lir_write_inst(LIR_TGT);
		                       lir_write_inst(LIR_NOT); break;
		case HIR_BINOP_GT:     lir_write_inst(LIR_TGT); break;
		case HIR_BINOP_GTEQ:   lir_write_inst(LIR_TLT);
		                       lir_write_inst(LIR_NOT); break;
		case HIR_BINOP_EQEQ:   lir_write_inst(LIR_TEQ); break;
		case HIR_BINOP_NEQ:    lir_write_inst(LIR_TEQ);
		                       lir_write_inst(LIR_NOT); break;
		case HIR_BINOP_AND:    lir_write_inst(LIR_AND); break;
		case HIR_BINOP_XOR:    lir_write_inst(LIR_XOR); break;
		case HIR_BINOP_OR:     lir_write_inst(LIR_OR);  break;
		case HIR_BINOP_ANDAND: lir_write_inst(LIR_BOOL2);
		                       lir_write_inst(LIR_AND); break;
		case HIR_BINOP_OROR:   lir_write_inst(LIR_BOOL2);
		                       lir_write_inst(LIR_OR);  break;
		case HIR_BINOP_COMMA:
			lir_write_inst(LIR_DISC);
			lir_write_inst(LIR_DISC);
			break;
		case HIR_BINOP_ARRAY:
			fprintf(stderr, "Internal Error: operator[] not reduced.\n");
			return;
	}
}
//}}}
//{{{
static void hir_reduce_binary_assignment(hir_binary_op_t *expr, int is_root)
{
	if(!hir_is_lvalue(expr->left))
	{
		error_non_lvalue();
		return;
	}
	
	if(expr->type == HIR_BINOP_EQ)
	{
		hir_eval_lvalue(expr->left);
		hir_reduce_expr(expr->right, 0);
		if(!is_root)
			lir_write_inst(LIR_DUP);
		hir_save_lvalue(expr->left);
		return;
	}
	
	hir_load_lvalue(expr->left);
	
	hir_reduce_expr(expr->right, 0);
	
	switch(expr->type)
	{
		case HIR_BINOP_ADDEQ:  lir_write_inst(LIR_ADD); break;
		case HIR_BINOP_SUBEQ:  lir_write_inst(LIR_SUB); break;
		case HIR_BINOP_MULEQ:  lir_write_inst(LIR_MUL); break;
		case HIR_BINOP_DIVEQ:  lir_write_inst(LIR_DIV); break;
		case HIR_BINOP_MODEQ:  lir_write_inst(LIR_MOD); break;
		case HIR_BINOP_ANDEQ:  lir_write_inst(LIR_AND); break;
		case HIR_BINOP_XOREQ:  lir_write_inst(LIR_XOR); break;
		case HIR_BINOP_OREQ:   lir_write_inst(LIR_OR);  break;
		case HIR_BINOP_LSFTEQ: lir_write_inst(LIR_ASL); break;
		case HIR_BINOP_RSFTEQ: lir_write_inst(LIR_ASR); break;
	}
	
	if(!is_root)
		lir_write_inst(LIR_DUP);
	
	hir_save_lvalue(expr->left);
}
//}}}

//{{{
static void hir_reduce_unary(hir_unary_op_t *expr, int is_root)
{
	switch(expr->type)
	{
		case HIR_UNARYOP_RETURN:
			hir_reduce_expr(expr->child, 0);
			lir_write_inst(LIR_RET);
			break;
		case HIR_UNARYOP_BOOLNOT:
			hir_reduce_expr(expr->child, is_root);
			if(!is_root)
				lir_write_inst(LIR_NOT);
			break;
		case HIR_UNARYOP_NEG:
			hir_reduce_expr(expr->child, is_root);
			if(!is_root)
				lir_write_inst(LIR_NEG);
			break;
		
		case HIR_UNARYOP_POSTINCR:
			if(!hir_is_lvalue(expr->child)) {
				error_non_lvalue();
				return;
			}
			if(hir_is_terminal(expr->child))
			{
				lir_write_inst_reg(LIR_INCR, hir_get_lvalue(expr->child));
			} else {
				hir_reduce_expr(expr->child, is_root);
				// TODO
			}
			break;
			
		case HIR_UNARYOP_POSTDECR:
			if(!hir_is_lvalue(expr->child)) {
				error_non_lvalue();
				return;
			}
			if(hir_is_terminal(expr->child))
			{
				lir_write_inst_reg(LIR_DECR, hir_get_lvalue(expr->child));
			} else {
				hir_reduce_expr(expr->child, is_root);
				// TODO
			}
			break;
			
		case HIR_UNARYOP_PREINCR:
			if(!hir_is_lvalue(expr->child)) {
				error_non_lvalue();
				return;
			}
			if(hir_is_terminal(expr->child))
			{
				lir_write_inst_reg(LIR_INCR, hir_get_lvalue(expr->child));
			} else {
				hir_reduce_expr(expr->child, is_root);
				// TODO
			}
			break;
			
		case HIR_UNARYOP_PREDECR:
			if(!hir_is_lvalue(expr->child)) {
				error_non_lvalue();
				return;
			}
			if(hir_is_terminal(expr->child))
			{
				lir_write_inst_reg(LIR_DECR, hir_get_lvalue(expr->child));
			} else {
				hir_reduce_expr(expr->child, is_root);
				// TODO
			}
			break;
			
		case HIR_UNARYOP_BITNOT:
			if(is_root)
				hir_reduce_expr(expr->child, is_root);
			else {
				lir_write_inst_immediate(LIR_LDIL, 0xFFFFFFFF);
				hir_reduce_expr(expr->child, is_root);
				lir_write_inst(LIR_SUB);
			}
			break;
			
		case HIR_UNARYOP_DEREF:
			hir_reduce_expr(expr->child, is_root);
			
			if(!is_root)
			{
				write_deref_sized(type_size(type_deref(expr->child->datatype)));
			}
			break;
		
		case HIR_UNARYOP_ADDRESS:
			hir_reduce_expr(expr->child, is_root);
			fprintf(stderr, "Warning: Unary address-of not yet supported.");
			break;
		
		case HIR_UNARYOP_ALLOCA:
			hir_reduce_expr(expr->child, is_root);
			lir_write_inst(LIR_ALLOCA);
			break;
	}
}
//}}}
//{{{
static void hir_reduce_term(hir_terminal_t *expr)
{
	switch(expr->type)
	{
		case HIR_TERM_IMMED:
			lir_write_inst_immediate(LIR_LDIL, expr->value);
			break;
		case HIR_TERM_VAR:
			lir_write_inst_reg(LIR_LDR, expr->value);
			break;
		case HIR_TERM_LABEL:
			lir_write_inst_label(LIR_LDLBL, expr->target);
			break;
	}
}
//}}}
//{{{
static void hir_reduce_call(hir_call_t *expr, int is_root)
{
	int i;
	int funcindex;
	
	for(i=0; i<functions_num; i++) {
		if(idcmp(expr->function, global_functions[i].identifier))
			break;
	}
	if(i>=functions_num) {
		error_undeclared_identifier(expr->function);
		return;
	}
	funcindex = i;
	
	for(i=expr->params.code_lines-1; i>=0; i--) {
		hir_reduce_expr(&expr->params.code[i], 0);
	}
	
	for(i=0; i<expr->params.code_lines; i++)
		lir_write_inst(LIR_STA);
	
	if(global_functions[funcindex].is_extern)
		lir_write_inst_immediate(LIR_CCALL, global_functions[funcindex].extern_index);
	else
		lir_write_inst_label(LIR_CALL, expr->function);
	
	if(type_is_void(expr->type))
	{
		if(!is_root)
		{
			warn_void_in_expr();
			lir_write_inst(LIR_LDIZ);
		}
	} else {
		if(is_root)
			lir_write_inst(LIR_DISC);
	}
}
//}}}
//{{{
static void hir_reduce_ifelse(hir_ifelse_t *expr, int is_root)
{
	id_handle_t cond_end, cond_block;
	
	hir_reduce_expr(expr->condition, 0);
	
	if(expr->alt.code_lines == 0) // Has no else- component
	{
		cond_end = generate_label();
		lir_write_inst(LIR_NOT);
		lir_write_inst_label(LIR_BRA, cond_end);
		hir_reduce_block(&expr->body);
		lir_write_label(cond_end);
	} else {
		cond_end = generate_label();
		cond_block = generate_label();
		lir_write_inst_label(LIR_BRA, cond_block);
		hir_reduce_block(&expr->alt);
		lir_write_inst_label(LIR_JMP, cond_end);
		lir_write_label(cond_block);
		hir_reduce_block(&expr->body);
		lir_write_label(cond_end);
	}
}
//}}}
//{{{
static void hir_reduce_loop(hir_loop_t *expr, int is_root)
{
	id_handle_t repeat, finish, test, continuation;
	
	repeat = generate_label();
	test = generate_label();
	finish = generate_label();
	
	push_break_target(finish);
	
	switch(expr->type)
	{
		case HIR_LOOP_DOWHILE:
			/*
				repeat:
					[body]
				test:
					[condition]
					bra repeat
				finish:
			*/
			push_continue_target(test);
			lir_write_label(repeat);
			hir_reduce_block(&expr->body);
			lir_write_label(test);
			hir_reduce_expr(expr->condition, 0);
			lir_write_inst_label(LIR_BRA, repeat);
			lir_write_label(finish);
			break;
		case HIR_LOOP_WHILE:
			/*
					jmp test
				repeat:
					[body]
				test:
					[condition]
					bra repeat
				finish:
			 */
			push_continue_target(test);
			lir_write_inst_label(LIR_JMP, test);
			lir_write_label(repeat);
			hir_reduce_block(&expr->body);
			lir_write_label(test);
			hir_reduce_expr(expr->condition, 0);
			lir_write_inst_label(LIR_BRA, repeat);
			lir_write_label(finish);
			break;
		case HIR_LOOP_FOR:
			/*
					[initializer]
					jmp test
				repeat:
					[body]
				continuation:
					[increment]]
				test:
					[condition]
					bra repeat
				finish:
			*/
			continuation = generate_label();
			push_continue_target(continuation);
			if(expr->initializer)
				hir_reduce_expr(expr->initializer, 1);
			lir_write_inst_label(LIR_JMP, test);
			lir_write_label(repeat);
			hir_reduce_block(&expr->body);
			lir_write_label(continuation);
			if(expr->iterator)
				hir_reduce_expr(expr->iterator, 1);
			lir_write_label(test);
			if(expr->condition)
				hir_reduce_expr(expr->condition, 0);
			else
				lir_write_inst(LIR_LDIZ);
			lir_write_inst_label(LIR_BRA, repeat);
			lir_write_label(finish);
	}
	
	pop_break_target();
	pop_continue_target();
}
//}}}
//{{{
static void hir_reduce_abort(hir_abort_t *expr)
{
	switch(expr->type)
	{
		case HIR_ABORT_BREAK:
			lir_write_inst_label(LIR_JMP, get_break_target(expr->levels));
			break;
		case HIR_ABORT_CONTINUE:
			lir_write_inst_label(LIR_JMP, get_continue_target(expr->levels));
			break;
	}
}
//}}}

//{{{
static int hir_is_lvalue(hir_expr_t *expr)
{
	switch(expr->type)
	{
		case HIR_EXPR_TERM:
			return( expr->data.terminal->type == HIR_TERM_VAR );
		case HIR_EXPR_UNARYOP:
			return( expr->data.unary->type == HIR_UNARYOP_DEREF );
		default:
			return 0;
	}
}
//}}}
//{{{
static int hir_is_terminal(hir_expr_t *expr)
{
	return expr->type == HIR_EXPR_TERM;
}
//}}}
//{{{
static int hir_get_lvalue(hir_expr_t *expr)
{
	if(!hir_is_lvalue(expr))
	{
		error_non_lvalue();
		return -1;
	}
	
	return expr->data.terminal->value;
}
//}}}

//{{{
static void hir_eval_lvalue(hir_expr_t *expr)
{
	assert(hir_is_lvalue(expr));
	
	if(expr->type == HIR_EXPR_UNARYOP)
	{
		hir_reduce_expr(expr->data.unary->child, 0);
	}
}
//}}}
//{{{
static void hir_load_lvalue(hir_expr_t *expr)
{
	hir_eval_lvalue(expr);
	
	if(expr->type == HIR_EXPR_TERM)
	{
		if(expr->data.terminal->type == HIR_TERM_VAR)
			lir_write_inst_reg(LIR_LDR, expr->data.terminal->value);
		else
			error_non_lvalue();
	}
	else
	{
		lir_write_inst(LIR_DUP);
		switch(type_size(expr->datatype))
		{
			case 1: lir_write_inst(LIR_DEREFB); break;
			case 2: lir_write_inst(LIR_DEREFW); break;
			case 4: lir_write_inst(LIR_DEREFL); break;
			default:
				fprintf(stderr, "Internal Error: Unsupported size in dereference.\n");
				break;
		}
	}
}
//}}}
//{{{
static void hir_save_lvalue(hir_expr_t *expr)
{
	if(expr->type == HIR_EXPR_UNARYOP)
	{
		switch(type_size(expr->datatype))
		{
			case 1: lir_write_inst(LIR_POKEB); break;
			case 2: lir_write_inst(LIR_POKEW); break;
			case 4: lir_write_inst(LIR_POKEL); break;
			default:
				fprintf(stderr, "Internal Error: Unsupported size in dereference.\n");
				break;
		}
	}
	else if(expr->type == HIR_EXPR_TERM)
	{
		lir_write_inst_reg(LIR_STR, expr->data.terminal->value);
	}
}
//}}}

//{{{
static void write_deref_sized(int size)
{
	switch( size )
	{
		case 1: lir_write_inst(LIR_DEREFB); break;
		case 2: lir_write_inst(LIR_DEREFW); break;
		case 4: lir_write_inst(LIR_DEREFL); break;
		default:
			fprintf(stderr, "Internal Error: Don't know how to dereference size %i.\n", size);
			break;
	}
}
//}}}

#define BREAK_STACK_DEPTH 64
static id_handle_t break_targets[BREAK_STACK_DEPTH];
static int break_depth = -1;
//{{{
static void push_break_target(id_handle_t target)
{
	if(break_depth >= BREAK_STACK_DEPTH-1)
		error_internal_memory();
	break_targets[++break_depth] = target;
}
//}}}
//{{{
static id_handle_t get_break_target(int depth)
{
	if(depth-1 > break_depth)
		error_invalid_break();
	return break_targets[break_depth - depth + 1];
}
//}}}
//{{{
static void pop_break_target(void)
{
	if(break_depth <= -1)
		error_internal_memory();
	break_depth --;
}
//}}}
#define CONTINUE_STACK_DEPTH 64
static id_handle_t continue_targets[CONTINUE_STACK_DEPTH];
static int continue_depth = -1;
//{{{
static void push_continue_target(id_handle_t target)
{
	if(continue_depth >= CONTINUE_STACK_DEPTH-1)
		error_internal_memory();
	continue_targets[++continue_depth] = target;
}
//}}}
//{{{
static id_handle_t get_continue_target(int depth)
{
	if(continue_depth-1 > continue_depth)
		error_invalid_continue();
	return continue_targets[continue_depth - depth + 1];
}
//}}}
//{{{
static void pop_continue_target(void)
{
	if(continue_depth <= -1)
		error_internal_memory();
	continue_depth --;
}
//}}}


