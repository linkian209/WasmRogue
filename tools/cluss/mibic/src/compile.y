%{
#include <stdio.h>
#include <string.h>
#include "compile.h"
#include "namespace.h"
#include "hir.h"
#include "lir.h"
#include "type.h"
 
void yyerror(const char *str)
{
	fprintf(stderr,"%s:%i: %s\n", input_filename, yylineno, str);
	errors++;
}
 
int yywrap()
{
	return 1;
} 
  
%}

%union {
	long numeric;
	char *string;
	id_handle_t identifier;
	type_handle_t datatype;
	hir_interm_t subexpr;
}


%token TOK_IDENTIFIER TOK_TYPE TOK_NUMBER TOK_STRING TOK_CONST TOK_INCR TOK_DECR TOK_IF TOK_ELSE TOK_BOGUS TOK_ADDEQ TOK_SUBEQ TOK_MULEQ TOK_DIVEQ TOK_MODEQ TOK_ANDEQ TOK_XOREQ TOK_OREQ TOK_LSFTEQ TOK_RSFTEQ TOK_OROR TOK_ANDAND TOK_EQEQ TOK_NEQ TOK_LTEQ TOK_GTEQ TOK_LTLT TOK_GTGT TOK_RETURN TOK_DO TOK_WHILE TOK_FOR TOK_EXTERN TOK_BREAK TOK_CONTINUE TOK_STRUCT TOK_KEY_STRING TOK_EXPORT TOK_LINK TOK_EVEN TOK_ARROW TOK_UNION TOK_SPLITPOINT

%right '!' '~' PREFIX
%left SUFFIX
%left '*' '/' '%'
%left '+' '-'
%left TOK_LTLT TOK_GTGT
%left '<' '>' TOK_LTEQ TOK_GTEQ
%left INEQUALITIES
%left TOK_EQEQ TOK_NEQ
%left '&'
%left '^'
%left '|'
%left TOK_ANDAND
%left TOK_OROR
%right '=' TOK_ADDEQ TOK_SUBEQ TOK_MULEQ TOK_DIVEQ TOK_MODEQ TOK_ANDEQ TOK_XOREQ TOK_OREQ TOK_LSFTEQ TOK_RSFTEQ

%expect 1   // Expect the dangling-else conflict

%start start

%%

start
	: /* empty */
	| start glbl
	;

glbl
	: func
	| struct_definition
	| emitted_label
	| directive
	;



func
	: prototype ';'
		{ hir_finish_prototype(); }
	| prototype func_body
		{ hir_finish_func_body(); }
	| TOK_EXTERN prototype '=' TOK_NUMBER ';'
		{ hir_finish_extern_func($<numeric>4); }
	;

prototype
	: type_specifier TOK_IDENTIFIER
		{ hir_start_func($<datatype>1, $<identifier>2); }
	  paramlist
	;

func_body
	: '{' varlist '}'
	| '{' expr_group '}'
	| '{' varlist expr_group '}'
	;


type_specifier
	: direct_declarator
	| type_specifier '*'
		{ $<datatype>$=type_pointer_to($<datatype>1); }
	;

direct_declarator
	: TOK_TYPE
		{ $<datatype>$=$<datatype>1; }
	| TOK_STRUCT TOK_IDENTIFIER
		{ $<datatype>$ = type_struct_named($<identifier>2); }
	| TOK_UNION TOK_IDENTIFIER
		{ $<datatype>$ = type_struct_named($<identifier>2); }
	;


emitted_label
	: TOK_EXPORT TOK_IDENTIFIER ';'
		{ hir_emit_label($<identifier>2, hir_load_immediate(0), -1); }
	| TOK_EXPORT TOK_IDENTIFIER '(' assign_expr ')' ';'
		{ hir_emit_label($<identifier>2, $<subexpr>4, -1); }
	| TOK_EXPORT TOK_IDENTIFIER '(' assign_expr ',' assign_expr ')' ';'
		{ hir_emit_label($<identifier>2, $<subexpr>4, $<subexpr>6); }
	;

