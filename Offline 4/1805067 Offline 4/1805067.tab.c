/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "1805067.y"

#include<bits/stdc++.h>
#include "symbol_table.h"
#include "util.h"

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;

FILE *fp;
ofstream logout;
ofstream errout;
string asmFile;

extern int line_count;
extern int error_count;
SymbolTable symbolTable(30); // bucketsize = 30

int label_count=0;
int current_offset=0; 
int dataLine = 3;
int codeLine = 4;
string currFuncReturnType = "";
int funcVarCount = 0;
int funcParameterCount = 0;
stack<int> ifStack;
stack<int> whileStack;
stack<int> forStack;

string newLabel(string prefix) {
	return prefix + "_"+ to_string(label_count++);
}
string get_new_label(int* temp_label_count){
    string new_var_label = "@L_" + to_string(++(*temp_label_count));
    return new_var_label;
}
void yyerror(char *s)
{
	error_count++;
	printError(logout, line_count, "Syntax error");
	printError(errout, line_count, "Syntax error");
}


#line 118 "1805067.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "1805067.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_DO = 7,                         /* DO  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_CONTINUE = 9,                   /* CONTINUE  */
  YYSYMBOL_PRINTLN = 10,                   /* PRINTLN  */
  YYSYMBOL_INCOP = 11,                     /* INCOP  */
  YYSYMBOL_DECOP = 12,                     /* DECOP  */
  YYSYMBOL_ASSIGNOP = 13,                  /* ASSIGNOP  */
  YYSYMBOL_NOT = 14,                       /* NOT  */
  YYSYMBOL_LPAREN = 15,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 16,                    /* RPAREN  */
  YYSYMBOL_LCURL = 17,                     /* LCURL  */
  YYSYMBOL_RCURL = 18,                     /* RCURL  */
  YYSYMBOL_LTHIRD = 19,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 20,                    /* RTHIRD  */
  YYSYMBOL_COMMA = 21,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 22,                 /* SEMICOLON  */
  YYSYMBOL_ID = 23,                        /* ID  */
  YYSYMBOL_INT = 24,                       /* INT  */
  YYSYMBOL_FLOAT = 25,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 26,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 27,                      /* CHAR  */
  YYSYMBOL_VOID = 28,                      /* VOID  */
  YYSYMBOL_ADDOP = 29,                     /* ADDOP  */
  YYSYMBOL_MULOP = 30,                     /* MULOP  */
  YYSYMBOL_RELOP = 31,                     /* RELOP  */
  YYSYMBOL_LOGICOP = 32,                   /* LOGICOP  */
  YYSYMBOL_CONST_INT = 33,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 34,               /* CONST_FLOAT  */
  YYSYMBOL_CONST_CHAR = 35,                /* CONST_CHAR  */
  YYSYMBOL_LOWER_THAN_ELSE = 36,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_start = 38,                     /* start  */
  YYSYMBOL_39_1 = 39,                      /* $@1  */
  YYSYMBOL_program = 40,                   /* program  */
  YYSYMBOL_unit = 41,                      /* unit  */
  YYSYMBOL_func_declaration = 42,          /* func_declaration  */
  YYSYMBOL_func_definition = 43,           /* func_definition  */
  YYSYMBOL_44_2 = 44,                      /* $@2  */
  YYSYMBOL_45_3 = 45,                      /* $@3  */
  YYSYMBOL_parameter_list = 46,            /* parameter_list  */
  YYSYMBOL_compound_statement = 47,        /* compound_statement  */
  YYSYMBOL_var_declaration = 48,           /* var_declaration  */
  YYSYMBOL_type_specifier = 49,            /* type_specifier  */
  YYSYMBOL_declaration_list = 50,          /* declaration_list  */
  YYSYMBOL_statements = 51,                /* statements  */
  YYSYMBOL_statement = 52,                 /* statement  */
  YYSYMBOL_53_4 = 53,                      /* $@4  */
  YYSYMBOL_54_5 = 54,                      /* $@5  */
  YYSYMBOL_55_6 = 55,                      /* $@6  */
  YYSYMBOL_56_7 = 56,                      /* $@7  */
  YYSYMBOL_if_expression = 57,             /* if_expression  */
  YYSYMBOL_expression_statement = 58,      /* expression_statement  */
  YYSYMBOL_variable = 59,                  /* variable  */
  YYSYMBOL_expression = 60,                /* expression  */
  YYSYMBOL_logic_expression = 61,          /* logic_expression  */
  YYSYMBOL_rel_expression = 62,            /* rel_expression  */
  YYSYMBOL_simple_expression = 63,         /* simple_expression  */
  YYSYMBOL_term = 64,                      /* term  */
  YYSYMBOL_unary_expression = 65,          /* unary_expression  */
  YYSYMBOL_factor = 66,                    /* factor  */
  YYSYMBOL_argument_list = 67,             /* argument_list  */
  YYSYMBOL_arguments = 68                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   169

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  126

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    70,    83,    89,    98,   104,   110,   118,
     143,   168,   167,   263,   262,   353,   359,   365,   371,   380,
     390,   409,   474,   480,   487,   495,   502,   508,   514,   522,
     528,   536,   542,   549,   549,   558,   564,   577,   576,   595,
     602,   595,   620,   640,   658,   671,   677,   689,   725,   772,
     778,   842,   849,   893,   899,   943,   949,   976,   982,  1048,
    1064,  1085,  1093,  1120,  1176,  1182,  1191,  1198,  1243,  1284,
    1291,  1298,  1305
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "DO", "RETURN", "CONTINUE", "PRINTLN", "INCOP", "DECOP",
  "ASSIGNOP", "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD",
  "RTHIRD", "COMMA", "SEMICOLON", "ID", "INT", "FLOAT", "DOUBLE", "CHAR",
  "VOID", "ADDOP", "MULOP", "RELOP", "LOGICOP", "CONST_INT", "CONST_FLOAT",
  "CONST_CHAR", "LOWER_THAN_ELSE", "$accept", "start", "$@1", "program",
  "unit", "func_declaration", "func_definition", "$@2", "$@3",
  "parameter_list", "compound_statement", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement", "$@4",
  "$@5", "$@6", "$@7", "if_expression", "expression_statement", "variable",
  "expression", "logic_expression", "rel_expression", "simple_expression",
  "term", "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-70)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -70,    26,     3,   -70,   -70,   -70,   -70,     3,   -70,   -70,
     -70,   -70,     1,   -70,    18,    36,    -3,    -1,    17,   -70,
      37,    -5,    42,    44,    48,   -70,    52,    46,     3,   -70,
     -70,    45,    71,   -70,   -70,    52,    57,    55,    69,    72,
     -70,    27,    73,    27,    27,   -70,   -70,    24,    27,   -70,
     -70,   -70,    75,   103,   -70,    52,   135,   -70,    41,    70,
     -70,    78,   -12,    77,   -70,   -70,   -70,   -70,   -70,    27,
      68,    88,    90,    91,    51,   -70,    99,    27,    27,   -70,
      97,   -70,   -70,   -70,   115,   -70,   -70,    27,   -70,    27,
      27,    27,    27,   104,    68,    27,   -70,   106,   -70,   -70,
     107,   108,   110,   -70,   -70,   -70,    77,    95,   -70,   -70,
      27,   117,   112,   -70,    27,   -70,   135,   119,   -70,   -70,
     -70,   -70,   135,   135,   -70,   -70
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,    22,    23,    24,     3,     5,     7,
       8,     6,     0,     4,    27,     0,     0,     0,     0,    21,
      13,     0,    18,     0,    25,    10,     0,    11,     0,    17,
      28,     0,    33,    14,     9,     0,    16,     0,     0,     0,
      39,     0,     0,     0,     0,    20,    45,    47,     0,    65,
      66,    31,     0,    33,    29,     0,    33,    32,    62,     0,
      49,    51,    53,    55,    57,    61,    12,    15,    26,     0,
       0,     0,     0,     0,    62,    60,     0,    70,     0,    59,
      27,    19,    30,    34,    36,    67,    68,     0,    46,     0,
       0,     0,     0,     0,     0,     0,    43,     0,    64,    72,
       0,    69,     0,    37,    50,    52,    56,    54,    58,    44,
       0,     0,     0,    63,     0,    48,    33,     0,    40,    42,
      71,    38,    33,    33,    35,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   -70,   132,   -70,   -70,   -70,   -70,   -70,
     -25,    13,     7,   -70,   -70,   -50,   -70,   -70,   -70,   -70,
     -70,   -58,   -43,   -40,   -69,    53,    56,    54,   -41,   -70,
     -70,   -70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     7,     8,     9,    10,    35,    26,    21,
      33,    51,    52,    15,    53,    54,    55,   116,    71,   123,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
     100,   101
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      74,    72,    75,    82,    76,    74,    84,    79,    99,    12,
      66,    27,    94,    20,    12,    11,    28,    90,   104,    91,
      11,     4,     5,    22,    14,     6,     3,     4,     5,    93,
      83,     6,    23,    16,    74,    36,   110,    17,   102,    77,
      24,    43,    44,    78,    74,   120,    74,    74,    74,    74,
      47,   108,    85,    86,    87,   111,    48,    18,    19,    25,
      49,    50,    85,    86,    30,    29,   121,    31,    34,    32,
     117,    74,   124,   125,    38,    68,    39,    40,    37,    41,
      67,    42,    43,    44,    69,    43,    44,    70,    73,    45,
      46,    47,    88,    46,    47,     4,     5,    48,    80,     6,
      48,    49,    50,    95,    49,    50,    38,    92,    39,    40,
      89,    41,    96,    42,    97,    98,    17,    43,    44,   103,
     109,    81,   112,   113,    90,    46,    47,     4,     5,   114,
     115,     6,    48,   118,   119,   122,    49,    50,    38,    13,
      39,    40,   105,    41,   106,    42,     0,   107,     0,    43,
      44,     0,     0,     0,     0,     0,     0,    46,    47,     4,
       5,     0,     0,     6,    48,     0,     0,     0,    49,    50
};

