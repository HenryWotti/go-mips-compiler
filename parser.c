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
#line 7 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "tables.h"
#include "parser.h"

int yylex(void);
int yylex_destroy(void);
void yyerror(char const *s);

void check_var();
void new_var();
int new_func();
void check_func_params();
void check_func();
void check_isArray(int idx, int line, char* name);
void check_isNotArray(int idx, int line);
void check_array_position_int(int line, Type postionType);
void check_array_type(Type array_Type, Type expressionType, int line);

extern char *yytext;
extern int yylineno;

Type id_type; //guarda o tipo do ID
Type id_type2; //guarda o tipo do ID
Type array_type; //gurda o tipo do Array
FuncTable *ft; //tabela de funções
StrTable *st; //tabela de strings
VarTable *vt; //tabela de variáveis
Type current_return_type; //guarda o atual tipo do retorno da função, caso ela tenha retorno
int current_scope = 0; //guarda o escopo da função, para diferencia-las tanto na tabela de função quantos suas variáveis na tabela de variáveis
int param_count = 0; //parametro visual passado em funções como 0, para dentro delas contarmos os parametros
int argument_count = 0; //conta o número de argumentos na chamada da função
int has_return = 0; //flag que é marcada caso a funcao não tenha void como retorno
int current_func_idx; //pega o index da funcao, para achar ela na function table e colocar os valores corretor de param_types, type e param_count
int func_idx; //pega o index da funcao
int idx;
int idx2;

Type arg_types[10]; //guarda os tipos de todos os argumentos chamados na chamada de uma função

char copied_id[128]; //copia o ultimo id visto
char copied_id_array[128]; //copia o ultimo id visto auxiliar para array
char copied_func_id[128]; //copia o ultimo id de funcao visto

Type last_decl_type; //tipo mais recente declarado

AST *ast_root = NULL;

