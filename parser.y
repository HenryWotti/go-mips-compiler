%output "parser.c"
%defines "parser.h"
%define parse.error verbose
%define parse.lac full
%define api.value.type {AST*}

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
  package_declaration import_declaration list_func_generic func_main {
    ast_root = $4;  // Atribui a raiz da AST
  }
;

package_declaration:
  PACKAGE MAIN
;

import_declaration:
  %empty
| IMPORT STRING_VAL { add_string(st, yytext); } import_declaration
;

func_main :
  FUNC MAIN { current_scope++; } LEFT_PARENTESES RIGHT_PARENTESES block {
    $$ = new_subtree(MAIN_NODE, VOID_TYPE_, 1, $6);
  }
;

block :
  LEFT_BRACE statement_list RIGHT_BRACE {
    $$ = new_subtree(BLOCK_NODE, VOID_TYPE_, 1, $2);
  }
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
    check_return_type(yylineno, current_return_type, get_node_type($2), 1);
    has_return = 1; // Indicar que um return foi encontrado
  }
;

statement_list:
  statement {
    $$ = new_subtree(STATEMANT_LIST, VOID_TYPE_, 1, $1); 
  }
| statement_list statement {
      add_child($1, $2); 
      $$ = $1;
  }
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
} RIGHT_PARENTESES SEMI {
  $$ = new_subtree(FUNC_CALL_NODE, get_type_from_func(yylineno, copied_func_id), 1, new_node(VAR_USE_NODE, func_idx, get_type_from_func(yylineno, copied_func_id)));
} //FUNCTION CALL
;

string_list: 
  STRING_VAL {
    int str_index = add_string(st, yytext);
    $$ = new_node(STR_VAL_NODE, str_index, STRING_TYPE_);  // Cria um nó da AST para a string
  }
| string_list COMMA STRING_VAL{
    int str_index = add_string(st, yytext);
    AST *str_node = new_node(STR_VAL_NODE, str_index, STRING_TYPE_);  // Cria um nó para a nova string
    add_child($1, str_node);  // Adiciona a nova string como filha da lista existente
    $$ = $1;  // A lista é retornada
}
;

val_declaration :
  VAR ID type_spec { new_var();
  $$ = new_node(VAR_DECL_NODE, lookup_var(vt, copied_id, current_scope), last_decl_type);
  }
;

assign_val :
  ID  { 
        check_var(); 
        id_type2 = get_type_from_var(yylineno, copied_id, current_scope);
        idx2 = lookup_var(vt, copied_id, current_scope);
        check_isArray(idx2, yylineno, copied_id);
      } ASSIGN assign_expression {
        check_assignment_type(yylineno, id_type2, get_node_type($4));
        $$ = new_subtree(ASSIGN_NODE, VOID_TYPE_, 2, new_node(VAR_USE_NODE, idx2, id_type2), $4);
      }
      //new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope))
;

array_printable:
  ID { 
      check_var(); 
      strcpy(copied_id_array, copied_id);
      //$$ = new_node(VAR_USE_NODE, var_idx, get_type_from_var(yylineno, copied_id, current_scope)); 
  } 
  LEFT_BRACKET id_int_compression RIGHT_BRACKET {
    check_array_position_int(yylineno, get_node_type($4));
    $$ = new_subtree(ARRAY_ACCESS_NODE, get_type_from_var(yylineno, copied_id_array, current_scope), 2, new_node(VAR_USE_NODE, lookup_var(vt, copied_id_array, current_scope), get_type_from_var(yylineno, copied_id_array, current_scope)), $4);
  }
;

array_declaration :
  VAR ID LEFT_BRACKET INT_VAL RIGHT_BRACKET type_spec { 
      new_var();
      idx = lookup_var(vt, copied_id, current_scope); 
      set_isArray_by_idx(vt, idx, 1);
      check_array_position_int(yylineno, INT_TYPE_); // O índice é do tipo INT
      //$$ = new_node(ARRAY_DECL_NODE, idx, last_decl_type);
      $$ = new_subtree(ARRAY_DECL_NODE, get_type_from_var(yylineno, copied_id, current_scope), 2, new_node(VAR_DECL_NODE, idx, last_decl_type), new_node_int(INT_VAL_NODE, get_data($4), INT_TYPE_));
  }
;

