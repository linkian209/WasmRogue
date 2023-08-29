#ifndef HIR_H
#define HIR_H

typedef int hir_interm_t;

#include "namespace.h"
#include "type.h"
#include "hir_struct.h"

//{{{
#define HIR_BLOCK_FUNC        0
#define HIR_BLOCK_LOOP        1
#define HIR_BLOCK_CALL        2
#define HIR_BLOCK_BRANCH      3
//}}}
//{{{
typedef struct hir_block
{
	int type;
	struct hir_expr *code;
	int code_lines, code_alloc;
} hir_block_t;
//}}}

//{{{
#define HIR_TERM_IMMED        1
#define HIR_TERM_VAR          2
#define HIR_TERM_LABEL        3
//}}}
//{{{
typedef struct hir_terminal
{
	int type;
	long value;
	id_handle_t target;
} hir_terminal_t;
//}}}

//{{{
#define HIR_BINOP_ADD         1
#define HIR_BINOP_SUB         2
#define HIR_BINOP_MUL         3
#define HIR_BINOP_DIV         4
#define HIR_BINOP_MOD         5
#define HIR_BINOP_LSHIFT      6
#define HIR_BINOP_RSHIFT      7
#define HIR_BINOP_LT          8
#define HIR_BINOP_LTEQ        9
#define HIR_BINOP_GT          10
#define HIR_BINOP_GTEQ        11
#define HIR_BINOP_EQEQ        12
#define HIR_BINOP_NEQ         13
#define HIR_BINOP_AND         14
#define HIR_BINOP_XOR         15
#define HIR_BINOP_OR          16
#define HIR_BINOP_ANDAND      17
#define HIR_BINOP_OROR        18
#define HIR_BINOP_EQ          19
#define HIR_BINOP_ADDEQ       20
#define HIR_BINOP_SUBEQ       21
#define HIR_BINOP_MULEQ       22
#define HIR_BINOP_DIVEQ       23
#define HIR_BINOP_MODEQ       24
#define HIR_BINOP_ANDEQ       25
#define HIR_BINOP_XOREQ       26
#define HIR_BINOP_OREQ        27
#define HIR_BINOP_LSFTEQ      28
#define HIR_BINOP_RSFTEQ      29
#define HIR_BINOP_COMMA       30
#define HIR_BINOP_ARRAY       31
#define HIR_BINOP_DOT         32
#define HIR_BINOP_ARROW       33
//}}}
//{{{
typedef struct hir_binary_op
{
	int type;
	struct hir_expr *left, *right;
} hir_binary_op_t;
//}}}

//{{{
#define HIR_UNARYOP_RETURN   0
#define HIR_UNARYOP_POSTINCR 1
#define HIR_UNARYOP_POSTDECR 2
#define HIR_UNARYOP_BOOLNOT  3
#define HIR_UNARYOP_BITNOT   4
#define HIR_UNARYOP_PREINCR  5
#define HIR_UNARYOP_PREDECR  6
#define HIR_UNARYOP_NEG      7
#define HIR_UNARYOP_DEREF    8
#define HIR_UNARYOP_ADDRESS  9
#define HIR_UNARYOP_ALLOCA   10
#define HIR_UNARYOP_CAST     11
//}}}
//{{{
typedef struct hir_unary_op
{
	int type;
	struct hir_expr *child;
} hir_unary_op_t;
//}}}

//{{{
typedef struct hir_call
{
	id_handle_t function;
	type_handle_t type;
	hir_block_t params;
} hir_call_t;
//}}}

//{{{
typedef struct hir_ifelse
{
	struct hir_expr *condition;
	hir_block_t body, alt;
	int has_else;
} hir_ifelse_t;
//}}}

//{{{
#define HIR_LOOP_DOWHILE      1
#define HIR_LOOP_WHILE        2
#define HIR_LOOP_FOR          3
//}}}
//{{{
typedef struct hir_loop
{
	int type;
	
	struct hir_expr *initializer;
	struct hir_expr *condition;
	struct hir_expr *iterator;
	
	hir_block_t body;
} hir_loop_t;
//}}}

