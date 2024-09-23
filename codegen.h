#ifndef CODEGEN_H
#define CODEGEN_H
#include <stdio.h>
#include "tables.h"

// Função para gerar código MIPS a partir da AST
void generate_mips_code(AST *ast, FILE *out);
void generate_mips_data_section(FILE *out);
void generate_mips_for_write_node(AST *ast, FILE *out);

#endif