#line 123 "parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FLOAT_TYPE_CAST = 3,            /* FLOAT_TYPE_CAST  */
  YYSYMBOL_INT_TYPE_CAST = 4,              /* INT_TYPE_CAST  */
  YYSYMBOL_STRING_VAL = 5,                 /* STRING_VAL  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_FOR = 7,                        /* FOR  */
  YYSYMBOL_FUNC = 8,                       /* FUNC  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_PACKAGE = 10,                   /* PACKAGE  */
  YYSYMBOL_IMPORT = 11,                    /* IMPORT  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_VAR = 13,                       /* VAR  */
  YYSYMBOL_INT_TYPE = 14,                  /* INT_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 15,                /* FLOAT_TYPE  */
  YYSYMBOL_STRING_TYPE = 16,               /* STRING_TYPE  */
  YYSYMBOL_VOID_TYPE = 17,                 /* VOID_TYPE  */
  YYSYMBOL_BOOL_TYPE = 18,                 /* BOOL_TYPE  */
  YYSYMBOL_PLUS_PLUS = 19,                 /* PLUS_PLUS  */
  YYSYMBOL_PLUS = 20,                      /* PLUS  */
  YYSYMBOL_MINUS_MINUS = 21,               /* MINUS_MINUS  */
  YYSYMBOL_MINUS = 22,                     /* MINUS  */
  YYSYMBOL_TIMES = 23,                     /* TIMES  */
  YYSYMBOL_OVER = 24,                      /* OVER  */
  YYSYMBOL_REST = 25,                      /* REST  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_EQUALS = 28,                    /* EQUALS  */
  YYSYMBOL_LESS_EQUAL = 29,                /* LESS_EQUAL  */
  YYSYMBOL_MORE_EQUAL = 30,                /* MORE_EQUAL  */
  YYSYMBOL_LESS = 31,                      /* LESS  */
  YYSYMBOL_MORE = 32,                      /* MORE  */
  YYSYMBOL_DIFERS = 33,                    /* DIFERS  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_LEFT_PARENTESES = 35,           /* LEFT_PARENTESES  */
  YYSYMBOL_RIGHT_PARENTESES = 36,          /* RIGHT_PARENTESES  */
  YYSYMBOL_LEFT_BRACKET = 37,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 38,             /* RIGHT_BRACKET  */
  YYSYMBOL_LEFT_BRACE = 39,                /* LEFT_BRACE  */
  YYSYMBOL_RIGHT_BRACE = 40,               /* RIGHT_BRACE  */
  YYSYMBOL_FLOAT_VAL = 41,                 /* FLOAT_VAL  */
  YYSYMBOL_INT_VAL = 42,                   /* INT_VAL  */
  YYSYMBOL_BOOL_VAL = 43,                  /* BOOL_VAL  */
  YYSYMBOL_ID = 44,                        /* ID  */
  YYSYMBOL_SHORT_ASSIGN = 45,              /* SHORT_ASSIGN  */
  YYSYMBOL_ASSIGN = 46,                    /* ASSIGN  */
  YYSYMBOL_SEMI = 47,                      /* SEMI  */
  YYSYMBOL_ADDRESS = 48,                   /* ADDRESS  */
  YYSYMBOL_COMMA = 49,                     /* COMMA  */
  YYSYMBOL_MAIN = 50,                      /* MAIN  */
  YYSYMBOL_PRINTLN = 51,                   /* PRINTLN  */
  YYSYMBOL_SCANF = 52,                     /* SCANF  */
  YYSYMBOL_FORMAT_STRING = 53,             /* FORMAT_STRING  */
  YYSYMBOL_FORMAT_INT = 54,                /* FORMAT_INT  */
  YYSYMBOL_FORMAT_FLOAT = 55,              /* FORMAT_FLOAT  */
  YYSYMBOL_FORMAT_BOOL = 56,               /* FORMAT_BOOL  */
  YYSYMBOL_IFX = 57,                       /* IFX  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_program = 59,                   /* program  */
  YYSYMBOL_package_declaration = 60,       /* package_declaration  */
  YYSYMBOL_import_declaration = 61,        /* import_declaration  */
  YYSYMBOL_62_1 = 62,                      /* $@1  */
  YYSYMBOL_func_main = 63,                 /* func_main  */
  YYSYMBOL_64_2 = 64,                      /* $@2  */
  YYSYMBOL_block = 65,                     /* block  */
  YYSYMBOL_list_func_generic = 66,         /* list_func_generic  */
  YYSYMBOL_func_generic = 67,              /* func_generic  */
  YYSYMBOL_68_3 = 68,                      /* $@3  */
  YYSYMBOL_69_4 = 69,                      /* $@4  */
  YYSYMBOL_argument_list = 70,             /* argument_list  */
  YYSYMBOL_71_5 = 71,                      /* $@5  */
  YYSYMBOL_return_statement = 72,          /* return_statement  */
  YYSYMBOL_statement_list = 73,            /* statement_list  */
  YYSYMBOL_statement = 74,                 /* statement  */
  YYSYMBOL_75_6 = 75,                      /* $@6  */
  YYSYMBOL_76_7 = 76,                      /* $@7  */
  YYSYMBOL_string_list = 77,               /* string_list  */
  YYSYMBOL_val_declaration = 78,           /* val_declaration  */
  YYSYMBOL_assign_val = 79,                /* assign_val  */
  YYSYMBOL_80_8 = 80,                      /* $@8  */
  YYSYMBOL_array_printable = 81,           /* array_printable  */
  YYSYMBOL_82_9 = 82,                      /* $@9  */
  YYSYMBOL_array_declaration = 83,         /* array_declaration  */
  YYSYMBOL_array_assign = 84,              /* array_assign  */
  YYSYMBOL_85_10 = 85,                     /* $@10  */
  YYSYMBOL_id_int_compression = 86,        /* id_int_compression  */
  YYSYMBOL_assign_expression = 87,         /* assign_expression  */
  YYSYMBOL_88_11 = 88,                     /* $@11  */
  YYSYMBOL_89_12 = 89,                     /* $@12  */
  YYSYMBOL_argument_list_call = 90,        /* argument_list_call  */
  YYSYMBOL_91_13 = 91,                     /* $@13  */
  YYSYMBOL_92_14 = 92,                     /* $@14  */
  YYSYMBOL_argument_val = 93,              /* argument_val  */
  YYSYMBOL_comma_expression = 94,          /* comma_expression  */
  YYSYMBOL_operator_expression = 95,       /* operator_expression  */
  YYSYMBOL_id_number_compression = 96,     /* id_number_compression  */
  YYSYMBOL_if_statement = 97,              /* if_statement  */
  YYSYMBOL_if_expression = 98,             /* if_expression  */
  YYSYMBOL_for_statement = 99,             /* for_statement  */
  YYSYMBOL_100_15 = 100,                   /* $@15  */
  YYSYMBOL_for_comparison = 101,           /* for_comparison  */
  YYSYMBOL_102_16 = 102,                   /* $@16  */
  YYSYMBOL_for_update = 103,               /* for_update  */
  YYSYMBOL_104_17 = 104,                   /* $@17  */
  YYSYMBOL_105_18 = 105,                   /* $@18  */
  YYSYMBOL_print_operation = 106,          /* print_operation  */
  YYSYMBOL_print_args = 107,               /* print_args  */
  YYSYMBOL_scanf_operation = 108,          /* scanf_operation  */
  YYSYMBOL_scan_args = 109,                /* scan_args  */
  YYSYMBOL_type_spec = 110,                /* type_spec  */
  YYSYMBOL_number_val_spec = 111,          /* number_val_spec  */
  YYSYMBOL_comparadors = 112,              /* comparadors  */
  YYSYMBOL_operators = 113                 /* operators  */
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
# define YYCOPY_NEEDED 1
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   247

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  246

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   127,   127,   133,   137,   138,   138,   142,   142,   148,
     154,   155,   159,   160,   159,   167,   168,   168,   172,   179,
     182,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   199,   207,   211,   220,   226,   226,   239,
     239,   251,   262,   262,   285,   290,   296,   297,   298,   299,
     308,   317,   319,   317,   327,   328,   328,   333,   333,   340,
     344,   347,   350,   356,   357,   361,   369,   383,   397,   411,
     425,   433,   441,   449,   460,   465,   466,   470,   473,   479,
     485,   489,   492,   499,   499,   526,   526,   535,   535,   548,
     548,   564,   570,   574,   575,   631,   637,   643,   649,   655,
     661,   668,   675,   682,   692,   693,   694,   695,   696,   700,
     701,   705,   706,   707,   708,   709,   710,   711,   715,   716,
     717,   718,   719
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
  "\"end of file\"", "error", "\"invalid token\"", "FLOAT_TYPE_CAST",
  "INT_TYPE_CAST", "STRING_VAL", "ELSE", "FOR", "FUNC", "IF", "PACKAGE",
  "IMPORT", "RETURN", "VAR", "INT_TYPE", "FLOAT_TYPE", "STRING_TYPE",
  "VOID_TYPE", "BOOL_TYPE", "PLUS_PLUS", "PLUS", "MINUS_MINUS", "MINUS",
  "TIMES", "OVER", "REST", "AND", "OR", "EQUALS", "LESS_EQUAL",
  "MORE_EQUAL", "LESS", "MORE", "DIFERS", "NOT", "LEFT_PARENTESES",
  "RIGHT_PARENTESES", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_BRACE",
  "RIGHT_BRACE", "FLOAT_VAL", "INT_VAL", "BOOL_VAL", "ID", "SHORT_ASSIGN",
  "ASSIGN", "SEMI", "ADDRESS", "COMMA", "MAIN", "PRINTLN", "SCANF",
  "FORMAT_STRING", "FORMAT_INT", "FORMAT_FLOAT", "FORMAT_BOOL", "IFX",
  "$accept", "program", "package_declaration", "import_declaration", "$@1",
  "func_main", "$@2", "block", "list_func_generic", "func_generic", "$@3",
  "$@4", "argument_list", "$@5", "return_statement", "statement_list",
  "statement", "$@6", "$@7", "string_list", "val_declaration",
  "assign_val", "$@8", "array_printable", "$@9", "array_declaration",
  "array_assign", "$@10", "id_int_compression", "assign_expression",
  "$@11", "$@12", "argument_list_call", "$@13", "$@14", "argument_val",
  "comma_expression", "operator_expression", "id_number_compression",
  "if_statement", "if_expression", "for_statement", "$@15",
  "for_comparison", "$@16", "for_update", "$@17", "$@18",
  "print_operation", "print_args", "scanf_operation", "scan_args",
  "type_spec", "number_val_spec", "comparadors", "operators", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-141)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-90)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,   -34,    26,    19,  -141,  -141,    38,  -141,  -141,    34,
      19,   -35,  -141,  -141,  -141,  -141,  -141,    27,    50,    15,
      55,   100,    60,    33,  -141,  -141,  -141,  -141,  -141,  -141,
     100,    12,  -141,    52,  -141,  -141,    29,    36,    24,    62,
      37,    72,   118,   110,     1,  -141,   120,   123,   124,   125,
     126,  -141,  -141,   127,   128,  -141,    15,    33,  -141,     5,
       5,  -141,  -141,   137,   138,   111,   104,    33,  -141,     5,
       5,  -141,   143,   120,  -141,  -141,   136,    20,   144,   134,
     145,    46,    94,  -141,  -141,  -141,   176,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,   139,  -141,   149,   150,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,     5,  -141,  -141,  -141,
    -141,  -141,     5,    51,   181,   152,   153,   155,   151,  -141,
      56,    24,    81,  -141,   156,  -141,  -141,   158,   142,   146,
     147,   148,   -29,  -141,   157,   136,   136,  -141,  -141,     5,
       5,  -141,    33,   136,   136,    56,   160,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,   163,   165,  -141,
     159,   161,   162,   164,  -141,   112,   166,    67,    78,   167,
     168,  -141,  -141,   100,    52,   169,    52,   170,    81,   171,
     173,   174,   175,   172,   177,   178,   179,   180,     5,     5,
    -141,     5,     5,  -141,  -141,  -141,   184,  -141,    56,   182,
      56,    24,   185,  -141,  -141,  -141,  -141,   183,   186,   187,
     188,  -141,   190,   189,   194,   196,   197,  -141,  -141,  -141,
    -141,  -141,  -141,   195,   198,   199,   200,   111,   201,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,     5,   193,    33,
    -141,   192,   217,  -141,  -141,  -141
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     4,     3,     1,     0,    10,     5,     0,
       4,     0,     2,    11,     6,    12,     7,     0,     0,    15,
       0,     0,     0,     0,   104,   106,   105,   108,   107,    16,
       0,     0,     8,    63,    13,    34,     0,     0,     0,     0,
      31,     0,     0,     0,     0,    19,    29,     0,     0,     0,
       0,    21,    22,     0,     0,    64,    15,     0,    83,     0,
       0,   110,   109,    76,    74,     0,     0,     0,    75,     0,
       0,    76,    74,    46,    18,    48,    47,     0,     0,     0,
       0,     0,     0,    30,     9,    20,     0,    24,    23,    25,
      26,    27,    28,    17,    14,     0,    74,     0,     0,   117,
     113,   114,   111,   112,   115,   116,     0,   118,   119,   120,
     121,   122,     0,     0,    77,     0,     0,     0,     0,    36,
      54,     0,     0,    92,    39,    94,    93,     0,     0,     0,
       0,     0,     0,    35,     0,     0,     0,    82,    81,     0,
       0,    65,     0,    50,    49,    54,     0,    59,    62,    61,
      60,    55,    32,    57,    38,    45,    44,     0,     0,    91,
       0,     0,     0,     0,    95,     0,     0,     0,     0,     0,
       0,    78,    52,     0,    63,     0,    63,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      68,     0,     0,    66,    69,    67,     0,    41,    54,     0,
      54,     0,     0,    96,    97,    98,    99,     0,     0,     0,
       0,    85,     0,     0,     0,     0,     0,    53,    56,    33,
      58,    43,    40,     0,     0,     0,     0,     0,     0,    73,
      71,    70,    72,   100,   101,   102,   103,     0,    87,     0,
      86,     0,     0,    84,    88,    90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -141,  -141,  -141,   212,  -141,  -141,  -141,   -56,  -141,  -141,
    -141,  -141,   191,  -141,  -141,  -141,   202,  -141,  -141,   -13,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,    28,  -117,
    -141,  -141,  -140,  -141,  -141,  -141,   -12,   203,   -37,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,   -27,  -141,   -64,   -31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     7,    10,    12,    18,    32,     9,    13,
      17,    57,    22,    33,    43,    44,    45,    78,   175,    73,
      47,    48,    79,   125,   158,    49,    50,    80,   157,    74,
     117,   196,   152,   174,   176,   153,    56,    75,    76,    51,
      67,    52,    95,   212,   227,   239,   241,   242,    53,   127,
      54,   132,    29,    68,   106,   113
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    94,   112,    34,   154,   172,    35,   164,    36,    15,
      37,   114,     1,    38,    39,    16,     4,    35,    46,    36,
     165,    37,    97,    98,    38,    39,     5,    69,    70,    35,
       6,    46,   115,   116,    24,    25,    26,    27,    28,    59,
      60,    84,    11,     8,   126,    40,    61,    62,    71,    96,
     119,   123,    41,    42,   139,   140,    40,   118,   218,    21,
     220,   147,    19,    41,    42,    61,    62,    71,    72,   137,
     188,   189,    31,    58,   -42,   138,   141,    61,    62,    63,
      64,   191,   192,   -37,   221,    20,   171,    61,    62,    71,
     124,    23,    61,    62,    71,    96,    30,   148,   149,   150,
     151,    55,   169,   170,   167,   168,    77,    81,    61,    62,
      71,    96,   167,   168,    24,    25,    26,    27,    28,    61,
      62,    71,    96,   155,   107,   156,   108,   109,   110,   111,
     190,   193,    99,   100,   101,   102,   103,   104,   105,    99,
     100,   101,   102,   103,   104,   105,   197,   128,   129,   130,
     131,   213,   214,    82,   215,   216,   107,    83,   108,   109,
     110,   111,   198,   237,   200,   183,   184,   185,   186,    86,
      87,    88,    89,    90,    91,    92,   -80,   -79,   -51,   120,
     121,   133,   122,   243,   134,   135,   136,   142,   143,   144,
     145,   160,   -74,   146,   159,   161,   162,   163,   173,   166,
     240,   177,   178,   194,   195,   199,   202,   179,     0,   180,
     181,   244,   182,   187,   -89,   203,   201,   204,   205,   206,
     217,   207,    14,   222,   211,   229,   208,   209,   210,   219,
     230,   223,   231,   232,   224,   225,   226,   228,   245,   233,
      65,     0,   234,   235,   236,   238,    85,    93
};