array_assign :
  ID { 
      check_var(); 
      array_type = get_type_from_var(yylineno, copied_id, current_scope);
      idx2 = lookup_var(vt, copied_id, current_scope);
      check_isNotArray(idx2, yylineno);  
  } 
  LEFT_BRACKET id_int_compression RIGHT_BRACKET ASSIGN assign_expression {
    // Verifica se a posição do array é um inteiro
    check_array_position_int(yylineno, get_node_type($4));
    
    // Verifica se o tipo do valor atribuído é compatível com o tipo do array
    check_array_type(array_type, get_node_type($7), yylineno);

    // Cria o nó de acesso ao array
    //Node* array_access_node = new_subtree(ARRAY_ACCESS_NODE, array_type, 2, $1, $4); 

    // Cria a subárvore para a atribuição
    $$ = new_subtree(ASSIGN_NODE, VOID_TYPE_, 2, new_subtree(ARRAY_ACCESS_NODE, array_type, 2, new_node(VAR_DECL_NODE, idx2, array_type), $4), $7);
  }
;


id_int_compression:
  ID { 
      check_var(); 
      int var_idx = lookup_var(vt, copied_id, current_scope); 
      $$ = new_node(VAR_USE_NODE, var_idx, get_type_from_var(yylineno, copied_id, current_scope)); 
  }
| INT_VAL { 
      $$ = $1;
  }
;

assign_expression :
  string_list { $$ = $1; }
| id_number_compression { $$ = $1; }
| operator_expression { $$ = $1; }
| INT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if (get_node_type($2) == FLOAT_TYPE_) {
        $$ = new_subtree(F2I_NODE, INT_TYPE_, 1, $2);
        printf("Line(%d): Converting 'float32' to 'int'\n", yylineno);
    } else {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'int'.\n", yylineno, get_text(get_node_type($2)));
        exit(EXIT_FAILURE);
    }
}
| FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if (get_node_type($2) == INT_TYPE_) {
        $$ = new_subtree(I2F_NODE, FLOAT_TYPE_, 1, $2);
        printf("Line(%d): Converting 'int' to 'float32'\n", yylineno);
    } else {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'float32'.\n", yylineno,get_text(get_node_type($2)));
        exit(EXIT_FAILURE);
    }
}
| ID {
    strcpy(copied_func_id, copied_id); check_func(); func_idx = lookup_func(ft, copied_func_id);
  } LEFT_PARENTESES argument_list_call { 
      check_func_params(); check_function_argument_types(ft, func_idx, arg_types, argument_count, yylineno); argument_count = 0; 
    } RIGHT_PARENTESES {
        $$ = new_subtree(FUNC_CALL_NODE, get_type_from_func(yylineno, copied_func_id), 1, new_node(VAR_USE_NODE, func_idx, get_type_from_func(yylineno, copied_func_id)));
      } //FUNCTION CALL
;

argument_list_call:
  %empty
| ID { 
    check_var(); 
    arg_types[argument_count] = get_type_from_var(yylineno, copied_id, current_scope); 
    argument_count++; 
} comma_expression argument_list_call
| argument_val { 
    arg_types[argument_count] = get_node_type($1); 
    argument_count++; 
} comma_expression argument_list_call
;

argument_val:
  STRING_VAL { 
      int str_index = add_string(st, yytext);
      $$ = new_node(STR_VAL_NODE, str_index, STRING_TYPE_);
  }
| BOOL_VAL { 
      $$ = $1;
  }
| INT_VAL { 
      $$ = $1;
  }
| FLOAT_VAL { 
      $$ = $1;
  }
;

comma_expression:
  %empty
| COMMA
;

