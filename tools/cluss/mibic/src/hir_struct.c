#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hir.h"
#include "util.h"
#include "type.h"

hir_struct_t *global_structs = NULL;
int structs_num = 0, structs_alloc = 0;

hir_struct_t current_struct;

//{{{
void hir_start_struct(id_handle_t identifier, int is_union)
{
	current_struct.identifier = identifier;
	current_struct.datasize = 0;
	current_struct.is_union = is_union;
	current_struct.elements = NULL;
	current_struct.elements_num = 0;
	current_struct.elements_alloc = 0;
}
//}}}
//{{{
void hir_add_member(type_handle_t type, id_handle_t identifier)
{
	hir_struct_member_t addition;
	
	expand_table((void**)&current_struct.elements, &current_struct.elements_alloc, current_struct.elements_num+1, sizeof(hir_struct_member_t));
	
	addition.identifier = identifier;
	addition.type = type;
	
	if(current_struct.is_union == 0)
	{
		addition.offset = current_struct.datasize;
		
		// Align to even addresses
		if( type_size(type) > 1 && (addition.offset & 1) )
		{
			addition.offset++;
			current_struct.datasize++;
		}
		current_struct.datasize += type_size(type);
	}
	else
	{
		if( type_size(type) > current_struct.datasize )
			current_struct.datasize = type_size(type);
		addition.offset = 0;
	}
	
	current_struct.elements[current_struct.elements_num++] = addition;
}
//}}}
//{{{
//
// Convert the last element of a struct to an array of same type
//
void hir_member_array(hir_interm_t num_elements)
{
	hir_struct_member_t *member = &current_struct.elements[current_struct.elements_num - 1];
	
	long v;
	hir_expr_t *value_expr;
	
	value_expr = hir_pop_temp(num_elements);
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
	
	current_struct.datasize -= type_size(member->type);
	member->type = type_array_of(member->type, v);
	current_struct.datasize += type_size(member->type);
}
//}}}
//{{{
void hir_finish_struct(void)
{
	// Fit to even size
	if(current_struct.datasize & 1)
		current_struct.datasize++;
	
	// Store struct
	expand_table( (void*)&global_structs, &structs_alloc, structs_num+1, sizeof(hir_struct_t) );
	global_structs[structs_num++] = current_struct;
	
	// DEBUG: Print elements and offsets
/*	printf("struct %s (size %i)\n", get_identifier_string(current_struct.identifier), current_struct.datasize);
	for(i=0; i<current_struct.elements_num; i++)
	{
		type_print(current_struct.elements[i].type);
		printf("\tat +%i: %s\n",
			current_struct.elements[i].offset,
			get_identifier_string(current_struct.elements[i].identifier));
	}*/
}
//}}}

//{{{
type_handle_t find_struct(id_handle_t identifier)
{
	int ii;
	
	for(ii=0; ii<structs_num; ii++)
	{
		if( idcmp(global_structs[ii].identifier, identifier) )
			return ii;
	}
	return -1;
}
//}}}
//{{{
int member_offset(type_handle_t type, id_handle_t member)
{
	hir_struct_t *struct_type;
	int ii;
	
	if(type_is_pointer(type))
		type = type_deref(type);
	
	assert(type_is_struct(type));
	
	struct_type = get_struct(type);
	
	for(ii=0; ii<struct_type->elements_num; ii++)
	{
		if(idcmp(member, struct_type->elements[ii].identifier))
			return struct_type->elements[ii].offset;
	}
	error_non_member(get_identifier_string(member));
	return 0;
}
//}}}
//{{{
type_handle_t member_type(type_handle_t type, id_handle_t member)
{
	hir_struct_t *struct_type;
	int ii;
	
	if(type_is_pointer(type))
		type = type_deref(type);
	
	assert(type_is_struct(type));
	
	struct_type = get_struct(type);
	
	for(ii=0; ii<struct_type->elements_num; ii++)
	{
		if(idcmp(member, struct_type->elements[ii].identifier))
		{
			return struct_type->elements[ii].type;
		}
	}
	error_non_member(get_identifier_string(member));
	return type_base(type_int);
}
//}}}