static const yytype_int16 yycheck[] =
{
      37,    57,    66,    30,   121,   145,     5,    36,     7,    44,
       9,    67,    10,    12,    13,    50,    50,     5,    31,     7,
      49,     9,    59,    60,    12,    13,     0,     3,     4,     5,
      11,    44,    69,    70,    14,    15,    16,    17,    18,     3,
       4,    40,     8,     5,    81,    44,    41,    42,    43,    44,
      77,     5,    51,    52,     3,     4,    44,    37,   198,    44,
     200,     5,    35,    51,    52,    41,    42,    43,    44,   106,
       3,     4,    39,    44,    37,   112,   113,    41,    42,    43,
      44,     3,     4,    46,   201,    35,   142,    41,    42,    43,
      44,    36,    41,    42,    43,    44,    36,    41,    42,    43,
      44,    49,   139,   140,   135,   136,    44,    35,    41,    42,
      43,    44,   143,   144,    14,    15,    16,    17,    18,    41,
      42,    43,    44,    42,    20,    44,    22,    23,    24,    25,
     167,   168,    28,    29,    30,    31,    32,    33,    34,    28,
      29,    30,    31,    32,    33,    34,   173,    53,    54,    55,
      56,   188,   189,    35,   191,   192,    20,    47,    22,    23,
      24,    25,   174,   227,   176,    53,    54,    55,    56,    49,
      47,    47,    47,    47,    47,    47,    39,    39,    35,    35,
      46,     5,    37,   239,    45,    36,    36,     6,    36,    36,
      35,    49,    36,    42,    36,    49,    49,    49,    38,    42,
     237,    38,    37,    36,    36,    36,   178,    48,    -1,    48,
      48,    19,    48,    47,    21,    44,    46,    44,    44,    44,
      36,    49,    10,    38,    44,    36,    49,    49,    49,    47,
      36,    48,    36,    36,    48,    48,    48,    47,    21,    44,
      37,    -1,    44,    44,    44,    44,    44,    56
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    59,    60,    50,     0,    11,    61,     5,    66,
      62,     8,    63,    67,    61,    44,    50,    68,    64,    35,
      35,    44,    70,    36,    14,    15,    16,    17,    18,   110,
      36,    39,    65,    71,   110,     5,     7,     9,    12,    13,
      44,    51,    52,    72,    73,    74,    77,    78,    79,    83,
      84,    97,    99,   106,   108,    49,    94,    69,    44,     3,
       4,    41,    42,    43,    44,    95,    96,    98,   111,     3,
       4,    43,    44,    77,    87,    95,    96,    44,    75,    80,
      85,    35,    35,    47,    40,    74,    49,    47,    47,    47,
      47,    47,    47,    70,    65,   100,    44,    96,    96,    28,
      29,    30,    31,    32,    33,    34,   112,    20,    22,    23,
      24,    25,   112,   113,    65,    96,    96,    88,    37,   110,
      35,    46,    37,     5,    44,    81,    96,   107,    53,    54,
      55,    56,   109,     5,    45,    36,    36,    96,    96,     3,
       4,    96,     6,    36,    36,    35,    42,     5,    41,    42,
      43,    44,    90,    93,    87,    42,    44,    86,    82,    36,
      49,    49,    49,    49,    36,    49,    42,   113,   113,    96,
      96,    65,    90,    38,    91,    76,    92,    38,    37,    48,
      48,    48,    48,    53,    54,    55,    56,    47,     3,     4,
      96,     3,     4,    96,    36,    36,    89,   110,    94,    36,
      94,    46,    86,    44,    44,    44,    44,    49,    49,    49,
      49,    44,   101,    96,    96,    96,    96,    36,    90,    47,
      90,    87,    38,    48,    48,    48,    48,   102,    47,    36,
      36,    36,    36,    44,    44,    44,    44,   112,    44,   103,
      96,   104,   105,    65,    19,    21
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    60,    61,    62,    61,    64,    63,    65,
      66,    66,    68,    69,    67,    70,    71,    70,    72,    73,
      73,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    76,    74,    77,    77,    78,    80,    79,    82,
      81,    83,    85,    84,    86,    86,    87,    87,    87,    87,
      87,    88,    89,    87,    90,    91,    90,    92,    90,    93,
      93,    93,    93,    94,    94,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    96,    96,    96,    97,    97,    98,
      98,    98,    98,   100,    99,   102,   101,   104,   103,   105,
     103,   106,   107,   107,   107,   108,   109,   109,   109,   109,
     109,   109,   109,   109,   110,   110,   110,   110,   110,   111,
     111,   112,   112,   112,   112,   112,   112,   112,   113,   113,
     113,   113,   113
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     2,     0,     0,     4,     0,     6,     3,
       0,     2,     0,     0,     9,     0,     0,     5,     2,     1,
       2,     1,     1,     2,     2,     2,     2,     2,     2,     1,
       2,     0,     0,     7,     1,     3,     3,     0,     4,     0,
       5,     6,     0,     7,     1,     1,     1,     1,     1,     3,
       3,     0,     0,     6,     0,     0,     4,     0,     4,     1,
       1,     1,     1,     0,     1,     3,     5,     5,     5,     5,
       7,     7,     7,     7,     1,     1,     1,     3,     5,     1,
       1,     3,     3,     0,    10,     0,     4,     0,     3,     0,
       3,     4,     1,     1,     1,     4,     4,     4,     4,     4,
       6,     6,     6,     6,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
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
        YY_LAC_DISCARD ("YYBACKUP");                              \
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


/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return YYENOMEM if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                                \
do {                                                                    \
  if (!yy_lac_established)                                              \
    {                                                                   \
      YYDPRINTF ((stderr,                                               \
                  "LAC: initial context established for %s\n",          \
                  yysymbol_name (yytoken)));                            \
      yy_lac_established = 1;                                           \
      switch (yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken))    \
        {                                                               \
        case YYENOMEM:                                                  \
          YYNOMEM;                                                      \
        case 1:                                                         \
          goto yyerrlab;                                                \
        }                                                               \
    }                                                                   \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      YYDPRINTF ((stderr, "LAC: initial context discarded due to "       \
                  Event "\n"));                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return YYENOMEM if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, yysymbol_kind_t yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  /* Reduce until we encounter a shift and thereby accept the token.  */
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yysymbol_name (yytoken)));
  if (yytoken == YYSYMBOL_YYUNDEF)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          /* Use the default action.  */
          yyrule = yydefact[+*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          /* Use the action from yytable.  */
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      /* By now we know we have to simulate a reduce.  */
      YYDPRINTF ((stderr, " R%d", yyrule - 1));
      {
        /* Pop the corresponding number of values from the stack.  */
        YYPTRDIFF_T yylen = yyr2[yyrule];
        /* First pop from the LAC stack as many tokens as possible.  */
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yyesp = yyes_prev;
                yylen -= yysize;
              }
          }
        /* Only afterwards look at the main stack.  */
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      /* Push the resulting state of the reduction.  */
      {
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return YYENOMEM;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}

