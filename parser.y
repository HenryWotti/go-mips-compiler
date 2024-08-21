%output "parser.c"
%defines "parser.h"
%define parse.error verbose
%define parse.lac full

%{
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

Type arg_types[10]; //guarda os tipos de todos os argumentos chamados na chamada de uma função

char copied_id[128]; //copia o ultimo id visto
char copied_func_id[128]; //copia o ultimo id de funcao visto

Type last_decl_type; //tipo mais recente declarado
%}

%token FLOAT_TYPE_CAST
%token INT_TYPE_CAST
%token STRING_VAL
%token ELSE
%token FOR
%token FUNC
%token IF
%token PACKAGE
%token IMPORT
%token RETURN
%token VAR
%token INT_TYPE
%token FLOAT_TYPE
%token STRING_TYPE
%token VOID_TYPE
%token BOOL_TYPE
%token PLUS_PLUS
%token PLUS
%token MINUS_MINUS
%token MINUS
%token TIMES
%token OVER
%token REST
%token AND
%token OR
%token EQUALS
%token LESS_EQUAL
%token MORE_EQUAL
%token LESS
%token MORE
%token DIFERS
%token NOT
%token LEFT_PARENTESES
%token RIGHT_PARENTESES
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_BRACE
%token RIGHT_BRACE
%token FLOAT_VAL
%token INT_VAL
%token BOOL_VAL
%token ID
%token SHORT_ASSIGN
%token ASSIGN
%token SEMI
%token ADDRESS
%token COMMA
%token MAIN
%token PRINTLN
%token SCANF
%token FORMAT_STRING
%token FORMAT_INT
%token FORMAT_FLOAT
%token FORMAT_BOOL

%left EQUALS DIFERS LESS LESS_EQUAL MORE MORE_EQUAL
%left PLUS MINUS
%left TIMES OVER REST
%left ASSIGN SHORT_ASSIGN ADDRESS
%left AND OR NOT
%nonassoc IFX
%nonassoc ELSE

%start program

%%

program:
  package_declaration import_declaration list_func_generic func_main 
;

package_declaration:
  PACKAGE MAIN
;

import_declaration:
  %empty
| IMPORT STRING_VAL import_declaration
;

func_main :
  FUNC MAIN { current_scope++; } LEFT_PARENTESES RIGHT_PARENTESES block
;

block :
  LEFT_BRACE statement_list RIGHT_BRACE
;

list_func_generic:
  %empty
| list_func_generic func_generic
;

func_generic:
  FUNC ID { strcpy(copied_func_id, copied_id); current_scope++; current_func_idx = new_func();
  } LEFT_PARENTESES argument_list RIGHT_PARENTESES type_spec { update_func_return_type(ft, current_func_idx, last_decl_type); current_return_type=last_decl_type;
  } block { 
    has_return = 0;
  }
;

argument_list:
  %empty
| ID type_spec { new_var(); add_param_type(ft, current_func_idx, last_decl_type, yylineno);} comma_expression argument_list
;

return_statement:
  RETURN assign_expression { 
    check_return_type(yylineno, current_return_type, $2, 1);
    has_return = 1; // Indicar que um return foi encontrado
  }
;

statement_list:
  statement
| statement_list statement
;

statement:
  if_statement
| for_statement
| assign_val SEMI
| val_declaration SEMI
| array_declaration SEMI
| array_assign SEMI
| print_operation SEMI
| scanf_operation SEMI
| string_list
| return_statement SEMI
| ID { strcpy(copied_func_id, copied_id); check_func(); func_idx = lookup_func(ft, copied_func_id);
} LEFT_PARENTESES argument_list_call { check_func_params(); check_function_argument_types(ft, func_idx, arg_types, argument_count, yylineno); argument_count = 0; 
} RIGHT_PARENTESES SEMI { $$ = get_type_from_func(yylineno, copied_func_id);
} //FUNCTION CALL
;

string_list: 
  STRING_VAL { $$ = STRING_TYPE_; }
| string_list COMMA STRING_VAL
;

val_declaration :
  VAR ID type_spec { new_var(); }
;

assign_val :
  ID  { 
        check_var(); 
        id_type = get_type_from_var(yylineno, copied_id, current_scope);
        int idx = lookup_var(vt, copied_id, current_scope);
        check_isArray(idx, yylineno, copied_id);
      } ASSIGN assign_expression {
        check_assignment_type(yylineno, id_type, $4);
      }
;

array_printable:
  ID { check_var(); $$ = get_type_from_var(yylineno, copied_id, current_scope); } LEFT_BRACKET id_int_compression RIGHT_BRACKET{
    check_array_position_int(yylineno, $4);
  }
;

