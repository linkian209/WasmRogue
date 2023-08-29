#include <assert.h>
#include "compile.h"
#include "hir.h"
#include "type.h"
#include "util.h"

hir_type_t *types_table=NULL;
int types_num=0, types_alloc=0;

static hir_type_t *deref_type(type_handle_t handle);
static int typevalcmp(hir_type_t *one, hir_type_t *two);
static type_handle_t type_find(hir_type_t *t);

//{{{
static hir_type_t *deref_type(type_handle_t handle)
{
	assert(handle < types_num);
	
	return &types_table[handle];
}
//}}}

//{{{
int type_is_void(type_handle_t t)
{
	return deref_type(t)->type_cat==TYPE_BASE && deref_type(t)->data.typ==type_void;
}
//}}}
//{{{
int type_is_pointer(type_handle_t t)
{
	return deref_type(t)->type_cat == TYPE_POINTER;
}
//}}}
//{{{
int type_is_struct(type_handle_t t)
{
	return deref_type(t)->type_cat == TYPE_STRUCT;
}
//}}}
//{{{
int type_is_array(type_handle_t t)
{
	return deref_type(t)->type_cat == TYPE_ARRAY;
}
//}}}
//{{{
int type_size(type_handle_t t)
{
	hir_type_t *info = deref_type(t);
	
	return info->size;
	
/*	switch(info->type_cat)
	{
		case TYPE_BASE:
			switch(info->data.typ)
			{
				case type_void:  return 0;
				case type_char:  return 1;
				case type_short: return 2;
				case type_int:   return 4;
				case type_long:  return 4;
			}
		case TYPE_POINTER:
			return 4;
		case TYPE_STRUCT:
			return get_struct(t)->datasize;
	} */
	return 0;
}
//}}}

//{{{
int typecmp(type_handle_t one, type_handle_t two)
{
	return typevalcmp(deref_type(one), deref_type(two));
	
}
//}}}
//{{{
static int typevalcmp(hir_type_t *one, hir_type_t *two)
{
	if(one->type_cat != two->type_cat)
		return 0;
	
	switch(one->type_cat)
	{
		case TYPE_STRUCT:
		case TYPE_BASE:
			return one->data.typ == two->data.typ;
		case TYPE_POINTER:
			return typecmp(one->data.child, two->data.child);
		case TYPE_ARRAY:
			return one->data.typ == two->data.typ && one->size == two->size;
	}
	
	return 1;
}
//}}}

//{{{
void init_types(void)
{
	int ii;
	
	expand_table((void*)&types_table, &types_alloc, 5, sizeof(hir_type_t));
	types_num = 5;
	
	for(ii=0; ii<5; ii++) {
		types_table[ii].type_cat = TYPE_BASE;
		types_table[ii].data.typ = ii;
	}
	types_table[type_void].size  = 0;
	types_table[type_char].size  = 1;
	types_table[type_short].size = 2;
	types_table[type_int].size   = 4;
	types_table[type_long].size  = 4;
}
//}}}

//{{{
type_handle_t type_base(int t)
{
	return t;
}
//}}}
//{{{
static type_handle_t type_find(hir_type_t *t)
{
	int ii;
	
	for(ii=0; ii<types_num; ii++)
	{
		if(typevalcmp(t, &types_table[ii]))
			return ii;
	}
	
	expand_table((void*)&types_table, &types_alloc, types_num+1, sizeof(hir_type_t));
	
	types_table[types_num++] = *t;
	return types_num-1;
}
//}}}
//{{{
type_handle_t type_pointer_to(type_handle_t t)
{
	hir_type_t addition;
	
	addition.type_cat = TYPE_POINTER;
	addition.data.child = t;
	addition.size = 4;
	
	return type_find(&addition);
}
//}}}
//{{{
type_handle_t type_array_of(type_handle_t t, int num_elements)
{
	hir_type_t addition;
	
	addition.type_cat = TYPE_ARRAY;
	addition.data.child = t;
	addition.size = type_size(t) * num_elements;
	
	return type_find(&addition);
}
//}}}
//{{{
type_handle_t type_struct_named(id_handle_t identifier)
{
	hir_type_t addition;
	
	addition.type_cat = TYPE_STRUCT;
	addition.data.typ = find_struct(identifier);
	
	if(addition.data.typ == -1) {
		error_invalid_type();
		return 0;
	}
	
	addition.size = global_structs[ addition.data.typ ].datasize;
	
	return type_find(&addition);
}
//}}}
//{{{
type_handle_t type_deref(type_handle_t t)
{
	return deref_type(t)->data.child;
}
//}}}

hir_typedef_t *typedef_table=NULL;
int typedefs_num=0, typedefs_alloc=0;

//{{{
void type_typedef(type_handle_t type, id_handle_t ident)
{
	int ii;
	hir_typedef_t addition;
	
	for(ii=0; ii<types_num; ii++)
	{
		if(idcmp(typedef_table[ii].identifier, ident)) {
			error_multiple_typedef();
			return;
		}
	}
	
	expand_table((void*)&typedef_table, &typedefs_alloc, typedefs_num+1, sizeof(hir_typedef_t));
	
	addition.type = type;
	addition.identifier = ident;
	typedef_table[typedefs_num++] = addition;
}
//}}}
//{{{
type_handle_t hir_get_typedef(id_handle_t identifier)
{
	int ii;
	
	for(ii=0; ii<typedefs_num; ii++)
	{
		if(idcmp(identifier, typedef_table[ii].identifier))
			return ii;
	}
	
	error_invalid_type();
	return 0;
}
//}}}

//{{{
hir_struct_t *get_struct(type_handle_t t)
{
	if(types_table[t].type_cat != TYPE_STRUCT)
		return NULL;
	
	return &global_structs[types_table[t].data.typ];
}
//}}}

//{{{
void type_print(type_handle_t t)
{
	if(type_is_pointer(t))
	{
		printf("pointer to ");
		type_print(type_deref(t));
	}
	else if(type_is_struct(t))
	{
		printf("structure");
	}
	else if(type_is_array(t))
	{
		printf("array of ");
		type_print(type_deref(t));
	} else {
		switch(t)
		{
			case type_void:  printf("void\n"); break;
			case type_char:  printf("char\n"); break;
			case type_short: printf("short\n"); break;
			case type_int:   printf("int\n"); break;
			case type_long:  printf("long\n"); break;
			default: printf("unknown type\n"); break;
		}
	}
}
//}}}

