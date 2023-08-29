#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "compile.h"
#include "hir.h"
#include "lir.h"
#include "util.h"

hir_func_t *global_functions = NULL;
int functions_num=0, functions_alloc=0;


hir_func_t current_function;

static void hir_delete_func(hir_func_t *f);
static int check_prototype_match(hir_func_t *one, hir_func_t *two);

static int find_variable(id_handle_t identifier);
static hir_interm_t hir_get_temp(void);
static hir_expr_t *hir_peek_temp(hir_interm_t t);

static void start_loop(int type, hir_expr_t *initializer, hir_expr_t *condition, hir_expr_t *iterator);
static void finish_loop(hir_expr_t *condition);

static void init_block(hir_block_t *block);
static void push_block(hir_block_t *block, int type);
static hir_block_t *current_block(void);
static void pop_block(void);
static void hir_write_expr(hir_expr_t *expr);

//{{{
static void hir_delete_func(hir_func_t *f)
{
	free(f->vars);
	f->vars = NULL;
	f->vars_alloc = 0;
	free_block_contents(&f->body);
}
//}}}
//{{{
void free_block_contents(hir_block_t *block)
{
	int i;
	for(i=0; i<block->code_lines; i++)
		free_expr_contents(&block->code[i]);
	free(block->code);
	
	block->code = NULL;
	block->code_lines = block->code_alloc = 0;
}
//}}}
//{{{
void free_expr(hir_expr_t *expr)
{
	free_expr_contents(expr);
	free(expr);
}
//}}}
//{{{
void free_expr_contents(hir_expr_t *expr)
{
	if(expr==NULL)
		return;
	
	switch(expr->type)
	{
		case HIR_EXPR_BINOP:
			free_expr(expr->data.binary->left);
			free_expr(expr->data.binary->right);
			free(expr->data.binary);
			break;
		case HIR_EXPR_UNARYOP:
			free_expr(expr->data.unary->child);
			free(expr->data.unary);
			break;
		case HIR_EXPR_TERM:
			free(expr->data.terminal);
			break;
		case HIR_EXPR_CALL:
			free_block_contents(&expr->data.call->params);
			free(expr->data.call);
			break;
		case HIR_EXPR_IFELSE:
			free_block_contents(&expr->data.ifelse->body);
			free_block_contents(&expr->data.ifelse->alt);
			free(expr->data.ifelse);
			break;
		case HIR_EXPR_LOOP:
			free_expr(expr->data.loop->initializer);
			free_expr(expr->data.loop->condition);
			free_expr(expr->data.loop->iterator);
			free_block_contents(&expr->data.loop->body);
			break;
		case HIR_EXPR_ABORT:
			free(expr->data.abort);
			break;
	}
}
//}}}

//{{{
static int check_prototype_match(hir_func_t *one, hir_func_t *two)
{
	if(one->params_num != two->params_num)
		return 0;
	if(!typecmp(one->ret, two->ret))
		return 0;
		
	return 1;
}
//}}}

//{{{
void hir_done(void)
{
	int i;
	
	for(i=0; i<functions_num; i++)
		hir_delete_func(&global_functions[i]);
	
	global_functions = realloc(global_functions, 0);
	functions_alloc = functions_num = 0;
}
//}}}

