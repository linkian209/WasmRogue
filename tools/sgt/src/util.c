#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include "sgt.h"

//{{{
int error(const char *format, ...)
{
	va_list varargs;
	int ret;
	va_start(varargs, format);
	ret = vfprintf(stderr, format, varargs);
	putc('\n', stderr);
	va_end(varargs);
	return ret;
}
//}}}
//{{{
// Input (str) starts with the character after a backslash, and continues at
// least to the end of the escape sequence. Advances the read position (*pos)
// accordingly.
char parse_escape(const char *str, int *pos)
{
	unsigned char ret = 0;
	
	// Escape sequences are as per K&R, with the addition that non-special
	// characters are taken unchanged.
	switch( str[(*pos)++] )
	{
		case 'a': return '\a'; // alert (bell)
		case 'b': return '\b'; // backspace
		case 'f': return '\f'; // formfeed
		case 'n': return '\n'; // newline
		case 'r': return '\r'; // carriage return
		case 't': return '\t'; // horizontal tab
		case 'v': return '\v'; // vertical tab
		case '\\': return '\\'; // backslash
		case '?': return '\?'; // question mark
		case '\'': return '\''; // single quote
		case '\"': return '\"'; // double quote
		case 'x': // hex number
			if(str[*pos] == '\0') {
				error("Invalid escape sequence encountered.");
				return '?';
			}
			if(str[*pos] >= 'a' && str[*pos] <= 'f')
				ret = (str[*pos] - 'a' + 10);
			else if(str[*pos] >= 'A' && str[*pos] <= 'F')
				ret = (str[*pos] - 'A' + 10);
			else if(str[*pos] >= '0' && str[*pos] <= '9')
				ret = (str[*pos] - '0');
			else {
				error("Invalid escape sequence encountered.");
				return '?';
			}
			(*pos)++;
			ret <<= 4;
			if(str[*pos] >= 'a' && str[*pos] <= 'f')
				ret += (str[*pos] - 'a' + 10);
			else if(str[*pos] >= 'A' && str[*pos] <= 'F')
				ret += (str[*pos] - 'A' + 10);
			else if(str[*pos] >= '0' && str[*pos] <= '9')
				ret += (str[*pos] - '0');
			else {
				error("Invalid escape sequence encountered.");
				return '?';
			}
			(*pos)++;
			return ret;
		case '0': case '1': case '2': case '3': // octal number
		case '4': case '5': case '6': case '7':
			(*pos)--;
			ret += str[*pos] - '0';
			(*pos)++;
			if(str[*pos] < '0' || str[*pos] > '7')
				return ret;
			ret <<= 3;
			ret += (str[*pos] - '0');
			(*pos)++;
			if(str[*pos] < '0' || str[*pos] > '7')
				return ret;
			ret <<= 3;
			ret += str[*pos] - '0';
			(*pos)++;
			return ret;
		case '\0': // Whoops! Past the end of the string!
			error("Invalid escape sequence encountered.");
			(*pos)--;
			return '\\';
	}
	return str[*pos];
}
//}}}
//{{{
/// Skip over any pending whitespace in a stream
void skip_whitespace(FILE *F)
{
	int in;
	do {
		in = getc(F);
		if(in == EOF) return;
	} while( isspace(in) );
	ungetc(in, F);
}
//}}}
//{{{
/// @brief Skip over a #...-style comment
///
/// If the current character is a '#', read the rest of the line, including
/// the newline. Otherwise, leave the stream unchanged. Returns 1 if a comment
/// was read, 0 otherwise.
int skip_comment(FILE *F)
{
	int in;
	
	in = getc(F);
	if(in != '#') {
		ungetc(in, F);
		return 0;
	}
	
	do {
		in = getc(F);
	} while( in != EOF && in != '\n' );
	
	return 1;
}
//}}}
//{{{
int isident(int C)
{
	return (isalnum(C) || C=='_');
}
//}}}
//{{{
int match_str(const char *str1, const char *expected)
{
	return strncmp(str1, expected, strlen(expected)) == 0;
}
//}}}
//{{{
const char *strip_path(const char *str)
{
	const char *ret = str;
	while(*str != '\0') {
		if(*str == '/') ret = str+1;
		str++;
	}
	return ret;
}
//}}}
//{{{
const char *stem(const char *str)
{
	const char *path_stripped = str;
	char *ret;
	char *pos;
	
	// Skip everything up to and including the last '/' character
	while(*str != '\0') {
		if(*str == '/') path_stripped = str+1;
		str++;
	}
	ret = strdup(path_stripped);
	    // No, this doesn't ever get freed; it's a noncumulative memory leak.
	
	// Skip everything after and including the first '.' character
	pos = ret;
	while(*pos != '\0') {
		if(*pos == '.') {
			*pos = '\0';
			break;
		}
		pos++;
	}
	
	return ret;
}
//}}}


