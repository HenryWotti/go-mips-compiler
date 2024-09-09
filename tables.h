
#ifndef TABLES_H
#define TABLES_H

#include "types.h"

// Strings Table
// ----------------------------------------------------------------------------

// Opaque structure.
// For simplicity, the table is implemented as a sequential list.
struct str_table;
typedef struct str_table StrTable;

// Creates an empty strings table.
StrTable *create_str_table();

// Adds the given string to the table without repetitions.
// String 's' is copied internally.
// Returns the index of the string in the table.
int add_string(StrTable *st, char *s);

// Returns a pointer to the string stored at index 'i'.
char *get_string(StrTable *st, int i);

// Prints the given table to stdout.
void print_str_table(StrTable *st);

// Clears the allocated structure.
void free_str_table(StrTable *st);

// Variables Table
// ----------------------------------------------------------------------------

// Opaque structure.
// For simplicity, the table is implemented as a sequential list.
// This table only stores the variable name and type, and its declaration line.
struct var_table;
typedef struct var_table VarTable;

// Creates an empty variables table.
VarTable *create_var_table();

// Adds a fresh var to the table.
// No check is made by this function, so make sure to call 'lookup_var' first.
// Returns the index where the variable was inserted.
int add_var(VarTable *vt, char *s, int line, Type type, int scope);

// Returns the index where the given variable is stored or -1 otherwise.
int lookup_var(VarTable *vt, char *s, int scope);

// Returns the variable name stored at the given index.
// No check is made by this function, so make sure that the index is valid first.
char *get_name(VarTable *vt, int i);

void set_isArray_by_idx(VarTable *vt, int idx, int isArray);

// Returns the declaration line of the variable stored at the given index.
// No check is made by this function, so make sure that the index is valid first.
int get_line(VarTable *vt, int i);

int get_isArray(VarTable *vt, int i);

// Returns the variable type stored at the given index.
// No check is made by this function, so make sure that the index is valid first.
Type get_type(VarTable *vt, int i);

int get_scope(VarTable *vt, int i);

// Prints the given table to stdout.
void print_var_table(VarTable *vt);

// Clears the allocated structure.
void free_var_table(VarTable *vt);

// Functions Table
// ----------------------------------------------------------------------------

struct func_table;
typedef struct func_table FuncTable;

FuncTable *create_func_table();
int add_func(FuncTable *ft, char *s, int line, Type type, int scope, int param_count);
void add_param_type(FuncTable *ft, int func_idx, Type param_type, int line);
void update_func_return_type(FuncTable *ft, int func_idx, Type return_type);
void check_function_argument_types(FuncTable *ft, int func_idx, Type arg_types[], int arg_count, int line);
int lookup_func(FuncTable *ft, char *s);
int lookup_func_in_scope(FuncTable *ft, char *s, int scope);
char *get_func_name(FuncTable *ft, int i);
int get_func_line(FuncTable *ft, int i);
Type get_func_type(FuncTable *ft, int i);
int get_func_scope(FuncTable *ft, int i);
int get_func_param_count(FuncTable *ft, int i);
void print_func_table(FuncTable *ft);
void free_func_table(FuncTable *ft);

// AST
//----------------------------------------------------------------------------------
#define CHILDREN_LIMIT 100 // Don't try this at home, kids... :P

typedef enum
{
    // Operações aritméticas e comparações
    ASSIGN_NODE,       // =
    SHORT_ASSIGN_NODE, // :=
    EQ_NODE,           // ==
    MINUS_NODE,        // -
    PLUS_NODE,         // +
    TIMES_NODE,        // *
    OVER_NODE,         // /
    REST_NODE,         // %
    PLUS_PLUS_NODE,    //++
    MINUS_MINUS_NODE,  //--

    // Operações lógicas
    AND_NODE,        // &&
    OR_NODE,         // ||
    NOT_NODE,        // !
    LESS_NODE,       // <
    MORE_NODE,       // >
    LESS_EQUAL_NODE, // <=
    MORE_EQUAL_NODE, // >=
    DIFERS_NODE,     // !=
    EQUALS_NODE,
    COMPARE_NODE,

    // Tipos de valor
    BOOL_VAL_NODE,  // Valores booleanos
    INT_VAL_NODE,   // Valores inteiros
    FLOAT_VAL_NODE, // Valores float
    STR_VAL_NODE,   // Valores string

    // Estruturas de controle e blocos
    IF_NODE,        // if
    BLOCK_NODE,     // bloco de código
    STATEMANT_LIST, // lista de statemants
    FOR_NODE,       // for

    // Operações com arrays
    ARRAY_ACCESS_NODE, // Acesso a elemento de array
    ARRAY_DECL_NODE,   // Declaração de array

    // Declarações e uso de variáveis
    VAR_DECL_NODE, // Declaração de variável
    VAR_USE_NODE,  // Uso de variável

    // Operações de entrada/saída
    WRITE_NODE, // printf ou println
    READ_NODE,  // scanf

    // Chamadas de função
    FUNC_CALL_NODE, // Chamada de função
    RETURN_NODE,

    // Conversão de tipos
    F2I_NODE, // float para int
    I2F_NODE, // int para float

    // Estruturas gerais do programa
    PROGRAM_NODE, // Nó raiz do programa
    MAIN_NODE,    // Função principal (main)
    ARGUMENT_LIST_NODE,
    PARAM_LIST_NODE,
    FUNC_USE_NODE,
    FUNC_DECL_NODE,
    FUNC_LIST_NODE,
    FUNC_NODE,
} NodeKind;

struct node; // Opaque structure to ensure encapsulation.

typedef struct node AST;

AST *new_node(NodeKind kind, int data, Type type);
AST *new_node_int(NodeKind kind, int value, Type type);
AST *new_node_float(NodeKind kind, float value, Type type);
AST *new_node_bool(NodeKind kind, int value, Type type);

void add_child(AST *parent, AST *child);
AST *get_child(AST *parent, int idx);

AST *new_subtree(NodeKind kind, Type type, int child_count, ...);

NodeKind get_kind(AST *node);
char *kind2str(NodeKind kind);

int get_data(AST *node);
void set_float_data(AST *node, float data);
float get_float_data(AST *node);

Type get_node_type(AST *node);
int get_child_count(AST *node);

void print_tree(AST *ast);
void print_dot(AST *ast);

void free_tree(AST *tree);

#endif // TABLES_H