/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 10 "smallc.y" /* yacc.c:339  */

////////////////////////////////////////////////////////////////////////
/*
  File Name: smallc.y
  The entrance of the program is implemented here!
  Destination OutputFile: smallc.tab.c smallc.tab.h smallc.output
  This program is the source file for the syntax analyzer. And you must 
  use it together with smallc.l, which generates the lexical analyzer to
  analyzer the input file, otherwise it won't work.
  You can use it with any number of parameters when executing it.
  The parameters are the names of the files to be parsed.
  If the file does not exist, it will send an error message and continue
  to parse the next file.
  If you do not enter extra parameters, you can input the to-be-parsed
  file directly to the terminal, whereas strongly not recommanded.
  Since our first project is very simple and can only find the very first
  syntax error, the remaining not parsed lexemes(if you use "copy" command
  to paste the code into the terminal) will still appear on the terminal 
  even if the program ends, which will lead to a huge chaos.
*/
////////////////////////////////////////////////////////////////////////

#include "main.hpp"
////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
extern "C"{
	void yyerror(const char *s);
	extern int yylex(void);
	// void yyrestart(FILE*);
}

#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;


extern int linecount; // get the linecount
extern char* yytext;  // get the token, used for yyerror()

struct Node;
struct SymbolTable;
struct Intermediate;
class Instruction;
class Inter;

#ifndef PROGRAM_GLOBAL
#define PROGRAM_GLOBAL
Node* program_out;
SymbolTable* symbol_table;
vector<Inter*>* inters;
vector<Instruction*>* instrs;
#endif


#line 125 "smallc.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "smallc.tab.h".  */
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
#line 1 "smallc.y" /* yacc.c:355  */

#include "Info.h"
#include "Intermediate.h"
#include "GenIntermediate.h"
#include "MIPS32.h"


#line 163 "smallc.tab.c" /* yacc.c:355  */

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
#line 71 "smallc.y" /* yacc.c:355  */

	int mI_Int;
	std::string* mS_Id;
	std::vector<Node*>* mV_NodeVector;
	Node* node;
	struct Variable_ArrayDeclarationInfo* mV_Var_Arr_Dec_Info;
	std::vector<Variable_ArrayDeclarationInfo*>* mV_Var_Arr_Dec_Info_Vector;
	std::vector<std::string>* mV_StringVector;

#line 242 "smallc.tab.c" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 271 "smallc.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   342

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  192

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   119,   119,   125,   131,   136,   143,   147,   153,   158,
     163,   168,   173,   178,   183,   188,   193,   198,   202,   209,
     216,   221,   226,   231,   237,   241,   246,   249,   252,   256,
     260,   264,   268,   272,   276,   281,   288,   294,   300,   305,
     312,   317,   322,   329,   334,   339,   344,   351,   355,   361,
     365,   370,   371,   374,   378,   382,   386,   390,   394,   398,
     402,   406,   410,   414,   418,   422,   426,   430,   434,   438,
     442,   446,   450,   456,   462,   468,   474,   480,   486,   492,
     498,   504,   508,   512,   516,   520,   524,   527,   531,   535,
     539,   546,   550,   555,   559
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "SEMI", "COMMA", "TYPE",
  "STRUCT", "RETURN", "IF", "ELSE", "BREAK", "CONT", "FOR", "LC", "RC",
  "READ", "WRITE", "LOWER_THAN_ELSE", "ASSIGN", "PLUSASSIGN",
  "MINUSASSIGN", "MULASSIGN", "DIVASSIGN", "ANDASSIGN", "XORASSIGN",
  "ORASSIGN", "SHLASSIGN", "SHRASSIGN", "LOGICALOR", "LOGICALAND", "BITOR",
  "BITXOR", "BITAND", "ET", "NET", "GT", "GE", "LT", "LE", "SHL", "SHR",
  "PLUS", "MINUS", "MUL", "DIV", "MOD", "LOGICALNOT", "PREINC", "PREDEC",
  "BITNOT", "LP", "RP", "LB", "RB", "DOT", "$accept", "PROGRAM", "EXTDEFS",
  "EXTDEF", "SEXTVARS", "EXTVARS", "STSPEC", "FUNC", "PARAS", "STMTBLOCK",
  "STMTS", "STMT", "DEFS", "SDEFS", "SDECS", "DECS", "VAR", "INIT", "EXP",
  "EXPS", "ARRS", "ARGS", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311
};
# endif

