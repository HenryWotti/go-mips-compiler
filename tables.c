#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables.h"

// Strings Table
// ----------------------------------------------------------------------------

#define STRING_MAX_SIZE 128
#define STRINGS_TABLE_MAX_SIZE 100

struct str_table {
    char t[STRINGS_TABLE_MAX_SIZE][STRING_MAX_SIZE];
    int size;
};

StrTable* create_str_table() {
    StrTable *st = malloc(sizeof * st);
    st->size = 0;
    return st;
}

int add_string(StrTable* st, char* s) {
    for (int i = 0; i < st->size; i++) {
        if (strcmp(st->t[i], s) == 0) {
            return i;
        }
    }
    strcpy(st->t[st->size], s);
    int idx_added = st->size;
    st->size++;
    return idx_added;
}

char* get_string(StrTable* st, int i) {
    return st->t[i];
}

void print_str_table(StrTable* st) {
    printf("Strings table:\n");
    for (int i = 0; i < st->size; i++) {
        printf("Entry %d -- %s\n", i, get_string(st, i));
    }
}

void free_str_table(StrTable* st) {
    free(st);
}

// Variables Table
// ----------------------------------------------------------------------------

#define VARIABLE_MAX_SIZE 128
#define VARIABLES_TABLE_MAX_SIZE 100

typedef struct {
  char name[VARIABLE_MAX_SIZE];
  int line;
  Type type;
  int scope;
  int isArray;
} Entry;

struct var_table {
    Entry t[VARIABLES_TABLE_MAX_SIZE];
    int size;
};

VarTable* create_var_table() {
    VarTable *vt = malloc(sizeof * vt);
    vt->size = 0;
    return vt;
}

int lookup_var(VarTable* vt, char* s, int scope) {
    for (int i = 0; i < vt->size; i++) {
        if (strcmp(vt->t[i].name, s) == 0 && vt->t[i].scope == scope) {
            return i;
        }
    }
    return -1;
}

int add_var(VarTable* vt, char* s, int line, Type type, int scope) {
    strcpy(vt->t[vt->size].name, s);
    vt->t[vt->size].line = line;
    vt->t[vt->size].type = type;
    vt->t[vt->size].scope = scope; // Definindo o escopo
    vt->t[vt->size].isArray = 0;
    int idx_added = vt->size;
    vt->size++;
    return idx_added;
}

void set_isArray_by_idx(VarTable *vt, int idx, int isArray) {
    if (idx != -1 && idx < vt->size) {
        vt->t[idx].isArray = isArray;
    } else {
        printf("SEMANTIC ERROR: Invalid index %d for set_isArray.\n", idx);
        exit(EXIT_FAILURE);
    }
}

char* get_name(VarTable* vt, int i) {
    return vt->t[i].name;
}

int get_line(VarTable* vt, int i) {
    return vt->t[i].line;
}

int get_scope(VarTable* vt, int i) {
    return vt->t[i].scope;
}

int get_isArray(VarTable* vt, int i) {
    return vt->t[i].isArray;
}

Type get_type(VarTable* vt, int i) {
    return vt->t[i].type;
}

void print_var_table(VarTable* vt) {
    printf("Variables table:\n");
    for (int i = 0; i < vt->size; i++) {
        printf("Entry %d -- name: %s, line: %d, type: %s, scope: %d, isArray: %d\n", i,
               get_name(vt, i), get_line(vt, i), get_text(get_type(vt, i)), get_scope(vt, i), get_isArray(vt, i));
    }
}

void free_var_table(VarTable* vt) {
    free(vt);
}

// Functions Table
// ----------------------------------------------------------------------------

#define FUNCTION_MAX_SIZE 128
#define FUNCTIONS_TABLE_MAX_SIZE 100
#define MAX_PARAM 10

typedef struct {
  char name[FUNCTION_MAX_SIZE];
  int line;
  Type type;
  int scope; // Adicionando o campo 'scope'
  int param_count;
  Type param_types[MAX_PARAM];
} FuncEntry;

struct func_table {
    FuncEntry t[FUNCTIONS_TABLE_MAX_SIZE];
    int size;
};

FuncTable* create_func_table() {
    FuncTable *ft = malloc(sizeof * ft);
    ft->size = 0;
    return ft;
}

int lookup_func(FuncTable* ft, char* s) {
    for (int i = 0; i < ft->size; i++) {
        if (strcmp(ft->t[i].name, s) == 0)  {
            return i;
        }
    }
    return -1;
}