array_declaration :
  VAR ID LEFT_BRACKET INT_VAL { $$ = INT_TYPE_; } RIGHT_BRACKET type_spec { new_var(); int idx = lookup_var(vt, copied_id, current_scope); set_isArray_by_idx(vt, idx, 1);
    check_array_position_int(yylineno, $4);
  }
;

array_assign :
  ID { check_var(); 
        array_type = get_type_from_var(yylineno, copied_id, current_scope);
        int idx = lookup_var(vt, copied_id, current_scope);
        check_isNotArray(idx, yylineno);
      } LEFT_BRACKET id_int_compression RIGHT_BRACKET ASSIGN assign_expression {
        check_array_position_int(yylineno, $4);
        check_array_type(array_type, $7, yylineno);
  }
;

id_int_compression:
  ID { check_var(); $$ = get_type_from_var(yylineno, copied_id, current_scope); }
| INT_VAL { $$ = INT_TYPE_; }
;

assign_expression :
  STRING_VAL { $$ = STRING_TYPE_; }
| id_number_compression { $$ = $1; }
| operator_expression { $$ = $1; }
| INT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if ($2 == FLOAT_TYPE_) {
        $$ = INT_TYPE_;
        printf("Line(%d): Converting 'float32' to 'int'\n", yylineno);
    } else {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'int'.\n", yylineno, get_text($2));
        exit(EXIT_FAILURE);
    }
}
| FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if ($2 == INT_TYPE_) {
        $$ = FLOAT_TYPE_;
        printf("Line(%d): Converting 'int' to 'float32'\n", yylineno);
    } else {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'float32'.\n", yylineno, get_text($2));
        exit(EXIT_FAILURE);
    }
}
| ID { strcpy(copied_func_id, copied_id); check_func(); func_idx = lookup_func(ft, copied_func_id);
} LEFT_PARENTESES argument_list_call { check_func_params(); check_function_argument_types(ft, func_idx, arg_types, argument_count, yylineno); argument_count = 0; 
} RIGHT_PARENTESES { $$ = get_type_from_func(yylineno, copied_func_id);
} //FUNCTION CALL
;

argument_list_call:
  %empty
| ID { check_var(); arg_types[argument_count] = get_type_from_var(yylineno, copied_id, current_scope); argument_count++; } comma_expression argument_list_call
| argument_val { arg_types[argument_count] = $1; argument_count++; } comma_expression argument_list_call
;

argument_val:
  STRING_VAL { $$ = STRING_TYPE_; }
| BOOL_VAL { $$ = BOOL_TYPE_; }
| INT_VAL { $$ = INT_TYPE_; }
| FLOAT_VAL { $$ = FLOAT_TYPE_; }
;

comma_expression:
  %empty
| COMMA
;

operator_expression:
  id_number_compression operators id_number_compression {
    if ($1 == $3) {
      $$ = $1; // Ambos são do mesmo tipo
    } else {
      printf("SEMANTIC ERROR (%d): Incompatible types '%s' and '%s' for operator\n", yylineno, get_text($1), get_text($3));
      exit(EXIT_FAILURE);
    }
}
| INT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators id_number_compression {
    if ($2 != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'int'.\n", yylineno, get_text($2));
        exit(EXIT_FAILURE);
    }
    if($5 == FLOAT_TYPE_ || $5 == BOOL_TYPE_ || $5 == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types 'int' and '%s' for operator\n", yylineno, get_text($5));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'float32' to 'int'\n", yylineno);
      $$ = INT_TYPE_;
    }
}
| id_number_compression operators INT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if ($4 != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'int'.\n", yylineno, get_text($4));
        exit(EXIT_FAILURE);
    }
    if($1 == FLOAT_TYPE_ || $1 == BOOL_TYPE_ || $1 == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types '%s' and 'int' for operator\n", yylineno, get_text($1));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'float32' to 'int'\n", yylineno);
      $$ = INT_TYPE_;
    }
}
| FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators id_number_compression {
    if ($2 != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'float32'.\n", yylineno, get_text($2));
        exit(EXIT_FAILURE);
    }
    if($5 == INT_TYPE_ || $5 == BOOL_TYPE_ || $5 == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types 'float32' and '%s' for operator\n", yylineno, get_text($5));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'int' to 'float32'\n", yylineno);
      $$ = FLOAT_TYPE_;
    }
}
| id_number_compression operators FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if ($4 != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'float32'.\n", yylineno, get_text($4));
        exit(EXIT_FAILURE);
    }
    if($1 == INT_TYPE_ || $1 == BOOL_TYPE_ || $1 == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types '%s' and 'float32' for operator\n", yylineno, get_text($1));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'int' to 'float32'\n", yylineno);
      $$ = FLOAT_TYPE_;
    }
}
| INT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if ($2 != FLOAT_TYPE_ || $6 != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    printf("SEMANTIC ERROR (%d): Incompatible types '%s' and '%s' for operator\n", yylineno, get_text($2), get_text($6));
    exit(EXIT_FAILURE);
}
| FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators INT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if ($2 != INT_TYPE_ || $6 != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    printf("SEMANTIC ERROR (%d): Incompatible types '%s' and '%s' for operator\n", yylineno, get_text($2), get_text($6));
    exit(EXIT_FAILURE);
}
| INT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators INT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if ($2 != FLOAT_TYPE_ || $6 != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    $$ = INT_TYPE_;
}
| FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if ($2 != INT_TYPE_ || $6 != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    $$ = FLOAT_TYPE_;
}
;