operator_expression:
  id_number_compression operators id_number_compression {
    if (get_node_type($1) == get_node_type($3)) {
      $$ = new_subtree(get_kind($2), get_node_type($1), 2, $1, $3);
    } else {
      printf("SEMANTIC ERROR (%d): Incompatible types '%s' and '%s' for operator\n", yylineno, get_text(get_node_type($1)), get_text(get_node_type($3)));
      exit(EXIT_FAILURE);
    }
}
| INT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators id_number_compression {
    if (get_node_type($2) != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'int'.\n", yylineno, get_text(get_node_type($2)));
        exit(EXIT_FAILURE);
    }
    if(get_node_type($5) == FLOAT_TYPE_ || get_node_type($5) == BOOL_TYPE_ || get_node_type($5) == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types 'int' and '%s' for operator\n", yylineno, get_text(get_node_type($5)));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'float32' to 'int'\n", yylineno);
      //new_node(F2I_NODE, INT_TYPE_, 1, $2)
      $$ = new_subtree(get_kind($4), INT_TYPE_, 2, new_subtree(F2I_NODE, INT_TYPE_, 1, $2), $5);
    }
}
| id_number_compression operators INT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if (get_node_type($4) != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'int'.\n", yylineno, get_text(get_node_type($4)));
        exit(EXIT_FAILURE);
    }
    if(get_node_type($1) == FLOAT_TYPE_ || get_node_type($1) == BOOL_TYPE_ || get_node_type($1) == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types '%s' and 'int' for operator\n", yylineno, get_text(get_node_type($1)));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'float32' to 'int'\n", yylineno);
      //$$ = new_subtree(F2I_NODE, INT_TYPE_, 2, $1, $4);
      $$ = new_subtree(get_kind($2), INT_TYPE_, 2, $1, new_subtree(F2I_NODE, INT_TYPE_, 1, $4));
    }
}
| FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators id_number_compression {
    if (get_node_type($2) != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'float32'.\n", yylineno, get_text(get_node_type($2)));
        exit(EXIT_FAILURE);
    }
    if(get_node_type($5) == INT_TYPE_ || get_node_type($5) == BOOL_TYPE_ || get_node_type($5) == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types 'float32' and '%s' for operator\n", yylineno, get_text(get_node_type($5)));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'int' to 'float32'\n", yylineno);
      //$$ = new_subtree(I2F_NODE, FLOAT_TYPE_, 2, $2, $5);
      $$ = new_subtree(get_kind($4), FLOAT_TYPE_, 2, new_subtree(I2F_NODE, FLOAT_TYPE_, 1, $2), $5);
    }
}
| id_number_compression operators FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if (get_node_type($4) != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Cannot cast type '%s' to 'float32'.\n", yylineno, get_text(get_node_type($4)));
        exit(EXIT_FAILURE);
    }
    if(get_node_type($1) == INT_TYPE_ || get_node_type($1) == BOOL_TYPE_ || get_node_type($1) == STRING_TYPE_){
      printf("SEMANTIC ERROR (%d): Incompatible types '%s' and 'float32' for operator\n", yylineno, get_text(get_node_type($1)));
      exit(EXIT_FAILURE);
    } else {
      printf("Line(%d): Converting 'int' to 'float32'\n", yylineno);
      //$$ = new_subtree(I2F_NODE, FLOAT_TYPE_, 2, $1, $4);
      $$ = new_subtree(get_kind($2), FLOAT_TYPE_, 2, $1, new_subtree(I2F_NODE, FLOAT_TYPE_, 1, $4));
    }
}
| INT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if (get_node_type($2) != FLOAT_TYPE_ || get_node_type($6) != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    printf("SEMANTIC ERROR (%d): Incompatible types '%s' and '%s' for operator\n", yylineno, get_text(get_node_type($2)), get_text(get_node_type($6)));
    exit(EXIT_FAILURE);
}
| FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators INT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if (get_node_type($2) != INT_TYPE_ || get_node_type($6) != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    printf("SEMANTIC ERROR (%d): Incompatible types '%s' and '%s' for operator\n", yylineno, get_text(get_node_type($2)), get_text(get_node_type($6)));
    exit(EXIT_FAILURE);
}
| INT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators INT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if (get_node_type($2) != FLOAT_TYPE_ || get_node_type($6) != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    //$$ = new_subtree(F2I_NODE, INT_TYPE_, 2, $2, $6);
    $$ = new_subtree(get_kind($4), INT_TYPE_, 2, new_subtree(I2F_NODE, INT_TYPE_, 1, $2), new_subtree(I2F_NODE, INT_TYPE_, 1, $6));
}
| FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES operators FLOAT_TYPE_CAST id_number_compression RIGHT_PARENTESES {
    if (get_node_type($2) != INT_TYPE_ || get_node_type($6) != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): Invalid cast in expression.\n", yylineno);
        exit(EXIT_FAILURE);
    }
    //$$ = new_subtree(I2F_NODE, FLOAT_TYPE_, 2, $2, $6);
    $$ = new_subtree(get_kind($4), FLOAT_TYPE_, 2, new_subtree(I2F_NODE, FLOAT_TYPE_, 1, $2), new_subtree(I2F_NODE, FLOAT_TYPE_, 1, $6));
}
;

id_number_compression:
  ID  { check_var(); 
        idx = lookup_var(vt, copied_id, current_scope);
        check_isArray(idx, yylineno, copied_id);
        $$ = new_node(VAR_USE_NODE, idx, get_type_from_var(yylineno, copied_id, current_scope));
      }
| number_val_spec { $$ = $1; }
| BOOL_VAL { $$ = $1; }
;

if_statement:
  IF if_expression block %prec IFX { 
      $$ = new_subtree(IF_NODE, VOID_TYPE_, 2, $2, $3);
  }