#define YYPACT_NINF -175

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-175)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -175,     4,    92,  -175,    14,    -2,  -175,    16,   -18,    96,
      22,    15,    79,  -175,  -175,   105,    98,  -175,    99,  -175,
    -175,    89,   142,  -175,     7,  -175,   118,   128,    13,  -175,
      52,   110,  -175,    39,   117,   117,   117,   117,   117,   117,
     117,  -175,  -175,   212,    87,    10,   143,  -175,  -175,  -175,
     144,  -175,    89,    99,   143,    64,   117,   146,   133,  -175,
       9,  -175,  -175,  -175,  -175,  -175,   178,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,  -175,  -175,  -175,   119,   160,
    -175,   125,    55,   129,   117,    94,   183,   185,   140,  -175,
     174,   175,  -175,  -175,   186,    18,  -175,   117,   117,  -175,
    -175,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   139,   228,   243,   257,   270,   281,   281,   -14,   -14,
     -14,   -14,    43,    43,    51,    51,  -175,  -175,  -175,  -175,
     224,  -175,  -175,    99,    89,  -175,   225,   117,  -175,  -175,
     117,   117,   117,  -175,  -175,   274,  -175,  -175,    65,  -175,
    -175,   176,   325,   278,   279,  -175,    89,   145,   117,   328,
     329,  -175,   324,   331,  -175,  -175,   145,   117,  -175,   284,
     145,  -175
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    15,     0,     3,    10,    47,     0,
       0,    11,    18,    40,     8,     0,    22,     5,     0,    38,
       7,    52,     0,    40,     0,     6,     0,     0,     0,    47,
      13,    25,    90,    92,    52,     0,     0,     0,     0,     0,
       0,    12,    49,    51,     0,     0,     0,    17,     9,    21,
       0,    19,    52,     0,     0,    52,    52,     0,    88,    94,
       0,    81,    82,    84,    85,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    16,    42,     0,     0,
      14,     0,    43,     0,    52,     0,     0,     0,     0,    23,
       0,     0,    27,    24,     0,     0,    89,    52,    52,    50,
      86,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    70,    69,    68,    67,    66,    64,    65,    60,    61,
      62,    63,    58,    59,    56,    57,    53,    54,    55,    39,
       0,    20,    36,     0,    52,    37,     0,    52,    33,    32,
      52,    52,    52,    26,    87,     0,    93,    41,    44,    45,
      28,     0,     0,     0,     0,    91,    52,    52,    52,     0,
       0,    46,    29,     0,    34,    35,    52,    52,    30,     0,
      52,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -175,  -175,  -175,  -175,  -175,  -175,   307,  -175,  -175,   330,
    -175,  -174,  -175,   316,   287,  -175,   -17,   -47,   -34,   -29,
    -175,   286
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     6,    15,     9,     7,    10,    28,   112,
      55,   113,    31,    24,    98,   101,    11,    41,    42,    43,
      58,    60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,    30,    12,   182,     3,   100,    61,    62,    63,    64,
      65,    66,   188,    13,    46,   118,   191,    46,     8,    50,
      14,   114,    59,    47,   118,   119,    96,    88,    89,    90,
      91,    92,    93,    94,    16,    21,   102,    19,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,    51,    32,    33,    22,
     156,   164,    52,   104,   105,   154,   106,   107,   108,    19,
     109,   110,   111,   165,   166,   176,    90,    91,    92,    93,
      94,    56,    32,    33,    23,    57,    92,    93,    94,     4,
       5,    17,    18,    29,    34,    27,    22,   169,    35,    22,
      25,    26,    36,    37,    38,    39,    40,    53,     5,    22,
      32,    33,    48,   171,   149,   150,   172,   173,   174,   181,
     152,   153,    49,    35,   155,   150,   168,    36,    37,    38,
      39,    40,    95,   114,   183,    44,   157,    97,    32,    33,
     116,    99,   114,   189,   104,   105,   114,   106,   107,   108,
      19,    35,   110,   111,   151,    36,    37,    38,    39,    40,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,   117,   158,    35,
     159,   163,   160,    36,    37,    38,    39,    40,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,   161,   162,   167,   177,
     170,   120,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,   175,
     178,   179,   180,   184,   185,   186,   187,   190,    54,    45,
      20,   103,   115
};