/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yy_state_t *yyesa;
  yy_state_t **yyes;
  YYPTRDIFF_T *yyes_capacity;
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

  int yyx;
  for (yyx = 0; yyx < YYNTOKENS; ++yyx)
    {
      yysymbol_kind_t yysym = YY_CAST (yysymbol_kind_t, yyx);
      if (yysym != YYSYMBOL_YYerror && yysym != YYSYMBOL_YYUNDEF)
        switch (yy_lac (yyctx->yyesa, yyctx->yyes, yyctx->yyes_capacity, yyctx->yyssp, yysym))
          {
          case YYENOMEM:
            return YYENOMEM;
          case 1:
            continue;
          default:
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
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
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else if (yyn == 0)
        YYDPRINTF ((stderr, "No expected tokens.\n"));
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store or if
   yy_lac returned YYENOMEM.  */
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

    yy_state_t yyesa[20];
    yy_state_t *yyes = yyesa;
    YYPTRDIFF_T yyes_capacity = 20 < YYMAXDEPTH ? 20 : YYMAXDEPTH;

  /* Whether LAC context is established.  A Boolean.  */
  int yy_lac_established = 0;
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
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      YY_LAC_ESTABLISH;
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
  YY_LAC_DISCARD ("shift");
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
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2: /* program: package_declaration import_declaration list_func_generic func_main  */
#line 127 "parser.y"
                                                                     {
    ast_root = yyvsp[0];  // Atribui a raiz da AST
  }
#line 1910 "parser.c"
    break;

  case 5: /* $@1: %empty  */
#line 138 "parser.y"
                    { add_string(st, yytext); }
#line 1916 "parser.c"
    break;

  case 7: /* $@2: %empty  */
#line 142 "parser.y"
            { current_scope++; }
#line 1922 "parser.c"
    break;

  case 8: /* func_main: FUNC MAIN $@2 LEFT_PARENTESES RIGHT_PARENTESES block  */
#line 142 "parser.y"
                                                                        {
    yyval = new_subtree(MAIN_NODE, VOID_TYPE_, 1, yyvsp[0]);
  }
#line 1930 "parser.c"
    break;

  case 9: /* block: LEFT_BRACE statement_list RIGHT_BRACE  */
#line 148 "parser.y"
                                        {
    yyval = new_subtree(BLOCK_NODE, VOID_TYPE_, 1, yyvsp[-1]);
  }
#line 1938 "parser.c"
    break;

  case 12: /* $@3: %empty  */
#line 159 "parser.y"
          { strcpy(copied_func_id, copied_id); current_scope++; current_func_idx = new_func();
  }
#line 1945 "parser.c"
    break;

  case 13: /* $@4: %empty  */
#line 160 "parser.y"
                                                             { update_func_return_type(ft, current_func_idx, last_decl_type); current_return_type=last_decl_type;
  }
#line 1952 "parser.c"
    break;

  case 14: /* func_generic: FUNC ID $@3 LEFT_PARENTESES argument_list RIGHT_PARENTESES type_spec $@4 block  */
#line 161 "parser.y"
          { 
    has_return = 0;
  }
#line 1960 "parser.c"
    break;

  case 16: /* $@5: %empty  */
#line 168 "parser.y"
               { new_var(); add_param_type(ft, current_func_idx, last_decl_type, yylineno);}
#line 1966 "parser.c"
    break;

  case 18: /* return_statement: RETURN assign_expression  */
#line 172 "parser.y"
                           { 
    check_return_type(yylineno, current_return_type, get_node_type(yyvsp[0]), 1);
    has_return = 1; // Indicar que um return foi encontrado
  }
#line 1975 "parser.c"
    break;

  case 19: /* statement_list: statement  */
#line 179 "parser.y"
            {
    yyval = new_subtree(STATEMANT_LIST, VOID_TYPE_, 1, yyvsp[0]); 
  }
#line 1983 "parser.c"
    break;

  case 20: /* statement_list: statement_list statement  */
#line 182 "parser.y"
                           {
      add_child(yyvsp[-1], yyvsp[0]); 
      yyval = yyvsp[-1];
  }
#line 1992 "parser.c"
    break;

  case 31: /* $@6: %empty  */
#line 199 "parser.y"
     { strcpy(copied_func_id, copied_id); check_func(); func_idx = lookup_func(ft, copied_func_id);
}
#line 1999 "parser.c"
    break;

  case 32: /* $@7: %empty  */
#line 200 "parser.y"
                                     { check_func_params(); check_function_argument_types(ft, func_idx, arg_types, argument_count, yylineno); argument_count = 0; 
}
#line 2006 "parser.c"
    break;

  case 33: /* statement: ID $@6 LEFT_PARENTESES argument_list_call $@7 RIGHT_PARENTESES SEMI  */
#line 201 "parser.y"
                        {
  yyval = new_subtree(FUNC_CALL_NODE, get_type_from_func(yylineno, copied_func_id), 1, new_node(VAR_USE_NODE, func_idx, get_type_from_func(yylineno, copied_func_id)));
}
#line 2014 "parser.c"
    break;

  case 34: /* string_list: STRING_VAL  */
#line 207 "parser.y"
             {
    int str_index = add_string(st, yytext);
    yyval = new_node(STR_VAL_NODE, str_index, STRING_TYPE_);  // Cria um nó da AST para a string
  }
#line 2023 "parser.c"
    break;

  case 35: /* string_list: string_list COMMA STRING_VAL  */
#line 211 "parser.y"
                              {
    int str_index = add_string(st, yytext);
    AST *str_node = new_node(STR_VAL_NODE, str_index, STRING_TYPE_);  // Cria um nó para a nova string
    add_child(yyvsp[-2], str_node);  // Adiciona a nova string como filha da lista existente
    yyval = yyvsp[-2];  // A lista é retornada
}
#line 2034 "parser.c"
    break;

  case 36: /* val_declaration: VAR ID type_spec  */
#line 220 "parser.y"
                   { new_var();
  yyval = new_node(VAR_DECL_NODE, lookup_var(vt, copied_id, current_scope), last_decl_type);
  }
#line 2042 "parser.c"
    break;

  case 37: /* $@8: %empty  */
#line 226 "parser.y"
      { 
        check_var(); 
        id_type2 = get_type_from_var(yylineno, copied_id, current_scope);
        idx2 = lookup_var(vt, copied_id, current_scope);
        check_isArray(idx2, yylineno, copied_id);
      }
#line 2053 "parser.c"
    break;

  case 38: /* assign_val: ID $@8 ASSIGN assign_expression  */
#line 231 "parser.y"
                                 {
        check_assignment_type(yylineno, id_type2, get_node_type(yyvsp[0]));
        yyval = new_subtree(ASSIGN_NODE, VOID_TYPE_, 2, new_node(VAR_USE_NODE, idx2, id_type2), yyvsp[0]);
      }
#line 2062 "parser.c"
    break;

  case 39: /* $@9: %empty  */
#line 239 "parser.y"
     { 
      check_var(); 
      strcpy(copied_id_array, copied_id);
      //$$ = new_node(VAR_USE_NODE, var_idx, get_type_from_var(yylineno, copied_id, current_scope)); 
  }
#line 2072 "parser.c"
    break;

  case 40: /* array_printable: ID $@9 LEFT_BRACKET id_int_compression RIGHT_BRACKET  */
#line 244 "parser.y"
                                                {
    check_array_position_int(yylineno, get_node_type(yyvsp[-1]));
    yyval = new_subtree(ARRAY_ACCESS_NODE, get_type_from_var(yylineno, copied_id_array, current_scope), 2, new_node(VAR_USE_NODE, lookup_var(vt, copied_id_array, current_scope), get_type_from_var(yylineno, copied_id_array, current_scope)), yyvsp[-1]);
  }
#line 2081 "parser.c"
    break;

  case 41: /* array_declaration: VAR ID LEFT_BRACKET INT_VAL RIGHT_BRACKET type_spec  */
#line 251 "parser.y"
                                                      { 
      new_var();
      idx = lookup_var(vt, copied_id, current_scope); 
      set_isArray_by_idx(vt, idx, 1);
      check_array_position_int(yylineno, INT_TYPE_); // O índice é do tipo INT
      //$$ = new_node(ARRAY_DECL_NODE, idx, last_decl_type);
      yyval = new_subtree(ARRAY_DECL_NODE, get_type_from_var(yylineno, copied_id, current_scope), 2, new_node(VAR_DECL_NODE, idx, last_decl_type), new_node_int(INT_VAL_NODE, get_data(yyvsp[-2]), INT_TYPE_));
  }
#line 2094 "parser.c"
    break;

  case 42: /* $@10: %empty  */
#line 262 "parser.y"
     { 
      check_var(); 
      array_type = get_type_from_var(yylineno, copied_id, current_scope);
      idx2 = lookup_var(vt, copied_id, current_scope);
      check_isNotArray(idx2, yylineno);  
  }
#line 2105 "parser.c"
    break;

  case 43: /* array_assign: ID $@10 LEFT_BRACKET id_int_compression RIGHT_BRACKET ASSIGN assign_expression  */
#line 268 "parser.y"
                                                                         {
    // Verifica se a posição do array é um inteiro
    check_array_position_int(yylineno, get_node_type(yyvsp[-3]));
    
    // Verifica se o tipo do valor atribuído é compatível com o tipo do array
    check_array_type(array_type, get_node_type(yyvsp[0]), yylineno);

    // Cria o nó de acesso ao array
    //Node* array_access_node = new_subtree(ARRAY_ACCESS_NODE, array_type, 2, $1, $4); 

    // Cria a subárvore para a atribuição
    yyval = new_subtree(ASSIGN_NODE, VOID_TYPE_, 2, new_subtree(ARRAY_ACCESS_NODE, array_type, 2, new_node(VAR_DECL_NODE, idx2, array_type), yyvsp[-3]), yyvsp[0]);
  }
#line 2123 "parser.c"
    break;

  case 44: /* id_int_compression: ID  */
#line 285 "parser.y"
     { 
      check_var(); 
      int var_idx = lookup_var(vt, copied_id, current_scope); 
      yyval = new_node(VAR_USE_NODE, var_idx, get_type_from_var(yylineno, copied_id, current_scope)); 
  }
#line 2133 "parser.c"
    break;

  case 45: /* id_int_compression: INT_VAL  */
#line 290 "parser.y"
          { 
      yyval = yyvsp[0];
  }
#line 2141 "parser.c"
    break;

  case 46: /* assign_expression: string_list  */
#line 296 "parser.y"
              { yyval = yyvsp[0]; }
#line 2147 "parser.c"
    break;

  case 47: /* assign_expression: id_number_compression  */
#line 297 "parser.y"
                        { yyval = yyvsp[0]; }
#line 2153 "parser.c"
    break;

  case 48: /* assign_expression: operator_expression  */
#line 298 "parser.y"
                      { yyval = yyvsp[0]; }
#line 2159 "parser.c"
    break;

  case 49: /* assign_expression: INT_TYPE_CAST id_number_compression RIGHT_PARENTESES  */
#line 299 "parser.y"
                                                       {
    if (get_node_type(yyvsp[-1]) == FLOAT_TYPE_) {
        yyval = new_subtree(F2I_NODE, INT_TYPE_, 1, yyvsp[-1]);
        printf("Line(%d): Converting 'float32' to 'int'\n", yylineno);
    } else {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'int'.\n", yylineno, get_text(get_node_type(yyvsp[-1])));
        exit(EXIT_FAILURE);
    }
}
#line 2173 "parser.c"
    break;

  case 50: /* assign_expression: FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES  */
#line 308 "parser.y"
                                                         {
    if (get_node_type(yyvsp[-1]) == INT_TYPE_) {
        yyval = new_subtree(I2F_NODE, FLOAT_TYPE_, 1, yyvsp[-1]);
        printf("Line(%d): Converting 'int' to 'float32'\n", yylineno);
    } else {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'float32'.\n", yylineno,get_text(get_node_type(yyvsp[-1])));
        exit(EXIT_FAILURE);
    }
}
#line 2187 "parser.c"
    break;

  case 51: /* $@11: %empty  */
#line 317 "parser.y"
     {
    strcpy(copied_func_id, copied_id); check_func(); func_idx = lookup_func(ft, copied_func_id);
  }
#line 2195 "parser.c"
    break;

  case 52: /* $@12: %empty  */
#line 319 "parser.y"
                                       { 
      check_func_params(); check_function_argument_types(ft, func_idx, arg_types, argument_count, yylineno); argument_count = 0; 
    }
#line 2203 "parser.c"
    break;

  case 53: /* assign_expression: ID $@11 LEFT_PARENTESES argument_list_call $@12 RIGHT_PARENTESES  */
#line 321 "parser.y"
                       {
        yyval = new_subtree(FUNC_CALL_NODE, get_type_from_func(yylineno, copied_func_id), 1, new_node(VAR_USE_NODE, func_idx, get_type_from_func(yylineno, copied_func_id)));
      }
#line 2211 "parser.c"
    break;

  case 55: /* $@13: %empty  */
#line 328 "parser.y"
     { 
    check_var(); 
    arg_types[argument_count] = get_type_from_var(yylineno, copied_id, current_scope); 
    argument_count++; 
}
#line 2221 "parser.c"
    break;

  case 57: /* $@14: %empty  */
#line 333 "parser.y"
               { 
    arg_types[argument_count] = get_node_type(yyvsp[0]); 
    argument_count++; 
}
#line 2230 "parser.c"
    break;

  case 59: /* argument_val: STRING_VAL  */
#line 340 "parser.y"
             { 
      int str_index = add_string(st, yytext);
      yyval = new_node(STR_VAL_NODE, str_index, STRING_TYPE_);
  }
#line 2239 "parser.c"
    break;

  case 60: /* argument_val: BOOL_VAL  */
#line 344 "parser.y"
           { 
      yyval = yyvsp[0];
  }
#line 2247 "parser.c"
    break;

  case 61: /* argument_val: INT_VAL  */
#line 347 "parser.y"
          { 
      yyval = yyvsp[0];
  }
#line 2255 "parser.c"
    break;

  case 62: /* argument_val: FLOAT_VAL  */
#line 350 "parser.y"
            { 
      yyval = yyvsp[0];
  }
#line 2263 "parser.c"
    break;

  case 65: /* operator_expression: id_number_compression operators id_number_compression  */
#line 361 "parser.y"
                                                        {
    if (get_node_type(yyvsp[-2]) == get_node_type(yyvsp[0])) {
      yyval = new_subtree(get_kind(yyvsp[-1]), get_node_type(yyvsp[-2]), 2, yyvsp[-2], yyvsp[0]);
    } else {
      printf("SEMANTIC ERROR (%d): Incompatible types '%s' and '%s' for operator\n", yylineno, get_text(get_node_type(yyvsp[-2])), get_text(get_node_type(yyvsp[0])));
      exit(EXIT_FAILURE);
    }
}
#line 2276 "parser.c"
    break;

  case 66: /* operator_expression: INT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators id_number_compression  */
#line 369 "parser.y"
                                                                                       {
    if (get_node_type(yyvsp[-3]) != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'int'.\n", yylineno, get_text(get_node_type(yyvsp[-3])));
        exit(EXIT_FAILURE);
    }
    if(get_node_type(yyvsp[0]) == FLOAT_TYPE_ || get_node_type(yyvsp[0]) == BOOL_TYPE_ || get_node_type(yyvsp[0]) == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types 'int' and '%s' for operator\n", yylineno, get_text(get_node_type(yyvsp[0])));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'float32' to 'int'\n", yylineno);
      //new_node(F2I_NODE, INT_TYPE_, 1, $2)
      yyval = new_subtree(get_kind(yyvsp[-1]), INT_TYPE_, 2, new_subtree(F2I_NODE, INT_TYPE_, 1, yyvsp[-3]), yyvsp[0]);
    }
}
#line 2295 "parser.c"
    break;

  case 67: /* operator_expression: id_number_compression operators INT_TYPE_CAST id_number_compression RIGHT_PARENTESES  */
#line 383 "parser.y"
                                                                                       {
    if (get_node_type(yyvsp[-1]) != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'int'.\n", yylineno, get_text(get_node_type(yyvsp[-1])));
        exit(EXIT_FAILURE);
    }
    if(get_node_type(yyvsp[-4]) == FLOAT_TYPE_ || get_node_type(yyvsp[-4]) == BOOL_TYPE_ || get_node_type(yyvsp[-4]) == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types '%s' and 'int' for operator\n", yylineno, get_text(get_node_type(yyvsp[-4])));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'float32' to 'int'\n", yylineno);
      //$$ = new_subtree(F2I_NODE, INT_TYPE_, 2, $1, $4);
      yyval = new_subtree(get_kind(yyvsp[-3]), INT_TYPE_, 2, yyvsp[-4], new_subtree(F2I_NODE, INT_TYPE_, 1, yyvsp[-1]));
    }
}
#line 2314 "parser.c"
    break;

  case 68: /* operator_expression: FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators id_number_compression  */