static const yytype_int8 yycheck[] =
{
      43,    41,    43,    53,    44,    48,    56,    48,    77,     2,
      35,    16,    70,    16,     7,     2,    21,    29,    87,    31,
       7,    24,    25,    16,    23,    28,     0,    24,    25,    69,
      55,    28,    33,    15,    77,    28,    94,    19,    78,    15,
      23,    14,    15,    19,    87,   114,    89,    90,    91,    92,
      23,    92,    11,    12,    13,    95,    29,    21,    22,    22,
      33,    34,    11,    12,    20,    23,   116,    19,    22,    17,
     110,   114,   122,   123,     3,    20,     5,     6,    33,     8,
      23,    10,    14,    15,    15,    14,    15,    15,    15,    18,
      22,    23,    22,    22,    23,    24,    25,    29,    23,    28,
      29,    33,    34,    15,    33,    34,     3,    30,     5,     6,
      32,     8,    22,    10,    23,    16,    19,    14,    15,     4,
      16,    18,    16,    16,    29,    22,    23,    24,    25,    21,
      20,    28,    29,    16,    22,    16,    33,    34,     3,     7,
       5,     6,    89,     8,    90,    10,    -1,    91,    -1,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    -1,    -1,    -1,    33,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    38,    39,     0,    24,    25,    28,    40,    41,    42,
      43,    48,    49,    41,    23,    50,    15,    19,    21,    22,
      16,    46,    49,    33,    23,    22,    45,    16,    21,    23,
      20,    19,    17,    47,    22,    44,    49,    33,     3,     5,
       6,     8,    10,    14,    15,    18,    22,    23,    29,    33,
      34,    48,    49,    51,    52,    53,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    47,    23,    20,    15,
      15,    55,    60,    15,    59,    65,    60,    15,    19,    65,
      23,    18,    52,    47,    52,    11,    12,    13,    22,    32,
      29,    31,    30,    60,    58,    15,    22,    23,    16,    61,
      67,    68,    60,     4,    61,    62,    64,    63,    65,    16,
      58,    60,    16,    16,    21,    20,    54,    60,    16,    22,
      61,    52,    16,    56,    52,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    39,    38,    40,    40,    41,    41,    41,    42,
      42,    44,    43,    45,    43,    46,    46,    46,    46,    47,
      47,    48,    49,    49,    49,    50,    50,    50,    50,    51,
      51,    52,    52,    53,    52,    52,    52,    54,    52,    55,
      56,    52,    52,    52,    57,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    65,    66,    66,    66,    66,    66,    66,    66,    67,
      67,    68,    68
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     1,     6,
       5,     0,     7,     0,     6,     4,     3,     2,     1,     3,
       2,     3,     1,     1,     1,     3,     6,     1,     4,     1,
       2,     1,     1,     0,     2,     7,     2,     0,     5,     0,
       0,     7,     5,     3,     4,     1,     2,     1,     4,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     2,
       2,     1,     1,     4,     3,     1,     1,     2,     2,     1,
       0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 70 "1805067.y"
        {
		    initAsmFile(asmFile);
			dataLine = 3;
			codeLine = 4;
	}
#line 1272 "1805067.tab.c"
    break;

  case 3: /* start: $@1 program  */
#line 75 "1805067.y"
        {
		printNewlineInAsm(asmFile);
		printCharInAsm(asmFile);
		printIntegerInAsm(asmFile);
		printAsm(asmFile,"END MAIN");
	}
#line 1283 "1805067.tab.c"
    break;

  case 4: /* program: program unit  */
#line 84 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-1].symbolInfo)->getSymbolName() + "\n" + (yyvsp[0].symbolInfo)->getSymbolName(), "program");
		printRuleInLog(logout, line_count, "program : program unit");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1293 "1805067.tab.c"
    break;

  case 5: /* program: unit  */
#line 90 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "program : unit");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());

	}
#line 1304 "1805067.tab.c"
    break;

  case 6: /* unit: var_declaration  */
#line 99 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "unit : var_declaration");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1314 "1805067.tab.c"
    break;

  case 7: /* unit: func_declaration  */
#line 105 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "unit : func_declaration");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1324 "1805067.tab.c"
    break;

  case 8: /* unit: func_definition  */