static const yytype_uint8 yycheck[] =
{
      34,    18,     4,   177,     0,    52,    35,    36,    37,    38,
      39,    40,   186,    15,     7,     6,   190,     7,     4,     6,
       4,    55,    56,    16,     6,    16,    16,    41,    42,    43,
      44,    45,    46,    47,    52,    20,    53,    15,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    53,     3,     4,    54,
     104,    53,    20,     9,    10,    20,    12,    13,    14,    15,
      16,    17,    18,   117,   118,    20,    43,    44,    45,    46,
      47,    52,     3,     4,    15,    56,    45,    46,    47,     7,
       8,     5,     6,     4,    15,     7,    54,   154,    44,    54,
       5,     6,    48,    49,    50,    51,    52,     7,     8,    54,
       3,     4,     4,   157,     5,     6,   160,   161,   162,   176,
       5,     6,     4,    44,     5,     6,   153,    48,    49,    50,
      51,    52,    55,   177,   178,     3,    52,     4,     3,     4,
       4,     7,   186,   187,     9,    10,   190,    12,    13,    14,
      15,    44,    17,    18,     4,    48,    49,    50,    51,    52,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    54,     5,    44,
       5,     5,    52,    48,    49,    50,    51,    52,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    52,    52,     4,    53,
       5,    53,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    55,
       5,    53,    53,     5,     5,    11,     5,    53,    31,    23,
      10,    54,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    58,    59,     0,     7,     8,    60,    63,     4,    62,
      64,    73,     4,    15,     4,    61,    52,     5,     6,    15,
      66,    20,    54,    15,    70,     5,     6,     7,    65,     4,
      73,    69,     3,     4,    15,    44,    48,    49,    50,    51,
      52,    74,    75,    76,     3,    70,     7,    16,     4,     4,
       6,    53,    20,     7,    63,    67,    52,    56,    77,    75,
      78,    76,    76,    76,    76,    76,    76,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    55,    16,     4,    71,     7,
      74,    72,    73,    71,     9,    10,    12,    13,    14,    16,
      17,    18,    66,    68,    75,    78,     4,    54,     6,    16,
      53,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,     5,
       6,     4,     5,     6,    20,     5,    75,    52,     5,     5,
      52,    52,    52,     5,    53,    75,    75,     4,    73,    74,
       5,    75,    75,    75,    75,    55,    20,    53,     5,    53,
      53,    74,    68,    75,     5,     5,    11,     5,    68,    75,
      53,    68
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    60,    61,    61,
      61,    62,    62,    62,    62,    62,    63,    63,    63,    64,
      65,    65,    65,    66,    67,    67,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    69,    69,    69,    70,
      70,    71,    71,    72,    72,    72,    72,    73,    73,    74,
      74,    75,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    77,    78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     3,     3,     1,     3,
       0,     1,     3,     3,     5,     0,     5,     4,     2,     4,
       4,     2,     0,     4,     2,     0,     2,     1,     3,     5,
       7,     9,     2,     2,     5,     5,     4,     4,     0,     4,
       0,     3,     1,     1,     3,     3,     5,     1,     4,     1,
       3,     1,     0,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     2,     3,     4,     2,     3,
       1,     4,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 119 "smallc.y" /* yacc.c:1646  */
    {
								program_out = new Node((yyloc).first_line, Program);
								program_out->extern_declarations = (yyvsp[0].mV_NodeVector);
								}
#line 1610 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 125 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_NodeVector) = (yyvsp[-1].mV_NodeVector);
								if((yyvsp[0].node)!=NULL){
									(yyval.mV_NodeVector)->push_back((yyvsp[0].node));
								}
								}
#line 1621 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 131 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_NodeVector) = new vector<Node*>();					
								}
