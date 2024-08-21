#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "tables.h"

static const char *TYPE_STRING[] = {
    "int",
    "float32",
    "bool",
    "string",
    "void"
};

const char* get_text(Type type) {
    return TYPE_STRING[type];
}

void check_return_type(int line, Type return_type, Type expr_type, int has_return) {
    if (return_type == VOID_TYPE_) {
        if (has_return) {
            printf("SEMANTIC ERROR (%d): 'void' function should not return a value.\n", line);
            exit(EXIT_FAILURE);
        }
    } else if (return_type != expr_type) {
        printf("SEMANTIC ERROR (%d): Function declared to return '%s' but returns '%s'.\n",
               line, get_text(return_type), get_text(expr_type));
        exit(EXIT_FAILURE);
    }
}


void check_format_type(int line, Type var_type, Type expected_type, const char *format) {
    if (var_type != expected_type) {
        printf("SEMANTIC ERROR (%d): Mismatched type for format specifier '%s'. Expected '%s' but got '%s'.\n",
               line, format, get_text(expected_type), get_text(var_type));
        exit(EXIT_FAILURE);
    }
}

void check_assignment_type(int line, Type id_type, Type expr_type) {
    if (id_type == INT_TYPE_ && expr_type != INT_TYPE_) {
        printf("SEMANTIC ERROR (%d): cannot assign type '%s' to 'int'.\n", line, get_text(expr_type));
        exit(EXIT_FAILURE);
    }
    if (id_type == FLOAT_TYPE_ && expr_type != FLOAT_TYPE_) {
        printf("SEMANTIC ERROR (%d): cannot assign type '%s' to 'float32'.\n", line, get_text(expr_type));
        exit(EXIT_FAILURE);
    }
    if (id_type == STRING_TYPE_ && expr_type != STRING_TYPE_) {
        printf("SEMANTIC ERROR (%d): cannot assign type '%s' to 'string'.\n", line, get_text(expr_type));
        exit(EXIT_FAILURE);
    }
    if (id_type == BOOL_TYPE_ && expr_type != BOOL_TYPE_) {
        printf("SEMANTIC ERROR (%d): cannot assign type '%s' to 'bool'.\n", line, get_text(expr_type));
        exit(EXIT_FAILURE);
    }
}

void check_conditional_type(int line, Type expr_type, char *op) {
    if (expr_type != BOOL_TYPE_) {
        printf("SEMANTIC ERROR (%d): conditional expression in '%s' is '%s' instead of 'bool'.\n",
               line, op, get_text(expr_type));
        exit(EXIT_FAILURE);
    }
}
