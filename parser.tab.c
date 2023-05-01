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
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include "log.h"
    #include "parser.h"
    extern int yylex();
    extern void yyerror();


#line 81 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_RE_T = 3,                       /* RE_T  */
  YYSYMBOL_CE_T = 4,                       /* CE_T  */
  YYSYMBOL_LE_T = 5,                       /* LE_T  */
  YYSYMBOL_EE_T = 6,                       /* EE_T  */
  YYSYMBOL_FE_T = 7,                       /* FE_T  */
  YYSYMBOL_GE_T = 8,                       /* GE_T  */
  YYSYMBOL_HE_T = 9,                       /* HE_T  */
  YYSYMBOL_VE_T = 10,                      /* VE_T  */
  YYSYMBOL_IE_T = 11,                      /* IE_T  */
  YYSYMBOL_CVS_T = 12,                     /* CVS_T  */
  YYSYMBOL_INT_T = 13,                     /* INT_T  */
  YYSYMBOL_DEC_T = 14,                     /* DEC_T  */
  YYSYMBOL_PREF_T = 15,                    /* PREF_T  */
  YYSYMBOL_TS_T = 16,                      /* TS_T  */
  YYSYMBOL_DS_T = 17,                      /* DS_T  */
  YYSYMBOL_AS_T = 18,                      /* AS_T  */
  YYSYMBOL_G2_T = 19,                      /* G2_T  */
  YYSYMBOL_END_T = 20,                     /* END_T  */
  YYSYMBOL_DC_T = 21,                      /* DC_T  */
  YYSYMBOL_AC_T = 22,                      /* AC_T  */
  YYSYMBOL_SINE_T = 23,                    /* SINE_T  */
  YYSYMBOL_PULSE_T = 24,                   /* PULSE_T  */
  YYSYMBOL_RAMP_T = 25,                    /* RAMP_T  */
  YYSYMBOL_STEP_T = 26,                    /* STEP_T  */
  YYSYMBOL_27_n_ = 27,                     /* '\n'  */
  YYSYMBOL_28_ = 28,                       /* '('  */
  YYSYMBOL_29_ = 29,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 30,                  /* $accept  */
  YYSYMBOL_netlist = 31,                   /* netlist  */
  YYSYMBOL_statement = 32,                 /* statement  */
  YYSYMBOL_control = 33,                   /* control  */
  YYSYMBOL_element = 34,                   /* element  */
  YYSYMBOL_resistor = 35,                  /* resistor  */
  YYSYMBOL_capacitor = 36,                 /* capacitor  */
  YYSYMBOL_inductor = 37,                  /* inductor  */
  YYSYMBOL_current_source = 38,            /* current_source  */
  YYSYMBOL_voltage_source = 39,            /* voltage_source  */
  YYSYMBOL_voltage_controled_voltage_source = 40, /* voltage_controled_voltage_source  */
  YYSYMBOL_voltage_controled_current_source = 41, /* voltage_controled_current_source  */
  YYSYMBOL_current_controled_voltage_source = 42, /* current_controled_voltage_source  */
  YYSYMBOL_current_controled_current_source = 43, /* current_controled_current_source  */
  YYSYMBOL_dc = 44,                        /* dc  */
  YYSYMBOL_tran = 45,                      /* tran  */
  YYSYMBOL_value = 46                      /* value  */
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
typedef yytype_uint8 yy_state_t;

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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   127

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


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
      27,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,    29,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    26,    26,    27,    28,    30,    31,    32,    33,    34,
      38,    39,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    55,    62,    72,    79,    89,    99,   106,   113,   117,
     121,   125,   129,   133,   140,   147,   151,   155,   159,   163,
     170,   177,   184,   188,   192,   196,   200,   206,   216,   226,
     235,   244,   250,   255,   256,   257
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "RE_T", "CE_T", "LE_T",
  "EE_T", "FE_T", "GE_T", "HE_T", "VE_T", "IE_T", "CVS_T", "INT_T",
  "DEC_T", "PREF_T", "TS_T", "DS_T", "AS_T", "G2_T", "END_T", "DC_T",
  "AC_T", "SINE_T", "PULSE_T", "RAMP_T", "STEP_T", "'\\n'", "'('", "')'",
  "$accept", "netlist", "statement", "control", "element", "resistor",
  "capacitor", "inductor", "current_source", "voltage_source",
  "voltage_controled_voltage_source", "voltage_controled_current_source",
  "current_controled_voltage_source", "current_controled_current_source",
  "dc", "tran", "value", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-42)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -42,    88,   -42,    -6,    -5,    -4,    -3,     0,     2,     3,
       4,     5,   -11,   -42,   -42,   -42,   -42,   -13,     1,   -42,
     -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
       7,    13,    14,    18,    26,    28,    29,    35,    41,   -42,
      40,   -11,   -42,   -42,   -42,   -11,   -11,   -11,    43,    45,
      47,    50,    11,    96,   -42,   -42,    44,    51,   -42,    53,
     -11,    58,   -11,   -11,   -11,    48,    54,    55,    61,   -42,
     -11,   -11,    62,    72,    73,    74,    56,   -42,   -42,   -11,
     -42,   -11,   -42,   -42,   -11,   -11,   -11,   -11,   -11,    60,
     -11,   -11,   -11,   -11,   -11,   -42,   -42,   -42,   -42,   -11,
     -11,    77,   -11,   -42,    84,   -11,   -11,    78,   -11,   -11,
     -11,   -42,    82,   -42,   -11,   -11,    93,    85,   -11,   -11,
     -42,   -11,   -11,   -42,    94,   -11,   -11,   -11,   -11,   -42,
      87,    95,    97,    98,   -42,   -42,   104,   106,   -42,   -42
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     4,     9,     3,     0,     0,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    10,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
      54,     0,     7,     8,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,    52,    21,    23,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    40,
       0,     0,     0,     0,     0,     0,    26,    22,    24,     0,
      50,     0,    49,    41,     0,     0,     0,     0,     0,    27,
       0,     0,     0,     0,     0,    33,    47,    48,    42,     0,
       0,     0,     0,    34,    28,     0,     0,     0,     0,     0,
       0,    45,     0,    35,     0,     0,    31,     0,     0,     0,
      46,     0,     0,    38,    32,     0,     0,     0,     0,    39,
       0,     0,     0,     0,    43,    44,    29,    30,    36,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,   -42,   -41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    41
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,    43,    39,    40,    56,    57,    58,    30,    31,    32,
      33,    69,    76,    34,    42,    35,    36,    37,    38,    80,
      45,    82,    83,    84,    39,    40,    46,    47,    44,    89,
      90,    48,    63,    64,    65,    66,    67,    68,    96,    49,
      97,    50,    51,    98,    99,   100,   101,   102,    52,   104,
     105,   106,   107,   108,    53,    54,    59,    60,   109,   110,
      61,   112,    62,    77,   114,   115,    79,   117,   118,   119,
      78,    81,     0,   121,   122,    95,    85,   125,   126,   103,
     127,   128,    86,    87,   130,   131,   132,   133,     2,    88,
      91,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      92,    93,    94,   113,    12,    13,   111,   116,    14,    39,
      40,   120,   123,   129,   124,    15,   134,    70,    71,    72,
      73,    74,    75,   138,   135,   139,   136,   137
};