#line 1629 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 136 "smallc.y" /* yacc.c:1646  */
    {
								if((yyvsp[-1].mV_Var_Arr_Dec_Info_Vector)->size()==0) (yyval.node) = NULL;
								else {
									(yyval.node) = new Node((yyloc).first_line, Declaration);
									(yyval.node)->initial_Declaration_Global_Variable_Array((yyvsp[-1].mV_Var_Arr_Dec_Info_Vector));
								}
								}
#line 1641 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 143 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Declaration);
 								(yyval.node)->initial_Declaration_Global_Struct((yyvsp[-2].mV_StringVector), (yyvsp[-1].mV_StringVector));
 								}
#line 1650 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 147 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Function);
 								(yyval.node)->initial_Function((yyvsp[-1].mV_StringVector), (yyvsp[0].node));
 								}
#line 1659 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 153 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_StringVector) = new vector<string>();
								(yyval.mV_StringVector)->push_back(*(yyvsp[0].mS_Id));
								delete (yyvsp[0].mS_Id);
								}
#line 1669 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 158 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_StringVector) = (yyvsp[-2].mV_StringVector);
 								(yyval.mV_StringVector)->push_back(*(yyvsp[0].mS_Id));
 								delete (yyvsp[0].mS_Id);
 								}
#line 1679 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 163 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_StringVector) = new vector<string>();
								}
#line 1687 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 168 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_Var_Arr_Dec_Info_Vector) = new vector<Variable_ArrayDeclarationInfo*>();
								(yyvsp[0].mV_Var_Arr_Dec_Info)->mv_InitList = new vector<Node*>();
								(yyval.mV_Var_Arr_Dec_Info_Vector)->push_back((yyvsp[0].mV_Var_Arr_Dec_Info));
								}
#line 1697 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 173 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_Var_Arr_Dec_Info_Vector) = new vector<Variable_ArrayDeclarationInfo*>();
								(yyvsp[-2].mV_Var_Arr_Dec_Info)->mv_InitList = (yyvsp[0].mV_NodeVector);
								(yyval.mV_Var_Arr_Dec_Info_Vector)->push_back((yyvsp[-2].mV_Var_Arr_Dec_Info));
								}
#line 1707 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 178 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_Var_Arr_Dec_Info_Vector) = (yyvsp[-2].mV_Var_Arr_Dec_Info_Vector);
 								(yyvsp[0].mV_Var_Arr_Dec_Info)->mv_InitList = new vector<Node*>();
 								(yyval.mV_Var_Arr_Dec_Info_Vector)->push_back((yyvsp[0].mV_Var_Arr_Dec_Info));
								}
#line 1717 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 183 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_Var_Arr_Dec_Info_Vector) = (yyvsp[-4].mV_Var_Arr_Dec_Info_Vector);
 								(yyvsp[-2].mV_Var_Arr_Dec_Info)->mv_InitList = (yyvsp[0].mV_NodeVector);
 								(yyval.mV_Var_Arr_Dec_Info_Vector)->push_back((yyvsp[-2].mV_Var_Arr_Dec_Info));
								}
#line 1727 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 188 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_Var_Arr_Dec_Info_Vector) = new vector<Variable_ArrayDeclarationInfo*>();
							    }
#line 1735 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 193 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_StringVector) = (yyvsp[-1].mV_StringVector);
								(yyval.mV_StringVector)->push_back(*(yyvsp[-3].mS_Id));
								delete (yyvsp[-3].mS_Id);
								}
#line 1745 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 198 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_StringVector) = (yyvsp[-1].mV_StringVector);
 								(yyval.mV_StringVector)->push_back("#");
 								}
#line 1754 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 202 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_StringVector) = new vector<string>();
 								(yyval.mV_StringVector)->push_back(*(yyvsp[0].mS_Id));
 								delete (yyvsp[0].mS_Id);
 								}
#line 1764 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 209 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_StringVector) = (yyvsp[-1].mV_StringVector);
								(yyval.mV_StringVector)->push_back(*(yyvsp[-3].mS_Id));
								delete (yyvsp[-3].mS_Id);
								}
