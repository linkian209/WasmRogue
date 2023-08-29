#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "namespace.h"
#include "util.h"

//{{{
void init_namespace(namespace_t *ns)
{
	int i;
	
	assert(ns);
	
	ns->num = 0;
	ns->alloc = 16;
	ns->ids = (identifier_info_t*)calloc(sizeof(identifier_info_t), ns->alloc);
	
	if(ns->ids == NULL)
		error_internal_memory();
	
	for(i=0; i<ns->alloc; i++)
		ns->ids[i].str = NULL;
}
//}}}
//{{{
void delete_namespace(namespace_t *ns)
{
	int i;
	
	assert(ns);
	assert(ns->ids != NULL);
	
	for(i=0; i<ns->num; i++)
	{
		if(ns->ids[i].str)
		{
			free(ns->ids[i].str);
			ns->ids[i].str = NULL;
		}
	}
	free(ns->ids);
	ns->ids = NULL;
}
//}}}
//{{{
id_handle_t get_identifier(namespace_t *ns, const char *identifier)
{
	int i;
	id_handle_t ret;
	
	assert(ns);
	assert(ns->ids);
	assert(identifier);
	
	ret.ns = ns;
	
	for(i=0; i<ns->num; i++)
	{
		if( strcmp(identifier, ns->ids[i].str) == 0 )
		{
			ret.id = i;
			return ret;
		}
	}
	
	add_identifier(ns, identifier);
	ret.id = ns->num - 1;
	return ret;
}
//}}}
//{{{
const char *get_identifier_string(id_handle_t id)
{
	if(id.ns == NULL)
		return "(no identifier)";
	
	return id.ns->ids[id.id].str;
}
//}}}
//{{{
void add_identifier(namespace_t *ns, const char *identifier)
{
	identifier_info_t addition;
	
	assert(ns);
	assert(ns->ids);
	assert(identifier);
	
	if(ns->num + 1 > ns->alloc)
	{
		ns->alloc *= 2;
		ns->ids = (identifier_info_t*)realloc(ns->ids, ns->alloc*sizeof(identifier_info_t));
		
		if(ns->ids == NULL)
			error_internal_memory();
	}
	
	addition.str = strdup(identifier);
	ns->ids[ns->num++] = addition;
}
//}}}
//{{{
int idcmp(id_handle_t one, id_handle_t two)
{
	return one.ns==two.ns && one.id==two.id;
}
//}}}
//{{{
int id_is_null(id_handle_t id)
{
	return id.ns == NULL;
}
//}}}
//{{{
id_handle_t blank_identifier(void)
{
	id_handle_t ret;
	ret.ns = NULL;
	ret.id = 0;
	return ret;
}
//}}}