#line 111 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "unit : func_definition");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1334 "1805067.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 119 "1805067.y"
        {
		currFuncReturnType  = (yyvsp[-5].symbolInfo)->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll((yyvsp[-4].symbolInfo)->getSymbolName());
		if(temp_func == nullptr) {	//function isn't declared yet
			vector<Parameter> parameter_list = extractParameterList((yyvsp[-2].symbolInfo)->getSymbolName());
			FunctionData* func_data = new FunctionData();
			vector<Parameter> declared_list = extractParameterList((yyvsp[-2].symbolInfo)->getSymbolName());
			func_data->setParameterList(declared_list);
			temp_func = new SymbolInfo((yyvsp[-4].symbolInfo)->getSymbolName(),"ID");
			temp_func->setDtype(currFuncReturnType);
			temp_func->setFunctionData(func_data);
			symbolTable.insert(temp_func);
			symbolTable.enterScope();
			symbolTable.exitScope();
		} else {	//multiple declaration
			error_count++;
			printError(errout, line_count, "Multiple declaration of " + (yyvsp[-4].symbolInfo)->getSymbolName());
			printError(logout, line_count, "Multiple declaration of " + (yyvsp[-4].symbolInfo)->getSymbolName());
		}
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-5].symbolInfo)->getSymbolName() + " " + (yyvsp[-4].symbolInfo)->getSymbolName() + "(" + (yyvsp[-2].symbolInfo)->getSymbolName() + ");", "func_declaration");
		(yyval.symbolInfo)->setDtype(currFuncReturnType);
		printRuleInLog(logout, line_count, "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1363 "1805067.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 144 "1805067.y"
        {
		string currFuncReturnType = (yyvsp[-4].symbolInfo)->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll((yyvsp[-3].symbolInfo)->getSymbolName());
		if(temp_func == nullptr) {	//function isn't declared yet
			FunctionData* func_data = new FunctionData();
			temp_func = new SymbolInfo((yyvsp[-3].symbolInfo)->getSymbolName(),"ID");
			temp_func->setDtype(currFuncReturnType);
			temp_func->setFunctionData(func_data);
			symbolTable.insert(temp_func);
			symbolTable.enterScope();
			symbolTable.exitScope();
		} else {	//multiple declaration
			error_count++;
			printError(errout, line_count, "Multiple declaration of " + (yyvsp[-3].symbolInfo)->getSymbolName());
			printError(logout, line_count, "Multiple declaration of " + (yyvsp[-3].symbolInfo)->getSymbolName());
		}
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-4].symbolInfo)->getSymbolName() + " " + (yyvsp[-3].symbolInfo)->getSymbolName() + "();", "func_declaration");
		(yyval.symbolInfo)->setDtype(currFuncReturnType);
		printRuleInLog(logout, line_count, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1389 "1805067.tab.c"
    break;

  case 11: /* $@2: %empty  */
#line 168 "1805067.y"
        {
		currFuncReturnType = (yyvsp[-4].symbolInfo)->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll((yyvsp[-3].symbolInfo)->getSymbolName());
		vector<Parameter> defined_list = extractParameterList((yyvsp[-1].symbolInfo)->getSymbolName());
		funcParameterCount = defined_list.size();
		if(temp_func == nullptr) {	//function ID isn't declared yet
			FunctionData* func_data = new FunctionData();
			func_data->setParameterList(defined_list);
			func_data->setDefined(true);
			temp_func = new SymbolInfo((yyvsp[-3].symbolInfo)->getSymbolName(),"ID");
			temp_func->setDtype(currFuncReturnType);
			temp_func->setFunctionData(func_data);
			symbolTable.insert(temp_func);
		} else { //function ID has been declared
			FunctionData* func_data = temp_func->getFunctionData();
			
			if(func_data == nullptr) {	//ID is not a function
				error_count++;
				printError(errout, line_count, "Multiple declaration of " + temp_func->getSymbolName());
				printError(logout, line_count, "Multiple declaration of " + temp_func->getSymbolName());
			} else if(func_data->isDefined()) {	//ID is a function and defined
				error_count++;
				printError(errout, line_count, "Redefinition of " + temp_func->getSymbolName());
				printError(logout, line_count, "Redefinition of " + temp_func->getSymbolName());
			} else {					
					vector<Parameter> declared_list = func_data->getParameterList();
					if(currFuncReturnType != temp_func->getDtype()){
						error_count++;
						printError(errout, line_count, "Return type mismatch with function declaration in function " + temp_func->getSymbolName());
						printError(logout, line_count, "Return type mismatch with function declaration in function " + temp_func->getSymbolName());
					}
					if(declared_list.size() != defined_list.size()) {
						error_count++;
						printError(errout, line_count, "Total number of arguments mismatch with declaration in function var" + temp_func->getSymbolName());
						printError(logout, line_count, "Total number of arguments mismatch with declaration in function var" + temp_func->getSymbolName());
					}
					
					int smaller_size = min(declared_list.size(),defined_list.size());
					for (int i = 0; i < smaller_size ; i++) {
						if (declared_list[i].getParameterType() != defined_list[i].getParameterType()) {
							error_count++;
							printError(errout, line_count, "Type mismatch with function declaration in function " + temp_func->getSymbolName());
							printError(logout, line_count, "Type mismatch with function declaration in function " + temp_func->getSymbolName());
						}
					}
					
			}
		}	
		symbolTable.enterScope();

		int paramListSize = defined_list.size();
		for(int i = 0; i < paramListSize; i++) {
			SymbolInfo* temp_symbol = new SymbolInfo(defined_list[i].getParameterName(), "ID");
			temp_symbol->setDtype(defined_list[i].getParameterType());
			int offset = paramListSize - i + 1;
			temp_symbol->setOffset(offset*2);
			if(!symbolTable.insert(temp_symbol)) {
				error_count++;
				printError(errout, line_count, "Multiple declaration of " + temp_symbol->getSymbolName() +" in parameter");
				printError(logout, line_count, "Multiple declaration of " + temp_symbol->getSymbolName() +" in parameter");
			}
		}
		string asmCode = "";
		asmCode += "\t"+(yyvsp[-3].symbolInfo)->getSymbolName()+"  PROC\n";
		asmCode += "\n";
		asmCode += "\t\tPUSH BP\n";
		asmCode += "\t\tMOV BP, SP\n";
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		// $$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "(" + $4->getSymbolName() + ")" + $6->getSymbolName(), "func_definition");
		// $$->setDtype(currFuncReturnType);
		// printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		// printCodeInLog(logout, $$->getSymbolName());
	}
#line 1468 "1805067.tab.c"
    break;

  case 12: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@2 compound_statement  */
#line 243 "1805067.y"
        {
		string exitLabel = newLabel("EXIT_"+(yyvsp[-5].symbolInfo)->getSymbolName());
		string asmCode = "";
		asmCode += "\t\t"+exitLabel+":\n";
		asmCode += "\t\tMOV SP, BP\n";
		asmCode += "\t\tPOP BP\n";
		asmCode += "\n";
		asmCode +="\t\tRET "+to_string(2*funcParameterCount)+"\n";
		asmCode += "\t"+(yyvsp[-5].symbolInfo)->getSymbolName()+" ENDP\n";
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		funcParameterCount = 0;
		funcVarCount = 0;

		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-6].symbolInfo)->getSymbolName() + " " + (yyvsp[-5].symbolInfo)->getSymbolName() + "(" + (yyvsp[-3].symbolInfo)->getSymbolName() + ")" + (yyvsp[0].symbolInfo)->getSymbolName(), "func_definition");
		(yyval.symbolInfo)->setDtype(currFuncReturnType);
		printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1492 "1805067.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 263 "1805067.y"
        {
		string currFuncReturnType = (yyvsp[-3].symbolInfo)->getSymbolName();
		SymbolInfo* temp_func = symbolTable.lookupAll((yyvsp[-2].symbolInfo)->getSymbolName());
		if(temp_func == nullptr) {	//function ID isn't declared yet
			FunctionData* func_data = new FunctionData();
			func_data->setDefined(true);
			temp_func = new SymbolInfo((yyvsp[-2].symbolInfo)->getSymbolName(),"ID");
			temp_func->setFunctionData(func_data);
			symbolTable.insert(temp_func);
		} else { //function ID has been declared
			FunctionData* func_data = temp_func->getFunctionData(); 	
			if(func_data == nullptr) {	//ID is not a function
				error_count++;
				printError(errout, line_count, "Multiple declaration of " + temp_func->getSymbolName()+", redeclared as function");
				printError(logout, line_count, "Multiple declaration of " + temp_func->getSymbolName()+", redeclared as function");
			} else {	//ID is a function
				if(func_data->isDefined()) { 
					error_count++;
					printError(errout, line_count, "Redefinition of  of " + temp_func->getSymbolName());
					printError(logout, line_count, "Redefinition of  of " + temp_func->getSymbolName());
				} else {
					vector<Parameter> declared_list = func_data->getParameterList();
					//bool error_flag = false;
					if(declared_list.size() != 0) {
						error_count++;
						//error_flag = true;
						printError(errout, line_count, "Total number of arguments mismatch with declaration in function var" + temp_func->getSymbolName());
						printError(logout, line_count, "Total number of arguments mismatch with declaration in function var" + temp_func->getSymbolName());
					}
					
					if(currFuncReturnType != temp_func->getDtype()) {
						//error_flag = true;
						error_count++;
						printError(errout, line_count, "Return type mismatch with function declaration in function " + temp_func->getSymbolName());
						printError(logout, line_count, "Return type mismatch with function declaration in function " + temp_func->getSymbolName());
					}

					// if(!error_flag) {
					// 	//symbolTable.enterScope();
					// }
				}
			}
			
		}
		string asmCode = "";
		asmCode += "\t"+(yyvsp[-2].symbolInfo)->getSymbolName()+"  PROC\n";
		asmCode += "\n";
		if((yyvsp[-2].symbolInfo)->getSymbolName()=="main") {
			asmCode += "\t\tMOV AX, @DATA\n";
			asmCode += "\t\tMOV DS, AX\n";
		} else {
			asmCode += "\t\tPUSH BP\n";
			asmCode += "\t\tMOV BP, SP\n";
		}
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		symbolTable.enterScope();
		// $$ = new SymbolInfo($1->getSymbolName() + " " + $2->getSymbolName() + "()" + $5->getSymbolName(), "func_definition");
		// $$->setDtype(currFuncReturnType);
		// printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN RPAREN compound_statement");
		// printCodeInLog(logout, $$->getSymbolName());
		
	}
#line 1560 "1805067.tab.c"
    break;

  case 14: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement  */
#line 327 "1805067.y"
        {
		string exitLabel = newLabel("EXIT_"+(yyvsp[-4].symbolInfo)->getSymbolName());
		string asmCode = "";
		asmCode += "\t\t"+exitLabel+":\n";
		if((yyvsp[-4].symbolInfo)->getSymbolName()=="main") {
				asmCode += "\t\tMOV AH, 4CH\n";
				asmCode += "\t\tINT 21H\n";
				asmCode += "\n";
		} else {
				asmCode += "\t\tMOV SP, BP\n";
				asmCode += "\t\tPOP BP\n";
				asmCode += "\n";
				asmCode +="\t\tRET\n";
		}
		asmCode += "\t"+(yyvsp[-4].symbolInfo)->getSymbolName()+" ENDP\n";
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		funcVarCount = 0;

		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-5].symbolInfo)->getSymbolName() + " " + (yyvsp[-4].symbolInfo)->getSymbolName() + "()" + (yyvsp[0].symbolInfo)->getSymbolName(), "func_definition");
		(yyval.symbolInfo)->setDtype(currFuncReturnType);
		printRuleInLog(logout, line_count, "func_definition : type_specifier ID LPAREN RPAREN compound_statement");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1589 "1805067.tab.c"
    break;

  case 15: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 354 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-3].symbolInfo)->getSymbolName() + "," + (yyvsp[-1].symbolInfo)->getSymbolName() + " " + (yyvsp[0].symbolInfo)->getSymbolName(), "parameter_list");
		printRuleInLog(logout, line_count, "parameter_list : parameter_list COMMA type_specifier ID");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1599 "1805067.tab.c"
    break;

  case 16: /* parameter_list: parameter_list COMMA type_specifier  */
#line 360 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getSymbolName() + "," + (yyvsp[0].symbolInfo)->getSymbolName(), "parameter_list");
		printRuleInLog(logout, line_count, "parameter_list : parameter_list COMMA type_specifier");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1609 "1805067.tab.c"
    break;

  case 17: /* parameter_list: type_specifier ID  */
#line 366 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-1].symbolInfo)->getSymbolName() + " " + (yyvsp[0].symbolInfo)->getSymbolName(), "parameter_list");
		printRuleInLog(logout, line_count, "parameter_list : type_specifier ID");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1619 "1805067.tab.c"
    break;

  case 18: /* parameter_list: type_specifier  */
