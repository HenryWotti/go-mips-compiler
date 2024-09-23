#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables.h"
#include "codegen.h"

// Variável global para contador de labels (usada em loops e ifs)
static int label_counter = 0;

extern FuncTable *ft;
extern StrTable *st;
extern VarTable *vt;

// Função auxiliar para gerar labels únicos
int generate_label() {
    return label_counter++;
}

// Função para gerar o código MIPS de um nó AST
void generate_mips_code(AST *ast, FILE *out) {
    if (!ast) return;

    switch (get_kind(ast)) {
        
        case PROGRAM_NODE:
            //printf(out, "# Programa principal\n");
            // Gerar a seção .data para as strings
            generate_mips_data_section(out);
            // Gera a seção de texto e o código da função main
            fprintf(out, ".text\n");
            generate_mips_code(get_child(ast, 0), out);  // Gera o código para funclist
            generate_mips_code(get_child(ast, 1), out);  // Gera o código para a função main
            break;   

        // Atribuição    
        case ASSIGN_NODE:
            //fprintf(out, "# Atribuiçcao\n");
            generate_mips_code(get_child(ast, 1), out);  // Gera código para o valor
            fprintf(out, "    sw $t0, %d($gp)\n", get_data(get_child(ast, 0)));  // Armazena o valor
            break;

        // Operação de soma
        case PLUS_NODE:
            //fprintf(out, "# Soma\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");  // Move para $t1
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    add $t0, $t1, $t0\n");  // Soma $t1 e $t0
            break;

        // Operação de subtração
        case MINUS_NODE:
            //fprintf(out, "# Subtracao\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");  // Move para $t1
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    sub $t0, $t1, $t0\n");  // Subtrai $t0 de $t1
            break;

        // Multiplicação
        case TIMES_NODE:
            //fprintf(out, "# Multiplicacao\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");  // Move para $t1
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    mul $t0, $t1, $t0\n");  // Multiplica $t1 e $t0
            break;

        // Divisão
        case OVER_NODE:
            //fprintf(out, "# Divisao\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");  // Move para $t1
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    div $t0, $t1, $t0\n");  // Divide $t1 por $t0
            break;

        // Operação de resto (módulo)
        case REST_NODE:
            //fprintf(out, "# Modulo\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");  // Move para $t1
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    rem $t0, $t1, $t0\n");  // Calcula o resto de $t1 por $t0
            break;

        // Menor que
        case LESS_NODE:
            //fprintf(out, "# Menor que\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    slt $t0, $t1, $t0\n");  // Menor que
            break;

        // Maior que
        case MORE_NODE:
            //fprintf(out, "# Maior que\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    sgt $t0, $t1, $t0\n");  // Maior que
            break;

        // Menor ou igual
        case LESS_EQUAL_NODE:
            //fprintf(out, "# Menor ou igual\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    sle $t0, $t1, $t0\n");  // Menor ou igual
            break;

        // Maior ou igual
        case MORE_EQUAL_NODE:
            //fprintf(out, "# Maior ou igual\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    sge $t0, $t1, $t0\n");  // Maior ou igual
            break;

        // Diferente
        case DIFERS_NODE:
            //fprintf(out, "# Diferente\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    sne $t0, $t1, $t0\n");  // Diferente
            break;

        // Igual
        case EQ_NODE:
            //fprintf(out, "# Igual\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    seq $t0, $t1, $t0\n");  // Igual
            break;

        // Lógica AND
        case AND_NODE:
            //fprintf(out, "# AND logico\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    and $t0, $t1, $t0\n");  // AND lógico
            break;

        // Lógica OR
        case OR_NODE:
            //fprintf(out, "# OR logico\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando esquerdo
            fprintf(out, "    move $t1, $t0\n");
            generate_mips_code(get_child(ast, 1), out);  // Operando direito
            fprintf(out, "    or $t0, $t1, $t0\n");  // OR lógico
            break;

        // Lógica NOT
        case NOT_NODE:
            //fprintf(out, "# NOT logico\n");
            generate_mips_code(get_child(ast, 0), out);  // Operando
            fprintf(out, "    not $t0, $t0\n");  // NOT lógico
            break;

        // Declaração de variável
        case VAR_DECL_NODE:
            //fprintf(out, "# Declaracao de variavel\n");
            // Nenhuma ação necessária em MIPS para uma declaração
            break;

        // Uso de variável
        case VAR_USE_NODE:
            //fprintf(out, "# Uso de variavel\n");
            fprintf(out, "    lw $t0, %d($gp)\n", get_data(ast));  // Carrega o valor da variável
            break;

        // IF
        case IF_NODE: {
            int label_else = generate_label();
            int label_end = generate_label();
            //fprintf(out, "# IF condicional\n");
            generate_mips_code(get_child(ast, 0), out);  // Gera o código para a condição
            fprintf(out, "    beq $t0, $zero, else_%d\n", label_else);  // Se a condição for falsa, vai para o else
            generate_mips_code(get_child(ast, 1), out);  // Gera o código para o bloco 'then'
            fprintf(out, "    j end_if_%d\n", label_end);  // Pula para o final do IF
            fprintf(out, "else_%d:\n", label_else);
            if (get_child_count(ast) == 3) {
                generate_mips_code(get_child(ast, 2), out);  // Gera o código para o bloco 'else'
            }
            fprintf(out, "end_if_%d:\n", label_end);
            break;
        }

        // Bloco de código
        case BLOCK_NODE:
            //fprintf(out, "# Bloco de codigo\n");
            for (int i = 0; i < get_child_count(ast); i++) {
                generate_mips_code(get_child(ast, i), out);  // Gera código para cada instrução no bloco
            }
            break;

        // Main
        case MAIN_NODE:
            //fprintf(out, "# Main\n");
            fprintf(out, ".globl main\nmain:\n");
            generate_mips_code(get_child(ast, 0), out);  // Gera código para o corpo do main
            fprintf(out, "    li $v0, 10\n    syscall\n");  // Finaliza o programa
            break;

        // For (loop)
        case FOR_NODE: {
            int label_start = generate_label();
            int label_end = generate_label();
            //fprintf(out, "# For loop\n");
            generate_mips_code(get_child(ast, 0), out);  // Inicialização do loop
            fprintf(out, "loop_start_%d:\n", label_start);
            generate_mips_code(get_child(ast, 1), out);  // Condição do loop
            fprintf(out, "    beq $t0, $zero, loop_end_%d\n", label_end);  // Verifica a condição
            generate_mips_code(get_child(ast, 3), out);  // Corpo do loop
            generate_mips_code(get_child(ast, 2), out);  // Atualização do loop
            fprintf(out, "    j loop_start_%d\n", label_start);  // Volta para o início
            fprintf(out, "loop_end_%d:\n", label_end);
            break;
        }

        // Escrita (print)
        case WRITE_NODE:
            //fprintf(out, "# Escreve valor\n");
            generate_mips_for_write_node(ast, out);
            break;

        // Leitura (scanf)
        case READ_NODE:
            //fprintf(out, "# Leitura de valor\n");
            fprintf(out, "    li $v0, 5\n    syscall\n");  // Chama syscall para ler inteiro
            fprintf(out, "    sw $v0, %d($gp)\n", get_data(get_child(ast, 0)));  // Armazena o valor lido
            break;

        // Função (declaração)
        case FUNC_DECL_NODE:
            //fprintf(out, "# Declaracao de funcao\n");
            // Ignorado neste momento, pois as funções estão sendo registradas
            break;

        // Função (uso)
        case FUNC_USE_NODE:
            //fprintf(out, "# Chamada de funcao\n");
            // Implementar chamada de função e pilha de ativação
            break;

        case FUNC_LIST_NODE:
            //fprintf(out, "# Lista de funções\n");
            for (int i = 0; i < get_child_count(ast); i++) {
                generate_mips_code(get_child(ast, i), out);  // Gera o código para cada função
            }
            break;

        case BOOL_VAL_NODE:
            //fprintf(out, "# Valor booleano\n");
            if (get_data(ast) == 1) {
                fprintf(out, "    li $t0, 1\n");  // 'true' é representado por 1
            } else {
                fprintf(out, "    li $t0, 0\n");  // 'false' é representado por 0
            }
            break;

        case INT_VAL_NODE:
            //fprintf(out, "# Valor inteiro\n");
            fprintf(out, "    li $t0, %d\n", get_data(ast));  // Carrega o valor inteiro imediato para $t0
            break;   

        case FLOAT_VAL_NODE:
            //fprintf(out, "# Valor float\n");
            fprintf(out, "    li.s $f0, %.2f\n", get_float_data(ast));  // Carrega o valor float imediato para $f0
            break;

        case STR_VAL_NODE:
            //fprintf(out, "# Valor string\n");
            fprintf(out, "    la $t0, _str%d\n", get_data(ast));  // Carrega o endereço da string para $t0
            break;

        // Conversão de float para int
        case F2I_NODE:
            //fprintf(out, "# Conversão de float para int\n");
            generate_mips_code(get_child(ast, 0), out);  // Gera o valor float
            fprintf(out, "    cvt.w.s $f0, $f0\n");      // Converte float para int (em $f0)
            fprintf(out, "    mfc1 $t0, $f0\n");         // Move o valor inteiro para $t0
            break;

        // Conversão de int para float
        case I2F_NODE:
            //fprintf(out, "# Conversão de int para float\n");
            generate_mips_code(get_child(ast, 0), out);  // Gera o valor int
            fprintf(out, "    mtc1 $t0, $f0\n");         // Move o valor int para $f0
            fprintf(out, "    cvt.s.w $f0, $f0\n");      // Converte o valor int para float
            break;

        default:
            fprintf(stderr, "Erro: Tipo de node nao reconhecido no codigo MIPS: %s\n", kind2str(get_kind(ast)));
            break;
    }
}