#line 397 "parser.y"
                                                                                         {
    if (get_node_type(yyvsp[-3]) != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'float32'.\n", yylineno, get_text(get_node_type(yyvsp[-3])));
        exit(EXIT_FAILURE);
    }
    if(get_node_type(yyvsp[0]) == INT_TYPE_ || get_node_type(yyvsp[0]) == BOOL_TYPE_ || get_node_type(yyvsp[0]) == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types 'float32' and '%s' for operator\n", yylineno, get_text(get_node_type(yyvsp[0])));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'int' to 'float32'\n", yylineno);
      //$$ = new_subtree(I2F_NODE, FLOAT_TYPE_, 2, $2, $5);
      yyval = new_subtree(get_kind(yyvsp[-1]), FLOAT_TYPE_, 2, new_subtree(I2F_NODE, FLOAT_TYPE_, 1, yyvsp[-3]), yyvsp[0]);
    }
}
#line 2333 "parser.c"
    break;

  case 69: /* operator_expression: id_number_compression operators FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES  */
#line 411 "parser.y"
                                                                                         {
    if (get_node_type(yyvsp[-1]) != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'float32'.\n", yylineno, get_text(get_node_type(yyvsp[-1])));
        exit(EXIT_FAILURE);
    }
    if(get_node_type(yyvsp[-4]) == INT_TYPE_ || get_node_type(yyvsp[-4]) == BOOL_TYPE_ || get_node_type(yyvsp[-4]) == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types '%s' and 'float32' for operator\n", yylineno, get_text(get_node_type(yyvsp[-4])));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'int' to 'float32'\n", yylineno);
      //$$ = new_subtree(I2F_NODE, FLOAT_TYPE_, 2, $1, $4);
      yyval = new_subtree(get_kind(yyvsp[-3]), FLOAT_TYPE_, 2, yyvsp[-4], new_subtree(I2F_NODE, FLOAT_TYPE_, 1, yyvsp[-1]));
    }
}
#line 2352 "parser.c"
    break;

  case 70: /* operator_expression: INT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES  */