#line 372 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[0].symbolInfo)->getSymbolName(), "parameter_list");
		printRuleInLog(logout, line_count, "parameter_list : type_specifier");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1629 "1805067.tab.c"
    break;

  case 19: /* compound_statement: LCURL statements RCURL  */
#line 381 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo("{\n" + (yyvsp[-1].symbolInfo)->getSymbolName() + "\n}", "compound_statement");
		printRuleInLog(logout, line_count, "compound_statement : LCURL statements RCURL");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
		cout<<"print from compound statement\n";
		//symbolTable.printAllScopeTable();
		symbolTable.printAllScopeTable(logout);
		symbolTable.exitScope();
	}
#line 1643 "1805067.tab.c"
    break;

  case 20: /* compound_statement: LCURL RCURL  */
#line 391 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo("{}", "compound_statement");
		printRuleInLog(logout, line_count, "compound_statement : LCURL RCURL");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
		cout<<"print from compound statement\n";
		//symbolTable.printAllScopeTable();
		symbolTable.printAllScopeTable(logout);
		symbolTable.exitScope();
		cout<<"print from compound statement end\n";
	}
#line 1658 "1805067.tab.c"
    break;

  case 21: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 410 "1805067.y"
        {
		string varType = (yyvsp[-2].symbolInfo)->getSymbolName();
		if (varType == "void") {
			error_count++;
			printError(errout, line_count, "Variable type cannot be void");
			printError(logout, line_count, "Variable type cannot be void");
		} else{
			vector<string> varList = split((yyvsp[-1].symbolInfo)->getSymbolName(), ',');
			for (string var: varList) {
				SymbolInfo* temp = new SymbolInfo();
				int tempVarSize = 0;
				if (isArray(var)) {
					string varName = extractArrayName(var);
					temp->setSymbolName(varName);
					temp->setSymbolType("ID");
					int size = extractArraySize(var);
					ArrayData* arrayData = new ArrayData(size);
					temp->setDtype(varType);
					temp->setArrayData(arrayData);
					tempVarSize = size;
		 		} else {
						temp = new SymbolInfo(var, "ID");
						temp->setDtype(varType);
				}
				bool flag = symbolTable.insert(temp);
				if (!flag) {
					error_count++;
					printError(errout, line_count, "Multiple declaration of " + temp->getSymbolName());
					printError(logout, line_count, "Multiple declaration of " + temp->getSymbolName());
				}

				//added in offline 4
				string asmCode = "";
				if (symbolTable.getCurrentScopeId() == "1") { // global variable
					if(tempVarSize == 0) {
						asmCode += "\t" + var +" DW ? ;declared globally at line "+ to_string(line_count);
					} else { //array
						asmCode += "\t" + var +" DW " + to_string(tempVarSize) + " DUP(?) ;declared globally at line "+ to_string(line_count);
					}
					printAtLineNo(asmFile, asmCode, dataLine);
					dataLine++;
				} else {
					if(tempVarSize == 0) {
						funcVarCount++;

						temp->setOffset(funcVarCount*(-2));
						asmCode += "\t\tSUB SP, 2 ;line no: " + to_string(line_count) + " " + var + " declared\n";
					} else {	//array
						funcVarCount += tempVarSize;
						temp->setOffset(funcVarCount*(-2));
						asmCode += "\t\tSUB SP, " + to_string(funcVarCount*2) +" ;line no: " + to_string(line_count) + " " + var + " declared\n";
					}
					printAsm(asmFile, asmCode);
				}

			}
		}
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getSymbolName() + " " + (yyvsp[-1].symbolInfo)->getSymbolName() + ";", "var_declaration");
		(yyval.symbolInfo)->setDtype((yyvsp[-2].symbolInfo)->getSymbolName());
		printRuleInLog(logout, line_count, "var_declaration : type_specifier declaration_list SEMICOLON");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1725 "1805067.tab.c"
    break;

  case 22: /* type_specifier: INT  */
#line 475 "1805067.y"
        {
		(yyval.symbolInfo)= new SymbolInfo("int","INT");
		printRuleInLog(logout, line_count, "type_specifier : INT");	
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1735 "1805067.tab.c"
    break;

  case 23: /* type_specifier: FLOAT  */
#line 481 "1805067.y"
        {
		(yyval.symbolInfo)= new SymbolInfo("float","FLOAT");
		printRuleInLog(logout, line_count, "type_specifier : FLOAT");			
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());

	}
#line 1746 "1805067.tab.c"
    break;

  case 24: /* type_specifier: VOID  */
#line 488 "1805067.y"
        {
		(yyval.symbolInfo)= new SymbolInfo("void","VOID");
		printRuleInLog(logout, line_count, "type_specifier : VOID");		
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1756 "1805067.tab.c"
    break;

  case 25: /* declaration_list: declaration_list COMMA ID  */
#line 496 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getSymbolName() + "," + (yyvsp[0].symbolInfo)->getSymbolName(), "declaration_list");
		printRuleInLog(logout, line_count, "declaration_list : declaration_list COMMA ID");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());

	}
#line 1767 "1805067.tab.c"
    break;

  case 26: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 503 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-5].symbolInfo)->getSymbolName() + "," + (yyvsp[-3].symbolInfo)->getSymbolName() + "[" + (yyvsp[-1].symbolInfo)->getSymbolName() + "]", "declaration_list");
		printRuleInLog(logout, line_count, "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1777 "1805067.tab.c"
    break;

  case 27: /* declaration_list: ID  */
#line 509 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "declaration_list : ID");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1787 "1805067.tab.c"
    break;

  case 28: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 515 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-3].symbolInfo)->getSymbolName() + "[" + (yyvsp[-1].symbolInfo)->getSymbolName() + "]", "declaration_list");
		printRuleInLog(logout, line_count, "declaration_list : ID LTHIRD CONST_INT RTHIRD");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1797 "1805067.tab.c"
    break;

  case 29: /* statements: statement  */
#line 523 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "statements : statement");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1807 "1805067.tab.c"
    break;

  case 30: /* statements: statements statement  */
#line 529 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-1].symbolInfo)->getSymbolName() + "\n" + (yyvsp[0].symbolInfo)->getSymbolName(), "statements");
		printRuleInLog(logout, line_count, "statements : statements statement");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1817 "1805067.tab.c"
    break;

  case 31: /* statement: var_declaration  */
#line 537 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "statement : var_declaration");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1827 "1805067.tab.c"
    break;

  case 32: /* statement: expression_statement  */
#line 543 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "statement : expression_statement");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1837 "1805067.tab.c"
    break;

  case 33: /* $@4: %empty  */
#line 549 "1805067.y"
        {
		symbolTable.enterScope();
	}
#line 1845 "1805067.tab.c"
    break;

  case 34: /* statement: $@4 compound_statement  */
#line 553 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo); 	//$$ = $2;
		printRuleInLog(logout, line_count, "statement : compound_statement");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1855 "1805067.tab.c"
    break;

  case 35: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 559 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo("for (" + (yyvsp[-4].symbolInfo)->getSymbolName() + (yyvsp[-3].symbolInfo)->getSymbolName() + (yyvsp[-2].symbolInfo)->getSymbolName() + ")" + (yyvsp[0].symbolInfo)->getSymbolName(), "statement");
		printRuleInLog(logout, line_count, "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1865 "1805067.tab.c"
    break;

  case 36: /* statement: if_expression statement  */
#line 565 "1805067.y"
        {
		string elseLabel = "ELSE_LABEL_"+to_string(ifStack.top());
		string asmCode = "\t\t"+elseLabel+":\n";
		asmCode += "\t\t;line no "+ to_string(line_count)+" :End of If block\n\n"; 
		printAsm(asmFile,asmCode);
		ifStack.pop();

		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-1].symbolInfo)->getSymbolName()+(yyvsp[0].symbolInfo)->getSymbolName(), "statement");
		printRuleInLog(logout, line_count, "statement : IF LPAREN expression RPAREN statement");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1881 "1805067.tab.c"
    break;

  case 37: /* $@5: %empty  */
#line 577 "1805067.y"
        {
		string asmCode;
		string exitLabel = "END_IF_"+to_string(ifStack.top());
		asmCode += "\t\tJMP "+exitLabel+"\n";
		string elseLabel = "ELSE_LABEL_"+to_string(ifStack.top());
		asmCode += "\t\t"+elseLabel+":\n";
		printAsm(asmFile,asmCode);
	}
#line 1894 "1805067.tab.c"
    break;

  case 38: /* statement: if_expression statement ELSE $@5 statement  */
#line 584 "1805067.y"
                    {
		string exitLabel = "END_IF_"+to_string(ifStack.top());
		string asmCode = "\t\t"+exitLabel+":\n";
		asmCode += "\t\t;line no "+ to_string(line_count)+" :End of If Else block\n\n";
		printAsm(asmFile,asmCode);
		ifStack.pop();

		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-4].symbolInfo)->getSymbolName()+(yyvsp[-3].symbolInfo)->getSymbolName()+"else\n"+(yyvsp[0].symbolInfo)->getSymbolName(), "statement");
		printRuleInLog(logout, line_count, "statement : IF LPAREN expression RPAREN statement ELSE statement");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1910 "1805067.tab.c"
    break;

  case 39: /* $@6: %empty  */
