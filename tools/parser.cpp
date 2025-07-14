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
#line 6 "assets/parser.bison"

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

#include "expr.h"
#include "decl.h"
#include "stmt.h"
#include "symbol.h"
#include "type.h"
#include "semantic_routines.h"

#include "intel_codegen.h"
#include "typecheck.h"
#include "log.h"
#include "dot_log.h"
#include "dot_gen.h"

extern int yylex();
extern char *yytext;

std::map<std::string, struct expr *> symbolTable; // Use std::string for symbol table keys
std::stringstream dataSection; // To collect .data section entries


int yyerror(const char *s) {
    extern char *yytext;
    extern int yylineno;
    printf("Parse error near token '%s' at line %d: %s\n", yytext, yylineno, s);
    return 1;
}

void print_symbol_table() {
    for (const auto &entry : symbolTable) {
        printf("\n Variable %s = %d\n", entry.first.c_str(), expr_evaluate(entry.second));
    }
}

struct expr *parser_result;

#line 114 "tools/parser.cpp"

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

#include "token.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_ID = 3,                   /* TOKEN_ID  */
  YYSYMBOL_TOKEN_STRING_LITERAL = 4,       /* TOKEN_STRING_LITERAL  */
  YYSYMBOL_TOKEN_INT = 5,                  /* TOKEN_INT  */
  YYSYMBOL_TOKEN_PLUS = 6,                 /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 7,                /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_MUL = 8,                  /* TOKEN_MUL  */
  YYSYMBOL_TOKEN_DIV = 9,                  /* TOKEN_DIV  */
  YYSYMBOL_TOKEN_SEMI = 10,                /* TOKEN_SEMI  */
  YYSYMBOL_TOKEN_LPAREN = 11,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 12,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_ASSIGN = 13,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_ERROR = 14,               /* TOKEN_ERROR  */
  YYSYMBOL_TOKEN_IF = 15,                  /* TOKEN_IF  */
  YYSYMBOL_TOKEN_WHILE = 16,               /* TOKEN_WHILE  */
  YYSYMBOL_TOKEN_PRINT = 17,               /* TOKEN_PRINT  */
  YYSYMBOL_TOKEN_RETURN = 18,              /* TOKEN_RETURN  */
  YYSYMBOL_TOKEN_LBRACE = 19,              /* TOKEN_LBRACE  */
  YYSYMBOL_TOKEN_RBRACE = 20,              /* TOKEN_RBRACE  */
  YYSYMBOL_TOKEN_COMMA = 21,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_VOID = 22,                /* TOKEN_VOID  */
  YYSYMBOL_TOKEN_INT_TYPE = 23,            /* TOKEN_INT_TYPE  */
  YYSYMBOL_TOKEN_BOOLEAN_TYPE = 24,        /* TOKEN_BOOLEAN_TYPE  */
  YYSYMBOL_TOKEN_STRING_TYPE = 25,         /* TOKEN_STRING_TYPE  */
  YYSYMBOL_TOKEN_FOR = 26,                 /* TOKEN_FOR  */
  YYSYMBOL_TOKEN_FUNCTION = 27,            /* TOKEN_FUNCTION  */
  YYSYMBOL_TOKEN_DPOINTS = 28,             /* TOKEN_DPOINTS  */
  YYSYMBOL_TOKEN_INCREMENT = 29,           /* TOKEN_INCREMENT  */
  YYSYMBOL_TOKEN_DECREMENT = 30,           /* TOKEN_DECREMENT  */
  YYSYMBOL_TOKEN_EQ = 31,                  /* TOKEN_EQ  */
  YYSYMBOL_TOKEN_NEQ = 32,                 /* TOKEN_NEQ  */
  YYSYMBOL_TOKEN_LT = 33,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_GT = 34,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_LEQ = 35,                 /* TOKEN_LEQ  */
  YYSYMBOL_TOKEN_GEQ = 36,                 /* TOKEN_GEQ  */
  YYSYMBOL_TOKEN_TRUE = 37,                /* TOKEN_TRUE  */
  YYSYMBOL_TOKEN_FALSE = 38,               /* TOKEN_FALSE  */
  YYSYMBOL_39_then_ = 39,                  /* "then"  */
  YYSYMBOL_TOKEN_ELSE = 40,                /* TOKEN_ELSE  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_decl_list = 43,                 /* decl_list  */
  YYSYMBOL_decl = 44,                      /* decl  */
  YYSYMBOL_type = 45,                      /* type  */
  YYSYMBOL_param_list = 46,                /* param_list  */
  YYSYMBOL_param_decl = 47,                /* param_decl  */
  YYSYMBOL_stmt = 48,                      /* stmt  */
  YYSYMBOL_normal_stmt = 49,               /* normal_stmt  */
  YYSYMBOL_stmt_block = 50,                /* stmt_block  */
  YYSYMBOL_stmt_list = 51,                 /* stmt_list  */
  YYSYMBOL_for_assignment = 52,            /* for_assignment  */
  YYSYMBOL_assignment = 53,                /* assignment  */
  YYSYMBOL_expr = 54,                      /* expr  */
  YYSYMBOL_cond = 55,                      /* cond  */
  YYSYMBOL_term = 56,                      /* term  */
  YYSYMBOL_call = 57,                      /* call  */
  YYSYMBOL_call_args = 58,                 /* call_args  */
  YYSYMBOL_factor = 59                     /* factor  */
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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   179

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    80,    80,   110,   111,   115,   116,   117,   126,   127,
     128,   129,   133,   134,   135,   139,   143,   144,   145,   149,
     150,   151,   152,   153,   154,   158,   164,   165,   167,   171,
     174,   178,   179,   183,   190,   191,   192,   193,   197,   198,
     199,   200,   201,   202,   205,   206,   207,   208,   212,   216,
     217,   218,   222,   223,   224,   225,   226,   227,   228
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
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_ID",
  "TOKEN_STRING_LITERAL", "TOKEN_INT", "TOKEN_PLUS", "TOKEN_MINUS",
  "TOKEN_MUL", "TOKEN_DIV", "TOKEN_SEMI", "TOKEN_LPAREN", "TOKEN_RPAREN",
  "TOKEN_ASSIGN", "TOKEN_ERROR", "TOKEN_IF", "TOKEN_WHILE", "TOKEN_PRINT",
  "TOKEN_RETURN", "TOKEN_LBRACE", "TOKEN_RBRACE", "TOKEN_COMMA",
  "TOKEN_VOID", "TOKEN_INT_TYPE", "TOKEN_BOOLEAN_TYPE",
  "TOKEN_STRING_TYPE", "TOKEN_FOR", "TOKEN_FUNCTION", "TOKEN_DPOINTS",
  "TOKEN_INCREMENT", "TOKEN_DECREMENT", "TOKEN_EQ", "TOKEN_NEQ",
  "TOKEN_LT", "TOKEN_GT", "TOKEN_LEQ", "TOKEN_GEQ", "TOKEN_TRUE",
  "TOKEN_FALSE", "\"then\"", "TOKEN_ELSE", "$accept", "program",
  "decl_list", "decl", "type", "param_list", "param_decl", "stmt",
  "normal_stmt", "stmt_block", "stmt_list", "for_assignment", "assignment",
  "expr", "cond", "term", "call", "call_args", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-91)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      15,    23,    17,   -91,    15,   152,   -91,   -91,   -91,   -91,
     -91,   -91,   110,    20,    39,   -91,     4,    56,    49,   -91,
     -91,     9,     4,   -91,   -91,    22,   -91,    -5,   -91,   -91,
      34,    19,   -91,     4,   -91,   -91,    32,     4,     4,   -91,
       4,     4,     4,     4,     4,     4,     9,     9,   110,    65,
      56,   115,    24,   -91,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,   -91,   -91,   -91,    60,   -91,   -91,     4,   -91,
     -91,   115,   111,    -3,    69,    74,     4,     4,   -91,    75,
     -91,   -91,   -91,   -91,    82,     4,   -91,   -91,     4,     4,
      14,    64,    90,   -91,   115,    70,    77,   -91,   -91,    -8,
      97,   -91,   141,   137,     4,    47,   -91,    84,   141,    90,
     -91,   112,   137,   -91
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     2,     4,     0,     1,     3,     8,     9,
      10,    11,     0,     0,     0,     5,     0,    12,    58,    56,
      57,     0,     0,    54,    55,     0,    36,    37,    47,    46,
       0,     0,    13,    49,    58,    52,     0,     0,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     0,    53,    34,    35,    38,    39,    40,    41,
      42,    43,    44,    45,    15,     0,    14,    48,     0,    26,
       7,    51,     0,     0,     0,     0,    49,     0,    25,     0,
      28,    27,    18,    24,     0,     0,    32,    33,     0,     0,
       0,     0,    30,    23,    31,     0,     0,    21,    22,     0,
       0,    29,     0,     0,     0,    16,    19,     0,     0,     0,
      17,     0,     0,    20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -91,   -91,   119,    53,   -11,   -91,    86,   -69,   -27,    73,
     -91,   -91,   -90,   -16,   -91,   128,   -91,    63,     2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,    13,    31,    32,    81,    82,    83,
      72,   100,    84,    51,    26,    27,    28,    52,    29
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      25,    14,   101,    46,    47,    85,    36,    18,    19,    20,
      85,    21,    34,    19,    20,    22,    21,     6,     1,   111,
      22,    86,    87,    35,    97,     5,    86,    87,    37,    38,
      15,    49,    39,    16,   106,    68,    67,    64,    37,    38,
      50,    23,    24,   113,    53,    68,    23,    24,    62,    63,
      17,     5,    71,    40,    41,    42,    43,    44,    45,    30,
      33,    91,    48,    40,    41,    42,    43,    44,    45,    94,
      37,    38,    95,    96,    98,   105,    37,    38,    65,    69,
      88,   110,   102,    37,    38,    89,    92,   108,   107,   103,
      37,    38,    93,    99,   109,    40,    41,    42,    43,    44,
      45,    40,    41,    42,    43,    44,    45,   104,    40,    41,
      42,    43,    44,    45,    73,    40,    41,    42,    43,    44,
      45,    37,    38,     7,   112,    80,    74,    75,    76,    77,
      69,    78,     8,     9,    10,    11,    66,    79,    70,    90,
      99,     0,     0,     0,    99,     0,    40,    41,    42,    43,
      44,    45,    74,    75,    76,    77,    69,    75,    76,    77,
      69,     0,     0,    79,     0,    54,    55,    79,    56,    57,
      58,    59,    60,    61,     8,     9,    10,    11,     0,    12
};