int lookup_func_in_scope(FuncTable* ft, char* s, int scope) {
    for (int i = 0; i < ft->size; i++) {
        if (strcmp(ft->t[i].name, s) == 0 && ft->t[i].scope <= scope) {
            return i;
        }
    }
    return -1;
}

int add_func(FuncTable* ft, char* s, int line, Type type, int scope, int param_count) {
    strcpy(ft->t[ft->size].name, s);
    ft->t[ft->size].line = line;
    ft->t[ft->size].type = type;
    ft->t[ft->size].scope = scope;
    ft->t[ft->size].param_count = param_count;
    int idx_added = ft->size;
    ft->size++;
    return idx_added;
}

void add_param_type(FuncTable* ft, int func_idx, Type param_type, int line) {
    if (ft->t[func_idx].param_count >= MAX_PARAM) {
        printf("SEMANTIC ERROR ('%d'): Maximum number of parameters exceeded for function '%s'.\n", line, ft->t[func_idx].name);
        exit(EXIT_FAILURE);
    }
    ft->t[func_idx].param_types[ft->t[func_idx].param_count] = param_type;
    ft->t[func_idx].param_count++; 
}

void update_func_return_type(FuncTable* ft, int func_idx, Type return_type) {
    ft->t[func_idx].type = return_type;
}

void check_function_argument_types(FuncTable* ft, int func_idx, Type arg_types[], int arg_count, int line) {
    for (int i = 0; i < arg_count; i++) {
        if (arg_types[i] != ft->t[func_idx].param_types[i]) {
            printf("SEMANTIC ERROR ('%d'): Incompatible type for argument %d in function '%s'. Expected '%s' but got '%s'\n", line,
                   i + 1, ft->t[func_idx].name, get_text(ft->t[func_idx].param_types[i]), get_text(arg_types[i]));
            exit(EXIT_FAILURE);
        }
    }
}

char* get_func_name(FuncTable* ft, int i) {
    return ft->t[i].name;
}

int get_func_line(FuncTable* ft, int i) {
    return ft->t[i].line;
}

Type get_func_type(FuncTable* ft, int i) {
    return ft->t[i].type;
}

int get_func_scope(FuncTable* ft, int i) {
    return ft->t[i].scope;
}

int get_func_param_count(FuncTable* ft, int i) {
    return ft->t[i].param_count;
}

void print_func_table(FuncTable* ft) {
    printf("Functions table:\n");
    for (int i = 0; i < ft->size; i++) {
        printf("Entry %d -- name: %s, line: %d, type: %s, scope: %d, param_count: %d\n", i,
               get_func_name(ft, i), get_func_line(ft, i), get_text(get_func_type(ft, i)), get_func_scope(ft, i), get_func_param_count(ft, i));
    }
}

void free_func_table(FuncTable* ft) {
    free(ft);
}

// AST
//----------------------------------------------------------------------------------
#define CHILDREN_LIMIT 20 // Don't try this at home, kids... :P

struct node {
    NodeKind kind;
    union {
        int   as_int;
        float as_float;
    } data;
    Type type;
    int count;
    AST* child[CHILDREN_LIMIT];
};

AST* new_node(NodeKind kind, int data, Type type) {
    AST* node = malloc(sizeof * node);
    node->kind = kind;
    node->data.as_int = data;
    node->type = type;
    node->count = 0;
    for (int i = 0; i < CHILDREN_LIMIT; i++) {
        node->child[i] = NULL;
    }
    return node;
}

AST* new_node_int(NodeKind kind, int value, Type type) {
    AST* node = malloc(sizeof * node);
    node->kind = kind;
    node->data.as_int = value;
    node->type = type;
    node->count = 0;
    for (int i = 0; i < CHILDREN_LIMIT; i++) {
        node->child[i] = NULL;
    }
    return node;
}

AST* new_node_float(NodeKind kind, float value, Type type) {
    AST* node = malloc(sizeof * node);
    node->kind = kind;
    node->data.as_float = value;
    node->type = type;
    node->count = 0;
    for (int i = 0; i < CHILDREN_LIMIT; i++) {
        node->child[i] = NULL;
    }
    return node;
}

AST* new_node_bool(NodeKind kind, int value, Type type) {
    // Bool values can still be treated as int (0 or 1)
    return new_node_int(kind, value, type);
}

void add_child(AST *parent, AST *child) {
    if (parent->count == CHILDREN_LIMIT) {
        fprintf(stderr, "Cannot add another child!\n");
        exit(1);
    }
    parent->child[parent->count] = child;
    parent->count++;
}

AST* get_child(AST *parent, int idx) {
    return parent->child[idx];
}