#line 595 "1805067.y"
                {
		whileStack.push(label_count);
		string whileStart = "WHILE_START_LABEL_"+label_count;
		label_count++;
		string asmCode = "";
		asmCode += "\t\t"+whileStart+":\n\n";
		printAsm(asmFile,asmCode);
	}
#line 1923 "1805067.tab.c"
    break;

  case 40: /* $@7: %empty  */
#line 602 "1805067.y"
                                   {
		string whileEnd = "WHILE_END_LABEL_"+whileStack.top();
		string asmCode = "";
		asmCode += "\t\tPOP BX \n"; 
		asmCode += "\t\tCMP BX, 0 \n";
		asmCode += "\t\tJE "+whileEnd+" \n\n";
		printAsm(asmFile,asmCode);
	}
#line 1936 "1805067.tab.c"
    break;

  case 41: /* statement: WHILE $@6 LPAREN expression RPAREN $@7 statement  */
#line 609 "1805067.y"
                    {
		string whileStart = "WHILE_START_LABEL_"+whileStack.top();
		string asmCode = "";
		asmCode += "\t\tJMP "+whileStart+"\n";
		string whileEnd = "WHILE_END_LABEL_"+whileStack.top();
		asmCode += "\t\t"+whileEnd+":\n\n";
		printAsm(asmFile,asmCode);
		(yyval.symbolInfo) = new SymbolInfo("while("+(yyvsp[-3].symbolInfo)->getSymbolName()+")"+(yyvsp[0].symbolInfo)->getSymbolName(), "statement");
		printRuleInLog(logout, line_count, "statement : WHILE LPAREN expression RPAREN statement");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1952 "1805067.tab.c"
    break;

  case 42: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 621 "1805067.y"
        {
		SymbolInfo* temp = symbolTable.lookupAll((yyvsp[-2].symbolInfo)->getSymbolName());
		if(temp == nullptr) {
			error_count++;
			printError(errout, line_count, "Undeclared variable " + (yyvsp[-2].symbolInfo)->getSymbolName());
			printError(logout, line_count, "Undeclared variable " + (yyvsp[-2].symbolInfo)->getSymbolName());
		}
		string asmCode = "";
		if (temp->getOffset() == 0){ 	//came across a global variable
			asmCode += "\t\tPUSH "+temp->getSymbolName()+" \t;line no "+ to_string(line_count) +": "+temp->getSymbolName() +" is pushed for print\n";
		} else { 		//came across a local variable
			asmCode += "\t\tPUSH [BP + " + to_string(temp->getOffset()) +"] \t;line no "+ to_string(line_count) +": "+temp->getSymbolName() +" is pushed for print\n";
		}
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		(yyval.symbolInfo) = new SymbolInfo("printf(" + (yyvsp[-2].symbolInfo)->getSymbolName() + ");", "statement");
		printRuleInLog(logout, line_count, "statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1976 "1805067.tab.c"
    break;

  case 43: /* statement: RETURN expression SEMICOLON  */
#line 641 "1805067.y"
        {
		if (currFuncReturnType == "void") {
			error_count++;
			printError(errout,line_count, "void function used in expression");
			printError(logout,line_count, "void function used in expression");
		} 
		string asmCode = "";
		asmCode += "\t\tPOP BX \t;line no "+to_string(line_count)+" :  return value saved in DX \n";
		asmCode += "\t\tMOV DX, BX\n";
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		(yyval.symbolInfo) = new SymbolInfo("return " + (yyvsp[-1].symbolInfo)->getSymbolName() + ";", "statement");
		(yyval.symbolInfo)->setDtype((yyvsp[-1].symbolInfo)->getDtype());
		printRuleInLog(logout, line_count, "statement : RETURN expression SEMICOLON");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 1997 "1805067.tab.c"
    break;

  case 44: /* if_expression: IF LPAREN expression RPAREN  */
#line 659 "1805067.y"
        {
		string asmCode = "";
		ifStack.push(label_count);
		string elseLabel = "ELSE_LABEL_"+to_string(ifStack.top());
		label_count++;
		asmCode += "\t\t;line no "+ to_string(line_count)+" : If block\n"; 
		asmCode += "\t\tPOP BX \n"; 
		asmCode += "\t\tCMP BX, 0 \n";
		asmCode += "\t\tJE "+elseLabel+" \n\n";
		printAsm(asmFile,asmCode);
		(yyval.symbolInfo)= new SymbolInfo("if ("+(yyvsp[-1].symbolInfo)->getSymbolName()+") ", "statement");
	}
#line 2014 "1805067.tab.c"
    break;

  case 45: /* expression_statement: SEMICOLON  */
#line 672 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo(";", "expression_statement");
		printRuleInLog(logout, line_count, "expression_statement : SEMICOLON");
		printCodeInLog(logout, ";");
	}
#line 2024 "1805067.tab.c"
    break;

  case 46: /* expression_statement: expression SEMICOLON  */
#line 678 "1805067.y"
        {
		//added in offline 4
		string asmCode = "\t\tPOP BX; line no "+ to_string(line_count) +": ; previously pushed value on stack is removed\n\n";
		printAsm(asmFile, asmCode);
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-1].symbolInfo)->getSymbolName() + ";", "expression_statement");
		(yyval.symbolInfo)->setDtype((yyvsp[-1].symbolInfo)->getDtype());
		printRuleInLog(logout, line_count, "expression_statement : expression SEMICOLON");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2038 "1805067.tab.c"
    break;

  case 47: /* variable: ID  */
#line 690 "1805067.y"
        {
		
		SymbolInfo* temp = symbolTable.lookupAll((yyvsp[0].symbolInfo)->getSymbolName());
		if(temp == nullptr) {
			error_count++;
			printError(errout, line_count, "Undeclared variable " + (yyvsp[0].symbolInfo)->getSymbolName());
			printError(logout, line_count, "Undeclared variable " + (yyvsp[0].symbolInfo)->getSymbolName());
		} else {
			if (temp->getArrayData() == nullptr) { // if it is not an array do nothing
				
			} else {	// if it is an array
				error_count++;
				printError(errout, line_count, "Type mismatch, " + temp->getSymbolName() + " is an array");
				printError(logout, line_count, "Type mismatch, " + temp->getSymbolName() + " is an array");
			}
		}
		//added in offline 4
		string asmCode = "";
		if (temp->getOffset() == 0){ 	//came across a global variable
			asmCode += "\t\tMOV BX, "+temp->getSymbolName()+"\n";
			asmCode += "\t\tPUSH BX; line no "+ to_string(line_count) +": "+temp->getSymbolName() +" loaded\n";
			asmCode += "\n";
		} else { 		//came across a local variable
			asmCode += "\t\tMOV BX, [BP + " + to_string(temp->getOffset()) +"] \n";
			asmCode += "\t\tPUSH BX; line no "+ to_string(line_count) +": "+temp->getSymbolName() +" loaded\n";
			asmCode += "\n";
		}
		printAsm(asmFile, asmCode);

		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		(yyval.symbolInfo)->setDtype((yyvsp[0].symbolInfo)->getDtype());
		printRuleInLog(logout, line_count, "variable : ID");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
		
	}
#line 2078 "1805067.tab.c"
    break;

  case 48: /* variable: ID LTHIRD expression RTHIRD  */
#line 726 "1805067.y"
        {
		SymbolInfo* temp = symbolTable.lookupAll((yyvsp[-3].symbolInfo)->getSymbolName());
		string asmCode = "";
		if(temp == nullptr) {
			error_count++;
			printError(errout, line_count, "Undeclared variable " + (yyvsp[-3].symbolInfo)->getSymbolName());
			printError(logout, line_count, "Undeclared variable " + (yyvsp[-3].symbolInfo)->getSymbolName());
		} else {
			if (temp->getArrayData() == nullptr) { // if it is not an array
				error_count++;
				printError(errout, line_count, "Type mismatch, " + temp->getSymbolName() + " is not an array");
				printError(logout, line_count, "Type mismatch, " + temp->getSymbolName() + " is not an array");
			} else {	// if it is an array
				if ((yyvsp[-1].symbolInfo)->getDtype() != "int") {
					error_count++;
					printError(errout, line_count, "Expression inside third brackets not an integer");
					printError(logout, line_count, "Expression inside third brackets not an integer");
				} else { //added in offline 4
					
					asmCode += "\t\tPOP BX \t;Array index in BX.\n";
					asmCode += "\t\tSHL BX, 1\t \t;because 2 byte element.\n";
					
					if(temp->getOffset() == 0){ 	// global array
						asmCode += "\t\tPUSH "+ temp->getSymbolName()+"[BX] \t;pushing the value of the array at index "+ (yyvsp[-1].symbolInfo)->getSymbolName()+" \n";
						asmCode += "\t\tPUSH BX \t;index pushed to stack\n";
						asmCode += "\n";
					} else { 		// local array
						asmCode += "\t\tNEG BX\n";
						asmCode += "\t\tADD BX, " + to_string(temp->getOffset()) + " \t;Array from BP/or data segment\n";
						asmCode += "\t\tADD BX, BP \n";
						asmCode += "\t\tPUSH [BX] \t;pushing the value of the array at index "+ (yyvsp[-1].symbolInfo)->getSymbolName()+" \n";
						asmCode += "\t\tPUSH BX \t;index pushed to stack\n";
						asmCode += "\n";
					}
					printAsm(asmFile,asmCode);
				}
			}
		}
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-3].symbolInfo)->getSymbolName() + "[" + (yyvsp[-1].symbolInfo)->getSymbolName() + "]","variable");
		(yyval.symbolInfo)->setDtype((yyvsp[-3].symbolInfo)->getDtype());
		printRuleInLog(logout, line_count, "variable : ID LTHIRD expression RTHIRD");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
								
	}
