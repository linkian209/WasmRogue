#ifndef COMPILE_H
#define COMPILE_H
#include <stdio.h>
#include "namespace.h"

extern char *input_filename;
extern const char *output_filename;
extern int should_free_input_filename;
extern int reverse_endian;
extern int debug_info;

extern namespace_t global_namespace;

extern int errors, warnings;

extern FILE *yyin;
extern int yylineno;
int yyparse(void);
int yylex(void);

#endif