#line 1774 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 216 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_StringVector) = (yyvsp[-3].mV_StringVector);
								(yyval.mV_StringVector)->push_back(*(yyvsp[0].mS_Id));
								delete (yyvsp[0].mS_Id);
								}
#line 1784 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 221 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_StringVector) = new vector<string>();
 								(yyval.mV_StringVector)->push_back(*(yyvsp[0].mS_Id));
 								delete (yyvsp[0].mS_Id);
 								}
#line 1794 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 226 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_StringVector) = new vector<string>();
 								}
#line 1802 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 231 "smallc.y" /* yacc.c:1646  */
    {
											(yyval.node) = new Node((yyloc).first_line, Statement);
											(yyval.node)->initial_Statement_StmtBlock((yyvsp[-2].mV_NodeVector), (yyvsp[-1].mV_NodeVector));
											}
#line 1811 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 237 "smallc.y" /* yacc.c:1646  */
    {
											(yyval.mV_NodeVector) = (yyvsp[-1].mV_NodeVector);
											(yyval.mV_NodeVector)->push_back((yyvsp[0].node));
											}
#line 1820 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 241 "smallc.y" /* yacc.c:1646  */
    {
											(yyval.mV_NodeVector) = new vector<Node*>();
											}
#line 1828 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 246 "smallc.y" /* yacc.c:1646  */
    {
											(yyval.node) = (yyvsp[-1].node);
											}
#line 1836 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 249 "smallc.y" /* yacc.c:1646  */
    {
 											(yyval.node) = (yyvsp[0].node);
 											}
#line 1844 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 252 "smallc.y" /* yacc.c:1646  */
    {
 											(yyval.node) = new Node((yyloc).first_line, Statement);
 											(yyval.node)->initial_Statement_Return((yyvsp[-1].node));
 											}
#line 1853 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 256 "smallc.y" /* yacc.c:1646  */
    {
 											(yyval.node) = new Node((yyloc).first_line, Statement);
 											(yyval.node)->initial_Statement_If((yyvsp[-2].node), (yyvsp[0].node));
 											}
#line 1862 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 260 "smallc.y" /* yacc.c:1646  */
    {
 											(yyval.node) = new Node((yyloc).first_line, Statement);
 											(yyval.node)->initial_Statement_IfElse((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
 											}
#line 1871 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 264 "smallc.y" /* yacc.c:1646  */
    {
 											(yyval.node) = new Node((yyloc).first_line, Statement);
 											(yyval.node)->initial_Statement_For((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
 											}
#line 1880 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 268 "smallc.y" /* yacc.c:1646  */
    {
 											(yyval.node) = new Node((yyloc).first_line, Statement);
 											(yyval.node)->me_StatementType = Stmt_Continue;
 											}
#line 1889 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 272 "smallc.y" /* yacc.c:1646  */
    {
 											(yyval.node) = new Node((yyloc).first_line, Statement);
 											(yyval.node)->me_StatementType = Stmt_Break;
 											}
#line 1898 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 276 "smallc.y" /* yacc.c:1646  */
    {
 											(yyval.node) = new Node((yyloc).first_line, Statement);
 											(yyval.node)->me_StatementType = Stmt_Read;
 											(yyval.node)->io_Expression = (yyvsp[-2].node);
 											}
#line 1908 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 281 "smallc.y" /* yacc.c:1646  */
    {
											(yyval.node) = new Node((yyloc).first_line, Statement);
 											(yyval.node)->me_StatementType = Stmt_Write;
 											(yyval.node)->io_Expression = (yyvsp[-2].node);
 											}
#line 1918 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 288 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_NodeVector) = (yyvsp[-3].mV_NodeVector);
								Node* temp = new Node((yylsp[-2]).first_line,Declaration);
								temp->initial_Declaration_Local_Variable_Array((yyvsp[-1].mV_Var_Arr_Dec_Info_Vector));
								(yyval.mV_NodeVector)->push_back(temp);
								}
#line 1929 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 294 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_NodeVector) = (yyvsp[-3].mV_NodeVector);
 								Node* temp = new Node((yylsp[-2]).first_line, Declaration);
 								temp->initial_Declaration_Local_Struct((yyvsp[-2].mV_StringVector), (yyvsp[-1].mV_StringVector));
 								(yyval.mV_NodeVector)->push_back(temp);
 								}
#line 1940 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 300 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_NodeVector) = new vector<Node*>();
								}
#line 1948 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 305 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_StringVector) = (yyvsp[-3].mV_StringVector);
								for(int i=0; i<(yyvsp[-1].mV_StringVector)->size(); ++i){
									(yyvsp[-3].mV_StringVector)->push_back((*(yyvsp[-1].mV_StringVector))[i]);
								}
								delete (yyvsp[-1].mV_StringVector);
								}
