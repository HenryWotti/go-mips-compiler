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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    FLOAT_TYPE_CAST = 258,         /* FLOAT_TYPE_CAST  */
    INT_TYPE_CAST = 259,           /* INT_TYPE_CAST  */
    STRING_VAL = 260,              /* STRING_VAL  */
    ELSE = 261,                    /* ELSE  */
    FOR = 262,                     /* FOR  */
    FUNC = 263,                    /* FUNC  */
    IF = 264,                      /* IF  */
    PACKAGE = 265,                 /* PACKAGE  */
    IMPORT = 266,                  /* IMPORT  */
    RETURN = 267,                  /* RETURN  */
    VAR = 268,                     /* VAR  */
    INT_TYPE = 269,                /* INT_TYPE  */
    FLOAT_TYPE = 270,              /* FLOAT_TYPE  */
    STRING_TYPE = 271,             /* STRING_TYPE  */
    VOID_TYPE = 272,               /* VOID_TYPE  */
    BOOL_TYPE = 273,               /* BOOL_TYPE  */
    PLUS_PLUS = 274,               /* PLUS_PLUS  */
    PLUS = 275,                    /* PLUS  */
    MINUS_MINUS = 276,             /* MINUS_MINUS  */
    MINUS = 277,                   /* MINUS  */
    TIMES = 278,                   /* TIMES  */
    OVER = 279,                    /* OVER  */
    REST = 280,                    /* REST  */
    AND = 281,                     /* AND  */
    OR = 282,                      /* OR  */
    EQUALS = 283,                  /* EQUALS  */
    LESS_EQUAL = 284,              /* LESS_EQUAL  */
    MORE_EQUAL = 285,              /* MORE_EQUAL  */
    LESS = 286,                    /* LESS  */
    MORE = 287,                    /* MORE  */
    DIFERS = 288,                  /* DIFERS  */
    NOT = 289,                     /* NOT  */
    LEFT_PARENTESES = 290,         /* LEFT_PARENTESES  */
    RIGHT_PARENTESES = 291,        /* RIGHT_PARENTESES  */
    LEFT_BRACKET = 292,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 293,           /* RIGHT_BRACKET  */
    LEFT_BRACE = 294,              /* LEFT_BRACE  */
    RIGHT_BRACE = 295,             /* RIGHT_BRACE  */
    FLOAT_VAL = 296,               /* FLOAT_VAL  */
    INT_VAL = 297,                 /* INT_VAL  */
    BOOL_VAL = 298,                /* BOOL_VAL  */
    ID = 299,                      /* ID  */
    SHORT_ASSIGN = 300,            /* SHORT_ASSIGN  */
    ASSIGN = 301,                  /* ASSIGN  */
    SEMI = 302,                    /* SEMI  */
    ADDRESS = 303,                 /* ADDRESS  */
    COMMA = 304,                   /* COMMA  */
    MAIN = 305,                    /* MAIN  */
    PRINTLN = 306,                 /* PRINTLN  */
    SCANF = 307,                   /* SCANF  */
    FORMAT_STRING = 308,           /* FORMAT_STRING  */
    FORMAT_INT = 309,              /* FORMAT_INT  */
    FORMAT_FLOAT = 310,            /* FORMAT_FLOAT  */
    FORMAT_BOOL = 311,             /* FORMAT_BOOL  */
    IFX = 312                      /* IFX  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */
