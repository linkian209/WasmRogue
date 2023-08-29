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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 23 "src/compile.y"
typedef union YYSTYPE {
	long numeric;
	char *string;
	id_handle_t identifier;
	type_handle_t datatype;
	hir_interm_t subexpr;
} YYSTYPE;
/* Line 1252 of yacc.c.  */
#line 141 "y.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