#line 1960 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 312 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_StringVector) = new vector<string>();
								}
#line 1968 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 317 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_StringVector) = (yyvsp[-2].mV_StringVector);
								(yyval.mV_StringVector)->push_back(*(yyvsp[0].mS_Id));
								delete (yyvsp[0].mS_Id);
								}
#line 1978 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 322 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_StringVector) = new vector<string>();
 								(yyval.mV_StringVector)->push_back(*(yyvsp[0].mS_Id));
 								delete (yyvsp[0].mS_Id);
 								}
#line 1988 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 329 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_Var_Arr_Dec_Info_Vector) = new vector<Variable_ArrayDeclarationInfo*>();
								(yyvsp[0].mV_Var_Arr_Dec_Info)->mv_InitList = new vector<Node*>();
								(yyval.mV_Var_Arr_Dec_Info_Vector)->push_back((yyvsp[0].mV_Var_Arr_Dec_Info));
								}
#line 1998 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 334 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_Var_Arr_Dec_Info_Vector) = (yyvsp[-2].mV_Var_Arr_Dec_Info_Vector);
 								(yyvsp[0].mV_Var_Arr_Dec_Info)->mv_InitList = new vector<Node*>();
 								(yyval.mV_Var_Arr_Dec_Info_Vector)->push_back((yyvsp[0].mV_Var_Arr_Dec_Info));
								}
#line 2008 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 339 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_Var_Arr_Dec_Info_Vector) = new vector<Variable_ArrayDeclarationInfo*>();
								(yyvsp[-2].mV_Var_Arr_Dec_Info)->mv_InitList = (yyvsp[0].mV_NodeVector);
								(yyval.mV_Var_Arr_Dec_Info_Vector)->push_back((yyvsp[-2].mV_Var_Arr_Dec_Info));
								}
#line 2018 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 344 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_Var_Arr_Dec_Info_Vector) = (yyvsp[-4].mV_Var_Arr_Dec_Info_Vector);
 								(yyvsp[-2].mV_Var_Arr_Dec_Info)->mv_InitList = (yyvsp[0].mV_NodeVector);
 								(yyval.mV_Var_Arr_Dec_Info_Vector)->push_back((yyvsp[-2].mV_Var_Arr_Dec_Info));
								}
#line 2028 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 351 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_Var_Arr_Dec_Info) = new Variable_ArrayDeclarationInfo();
								(yyval.mV_Var_Arr_Dec_Info)->ms_Name = *(yyvsp[0].mS_Id); delete (yyvsp[0].mS_Id);
								}
#line 2037 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 355 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_Var_Arr_Dec_Info) = (yyvsp[-3].mV_Var_Arr_Dec_Info);
 								(yyval.mV_Var_Arr_Dec_Info)->mv_ArrayDeclarationSubscriptList.push_back((yyvsp[-1].mI_Int));
 								}
#line 2046 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 361 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_NodeVector) = new vector<Node*>();
								(yyval.mV_NodeVector)->push_back((yyvsp[0].node));
								}
#line 2055 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 365 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_NodeVector) = (yyvsp[-1].mV_NodeVector);
 								}
#line 2063 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 370 "smallc.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node);}
#line 2069 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 371 "smallc.y" /* yacc.c:1646  */
    { (yyval.node) = NULL;}
#line 2075 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 374 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
 								}
#line 2084 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 378 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
 								}
#line 2093 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 382 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_MOD, (yyvsp[0].node));
 								}
#line 2102 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 386 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_PLUS, (yyvsp[0].node));
 								}
#line 2111 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 390 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_MINUS, (yyvsp[0].node));
 								}
