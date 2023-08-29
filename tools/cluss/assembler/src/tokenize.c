#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "cluss.h"

static void tokenizer_cleanup(void);
static char *current_token = NULL;
static int token_size=0, token_alloc=0;
static int expand_buffer(void);

int lineno=1;

#define append_character(ch)                 \
	(((token_size >= token_alloc) ?          \
		expand_buffer() : 0),                \
	(current_token[token_size++] = (ch)))

#define terminate_string()                   \
    (current_token[token_size] = '\0')

static int read_identifier(FILE *input);
static int read_integer(FILE *input);
static int read_line_comment(FILE *input);
static int read_C_comment(FILE *input);
static int read_grouping(FILE *input);

//{{{
void tokenizer_init(void)
{
	atexit(tokenizer_cleanup);
}
//}}}
//{{{
static void tokenizer_cleanup(void)
{
	if(current_token)
		free(current_token);
	token_alloc = 0;
}
//}}}
//{{{
// Simple tokenization rules:
// * ; ... \n, /* ... */, // ... \n, and # ... \n are all recognized comment
//   formats. Any comment whose body matches "\s*line\s*([0-9]+)\s*(\".*\")?
//   may be taken as a line-control directive.
// * Punctuators get their own tokens
// * Whitespace and commas separate tokens, but get eaten
// * Everything else is valid and grouped.
int get_token(FILE *input)
{
	char in;
	char tmp;
	
	token_size = 0;
	
	while(!feof(input))
	{
		in = getc(input);
		
		if(isalpha(in) || in=='_' || in=='.') {
				// Start of an identifier [a-zA-Z_.]
			ungetc(in, input);
			return read_identifier(input);
		}
		else if(isdigit(in) || in=='-') {
				// Start of a numeric constant
			ungetc(in, input);
			return read_integer(input);
		}
		else if(in==';' || in=='#') {
			read_line_comment(input);
		}
		else if(in=='/') {
			tmp = getc(input);
			if(tmp=='/') {
				read_line_comment(input);
			} else if(tmp=='*') {
				read_C_comment(input);
			} else {
				ungetc(tmp, input);
			}
		}
		else if(in=='\n') {
			lineno++;
		}
		else if(isspace(in)) {
			continue;
		}
		else if(in==EOF) {
			return TOK_EOF;
		} else {
			// By default, just stop at the next whitespace
			ungetc(in, input);
			return read_grouping(input);
		}
	}
	return TOK_EOF;
}
//}}}
//{{{
const char *token_string(void)
{
	return current_token;
}
//}}}

//{{{
static int expand_buffer(void)
{
	if(!current_token)
	{
		token_alloc = 16;
		current_token = (char*)malloc(token_alloc);
	} else {
		token_alloc <<= 1;
		current_token = (char*)realloc(current_token, token_alloc);
	}
	return 1;
}
//}}}
//{{{
static int read_identifier(FILE *input)
{
	int inc;
	int first_char = 1;
	
	do {
		inc = getc(input);
		if( isalpha(inc) || isdigit(inc) || inc=='_' || (inc=='.'&&first_char) )
		{
			first_char = 0;
			append_character(inc);
		} else {
			if( inc != EOF || feof(input) )
				ungetc(inc, input);
			break;
		}
	} while(1);
	terminate_string();
	
	return TOK_IDENTIFIER;
}
//}}}
//{{{
static int read_integer(FILE *input)
{
	int inc;
	
	do {
		inc = getc(input);
		if( isdigit(inc) || inc=='-' )
			append_character(inc);
		else {
			if( inc != EOF || feof(input) )
				ungetc(inc, input);
			break;
		}
	} while(1);
	terminate_string();
	
	return TOK_INTEGER;
}
//}}}
//{{{
static int read_line_comment(FILE *input)
{
	char in;
	do {
		if(feof(input)) break;
		in = getc(input);
	} while(in != '\n');
	lineno++;
	return 1;
}
//}}}
//{{{
static int read_C_comment(FILE *input)
{
	char in;
	do {
		if(feof(input)) {
			error("Unexpected end of file in comment");
			return 0;
		}
		
		in = getc(input);
		
		if(in == '\n')
		{
			lineno++;
		}
		else while(in == '*')
		{
			in = getc(input);
			if(in == '/')
				break;
			else if(in == '\n')
				lineno++;
		}
	} while(1);
	
	return 1;
}
//}}}
//{{{
static int read_grouping(FILE *input)
{
	int inc;
	
	do {
		inc = getc(input);
		if( !isspace(inc) && inc!=EOF )
			append_character(inc);
		else {
			if( inc != EOF || feof(input) )
				ungetc(inc, input);
			break;
		}
	} while(1);
	terminate_string();
	
	return TOK_GROUP;
}
//}}}

