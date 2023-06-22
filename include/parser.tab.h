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

#ifndef YY_YY_INCLUDE_PARSER_TAB_H_INCLUDED
# define YY_YY_INCLUDE_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
    RE_T = 258,                    /* RE_T  */
    CE_T = 259,                    /* CE_T  */
    LE_T = 260,                    /* LE_T  */
    EE_T = 261,                    /* EE_T  */
    FE_T = 262,                    /* FE_T  */
    GE_T = 263,                    /* GE_T  */
    HE_T = 264,                    /* HE_T  */
    VE_T = 265,                    /* VE_T  */
    IE_T = 266,                    /* IE_T  */
    ELM_T = 267,                   /* ELM_T  */
    INT_T = 268,                   /* INT_T  */
    DEC_T = 269,                   /* DEC_T  */
    PREF_T = 270,                  /* PREF_T  */
    TS_T = 271,                    /* TS_T  */
    DS_T = 272,                    /* DS_T  */
    AS_T = 273,                    /* AS_T  */
    G2_T = 274,                    /* G2_T  */
    END_T = 275,                   /* END_T  */
    DC_T = 276,                    /* DC_T  */
    AC_T = 277,                    /* AC_T  */
    SINE_T = 278,                  /* SINE_T  */
    PULSE_T = 279,                 /* PULSE_T  */
    RAMP_T = 280,                  /* RAMP_T  */
    STEP_T = 281,                  /* STEP_T  */
    PLT_T = 282,                   /* PLT_T  */
    IC_T = 283                     /* IC_T  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 10 "parser.y"

    char *sv;
    double dv;
    int iv;

#line 98 "./include/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_PARSER_TAB_H_INCLUDED  */