//{{{
void hir_start_func(type_handle_t return_type, id_handle_t identifier)
{
	current_function.ret = return_type;
	current_function.vars_num   = 0;
	current_function.vars_alloc = 0;
	current_function.identifier = identifier;
	current_function.params_num = 0;
	current_function.is_extern  = 0;
	current_function.has_body   = 0;
	current_function.extern_index = 0;
	
	current_function.vars = NULL;
	
	init_block(&current_function.body);
	push_block(&current_function.body, HIR_BLOCK_FUNC);
}
//}}}
//{{{
void hir_add_variable(type_handle_t type, id_handle_t identifier, int is_param)
{
	hir_var_t addition;
	
	expand_table( (void**)&current_function.vars, &current_function.vars_alloc, current_function.vars_num + 1, sizeof(hir_var_t) );
	
	addition.type = type;
	addition.id = identifier;
	addition.index = current_function.vars_num;
	addition.initializer.type = HIR_INIT_NONE;
	current_function.vars[current_function.vars_num++] = addition;
	
	if(is_param) current_function.params_num++;
}
//}}}
//{{{
void hir_finish_prototype(void)
{
	int i;
	
	for(i=0; i<functions_num; i++)
	{
		if( idcmp(global_functions[i].identifier, current_function.identifier) )
		{
			if(!check_prototype_match(&global_functions[i], &current_function))
				error_prototype_mismatch(current_function.identifier);
			
			hir_delete_func(&current_function);
			pop_block();
			return;
		}
	}
	
	expand_table((void*)&global_functions, &functions_alloc, functions_num+1, sizeof(hir_func_t));
	global_functions[functions_num].is_extern = 0;
	global_functions[functions_num].has_body = 0;
	global_functions[functions_num].extern_index = -1;
	global_functions[functions_num++] = current_function;
	pop_block();
}
//}}}
//{{{
void hir_finish_extern_func(int index)
{
	hir_finish_prototype();
	global_functions[functions_num-1].is_extern = 1;
	global_functions[functions_num-1].extern_index = index;
}
//}}}
//{{{
void hir_finish_func_body(void)
{
	int i;
	
	current_function.has_body = 1;
	
	for(i=0; i<functions_num; i++)
	{
		if( idcmp(global_functions[i].identifier, current_function.identifier) )
		{
			if(!check_prototype_match(&global_functions[i], &current_function))
				error_prototype_mismatch(current_function.identifier);
			
			hir_delete_func(&global_functions[i]);
			global_functions[i] = current_function;
			pop_block();
			return;
		}
	}
	
	expand_table((void*)&global_functions, &functions_alloc, functions_num+1, sizeof(hir_func_t));
	global_functions[functions_num].has_body = 1;
	global_functions[functions_num].is_extern = 0;
	global_functions[functions_num++] = current_function;
	
	pop_block();
}
//}}}

#define TEMP_STORE_SIZE 64
hir_expr_t *temp_store[TEMP_STORE_SIZE];

//{{{
static int find_variable(id_handle_t identifier)
{
	int i;
	
	for(i=0; i<current_function.vars_num; i++)
	{
		if(idcmp(identifier, current_function.vars[i].id))
			return i;
	}
	
	return -1;
}
//}}}

//{{{
static hir_interm_t hir_get_temp(void)
{
	int i;
	for(i=0; i<TEMP_STORE_SIZE; i++)
	{
		if(temp_store[i] == NULL)
			return i;
	}
	
	return -1;
}
//}}}
//{{{
hir_interm_t hir_write_temp(hir_expr_t *expr)
{
	hir_interm_t pos = hir_get_temp();
	temp_store[pos] = expr;
	return pos;
}
//}}}
//{{{
hir_expr_t *hir_pop_temp(hir_interm_t t)
{
	hir_expr_t *ret;
	
	if(t == -1)
		return NULL;
	
	ret = temp_store[t];
	temp_store[t] = NULL;
	return ret;
}
//}}}
//{{{
static hir_expr_t *hir_peek_temp(hir_interm_t t)
{
	if(t==-1) return NULL;
	return temp_store[t];
}
//}}}

