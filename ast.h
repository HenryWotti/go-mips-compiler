#ifndef AST_H
#define AST_H

#include "types.h"


// AST
//----------------------------------------------------------------------------------
#define CHILDREN_LIMIT 100 // Don't try this at home, kids... :P

typedef enum {
    // Operações aritméticas e comparações
    ASSIGN_NODE,         // =
    EQ_NODE,             // ==
    MINUS_NODE,          // -
    PLUS_NODE,           // +
    TIMES_NODE,          // *
    OVER_NODE,           // /
    REST_NODE,           // %

    // Operações lógicas
    AND_NODE,            // &&
    OR_NODE,             // ||
    NOT_NODE,            // !
    LESS_NODE,           // <
    MORE_NODE,           // >
    LESS_EQUAL_NODE,     // <=
    MORE_EQUAL_NODE,     // >=
    DIFERS_NODE,         // !=
    EQUALS_NODE,
    COMPARE_NODE,

    // Tipos de valor
    BOOL_VAL_NODE,       // Valores booleanos
    INT_VAL_NODE,        // Valores inteiros
    FLOAT_VAL_NODE,      // Valores float
    STR_VAL_NODE,        // Valores string

    // Estruturas de controle e blocos
    IF_NODE,             // if
    BLOCK_NODE,          // bloco de código
    FOR_NODE,            // for

    // Operações com arrays
    ARRAY_ACCESS_NODE,   // Acesso a elemento de array
    ARRAY_DECL_NODE,     // Declaração de array

    // Declarações e uso de variáveis
    VAR_DECL_NODE,       // Declaração de variável
    VAR_USE_NODE,        // Uso de variável

    // Operações de entrada/saída
    WRITE_NODE,          // printf ou println
    READ_NODE,          // scanf

    // Chamadas de função
    FUNC_CALL_NODE,      // Chamada de função

    // Conversão de tipos
    F2I_NODE,            // float para int
    I2F_NODE,            // int para float

    // Estruturas gerais do programa
    PROGRAM_NODE,        // Nó raiz do programa
    MAIN_NODE            // Função principal (main)
} NodeKind;

struct node; // Opaque structure to ensure encapsulation.

typedef struct node AST;

AST* new_node(NodeKind kind, int data, Type type);
AST* new_node_int(NodeKind kind, int value, Type type);
AST* new_node_float(NodeKind kind, float value, Type type);
AST* new_node_bool(NodeKind kind, int value, Type type);

void add_child(AST *parent, AST *child);
AST* get_child(AST *parent, int idx);

AST* new_subtree(NodeKind kind, Type type, int child_count, ...);

NodeKind get_kind(AST *node);
char* kind2str(NodeKind kind);

int get_data(AST *node);
void set_float_data(AST *node, float data);
float get_float_data(AST *node);

Type get_node_type(AST *node);
int get_child_count(AST *node);

void print_tree(AST *ast);
void print_dot(AST *ast);

void free_tree(AST *ast);

#endif