AST* new_subtree(NodeKind kind, Type type, int child_count, ...) {
    if (child_count > CHILDREN_LIMIT) {
        fprintf(stderr, "Too many children as arguments!\n");
        exit(1);
    }

    AST* node = new_node(kind, 0, type);
    va_list ap;
    va_start(ap, child_count);
    for (int i = 0; i < child_count; i++) {
        add_child(node, va_arg(ap, AST*));
    }
    va_end(ap);
    return node;
}

NodeKind get_kind(AST *node) {
    return node->kind;
}

int get_data(AST *node) {
    return node->data.as_int;
}

void set_float_data(AST *node, float data) {
    node->data.as_float = data;
}

float get_float_data(AST *node) {
    return node->data.as_float;
}

Type get_node_type(AST *node) {
    return node->type;
}

int get_child_count(AST *node) {
    return node->count;
}

void free_tree(AST *tree) {
    if (tree == NULL) return;
    for (int i = 0; i < tree->count; i++) {
        free_tree(tree->child[i]);
    }
    free(tree);
}

// Dot output.

int nr;

extern VarTable *vt;

char* kind2str(NodeKind kind) {
    switch(kind) {
        case ASSIGN_NODE:       return "=";
        case EQ_NODE:           return "==";
        case BLOCK_NODE:        return "block";
        case BOOL_VAL_NODE:     return "bool_val ";
        case IF_NODE:           return "if";
        case FOR_NODE:          return "for";
        case INT_VAL_NODE:      return "int_val ";
        case MINUS_NODE:        return "-";
        case OVER_NODE:         return "/";
        case PLUS_NODE:         return "+";
        case REST_NODE:         return "%";
        case TIMES_NODE:        return "*";
        case LESS_NODE:         return "<";
        case MORE_NODE:         return ">";
        case LESS_EQUAL_NODE:   return "<=";
        case MORE_EQUAL_NODE:   return ">=";
        case DIFERS_NODE:       return "!=";
        case AND_NODE:          return "&&";
        case OR_NODE:           return "||";
        case NOT_NODE:          return "!";
        case EQUALS_NODE:       return "==";
        case COMPARE_NODE:      return "compare";
        case STATEMANT_LIST:    return "statemant_list";
        case PROGRAM_NODE:      return "program";
        case MAIN_NODE:         return "main";
        case FLOAT_VAL_NODE:    return "float_val ";
        case STR_VAL_NODE:      return "str_val ";
        case VAR_DECL_NODE:     return "var_decl";
        case VAR_USE_NODE:      return "var_use";
        case ARRAY_ACCESS_NODE: return "array_access";
        case ARRAY_DECL_NODE:   return "array_decl";
        case WRITE_NODE:        return "print";
        case READ_NODE:        return "scanf";
        case FUNC_CALL_NODE:    return "func_call";
        case F2I_NODE:          return "F2I";
        case I2F_NODE:          return "I2F";
        default:                return "ERROR!!";
    }
}

int has_data(NodeKind kind) {
    switch(kind) {
        case BOOL_VAL_NODE:
        case INT_VAL_NODE:
        case FLOAT_VAL_NODE:
        case STR_VAL_NODE:
        case VAR_DECL_NODE:
        case VAR_USE_NODE:
            return 1;
        default:
            return 0;
    }
}

int print_node_dot(AST *node) {
    int my_nr = nr++;

    fprintf(stderr, "node%d[label=\"", my_nr);
    if (node->type != VOID_TYPE_) {
        fprintf(stderr, "(%s) ", get_text(node->type));
    }
    if (node->kind == VAR_DECL_NODE || node->kind == VAR_USE_NODE) {
        fprintf(stderr, "%s@", get_name(vt, node->data.as_int));
    } else {
        fprintf(stderr, "%s", kind2str(node->kind));
    }
    if (has_data(node->kind)) {
        if (node->kind == FLOAT_VAL_NODE) {
            fprintf(stderr, "%.2f", node->data.as_float);
        } else if (node->kind == STR_VAL_NODE) {
            fprintf(stderr, "@%d", node->data.as_int);
        } else {
            fprintf(stderr, "%d", node->data.as_int);
        }
    }
    fprintf(stderr, "\"];\n");

    for (int i = 0; i < node->count; i++) {
        int child_nr = print_node_dot(node->child[i]);
        fprintf(stderr, "node%d -> node%d;\n", my_nr, child_nr);
    }
    return my_nr;
}

void print_dot(AST *tree) {
    nr = 0;
    fprintf(stderr, "digraph {\ngraph [ordering=\"out\"];\n");
    print_node_dot(tree);
    fprintf(stderr, "}\n");
}