#ifndef UTIL_H
#define UTIL_H

#include "namespace.h"

#define CODE_LABEL_FLAGS 4

#define ERROR_INTERNAL 1
#define ERROR_INVOCATION 2
#define ERROR_FILES 3

void error_internal_memory(void);
void error_opening_file(const char *filename);
void error_undeclared_identifier(id_handle_t id);
void error_undeclared_function(id_handle_t id);
void error_prototype_mismatch(id_handle_t id);
void error_non_lvalue(void);
void error_invalid_break(void);
void error_invalid_continue(void);
void error_deref_non_pointer(void);
void error_multiple_typedef(void);
void error_invalid_type(void);
void error_non_constant(void);
void error_non_struct(void);
void error_non_member(const char *member);
void warn_statement_no_effect(void);
void warn_void_in_expr(void);
void init_table(void **table, int *cur_size, int new_size, size_t entry_size);
void expand_table(void **table, int *cur_size, int new_size, size_t entry_size);
id_handle_t generate_label(void);
char parse_escape(const char **str);
int parse_char_constant(const char *str);
char *parse_string(const char *source);

#endif

