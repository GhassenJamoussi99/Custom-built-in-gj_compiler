/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INCLUDE_TOKEN_H_INCLUDED
# define YY_YY_INCLUDE_TOKEN_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_ID = 258,                /* TOKEN_ID  */
    TOKEN_STRING_LITERAL = 259,    /* TOKEN_STRING_LITERAL  */
    TOKEN_INT = 260,               /* TOKEN_INT  */
    TOKEN_PLUS = 261,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 262,             /* TOKEN_MINUS  */
    TOKEN_MUL = 263,               /* TOKEN_MUL  */
    TOKEN_DIV = 264,               /* TOKEN_DIV  */
    TOKEN_SEMI = 265,              /* TOKEN_SEMI  */
    TOKEN_LPAREN = 266,            /* TOKEN_LPAREN  */
    TOKEN_RPAREN = 267,            /* TOKEN_RPAREN  */
    TOKEN_ASSIGN = 268,            /* TOKEN_ASSIGN  */
    TOKEN_ERROR = 269,             /* TOKEN_ERROR  */
    TOKEN_IF = 270,                /* TOKEN_IF  */
    TOKEN_WHILE = 271,             /* TOKEN_WHILE  */
    TOKEN_PRINT = 272,             /* TOKEN_PRINT  */
    TOKEN_RETURN = 273,            /* TOKEN_RETURN  */
    TOKEN_LBRACE = 274,            /* TOKEN_LBRACE  */
    TOKEN_RBRACE = 275,            /* TOKEN_RBRACE  */
    TOKEN_COMMA = 276,             /* TOKEN_COMMA  */
    TOKEN_VOID = 277,              /* TOKEN_VOID  */
    TOKEN_INT_TYPE = 278,          /* TOKEN_INT_TYPE  */
    TOKEN_BOOLEAN_TYPE = 279,      /* TOKEN_BOOLEAN_TYPE  */
    TOKEN_STRING_TYPE = 280,       /* TOKEN_STRING_TYPE  */
    TOKEN_FOR = 281,               /* TOKEN_FOR  */
    TOKEN_FUNCTION = 282,          /* TOKEN_FUNCTION  */
    TOKEN_DPOINTS = 283,           /* TOKEN_DPOINTS  */
    TOKEN_INCREMENT = 284,         /* TOKEN_INCREMENT  */
    TOKEN_DECREMENT = 285,         /* TOKEN_DECREMENT  */
    TOKEN_EQ = 286,                /* TOKEN_EQ  */
    TOKEN_NEQ = 287,               /* TOKEN_NEQ  */
    TOKEN_LT = 288,                /* TOKEN_LT  */
    TOKEN_GT = 289,                /* TOKEN_GT  */
    TOKEN_LEQ = 290,               /* TOKEN_LEQ  */
    TOKEN_GEQ = 291,               /* TOKEN_GEQ  */
    TOKEN_TRUE = 292,              /* TOKEN_TRUE  */
    TOKEN_FALSE = 293,             /* TOKEN_FALSE  */
    TOKEN_ELSE = 295               /* TOKEN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 48 "assets/parser.bison"

    struct expr *expr_ptr;
    struct decl *decl;
    struct stmt *stmt;
    struct type *type;
    struct param_list *param;
    char* expr_id;
    struct expr *string_literal;

#line 113 "include/token.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_TOKEN_H_INCLUDED  */