static const yytype_int8 yycheck[] =
{
      16,    12,    92,     8,     9,    13,    22,     3,     4,     5,
      13,     7,     3,     4,     5,    11,     7,     0,     3,   109,
      11,    29,    30,    21,    10,    28,    29,    30,     6,     7,
      10,    12,    10,    13,   103,    21,    12,    48,     6,     7,
      21,    37,    38,   112,    12,    21,    37,    38,    46,    47,
      11,    28,    68,    31,    32,    33,    34,    35,    36,     3,
      11,    77,    28,    31,    32,    33,    34,    35,    36,    85,
       6,     7,    88,    89,    10,   102,     6,     7,    13,    19,
      11,   108,    12,     6,     7,    11,    11,    40,   104,    12,
       6,     7,    10,     3,    10,    31,    32,    33,    34,    35,
      36,    31,    32,    33,    34,    35,    36,    10,    31,    32,
      33,    34,    35,    36,     3,    31,    32,    33,    34,    35,
      36,     6,     7,     4,    12,    72,    15,    16,    17,    18,
      19,    20,    22,    23,    24,    25,    50,    26,    65,    76,
       3,    -1,    -1,    -1,     3,    -1,    31,    32,    33,    34,
      35,    36,    15,    16,    17,    18,    19,    16,    17,    18,
      19,    -1,    -1,    26,    -1,    37,    38,    26,    40,    41,
      42,    43,    44,    45,    22,    23,    24,    25,    -1,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    42,    43,    44,    28,     0,    43,    22,    23,
      24,    25,    27,    45,    45,    10,    13,    11,     3,     4,
       5,     7,    11,    37,    38,    54,    55,    56,    57,    59,
       3,    46,    47,    11,     3,    59,    54,     6,     7,    10,
      31,    32,    33,    34,    35,    36,     8,     9,    28,    12,
      21,    54,    58,    12,    56,    56,    56,    56,    56,    56,
      56,    56,    59,    59,    45,    13,    47,    12,    21,    19,
      50,    54,    51,     3,    15,    16,    17,    18,    20,    26,
      44,    48,    49,    50,    53,    13,    29,    30,    11,    11,
      58,    54,    11,    10,    54,    54,    54,    10,    10,     3,
      52,    53,    12,    12,    10,    49,    48,    54,    40,    10,
      49,    53,    12,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    45,    45,
      45,    45,    46,    46,    46,    47,    48,    48,    48,    49,
      49,    49,    49,    49,    49,    50,    51,    51,    51,    52,
      52,    53,    53,    53,    54,    54,    54,    54,    55,    55,
      55,    55,    55,    55,    56,    56,    56,    56,    57,    58,
      58,    58,    59,    59,    59,    59,    59,    59,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     4,     6,     9,     1,     1,
       1,     1,     0,     1,     3,     3,     5,     7,     1,     5,
       9,     3,     3,     2,     1,     3,     0,     2,     2,     1,
       0,     3,     2,     2,     3,     3,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     4,     0,
       1,     3,     2,     3,     1,     1,     1,     1,     1
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
  case 2: /* program: decl_list  */
#line 80 "assets/parser.bison"
                                                                    {
                                                                      (yyvsp[0].decl)->resolve();
                                                                      (yyvsp[0].decl)->typecheck();

                                                                      //Before folding
                                                                      DOT_LOGCFG.initiate();
                                                                      print_decl_list_dot((yyvsp[0].decl));
                                                                      DOT_LOGCFG.finish();

                                                                      //Fold - Optimize                                                    
                                                                      constant_fold_decls((yyvsp[0].decl));

                                                                      //After folding

                                                                      //Setup new DOT configs for the optimized ast
                                                                      DOT_LOGCFG.OPTIMIZE_FLAG = true;
                                                                      DOT_LOGCFG.updateFilePath();
                                                                      DOT_LOGCFG.clearFile();

                                                                      DOT_LOGCFG.initiate();                                                                   
                                                                      print_decl_list_dot((yyvsp[0].decl));
                                                                      DOT_LOGCFG.finish();

                                                                      //Generate assembly code
                                                                      decl_codegen((yyvsp[0].decl));
                                                                      decl_finish_codegen();
                                                                    }
#line 1271 "tools/parser.cpp"
    break;

  case 3: /* decl_list: decl decl_list  */
#line 110 "assets/parser.bison"
                                                                    { (yyval.decl) = (yyvsp[-1].decl); (yyvsp[-1].decl)->next = (yyvsp[0].decl); }
#line 1277 "tools/parser.cpp"
    break;

  case 4: /* decl_list: %empty  */
#line 111 "assets/parser.bison"
                                                                    { (yyval.decl) = nullptr; }
#line 1283 "tools/parser.cpp"
    break;

  case 5: /* decl: TOKEN_ID TOKEN_DPOINTS type TOKEN_SEMI  */
#line 115 "assets/parser.bison"
                                             { (yyval.decl) = new Decl(std::string((yyvsp[-3].expr_id)), (yyvsp[-1].type), nullptr, nullptr, nullptr); }
#line 1289 "tools/parser.cpp"
    break;

  case 6: /* decl: TOKEN_ID TOKEN_DPOINTS type TOKEN_ASSIGN expr TOKEN_SEMI  */
#line 116 "assets/parser.bison"
                                                               { (yyval.decl) = new Decl(std::string((yyvsp[-5].expr_id)), (yyvsp[-3].type), (yyvsp[-1].expr_ptr), nullptr, nullptr); }
#line 1295 "tools/parser.cpp"
    break;

  case 7: /* decl: TOKEN_ID TOKEN_DPOINTS TOKEN_FUNCTION type TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_ASSIGN stmt_block  */
#line 117 "assets/parser.bison"
                                                                                                              { 
                    (yyval.decl) = new Decl(std::string((yyvsp[-8].expr_id)),
                      type_create(TYPE_FUNCTION, (yyvsp[-5].type), (yyvsp[-3].param)),
                      nullptr,
                      (yyvsp[0].stmt),
                      nullptr);}
#line 1306 "tools/parser.cpp"
    break;

  case 8: /* type: TOKEN_VOID  */
#line 126 "assets/parser.bison"
                                                                    { (yyval.type) = type_create(TYPE_VOID, nullptr, nullptr); }
#line 1312 "tools/parser.cpp"
    break;

  case 9: /* type: TOKEN_INT_TYPE  */
#line 127 "assets/parser.bison"
                                                                    { (yyval.type) = type_create(TYPE_INTEGER, nullptr, nullptr); }
#line 1318 "tools/parser.cpp"
    break;

  case 10: /* type: TOKEN_BOOLEAN_TYPE  */
#line 128 "assets/parser.bison"
                                                                    { (yyval.type) = type_create(TYPE_BOOLEAN, nullptr, nullptr); }
#line 1324 "tools/parser.cpp"
    break;

  case 11: /* type: TOKEN_STRING_TYPE  */
#line 129 "assets/parser.bison"
                                                                    { (yyval.type) = type_create(TYPE_STRING, nullptr, nullptr); }
#line 1330 "tools/parser.cpp"
    break;

  case 12: /* param_list: %empty  */
#line 133 "assets/parser.bison"
                                                                    { (yyval.param) = nullptr; }
#line 1336 "tools/parser.cpp"
    break;

  case 13: /* param_list: param_decl  */
#line 134 "assets/parser.bison"
                                                                    { (yyval.param) = (yyvsp[0].param); }
#line 1342 "tools/parser.cpp"
    break;

  case 14: /* param_list: param_list TOKEN_COMMA param_decl  */
#line 135 "assets/parser.bison"
                                                                    { (yyval.param) = param_list_append((yyvsp[-2].param), (yyvsp[0].param)); }
#line 1348 "tools/parser.cpp"
    break;

  case 15: /* param_decl: TOKEN_ID TOKEN_DPOINTS type  */
#line 139 "assets/parser.bison"
                                                                    { (yyval.param) = param_list_create(std::string((yyvsp[-2].expr_id)), (yyvsp[0].type), nullptr); }
#line 1354 "tools/parser.cpp"
    break;

  case 16: /* stmt: TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN normal_stmt  */
#line 143 "assets/parser.bison"
                                                                                 { (yyval.stmt) = stmt_create_if_else((yyvsp[-2].expr_ptr), (yyvsp[0].stmt), nullptr);   LOG(DEBUG) << "stmt_create_if_else:: IF_STMT";}
#line 1360 "tools/parser.cpp"
    break;

  case 17: /* stmt: TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN normal_stmt TOKEN_ELSE normal_stmt  */
#line 144 "assets/parser.bison"
                                                                                 { (yyval.stmt) = stmt_create_if_else((yyvsp[-4].expr_ptr), (yyvsp[-2].stmt), (yyvsp[0].stmt));        LOG(DEBUG) << "stmt_create_if_else::IF_ELSE_STMT";}
#line 1366 "tools/parser.cpp"
    break;

  case 19: /* normal_stmt: TOKEN_WHILE TOKEN_LPAREN expr TOKEN_RPAREN stmt  */
#line 149 "assets/parser.bison"
                                                                                                { (yyval.stmt) = stmt_create(STMT_WHILE, nullptr, nullptr, (yyvsp[-2].expr_ptr), nullptr, (yyvsp[0].stmt), nullptr, nullptr); }
#line 1372 "tools/parser.cpp"
    break;

  case 20: /* normal_stmt: TOKEN_FOR TOKEN_LPAREN for_assignment TOKEN_SEMI expr TOKEN_SEMI assignment TOKEN_RPAREN stmt  */
#line 150 "assets/parser.bison"
                                                                                                    { (yyval.stmt) = stmt_create(STMT_FOR, nullptr, (yyvsp[-6].expr_ptr), (yyvsp[-4].expr_ptr), (yyvsp[-2].expr_ptr), (yyvsp[0].stmt), nullptr, nullptr); }
#line 1378 "tools/parser.cpp"
    break;

  case 21: /* normal_stmt: TOKEN_PRINT call_args TOKEN_SEMI  */
#line 151 "assets/parser.bison"
                                                                                                { (yyval.stmt) = stmt_create(STMT_PRINT, nullptr, nullptr, (yyvsp[-1].expr_ptr), nullptr, nullptr, nullptr, nullptr); }
#line 1384 "tools/parser.cpp"
    break;

  case 22: /* normal_stmt: TOKEN_RETURN expr TOKEN_SEMI  */
#line 152 "assets/parser.bison"
                                                                                                { (yyval.stmt) = stmt_create(STMT_RETURN, nullptr, nullptr, (yyvsp[-1].expr_ptr), nullptr, nullptr, nullptr, nullptr); }
#line 1390 "tools/parser.cpp"
    break;

  case 23: /* normal_stmt: assignment TOKEN_SEMI  */
#line 153 "assets/parser.bison"
                                                                                                { (yyval.stmt) = stmt_create(STMT_EXPR, nullptr, nullptr, (yyvsp[-1].expr_ptr), nullptr, nullptr, nullptr, nullptr); }
#line 1396 "tools/parser.cpp"
    break;

  case 24: /* normal_stmt: stmt_block  */
#line 154 "assets/parser.bison"
                                                                                                { (yyval.stmt) = stmt_create(STMT_BLOCK, nullptr, nullptr, nullptr, nullptr, (yyvsp[0].stmt), nullptr, nullptr); }
#line 1402 "tools/parser.cpp"
    break;

  case 25: /* stmt_block: TOKEN_LBRACE stmt_list TOKEN_RBRACE  */
#line 159 "assets/parser.bison"
        { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1408 "tools/parser.cpp"
    break;

  case 26: /* stmt_list: %empty  */
#line 164 "assets/parser.bison"
        { (yyval.stmt) = nullptr; }
#line 1414 "tools/parser.cpp"
    break;

  case 27: /* stmt_list: stmt_list stmt  */
#line 166 "assets/parser.bison"
        { (yyval.stmt) = stmt_list_append((yyvsp[-1].stmt), (yyvsp[0].stmt)); }
#line 1420 "tools/parser.cpp"
    break;

  case 28: /* stmt_list: stmt_list decl  */
#line 168 "assets/parser.bison"
        { (yyval.stmt) = stmt_list_append((yyvsp[-1].stmt), stmt_create(STMT_DECL, (yyvsp[0].decl), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)); }
#line 1426 "tools/parser.cpp"
    break;

  case 29: /* for_assignment: assignment  */
#line 172 "assets/parser.bison"
                { (yyval.expr_ptr) = (yyvsp[0].expr_ptr); }
#line 1432 "tools/parser.cpp"
    break;

  case 30: /* for_assignment: %empty  */
#line 174 "assets/parser.bison"
                    { (yyval.expr_ptr) = NULL; }
#line 1438 "tools/parser.cpp"
    break;

  case 31: /* assignment: TOKEN_ID TOKEN_ASSIGN expr  */
#line 178 "assets/parser.bison"
                                   { (yyval.expr_ptr) = expr_create(EXPR_ASSIGN, expr_create_name(std::string((yyvsp[-2].expr_id))), (yyvsp[0].expr_ptr)); }
#line 1444 "tools/parser.cpp"
    break;

  case 32: /* assignment: TOKEN_ID TOKEN_INCREMENT  */
#line 179 "assets/parser.bison"
                                   { 
        struct expr *new_expr = expr_create(EXPR_ADD, expr_create_name(std::string((yyvsp[-1].expr_id))), expr_create_integer_literal(1));
        (yyval.expr_ptr) = expr_create(EXPR_ASSIGN, expr_create_name(std::string((yyvsp[-1].expr_id))), new_expr); 
      }
#line 1453 "tools/parser.cpp"
    break;

  case 33: /* assignment: TOKEN_ID TOKEN_DECREMENT  */
#line 183 "assets/parser.bison"
                                   { 
        struct expr *new_expr = expr_create(EXPR_SUBTRACT, expr_create_name(std::string((yyvsp[-1].expr_id))), expr_create_integer_literal(1));
        (yyval.expr_ptr) = expr_create(EXPR_ASSIGN, expr_create_name(std::string((yyvsp[-1].expr_id))), new_expr); 
      }
#line 1462 "tools/parser.cpp"
    break;

  case 34: /* expr: expr TOKEN_PLUS term  */
#line 190 "assets/parser.bison"
                                      { (yyval.expr_ptr) = expr_create(EXPR_ADD, (yyvsp[-2].expr_ptr), (yyvsp[0].expr_ptr));}
#line 1468 "tools/parser.cpp"
    break;

  case 35: /* expr: expr TOKEN_MINUS term  */
#line 191 "assets/parser.bison"
                                      { (yyval.expr_ptr) = expr_create(EXPR_SUBTRACT, (yyvsp[-2].expr_ptr), (yyvsp[0].expr_ptr)); }
#line 1474 "tools/parser.cpp"
    break;

  case 36: /* expr: cond  */
#line 192 "assets/parser.bison"
                                      { (yyval.expr_ptr) = (yyvsp[0].expr_ptr); }
#line 1480 "tools/parser.cpp"
    break;

  case 37: /* expr: term  */
#line 193 "assets/parser.bison"
                                      { (yyval.expr_ptr) = (yyvsp[0].expr_ptr); }
#line 1486 "tools/parser.cpp"
    break;

  case 38: /* cond: expr TOKEN_EQ term  */
#line 197 "assets/parser.bison"
                         { (yyval.expr_ptr) = expr_create(EXPR_EQ, (yyvsp[-2].expr_ptr), (yyvsp[0].expr_ptr)); }
#line 1492 "tools/parser.cpp"
    break;

  case 39: /* cond: expr TOKEN_NEQ term  */
#line 198 "assets/parser.bison"
                          { (yyval.expr_ptr) = expr_create(EXPR_NEQ, (yyvsp[-2].expr_ptr), (yyvsp[0].expr_ptr)); }
#line 1498 "tools/parser.cpp"
    break;

  case 40: /* cond: expr TOKEN_LT term  */
#line 199 "assets/parser.bison"
                         { (yyval.expr_ptr) = expr_create(EXPR_LT, (yyvsp[-2].expr_ptr), (yyvsp[0].expr_ptr));}
#line 1504 "tools/parser.cpp"
    break;

  case 41: /* cond: expr TOKEN_GT term  */
#line 200 "assets/parser.bison"
                         { (yyval.expr_ptr) = expr_create(EXPR_GT, (yyvsp[-2].expr_ptr), (yyvsp[0].expr_ptr)); }
#line 1510 "tools/parser.cpp"
    break;

  case 42: /* cond: expr TOKEN_LEQ term  */
#line 201 "assets/parser.bison"
                          { (yyval.expr_ptr) = expr_create(EXPR_LEQ, (yyvsp[-2].expr_ptr), (yyvsp[0].expr_ptr)); }
#line 1516 "tools/parser.cpp"
    break;

  case 43: /* cond: expr TOKEN_GEQ term  */
#line 202 "assets/parser.bison"
                          { (yyval.expr_ptr) = expr_create(EXPR_GEQ, (yyvsp[-2].expr_ptr), (yyvsp[0].expr_ptr)); }
#line 1522 "tools/parser.cpp"
    break;

  case 44: /* term: term TOKEN_MUL factor  */
#line 205 "assets/parser.bison"
                                     { (yyval.expr_ptr) = expr_create(EXPR_MULTIPLY,(yyvsp[-2].expr_ptr),(yyvsp[0].expr_ptr)); }
#line 1528 "tools/parser.cpp"
    break;

  case 45: /* term: term TOKEN_DIV factor  */
#line 206 "assets/parser.bison"
                                     { (yyval.expr_ptr) = expr_create(EXPR_DIVIDE,(yyvsp[-2].expr_ptr),(yyvsp[0].expr_ptr)); }
#line 1534 "tools/parser.cpp"
    break;

  case 46: /* term: factor  */
#line 207 "assets/parser.bison"
                                     { (yyval.expr_ptr) = (yyvsp[0].expr_ptr); }
#line 1540 "tools/parser.cpp"
    break;

  case 47: /* term: call  */
#line 208 "assets/parser.bison"
                                     { (yyval.expr_ptr) = (yyvsp[0].expr_ptr); }
#line 1546 "tools/parser.cpp"
    break;

  case 48: /* call: TOKEN_ID TOKEN_LPAREN call_args TOKEN_RPAREN  */
#line 212 "assets/parser.bison"
                                                   { (yyval.expr_ptr) = expr_create(EXPR_CALL, expr_create_name(std::string((yyvsp[-3].expr_id))), (yyvsp[-1].expr_ptr)); }
#line 1552 "tools/parser.cpp"
    break;

  case 49: /* call_args: %empty  */
#line 216 "assets/parser.bison"
                                     { (yyval.expr_ptr) = nullptr; }
#line 1558 "tools/parser.cpp"
    break;

  case 50: /* call_args: expr  */
#line 217 "assets/parser.bison"
                                     { (yyval.expr_ptr) = expr_list_create((yyvsp[0].expr_ptr)); }
#line 1564 "tools/parser.cpp"
    break;

  case 51: /* call_args: call_args TOKEN_COMMA expr  */
#line 218 "assets/parser.bison"
                                     { (yyval.expr_ptr) = expr_list_append((yyvsp[-2].expr_ptr), (yyvsp[0].expr_ptr)); }
#line 1570 "tools/parser.cpp"
    break;

  case 52: /* factor: TOKEN_MINUS factor  */
#line 222 "assets/parser.bison"
                                     { (yyval.expr_ptr) = expr_create(EXPR_SUBTRACT, expr_create_integer_literal(0),(yyvsp[0].expr_ptr)); }
#line 1576 "tools/parser.cpp"
    break;

  case 53: /* factor: TOKEN_LPAREN expr TOKEN_RPAREN  */
#line 223 "assets/parser.bison"
                                     { (yyval.expr_ptr) = (yyvsp[-1].expr_ptr); }
#line 1582 "tools/parser.cpp"
    break;

  case 54: /* factor: TOKEN_TRUE  */
#line 224 "assets/parser.bison"
                                     { (yyval.expr_ptr) = expr_create_boolean_literal(true);}
#line 1588 "tools/parser.cpp"
    break;

  case 55: /* factor: TOKEN_FALSE  */
#line 225 "assets/parser.bison"
                                     { (yyval.expr_ptr) = expr_create_boolean_literal(false);}
#line 1594 "tools/parser.cpp"
    break;

  case 56: /* factor: TOKEN_STRING_LITERAL  */
#line 226 "assets/parser.bison"
                                     { (yyval.expr_ptr) = expr_create_string_literal(std::string(yytext)); }
#line 1600 "tools/parser.cpp"
    break;

  case 57: /* factor: TOKEN_INT  */
#line 227 "assets/parser.bison"
                                     { (yyval.expr_ptr) = expr_create_integer_literal(atoi(yytext)); }
#line 1606 "tools/parser.cpp"
    break;

  case 58: /* factor: TOKEN_ID  */
#line 228 "assets/parser.bison"
                                     { (yyval.expr_ptr) = expr_create_name(std::string((yyvsp[0].expr_id))); }
#line 1612 "tools/parser.cpp"
    break;


#line 1616 "tools/parser.cpp"

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

#line 229 "assets/parser.bison"


