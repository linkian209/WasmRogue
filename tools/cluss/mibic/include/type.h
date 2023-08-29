#ifndef TYPE_H
#define TYPE_H


typedef int type_handle_t;

#define TYPE_BASE    0
#define TYPE_POINTER 1
#define TYPE_STRUCT  2
#define TYPE_ARRAY   3
typedef struct hir_type
{
	int type_cat;
	int size;
	union
	{
		int typ;
		type_handle_t child;
	} data;
} hir_type_t;

typedef struct hir_typedef
{
	type_handle_t type;
	id_handle_t identifier;
} hir_typedef_t;

#define type_void  0
#define type_char  1
#define type_short 2
#define type_int   3
#define type_long  4

void init_types(void);

int type_is_void(type_handle_t t);
int type_is_pointer(type_handle_t t);
int type_is_struct(type_handle_t t);
int type_is_array(type_handle_t t);
int type_size(type_handle_t t);
int typecmp(type_handle_t one, type_handle_t two);
type_handle_t type_base(int t);
type_handle_t type_pointer_to(type_handle_t t);
type_handle_t type_array_of(type_handle_t t, int num_elements);
type_handle_t type_struct_named(id_handle_t identifier);
type_handle_t type_deref(type_handle_t t);
void type_typedef(type_handle_t type, id_handle_t ident);
struct hir_struct_t *get_struct(type_handle_t t);

void type_print(type_handle_t t);

#endif

