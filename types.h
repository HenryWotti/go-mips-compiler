
#ifndef TYPES_H
#define TYPES_H


typedef enum {
    INT_TYPE_,
    FLOAT_TYPE_,
    BOOL_TYPE_,
    STRING_TYPE_,
    VOID_TYPE_
} Type;

const char* get_text(Type type);
void check_return_type(int line, Type return_type, Type expr_type, int has_return);
void check_format_type(int line, Type var_type, Type expected_type, const char *format);
void check_assignment_type(int line, Type id_type, Type expr_type);
void check_conditional_type(int line, Type expr_type, char *op);
Type get_type_from_var(int line, char *name, int current_scope2);
Type get_type_from_func(int line, char *name);

#endif // TYPES_H