//{{{
hir_interm_t hir_load_immediate(long value)
{
	hir_terminal_t *term = (hir_terminal_t*)malloc(sizeof(hir_terminal_t));
	hir_expr_t *expr = (hir_expr_t*)malloc(sizeof(hir_expr_t));
	
	if(term==NULL || expr==NULL)
		error_internal_memory();
	
	term->type = HIR_TERM_IMMED;
	term->value = value;
	
	expr->type = HIR_EXPR_TERM;
	expr->datatype = type_base(type_long);
	expr->data.terminal = term;
	expr->lineno = yylineno;
	expr->filename = input_filename;
	
	return hir_write_temp(expr);
}
//}}}
//{{{
hir_interm_t hir_load_string(char *str)
{
	id_handle_t id = generate_label();
	hir_terminal_t *term = (hir_terminal_t*)malloc(sizeof(hir_terminal_t));
	hir_expr_t *expr = (hir_expr_t*)malloc(sizeof(hir_expr_t));
	
	lir_write_label_flags(id, 0, 0, 0);
	hir_emit_string(str);
	
	if(term==NULL || expr==NULL)
		error_internal_memory();
	
	term->type = HIR_TERM_LABEL;
	term->target = id;
	
	expr->type = HIR_EXPR_TERM;
	expr->datatype = type_pointer_to(type_base(type_char));
	expr->data.terminal = term;
	expr->lineno = yylineno;
	expr->filename = input_filename;
	
	return hir_write_temp(expr);

}
//}}}
//{{{
hir_interm_t hir_load_variable(id_handle_t identifier)
{
	hir_terminal_t *term;
	hir_expr_t *expr;
	
	long var = find_variable(identifier);
	
	if(var == -1)
	{
		if(hir_is_constant(identifier))
		{
			return hir_load_immediate(hir_get_constant_value(identifier));
		} else {
			error_undeclared_identifier(identifier);
			return hir_load_immediate(0);
		}
	}
	
	term = (hir_terminal_t*)malloc(sizeof(hir_terminal_t));
	expr = (hir_expr_t*)malloc(sizeof(hir_expr_t));
	
	if(term==NULL || expr==NULL)
		error_internal_memory();
	
	term->type = HIR_TERM_VAR;
	term->value = var;
	
	expr->type = HIR_EXPR_TERM;
	expr->datatype = current_function.vars[var].type;
	expr->data.terminal = term;
	expr->lineno = yylineno;
	expr->filename = input_filename;
	
	return hir_write_temp(expr);
}
//}}}
//{{{
hir_interm_t hir_binary_op(hir_interm_t left, hir_interm_t right, int type)
{
	hir_expr_t *expr = (hir_expr_t*)malloc(sizeof(hir_expr_t));
	hir_binary_op_t *binop = (hir_binary_op_t*)malloc(sizeof(hir_binary_op_t));
	
	if(expr==NULL || binop==NULL)
		error_internal_memory();
	
	expr->type = HIR_EXPR_BINOP;
	expr->data.binary = binop;
	expr->lineno = yylineno;
	expr->filename = input_filename;
	binop->type = type;
	binop->left = hir_pop_temp(left);
	binop->right = hir_pop_temp(right);
	
	switch(type)
	{
		case HIR_BINOP_ARRAY:
			expr->datatype = type_deref(binop->left->datatype);
			break;
		default:
			expr->datatype = binop->left->datatype;
			break;
	}
	
	return hir_write_temp(expr);
}
//}}}
//{{{
hir_interm_t hir_cast(hir_interm_t child, type_handle_t type)
{
	hir_expr_t *expr = hir_pop_temp(child);
	expr->datatype = type;
	return hir_write_temp(expr);
}
//}}}
//{{{
hir_interm_t hir_selection_op(hir_interm_t left, id_handle_t right, int type)
{
	hir_expr_t *expr = hir_peek_temp(left);
	
	if(type == HIR_BINOP_ARROW)
	{
		if( !type_is_struct( type_deref(expr->datatype) ) )
		{
			error_non_struct();
			return hir_load_immediate(0);
		}
		/*
		 * oper->        deref
		 *  /  \   --->    |
		 * a    b        oper+
		 *               /   \
		 *              a  offset(b)
		 */
		return hir_unary_op(
				hir_cast(
					hir_binary_op(
						left,
						hir_load_immediate(member_offset( expr->datatype, right )),
						HIR_BINOP_ADD),
					type_pointer_to( member_type( expr->datatype, right ) )
					),
				HIR_UNARYOP_DEREF);
	}
	else //if(type == HIR_BINOP_DOT)
	{
		if( !type_is_struct(expr->datatype) )
		{
			error_non_struct();
			return hir_load_immediate(0);
		}
		/*
		 *  oper.        deref
		 *  /  \   --->    |
		 * a    b        oper+
		 *               /   \
		 *            addr offset(b)
		 *              |
		 *              a
		 */
		return hir_unary_op(
				hir_binary_op(
					hir_cast(hir_unary_op(left, HIR_UNARYOP_ADDRESS), type_pointer_to( member_type(expr->datatype, right) )),
					hir_load_immediate(member_offset( expr->datatype, right )),
					HIR_BINOP_ADD),
				HIR_UNARYOP_DEREF);
	}
}
//}}}
//{{{
hir_interm_t hir_unary_op(hir_interm_t child, int type)
{
	hir_expr_t *expr = (hir_expr_t*)malloc(sizeof(hir_expr_t));
	hir_unary_op_t *op = (hir_unary_op_t*)malloc(sizeof(hir_unary_op_t));
	
	if(expr==NULL || op==NULL)
		error_internal_memory();
	
	expr->type = HIR_EXPR_UNARYOP;
	expr->data.unary = op;
	expr->lineno = yylineno;
	expr->filename = input_filename;
	op->type = type;
	op->child = hir_pop_temp(child);
	
	if(type == HIR_UNARYOP_DEREF)
		expr->datatype = type_deref(op->child->datatype);
	else if(type == HIR_UNARYOP_ADDRESS)
		expr->datatype = type_pointer_to(op->child->datatype);
	else
		expr->datatype = op->child->datatype;
	
	return hir_write_temp(expr);
}
//}}}