id_number_compression:
  ID  { check_var(); 
        $$ = get_type_from_var(yylineno, copied_id, current_scope);
        int idx = lookup_var(vt, copied_id, current_scope);
        check_isArray(idx, yylineno, copied_id);
      }
| number_val_spec { $$ = $1; }
| BOOL_VAL { $$ = BOOL_TYPE_; }
;

if_statement:
  IF if_expression block %prec IFX
| IF if_expression block ELSE block
;

if_expression:
  ID { check_var(); Type expr_type = get_type_from_var(yylineno, copied_id, current_scope); check_conditional_type(yylineno, expr_type, "if"); }
| BOOL_VAL { check_conditional_type(yylineno, BOOL_TYPE_, "if"); }
| id_number_compression comparadors id_number_compression
| operator_expression comparadors id_number_compression
;

for_statement:
  FOR ID { last_decl_type = INT_TYPE_; new_var(); } SHORT_ASSIGN INT_VAL { $$ = INT_TYPE_; } SEMI for_comparison SEMI for_update block
;

for_comparison:
  ID { check_var(); } comparadors id_number_compression
;

for_update:
  ID { check_var(); } PLUS_PLUS
| ID { check_var(); } MINUS_MINUS
;

print_operation:
    PRINTLN LEFT_PARENTESES print_args RIGHT_PARENTESES
;

print_args:
  STRING_VAL { /* Ignora strings sem formatação */ }
| id_number_compression
| array_printable
| FORMAT_STRING COMMA ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, STRING_TYPE_, "%s"); }
| FORMAT_INT COMMA ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, INT_TYPE_, "%d"); }
| FORMAT_FLOAT COMMA ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, FLOAT_TYPE_, "%g"); }
| FORMAT_BOOL COMMA ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, BOOL_TYPE_, "%t"); }
| print_args COMMA FORMAT_STRING COMMA ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, STRING_TYPE_, "%s"); }
| print_args COMMA FORMAT_INT COMMA ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, INT_TYPE_, "%d"); }
| print_args COMMA FORMAT_FLOAT COMMA ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, FLOAT_TYPE_, "%g"); }
| print_args COMMA FORMAT_BOOL COMMA ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, BOOL_TYPE_, "%t"); }
;

scanf_operation:
    SCANF LEFT_PARENTESES scan_args RIGHT_PARENTESES
;

scan_args:
  FORMAT_STRING COMMA ADDRESS ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, STRING_TYPE_, "%s"); }
| FORMAT_INT COMMA ADDRESS ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, INT_TYPE_, "%d"); }
| FORMAT_FLOAT COMMA ADDRESS ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, FLOAT_TYPE_, "%g"); }
| FORMAT_BOOL COMMA ADDRESS ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, BOOL_TYPE_, "%t"); }
| scan_args COMMA FORMAT_STRING COMMA ADDRESS ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, STRING_TYPE_, "%s"); }
| scan_args COMMA FORMAT_INT COMMA ADDRESS ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, INT_TYPE_, "%d"); }
| scan_args COMMA FORMAT_FLOAT COMMA ADDRESS ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, FLOAT_TYPE_, "%g"); }
| scan_args COMMA FORMAT_BOOL COMMA ADDRESS ID { check_var(); Type var_type = get_type_from_var(yylineno, copied_id, current_scope); check_format_type(yylineno, var_type, BOOL_TYPE_, "%t"); }
;

type_spec:
  INT_TYPE    { last_decl_type = INT_TYPE_; }
| STRING_TYPE { last_decl_type = STRING_TYPE_; }
| FLOAT_TYPE  { last_decl_type = FLOAT_TYPE_; }
| BOOL_TYPE   { last_decl_type = BOOL_TYPE_; }
| VOID_TYPE   { last_decl_type = VOID_TYPE_; }
;

number_val_spec:
  INT_VAL { $$ = INT_TYPE_; }
| FLOAT_VAL { $$ = FLOAT_TYPE_; }
;

comparadors:
  LESS
| MORE
| LESS_EQUAL
| MORE_EQUAL
| DIFERS
| NOT
| EQUALS
;

operators:
  PLUS
| MINUS
| TIMES
| OVER
| REST
;

%%

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