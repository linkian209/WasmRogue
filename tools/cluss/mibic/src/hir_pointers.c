#include <stdlib.h>
#include <assert.h>
#include "hir.h"

static void hir_pointers_function(hir_func_t *func);
static void hir_pointers_block(hir_block_t *block);
static void hir_pointers_binop(hir_expr_t *expr);
static void hir_pointers_unaryop(hir_expr_t *expr);
static void hir_pointers_call(hir_call_t *expr);
static void hir_pointers_ifelse(hir_ifelse_t *expr);
static void hir_pointers_loop(hir_loop_t *expr);

static int hir_is_numeric(hir_expr_t *expr);
static long hir_get_numeric(hir_expr_t *expr);
static int operator_is_commutative(int oper);
static int operator_is_identity(int oper, int num);

//{{{
void hir_reduce_pointers(void)
{
	int ii;
	
	for(ii=0; ii<functions_num; ii++)
		hir_pointers_function(&global_functions[ii]);
}
//}}}
//{{{
static void hir_pointers_function(hir_func_t *func)
{
	assert(func);
	
	if(!func->has_body)
		return;
	hir_pointers_block(&func->body);
}
//}}}
//{{{
static void hir_pointers_block(hir_block_t *block)
{
	int ii;
	
	assert(block);
	
	for(ii=0; ii<block->code_lines; ii++)
		hir_pointers_expr(&block->code[ii]);
}
//}}}
//{{{
void hir_pointers_expr(hir_expr_t *expr)
{
	assert(expr);
	
	switch(expr->type)
	{
		case HIR_EXPR_BINOP:
			hir_pointers_binop(expr);
			break;
		case HIR_EXPR_UNARYOP:
			hir_pointers_unaryop(expr);
			break;
		case HIR_EXPR_TERM:
			break;
		case HIR_EXPR_CALL:
			hir_pointers_call(expr->data.call);
			break;
		case HIR_EXPR_IFELSE:
			hir_pointers_ifelse(expr->data.ifelse);
			break;
		case HIR_EXPR_LOOP:
			hir_pointers_loop(expr->data.loop);
			break;
		case HIR_EXPR_ABORT:
			break;
	}
}
//}}}