hir_call_t *callstack[64];
int callstackpos = -1;
//{{{
void hir_start_call(id_handle_t id)
{
	int ii;
	int which_func = 0;
	
	assert(functions_num > 0);
	
	// Check that this function is declared
	for(ii=0; ii<functions_num; ii++)
	{
		if( idcmp(global_functions[ii].identifier, id) )
			break;
	}
	if(ii >= functions_num)
	{
		error_undeclared_function(id);
		which_func = 0;
	}
	else
		which_func = ii;
	
	callstack[++callstackpos] = (hir_call_t*)malloc(sizeof(hir_call_t));
	
	if(callstack[callstackpos] == NULL)
		error_internal_memory();
	
	callstack[callstackpos]->function = id;
	callstack[callstackpos]->type = global_functions[which_func].ret;
	init_block(&callstack[callstackpos]->params);
	push_block(&callstack[callstackpos]->params, HIR_BLOCK_CALL);
}
//}}}
//{{{
hir_interm_t hir_finish_call(void)
{
	hir_expr_t *expr = (hir_expr_t*)malloc(sizeof(hir_expr_t));
	
	if(expr==NULL)
		error_internal_memory();
	
	expr->type = HIR_EXPR_CALL;
	expr->datatype = callstack[callstackpos]->type;
	expr->data.call = callstack[callstackpos--];
	expr->lineno = yylineno;
	expr->filename = input_filename;
	
	pop_block();
	
	return hir_write_temp(expr);
}
//}}}

hir_ifelse_t *ifstack[64];
int ifstackpos = -1;
//{{{
void start_if_block(hir_interm_t condition)
{
	ifstack[++ifstackpos] = (hir_ifelse_t*)malloc(sizeof(hir_ifelse_t));
	ifstack[ifstackpos]->condition = hir_pop_temp(condition);
	ifstack[ifstackpos]->has_else = 0;
	
	init_block(&ifstack[ifstackpos]->body);
	init_block(&ifstack[ifstackpos]->alt);
	
	push_block(&ifstack[ifstackpos]->body, HIR_BLOCK_BRANCH);
}
//}}}
//{{{
void start_else_block(void)
{
	ifstack[ifstackpos]->has_else = 1;
	pop_block();
	push_block(&ifstack[ifstackpos]->alt, HIR_BLOCK_BRANCH);
}
//}}}
//{{{
void finish_if_block(void)
{
	hir_expr_t expr;
	
	pop_block();
	
	expr.type = HIR_EXPR_IFELSE;
	expr.lineno = yylineno;
	expr.filename = input_filename;
	expr.data.ifelse = ifstack[ifstackpos--];
	hir_write_expr(&expr);
}
//}}}