void generate_mips_for_write_node(AST *ast, FILE *out) {
    AST *expression = get_child(ast, 0);  // O que será escrito

    switch (get_node_type(expression)) {
        case STRING_TYPE_:
            // Para strings, carregar o endereço da string e usar syscall de impressão de string
            fprintf(out, "    la $a0, _str%d\n", get_data(expression)); // Carrega o endereço da string em $a0
            fprintf(out, "    li $v0, 4\n");  // Syscall 4 para impressão de string
            fprintf(out, "    syscall\n");
            break;

        case INT_TYPE_:
            // Para inteiros, mover o valor para o registrador $a0 e imprimir
            generate_mips_code(expression, out);  // Gera o valor que será impresso
            fprintf(out, "    move $a0, $t0\n");  // Move o valor para $a0
            fprintf(out, "    li $v0, 1\n");  // Syscall 1 para imprimir inteiros
            fprintf(out, "    syscall\n");
            break;

        case FLOAT_TYPE_:
            // Caso seja um float, manipula para impressão
            fprintf(out, "# Impressão de float\n");
            generate_mips_code(expression, out);  // Gera o valor float a ser impresso
            fprintf(out, "    mov.s $f12, $f0\n");  // Move o valor de $f0 para $f12 (float syscall usa $f12)
            fprintf(out, "    li $v0, 2\n");  // Código syscall 2 para impressão de float
            fprintf(out, "    syscall\n");
            break;

        case BOOL_TYPE_:
            // Para booleanos, verificar o valor e imprimir "true" ou "false"
            fprintf(out, "    lw $t0, %d($gp)\n", get_data(expression));  // Carrega o valor booleano da memória
            fprintf(out, "    li $t1, 1\n");  // Valor de true
            fprintf(out, "    beq $t0, $t1, print_true\n");  // Se for true, vai para print_true
            fprintf(out, "    li $v0, 4\n");  // Syscall para imprimir string
            fprintf(out, "    la $a0, false_str\n");  // Carrega a string "false"
            fprintf(out, "    syscall\n");  // Imprime "false"
            fprintf(out, "    j print_end\n");  // Pula para o final
            fprintf(out, "print_true:\n");
            fprintf(out, "    li $v0, 4\n");  // Syscall para imprimir string
            fprintf(out, "    la $a0, true_str\n");  // Carrega a string "true"
            fprintf(out, "    syscall\n");  // Imprime "true"
            fprintf(out, "print_end:\n");
            break;

        default:
            fprintf(stderr, "Erro: Tipo de dado nao suportado para impressao\n");
            break;
    }
}

void generate_mips_data_section(FILE *out) {
    fprintf(out, ".data\n");

    // Gera todas as strings usadas no programa
    for (int i = 0; i < get_string_table_size(st); i++) {
        fprintf(out, "_str%d: .asciiz \"%s\"\n", i, get_string_from_table(st, i));
    }
    // Adiciona as strings "true" e "false"
    fprintf(out, "true_str: .asciiz \"true\"\n");
    fprintf(out, "false_str: .asciiz \"false\"\n");
}