directive
	: TOK_EVEN ';'
		{ lir_write_inst(LIR_EVEN); }
	| TOK_SPLITPOINT ';'
		{ lir_write_inst(LIR_SPLITPOINT); }
	| TOK_TYPE ':' root_expr ';'
		{ hir_emit_constant($<datatype>1, $<subexpr>3); }
	| TOK_KEY_STRING ':' TOK_STRING ';'
		{ hir_emit_string($<string>3); }
	| TOK_LINK ':' TOK_IDENTIFIER ';'
		{ hir_emit_link($<identifier>3); }
	| TOK_LINK ':' TOK_NUMBER ';'
		{ hir_emit_constant(type_base(type_short), 0);
		  hir_emit_constant(type_base(type_short), $<numeric>3);
		}
	;

optional_identifier
	: /* empty */
		{ $<identifier>$ = blank_identifier(); }
	| TOK_IDENTIFIER
		{ $<identifier>$ = $<identifier>1; }
	;



paramlist
	: '(' parameters ')'
	;

parameters
	: /* empty */
	| parameter
	| parameters ',' parameter
	;

parameter
	: type_specifier optional_identifier
		{ hir_add_variable($<datatype>1, $<identifier>2, 1); }
	;


varlist
	: varlist vardecl ';'
	| vardecl ';'
	;

vardecl
	: type_specifier TOK_IDENTIFIER
	  { hir_add_variable($<datatype>1, $<identifier>2, 0); }
	| type_specifier TOK_IDENTIFIER '[' root_expr ']'
	  {
		hir_add_variable(type_pointer_to($<datatype>1), $<identifier>2, 0);
		hir_finish_expr(
			hir_binary_op(
				hir_load_variable($<identifier>2),
				hir_unary_op(
					hir_binary_op(
						$<subexpr>4,
						hir_load_immediate(type_size($<datatype>1)),
						HIR_BINOP_MUL
					),
					HIR_UNARYOP_ALLOCA
				),
				HIR_BINOP_EQ
			)
		);
	  }
	| type_specifier TOK_IDENTIFIER '=' assign_expr
	  {
		hir_add_variable($<datatype>1, $<identifier>2, 0);
		hir_finish_expr(
			hir_binary_op(
				hir_load_variable($<identifier>2),
				$<subexpr>4,
				HIR_BINOP_EQ
			)
		);
	  }
	;



codeblock
	: '{' '}'
	| '{' expr_group '}'
	| complete_expr
	;

expr_group
	: expr_group complete_expr
	| complete_expr
	;

complete_expr
	: normal_expr
	| conditional_expr
	| do_while_loop
	| while_loop
	| for_loop
	| return_statement
	| break_statement
	| continue_statement
	;

normal_expr
	: root_expr ';'
		{ hir_finish_expr($<subexpr>1); }
	;

root_expr
	: assign_expr                        { $<subexpr>$ = $<subexpr>1;                                               }
	| root_expr ',' assign_expr          { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_COMMA);  }
	;

assign_expr
	: bool_or_expr                       { $<subexpr>$ = $<subexpr>1;                                               }
	| assign_expr '=' assign_expr        { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_EQ);     }
	| assign_expr TOK_ADDEQ assign_expr  { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_ADDEQ);  }
	| assign_expr TOK_SUBEQ assign_expr  { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_SUBEQ);  }
	| assign_expr TOK_MULEQ assign_expr  { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_MULEQ);  }
	| assign_expr TOK_DIVEQ assign_expr  { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_DIVEQ);  }
	| assign_expr TOK_MODEQ assign_expr  { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_MODEQ);  }
	| assign_expr TOK_ANDEQ assign_expr  { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_ANDEQ);  }
	| assign_expr TOK_XOREQ assign_expr  { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_XOREQ);  }
	| assign_expr TOK_OREQ assign_expr   { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_OREQ);   }
	| assign_expr TOK_LSFTEQ assign_expr { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_LSFTEQ); }
	| assign_expr TOK_RSFTEQ assign_expr { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_RSFTEQ); }
	;