#line 2127 "1805067.tab.c"
    break;

  case 49: /* expression: logic_expression  */
#line 773 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "expression : logic_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2137 "1805067.tab.c"
    break;

  case 50: /* expression: variable ASSIGNOP logic_expression  */
#line 779 "1805067.y"
        {
		string left_operand = (yyvsp[-2].symbolInfo)->getDtype();
		string right_operand = (yyvsp[0].symbolInfo)->getDtype();
		if((yyvsp[-2].symbolInfo)->getDtype()=="" || (yyvsp[0].symbolInfo)->getDtype()=="") {
			
		} else if(left_operand != right_operand) {
            if((yyvsp[-2].symbolInfo)->getDtype()=="void" || (yyvsp[0].symbolInfo)->getDtype()=="void") {
				//DO NOTHING, AS IT HAS BEEN HANDLED
			} else if(left_operand == "float" && right_operand == "int") {
					
			} else {
				error_count++;
				printError(errout, line_count,  "Type mismatch");
				printError(logout, line_count,  "Type mismatch");
			}
        }

		//added in offline 4;
		string varName = (yyvsp[-2].symbolInfo)->getSymbolName();
		if(isArray((yyvsp[-2].symbolInfo)->getSymbolName())) {
			varName = extractArrayName((yyvsp[-2].symbolInfo)->getSymbolName());
		}
		SymbolInfo* temp = symbolTable.lookupAll(varName);
		string asmCode = "";
		if (temp->getArrayData() == nullptr) { 
			asmCode += "\t\tPOP AX \t;retrieves right operand\n";
			asmCode += "\t\tPOP BX \t;retrieves left operand\n";
			 
			if(temp->getOffset() == 0){ 	// global variable
				asmCode += "\t\tMOV "+ temp->getSymbolName() +", AX; line no "+ to_string(line_count) +": "+temp->getSymbolName()+" assigned \n";
				asmCode += "\t\tMOV BX, AX ;not needed probably\n ";
				asmCode += "\t\tPUSH BX\n";
			} else { 		// local variable
				asmCode += "\t\tMOV [BP + " + to_string(temp->getOffset()) +"], AX; line no "+ to_string(line_count) +": "+temp->getSymbolName()+" assigned \n";
				asmCode += "\t\tMOV BX, AX ;not needed probably\n ";
				asmCode += "\t\tPUSH BX\n";
			}
			
		} else { //left operand array
			asmCode += "\t\tPOP AX \t;retrieves right operand\n";
			asmCode += "\t\tPOP BX \t;retrieves left operand index\n";
			asmCode += "\t\tPOP DX \t;retrieves array value in left\n";
			if (temp->getOffset() == 0){ 	//global array
				asmCode += "\t\tMOV "+temp->getSymbolName()+"[BX], AX \t;line no "+to_string(line_count) +": "+temp->getSymbolName()+" assigned \n";
				asmCode += "\t\tMOV BX, AX \n";
				asmCode += "\t\tPUSH BX";
				
			} else { 		//local array
				asmCode += "\t\tMOV [BX], AX \t;line no "+to_string(line_count) +": "+temp->getSymbolName()+" assigned \n";
				asmCode += "\t\tMOV BX, AX \n";
				asmCode += "\t\tPUSH BX\n";
			}
		}
		asmCode += "\n";
		printAsm(asmFile, asmCode);

		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getSymbolName() + "=" + (yyvsp[0].symbolInfo)->getSymbolName(), "expression");
		(yyval.symbolInfo)->setDtype((yyvsp[-2].symbolInfo)->getDtype());
		printRuleInLog(logout, line_count, "expression : variable ASSIGNOP logic_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2203 "1805067.tab.c"
    break;

  case 51: /* logic_expression: rel_expression  */
#line 843 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "logic_expression : rel_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());

	}