| IF if_expression block ELSE block { 
      $$ = new_subtree(IF_NODE, VOID_TYPE_, 3, $2, $3, $5);
  }
;

if_expression:
  ID { 
      check_var(); 
      Type expr_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_conditional_type(yylineno, expr_type, "if"); 
      $$ = new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), expr_type); 
  }
| BOOL_VAL { 
      check_conditional_type(yylineno, BOOL_TYPE_, "if");
      $$ = $1; // Como o BOOL_VAL já é um nó, simplesmente atribuímos $1 a $$.
  }
| id_number_compression comparadors id_number_compression { 
      $$ = new_subtree(get_kind($2), VOID_TYPE_, 2, $1, $3); 
  }
| operator_expression comparadors id_number_compression { 
      $$ = new_subtree(get_kind($2), VOID_TYPE_, 2, $1, $3);
  }
  //$$ = new_subtree(get_kind($3), VOID_TYPE_, 2, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), $4);
;

for_statement:
  FOR ID { 
      last_decl_type = INT_TYPE_; 
      new_var(); 
  } SHORT_ASSIGN INT_VAL SEMI for_comparison SEMI for_update block {
      // $2: ID (variável), $4: SHORT_ASSIGN, $5: INT_VAL, $6: SEMI, $7: for_comparison, $8: SEMI, $9: for_update, $10: block

      // Inicialização: ID := INT_VAL
      AST *init_node = new_subtree(SHORT_ASSIGN_NODE, VOID_TYPE_, 2, 
                                   new_node(VAR_DECL_NODE, lookup_var(vt, copied_id, current_scope), INT_TYPE_), 
                                   new_node_int(INT_VAL_NODE, get_data($5), INT_TYPE_));

      // Condição de continuação do loop (e.g., i < 5)
      AST *cond_node = $7; 

      // Atualização (e.g., i++)
      AST *update_node = $9; 

      // Bloco do loop
      AST *body_node = $10;

      // Nó principal do loop for
      $$ = new_subtree(FOR_NODE, VOID_TYPE_, 4, init_node, cond_node, update_node, body_node);
  }
;


for_comparison:
  ID { 
      check_var();
  } comparadors id_number_compression {
      // Cria o nó de comparação entre a variável e a expressão
      $$ = new_subtree(get_kind($3), VOID_TYPE_, 2, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), $4);
  }
;

for_update:
  ID { 
      check_var(); 
  } PLUS_PLUS {
      // Cria um nó para a operação de incremento (i + 1)
      AST *increment_node = new_subtree(PLUS_NODE, INT_TYPE_, 2, 
                              new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), 
                              new_node_int(INT_VAL_NODE, 1, INT_TYPE_));
                              
      // Cria um nó para a atribuição (i = i + 1)
      $$ = new_subtree(ASSIGN_NODE, VOID_TYPE_, 2, 
            new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), 
            increment_node);
  }
| ID { 
      check_var(); 
  } MINUS_MINUS {
      // Cria um nó para a operação de incremento (i + 1)
      AST *increment_node = new_subtree(MINUS_NODE, INT_TYPE_, 2, 
                              new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), 
                              new_node_int(INT_VAL_NODE, 1, INT_TYPE_));
                              
      // Cria um nó para a atribuição (i = i + 1)
      $$ = new_subtree(ASSIGN_NODE, VOID_TYPE_, 2, 
            new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), get_type_from_var(yylineno, copied_id, current_scope)), 
            increment_node);
  }
;

print_operation:
    PRINTLN LEFT_PARENTESES print_args RIGHT_PARENTESES {
        $$ = new_subtree(WRITE_NODE, VOID_TYPE_, 1, $3);  // Cria um nó WRITE_NODE na AST
    }
;

print_args:
  STRING_VAL {
      int str_index = add_string(st, yytext);
      $$ = new_node(STR_VAL_NODE, str_index, STRING_TYPE_);
  }
