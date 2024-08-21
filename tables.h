
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
StrTable* create_str_table();

// Adds the given string to the table without repetitions.
// String 's' is copied internally.
// Returns the index of the string in the table.
int add_string(StrTable* st, char* s);

// Returns a pointer to the string stored at index 'i'.
char* get_string(StrTable* st, int i);

// Prints the given table to stdout.
void print_str_table(StrTable* st);

// Clears the allocated structure.
void free_str_table(StrTable* st);


// Variables Table
// ----------------------------------------------------------------------------

// Opaque structure.
// For simplicity, the table is implemented as a sequential list.
// This table only stores the variable name and type, and its declaration line.
struct var_table;
typedef struct var_table VarTable;

// Creates an empty variables table.
VarTable* create_var_table();

// Adds a fresh var to the table.
// No check is made by this function, so make sure to call 'lookup_var' first.
// Returns the index where the variable was inserted.
int add_var(VarTable* vt, char* s, int line, Type type, int scope);

// Returns the index where the given variable is stored or -1 otherwise.
int lookup_var(VarTable* vt, char* s, int scope);

// Returns the variable name stored at the given index.
// No check is made by this function, so make sure that the index is valid first.
char* get_name(VarTable* vt, int i);

void set_isArray_by_idx(VarTable *vt, int idx, int isArray);

// Returns the declaration line of the variable stored at the given index.
// No check is made by this function, so make sure that the index is valid first.
int get_line(VarTable* vt, int i);

int get_isArray(VarTable* vt, int i);

// Returns the variable type stored at the given index.
// No check is made by this function, so make sure that the index is valid first.
Type get_type(VarTable* vt, int i);

int get_scope(VarTable* vt, int i);

// Prints the given table to stdout.
void print_var_table(VarTable* vt);

// Clears the allocated structure.
void free_var_table(VarTable* vt);

// Functions Table
// ----------------------------------------------------------------------------

struct func_table;
typedef struct func_table FuncTable;

FuncTable* create_func_table();
int add_func(FuncTable* ft, char* s, int line, Type type, int scope, int param_count);
void add_param_type(FuncTable* ft, int func_idx, Type param_type, int line);
void update_func_return_type(FuncTable* ft, int func_idx, Type return_type);
void check_function_argument_types(FuncTable* ft, int func_idx, Type arg_types[], int arg_count, int line);
int lookup_func(FuncTable* ft, char* s);
int lookup_func_in_scope(FuncTable* ft, char* s, int scope);
char* get_func_name(FuncTable* ft, int i);
int get_func_line(FuncTable* ft, int i);
Type get_func_type(FuncTable* ft, int i);
int get_func_scope(FuncTable* ft, int i);
int get_func_param_count(FuncTable* ft, int i);
void print_func_table(FuncTable* ft);
void free_func_table(FuncTable* ft);

#endif // TABLES_H