#line 2214 "1805067.tab.c"
    break;

  case 52: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 850 "1805067.y"
        {
		string left_operand = (yyvsp[-2].symbolInfo)->getDtype();
		string right_operand = (yyvsp[0].symbolInfo)->getDtype();
		if(left_operand != "int" || right_operand != "int") {
            error_count++;
            printError(errout, line_count, "Non-Integer operand on modulus operator");
			printError(logout, line_count, "Non-Integer operand on modulus operator");
        } 

		string logicalop = (yyvsp[-1].symbolInfo)->getSymbolName();
		string asmCode ="";
				
		if(logicalop == "||") {
			asmCode += "\t\t; OR OPERATION\n";
			asmCode += "\t\tPOP BX \n";
			asmCode += "\t\tPOP AX \n";
			asmCode += "\t\tOR BX, AX \n";
			asmCode += "\t\tPUSH BX \n";
		} else {
			string jumpExitLabel = newLabel("BRANCH_EXIT");
			string jumpZeroLabel = newLabel("BRANCH_ZERO");
			asmCode += "\t\t; AND OPERATION\n";
			asmCode += "\t\tPOP BX \n";
			asmCode += "\t\tCMP BX, 0 \n";
			asmCode += "\t\tJE "+ jumpZeroLabel +" \t; line no: "+to_string(line_count)+": condition not true\n";
			asmCode += "\t\tPOP BX \n";
			asmCode += "\t\tCMP BX, 0 \n";
			asmCode += "\t\tJE "+ jumpZeroLabel +" \t; line no: "+to_string(line_count)+": condition not true\n";
			asmCode += "\t\tPUSH 1 \t; line no: "+to_string(line_count)+": condition is true\n";
			asmCode += "\t\tJMP "+jumpExitLabel+"\n";
			asmCode += "\t\t"+jumpZeroLabel +":\n";
			asmCode += "\t\tPUSH 0 \n"; 
			asmCode += "\t\t"+jumpExitLabel+": \t;exiting AND operation\n";
		}
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getSymbolName() + (yyvsp[-1].symbolInfo)->getSymbolName() + (yyvsp[0].symbolInfo)->getSymbolName(), "logic_expression");
		(yyval.symbolInfo)->setDtype("int");
		printRuleInLog(logout, line_count, "logic_expression : rel_expression LOGICOP rel_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2260 "1805067.tab.c"
    break;

  case 53: /* rel_expression: simple_expression  */
#line 894 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "rel_expression : simple_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2270 "1805067.tab.c"
    break;

  case 54: /* rel_expression: simple_expression RELOP simple_expression  */
#line 900 "1805067.y"
        {
		string relop = (yyvsp[-1].symbolInfo)->getSymbolName();
		string jumpCode ;
		if (relop == "=="){
			jumpCode = "JE";
		}
		else if(relop == "!="){
			jumpCode = "JNE";
		}
		else if(relop == ">"){
			jumpCode = "JG";
		}
		else if(relop == ">="){
			jumpCode = "JGE";
		}
		else if(relop == "<"){
			jumpCode = "JL";
		}
		else if(relop == "<="){
			jumpCode = "JLE";
		}
		cout<<jumpCode<<"\n";
		string jumpTrueLabel = newLabel("BRANCH_TRUE");
		string jumpFalseLabel = newLabel("BRANCH_FALSE");
		string asmCode = "";
		asmCode += "\t\tPOP BX \t;line no:"+to_string(line_count)+" :  retrieves right operand\n";
		asmCode += "\t\tPOP AX \t;line no:"+to_string(line_count)+" :  retrieves left operand\n";
		asmCode += "\t\tCMP AX, BX \n";
		asmCode += "\t\t"+jumpCode+" "+jumpTrueLabel+"\n";
		asmCode += "\t\tMOV BX, 0\n";
		asmCode += "\t\tJMP "+jumpFalseLabel+"\n";
		asmCode += "\t\t"+jumpTrueLabel+":\n";
		asmCode += "\t\tMOV BX, 1\n";
		asmCode += "\t\t"+jumpFalseLabel+":\n";
		asmCode += "\t\tPUSH BX\n";
		asmCode += "\n";
		printAsm(asmFile, asmCode);
		(yyval.symbolInfo)->setDtype("int");
		printRuleInLog(logout, line_count, "rel_expression : simple_expression RELOP simple_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2316 "1805067.tab.c"
    break;

  case 55: /* simple_expression: term  */
#line 944 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "simple_expression : term");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2326 "1805067.tab.c"
    break;

  case 56: /* simple_expression: simple_expression ADDOP term  */
#line 950 "1805067.y"
        {
		//added in offline 4
		string asmCode ="";
		asmCode += "\t\tPOP BX\n";
		asmCode += "\t\tPOP AX\n";
		if((yyvsp[-1].symbolInfo)->getSymbolName() == "+"){
			asmCode += "\t\tADD BX, AX\n";
		} else {
			asmCode += "\t\tSUB AX, BX\n";
			asmCode += "\t\tMOV BX, AX\n";
		}
		
		asmCode += "\t\tPUSH BX\n";
		asmCode += "\n";
		printAsm(asmFile, asmCode);
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getSymbolName() + (yyvsp[-1].symbolInfo)->getSymbolName() + (yyvsp[0].symbolInfo)->getSymbolName(), "simple_expression");
		if (((yyvsp[-2].symbolInfo)->getDtype() == "float") || ((yyvsp[0].symbolInfo)->getDtype() == "float")) {
			(yyval.symbolInfo)->setDtype("float");
		} else {
			(yyval.symbolInfo)->setDtype("int");
		}	
		printRuleInLog(logout, line_count, "simple_expression : simple_expression ADDOP term");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2355 "1805067.tab.c"
    break;

  case 57: /* term: unary_expression  */
#line 977 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "term : unary_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2365 "1805067.tab.c"
    break;

  case 58: /* term: term MULOP unary_expression  */
#line 983 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getSymbolName() + (yyvsp[-1].symbolInfo)->getSymbolName() + (yyvsp[0].symbolInfo)->getSymbolName(), "term");
		string left_operand = (yyvsp[-2].symbolInfo)->getDtype();
		string right_operand = (yyvsp[0].symbolInfo)->getDtype();
		string asmCode = "";
		if((yyvsp[-1].symbolInfo)->getSymbolName() == "%") {
            if((yyvsp[0].symbolInfo)->getSymbolName() == "0") {
				error_count++;
                printError(errout, line_count, "Modulus by Zero");
				printError(logout, line_count, "Modulus by Zero");
            } else if(left_operand != "int" || right_operand != "int") {
                error_count++;
                printError(errout, line_count, "Non-Integer operand on modulus operator");
				printError(logout, line_count, "Non-Integer operand on modulus operator");
            } else {		//MULOP = %
				asmCode += "\t\tPOP BX; line no "+to_string(line_count) +" :  ; MODULUS start of integers\n";
				asmCode += "\t\tMOV CX, BX \n";
				asmCode += "\t\tXOR DX, DX \n";
				asmCode += "POP AX \n";
				asmCode += "IDIV CX \n";
				asmCode += "MOV BX, DX \n";
				asmCode += "PUSH BX \n";
				asmCode += "\n";

			}
			(yyval.symbolInfo)->setDtype("int");
        } else {  							 
			if ((yyvsp[-1].symbolInfo)->getSymbolName() == "/") { 				//MULOP = /
				if ((yyvsp[0].symbolInfo)->getSymbolName() == "0") {
					error_count++;
					printError(errout, line_count, "Division by Zero");
					printError(logout, line_count, "Division by Zero");
				} else {
					asmCode += "\t\tPOP BX; line no "+to_string(line_count) +" :  ; division start of integers\n";
					asmCode += "\t\tMOV CX, BX \n";
					asmCode += "\t\tXOR DX, DX \n";
					asmCode += "POP AX \n";
					asmCode += "IDIV CX \n";
					asmCode += "MOV BX, AX \n";
					asmCode += "PUSH BX \n";
					asmCode += "\n";
				}
			} else { 			// MULOP = *
				asmCode += "\t\tPOP BX; line no "+to_string(line_count) +" :  ; multiplication start of 2 integers\n";
				asmCode += "\t\tMOV CX, BX \n";
				asmCode += "POP AX \n";
				asmCode += "IMUL CX \n";
				asmCode += "MOV BX, AX \n";
				asmCode += "PUSH BX \n";
				asmCode += "\n";
			}

			if (left_operand == "float" || right_operand == "float") {
				(yyval.symbolInfo)->setDtype("float");
			} else {
				(yyval.symbolInfo)->setDtype("int");
			}												

		}
		printAsm(asmFile,asmCode);
		printRuleInLog(logout, line_count, "term : term MULOP unary_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2433 "1805067.tab.c"
    break;

  case 59: /* unary_expression: ADDOP unary_expression  */
#line 1049 "1805067.y"
        {

		if((yyvsp[-1].symbolInfo)->getSymbolName() == "-"){
			string asmCode = "\t\t;line no: " + to_string(line_count) + " Negating the value\n";
			asmCode += "\t\tPOP BX \t;pop the value\n";
			asmCode += "\t\tNEG BX \t; negate the value\n";
			asmCode += "\t\tPUSH BX \t; push the value \n";
			asmCode += "\n";
			printAsm(asmFile, asmCode);
		} 
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-1].symbolInfo)->getSymbolName() + (yyvsp[0].symbolInfo)->getSymbolName(), "unary_expression");
		(yyval.symbolInfo)->setDtype((yyvsp[0].symbolInfo)->getDtype());
		printRuleInLog(logout, line_count, "unary_expression : ADDOP unary_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2453 "1805067.tab.c"
    break;

  case 60: /* unary_expression: NOT unary_expression  */
#line 1065 "1805067.y"
        {
		string notEqualLabel = newLabel("NOT_EQUAL");
		string equalLabel = newLabel("EQUAL");
		string asmCode = "";
		asmCode += "\t\tPOP BX; line no "+to_string(line_count)+" :  not operation\n";
		asmCode += "\t\tCMP BX, 0 \n";
		asmCode += "\t\tJNE "+notEqualLabel+"\n";
		asmCode += "\t\tMOV BX, 0\n";
		asmCode += "\t\tJMP "+equalLabel+"\n";
		asmCode += "\t\t"+notEqualLabel+":\n";
		asmCode += "\t\tMOV BX, 1\n";
		asmCode += "\t\t"+equalLabel+":\n";
		asmCode += "\t\tPUSH BX\n";
		asmCode += "\n";
		printAsm(asmFile, asmCode);
		(yyval.symbolInfo) = new SymbolInfo("!" + (yyvsp[0].symbolInfo)->getSymbolName(), "unary_expression");
		(yyval.symbolInfo)->setDtype("int");
		printRuleInLog(logout, line_count, "unary_expression : NOT unary_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2478 "1805067.tab.c"
    break;

  case 61: /* unary_expression: factor  */
#line 1086 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "unary_expression : factor");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2488 "1805067.tab.c"
    break;

  case 62: /* factor: variable  */
#line 1094 "1805067.y"
        {


		// asmCode += "\t\tPUSH [BX] \t;pushing the value of the array at index "+ $3->getSymbolName()+" \n";
		//				asmCode += "\t\tPUSH BX \t;index pushed to stack\n";

		//added in offline 4
		string varName = (yyvsp[0].symbolInfo)->getSymbolName();
		if(isArray((yyvsp[0].symbolInfo)->getSymbolName())) {
			varName = extractArrayName((yyvsp[0].symbolInfo)->getSymbolName());
		}
		SymbolInfo* temp = symbolTable.lookupAll(varName);

		
		if (temp->getArrayData() == nullptr) { 
			//it's a variable. its value is in the stack
		} else {
			//it's an array. its index/address is in the top of the stack, value is next to top
			string asmCode = "\t\tPOP BX ;it's an array. its index/address is in the top of the stack,pop to get the value in top\n";
			printAsm(asmFile, asmCode);
		}
		
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "factor : variable");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2519 "1805067.tab.c"
    break;

  case 63: /* factor: ID LPAREN argument_list RPAREN  */
#line 1121 "1805067.y"
        {
		SymbolInfo* func_called;
		func_called = symbolTable.lookupAll((yyvsp[-3].symbolInfo)->getSymbolName());
		if (func_called == nullptr) {
			error_count++;
			printError(errout, line_count, "Undeclared function " + (yyvsp[-3].symbolInfo)->getSymbolName());
			printError(logout, line_count, "Undeclared function " + (yyvsp[-3].symbolInfo)->getSymbolName());
		} else {
			if (func_called->getFunctionData() == nullptr) {
				error_count++;
				printError(errout, line_count, func_called->getSymbolName() + " is not a function");
				printError(logout, line_count, func_called->getSymbolName() + " is not a function");
			} else {	
				vector<string> arg_dtype_list = split((yyvsp[-1].symbolInfo)->getDtype(), ',');
				FunctionData* func_data = func_called->getFunctionData();
				vector<Parameter> parameter_list = func_data->getParameterList();
				if (func_called->getDtype() == "void") {
					error_count++;
					printError(errout,line_count, "Void function used in expression");
					printError(logout,line_count, "Void function used in expression");
				} else if (parameter_list.size() != arg_dtype_list.size()) {
					error_count++;
					printError(errout, line_count, "Total number of arguments mismatch with declaration in function " + func_called->getSymbolName());
					printError(logout, line_count, "Total number of arguments mismatch with declaration in function " + func_called->getSymbolName());
				} else {
					bool errorFlag = false;
					for (int i = 0; i < arg_dtype_list.size(); i++) {
						if (arg_dtype_list[i] != parameter_list[i].getParameterType()) {
							if(parameter_list[i].getParameterType() == "float" && arg_dtype_list[i] == "int") {

							} else {
								error_count++;
								printError(errout, line_count,  to_string(i+1) + "th argument mismatch in function " + func_called->getSymbolName());
								printError(logout, line_count, 	to_string(i+1) + "th argument mismatch in function " + func_called->getSymbolName());
								errorFlag = true;
							}
						}
					}

				}
			}
		}

		string asmCode = "";
		asmCode += "\t\tCALL "+(yyvsp[-3].symbolInfo)->getSymbolName()+" \t;line no "+to_string(line_count)+" : function "+(yyvsp[-3].symbolInfo)->getSymbolName()+" called\n";
		asmCode += "\t\tMOV BX, DX \t;line no "+to_string(line_count)+" :  return result is in DX.\n";
		asmCode += "\t\tPUSH BX \n";
		asmCode += "\n";
		printAsm(asmFile,asmCode);
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-3].symbolInfo)->getSymbolName() + "(" + (yyvsp[-1].symbolInfo)->getSymbolName() + ")", "factor");
		(yyval.symbolInfo)->setDtype((yyvsp[-3].symbolInfo)->getDtype());
		printRuleInLog(logout, line_count, "factor : ID LPAREN argument_list RPAREN");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());

	}
#line 2579 "1805067.tab.c"
    break;

  case 64: /* factor: LPAREN expression RPAREN  */
#line 1177 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo("(" + (yyvsp[-1].symbolInfo)->getSymbolName() + ")", (yyvsp[-1].symbolInfo)->getSymbolType());
		printRuleInLog(logout, line_count, "factor : LPAREN expression RPAREN");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2589 "1805067.tab.c"
    break;

  case 65: /* factor: CONST_INT  */
#line 1183 "1805067.y"
        {
		(yyval.symbolInfo) = yylval.symbolInfo;
		(yyval.symbolInfo)->setDtype("int");
		string asmCode = "\t\tPUSH " + (yyval.symbolInfo)->getSymbolName() + " ;push CONST_INT \n";
		printAsm(asmFile, asmCode);
		printRuleInLog(logout, line_count, "factor : CONST_INT");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2602 "1805067.tab.c"
    break;

  case 66: /* factor: CONST_FLOAT  */
#line 1192 "1805067.y"
        {
		(yyval.symbolInfo) = yylval.symbolInfo;
		(yyval.symbolInfo)->setDtype("float");
		printRuleInLog(logout, line_count, "factor : CONST_FLOAT");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2613 "1805067.tab.c"
    break;

  case 67: /* factor: variable INCOP  */
#line 1199 "1805067.y"
        {
		
		//added in offline 4
		string varName = (yyvsp[-1].symbolInfo)->getSymbolName();
		if(isArray((yyvsp[-1].symbolInfo)->getSymbolName())) {
			varName = extractArrayName((yyvsp[-1].symbolInfo)->getSymbolName());
		}
		SymbolInfo* temp = symbolTable.lookupAll(varName);
		cout<<"thik++\n";
		string asmCode = "";
		if (temp->getArrayData() == nullptr) { 
			asmCode += "\t\tPOP AX \n";
			asmCode += "\t\tPUSH AX \n"; //retrieves value
			if(temp->getOffset() == 0){ 	// global variable
				asmCode +="\t\tINC AX\n";
				asmCode += "\t\t MOV "+temp->getSymbolName()+", AX;	line no:"+to_string(line_count)+"\n";
				
			} else { 		// local variable
				asmCode += "\t\tINC AX\n";
				asmCode += "\t\t MOV [BP + "+to_string(temp->getOffset())+"], AX;	line no:"+to_string(line_count)+"\n";
				
			}
			
		} else {
			asmCode += "\t\tPOP BX\n"; //retrieves address
			asmCode += "\t\tPOP AX\n"; //retrieves value
			asmCode += "\t\tPUSH AX\n";
			if (temp->getOffset() == 0){ 	//global array
				asmCode +="\t\tINC AX\n";
				asmCode += "\t\t MOV "+temp->getSymbolName()+"[BX], AX;	line no:"+to_string(line_count)+"\n";
				
			} else { 		//local array
				asmCode +="\t\tINC AX\n";
				asmCode += "\t\t MOV [BX], AX;	line no:"+to_string(line_count)+"\n";
				
			}
		}
		asmCode += "\n";
		printAsm(asmFile, asmCode);

		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-1].symbolInfo)->getSymbolName() + "++", (yyvsp[-1].symbolInfo)->getSymbolType());
		printRuleInLog(logout, line_count, "factor : variable INCOP");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2662 "1805067.tab.c"
    break;

  case 68: /* factor: variable DECOP  */
#line 1244 "1805067.y"
        {
		//added in offline 4
		string varName = (yyvsp[-1].symbolInfo)->getSymbolName();
		if(isArray((yyvsp[-1].symbolInfo)->getSymbolName())) {
			varName = extractArrayName((yyvsp[-1].symbolInfo)->getSymbolName());
		}
		SymbolInfo* temp = symbolTable.lookupAll(varName);

		string asmCode = "";
		if (temp->getArrayData() == nullptr) { 
			asmCode += "\t\tPOP AX\n";
			asmCode += "\t\tPUSH AX\n";
			if (temp->getOffset() == 0){ 	//global array
				asmCode +="\t\tDEC AX\n";
				asmCode += "\t\t MOV "+temp->getSymbolName()+"[BX], AX;	line no:"+to_string(line_count)+"\n";
				asmCode += "\t\t POP BX; line no "+ to_string(line_count) +"; previously pushed value on stack is removed\n";
			} else { 		//local array
				asmCode +="\t\tDEC AX\n";
				asmCode += "\t\t MOV [BX], AX;	line no:"+to_string(line_count)+"\n";
				asmCode += "\t\t POP BX; line no "+ to_string(line_count) +"; previously pushed value on stack is removed\n";
			}
		} else {
			asmCode += "\t\tPOP AX \n";
			asmCode += "\t\tPUSH AX \n";
			if(temp->getOffset() == 0){ 	// global variable
				asmCode +="\t\tDEC AX\n";
				asmCode += "\t\t MOV "+temp->getSymbolName()+", AX;	line no:"+to_string(line_count)+"\n";
			} else { 		// local variable
				asmCode += "\t\tDEC AX\n";
				asmCode += "\t\t MOV [BP + "+to_string(temp->getOffset())+"], AX;	line no:"+to_string(line_count)+"\n";
			}
		}
		printAsm(asmFile, asmCode);

		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-1].symbolInfo)->getSymbolName() + "--", (yyvsp[-1].symbolInfo)->getSymbolType());
		printRuleInLog(logout, line_count, "factor : variable DECOP");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2705 "1805067.tab.c"
    break;

  case 69: /* argument_list: arguments  */
