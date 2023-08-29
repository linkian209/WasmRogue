#ifndef NAMESPACE_H
#define NAMESPACE_H

typedef struct identifier_info
{
	char *str;
} identifier_info_t;

typedef struct namespace
{
	identifier_info_t *ids;
	int num;
	int alloc;
} namespace_t;

typedef struct id_handle
{
	namespace_t *ns;
	int id;
} id_handle_t;

#define id_null {NULL, 0}

void init_namespace(namespace_t *ns);
void delete_namespace(namespace_t *ns);
id_handle_t get_identifier(namespace_t *ns, const char *identifier);
const char *get_identifier_string(id_handle_t id);
void add_identifier(namespace_t *ns, const char *identifier);
int idcmp(id_handle_t one, id_handle_t two);
int id_is_null(id_handle_t id);
id_handle_t blank_identifier(void);

#endif