#line 425 "parser.y"
                                                                                                                        {
    if (get_node_type(yyvsp[-5]) != FLOAT_TYPE_ || get_node_type(yyvsp[-1]) != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    printf("SEMANTIC ERROR (%d): Incompatible types '%s' and '%s' for operator\n", yylineno, get_text(get_node_type(yyvsp[-5])), get_text(get_node_type(yyvsp[-1])));
    exit(EXIT_FAILURE);
}
#line 2365 "parser.c"
    break;

  case 71: /* operator_expression: FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators INT_TYPE_CAST id_number_compression RIGHT_PARENTESES  */
#line 433 "parser.y"
                                                                                                                        {
    if (get_node_type(yyvsp[-5]) != INT_TYPE_ || get_node_type(yyvsp[-1]) != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    printf("SEMANTIC ERROR (%d): Incompatible types '%s' and '%s' for operator\n", yylineno, get_text(get_node_type(yyvsp[-5])), get_text(get_node_type(yyvsp[-1])));
    exit(EXIT_FAILURE);
}
#line 2378 "parser.c"
    break;

  case 72: /* operator_expression: INT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators INT_TYPE_CAST id_number_compression RIGHT_PARENTESES  */
#line 441 "parser.y"
                                                                                                                      {
    if (get_node_type(yyvsp[-5]) != FLOAT_TYPE_ || get_node_type(yyvsp[-1]) != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    //$$ = new_subtree(F2I_NODE, INT_TYPE_, 2, $2, $6);
    yyval = new_subtree(get_kind(yyvsp[-3]), INT_TYPE_, 2, new_subtree(I2F_NODE, INT_TYPE_, 1, yyvsp[-5]), new_subtree(I2F_NODE, INT_TYPE_, 1, yyvsp[-1]));
}
#line 2391 "parser.c"
    break;

  case 73: /* operator_expression: FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES  */
#line 449 "parser.y"
                                                                                                                          {
    if (get_node_type(yyvsp[-5]) != INT_TYPE_ || get_node_type(yyvsp[-1]) != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    //$$ = new_subtree(I2F_NODE, FLOAT_TYPE_, 2, $2, $6);
    yyval = new_subtree(get_kind(yyvsp[-3]), FLOAT_TYPE_, 2, new_subtree(I2F_NODE, FLOAT_TYPE_, 1, yyvsp[-5]), new_subtree(I2F_NODE, FLOAT_TYPE_, 1, yyvsp[-1]));
}
#line 2404 "parser.c"
    break;

  case 74: /* id_number_compression: ID  */
#line 460 "parser.y"
      { check_var(); 
        idx = lookup_var(vt, copied_id, current_scope);
        check_isArray(idx, yylineno, copied_id);
        yyval = new_node(VAR_USE_NODE, idx, get_type_from_var(yylineno, copied_id, current_scope));
      }
#line 2414 "parser.c"
    break;

  case 75: /* id_number_compression: number_val_spec  */
#line 465 "parser.y"
                  { yyval = yyvsp[0]; }
#line 2420 "parser.c"
    break;

  case 76: /* id_number_compression: BOOL_VAL  */
#line 466 "parser.y"
           { yyval = yyvsp[0]; }
#line 2426 "parser.c"
    break;

  case 77: /* if_statement: IF if_expression block  */
#line 470 "parser.y"
                                   { 
      yyval = new_subtree(IF_NODE, VOID_TYPE_, 2, yyvsp[-1], yyvsp[0]);
  }
#line 2434 "parser.c"
    break;

  case 78: /* if_statement: IF if_expression block ELSE block  */
#line 473 "parser.y"
                                    { 
      yyval = new_subtree(IF_NODE, VOID_TYPE_, 3, yyvsp[-3], yyvsp[-2], yyvsp[0]);
  }
#line 2442 "parser.c"
    break;

  case 79: /* if_expression: ID  */
#line 479 "parser.y"
     { 
      check_var(); 
      Type expr_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_conditional_type(yylineno, expr_type, "if"); 
      yyval = new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), expr_type); 
  }
#line 2453 "parser.c"
    break;

  case 80: /* if_expression: BOOL_VAL  */
#line 485 "parser.y"
           { 
      check_conditional_type(yylineno, BOOL_TYPE_, "if");
      yyval = yyvsp[0]; // Como o BOOL_VAL já é um nó, simplesmente atribuímos $1 a $$.
  }
#line 2462 "parser.c"
    break;

  case 81: /* if_expression: id_number_compression comparadors id_number_compression  */
#line 489 "parser.y"
                                                          { 
      yyval = new_subtree(get_kind(yyvsp[-1]), VOID_TYPE_, 2, yyvsp[-2], yyvsp[0]); 
  }
#line 2470 "parser.c"
    break;

  case 82: /* if_expression: operator_expression comparadors id_number_compression  */
#line 492 "parser.y"
                                                        { 
      yyval = new_subtree(get_kind(yyvsp[-1]), VOID_TYPE_, 2, yyvsp[-2], yyvsp[0]);
  }
#line 2478 "parser.c"
    break;

  case 83: /* $@15: %empty  */
#line 499 "parser.y"
         { 
      last_decl_type = INT_TYPE_; 
      new_var(); 
  }
#line 2487 "parser.c"
    break;

  case 84: /* for_statement: FOR ID $@15 SHORT_ASSIGN INT_VAL SEMI for_comparison SEMI for_update block  */
#line 502 "parser.y"
                                                                   {
      // $2: ID (variável), $4: SHORT_ASSIGN, $5: INT_VAL, $6: SEMI, $7: for_comparison, $8: SEMI, $9: for_update, $10: block

      // Inicialização: ID := INT_VAL
      AST *init_node = new_subtree(SHORT_ASSIGN_NODE, VOID_TYPE_, 2, 
                                   new_node(VAR_DECL_NODE, lookup_var(vt, copied_id, current_scope), INT_TYPE_), 
                                   new_node_int(INT_VAL_NODE, get_data(yyvsp[-5]), INT_TYPE_));

      // Condição de continuação do loop (e.g., i < 5)
      AST *cond_node = yyvsp[-3]; 

      // Atualização (e.g., i++)
      AST *update_node = yyvsp[-1]; 

      // Bloco do loop
      AST *body_node = yyvsp[0];

      // Nó principal do loop for
      yyval = new_subtree(FOR_NODE, VOID_TYPE_, 4, init_node, cond_node, update_node, body_node);
  }
#line 2512 "parser.c"
    break;

  case 85: /* $@16: %empty  */
#line 526 "parser.y"
     { 
      check_var();
  }
#line 2520 "parser.c"
    break;

  case 86: /* for_comparison: ID $@16 comparadors id_number_compression  */
#line 528 "parser.y"
                                      {
      // Cria o nó de comparação entre a variável e a expressão
      yyval = new_subtree(get_kind(yyvsp[-1]), VOID_TYPE_, 2, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), yyvsp[0]);
  }
#line 2529 "parser.c"
    break;

  case 87: /* $@17: %empty  */
#line 535 "parser.y"
     { 
      check_var(); 
  }
#line 2537 "parser.c"
    break;

  case 88: /* for_update: ID $@17 PLUS_PLUS  */
#line 537 "parser.y"
              {
      // Cria um nó para a operação de incremento (i + 1)
      AST *increment_node = new_subtree(PLUS_NODE, INT_TYPE_, 2, 
                              new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), 
                              new_node_int(INT_VAL_NODE, 1, INT_TYPE_));
                              
      // Cria um nó para a atribuição (i = i + 1)
      yyval = new_subtree(ASSIGN_NODE, VOID_TYPE_, 2, 
            new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), 
            increment_node);
  }
