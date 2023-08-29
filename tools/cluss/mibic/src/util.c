#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "compile.h"

//{{{
void error_internal_memory(void)
{
	fprintf(stderr, "Internal memory error; aborting.\n");
	exit(ERROR_INTERNAL);
}
//}}}
//{{{
void error_opening_file(const char *filename)
{
	fprintf(stderr, "Error opening file '%s'.\n", filename);
	errors++;
}
//}}}
//{{{
void error_undeclared_identifier(id_handle_t id)
{
	fprintf(stderr, "%s:%i: Undeclared identifier '%s'.\n", input_filename, yylineno, get_identifier_string(id));
	errors++;
}
//}}}
//{{{
void error_undeclared_function(id_handle_t id)
{
	fprintf(stderr, "%s:%i: Undeclared function '%s'.\n", input_filename, yylineno, get_identifier_string(id));
	errors++;
}
//}}}
//{{{
void error_prototype_mismatch(id_handle_t id)
{
	fprintf(stderr, "%s:%i: Prototype mismatch for function '%s'.\n", input_filename, yylineno, get_identifier_string(id));
	errors++;
}
//}}}
//{{{
void error_non_lvalue(void)
{
	fprintf(stderr, "%s:%i: Non-lvalue in assignment.\n", input_filename, yylineno);
	errors++;
}
//}}}
//{{{
void error_invalid_break(void)
{
	fprintf(stderr, "%s:%i: Invalid break statement.\n", input_filename, yylineno);
	errors++;
}
//}}}
//{{{
void error_invalid_continue(void)
{
	fprintf(stderr, "%s:%i: Invalid continue statement.\n", input_filename, yylineno);
	errors++;
}
//}}}
//{{{
void error_deref_non_pointer(void)
{
	fprintf(stderr, "%s:%i: Dereferencing non pointer.\n", input_filename, yylineno);
	errors++;
}
//}}}
//{{{
void error_multiple_typedef(void)
{
	fprintf(stderr, "%s:%i: Typedef already declared.\n", input_filename, yylineno);
	errors++;
}
//}}}
//{{{
void error_invalid_type(void)
{
	fprintf(stderr, "%s:%i: Invalid type.\n", input_filename, yylineno);
	errors++;
}
//}}}
//{{{
void error_non_constant(void)
{
	fprintf(stderr, "%s:%i: Expression not constant.\n", input_filename, yylineno);
	errors++;
}
//}}}
//{{{
void error_non_struct(void)
{
	fprintf(stderr, "%s:%i: Left side of expression is not a struct.\n", input_filename, yylineno);
	errors++;
}
//}}}
//{{{
void error_non_member(const char *name)
{
	fprintf(stderr, "%s:%i: %s is not a member.\n", input_filename, yylineno,
		name);
	errors++;
}
//}}}
//{{{
void warn_statement_no_effect(void)
{
	fprintf(stderr, "%s:%i: Warning: statement with no effect.\n", input_filename, yylineno);
	warnings++;
}
//}}}
//{{{
void warn_escape_sequence(void)
{
	fprintf(stderr, "%s:%i: Warning: Invalid escape sequence ignored.\n", input_filename, yylineno);
	warnings++;
}
//}}}
//{{{
void warn_void_in_expr(void)
{
	fprintf(stderr, "%s:%i: Warning: void value not ignored as it ought to be.\n", input_filename, yylineno);
	warnings++;
}
//}}}

//{{{
void init_table(void **table, int *cur_size, int new_size, size_t entry_size)
{
	if(*table != NULL || *cur_size != 0)
		return;
	
	*cur_size = new_size;
	*table = malloc(*cur_size * entry_size);
	
	if(*table == NULL)
		error_internal_memory();

}
//}}}
//{{{
void expand_table(void **table, int *cur_size, int new_size, size_t entry_size)
{
	if(new_size <= *cur_size)
		return;
	
	if(*cur_size > 1) *cur_size *= 2;
	else              *cur_size = 16;
	
	*table = realloc(*table, *cur_size * entry_size);
	
	if(*table == NULL)
		error_internal_memory();
}
//}}}

static int label_num = 0;
//{{{
id_handle_t generate_label(void)
{
	char str[16];
	sprintf(str, "__l%i", label_num++);
	return get_identifier(&global_namespace, str);
}
//}}}

//{{{
// Input (str) starts with the character after a backslash, and continues at
// least to the end of the escape sequence. Advances the read ptr according to
// the length of the escape sequence.
char parse_escape(const char **str)
{
	unsigned char ret = 0;
	
	// Escape sequences are as per K&R, with the addition that non-special
	// characters are taken unchanged.
	switch(*((*str)++))
	{
		case 'a': // alert (bell)
			return '\a';
		case 'b': // backspace
			return '\b';
		case 'f': // formfeed
			return '\f';
		case 'n': // newline
			return '\n';
		case 'r': // carriage return
			return '\r';
		case 't': // horizontal tab
			return '\t';
		case 'v': // vertical tab
			return '\v';
		case '\\': // backslash
			return '\\';
		case '?': // question mark
			return '\?';
		case '\'': // single quote
			return '\'';
		case '\"': // double quote
			return '\"';
		case 'x': // hex number
			if(**str == '\0') {
				warn_escape_sequence();
				return '?';
			}
			if(**str >= 'a' && **str <= 'f')
				ret = (**str - 'a') << 4;
			else if(**str >= 'A' && **str <= 'F')
				ret = (**str - 'A') << 4;
			else if(**str >= '0' && **str <= '9')
				ret = (**str - '0') << 4;
			else {
				warn_escape_sequence();
				return '?';
			}
			(*str)++;
			if(**str >= 'a' && **str <= 'f')
				ret |= (**str - 'a');
			else if(**str >= 'A' && **str <= 'F')
				ret |= (**str - 'A');
			else if(**str >= '0' && **str <= '9')
				ret |= (**str - '0');
			else {
				warn_escape_sequence();
				return '?';
			}
			return ret;
		case '0': case '1': case '2': case '3': // octal number
			(*str)--;
			(*str)++;
			if(**str < '0' || **str > '7') {
				(*str)--;
				return ret;
			}
			ret <<= 3;
			ret |= (**str - '0');
			(*str)++;
			if(**str < '0' || **str > '7') {
				(*str)--;
				return ret;
			}
			ret |= **str - '0';
			(*str)++;
			ret <<= 3;
			return ret;
		case '\0': // Whoops! Past the end of the string!
			warn_escape_sequence();
			(*str)--;
			return '\\';
	}
	return **str;
}
//}}}
//{{{
int parse_char_constant(const char *str)
{
	str++;
	if(*str == '\\')
	{
		str++;
		return parse_escape(&str);
	}
	else
		return *str;
}
//}}}
//{{{
// Input is a tokenized string, meaning it still has quote marks around it and
// escape sequences inside. Input length is guaranteed to be at least 2
// (two matching quotes)
char *parse_string(const char *str)
{
	int write_pos = 0;
	const char *read_pos;
	char *ret = malloc(strlen(str) - 1); // +1 for terminator, -2 for quote marks
	
	for(read_pos = str+1; *read_pos != '\0' && read_pos[1] != '\0'; read_pos++)
	{
		if(*read_pos == '\\') {
			read_pos++;
			ret[write_pos++] = parse_escape(&read_pos);
			read_pos--;
		} else {
			ret[write_pos++] = *read_pos;
		}
	}
	ret[write_pos] = '\0';
	
	return ret;
}
//}}}