#line 2120 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 394 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_SHL, (yyvsp[0].node));
 								}
#line 2129 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 398 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_SHR, (yyvsp[0].node));
 								}
#line 2138 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 402 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_GT, (yyvsp[0].node));
 								}
#line 2147 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 406 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_GE, (yyvsp[0].node));
 								}
#line 2156 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 410 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_LT, (yyvsp[0].node));
 								}
#line 2165 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 414 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_LE, (yyvsp[0].node));
 								}
#line 2174 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 418 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_ET, (yyvsp[0].node));
 								}
#line 2183 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 422 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_NET, (yyvsp[0].node));
 								}
#line 2192 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 426 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_BITAND, (yyvsp[0].node));
 								}
#line 2201 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 430 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_BITXOR, (yyvsp[0].node));
 								}
#line 2210 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 434 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_BITOR, (yyvsp[0].node));
 								}
#line 2219 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 438 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_LOGICALAND, (yyvsp[0].node));
 								}
#line 2228 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 442 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
								(yyval.node)->initial_Expression_BinaryOp((yyvsp[-2].node), OP_LOGICALOR, (yyvsp[0].node));
 								}
#line 2237 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 446 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Assign((yyvsp[-2].node), (yyvsp[0].node));
 								}
#line 2246 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 450 "smallc.y" /* yacc.c:1646  */
    {
 								Node* temp = new Node((yyloc).first_line, Expression);
 								temp->initial_Expression_BinaryOp((yyvsp[-2].node), OP_PLUS, (yyvsp[0].node));
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Assign((yyvsp[-2].node), temp);
 								}
#line 2257 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 456 "smallc.y" /* yacc.c:1646  */
    {
 								Node* temp = new Node((yyloc).first_line, Expression);
 								temp->initial_Expression_BinaryOp((yyvsp[-2].node), OP_MINUS, (yyvsp[0].node));
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Assign((yyvsp[-2].node), temp);
 								}
#line 2268 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 462 "smallc.y" /* yacc.c:1646  */
    {
 								Node* temp = new Node((yyloc).first_line, Expression);
 								temp->initial_Expression_BinaryOp((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Assign((yyvsp[-2].node), temp); 	
 								}
#line 2279 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 468 "smallc.y" /* yacc.c:1646  */
    {
 								Node* temp = new Node((yyloc).first_line, Expression);
 								temp->initial_Expression_BinaryOp((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Assign((yyvsp[-2].node), temp);
 								}
#line 2290 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 474 "smallc.y" /* yacc.c:1646  */
    {
 								Node* temp = new Node((yyloc).first_line, Expression);
 								temp->initial_Expression_BinaryOp((yyvsp[-2].node), OP_BITAND, (yyvsp[0].node));
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Assign((yyvsp[-2].node), temp);
 								}
#line 2301 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 480 "smallc.y" /* yacc.c:1646  */
    {
 								Node* temp = new Node((yyloc).first_line, Expression);
 								temp->initial_Expression_BinaryOp((yyvsp[-2].node), OP_BITXOR, (yyvsp[0].node));
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Assign((yyvsp[-2].node), temp);
 								}
#line 2312 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 486 "smallc.y" /* yacc.c:1646  */
    {
 								Node* temp = new Node((yyloc).first_line, Expression);
 								temp->initial_Expression_BinaryOp((yyvsp[-2].node), OP_BITOR, (yyvsp[0].node));
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Assign((yyvsp[-2].node), temp);
 								}
#line 2323 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 492 "smallc.y" /* yacc.c:1646  */
    {
 								Node* temp = new Node((yyloc).first_line, Expression);
 								temp->initial_Expression_BinaryOp((yyvsp[-2].node), OP_SHL, (yyvsp[0].node));
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Assign((yyvsp[-2].node), temp);
 								}
#line 2334 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 498 "smallc.y" /* yacc.c:1646  */
    {
 								Node* temp = new Node((yyloc).first_line, Expression);
 								temp->initial_Expression_BinaryOp((yyvsp[-2].node), OP_SHR, (yyvsp[0].node));
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Assign((yyvsp[-2].node), temp);
 								}
#line 2345 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 504 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_UnaryOp(OP_MINUS, (yyvsp[0].node));
 								}
#line 2354 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 508 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_UnaryOp(OP_LOGICALNOT, (yyvsp[0].node));
 								}
#line 2363 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 512 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_UnaryOp(OP_BITNOT, (yyvsp[0].node));
 								}
#line 2372 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 516 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_UnaryAssign(OP_PREINC, (yyvsp[0].node));
 								}
