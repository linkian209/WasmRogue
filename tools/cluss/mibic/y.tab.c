/* A Bison parser, made by GNU Bison 1.875b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_IDENTIFIER = 258,
     TOK_TYPE = 259,
     TOK_NUMBER = 260,
     TOK_STRING = 261,
     TOK_CONST = 262,
     TOK_INCR = 263,
     TOK_DECR = 264,
     TOK_IF = 265,
     TOK_ELSE = 266,
     TOK_BOGUS = 267,
     TOK_ADDEQ = 268,
     TOK_SUBEQ = 269,
     TOK_MULEQ = 270,
     TOK_DIVEQ = 271,
     TOK_MODEQ = 272,
     TOK_ANDEQ = 273,
     TOK_XOREQ = 274,
     TOK_OREQ = 275,
     TOK_LSFTEQ = 276,
     TOK_RSFTEQ = 277,
     TOK_OROR = 278,
     TOK_ANDAND = 279,
     TOK_EQEQ = 280,
     TOK_NEQ = 281,
     TOK_LTEQ = 282,
     TOK_GTEQ = 283,
     TOK_LTLT = 284,
     TOK_GTGT = 285,
     TOK_RETURN = 286,
     TOK_DO = 287,
     TOK_WHILE = 288,
     TOK_FOR = 289,
     TOK_EXTERN = 290,
     TOK_BREAK = 291,
     TOK_CONTINUE = 292,
     TOK_STRUCT = 293,
     TOK_KEY_STRING = 294,
     TOK_EXPORT = 295,
     TOK_LINK = 296,
     TOK_EVEN = 297,
     TOK_ARROW = 298,
     TOK_UNION = 299,
     TOK_SPLITPOINT = 300,
     PREFIX = 301,
     SUFFIX = 302,
     INEQUALITIES = 303
   };
#endif
#define TOK_IDENTIFIER 258
#define TOK_TYPE 259
#define TOK_NUMBER 260
#define TOK_STRING 261
#define TOK_CONST 262
#define TOK_INCR 263
#define TOK_DECR 264
#define TOK_IF 265
#define TOK_ELSE 266
#define TOK_BOGUS 267
#define TOK_ADDEQ 268
#define TOK_SUBEQ 269
#define TOK_MULEQ 270
#define TOK_DIVEQ 271
#define TOK_MODEQ 272
#define TOK_ANDEQ 273
#define TOK_XOREQ 274
#define TOK_OREQ 275
#define TOK_LSFTEQ 276
#define TOK_RSFTEQ 277
#define TOK_OROR 278
#define TOK_ANDAND 279
#define TOK_EQEQ 280
#define TOK_NEQ 281
#define TOK_LTEQ 282
#define TOK_GTEQ 283
#define TOK_LTLT 284
#define TOK_GTGT 285
#define TOK_RETURN 286
#define TOK_DO 287
#define TOK_WHILE 288
#define TOK_FOR 289
#define TOK_EXTERN 290
#define TOK_BREAK 291
#define TOK_CONTINUE 292
#define TOK_STRUCT 293
#define TOK_KEY_STRING 294
#define TOK_EXPORT 295
#define TOK_LINK 296
#define TOK_EVEN 297
#define TOK_ARROW 298
#define TOK_UNION 299
#define TOK_SPLITPOINT 300
#define PREFIX 301
#define SUFFIX 302
#define INEQUALITIES 303




/* Copy the first part of user declarations.  */
#line 1 "src/compile.y"

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
  


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 23 "src/compile.y"
typedef union YYSTYPE {
	long numeric;
	char *string;
	id_handle_t identifier;
	type_handle_t datatype;
	hir_interm_t subexpr;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 202 "y.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 214 "y.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   524

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  62
/* YYNRULES -- Number of rules. */
#define YYNRULES  154
/* YYNRULES -- Number of states. */
#define YYNSTATES  295

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,     2,     2,    52,    58,     2,
      65,    66,    50,    53,    67,    54,    71,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    68,    62,
      55,    61,    56,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,    70,    59,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    63,    60,    64,    47,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    48,    49,    57
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    15,    18,
      21,    27,    28,    33,    37,    41,    46,    48,    51,    53,
      56,    59,    63,    70,    79,    82,    85,    90,    95,   100,
     105,   106,   108,   112,   113,   115,   119,   122,   126,   129,
     132,   138,   143,   146,   150,   152,   155,   157,   159,   161,
     163,   165,   167,   169,   171,   173,   176,   178,   182,   184,
     188,   192,   196,   200,   204,   208,   212,   216,   220,   224,
     228,   230,   234,   236,   240,   242,   246,   248,   252,   254,
     258,   260,   264,   268,   270,   274,   278,   282,   286,   288,
     292,   296,   298,   302,   306,   308,   312,   316,   320,   322,
     325,   328,   331,   334,   337,   340,   343,   346,   348,   350,
     353,   356,   361,   365,   369,   371,   373,   377,   379,   380,
     386,   387,   389,   393,   395,   397,   399,   400,   407,   408,
     413,   417,   418,   427,   428,   435,   436,   447,   448,   450,
     453,   459,   462,   468,   469,   477,   478,   486,   488,   491,
     492,   498,   499,   503,   510
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
      73,     0,    -1,    -1,    73,    74,    -1,    75,    -1,   127,
      -1,    81,    -1,    82,    -1,    76,    62,    -1,    76,    78,
      -1,    35,    76,    61,     5,    62,    -1,    -1,    79,     3,
      77,    84,    -1,    63,    87,    64,    -1,    63,    90,    64,
      -1,    63,    87,    90,    64,    -1,    80,    -1,    79,    50,
      -1,     4,    -1,    38,     3,    -1,    44,     3,    -1,    40,
       3,    62,    -1,    40,     3,    65,    94,    66,    62,    -1,
      40,     3,    65,    94,    67,    94,    66,    62,    -1,    42,
      62,    -1,    45,    62,    -1,     4,    68,    93,    62,    -1,
      39,    68,     6,    62,    -1,    41,    68,     3,    62,    -1,
      41,    68,     5,    62,    -1,    -1,     3,    -1,    65,    85,
      66,    -1,    -1,    86,    -1,    85,    67,    86,    -1,    79,
      83,    -1,    87,    88,    62,    -1,    88,    62,    -1,    79,
       3,    -1,    79,     3,    69,    93,    70,    -1,    79,     3,
      61,    94,    -1,    63,    64,    -1,    63,    90,    64,    -1,
      91,    -1,    90,    91,    -1,    91,    -1,    92,    -1,   112,
      -1,   118,    -1,   120,    -1,   122,    -1,   117,    -1,   125,
      -1,   126,    -1,    93,    62,    -1,    94,    -1,    93,    67,
      94,    -1,    95,    -1,    94,    61,    94,    -1,    94,    13,
      94,    -1,    94,    14,    94,    -1,    94,    15,    94,    -1,
      94,    16,    94,    -1,    94,    17,    94,    -1,    94,    18,
      94,    -1,    94,    19,    94,    -1,    94,    20,    94,    -1,
      94,    21,    94,    -1,    94,    22,    94,    -1,    96,    -1,
      95,    23,    95,    -1,    97,    -1,    96,    24,    96,    -1,
      98,    -1,    97,    60,    97,    -1,    99,    -1,    98,    59,
      98,    -1,   100,    -1,    99,    58,    99,    -1,   101,    -1,
     100,    25,   100,    -1,   100,    26,   100,    -1,   102,    -1,
     101,    55,   101,    -1,   101,    27,   101,    -1,   101,    56,
     101,    -1,   101,    28,   101,    -1,   103,    -1,   102,    29,
     102,    -1,   102,    30,   102,    -1,   104,    -1,   103,    53,
     103,    -1,   103,    54,   103,    -1,   105,    -1,   104,    50,
     104,    -1,   104,    51,   104,    -1,   104,    52,   104,    -1,
     106,    -1,    46,   105,    -1,    47,   105,    -1,     8,   105,
      -1,     9,   105,    -1,    53,   105,    -1,    54,   105,    -1,
      50,   105,    -1,    58,   105,    -1,   107,    -1,   108,    -1,
     106,     8,    -1,   106,     9,    -1,   106,    69,    93,    70,
      -1,   106,    71,     3,    -1,   106,    43,     3,    -1,     3,
      -1,     5,    -1,    65,    93,    66,    -1,     6,    -1,    -1,
       3,   109,    65,   110,    66,    -1,    -1,   111,    -1,   110,
      67,   111,    -1,    94,    -1,   113,    -1,   115,    -1,    -1,
      10,    65,    94,    66,   114,    89,    -1,    -1,   113,    11,
     116,    89,    -1,    31,    93,    62,    -1,    -1,    32,   119,
      89,    33,    65,    93,    66,    62,    -1,    -1,    33,    65,
      93,    66,   121,    89,    -1,    -1,    34,    65,   124,    62,
     124,    62,   124,    66,   123,    89,    -1,    -1,    93,    -1,
      36,    62,    -1,    36,    65,     5,    66,    62,    -1,    37,
      62,    -1,    37,    65,     5,    66,    62,    -1,    -1,    38,
       3,   128,    63,   130,    64,    62,    -1,    -1,    44,     3,
     129,    63,   130,    64,    62,    -1,   131,    -1,   130,   131,
      -1,    -1,    79,     3,   132,   133,    62,    -1,    -1,    69,
      93,    70,    -1,    69,    93,    70,    69,    93,    70,    -1,
      69,    93,    70,    69,    93,    70,    69,    93,    70,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    55,    55,    57,    61,    62,    63,    64,    70,    72,
      74,    80,    79,    85,    86,    87,    92,    93,    98,   100,
     102,   108,   110,   112,   117,   119,   121,   123,   125,   127,
     135,   136,   143,   146,   148,   149,   153,   159,   160,   164,
     166,   184,   200,   201,   202,   206,   207,   211,   212,   213,
     214,   215,   216,   217,   218,   222,   227,   228,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     247,   248,   252,   253,   257,   258,   262,   263,   267,   268,
     272,   273,   274,   278,   279,   280,   281,   282,   286,   287,
     288,   292,   293,   294,   298,   299,   300,   301,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   317,   318,   319,
     320,   321,   322,   323,   327,   328,   329,   330,   336,   335,
     341,   343,   344,   348,   355,   357,   363,   362,   370,   369,
     376,   384,   383,   391,   390,   398,   397,   403,   405,   409,
     411,   416,   418,   426,   425,   430,   429,   436,   437,   442,
     441,   447,   449,   451,   454
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_IDENTIFIER", "TOK_TYPE", "TOK_NUMBER", 
  "TOK_STRING", "TOK_CONST", "TOK_INCR", "TOK_DECR", "TOK_IF", "TOK_ELSE", 
  "TOK_BOGUS", "TOK_ADDEQ", "TOK_SUBEQ", "TOK_MULEQ", "TOK_DIVEQ", 
  "TOK_MODEQ", "TOK_ANDEQ", "TOK_XOREQ", "TOK_OREQ", "TOK_LSFTEQ", 
  "TOK_RSFTEQ", "TOK_OROR", "TOK_ANDAND", "TOK_EQEQ", "TOK_NEQ", 
  "TOK_LTEQ", "TOK_GTEQ", "TOK_LTLT", "TOK_GTGT", "TOK_RETURN", "TOK_DO", 
  "TOK_WHILE", "TOK_FOR", "TOK_EXTERN", "TOK_BREAK", "TOK_CONTINUE", 
  "TOK_STRUCT", "TOK_KEY_STRING", "TOK_EXPORT", "TOK_LINK", "TOK_EVEN", 
  "TOK_ARROW", "TOK_UNION", "TOK_SPLITPOINT", "'!'", "'~'", "PREFIX", 
  "SUFFIX", "'*'", "'/'", "'%'", "'+'", "'-'", "'<'", "'>'", 
  "INEQUALITIES", "'&'", "'^'", "'|'", "'='", "';'", "'{'", "'}'", "'('", 
  "')'", "','", "':'", "'['", "']'", "'.'", "$accept", "start", "glbl", 
  "func", "prototype", "@1", "func_body", "type_specifier", 
  "direct_declarator", "emitted_label", "directive", 
  "optional_identifier", "paramlist", "parameters", "parameter", 
  "varlist", "vardecl", "codeblock", "expr_group", "complete_expr", 
  "normal_expr", "root_expr", "assign_expr", "bool_or_expr", 
  "bool_and_expr", "or_expr", "xor_expr", "and_expr", "comparison_expr", 
  "inequality_expr", "shift_expr", "additive_expr", "mult_expr", 
  "prefix_expr", "suffix_expr", "primary_expr", "function_call", "@2", 
  "function_params", "function_param", "conditional_expr", 
  "simple_condition", "@3", "else_condition", "@4", "return_statement", 
  "do_while_loop", "@5", "while_loop", "@6", "for_loop", "@7", 
  "optional_expr", "break_statement", "continue_statement", 
  "struct_definition", "@8", "@9", "struct_members", "struct_member", 
  "@10", "member_array_specifiers", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    33,   126,   301,   302,
      42,    47,    37,    43,    45,    60,    62,   303,    38,    94,
     124,    61,    59,   123,   125,    40,    41,    44,    58,    91,
      93,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    72,    73,    73,    74,    74,    74,    74,    75,    75,
      75,    77,    76,    78,    78,    78,    79,    79,    80,    80,
      80,    81,    81,    81,    82,    82,    82,    82,    82,    82,
      83,    83,    84,    85,    85,    85,    86,    87,    87,    88,
      88,    88,    89,    89,    89,    90,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    92,    93,    93,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      95,    95,    96,    96,    97,    97,    98,    98,    99,    99,
     100,   100,   100,   101,   101,   101,   101,   101,   102,   102,
     102,   103,   103,   103,   104,   104,   104,   104,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   106,   106,
     106,   106,   106,   106,   107,   107,   107,   107,   109,   108,
     110,   110,   110,   111,   112,   112,   114,   113,   116,   115,
     117,   119,   118,   121,   120,   123,   122,   124,   124,   125,
     125,   126,   126,   128,   127,   129,   127,   130,   130,   132,
     131,   133,   133,   133,   133
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     2,     2,
       5,     0,     4,     3,     3,     4,     1,     2,     1,     2,
       2,     3,     6,     8,     2,     2,     4,     4,     4,     4,
       0,     1,     3,     0,     1,     3,     2,     3,     2,     2,
       5,     4,     2,     3,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     1,     2,
       2,     4,     3,     3,     1,     1,     3,     1,     0,     5,
       0,     1,     3,     1,     1,     1,     0,     6,     0,     4,
       3,     0,     8,     0,     6,     0,    10,     0,     1,     2,
       5,     2,     5,     0,     7,     0,     7,     1,     2,     0,
       5,     0,     3,     6,     9
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     1,    18,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     4,     0,     0,    16,     6,     7,     5,
       0,    18,     0,     0,     0,    19,     0,     0,     0,    24,
      20,    25,     8,     0,     9,    11,    17,   114,   115,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,    58,    70,    72,    74,    76,    78,    80,    83,    88,
      91,    94,    98,   107,   108,    19,    20,     0,     0,     0,
      21,     0,     0,     0,     0,     0,     0,   131,     0,     0,
       0,     0,     0,     0,     0,     0,    46,    47,     0,    48,
     124,   125,    52,    49,    50,    51,    53,    54,     0,     0,
     101,   102,    99,   100,   105,   103,   104,   106,     0,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,   110,     0,     0,     0,     0,     0,    27,     0,    28,
      29,     0,     0,     0,     0,     0,   137,   139,     0,   141,
       0,    39,    13,     0,     0,    38,    14,    45,    55,   128,
      33,    12,   120,   116,    57,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    59,    71,    73,    75,    77,
      79,    81,    82,    85,    87,    84,    86,    89,    90,    92,
      93,    95,    96,    97,   113,     0,   112,    10,     0,     0,
     147,     0,     0,     0,     0,   130,     0,     0,    44,     0,
     138,     0,     0,     0,     0,     0,    37,    15,     0,    30,
       0,    34,   123,     0,   121,   111,   149,     0,   148,    22,
       0,     0,   126,    42,     0,     0,   133,   137,     0,     0,
      41,     0,   129,    31,    36,    32,     0,   119,     0,   151,
     144,     0,   146,     0,    43,     0,     0,     0,   140,   142,
      40,    35,   122,     0,     0,    23,   127,     0,   134,   137,
       0,   150,     0,     0,   152,   132,   135,     0,     0,     0,
     136,   153,     0,     0,   154
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,    12,    13,    14,    98,    34,   208,    16,    17,
      18,   254,   171,   230,   231,    83,    84,   217,    85,   218,
      87,    88,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    99,   233,   234,
      89,    90,   263,    91,   228,    92,    93,   154,    94,   266,
      95,   288,   221,    96,    97,    19,    68,    74,   209,   210,
     259,   274
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -232
static const short yypact[] =
{
    -232,   451,  -232,   -11,    75,    77,    48,    91,    60,    70,
     139,   111,  -232,  -232,    23,     5,  -232,  -232,  -232,  -232,
     109,  -232,   151,   168,    73,   115,   169,    13,    90,  -232,
     154,  -232,  -232,   178,  -232,  -232,  -232,   153,  -232,  -232,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   -50,
     463,   196,   197,   160,   164,   171,     6,    -6,    92,   112,
     -26,  -232,     1,  -232,  -232,  -232,  -232,   221,   167,   172,
    -232,   109,   177,   182,   170,   181,   109,  -232,   183,   184,
      42,    43,    24,    93,   185,   232,  -232,  -232,   -47,  -232,
     239,  -232,  -232,  -232,  -232,  -232,  -232,  -232,   186,   187,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,   102,  -232,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
    -232,  -232,   251,   109,   252,   195,    75,  -232,    21,  -232,
    -232,    75,   109,   -44,   295,   109,   109,  -232,   253,  -232,
     255,   -55,  -232,   199,   330,  -232,  -232,  -232,  -232,  -232,
      75,  -232,   109,  -232,   463,   463,   463,   463,   463,   463,
     463,   463,   463,   463,   463,   463,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,    74,  -232,  -232,    26,     7,
    -232,   200,   109,     9,   293,  -232,   365,   237,  -232,   110,
     204,   211,   208,   209,   109,   109,  -232,  -232,   295,    27,
     113,  -232,   463,   131,  -232,  -232,  -232,   214,  -232,  -232,
     453,   215,  -232,  -232,   400,   216,  -232,   109,   218,   222,
     463,    78,  -232,  -232,  -232,  -232,    75,  -232,   109,   219,
    -232,   225,  -232,   295,  -232,   109,   295,   227,  -232,  -232,
    -232,  -232,  -232,   109,   229,  -232,  -232,   133,  -232,   109,
      82,  -232,   230,   217,   224,  -232,  -232,   109,   295,    83,
    -232,   226,   109,    94,  -232
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -232,  -232,  -232,  -232,   290,  -232,  -232,     0,  -232,  -232,
    -232,  -232,  -232,  -232,    46,  -232,   233,  -182,   -78,   -31,
    -232,   -20,   -52,   198,   176,   193,   194,   192,    76,   -40,
      68,    72,   -28,   149,  -232,  -232,  -232,  -232,  -232,    63,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -231,  -232,  -232,  -232,  -232,  -232,   173,  -206,
    -232,  -232
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -146
static const short yytable[] =
{
      49,    15,    86,   238,    15,   164,   224,   238,    35,   140,
     141,    21,   109,    21,   225,   168,   267,   110,   215,   148,
     110,   129,   130,   110,   137,   138,   139,   161,   108,   236,
     253,   127,   128,    82,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   142,    22,   252,    22,   283,   131,
     132,    23,    86,    23,   167,    36,   153,    20,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     143,   237,   144,   241,    36,    70,    36,    36,    71,    21,
      25,   276,   121,    82,   278,    32,    33,   211,   212,   193,
     194,   195,   196,    72,    27,    73,    37,    21,    38,    39,
     214,    40,    41,    75,   157,   159,   290,   158,   160,   201,
     202,   203,    37,    22,    38,    39,    26,    40,    41,    23,
     232,   133,   134,   205,    76,    77,    78,    79,    28,    80,
      81,    22,    29,   167,    67,   219,   220,    23,   244,    42,
      43,   110,    30,    44,   235,   110,    45,    46,   270,   110,
     110,    47,   284,   291,    65,    42,    43,   162,    48,    44,
     240,   110,    45,    46,   294,   135,   136,    47,   173,   110,
     229,    66,   250,    31,    48,    69,   246,   110,  -143,   255,
     256,    37,    21,    38,    39,    86,    40,    41,    75,   100,
     101,   102,   103,   104,   105,   106,   107,   257,   258,   282,
     110,   197,   198,   191,   192,   251,   232,   199,   200,    76,
      77,    78,    79,   167,    80,    81,    22,  -145,  -118,   122,
     124,   123,    23,   125,    42,    43,   145,   220,    44,   126,
     146,    45,    46,   151,   147,    37,    47,    38,    39,   149,
      40,    41,    75,    48,   150,   277,   152,   165,   155,   156,
     169,   170,   172,   280,   204,   206,   229,   207,   222,   220,
     223,   226,   239,    76,    77,    78,    79,   289,    80,    81,
     245,   110,   293,   247,   248,   249,   260,   262,    42,    43,
     268,   265,    44,   286,   269,    45,    46,   275,   273,   279,
      47,   281,   285,   287,    24,   292,   166,    48,    37,   187,
      38,    39,   271,    40,    41,    75,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   163,   188,   190,   189,
     186,   272,     0,     0,   213,     0,    76,    77,    78,    79,
       0,    80,    81,    37,     0,    38,    39,     0,    40,    41,
      75,    42,    43,     0,     0,    44,     0,     0,    45,    46,
       0,     0,     0,    47,   121,     0,     0,     0,   216,   242,
      48,    76,    77,    78,    79,     0,    80,    81,    37,     0,
      38,    39,     0,    40,    41,    75,    42,    43,     0,     0,
      44,     0,     0,    45,    46,     0,     0,     0,    47,     0,
       0,     0,     0,     0,   227,    48,    76,    77,    78,    79,
       0,    80,    81,    37,     0,    38,    39,     0,    40,    41,
      75,    42,    43,     0,     0,    44,     0,     0,    45,    46,
       0,     0,     0,    47,     0,     0,     0,     0,     0,   243,
      48,    76,    77,    78,    79,     0,    80,    81,     0,     0,
       0,     0,     0,     0,     0,     0,    42,    43,     0,     0,
      44,     2,     0,    45,    46,     3,     0,     0,    47,     0,
       0,     0,     0,     0,   264,    48,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,     4,     0,     0,     5,
       6,     7,     8,     9,     0,    10,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,     0,     0,     0,     0,   261,
       0,     0,     0,     0,   121
};

static const short yycheck[] =
{
      20,     1,    33,   209,     4,    83,    61,   213,     3,     8,
       9,     4,    62,     4,    69,    62,   247,    67,    62,    71,
      67,    27,    28,    67,    50,    51,    52,     3,    48,     3,
       3,    25,    26,    33,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    43,    38,   228,    38,   279,    55,
      56,    44,    83,    44,    85,    50,    76,    68,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      69,    64,    71,    64,    50,    62,    50,    50,    65,     4,
       3,   263,    61,    83,   266,    62,    63,    66,    67,   129,
     130,   131,   132,     3,     3,     5,     3,     4,     5,     6,
     152,     8,     9,    10,    62,    62,   288,    65,    65,   137,
     138,   139,     3,    38,     5,     6,    68,     8,     9,    44,
     172,    29,    30,   143,    31,    32,    33,    34,    68,    36,
      37,    38,    62,   164,    61,   155,   156,    44,   216,    46,
      47,    67,     3,    50,    70,    67,    53,    54,    70,    67,
      67,    58,    70,    70,     3,    46,    47,    64,    65,    50,
     212,    67,    53,    54,    70,    53,    54,    58,    66,    67,
     170,     3,   224,    62,    65,     6,    66,    67,    63,    66,
      67,     3,     4,     5,     6,   216,     8,     9,    10,    40,
      41,    42,    43,    44,    45,    46,    47,    66,    67,    66,
      67,   133,   134,   127,   128,   225,   258,   135,   136,    31,
      32,    33,    34,   244,    36,    37,    38,    63,    65,    23,
      60,    24,    44,    59,    46,    47,     5,   247,    50,    58,
      63,    53,    54,    63,    62,     3,    58,     5,     6,    62,
       8,     9,    10,    65,    62,   265,    65,    62,    65,    65,
      11,    65,    65,   273,     3,     3,   256,    62,     5,   279,
       5,    62,    62,    31,    32,    33,    34,   287,    36,    37,
      33,    67,   292,    62,    66,    66,    62,    62,    46,    47,
      62,    65,    50,    66,    62,    53,    54,    62,    69,    62,
      58,    62,    62,    69,     4,    69,    64,    65,     3,   123,
       5,     6,   256,     8,     9,    10,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    83,   124,   126,   125,
     122,   258,    -1,    -1,   151,    -1,    31,    32,    33,    34,
      -1,    36,    37,     3,    -1,     5,     6,    -1,     8,     9,
      10,    46,    47,    -1,    -1,    50,    -1,    -1,    53,    54,
      -1,    -1,    -1,    58,    61,    -1,    -1,    -1,    63,    66,
      65,    31,    32,    33,    34,    -1,    36,    37,     3,    -1,
       5,     6,    -1,     8,     9,    10,    46,    47,    -1,    -1,
      50,    -1,    -1,    53,    54,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    64,    65,    31,    32,    33,    34,
      -1,    36,    37,     3,    -1,     5,     6,    -1,     8,     9,
      10,    46,    47,    -1,    -1,    50,    -1,    -1,    53,    54,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    64,
      65,    31,    32,    33,    34,    -1,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,
      50,     0,    -1,    53,    54,     4,    -1,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    64,    65,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    35,    -1,    -1,    38,
      39,    40,    41,    42,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    61
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    73,     0,     4,    35,    38,    39,    40,    41,    42,
      44,    45,    74,    75,    76,    79,    80,    81,    82,   127,
      68,     4,    38,    44,    76,     3,    68,     3,    68,    62,
       3,    62,    62,    63,    78,     3,    50,     3,     5,     6,
       8,     9,    46,    47,    50,    53,    54,    58,    65,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,     3,     3,    61,   128,     6,
      62,    65,     3,     5,   129,    10,    31,    32,    33,    34,
      36,    37,    79,    87,    88,    90,    91,    92,    93,   112,
     113,   115,   117,   118,   120,   122,   125,   126,    77,   109,
     105,   105,   105,   105,   105,   105,   105,   105,    93,    62,
      67,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    61,    23,    24,    60,    59,    58,    25,    26,    27,
      28,    55,    56,    29,    30,    53,    54,    50,    51,    52,
       8,     9,    43,    69,    71,     5,    63,    62,    94,    62,
      62,    63,    65,    93,   119,    65,    65,    62,    65,    62,
      65,     3,    64,    88,    90,    62,    64,    91,    62,    11,
      65,    84,    65,    66,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    95,    96,    97,    98,
      99,   100,   100,   101,   101,   101,   101,   102,   102,   103,
     103,   104,   104,   104,     3,    93,     3,    62,    79,   130,
     131,    66,    67,   130,    94,    62,    63,    89,    91,    93,
      93,   124,     5,     5,    61,    69,    62,    64,   116,    79,
      85,    86,    94,   110,   111,    70,     3,    64,   131,    62,
      94,    64,    66,    64,    90,    33,    66,    62,    66,    66,
      94,    93,    89,     3,    83,    66,    67,    66,    67,   132,
      62,    66,    62,   114,    64,    65,   121,   124,    62,    62,
      70,    86,   111,    69,   133,    62,    89,    93,    89,    62,
      93,    62,    66,   124,    70,    62,    66,    69,   123,    93,
      89,    70,    69,    93,    70
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:
#line 71 "src/compile.y"
    { hir_finish_prototype(); }
    break;

  case 9:
#line 73 "src/compile.y"
    { hir_finish_func_body(); }
    break;

  case 10:
#line 75 "src/compile.y"
    { hir_finish_extern_func(yyvsp[-1].numeric); }
    break;

  case 11:
#line 80 "src/compile.y"
    { hir_start_func(yyvsp[-1].datatype, yyvsp[0].identifier); }
    break;

  case 17:
#line 94 "src/compile.y"
    { yyval.datatype=type_pointer_to(yyvsp[-1].datatype); }
    break;

  case 18:
#line 99 "src/compile.y"
    { yyval.datatype=yyvsp[0].datatype; }
    break;

  case 19:
#line 101 "src/compile.y"
    { yyval.datatype = type_struct_named(yyvsp[0].identifier); }
    break;

  case 20:
#line 103 "src/compile.y"
    { yyval.datatype = type_struct_named(yyvsp[0].identifier); }
    break;

  case 21:
#line 109 "src/compile.y"
    { hir_emit_label(yyvsp[-1].identifier, hir_load_immediate(0), -1); }
    break;

  case 22:
#line 111 "src/compile.y"
    { hir_emit_label(yyvsp[-4].identifier, yyvsp[-2].subexpr, -1); }
    break;

  case 23:
#line 113 "src/compile.y"
    { hir_emit_label(yyvsp[-6].identifier, yyvsp[-4].subexpr, yyvsp[-2].subexpr); }
    break;

  case 24:
#line 118 "src/compile.y"
    { lir_write_inst(LIR_EVEN); }
    break;

  case 25:
#line 120 "src/compile.y"
    { lir_write_inst(LIR_SPLITPOINT); }
    break;

  case 26:
#line 122 "src/compile.y"
    { hir_emit_constant(yyvsp[-3].datatype, yyvsp[-1].subexpr); }
    break;

  case 27:
#line 124 "src/compile.y"
    { hir_emit_string(yyvsp[-1].string); }
    break;

  case 28:
#line 126 "src/compile.y"
    { hir_emit_link(yyvsp[-1].identifier); }
    break;

  case 29:
#line 128 "src/compile.y"
    { hir_emit_constant(type_base(type_short), 0);
		  hir_emit_constant(type_base(type_short), yyvsp[-1].numeric);
		}
    break;

  case 30:
#line 135 "src/compile.y"
    { yyval.identifier = blank_identifier(); }
    break;

  case 31:
#line 137 "src/compile.y"
    { yyval.identifier = yyvsp[0].identifier; }
    break;

  case 36:
#line 154 "src/compile.y"
    { hir_add_variable(yyvsp[-1].datatype, yyvsp[0].identifier, 1); }
    break;

  case 39:
#line 165 "src/compile.y"
    { hir_add_variable(yyvsp[-1].datatype, yyvsp[0].identifier, 0); }
    break;

  case 40:
#line 167 "src/compile.y"
    {
		hir_add_variable(type_pointer_to(yyvsp[-4].datatype), yyvsp[-3].identifier, 0);
		hir_finish_expr(
			hir_binary_op(
				hir_load_variable(yyvsp[-3].identifier),
				hir_unary_op(
					hir_binary_op(
						yyvsp[-1].subexpr,
						hir_load_immediate(type_size(yyvsp[-4].datatype)),
						HIR_BINOP_MUL
					),
					HIR_UNARYOP_ALLOCA
				),
				HIR_BINOP_EQ
			)
		);
	  }
    break;

  case 41:
#line 185 "src/compile.y"
    {
		hir_add_variable(yyvsp[-3].datatype, yyvsp[-2].identifier, 0);
		hir_finish_expr(
			hir_binary_op(
				hir_load_variable(yyvsp[-2].identifier),
				yyvsp[0].subexpr,
				HIR_BINOP_EQ
			)
		);
	  }
    break;

  case 55:
#line 223 "src/compile.y"
    { hir_finish_expr(yyvsp[-1].subexpr); }
    break;

  case 56:
#line 227 "src/compile.y"
    { yyval.subexpr = yyvsp[0].subexpr;                                               }
    break;

  case 57:
#line 228 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_COMMA);  }
    break;

  case 58:
#line 232 "src/compile.y"
    { yyval.subexpr = yyvsp[0].subexpr;                                               }
    break;

  case 59:
#line 233 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_EQ);     }
    break;

  case 60:
#line 234 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_ADDEQ);  }
    break;

  case 61:
#line 235 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_SUBEQ);  }
    break;

  case 62:
#line 236 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_MULEQ);  }
    break;

  case 63:
#line 237 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_DIVEQ);  }
    break;

  case 64:
#line 238 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_MODEQ);  }
    break;

  case 65:
#line 239 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_ANDEQ);  }
    break;

  case 66:
#line 240 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_XOREQ);  }
    break;

  case 67:
#line 241 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_OREQ);   }
    break;

  case 68:
#line 242 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_LSFTEQ); }
    break;

  case 69:
#line 243 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_RSFTEQ); }
    break;

  case 71:
#line 248 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_OROR);   }
    break;

  case 73:
#line 253 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_ANDAND); }
    break;

  case 75:
#line 258 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_OR);     }
    break;

  case 77:
#line 263 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_XOR);    }
    break;

  case 79:
#line 268 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_AND);    }
    break;

  case 81:
#line 273 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_EQEQ);   }
    break;

  case 82:
#line 274 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_NEQ);    }
    break;

  case 84:
#line 279 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_LT);     }
    break;

  case 85:
#line 280 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_LTEQ);   }
    break;

  case 86:
#line 281 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_GT);     }
    break;

  case 87:
#line 282 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_GTEQ);   }
    break;

  case 89:
#line 287 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_LSHIFT); }
    break;

  case 90:
#line 288 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_RSHIFT); }
    break;

  case 92:
#line 293 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_ADD);    }
    break;

  case 93:
#line 294 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_SUB);    }
    break;

  case 95:
#line 299 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_MUL);    }
    break;

  case 96:
#line 300 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_DIV);    }
    break;

  case 97:
#line 301 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-2].subexpr, yyvsp[0].subexpr, HIR_BINOP_MOD);    }
    break;

  case 98:
#line 305 "src/compile.y"
    { yyval.subexpr = yyvsp[0].subexpr;                                               }
    break;

  case 99:
#line 306 "src/compile.y"
    { yyval.subexpr = hir_unary_op(yyvsp[0].subexpr, HIR_UNARYOP_BOOLNOT);            }
    break;

  case 100:
#line 307 "src/compile.y"
    { yyval.subexpr = hir_unary_op(yyvsp[0].subexpr, HIR_UNARYOP_BITNOT);             }
    break;

  case 101:
#line 308 "src/compile.y"
    { yyval.subexpr = hir_unary_op(yyvsp[0].subexpr, HIR_UNARYOP_PREINCR);            }
    break;

  case 102:
#line 309 "src/compile.y"
    { yyval.subexpr = hir_unary_op(yyvsp[0].subexpr, HIR_UNARYOP_PREDECR);            }
    break;

  case 103:
#line 310 "src/compile.y"
    { yyval.subexpr = yyvsp[0].subexpr;                                               }
    break;

  case 104:
#line 311 "src/compile.y"
    { yyval.subexpr = hir_unary_op(yyvsp[0].subexpr, HIR_UNARYOP_NEG);                }
    break;

  case 105:
#line 312 "src/compile.y"
    { yyval.subexpr = hir_unary_op(yyvsp[0].subexpr, HIR_UNARYOP_DEREF);              }
    break;

  case 106:
#line 313 "src/compile.y"
    { yyval.subexpr = hir_unary_op(yyvsp[0].subexpr, HIR_UNARYOP_ADDRESS);            }
    break;

  case 108:
#line 318 "src/compile.y"
    { yyval.subexpr = yyvsp[0].subexpr;                                               }
    break;

  case 109:
#line 319 "src/compile.y"
    { yyval.subexpr = hir_unary_op(yyvsp[-1].subexpr, HIR_UNARYOP_POSTINCR);           }
    break;

  case 110:
#line 320 "src/compile.y"
    { yyval.subexpr = hir_unary_op(yyvsp[-1].subexpr, HIR_UNARYOP_POSTDECR);           }
    break;

  case 111:
#line 321 "src/compile.y"
    { yyval.subexpr = hir_binary_op(yyvsp[-3].subexpr, yyvsp[-1].subexpr, HIR_BINOP_ARRAY);  }
    break;

  case 112:
#line 322 "src/compile.y"
    { yyval.subexpr = hir_selection_op(yyvsp[-2].subexpr, yyvsp[0].identifier, HIR_BINOP_DOT); }
    break;

  case 113:
#line 323 "src/compile.y"
    { yyval.subexpr = hir_selection_op(yyvsp[-2].subexpr, yyvsp[0].identifier, HIR_BINOP_ARROW); }
    break;

  case 114:
#line 327 "src/compile.y"
    { yyval.subexpr = hir_load_variable(yyvsp[0].identifier);                         }
    break;

  case 115:
#line 328 "src/compile.y"
    { yyval.subexpr = hir_load_immediate(yyvsp[0].numeric);                           }
    break;

  case 116:
#line 329 "src/compile.y"
    { yyval.subexpr = yyvsp[-1].subexpr;                                               }
    break;

  case 117:
#line 330 "src/compile.y"
    { yyval.subexpr = hir_load_string(yyvsp[0].string);                               }
    break;

  case 118:
#line 336 "src/compile.y"
    { hir_start_call(yyvsp[0].identifier); }
    break;

  case 119:
#line 338 "src/compile.y"
    { yyval.subexpr = hir_finish_call(); }
    break;

  case 123:
#line 349 "src/compile.y"
    { hir_finish_expr(yyvsp[0].subexpr); }
    break;

  case 124:
#line 356 "src/compile.y"
    { finish_if_block(); }
    break;

  case 125:
#line 358 "src/compile.y"
    { finish_if_block(); }
    break;

  case 126:
#line 363 "src/compile.y"
    { start_if_block(yyvsp[-1].subexpr); }
    break;

  case 128:
#line 370 "src/compile.y"
    { start_else_block(); }
    break;

  case 130:
#line 377 "src/compile.y"
    { hir_finish_expr(
			hir_unary_op(yyvsp[-1].subexpr, HIR_UNARYOP_RETURN)
		  ); }
    break;

  case 131:
#line 384 "src/compile.y"
    { start_do_while_block(); }
    break;

  case 132:
#line 386 "src/compile.y"
    { finish_do_while_block(yyvsp[-2].subexpr); }
    break;

  case 133:
#line 391 "src/compile.y"
    { start_while_block(yyvsp[-1].subexpr); }
    break;

  case 134:
#line 393 "src/compile.y"
    { finish_while_block(); }
    break;

  case 135:
#line 398 "src/compile.y"
    { start_for_block(yyvsp[-5].subexpr, yyvsp[-3].subexpr, yyvsp[-1].subexpr); }
    break;

  case 136:
#line 400 "src/compile.y"
    { finish_for_block(); }
    break;

  case 139:
#line 410 "src/compile.y"
    { hir_break(1); }
    break;

  case 140:
#line 412 "src/compile.y"
    { hir_break(yyvsp[-2].numeric); }
    break;

  case 141:
#line 417 "src/compile.y"
    { hir_continue(1); }
    break;

  case 142:
#line 419 "src/compile.y"
    { hir_continue(yyvsp[-2].numeric); }
    break;

  case 143:
#line 426 "src/compile.y"
    { hir_start_struct(yyvsp[0].identifier, 0); }
    break;

  case 144:
#line 428 "src/compile.y"
    { hir_finish_struct(); }
    break;

  case 145:
#line 430 "src/compile.y"
    { hir_start_struct(yyvsp[0].identifier, 1); }
    break;

  case 146:
#line 432 "src/compile.y"
    { hir_finish_struct(); }
    break;

  case 149:
#line 442 "src/compile.y"
    { hir_add_member(yyvsp[-1].datatype, yyvsp[0].identifier); }
    break;

  case 152:
#line 450 "src/compile.y"
    { hir_member_array( yyvsp[-1].subexpr ); }
    break;

  case 153:
#line 452 "src/compile.y"
    { hir_member_array( yyvsp[-1].subexpr );
		  hir_member_array( yyvsp[-4].subexpr ); }
    break;

  case 154:
#line 455 "src/compile.y"
    { hir_member_array( yyvsp[-1].subexpr );
		  hir_member_array( yyvsp[-4].subexpr );
		  hir_member_array( yyvsp[-7].subexpr ); }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1962 "y.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}