| id_number_compression { $$ = $1; }
| array_printable { $$ = $1; }
/*| FORMAT_STRING COMMA ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, STRING_TYPE_, "%s"); 
      $$ = new_subtree(WRITE_NODE, STRING_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
| FORMAT_INT COMMA ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, INT_TYPE_, "%d"); 
      $$ = new_subtree(WRITE_NODE, INT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
| FORMAT_FLOAT COMMA ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, FLOAT_TYPE_, "%g"); 
      $$ = new_subtree(WRITE_NODE, FLOAT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
| FORMAT_BOOL COMMA ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, BOOL_TYPE_, "%t"); 
      $$ = new_subtree(WRITE_NODE, BOOL_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
| print_args COMMA FORMAT_STRING COMMA ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, STRING_TYPE_, "%s"); 
      add_child($1, new_subtree(WRITE_NODE, STRING_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      $$ = $1;
  }
| print_args COMMA FORMAT_INT COMMA ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, INT_TYPE_, "%d"); 
      add_child($1, new_subtree(WRITE_NODE, INT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      $$ = $1;
  }
| print_args COMMA FORMAT_FLOAT COMMA ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, FLOAT_TYPE_, "%g"); 
      add_child($1, new_subtree(WRITE_NODE, FLOAT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      $$ = $1;
  }
| print_args COMMA FORMAT_BOOL COMMA ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, BOOL_TYPE_, "%t"); 
      add_child($1, new_subtree(WRITE_NODE, BOOL_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      $$ = $1;
  }*/
;

scanf_operation:
    SCANF LEFT_PARENTESES scan_args RIGHT_PARENTESES {
        $$ = $3;
    }
;

scan_args:
  FORMAT_STRING COMMA ADDRESS ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, STRING_TYPE_, "%s"); 
      $$ = new_subtree(READ_NODE, STRING_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
| FORMAT_INT COMMA ADDRESS ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, INT_TYPE_, "%d"); 
      $$ = new_subtree(READ_NODE, INT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
| FORMAT_FLOAT COMMA ADDRESS ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, FLOAT_TYPE_, "%g"); 
      $$ = new_subtree(READ_NODE, FLOAT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
| FORMAT_BOOL COMMA ADDRESS ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, BOOL_TYPE_, "%t"); 
      $$ = new_subtree(READ_NODE, BOOL_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type));
  }
| scan_args COMMA FORMAT_STRING COMMA ADDRESS ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, STRING_TYPE_, "%s"); 
      add_child($1, new_subtree(READ_NODE, STRING_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      $$ = $1;
  }
| scan_args COMMA FORMAT_INT COMMA ADDRESS ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, INT_TYPE_, "%d"); 
      add_child($1, new_subtree(READ_NODE, INT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      $$ = $1;
  }
| scan_args COMMA FORMAT_FLOAT COMMA ADDRESS ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, FLOAT_TYPE_, "%g"); 
      add_child($1, new_subtree(READ_NODE, FLOAT_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      $$ = $1;
  }
| scan_args COMMA FORMAT_BOOL COMMA ADDRESS ID { 
      check_var(); 
      Type var_type = get_type_from_var(yylineno, copied_id, current_scope); 
      check_format_type(yylineno, var_type, BOOL_TYPE_, "%t"); 
      add_child($1, new_subtree(READ_NODE, BOOL_TYPE_, 1, new_node(VAR_USE_NODE, lookup_var(vt, copied_id, current_scope), var_type)));
      $$ = $1;
  }
;

type_spec:
  INT_TYPE    { last_decl_type = INT_TYPE_; }
| STRING_TYPE { last_decl_type = STRING_TYPE_; }
| FLOAT_TYPE  { last_decl_type = FLOAT_TYPE_; }
| BOOL_TYPE   { last_decl_type = BOOL_TYPE_; }
| VOID_TYPE   { last_decl_type = VOID_TYPE_; }
;

number_val_spec:
  INT_VAL { $$ = $1; }
| FLOAT_VAL { $$ = $1; }
;

comparadors:
  LESS { $$ = new_node(LESS_NODE, 0, VOID_TYPE_); }
| MORE { $$ = new_node(MORE_NODE, 0, VOID_TYPE_); }
| LESS_EQUAL { $$ = new_node(LESS_EQUAL_NODE, 0, VOID_TYPE_); }
| MORE_EQUAL { $$ = new_node(MORE_EQUAL_NODE, 0, VOID_TYPE_); }
| DIFERS { $$ = new_node(DIFERS_NODE, 0, VOID_TYPE_); }
| NOT { $$ = new_node(NOT_NODE, 0, VOID_TYPE_); }
| EQUALS { $$ = new_node(EQUALS_NODE, 0, VOID_TYPE_); }
;

operators:
  PLUS { $$ = new_node(PLUS_NODE, 0, VOID_TYPE_); }
| MINUS { $$ = new_node(MINUS_NODE, 0, VOID_TYPE_); }
| TIMES { $$ = new_node(TIMES_NODE, 0, VOID_TYPE_); }
| OVER { $$ = new_node(OVER_NODE, 0, VOID_TYPE_); }
| REST { $$ = new_node(REST_NODE, 0, VOID_TYPE_); }
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