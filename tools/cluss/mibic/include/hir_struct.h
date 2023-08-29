#ifndef HIR_STRUCT_H
#define HIR_STRUCT_H

#include "hir.h"
#include "type.h"

typedef struct hir_struct_t
{
	id_handle_t identifier;
	int datasize;
	int is_union;
	
	struct hir_struct_member *elements;
	int elements_num, elements_alloc;
} hir_struct_t;

typedef struct hir_struct_member
{
	id_handle_t identifier;
	type_handle_t type;
	int offset;
} hir_struct_member_t;

void hir_start_struct(id_handle_t identifier, int is_union);
void hir_add_member(type_handle_t type, id_handle_t identifier);
void hir_member_array(hir_interm_t num_elements);
void hir_finish_struct(void);
type_handle_t find_struct(id_handle_t identifier);
int member_offset(type_handle_t type, id_handle_t member);
type_handle_t member_type(type_handle_t type, id_handle_t member);

extern hir_struct_t *global_structs;
extern int structs_num, structs_alloc;


#endif