//{{{
#define HIR_ABORT_BREAK       1
#define HIR_ABORT_CONTINUE    2
//}}}
//{{{
typedef struct hir_abort
{
	int type;
	int levels;
} hir_abort_t;
//}}}

//{{{
#define HIR_EXPR_BINOP        1
#define HIR_EXPR_UNARYOP      2
#define HIR_EXPR_TERM         3
#define HIR_EXPR_CALL         4
#define HIR_EXPR_IFELSE       5
#define HIR_EXPR_LOOP         6
#define HIR_EXPR_ABORT        7
//}}}
//{{{
typedef struct hir_expr
{
	int type;
	type_handle_t datatype;
	int lineno;
	char *filename;
	union {
		struct hir_binary_op *binary;
		struct hir_unary_op *unary;
		struct hir_terminal *terminal;
		struct hir_call *call;
		struct hir_ifelse *ifelse;
		struct hir_loop *loop;
		struct hir_abort *abort;
	} data;
} hir_expr_t;
//}}}

//{{{
#define HIR_INIT_NONE         0
#define HIR_INIT_NUMERIC      1
//}}}
//{{{
typedef struct hir_initializer
{
	int type;
	hir_expr_t *value;
} hir_initializer_t;
//}}}

//{{{
typedef struct hir_var
{
	type_handle_t type;
	id_handle_t id;
	int index;
	
	hir_initializer_t initializer;
} hir_var_t;
//}}}

//{{{
typedef struct hir_func
{
	id_handle_t identifier;
	type_handle_t ret;
	char is_extern, has_body;
	int extern_index;
	
	hir_var_t *vars;
	int vars_num, vars_alloc;
	int params_num;
	
	hir_block_t body;
} hir_func_t;
//}}}

void free_block_contents(hir_block_t *block);
void free_expr(hir_expr_t *expr);
void free_expr_contents(hir_expr_t *expr);

void hir_done(void);

void hir_start_func(type_handle_t return_type, id_handle_t identifier);
void hir_add_variable(type_handle_t type, id_handle_t identifier, int is_param);
void hir_finish_prototype(void);
void hir_finish_extern_func(int index);
void hir_finish_func_body(void);

hir_interm_t hir_load_immediate(long value);
hir_interm_t hir_load_string(char *str);
hir_interm_t hir_load_variable(id_handle_t identifier);
hir_interm_t hir_binary_op(hir_interm_t left, hir_interm_t right, int type);
hir_interm_t hir_cast(hir_interm_t child, type_handle_t type);
hir_interm_t hir_selection_op(hir_interm_t left, id_handle_t right, int type);
hir_interm_t hir_unary_op(hir_interm_t child, int type);
void hir_finish_expr(hir_interm_t handle);

hir_interm_t hir_write_temp(hir_expr_t *expr);
hir_expr_t *hir_pop_temp(hir_interm_t t);

void hir_debug_print_all(void);

void hir_start_call(id_handle_t id);
hir_interm_t hir_finish_call(void);

void start_if_block(hir_interm_t condition);
void start_else_block(void);
void finish_if_block(void);

void start_do_while_block(void);
void finish_do_while_block(hir_interm_t condition);

void start_while_block(hir_interm_t condition);
void finish_while_block(void);

void start_for_block(hir_interm_t initializer, hir_interm_t condition, hir_interm_t iterator);
void finish_for_block(void);

void hir_break(int levels);
void hir_continue(int levels);

void hir_reduce(void);
void hir_reduce_pointers(void);

extern hir_func_t *global_functions;
extern int functions_num, functions_alloc;

int hir_is_constant(id_handle_t identifier);
long hir_get_constant_value(id_handle_t identifier);
void hir_write_constant(id_handle_t identifier, hir_interm_t value);
void hir_emit_constant(type_handle_t type, hir_interm_t value);
void hir_emit_string(char *str);
void hir_emit_link(id_handle_t id);
void hir_emit_label(id_handle_t id, hir_interm_t flags, hir_interm_t offset);

void hir_pointers_expr(hir_expr_t *expr);

#endif