#line 2381 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 520 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_UnaryAssign(OP_PREDEC, (yyvsp[0].node));
 								}
#line 2390 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 524 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = (yyvsp[-1].node);
 								}
#line 2398 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 527 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_FunctionCall((yyvsp[-3].mS_Id), (yyvsp[-1].mV_NodeVector));
 								}
#line 2407 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 531 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Variable_Array((yyvsp[-1].mS_Id), (yyvsp[0].mV_NodeVector));
 								}
#line 2416 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 535 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_StructMember((yyvsp[-2].mS_Id), (yyvsp[0].mS_Id));
 								}
#line 2425 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 539 "smallc.y" /* yacc.c:1646  */
    { 
 								(yyval.node) = new Node((yyloc).first_line, Expression);
 								(yyval.node)->initial_Expression_Int((yyvsp[0].mI_Int));
 								// cout << "Line: " << $$->mi_LineNum << " EXPS -> INT " << $$->mi_IntExpression_Val << endl;
 								}
#line 2435 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 546 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_NodeVector) = (yyvsp[-3].mV_NodeVector);
								(yyval.mV_NodeVector)->push_back((yyvsp[-1].node));
								}
#line 2444 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 550 "smallc.y" /* yacc.c:1646  */
    { 
								(yyval.mV_NodeVector) = new vector<Node*>();
								}
#line 2452 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 555 "smallc.y" /* yacc.c:1646  */
    {
								(yyval.mV_NodeVector) = (yyvsp[-2].mV_NodeVector);
								(yyvsp[-2].mV_NodeVector)->push_back((yyvsp[0].node));
								}
#line 2461 "smallc.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 559 "smallc.y" /* yacc.c:1646  */
    {
 								(yyval.mV_NodeVector) = new vector<Node*>();
 								if((yyvsp[0].node)!=NULL)(yyval.mV_NodeVector)->push_back((yyvsp[0].node));
 								}
#line 2470 "smallc.tab.c" /* yacc.c:1646  */
    break;


#line 2474 "smallc.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 564 "smallc.y" /* yacc.c:1906  */


// function to print the error message
void yyerror(const char *s)
{
	fprintf(stderr, "[line %d]: %s %s\n", yylloc.first_line, s, yytext);
}

int main(int argc, char **argv)
{
	int i;
	if(argc<2){ // input the to-be-parsed program via terminal, not recommanded.
		linecount = 1;
		yyparse();
		cout << "Parsing complete" << endl;
		return 0;
	}
	program_out = NULL;
	for(i=1; i<argc; ++i){ // input the to-be-parsed program via files
		FILE *f = fopen(argv[i], "r");
		if(!f){
			perror(argv[i]);
			continue;
		}
		printf("\n");
		linecount = 1;
		extern FILE* yyin;
		yyin = f;
		yyparse();
		cout << "FILE: " << argv[i] << " Parsing complete\n";
		fclose(f);	
	}
	if(program_out==NULL){
		cout << "Please check the syntax error before generating codes!" << endl;
		return 0;
	}
	inters = new vector<Inter*>();
	instrs = new vector<Instruction*>(); 
	if(!generate_intermediates(symbol_table, inters, program_out, instrs)){
		cout << "Semantic Error Exists" << endl;
		return 0;
	}
	else {
		cout << "Semantic Check Pass" << endl;
	}

	// Intermediate Code Print
	ofstream fout("InterCode");
	for(auto it = inters->begin(); it != inters->end(); ++it){
		fout << **it;
		delete (*it);
	}

	// MIPS32 Code Print
	ofstream ffout("MIPSCode.s");
	for(auto it = instrs->begin(); it != instrs->end(); ++it){
		ffout << **it;
		delete(*it);
	}

	return 0;
}

