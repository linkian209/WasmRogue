#include <stdio.h>
#include <assert.h>
#include "hir.h"

static void hir_debug_print_block(hir_block_t *block, int indentation);
static void hir_debug_print_func(hir_func_t *f);
static void hir_debug_print_expr(hir_expr_t *expr, int indentation);
static void hir_debug_print_binop(hir_binary_op_t *expr);
static void hir_debug_print_unaryop(hir_unary_op_t *expr);
static void hir_debug_print_terminal(hir_terminal_t *expr);
static void hir_debug_print_call(hir_call_t *expr, int indentation);

//{{{
void hir_debug_print_all(void)
{
	int ii;
	
	for(ii=0; ii<functions_num; ii++)
		hir_debug_print_func( &global_functions[ii] );
}
//}}}
//{{{
static void hir_debug_print_func(hir_func_t *f)
{
	int i;
	hir_var_t *v;
	
	for(i=0; i<f->vars_num; i++)
	{
		v = &f->vars[i];
		printf("%2i: (%i) %s\n", v->index, v->type, get_identifier_string(v->id));
	}
	
	hir_debug_print_block(&f->body, 0);
}
//}}}
//{{{
static void hir_debug_print_block(hir_block_t *block, int indentation)
{
	int ii;
	int jj;
	
	for(ii=0; ii<block->code_lines; ii++)
	{
		for(jj=0; jj<indentation; jj++)
			printf("    ");
		hir_debug_print_expr(&block->code[ii], indentation);
		putchar('\n');
	}
}
//}}}
//{{{
static void hir_debug_print_expr(hir_expr_t *expr, int indentation)
{
	assert(expr != NULL);
	
	switch(expr->type)
	{
		case HIR_EXPR_BINOP:
			hir_debug_print_binop(expr->data.binary);
			break;
		case HIR_EXPR_UNARYOP:
			hir_debug_print_unaryop(expr->data.unary);
			break;
		case HIR_EXPR_TERM:
			hir_debug_print_terminal(expr->data.terminal);
			break;
		case HIR_EXPR_CALL:
			hir_debug_print_call(expr->data.call, indentation);
			break;
		case HIR_EXPR_IFELSE:
			break;
		case HIR_EXPR_LOOP:
			break;
		case HIR_EXPR_ABORT:
			break;
	}
}
//}}}
//{{{
static void hir_debug_print_binop(hir_binary_op_t *expr)
{
	assert(expr != NULL);
	
	switch(expr->type)
	{
		case HIR_BINOP_ADD:    printf("add");    break;
		case HIR_BINOP_SUB:    printf("sub");    break;
		case HIR_BINOP_MUL:    printf("mul");    break;
		case HIR_BINOP_DIV:    printf("div");    break;
		case HIR_BINOP_MOD:    printf("mod");    break;
		case HIR_BINOP_LSHIFT: printf("lshift"); break;
		case HIR_BINOP_RSHIFT: printf("rshift"); break;
		case HIR_BINOP_LT:     printf("lt");     break;
		case HIR_BINOP_LTEQ:   printf("lteq");   break;
		case HIR_BINOP_GT:     printf("gt");     break;
		case HIR_BINOP_GTEQ:   printf("gteq");   break;
		case HIR_BINOP_EQEQ:   printf("cmp");    break;
		case HIR_BINOP_NEQ:    printf("neq");    break;
		case HIR_BINOP_AND:    printf("and");    break;
		case HIR_BINOP_XOR:    printf("xor");    break;
		case HIR_BINOP_OR:     printf("or");     break;
		case HIR_BINOP_ANDAND: printf("band");   break;
		case HIR_BINOP_OROR:   printf("bor");    break;
		case HIR_BINOP_EQ:     printf("eq");     break;
		case HIR_BINOP_ADDEQ:  printf("addeq");  break;
		case HIR_BINOP_SUBEQ:  printf("subeq");  break;
		case HIR_BINOP_MULEQ:  printf("muleq");  break;
		case HIR_BINOP_DIVEQ:  printf("diveq");  break;
		case HIR_BINOP_MODEQ:  printf("modeq");  break;
		case HIR_BINOP_ANDEQ:  printf("andeq");  break;
		case HIR_BINOP_XOREQ:  printf("xoreq");  break;
		case HIR_BINOP_OREQ:   printf("oreq");   break;
		case HIR_BINOP_LSFTEQ: printf("lsfteq"); break;
		case HIR_BINOP_RSFTEQ: printf("rsfteq"); break;
		case HIR_BINOP_COMMA:  printf("comma");  break;
		case HIR_BINOP_ARRAY:  printf("deref");  break;
		default:               printf("invalid");break;
	}
	
	printf("(");
	hir_debug_print_expr(expr->left, 0);
	printf(", ");
	hir_debug_print_expr(expr->right, 0);
	printf(")");
}
//}}}
//{{{
static void hir_debug_print_unaryop(hir_unary_op_t *expr)
{
	assert(expr != NULL);
	
	switch(expr->type)
	{
		case HIR_UNARYOP_POSTINCR: printf("postincr"); break;
		case HIR_UNARYOP_POSTDECR: printf("postdecr"); break;
		case HIR_UNARYOP_BOOLNOT:  printf("boolnot");  break;
		case HIR_UNARYOP_BITNOT:   printf("bitnot");   break;
		case HIR_UNARYOP_PREINCR:  printf("preincr");  break;
		case HIR_UNARYOP_PREDECR:  printf("predecr");  break;
		case HIR_UNARYOP_NEG:      printf("neg");      break;
		case HIR_UNARYOP_DEREF:    printf("deref");    break;
		case HIR_UNARYOP_ADDRESS:  printf("address");  break;
		case HIR_UNARYOP_ALLOCA:   printf("alloca");   break;
		default:                   printf("invalid");  break;
	}
	printf("(");
	hir_debug_print_expr(expr->child, 0);
	printf(")");
}
//}}}
//{{{
static void hir_debug_print_terminal(hir_terminal_t *expr)
{
	assert(expr != NULL);
	
	switch(expr->type)
	{
		case HIR_TERM_IMMED:
			printf("#%li", expr->value);
			break;
		case HIR_TERM_VAR:
			printf("%%%li", expr->value);
			break;
		case HIR_TERM_LABEL:
			printf("%s", get_identifier_string(expr->target));
			break;
	}
}
//}}}
//{{{
static void hir_debug_print_call(hir_call_t *expr, int indentation)
{
	int ii;
	
	printf("CALL(%s,\n", get_identifier_string(expr->function));
	hir_debug_print_block(&expr->params, indentation+1);
	
	for(ii=0; ii<indentation; ii++) printf("    ");
	
	printf(")");
}
//}}}