#line 2553 "parser.c"
    break;

  case 89: /* $@18: %empty  */
#line 548 "parser.y"
     { 
      check_var(); 
  }
#line 2561 "parser.c"
    break;

  case 90: /* for_update: ID $@18 MINUS_MINUS  */
#line 550 "parser.y"
                {
      // Cria um nó para a operação de incremento (i + 1)
      AST *increment_node = new_subtree(MINUS_NODE, INT_TYPE_, 2, 
                              new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), 
                              new_node_int(INT_VAL_NODE, 1, INT_TYPE_));
                              
      // Cria um nó para a atribuição (i = i + 1)
      yyval = new_subtree(ASSIGN_NODE, VOID_TYPE_, 2, 
            new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), 
            increment_node);
  }
#line 2577 "parser.c"
    break;

  case 91: /* print_operation: PRINTLN LEFT_PARENTESES print_args RIGHT_PARENTESES  */
#line 564 "parser.y"
                                                        {
        yyval = new_subtree(WRITE_NODE, VOID_TYPE_, 1, yyvsp[-1]);  // Cria um nó WRITE_NODE na AST
    }
#line 2585 "parser.c"
    break;

  case 92: /* print_args: STRING_VAL  */
#line 570 "parser.y"
             {
      int str_index = add_string(st, yytext);
      yyval = new_node(STR_VAL_NODE, str_index, STRING_TYPE_);
  }
#line 2594 "parser.c"
    break;

  case 93: /* print_args: id_number_compression  */
#line 574 "parser.y"
                        { yyval = yyvsp[0]; }
#line 2600 "parser.c"
    break;

  case 94: /* print_args: array_printable  */
#line 575 "parser.y"
                  { yyval = yyvsp[0]; }
#line 2606 "parser.c"
    break;

  case 95: /* scanf_operation: SCANF LEFT_PARENTESES scan_args RIGHT_PARENTESES  */
#line 631 "parser.y"
                                                     {
        yyval = yyvsp[-1];
    }
#line 2614 "parser.c"
    break;

  case 96: /* scan_args: FORMAT_STRING COMMA ADDRESS ID  */