bool_or_expr
	: bool_and_expr
	| bool_or_expr TOK_OROR bool_or_expr { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_OROR);   }
	;

bool_and_expr
	: or_expr
	| bool_and_expr TOK_ANDAND bool_and_expr    { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_ANDAND); }
	;

or_expr
	: xor_expr
	| or_expr '|' or_expr                { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_OR);     }
	;

xor_expr
	: and_expr
	| xor_expr '^' xor_expr              { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_XOR);    }
	;

and_expr
	: comparison_expr
	| and_expr '&' and_expr              { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_AND);    }
	;

comparison_expr
	: inequality_expr
	| comparison_expr TOK_EQEQ comparison_expr  { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_EQEQ);   }
	| comparison_expr TOK_NEQ comparison_expr   { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_NEQ);    }
	;

inequality_expr
	: shift_expr
	| inequality_expr '<' inequality_expr      { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_LT);     }
	| inequality_expr TOK_LTEQ inequality_expr { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_LTEQ);   }
	| inequality_expr '>' inequality_expr      { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_GT);     }
	| inequality_expr TOK_GTEQ inequality_expr { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_GTEQ);   }
	;

shift_expr
	: additive_expr
	| shift_expr TOK_LTLT shift_expr     { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_LSHIFT); }
	| shift_expr TOK_GTGT shift_expr     { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_RSHIFT); }
	;

additive_expr
	: mult_expr
	| additive_expr '+' additive_expr    { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_ADD);    }
	| additive_expr '-' additive_expr    { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_SUB);    }
	;

mult_expr
	: prefix_expr
	| mult_expr '*' mult_expr            { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_MUL);    }
	| mult_expr '/' mult_expr            { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_DIV);    }
	| mult_expr '%' mult_expr            { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_MOD);    }
	;

prefix_expr
	: suffix_expr                        { $<subexpr>$ = $<subexpr>1;                                               }
	| '!' prefix_expr       %prec PREFIX { $<subexpr>$ = hir_unary_op($<subexpr>2, HIR_UNARYOP_BOOLNOT);            }
	| '~' prefix_expr       %prec PREFIX { $<subexpr>$ = hir_unary_op($<subexpr>2, HIR_UNARYOP_BITNOT);             }
	| TOK_INCR prefix_expr  %prec PREFIX { $<subexpr>$ = hir_unary_op($<subexpr>2, HIR_UNARYOP_PREINCR);            }
	| TOK_DECR prefix_expr  %prec PREFIX { $<subexpr>$ = hir_unary_op($<subexpr>2, HIR_UNARYOP_PREDECR);            }
	| '+' prefix_expr       %prec PREFIX { $<subexpr>$ = $<subexpr>2;                                               }
	| '-' prefix_expr       %prec PREFIX { $<subexpr>$ = hir_unary_op($<subexpr>2, HIR_UNARYOP_NEG);                }
	| '*' prefix_expr       %prec PREFIX { $<subexpr>$ = hir_unary_op($<subexpr>2, HIR_UNARYOP_DEREF);              }
	| '&' prefix_expr       %prec PREFIX { $<subexpr>$ = hir_unary_op($<subexpr>2, HIR_UNARYOP_ADDRESS);            }
	;

suffix_expr
	: primary_expr 
	| function_call                  %prec SUFFIX { $<subexpr>$ = $<subexpr>1;                                               }
	| suffix_expr TOK_INCR           %prec SUFFIX { $<subexpr>$ = hir_unary_op($<subexpr>1, HIR_UNARYOP_POSTINCR);           }
	| suffix_expr TOK_DECR           %prec SUFFIX { $<subexpr>$ = hir_unary_op($<subexpr>1, HIR_UNARYOP_POSTDECR);           }
	| suffix_expr '[' root_expr ']'  %prec SUFFIX { $<subexpr>$ = hir_binary_op($<subexpr>1, $<subexpr>3, HIR_BINOP_ARRAY);  }
	| suffix_expr '.' TOK_IDENTIFIER       %prec SUFFIX { $<subexpr>$ = hir_selection_op($<subexpr>1, $<identifier>3, HIR_BINOP_DOT); }
	| suffix_expr TOK_ARROW TOK_IDENTIFIER %prec SUFFIX { $<subexpr>$ = hir_selection_op($<subexpr>1, $<identifier>3, HIR_BINOP_ARROW); }
	;