//{{{
static void hir_pointers_binop(hir_expr_t *expr)
{
	hir_interm_t construction;
	long tmp;
	long tmp1, tmp2;
	hir_expr_t *tmp_expr;
	
	assert(expr);
	
	hir_pointers_expr(expr->data.binary->left);
	hir_pointers_expr(expr->data.binary->right);
	
	
	/*
	 *      pointer               Deref
	 *       op[]         --->   Pointer
	 *       /   \                  |
	 *    Ptr     Index            Add
	 *                            /   \
	 *                          Ptr   Mul
	 *                               /   \
	 *                            Index Size
	 */
	if(expr->data.binary->type == HIR_BINOP_ARRAY)
	{
//		if(type_is_array(expr->data.binary->left->datatype))
//		{
//		} else
//		{
			assert( type_is_pointer(expr->data.binary->left->datatype) || type_is_array(expr->data.binary->left->datatype) );
			
			tmp = type_size(type_deref(expr->data.binary->left->datatype));
			
			construction = hir_write_temp(expr->data.binary->left);
			if(type_is_array(expr->data.binary->left->datatype))
				construction = hir_cast( hir_unary_op( construction, HIR_UNARYOP_ADDRESS ),
				                         expr->data.binary->left->datatype );
			
			construction = \
				hir_binary_op(
					construction,
					hir_binary_op(
						hir_write_temp(expr->data.binary->right),
						hir_load_immediate(tmp),
						HIR_BINOP_MUL
						),
					HIR_BINOP_ADD
					);
			
			free(expr->data.binary);
			
			expr->type = HIR_EXPR_UNARYOP;
			expr->data.unary = (hir_unary_op_t*)malloc(sizeof(hir_unary_op_t));
			expr->data.unary->type = HIR_UNARYOP_DEREF;
			expr->data.unary->child = hir_pop_temp(construction);
			expr->datatype = type_deref(expr->data.unary->child->datatype);
			
			hir_pointers_unaryop( expr );
			
			return;
//		}
	}
	
	/*
	 *    Oper
	 *    /  \    ---> Num
	 *  Num  Num
	 */
	if(hir_is_numeric(expr->data.binary->left) &&
	   hir_is_numeric(expr->data.binary->right)
	  )
	{
		tmp1 = hir_get_numeric(expr->data.binary->left);
		tmp2 = hir_get_numeric(expr->data.binary->right);
		
		switch(expr->data.binary->type)
		{
			case HIR_BINOP_ADD:     tmp = tmp1 +  tmp2; break;
			case HIR_BINOP_SUB:     tmp = tmp1 -  tmp2; break;
			case HIR_BINOP_MUL:     tmp = tmp1 *  tmp2; break;
			case HIR_BINOP_DIV:     tmp = tmp1 /  tmp2; break;
			case HIR_BINOP_MOD:     tmp = tmp1 %  tmp2; break;
			case HIR_BINOP_LSHIFT:  tmp = tmp1 << tmp2; break;
			case HIR_BINOP_RSHIFT:  tmp = tmp1 >> tmp2; break;
			case HIR_BINOP_LT:      tmp = tmp1 <  tmp2; break;
			case HIR_BINOP_LTEQ:    tmp = tmp1 <= tmp2; break;
			case HIR_BINOP_GT:      tmp = tmp1 >  tmp2; break;
			case HIR_BINOP_GTEQ:    tmp = tmp1 >= tmp2; break;
			case HIR_BINOP_EQEQ:    tmp = tmp1 == tmp2; break;
			case HIR_BINOP_NEQ:     tmp = tmp1 != tmp2; break;
			case HIR_BINOP_AND:     tmp = tmp1 &  tmp2; break;
			case HIR_BINOP_XOR:     tmp = tmp1 ^  tmp2; break;
			case HIR_BINOP_OR:      tmp = tmp1 |  tmp2; break;
			case HIR_BINOP_ANDAND:  tmp = tmp1 && tmp2; break;
			case HIR_BINOP_OROR:    tmp = tmp1 || tmp2; break;
			case HIR_BINOP_COMMA:   tmp = tmp1 ,  tmp2; break;
			default: return;
		}
		
		free_expr_contents(expr);
		
		expr->type = HIR_EXPR_TERM;
		expr->data.terminal = malloc(sizeof(hir_terminal_t));
		expr->data.terminal->type = HIR_TERM_IMMED;
		expr->data.terminal->value = tmp;
		
		return;
	}
	
	/*
	 *   oper          oper
	 *   /  \    --->  /  \
	 *  num expr     expr num
	 *
	 *  oper E '+' '*' '&' '|' '&&' '||' '^' '=='
	 */
	if( hir_is_numeric(expr->data.binary->left) && operator_is_commutative(expr->data.binary->type) )
	{
		tmp_expr = expr->data.binary->left;
		expr->data.binary->left = expr->data.binary->right;
		expr->data.binary->right = tmp_expr;
	}
	
	/*
	 *   Oper
	 *   /   \               --> expr
	 * expr identity(oper)
	 */
	if( hir_is_numeric(expr->data.binary->right) &&
	    operator_is_identity(expr->data.binary->type, hir_get_numeric(expr->data.binary->right)) &&
		( expr->data.binary->type == HIR_BINOP_ADD ||
	      expr->data.binary->type == HIR_BINOP_SUB
		)
	  )
	{
		free_expr_contents(expr->data.binary->right);
		free(expr->data.binary->right);
		
		tmp_expr = expr->data.binary->left;
		expr->type = tmp_expr->type;
		expr->data = tmp_expr->data;
		free(tmp_expr);
	}
}
//}}}
//{{{
static void hir_pointers_unaryop(hir_expr_t *expr)
{
	hir_expr_t *tmp;
	long tmpval;
	
	assert(expr);
	
	hir_pointers_expr(expr->data.unary->child);
	
	/*
	 *   Addressof    Deref
	 *      |        Pointer
	 *     Deref  ,     |        --->  expr
	 *    Pointer   Addressof
	 *      |           |
	 *    expr        expr
	 */
	if( (
	     expr->data.unary->type == HIR_UNARYOP_ADDRESS &&
	     expr->data.unary->child->type == HIR_EXPR_UNARYOP &&
	     expr->data.unary->child->data.unary->type == HIR_UNARYOP_DEREF
	    ) || (
	     expr->data.unary->type == HIR_UNARYOP_DEREF &&
	     expr->data.unary->child->type == HIR_EXPR_UNARYOP &&
	     expr->data.unary->child->data.unary->type == HIR_UNARYOP_ADDRESS
	    )
	  )
	{
		tmp = expr->data.unary->child->data.unary->child;
		free(expr->data.unary->child->data.unary);
		free(expr->data.unary->child);
		free(expr->data.unary);
		*expr = *tmp;
		free(tmp);
		return;
	}

	/*
	 *   Oper
	 *    |    ---->  Num
	 *   Num
	 */
	if(hir_is_numeric(expr->data.unary->child))
	{
		tmpval = hir_get_numeric(expr->data.unary->child);
		
		switch(expr->data.unary->type)
		{
			case HIR_UNARYOP_BOOLNOT:
				tmpval = !tmpval;
				break;
			case HIR_UNARYOP_BITNOT:
				tmpval = ~tmpval;
				break;
			case HIR_UNARYOP_NEG:
				tmpval = -tmpval;
				break;
			
			case HIR_UNARYOP_RETURN:
			case HIR_UNARYOP_POSTINCR:
			case HIR_UNARYOP_POSTDECR:
			case HIR_UNARYOP_PREINCR:
			case HIR_UNARYOP_PREDECR:
			case HIR_UNARYOP_ALLOCA:
			case HIR_UNARYOP_DEREF:
			case HIR_UNARYOP_ADDRESS:
				return;
		}
		
		free_expr_contents(expr);
		expr->type = HIR_EXPR_TERM;
		expr->data.terminal = malloc(sizeof(hir_terminal_t));
		expr->data.terminal->type = HIR_TERM_IMMED;
		expr->data.terminal->value = tmpval;
		
		return;
	}
}
//}}}
//{{{
static void hir_pointers_call(hir_call_t *expr)
{
	int ii;
	
	assert(expr);
	
	for(ii=0; ii<expr->params.code_lines; ii++)
		hir_pointers_expr(&expr->params.code[ii]);
}
//}}}
//{{{
static void hir_pointers_ifelse(hir_ifelse_t *expr)
{
	assert(expr);
	
	hir_pointers_expr(expr->condition);
	hir_pointers_block(&expr->body);
	if(expr->alt.code_lines > 0)
		hir_pointers_block(&expr->alt);
}
//}}}
//{{{
static void hir_pointers_loop(hir_loop_t *expr)
{
	assert(expr);
	
	if(expr->initializer)
		hir_pointers_expr(expr->initializer);
	if(expr->iterator)
		hir_pointers_expr(expr->iterator);
	if(expr->condition)
		hir_pointers_expr(expr->condition);
	hir_pointers_block(&expr->body);
}
//}}}

