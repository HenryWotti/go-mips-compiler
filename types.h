
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

#endif // TYPES_H