static const yytype_int16 yycheck[] =
{
      41,     0,    13,    14,    45,    46,    47,    13,    13,    13,
      13,    52,    53,    13,    27,    13,    13,    13,    13,    60,
      13,    62,    63,    64,    13,    14,    13,    13,    27,    70,
      71,    13,    21,    22,    23,    24,    25,    26,    79,    13,
      81,    13,    13,    84,    85,    86,    87,    88,    13,    90,
      91,    92,    93,    94,    13,    15,    13,    12,    99,   100,
      13,   102,    12,    19,   105,   106,    13,   108,   109,   110,
      19,    13,    -1,   114,   115,    19,    28,   118,   119,    19,
     121,   122,    28,    28,   125,   126,   127,   128,     0,    28,
      28,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      28,    28,    28,    19,    16,    17,    29,    29,    20,    13,
      14,    29,    19,    19,    29,    27,    29,    21,    22,    23,
      24,    25,    26,    19,    29,    19,    29,    29
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    31,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    16,    17,    20,    27,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      14,    46,    27,     0,    27,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    15,    46,    46,    46,    46,    13,
      12,    13,    12,    21,    22,    23,    24,    25,    26,    46,
      21,    22,    23,    24,    25,    26,    46,    19,    19,    13,
      46,    13,    46,    46,    46,    28,    28,    28,    28,    46,
      46,    28,    28,    28,    28,    19,    46,    46,    46,    46,
      46,    46,    46,    19,    46,    46,    46,    46,    46,    46,
      46,    29,    46,    19,    46,    46,    29,    46,    46,    46,
      29,    46,    46,    19,    29,    46,    46,    46,    46,    19,
      46,    46,    46,    46,    29,    29,    29,    29,    19,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    31,    31,    31,    32,    32,    32,    32,    32,
      33,    33,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    35,    35,    36,    36,    37,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      39,    39,    39,    39,    39,    39,    39,    40,    41,    42,
      43,    44,    45,    46,    46,    46
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     0,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     5,     4,     5,     4,     4,     5,     6,    11,
      11,     7,     8,     5,     6,     7,    12,    12,     8,     9,
       4,     5,     6,    11,    11,     7,     8,     6,     6,     5,
       5,     1,     3,     1,     1,     2
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 21: /* resistor: RE_T INT_T INT_T value  */
#line 55 "parser.y"
                             {
        add_node((yyvsp[-2].iv));
        add_node((yyvsp[-1].iv));
        add_RLC((yyvsp[-3].sv),(yyvsp[-2].iv),(yyvsp[-1].iv),(yyvsp[0].dv),1);
        log_trace("Resistor : %s ,node %d --> %d ,value = %.16f OHM.",(yyvsp[-3].sv),(yyvsp[-2].iv),(yyvsp[-1].iv),(yyvsp[0].dv));
        free((yyvsp[-3].sv));   //DeAllocating sv memory which we allocatd in lexer
    }
#line 1466 "parser.tab.c"
    break;

  case 22: /* resistor: RE_T INT_T INT_T value G2_T  */
#line 62 "parser.y"
                                  {
        add_node((yyvsp[-3].iv));
        add_node((yyvsp[-2].iv));
        add_RLC((yyvsp[-4].sv),(yyvsp[-3].iv),(yyvsp[-2].iv),(yyvsp[-1].dv),2);
        log_trace("Resistor : %s ,node %d --> %d ,value = %.16f OHM.",(yyvsp[-4].sv),(yyvsp[-3].iv),(yyvsp[-2].iv),(yyvsp[-1].dv));
        free((yyvsp[-4].sv));   //DeAllocating sv memory which we allocatd in lexer
    }
#line 1478 "parser.tab.c"
    break;

  case 23: /* capacitor: CE_T INT_T INT_T value  */
#line 72 "parser.y"
                             {
        add_node((yyvsp[-2].iv));
        add_node((yyvsp[-1].iv));
        add_RLC((yyvsp[-3].sv),(yyvsp[-2].iv),(yyvsp[-1].iv),(yyvsp[0].dv),1);
        log_trace("Capacitor : %s ,node %d --> %d ,value = %.16f FARAD.",(yyvsp[-3].sv),(yyvsp[-2].iv),(yyvsp[-1].iv),(yyvsp[0].dv));
        free((yyvsp[-3].sv));   //DeAllocating sv memory which we allocatd in lexer
    }
#line 1490 "parser.tab.c"
    break;

  case 24: /* capacitor: CE_T INT_T INT_T value G2_T  */
#line 79 "parser.y"
                                  {
        add_node((yyvsp[-3].iv));
        add_node((yyvsp[-2].iv));
        add_RLC((yyvsp[-4].sv),(yyvsp[-3].iv),(yyvsp[-2].iv),(yyvsp[-1].dv),2);
        log_trace("Capacitor : %s ,node %d --> %d ,value = %.16f FARAD.",(yyvsp[-4].sv),(yyvsp[-3].iv),(yyvsp[-2].iv),(yyvsp[-1].dv));
        free((yyvsp[-4].sv));   //DeAllocating sv memory which we allocatd in lexer
    }
#line 1502 "parser.tab.c"
    break;

  case 25: /* inductor: LE_T INT_T INT_T value  */
#line 89 "parser.y"
                             {
        add_node((yyvsp[-2].iv));
        add_node((yyvsp[-1].iv));
        add_RLC((yyvsp[-3].sv),(yyvsp[-2].iv),(yyvsp[-1].iv),(yyvsp[0].dv),2);
        log_trace("Inductor : %s ,node %d --> %d ,value = %.16f Henry.",(yyvsp[-3].sv),(yyvsp[-2].iv),(yyvsp[-1].iv),(yyvsp[0].dv));
        free((yyvsp[-3].sv));   //DeAllocating sv memory which we allocatd in lexer
    }
#line 1514 "parser.tab.c"
    break;

  case 26: /* current_source: IE_T INT_T INT_T value  */
#line 99 "parser.y"
                               {
            add_node((yyvsp[-2].iv));
            add_node((yyvsp[-1].iv));
            add_I((yyvsp[-3].sv),(yyvsp[-2].iv),(yyvsp[-1].iv),(yyvsp[0].dv),1);
            log_trace("DC Current Source : %s ,node %d --> %d ,value = %.16f A.",(yyvsp[-3].sv),(yyvsp[-2].iv),(yyvsp[-1].iv),(yyvsp[0].dv));
            free((yyvsp[-3].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1526 "parser.tab.c"
    break;

  case 27: /* current_source: IE_T INT_T INT_T DC_T value  */
#line 106 "parser.y"
                                    {
            add_node((yyvsp[-3].iv));
            add_node((yyvsp[-2].iv));
            add_I((yyvsp[-4].sv),(yyvsp[-3].iv),(yyvsp[-2].iv),(yyvsp[0].dv),1);
            log_trace("DC Current Source : %s ,node %d --> %d ,value = %.16f A.",(yyvsp[-4].sv),(yyvsp[-3].iv),(yyvsp[-2].iv),(yyvsp[0].dv));
            free((yyvsp[-4].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1538 "parser.tab.c"
    break;

  case 28: /* current_source: IE_T INT_T INT_T AC_T value value  */
#line 113 "parser.y"
                                          {
            log_trace("AC Current Source : %s ,node %d --> %d ,amp = %f A, phase = %f deg.",(yyvsp[-5].sv),(yyvsp[-4].iv),(yyvsp[-3].iv),(yyvsp[-1].dv),(yyvsp[0].dv));
            free((yyvsp[-5].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1547 "parser.tab.c"
    break;

  case 29: /* current_source: IE_T INT_T INT_T SINE_T '(' value value value value value ')'  */
#line 117 "parser.y"
                                                                      {
            log_trace("SINE Current Source : %s ,node %d --> %d ,freq = %f, amp = %f, offset = %f, phase = %f, delay = %f A.",(yyvsp[-10].sv),(yyvsp[-9].iv),(yyvsp[-8].iv),(yyvsp[-5].dv),(yyvsp[-4].dv),(yyvsp[-3].dv),(yyvsp[-2].dv),(yyvsp[-1].dv));
            free((yyvsp[-10].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1556 "parser.tab.c"
    break;

  case 30: /* current_source: IE_T INT_T INT_T PULSE_T '(' value value value value value ')'  */
#line 121 "parser.y"
                                                                       {
            log_trace("PULSE Current Source : %s ,node %d --> %d ,Voff = %f, Von = %f, Ton = %f, Tperiod = %f, delay = %f A.",(yyvsp[-10].sv),(yyvsp[-9].iv),(yyvsp[-8].iv),(yyvsp[-5].dv),(yyvsp[-4].dv),(yyvsp[-3].dv),(yyvsp[-2].dv),(yyvsp[-1].dv));
            free((yyvsp[-10].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1565 "parser.tab.c"
    break;

  case 31: /* current_source: IE_T INT_T INT_T RAMP_T '(' value ')'  */
#line 125 "parser.y"
                                              {
            log_trace("RAMP Current Source : %s ,node %d --> %d ,delay = %f s.",(yyvsp[-6].sv),(yyvsp[-5].iv),(yyvsp[-4].iv),(yyvsp[-1].dv));
            free((yyvsp[-6].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1574 "parser.tab.c"
    break;

  case 32: /* current_source: IE_T INT_T INT_T STEP_T '(' value value ')'  */
#line 129 "parser.y"
                                                    {
            log_trace("DC Current Source : %s ,node %d --> %d ,Von = %f A, delay = %f s.",(yyvsp[-7].sv),(yyvsp[-6].iv),(yyvsp[-5].iv),(yyvsp[-2].dv),(yyvsp[-1].dv));
            free((yyvsp[-7].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1583 "parser.tab.c"
    break;

  case 33: /* current_source: IE_T INT_T INT_T value G2_T  */
#line 133 "parser.y"
                                    {
            add_node((yyvsp[-3].iv));
            add_node((yyvsp[-2].iv));
            add_I((yyvsp[-4].sv),(yyvsp[-3].iv),(yyvsp[-2].iv),(yyvsp[-1].dv),2);
            log_trace("DC Current Source : %s ,node %d --> %d ,value = %.16f A.",(yyvsp[-4].sv),(yyvsp[-3].iv),(yyvsp[-2].iv),(yyvsp[-1].dv));
            free((yyvsp[-4].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1595 "parser.tab.c"
    break;

  case 34: /* current_source: IE_T INT_T INT_T DC_T value G2_T  */
#line 140 "parser.y"
                                         {
            add_node((yyvsp[-4].iv));
            add_node((yyvsp[-3].iv));
            add_I((yyvsp[-5].sv),(yyvsp[-4].iv),(yyvsp[-3].iv),(yyvsp[-1].dv),2);
            log_trace("DC Current Source : %s ,node %d --> %d ,value = %.16f A.",(yyvsp[-5].sv),(yyvsp[-4].iv),(yyvsp[-3].iv),(yyvsp[-1].dv));
            free((yyvsp[-5].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1607 "parser.tab.c"
    break;

  case 35: /* current_source: IE_T INT_T INT_T AC_T value value G2_T  */
#line 147 "parser.y"
                                               {
            log_trace("AC Current Source : %s ,node %d --> %d ,amp = %f A, phase = %f deg.",(yyvsp[-6].sv),(yyvsp[-5].iv),(yyvsp[-4].iv),(yyvsp[-2].dv),(yyvsp[-1].dv));
            free((yyvsp[-6].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1616 "parser.tab.c"
    break;

  case 36: /* current_source: IE_T INT_T INT_T SINE_T '(' value value value value value ')' G2_T  */
#line 151 "parser.y"
                                                                           {
            log_trace("SINE Current Source : %s ,node %d --> %d ,freq = %f, amp = %f, offset = %f, phase = %f, delay = %f A.",(yyvsp[-11].sv),(yyvsp[-10].iv),(yyvsp[-9].iv),(yyvsp[-6].dv),(yyvsp[-5].dv),(yyvsp[-4].dv),(yyvsp[-3].dv),(yyvsp[-2].dv));
            free((yyvsp[-11].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1625 "parser.tab.c"
    break;

  case 37: /* current_source: IE_T INT_T INT_T PULSE_T '(' value value value value value ')' G2_T  */
#line 155 "parser.y"
                                                                           {
            log_trace("PULSE Current Source : %s ,node %d --> %d ,Voff = %f, Von = %f, Ton = %f, Tperiod = %f, delay = %f A.",(yyvsp[-11].sv),(yyvsp[-10].iv),(yyvsp[-9].iv),(yyvsp[-6].dv),(yyvsp[-5].dv),(yyvsp[-4].dv),(yyvsp[-3].dv),(yyvsp[-2].dv));
            free((yyvsp[-11].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1634 "parser.tab.c"
    break;

  case 38: /* current_source: IE_T INT_T INT_T RAMP_T '(' value ')' G2_T  */
#line 159 "parser.y"
                                                   {
            log_trace("RAMP Current Source : %s ,node %d --> %d ,delay = %f s.",(yyvsp[-7].sv),(yyvsp[-6].iv),(yyvsp[-5].iv),(yyvsp[-2].dv));
            free((yyvsp[-7].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1643 "parser.tab.c"
    break;

  case 39: /* current_source: IE_T INT_T INT_T STEP_T '(' value value ')' G2_T  */
#line 163 "parser.y"
                                                         {
            log_trace("DC Current Source : %s ,node %d --> %d ,Von = %f A, delay = %f s.",(yyvsp[-8].sv),(yyvsp[-7].iv),(yyvsp[-6].iv),(yyvsp[-3].dv),(yyvsp[-2].dv));
            free((yyvsp[-8].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1652 "parser.tab.c"
    break;

  case 40: /* voltage_source: VE_T INT_T INT_T value  */
#line 170 "parser.y"
                               {
            add_node((yyvsp[-2].iv));
            add_node((yyvsp[-1].iv));
            add_V((yyvsp[-3].sv),(yyvsp[-2].iv),(yyvsp[-1].iv),(yyvsp[0].dv));
            log_trace("DC Voltage Source : %s ,node %d --> %d ,value = %.16f V.",(yyvsp[-3].sv),(yyvsp[-2].iv),(yyvsp[-1].iv),(yyvsp[0].dv));
            free((yyvsp[-3].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1664 "parser.tab.c"
    break;

  case 41: /* voltage_source: VE_T INT_T INT_T DC_T value  */
#line 177 "parser.y"
                                    {
            add_node((yyvsp[-3].iv));
            add_node((yyvsp[-2].iv));
            add_V((yyvsp[-4].sv),(yyvsp[-3].iv),(yyvsp[-2].iv),(yyvsp[0].dv));
            log_trace("DC Voltage Source : %s ,node %d --> %d ,value = %.16f V.",(yyvsp[-4].sv),(yyvsp[-3].iv),(yyvsp[-2].iv),(yyvsp[0].dv));
            free((yyvsp[-4].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1676 "parser.tab.c"
    break;

  case 42: /* voltage_source: VE_T INT_T INT_T AC_T value value  */
#line 184 "parser.y"
                                          {
            log_trace("AC Voltage Source : %s ,node %d --> %d ,amp = %f V, phase = %f deg.",(yyvsp[-5].sv),(yyvsp[-4].iv),(yyvsp[-3].iv),(yyvsp[-1].dv),(yyvsp[0].dv));
            free((yyvsp[-5].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1685 "parser.tab.c"
    break;

  case 43: /* voltage_source: VE_T INT_T INT_T SINE_T '(' value value value value value ')'  */
#line 188 "parser.y"
                                                                      {
            log_trace("SINE Voltage Source : %s ,node %d --> %d ,freq = %f, amp = %f, offset = %f, phase = %f, delay = %f V.",(yyvsp[-10].sv),(yyvsp[-9].iv),(yyvsp[-8].iv),(yyvsp[-5].dv),(yyvsp[-4].dv),(yyvsp[-3].dv),(yyvsp[-2].dv),(yyvsp[-1].dv));
            free((yyvsp[-10].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1694 "parser.tab.c"
    break;

  case 44: /* voltage_source: VE_T INT_T INT_T PULSE_T '(' value value value value value ')'  */
#line 192 "parser.y"
                                                                       {
            log_trace("PULSE Voltage Source : %s ,node %d --> %d ,Voff = %f, Von = %f, Ton = %f, Tperiod = %f, delay = %f V.",(yyvsp[-10].sv),(yyvsp[-9].iv),(yyvsp[-8].iv),(yyvsp[-5].dv),(yyvsp[-4].dv),(yyvsp[-3].dv),(yyvsp[-2].dv),(yyvsp[-1].dv));
            free((yyvsp[-10].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1703 "parser.tab.c"
    break;

  case 45: /* voltage_source: VE_T INT_T INT_T RAMP_T '(' value ')'  */
#line 196 "parser.y"
                                              {
            log_trace("RAMP Voltage Source : %s ,node %d --> %d ,delay = %f s.",(yyvsp[-6].sv),(yyvsp[-5].iv),(yyvsp[-4].iv),(yyvsp[-1].dv));
            free((yyvsp[-6].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1712 "parser.tab.c"
    break;

  case 46: /* voltage_source: VE_T INT_T INT_T STEP_T '(' value value ')'  */
#line 200 "parser.y"
                                                    {
            log_trace("DC Voltage Source : %s ,node %d --> %d ,Von = %f V, delay = %f s.",(yyvsp[-7].sv),(yyvsp[-6].iv),(yyvsp[-5].iv),(yyvsp[-2].dv),(yyvsp[-1].dv));
            free((yyvsp[-7].sv));   //DeAllocating sv memory which we allocatd in lexer
        }
#line 1721 "parser.tab.c"
    break;

  case 47: /* voltage_controled_voltage_source: EE_T INT_T INT_T INT_T INT_T value  */
#line 206 "parser.y"
                                       {
        add_node((yyvsp[-4].iv));
        add_node((yyvsp[-3].iv));
        add_node((yyvsp[-2].iv));
        add_node((yyvsp[-1].iv));
        add_VCVS((yyvsp[-5].sv), (yyvsp[-4].iv), (yyvsp[-3].iv), (yyvsp[-2].iv), (yyvsp[-1].iv), (yyvsp[0].dv), 2);
        log_trace("VCVS : %s ,control : %d --> %d ,out : %d --> %d ,value = %.16f",(yyvsp[-5].sv), (yyvsp[-4].iv), (yyvsp[-3].iv), (yyvsp[-2].iv), (yyvsp[-1].iv), (yyvsp[0].dv));
        free((yyvsp[-5].sv));
    }
#line 1735 "parser.tab.c"
    break;

  case 48: /* voltage_controled_current_source: GE_T INT_T INT_T INT_T INT_T value  */
#line 216 "parser.y"
                                       {
        add_node((yyvsp[-4].iv));
        add_node((yyvsp[-3].iv));
        add_node((yyvsp[-2].iv));
        add_node((yyvsp[-1].iv));
        add_VCCS((yyvsp[-5].sv), (yyvsp[-4].iv), (yyvsp[-3].iv), (yyvsp[-2].iv), (yyvsp[-1].iv), (yyvsp[0].dv), 1);
        log_trace("VCCS : %s ,control : %d --> %d ,out : %d --> %d ,value = %.16f",(yyvsp[-5].sv), (yyvsp[-4].iv), (yyvsp[-3].iv), (yyvsp[-2].iv), (yyvsp[-1].iv), (yyvsp[0].dv));
        free((yyvsp[-5].sv));
    }
#line 1749 "parser.tab.c"
    break;

  case 49: /* current_controled_voltage_source: HE_T INT_T INT_T CVS_T value  */
#line 226 "parser.y"
                                 {
        add_node((yyvsp[-3].iv));
        add_node((yyvsp[-2].iv));
        add_CCCS((yyvsp[-4].sv), (yyvsp[-1].sv), (yyvsp[-3].iv), (yyvsp[-2].iv), (yyvsp[0].dv), 2);
        log_trace("CCVS : %s ,control : %s ,out : %d --> %d ,value = %.16f",(yyvsp[-4].sv) ,(yyvsp[-1].sv) ,(yyvsp[-3].iv) ,(yyvsp[-2].iv) ,(yyvsp[0].dv));
        free((yyvsp[-4].sv));
        free((yyvsp[-1].sv));
    }
#line 1762 "parser.tab.c"
    break;

  case 50: /* current_controled_current_source: FE_T INT_T INT_T CVS_T value  */
#line 235 "parser.y"
                                 {
        add_node((yyvsp[-3].iv));
        add_node((yyvsp[-2].iv));
        add_CCCS((yyvsp[-4].sv), (yyvsp[-1].sv), (yyvsp[-3].iv), (yyvsp[-2].iv), (yyvsp[0].dv), 1);
        log_trace("CCCS : %s ,control : %s ,out : %d --> %d ,value = %.16f",(yyvsp[-4].sv) ,(yyvsp[-1].sv) ,(yyvsp[-3].iv) ,(yyvsp[-2].iv) ,(yyvsp[0].dv));
        free((yyvsp[-4].sv));
        free((yyvsp[-1].sv));
    }
#line 1775 "parser.tab.c"
    break;

  case 51: /* dc: DS_T  */
#line 244 "parser.y"
         {
        log_trace("DC Analysis Detected!");
        set_simultaor_dc();
    }
#line 1784 "parser.tab.c"
    break;

  case 52: /* tran: TS_T value value  */
#line 250 "parser.y"
                     {
        log_trace("Transient Analysis Detected!,stop time = %.16f, step = %.16f", (yyvsp[-1].dv), (yyvsp[0].dv));
        set_simultaor_tran((yyvsp[-1].dv), (yyvsp[0].dv));
    }
#line 1793 "parser.tab.c"
    break;

  case 53: /* value: INT_T  */
#line 255 "parser.y"
                    {(yyval.dv) = (double)(yyvsp[0].iv);}
#line 1799 "parser.tab.c"
    break;

  case 55: /* value: DEC_T PREF_T  */
#line 257 "parser.y"
                    {(yyval.dv) = (yyvsp[-1].dv) * (yyvsp[0].dv);}
#line 1805 "parser.tab.c"
    break;


#line 1809 "parser.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 259 "parser.y"
