/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_SMALLC_TAB_H_INCLUDED
# define YY_YY_SMALLC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "smallc.y" /* yacc.c:1909  */

#include "Info.h"
#include "Intermediate.h"
#include "GenIntermediate.h"
#include "MIPS32.h"


#line 52 "smallc.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    ID = 259,
    SEMI = 260,
    COMMA = 261,
    TYPE = 262,
    STRUCT = 263,
    RETURN = 264,
    IF = 265,
    ELSE = 266,
    BREAK = 267,
    CONT = 268,
    FOR = 269,
    LC = 270,
    RC = 271,
    READ = 272,
    WRITE = 273,
    LOWER_THAN_ELSE = 274,
    ASSIGN = 275,
    PLUSASSIGN = 276,
    MINUSASSIGN = 277,
    MULASSIGN = 278,
    DIVASSIGN = 279,
    ANDASSIGN = 280,
    XORASSIGN = 281,
    ORASSIGN = 282,
    SHLASSIGN = 283,
    SHRASSIGN = 284,
    LOGICALOR = 285,
    LOGICALAND = 286,
    BITOR = 287,
    BITXOR = 288,
    BITAND = 289,
    ET = 290,
    NET = 291,
    GT = 292,
    GE = 293,
    LT = 294,
    LE = 295,
    SHL = 296,
    SHR = 297,
    PLUS = 298,
    MINUS = 299,
    MUL = 300,
    DIV = 301,
    MOD = 302,
    LOGICALNOT = 303,
    PREINC = 304,
    PREDEC = 305,
    BITNOT = 306,
    LP = 307,
    RP = 308,
    LB = 309,
    RB = 310,
    DOT = 311
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 71 "smallc.y" /* yacc.c:1909  */

	int mI_Int;
	std::string* mS_Id;
	std::vector<Node*>* mV_NodeVector;
	Node* node;
	struct Variable_ArrayDeclarationInfo* mV_Var_Arr_Dec_Info;
	std::vector<Variable_ArrayDeclarationInfo*>* mV_Var_Arr_Dec_Info_Vector;
	std::vector<std::string>* mV_StringVector;

#line 131 "smallc.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SMALLC_TAB_H_INCLUDED  */