//{{{
static int hir_is_numeric(hir_expr_t *expr)
{
	if(expr->type == HIR_EXPR_TERM && expr->data.terminal->type == HIR_TERM_IMMED)
		return 1;
	else
		return 0;
}
//}}}
//{{{
static long hir_get_numeric(hir_expr_t *expr)
{
	return expr->data.terminal->value;
}
//}}}

//{{{
static int operator_is_commutative(int oper)
{
	switch(oper)
	{
		case HIR_BINOP_ADD:
		case HIR_BINOP_MUL:
		case HIR_BINOP_AND:
		case HIR_BINOP_OR:
		case HIR_BINOP_ANDAND:
		case HIR_BINOP_OROR:
		case HIR_BINOP_XOR:
		case HIR_BINOP_EQEQ:
			return 1;
		default:
			return 0;
	}
}
//}}}
//{{{
static int operator_is_identity(int oper, int num)
{
	switch(oper)
	{
		case HIR_BINOP_ADD:
		case HIR_BINOP_SUB:
			return( num==0 );
		case HIR_BINOP_MUL:
		case HIR_BINOP_DIV:
			return( num==1 );
		case HIR_BINOP_ANDAND:
			return num;
		case HIR_BINOP_XOR:
			return( num==0xFFFFFFFF );
		default:
			return 0;
	}
}
//}}}
