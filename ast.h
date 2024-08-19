#ifndef AST_H
#define AST_H

#include "types.h"

typedef enum {
    ASSIGN_NODE,
    EQ_NODE,
    BLOCK_NODE,
    BOOL_VAL_NODE,
    IF_NODE,
    REPEAT_NODE,
    INT_VAL_NODE,
    MINUS_NODE,
    OVER_NODE,
    PLUS_NODE,
    REST_NODE,
    PROGRAM_NODE,
    MAIN_NODE,
    READ_NODE,
    FLOAT_VAL_NODE,
    STR_VAL_NODE,
    TIMES_NODE,
    VAR_DECL_NODE,
    VAR_LIST_NODE,
    VAR_USE_NODE,
    WRITE_NODE,

    F2I_NODE,   // Conversion of types.
    I2F_NODE
} NodeKind;

struct node; // Opaque structure to ensure encapsulation.

typedef struct node AST;

AST* new_node(NodeKind kind, int data, Type type);

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
