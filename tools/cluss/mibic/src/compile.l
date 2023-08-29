%{
#include <stdio.h>
#include <string.h>
#include "namespace.h"
#include "compile.h"
#include "hir.h"
#include "util.h"
#include "y.tab.h"

extern YYSTYPE yylval;

void comment(void);
void parse_preprocessor_lineno(const char *txt);

%}

%option yylineno

%%
";"                     { return ';';             }
"{"                     { return '{';             }
"}"                     { return '}';             }
","                     { return ',';             }

"."                     { return '.';             }
"->"                    { return TOK_ARROW;       }
"!"                     { return '!';             }
"~"                     { return '~';             }
"*"                     { return '*';             }
"/"                     { return '/';             }
"%"                     { return '%';             }
"+"                     { return '+';             }
"-"                     { return '-';             }
"++"                    { return TOK_INCR;        }
"--"                    { return TOK_DECR;        }
"<<"                    { return TOK_LTLT;        }
">>"                    { return TOK_GTGT;        }
"<"                     { return '<';             }
"<="                    { return TOK_LTEQ;        }
">"                     { return '>';             }
">="                    { return TOK_GTEQ;        }
"=="                    { return TOK_EQEQ;        }
"!="                    { return TOK_NEQ;         }
"&"                     { return '&';             }
"^"                     { return '^';             }
"|"                     { return '|';             }
"&&"                    { return TOK_ANDAND;      }
"||"                    { return TOK_OROR;        }
"="                     { return '=';             }
"+="                    { return TOK_ADDEQ;       }
"-="                    { return TOK_SUBEQ;       }
"*="                    { return TOK_MULEQ;       }
"/="                    { return TOK_DIVEQ;       }
"%="                    { return TOK_MODEQ;       }
"&="                    { return TOK_ANDEQ;       }
"^="                    { return TOK_XOREQ;       }
"|="                    { return TOK_OREQ;        }
"<<="                   { return TOK_LSFTEQ;      }
">>="                   { return TOK_RSFTEQ;      }
"\["                    { return '[';             }
"\]"                    { return ']';             }
":"                     { return ':';             }

"const"                 { return TOK_CONST;       }
"extern"                { return TOK_EXTERN;      }
"struct"                { return TOK_STRUCT;      }
"union"                 { return TOK_UNION;       }
"even"                  { return TOK_EVEN;        }
"splitpoint"            { return TOK_SPLITPOINT;  }
"void"                  { yylval.datatype=type_base(type_void);   return TOK_TYPE; }
"long"                  { yylval.datatype=type_base(type_long);   return TOK_TYPE; }
"ulong"                 { yylval.datatype=type_base(type_long);   return TOK_TYPE; }
"slong"                 { yylval.datatype=type_base(type_long);   return TOK_TYPE; }
"int"                   { yylval.datatype=type_base(type_int);    return TOK_TYPE; }
"sint"                  { yylval.datatype=type_base(type_short);  return TOK_TYPE; }
"uint"                  { yylval.datatype=type_base(type_short);  return TOK_TYPE; }
"short"                 { yylval.datatype=type_base(type_short);  return TOK_TYPE; }
"ushort"                { yylval.datatype=type_base(type_short);  return TOK_TYPE; }
"sshort"                { yylval.datatype=type_base(type_short);  return TOK_TYPE; }
"char"                  { yylval.datatype=type_base(type_char);   return TOK_TYPE; }
"uchar"                 { yylval.datatype=type_base(type_char);   return TOK_TYPE; }
"schar"                 { yylval.datatype=type_base(type_char);   return TOK_TYPE; }
"string"                { return TOK_KEY_STRING;  }
"export"                { return TOK_EXPORT;      }
"link"                  { return TOK_LINK;        }

"return"                { return TOK_RETURN;      }
"if"                    { return TOK_IF;          }
"else"                  { return TOK_ELSE;        }
"do"                    { return TOK_DO;          }
"while"                 { return TOK_WHILE;       }
"for"                   { return TOK_FOR;         }
"break"                 { return TOK_BREAK;       }
"continue"              { return TOK_CONTINUE;    }

[0-9]+                  { yylval.numeric=atoi(yytext); return TOK_NUMBER; }
\(                      { return '('; }
\)                      { return ')'; }
[_a-zA-Z][_a-zA-Z0-9]*  { yylval.identifier=get_identifier(&global_namespace, yytext); return TOK_IDENTIFIER; }
'(\\.|[^\\'])+'         { yylval.numeric=parse_char_constant(yytext); return TOK_NUMBER; }
'(\\.|[^\\'])+'         { yylval.numeric=parse_char_constant(yytext+1); return TOK_NUMBER; }
\"(\\.|[^\\"\n])*\"     { yylval.string=parse_string(yytext); return TOK_STRING; }

[ \t]+                  /* ignore whitespace */
\n                      /* ignore linefeeds */
\#[^\n]*\n              { parse_preprocessor_lineno(yytext); }
"/*"                    { comment(); }
\/\/[^\n]*\n            /* ignore //...-style comments */
.                       /* ignore bad characters */
%%


void comment(void)
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0) {}

	if ((c1 = input()) != '/' && c != 0)
		goto loop;
}


void parse_preprocessor_lineno(const char *txt)
{
	char inbuf[256];
	strcpy(inbuf, input_filename);
	txt++;
	while(*txt==' ' || *txt == '\t')
		txt++;
	if(txt[0] == 'l') {
		txt += 4;
	}
	sscanf(txt, "%i \"%256[^\"]\"", &yylineno, inbuf);
	if(should_free_input_filename)
		free(input_filename);
	input_filename = strdup(inbuf);
	should_free_input_filename = 1;
}


