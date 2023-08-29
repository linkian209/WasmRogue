#include <stdlib.h>
#include "hir.h"
#include "lir.h"
#include "util.h"

typedef struct hir_const
{
	id_handle_t id;
	long value;
} hir_const_t;

hir_const_t *constants_table = NULL;
int constants_num = 0, constants_alloc = 0;

//{{{
int hir_is_constant(id_handle_t identifier)
{
	int ii;
	for(ii=0; ii<constants_num; ii++)
	{
		if(idcmp(constants_table[ii].id, identifier))
			return 1;
	}
	return 0;
}
//}}}
//{{{
long hir_get_constant_value(id_handle_t identifier)
{
	int ii;
	for(ii=0; ii<constants_num; ii++)
	{
		if(idcmp(constants_table[ii].id, identifier))
			return constants_table[ii].value;
	}
	return 0;
}
//}}}

//{{{
void hir_write_constant(id_handle_t identifier, hir_interm_t value)
{
	hir_const_t addition;
	hir_expr_t *value_expr;
	
	addition.id = identifier;
	
	value_expr = hir_pop_temp(value);
	hir_pointers_expr(value_expr);
	if(value_expr->type != HIR_EXPR_TERM || value_expr->data.terminal->type != HIR_TERM_IMMED)
	{
		error_non_constant();
		addition.value = 0;
	} else
	{
		addition.value = value_expr->data.terminal->value;
	}
	free_expr_contents(value_expr);
	free(value_expr);
	
	expand_table( (void*)&constants_table, &constants_alloc, constants_num+1, sizeof(hir_const_t) );
	constants_table[constants_num++] = addition;
}
//}}}
//{{{
void hir_emit_constant(type_handle_t type, hir_interm_t value)
{
	long v;
	hir_expr_t *value_expr;
	
	value_expr = hir_pop_temp(value);
	hir_pointers_expr(value_expr);
	if(value_expr->type != HIR_EXPR_TERM || value_expr->data.terminal->type != HIR_TERM_IMMED)
	{
		error_non_constant();
		v = 0;
	} else {
		v = value_expr->data.terminal->value;
	}
	free_expr_contents(value_expr);
	free(value_expr);
	
	switch(type_size(type))
	{
		case 1:
			lir_write_inst_immediate(LIR_CHAR, v);
			break;
		case 2:
			lir_write_inst(LIR_EVEN);
			lir_write_inst_immediate(LIR_SHORT, v);
			break;
		case 4:
			lir_write_inst(LIR_EVEN);
			lir_write_inst_immediate(LIR_LONG, v);
			break;
	}
}
//}}}
//{{{
void hir_emit_string(char *str)
{
	while(*str != '\0')
	{
		lir_write_inst_immediate(LIR_CHAR, *str);
		str++;
	}
	lir_write_inst_immediate(LIR_CHAR, '\0');
}
//}}}
//{{{
void hir_emit_link(id_handle_t id)
{
	lir_write_inst(LIR_EVEN);
	lir_write_inst_label(LIR_FLINK, id);
}
//}}}
//{{{
void hir_emit_label(id_handle_t id, hir_interm_t flags, hir_interm_t offset)
{
	hir_expr_t *flags_expr, *offset_expr;
	short flags_val = 0, offset_val;
	
	flags_expr = hir_pop_temp(flags);
	hir_pointers_expr(flags_expr);
	if(flags_expr->type != HIR_EXPR_TERM || flags_expr->data.terminal->type != HIR_TERM_IMMED)
		error_non_constant();
	else
		flags_val = flags_expr->data.terminal->value;
	
	free_expr_contents(flags_expr);
	free(flags_expr);
	
	if(offset == -1)
		lir_write_label_flags(id, flags_val, 0, 0);
	else
	{
		offset_val = 0;
		offset_expr = hir_pop_temp(offset);
		hir_pointers_expr(offset_expr);
		if(offset_expr->type != HIR_EXPR_TERM || offset_expr->data.terminal->type != HIR_TERM_IMMED)
			error_non_constant();
		else
			offset_val = offset_expr->data.terminal->value;
		free_expr_contents(offset_expr);
		free(offset_expr);
		
		lir_write_label_flags(id, flags_val, offset_val, 1);
	}
}
//}}}