#line 1285 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "argument_list : arguments");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2715 "1805067.tab.c"
    break;

  case 70: /* argument_list: %empty  */
#line 1291 "1805067.y"
        {
		(yyval.symbolInfo) = new SymbolInfo("", "void");
		printRuleInLog(logout, line_count, "argument_list : ");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2725 "1805067.tab.c"
    break;

  case 71: /* arguments: arguments COMMA logic_expression  */
#line 1299 "1805067.y"
        { 
		(yyval.symbolInfo) = new SymbolInfo((yyvsp[-2].symbolInfo)->getSymbolName() +"," + (yyvsp[0].symbolInfo)->getSymbolName(), "arguments");
		(yyval.symbolInfo)->setDtype((yyvsp[-2].symbolInfo)->getDtype() + "," + (yyvsp[0].symbolInfo)->getDtype());
		printRuleInLog(logout, line_count, "arguments : arguments COMMA logic_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2736 "1805067.tab.c"
    break;

  case 72: /* arguments: logic_expression  */
#line 1306 "1805067.y"
        {
		(yyval.symbolInfo) = (yyvsp[0].symbolInfo);
		printRuleInLog(logout, line_count, "arguments : logic_expression");
		printCodeInLog(logout, (yyval.symbolInfo)->getSymbolName());
	}
#line 2746 "1805067.tab.c"
    break;


#line 2750 "1805067.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1313 "1805067.y"

int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	logout.open("log.txt");
	errout.open("error.txt");
	asmFile = "code.asm";
	yyin=fp;
	yyparse();
	symbolTable.printAllScopeTable(logout);
	logout<<"Total lines: "<<line_count<<"\n";
	logout<<"Total errors: "<<error_count<<"\n";
	logout.close();
	errout.close();
	
	return 0;
}