hir_loop_t *loopstack[64];
int loopstackpos = -1;
//{{{
static void start_loop(int type, hir_expr_t *initializer, hir_expr_t *condition, hir_expr_t *iterator)
{
	loopstack[++loopstackpos] = (hir_loop_t*)malloc(sizeof(hir_loop_t));
	
	loopstack[loopstackpos]->type = type;
	loopstack[loopstackpos]->initializer = initializer;
	loopstack[loopstackpos]->condition = condition;
	loopstack[loopstackpos]->iterator = iterator;
	
	init_block(&loopstack[loopstackpos]->body);
	push_block(&loopstack[loopstackpos]->body, HIR_BLOCK_LOOP);
}
//}}}
//{{{
static void finish_loop(hir_expr_t *condition)
{
	hir_expr_t expr;
	
	pop_block();
	
	if(condition != NULL) {
		loopstack[loopstackpos]->condition = condition;
	}
	
	expr.type = HIR_EXPR_LOOP;
	expr.lineno = yylineno;
	expr.filename = input_filename;
	expr.data.loop = loopstack[loopstackpos--];
	hir_write_expr(&expr);

}
//}}}
//{{{
void start_do_while_block(void)
{
	start_loop(HIR_LOOP_DOWHILE, NULL, NULL, NULL);
}
//}}}
//{{{
void finish_do_while_block(hir_interm_t condition)
{
	finish_loop(hir_pop_temp(condition));
}
//}}}

//{{{
void start_while_block(hir_interm_t condition)
{
	start_loop(HIR_LOOP_WHILE, NULL, hir_pop_temp(condition), NULL);
}
//}}}
//{{{
void finish_while_block(void)
{
	finish_loop(NULL);
}
//}}}

//{{{
void start_for_block(hir_interm_t initializer, hir_interm_t condition, hir_interm_t iterator)
{
	 start_loop(HIR_LOOP_FOR, hir_pop_temp(initializer), hir_pop_temp(condition), hir_pop_temp(iterator));
}
//}}}
//{{{
void finish_for_block(void)
{
	finish_loop(NULL);
}
//}}}

//{{{
static void hir_write_abort(int type, int levels)
{
	hir_expr_t *expr = (hir_expr_t*)malloc(sizeof(hir_expr_t));
	hir_abort_t *abort = (hir_abort_t*)malloc(sizeof(hir_abort_t));
	
	expr->type = HIR_EXPR_ABORT;
	expr->lineno = yylineno;
	expr->filename = input_filename;
	expr->data.abort = abort;
	abort->type = type;
	abort->levels = levels;
	
	hir_write_expr(expr);
	free(expr);
}
//}}}
//{{{
void hir_break(int levels)
{
	hir_write_abort(HIR_ABORT_BREAK, levels);
}
//}}}
//{{{
void hir_continue(int levels)
{
	hir_write_abort(HIR_ABORT_CONTINUE, levels);
}
//}}}

hir_block_t **block_stack = NULL;
int block_depth = 0, block_alloc = 0;
//{{{
static void init_block(hir_block_t *block)
{
	block->code = NULL;
	block->code_lines = 0;
	block->code_alloc = 0;
}
//}}}
//{{{
static void push_block(hir_block_t *block, int type)
{
	expand_table((void*)&block_stack, &block_alloc, block_depth+1, sizeof(hir_block_t*));
	
	block->type = type;
	block_stack[block_depth++] = block;
}
//}}}
//{{{
static hir_block_t *current_block(void)
{
	assert(block_depth > 0);
	return block_stack[block_depth - 1];
}
//}}}
//{{{
static void pop_block(void)
{
	assert(block_depth > 0);
	
	block_depth --;
}
//}}}
//{{{
void hir_finish_expr(hir_interm_t handle)
{
	hir_expr_t *expr;
	
	expand_table( (void**)&current_block()->code, &current_block()->code_alloc, current_block()->code_lines + 1, sizeof(hir_expr_t) );
	
	expr = hir_pop_temp(handle);
	current_block()->code[current_block()->code_lines++] = *expr;
	free(expr);
}
//}}}
//{{{
static void hir_write_expr(hir_expr_t *expr)
{
	expand_table( (void**)&current_block()->code, &current_block()->code_alloc, current_block()->code_lines + 1, sizeof(hir_expr_t) );
	
	current_block()->code[current_block()->code_lines++] = *expr;
}
//}}}

