
#include "types.h"

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