primary_expr
	: TOK_IDENTIFIER                     { $<subexpr>$ = hir_load_variable($<identifier>1);                         }
	| TOK_NUMBER                         { $<subexpr>$ = hir_load_immediate($<numeric>1);                           }
	| '(' root_expr ')'                  { $<subexpr>$ = $<subexpr>2;                                               }
	| TOK_STRING                         { $<subexpr>$ = hir_load_string($<string>1);                               }
	;


function_call
	: TOK_IDENTIFIER
		{ hir_start_call($<identifier>1); }
	'(' function_params ')'
		{ $<subexpr>$ = hir_finish_call(); }
	;

function_params
	: /* empty */
	| function_param
	| function_params ',' function_param
	;

function_param
	: assign_expr
		{ hir_finish_expr($<subexpr>1); }
	;



conditional_expr
	: simple_condition
		{ finish_if_block(); }
	| else_condition
		{ finish_if_block(); }
	;

simple_condition
	: TOK_IF '(' assign_expr ')'
		{ start_if_block($<subexpr>3); }
	  codeblock
	;


else_condition
	: simple_condition TOK_ELSE
		{ start_else_block(); }
	  codeblock
	;


return_statement
	: TOK_RETURN root_expr ';'
		{ hir_finish_expr(
			hir_unary_op($<subexpr>2, HIR_UNARYOP_RETURN)
		  ); }
	;

do_while_loop
	: TOK_DO
		{ start_do_while_block(); }
	  codeblock TOK_WHILE '(' root_expr ')' ';'
		{ finish_do_while_block($<subexpr>6); }
	;

while_loop
	: TOK_WHILE '(' root_expr ')'
		{ start_while_block($<subexpr>3); }
	  codeblock
		{ finish_while_block(); }
	;

for_loop
	: TOK_FOR '(' optional_expr ';' optional_expr ';' optional_expr ')'
		{ start_for_block($<subexpr>3, $<subexpr>5, $<subexpr>7); }
	  codeblock
		{ finish_for_block(); }
	;

optional_expr
	: /* empty */
	| root_expr
	;

break_statement
	: TOK_BREAK ';'
		{ hir_break(1); }
	| TOK_BREAK '(' TOK_NUMBER ')' ';'
		{ hir_break($<numeric>3); }
	;

continue_statement
	: TOK_CONTINUE ';'
		{ hir_continue(1); }
	| TOK_CONTINUE '(' TOK_NUMBER ')' ';'
		{ hir_continue($<numeric>3); }
	;



struct_definition
	: TOK_STRUCT TOK_IDENTIFIER 
		{ hir_start_struct($<identifier>2, 0); }
	  '{' struct_members '}' ';'
		{ hir_finish_struct(); }
	| TOK_UNION TOK_IDENTIFIER
		{ hir_start_struct($<identifier>2, 1); }
	  '{' struct_members '}' ';'
		{ hir_finish_struct(); }
	;

struct_members
	: struct_member
	| struct_members struct_member
	;

struct_member
	: type_specifier TOK_IDENTIFIER
		{ hir_add_member($<datatype>1, $<identifier>2); }
	  member_array_specifiers ';'
	;


member_array_specifiers
	: /* empty */
	| '[' root_expr ']'
		{ hir_member_array( $<subexpr>2 ); }
	| '[' root_expr ']' '[' root_expr ']'
		{ hir_member_array( $<subexpr>5 );
		  hir_member_array( $<subexpr>2 ); }
	| '[' root_expr ']' '[' root_expr ']' '[' root_expr ']'
		{ hir_member_array( $<subexpr>8 );
		  hir_member_array( $<subexpr>5 );
		  hir_member_array( $<subexpr>2 ); }
	;