#line 637 "parser.y"
                                 { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, STRING_TYPE_, "%s"); 
      yyval = new_subtree(READ_NODE, STRING_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
#line 2625 "parser.c"
    break;

  case 97: /* scan_args: FORMAT_INT COMMA ADDRESS ID  */
#line 643 "parser.y"
                              { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, INT_TYPE_, "%d"); 
      yyval = new_subtree(READ_NODE, INT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
#line 2636 "parser.c"
    break;

  case 98: /* scan_args: FORMAT_FLOAT COMMA ADDRESS ID  */
#line 649 "parser.y"
                                { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, FLOAT_TYPE_, "%g"); 
      yyval = new_subtree(READ_NODE, FLOAT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
#line 2647 "parser.c"
    break;

  case 99: /* scan_args: FORMAT_BOOL COMMA ADDRESS ID  */
#line 655 "parser.y"
                               { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, BOOL_TYPE_, "%t"); 
      yyval = new_subtree(READ_NODE, BOOL_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
#line 2658 "parser.c"
    break;

  case 100: /* scan_args: scan_args COMMA FORMAT_STRING COMMA ADDRESS ID  */
#line 661 "parser.y"
                                                 { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, STRING_TYPE_, "%s"); 
      add_child(yyvsp[-5], new_subtree(READ_NODE, STRING_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      yyval = yyvsp[-5];
  }
#line 2670 "parser.c"
    break;

  case 101: /* scan_args: scan_args COMMA FORMAT_INT COMMA ADDRESS ID  */
#line 668 "parser.y"
                                              { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, INT_TYPE_, "%d"); 
      add_child(yyvsp[-5], new_subtree(READ_NODE, INT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      yyval = yyvsp[-5];
  }
#line 2682 "parser.c"
    break;

  case 102: /* scan_args: scan_args COMMA FORMAT_FLOAT COMMA ADDRESS ID  */
#line 675 "parser.y"
                                                { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, FLOAT_TYPE_, "%g"); 
      add_child(yyvsp[-5], new_subtree(READ_NODE, FLOAT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      yyval = yyvsp[-5];
  }
#line 2694 "parser.c"
    break;

  case 103: /* scan_args: scan_args COMMA FORMAT_BOOL COMMA ADDRESS ID  */
#line 682 "parser.y"
                                               { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, BOOL_TYPE_, "%t"); 
      add_child(yyvsp[-5], new_subtree(READ_NODE, BOOL_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      yyval = yyvsp[-5];
  }
#line 2706 "parser.c"
    break;

  case 104: /* type_spec: INT_TYPE  */
#line 692 "parser.y"
              { last_decl_type = INT_TYPE_; }
#line 2712 "parser.c"
    break;

  case 105: /* type_spec: STRING_TYPE  */
#line 693 "parser.y"
              { last_decl_type = STRING_TYPE_; }
#line 2718 "parser.c"
    break;

  case 106: /* type_spec: FLOAT_TYPE  */
#line 694 "parser.y"
              { last_decl_type = FLOAT_TYPE_; }
#line 2724 "parser.c"
    break;

  case 107: /* type_spec: BOOL_TYPE  */
#line 695 "parser.y"
              { last_decl_type = BOOL_TYPE_; }
#line 2730 "parser.c"
    break;

  case 108: /* type_spec: VOID_TYPE  */
#line 696 "parser.y"
              { last_decl_type = VOID_TYPE_; }
#line 2736 "parser.c"
    break;

  case 109: /* number_val_spec: INT_VAL  */
#line 700 "parser.y"
          { yyval = yyvsp[0]; }
#line 2742 "parser.c"
    break;

  case 110: /* number_val_spec: FLOAT_VAL  */
#line 701 "parser.y"
            { yyval = yyvsp[0]; }
#line 2748 "parser.c"
    break;

  case 111: /* comparadors: LESS  */
#line 705 "parser.y"
       { yyval = new_node(LESS_NODE, 0, VOID_TYPE_); }
#line 2754 "parser.c"
    break;

  case 112: /* comparadors: MORE  */
#line 706 "parser.y"
       { yyval = new_node(MORE_NODE, 0, VOID_TYPE_); }
#line 2760 "parser.c"
    break;

  case 113: /* comparadors: LESS_EQUAL  */
#line 707 "parser.y"
             { yyval = new_node(LESS_EQUAL_NODE, 0, VOID_TYPE_); }
#line 2766 "parser.c"
    break;

  case 114: /* comparadors: MORE_EQUAL  */
#line 708 "parser.y"
             { yyval = new_node(MORE_EQUAL_NODE, 0, VOID_TYPE_); }
#line 2772 "parser.c"
    break;

  case 115: /* comparadors: DIFERS  */
#line 709 "parser.y"
         { yyval = new_node(DIFERS_NODE, 0, VOID_TYPE_); }
#line 2778 "parser.c"
    break;

  case 116: /* comparadors: NOT  */
#line 710 "parser.y"
      { yyval = new_node(NOT_NODE, 0, VOID_TYPE_); }
#line 2784 "parser.c"
    break;

  case 117: /* comparadors: EQUALS  */
#line 711 "parser.y"
         { yyval = new_node(EQUALS_NODE, 0, VOID_TYPE_); }
#line 2790 "parser.c"
    break;

  case 118: /* operators: PLUS  */
#line 715 "parser.y"
       { yyval = new_node(PLUS_NODE, 0, VOID_TYPE_); }
#line 2796 "parser.c"
    break;

  case 119: /* operators: MINUS  */
#line 716 "parser.y"
        { yyval = new_node(MINUS_NODE, 0, VOID_TYPE_); }
#line 2802 "parser.c"
    break;

  case 120: /* operators: TIMES  */
#line 717 "parser.y"
        { yyval = new_node(TIMES_NODE, 0, VOID_TYPE_); }
#line 2808 "parser.c"
    break;

  case 121: /* operators: OVER  */
#line 718 "parser.y"
       { yyval = new_node(OVER_NODE, 0, VOID_TYPE_); }
#line 2814 "parser.c"
    break;

  case 122: /* operators: REST  */
#line 719 "parser.y"
       { yyval = new_node(REST_NODE, 0, VOID_TYPE_); }
#line 2820 "parser.c"
    break;


#line 2824 "parser.c"

        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
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
          = {yyssp, yyesa, &yyes, &yyes_capacity, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
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

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

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
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 722 "parser.y"


void check_array_type(Type array_type, Type expression_type, int line) {
    if (array_type == INT_TYPE_ && expression_type != INT_TYPE_) {
        if (expression_type == FLOAT_TYPE_) {
            printf("SEMANTIC ERROR (%d): cannot assign 'float32' to 'int' array without explicit cast.\n", line);
            exit(EXIT_FAILURE);
        } else {
            printf("SEMANTIC ERROR (%d): Incompatible type assignment to 'int' array.\n", line);
            exit(EXIT_FAILURE);
        }
    } else if (array_type == FLOAT_TYPE_ && expression_type != FLOAT_TYPE_) {
        if (expression_type == INT_TYPE_) {
            printf("SEMANTIC ERROR (%d): cannot assign 'int' to 'float32' array without explicit cast.\n", line);
            exit(EXIT_FAILURE);
        } else {
            printf("SEMANTIC ERROR (%d): Incompatible type assignment to 'float32' array.\n", line);
            exit(EXIT_FAILURE);
        }
    }
}


void check_isNotArray(int idx, int line) {
  if (!get_isArray(vt, idx)) {
    printf("SEMANTIC ERROR (%d): Expected array variable.\n", line);
    exit(EXIT_FAILURE);
  } 
}

void check_array_position_int(int line, Type postionType){
  if(postionType != INT_TYPE_){
      printf("SEMANTIC ERROR (%d): it is only allowed to access the array position with integers.\n", line);
      exit(EXIT_FAILURE);
    }
}

void check_isArray(int idx, int line, char* name) {
  if (get_isArray(vt, idx)) {
    printf("SEMANTIC ERROR (%d): Array variable '%s' used without index.\n", line, name);
    exit(EXIT_FAILURE);
  }
}
        

Type get_type_from_func(int line, char *name) {
    int idx = lookup_func(ft, name);
    if (idx == -1) {
        printf("SEMANTIC ERROR (%d): function '%s' was not declared.\n", line, name);
        exit(EXIT_FAILURE);
    }
    return get_func_type(ft, idx);
}

Type get_type_from_var(int line, char *name, int current_scope2) {
    int idx = lookup_var(vt, name, current_scope2);
    if (idx == -1) {
        printf("SEMANTIC ERROR (%d): variable '%s' was not declared.\n", line, name);
        exit(EXIT_FAILURE);
    }
    return get_type(vt, idx);
}


void check_var() {
    /*printf("DEBUG: Checking variable %s at line %d, scope %d\n", copied_id, yylineno, current_scope);*/
    int idx = lookup_var(vt, copied_id, current_scope);
    if (idx == -1) {
        idx = lookup_func_in_scope(ft, copied_id, current_scope);
        if (idx == -1) {
            printf("SEMANTIC ERROR (%d): variable '%s' was not declared.\n",
                   yylineno, copied_id);
            exit(EXIT_FAILURE);
        }
    }
}

void check_func() {
    /*printf("DEBUG: Checking function %s at line %d, scope %d\n", copied_func_id, yylineno, current_scope);*/
    int idx = lookup_var(vt, copied_func_id, current_scope);
    if (idx == -1) {
        idx = lookup_func_in_scope(ft, copied_func_id, current_scope);
        if (idx == -1) {
            printf("SEMANTIC ERROR (%d): function '%s' was not declared.\n",
                   yylineno, copied_func_id);
            exit(EXIT_FAILURE);
        }
    }
}

void check_func_params() {
    /*printf("DEBUG: Checking function %s parameters at line %d, scope %d\n", copied_func_id, yylineno, current_scope);*/
    int idx = lookup_func_in_scope(ft, copied_func_id, current_scope);
    if (idx == -1) {
        printf("SEMANTIC ERROR (%d): function '%s' was not declared.\n",
               yylineno, copied_func_id);
        exit(EXIT_FAILURE);
    }
    int expected_params = get_func_param_count(ft, idx);
    if (expected_params != argument_count) {
        printf("SEMANTIC ERROR (%d): function '%s' expects %d parameters, but %d were provided.\n",
               yylineno, copied_func_id, expected_params, argument_count);
        exit(EXIT_FAILURE);
    }
}

void new_var() {
    /*printf("DEBUG: Adding new_var %s at line %d, scope %d\n", copied_id, yylineno, current_scope);*/
    int idx = lookup_var(vt, copied_id, current_scope);
    if (idx != -1) {
        printf("SEMANTIC ERROR (%d): variable '%s' already declared at line %d.\n",
                yylineno, copied_id, get_line(vt, idx));
        exit(EXIT_FAILURE);
    }
    add_var(vt, copied_id, yylineno, last_decl_type, current_scope);
}

int new_func() {
    /*printf("DEBUG: Adding new_func %s at line %d, scope %d\n", copied_func_id, yylineno, current_scope);*/
    int idx = lookup_func(ft, copied_func_id);
    if (idx != -1) {
        printf("SEMANTIC ERROR (%d): function '%s' already declared at line %d.\n",
                yylineno, copied_func_id, get_func_line(ft, idx));
        exit(EXIT_FAILURE);
    }
    return add_func(ft, copied_func_id, yylineno, last_decl_type, current_scope, param_count);
}

void yyerror (char const *s) {
    printf("SYNTAX ERROR (%d): %s\n", yylineno, s);
    exit(EXIT_FAILURE);
}

int main() {
    st = create_str_table();
    vt = create_var_table(); // Tabela de variáveis global
    ft = create_func_table(); // Tabela de funções

    yyparse();
    printf("PARSE SUCCESSFUL!\n");

    if (ast_root != NULL) {
        print_dot(ast_root);  // Imprime a AST no formato .dot
    }

    printf("\n\n");
    print_str_table(st); printf("\n\n");
    print_var_table(vt); printf("\n\n"); // Print the entire variable table
    print_func_table(ft); // Print the functions table

    free_str_table(st);
    free_var_table(vt); // Free the variable table
    free_func_table(ft); // Free the functions table
    yylex_destroy(); // To avoid memory leaks within flex...

    return 0;
}
