
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "tables.h"

NodeKind current_context_node_kind;
extern FuncTable *ft;

// ----------------------------------------------------------------------------

extern StrTable *st;
extern VarTable *vt;
extern AST *ast_root;

typedef union {
    int   as_int;
    float as_float;
} Word;

int return_encountered = 0;  // Global para indicar se um retorno foi encontrado
Word return_value;           // Variável para armazenar o valor de retorno

// ----------------------------------------------------------------------------

// Data stack -----------------------------------------------------------------

#define STACK_SIZE 100

Word stack[STACK_SIZE];
int sp; // stack pointer

// All these ops should have a boundary check, buuuut... X_X

void pushi(int x) {
    stack[++sp].as_int = x;
}

int popi() {
    return stack[sp--].as_int;
}

void pushf(float x) {
    stack[++sp].as_float = x;
}

float popf() {
    return stack[sp--].as_float;
}

void init_stack() {
    for (int i = 0; i < STACK_SIZE; i++) {
        stack[i].as_int = 0;
    }
    sp = -1;
}

void print_stack() {
    printf("*** STACK: ");
    for (int i = 0; i <= sp; i++) {
        printf("%d ", stack[i].as_int);
    }
    printf("\n");
}

// ----------------------------------------------------------------------------

// Variables memory -----------------------------------------------------------

#define MEM_SIZE 100
#define ARRAY_MEM_SIZE 100  // Tamanho separado para memória de arrays

Word mem[MEM_SIZE];         // Memória para variáveis normais
Word array_mem[ARRAY_MEM_SIZE]; // Memória separada para arrays

void storei(int addr, int val) {
    mem[addr].as_int = val;
}

int loadi(int addr) {
    return mem[addr].as_int;
}

void storef(int addr, float val) {
    mem[addr].as_float = val;
}

float loadf(int addr) {
    return mem[addr].as_float;
}

void store_arrayi(int addr, int val) {
    array_mem[addr].as_int = val;
}

int load_arrayi(int addr) {
    return array_mem[addr].as_int;
}

void store_arrayf(int addr, float val) {
    array_mem[addr].as_float = val;
}

float load_arrayf(int addr) {
    return array_mem[addr].as_float;
}

void init_mem() {
    for (int addr = 0; addr < MEM_SIZE; addr++) {
        mem[addr].as_int = 0;
    }
    for (int addr = 0; addr < ARRAY_MEM_SIZE; addr++) {
        array_mem[addr].as_int = 0;
    }
}

// ----------------------------------------------------------------------------

// #define TRACE
#ifdef TRACE
#define trace(msg) printf("TRACE: %s\n", msg)
#else
#define trace(msg)
#endif

#define MAX_STR_SIZE 128
static char str_buf[MAX_STR_SIZE];
#define clear_str_buf() str_buf[0] = '\0'

void rec_run_ast(AST *ast);

void read_int(int var_idx) {
    int x;
    printf("read (int): ");
    scanf("%d", &x);
    storei(var_idx, x);
}

void read_real(int var_idx) {
    float x;
    printf("read (float32): ");
    scanf("%f", &x);
    storef(var_idx, x);
}

void read_bool(int var_idx) {
    int x;
    printf("read (bool - 0 = false, 1 = true): ");
    scanf("%d", &x);
    storei(var_idx, x);
}

void read_str(int var_idx) {
    printf("read (string): ");
    clear_str_buf();
    scanf("%s", str_buf);   // Did anyone say Buffer Overflow..? ;P
    storei(var_idx, add_string(st, str_buf));
}

void write_int() {
    printf("%d\n", popi());
}

void write_real() {
    printf("%.2f\n", popf());
}

void write_bool() {
    popi() == 0 ? printf("false\n") : printf("true\n");
}

// Helper function to write strings.
void escape_str(const char* s, char *n) {
    int i = 0, j = 0;
    char c;
    while ((c = s[i++]) != '\0') {
        if (c == '"') { continue; }
        else if (c == '\\' && s[i] == 'n') {
            n[j++] = '\n';
            i++;
        } else {
            n[j++] = c;
        }
    }
    n[j] = '\0';
}

void write_str() {
    int s = popi(); // String pointer
    clear_str_buf();
    escape_str(get_string(st, s), str_buf);
    printf(str_buf); // Weird language semantics, if printing a string, no new line.
    printf("\n");
}

// ----------------------------------------------------------------------------

/*void run_assign(AST *ast) {
    trace("assign");
    rec_run_ast(get_child(ast, 1));  // Executa a expressão do lado direito
    int addr = get_data(get_child(ast, 0));  // Pega o endereço da variável
    
    // Verifica se o valor atribuído é int ou float
    if (get_node_type(get_child(ast, 1)) == FLOAT_TYPE_) {
        float val = popf();  // Retira o valor da pilha como float
        storef(addr, val);   // Armazena o valor float na memória
    } else {
        int val = popi();    // Retira o valor da pilha como int
        storei(addr, val);   // Armazena o valor int na memória
    }
}*/
void run_assign(AST *ast) {
    trace("assign");

    // Verifica se o lado esquerdo é um acesso a array
    if (get_kind(get_child(ast, 0)) == ARRAY_ACCESS_NODE) {
        rec_run_ast(get_child(ast, 1));  // Avalia o lado direito (valor a ser atribuído)

        // Pega o índice do array e a posição
        int array_idx = get_data(get_child(get_child(ast, 0), 0));
        rec_run_ast(get_child(get_child(ast, 0), 1));  // Avalia a posição no array
        int index = popi();  // Pega o índice avaliado

        // Verifica se o índice está dentro do limite do array
        int array_size = load_arrayi(array_idx);
        if (index < 0 || index >= array_size) {
            printf("Runtime Error: Array index out of bounds\n");
            exit(EXIT_FAILURE);
        }

        // Armazena o valor no array
        int val = popi();  // Pega o valor a ser atribuído
        store_arrayi(array_idx + index + 1, val);  // "+1" para não sobrepor o tamanho do array
    } else {
        // Caso normal de atribuição a variável simples
        rec_run_ast(get_child(ast, 1));  // Executa a expressão do lado direito
        int addr = get_data(get_child(ast, 0));  // Pega o endereço da variável
        
        // Verifica se o valor atribuído é int ou float
        if (get_node_type(get_child(ast, 1)) == FLOAT_TYPE_) {
            float val = popf();  // Retira o valor da pilha como float
            storef(addr, val);   // Armazena o valor float na memória
        } else {
            int val = popi();    // Retira o valor da pilha como int
            storei(addr, val);   // Armazena o valor int na memória
        }
    }
}

void run_block(AST *ast) {
    trace("block");

    for (int i = 0; i < get_child_count(ast); i++) {
        if (return_encountered) {
            break;  // Se um retorno foi encontrado, interrompe a execução do bloco
        }
        rec_run_ast(get_child(ast, i));  // Executa recursivamente cada instrução no bloco
    }
}

void run_bool_val(AST *ast) {
    trace("bool_val");
    pushi(get_data(ast));  // Empilha o valor booleano (0 = false, 1 = true)
}

void run_eq(AST *ast) {
    trace("eq");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    
    // Verifica se a comparação envolve floats
    if (get_node_type(get_child(ast, 0)) == FLOAT_TYPE_ || get_node_type(get_child(ast, 1)) == FLOAT_TYPE_) {
        float right = popf();  // Desempilha o valor da direita como float
        float left = popf();   // Desempilha o valor da esquerda como float
        pushi(left == right);  // Empilha o resultado da comparação
    } else {
        int right = popi();    // Desempilha o valor da direita como int
        int left = popi();     // Desempilha o valor da esquerda como int
        pushi(left == right);  // Empilha o resultado da comparação
    }
}

void run_if(AST *ast) {
    trace("if");
    rec_run_ast(get_child(ast, 0));  // Executa a expressão condicional
    int condition = popi();          // Desempilha o resultado da condição
    if (condition) {
        rec_run_ast(get_child(ast, 1));  // Executa o bloco "then" se a condição for verdadeira
    } else if (get_child_count(ast) == 3) {
        rec_run_ast(get_child(ast, 2));  // Executa o bloco "else" se houver e a condição for falsa
    }
}

void run_int_val(AST *ast) {
    trace("int_val");
    pushi(get_data(ast));  // Empilha o valor inteiro
}

void run_lt(AST *ast) {
    trace("lt");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    
    // Verifica se a comparação envolve floats
    if (get_node_type(get_child(ast, 0)) == FLOAT_TYPE_ || get_node_type(get_child(ast, 1)) == FLOAT_TYPE_) {
        float right = popf();  // Desempilha o valor da direita como float
        float left = popf();   // Desempilha o valor da esquerda como float
        pushi(left < right);   // Empilha o resultado da comparação
    } else {
        int right = popi();    // Desempilha o valor da direita como int
        int left = popi();     // Desempilha o valor da esquerda como int
        pushi(left < right);   // Empilha o resultado da comparação
    }
}

void run_minus(AST *ast) {
    trace("minus");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    
    // Verifique os tipos dos nós
    if (get_node_type(get_child(ast, 0)) == FLOAT_TYPE_ || get_node_type(get_child(ast, 1)) == FLOAT_TYPE_) {
        // Operação com floats
        float right = popf();   // Desempilha o valor da direita como float
        float left = popf();    // Desempilha o valor da esquerda como float
        pushf(left - right);    // Empilha o resultado da subtração de floats
    } else {
        // Operação com inteiros
        int right = popi();     // Desempilha o valor da direita como inteiro
        int left = popi();      // Desempilha o valor da esquerda como inteiro
        pushi(left - right);    // Empilha o resultado da subtração de inteiros
    }
}

void run_over(AST *ast) {
    trace("over");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    
    // Verifique os tipos dos nós
    if (get_node_type(get_child(ast, 0)) == FLOAT_TYPE_ || get_node_type(get_child(ast, 1)) == FLOAT_TYPE_) {
        // Operação com floats
        float right = popf();   // Desempilha o valor da direita como float
        float left = popf();    // Desempilha o valor da esquerda como float
        if (right == 0.0f) {
            printf("Runtime Error: Division by zero.\n");
            exit(EXIT_FAILURE);
        }
        pushf(left / right);    // Empilha o resultado da divisão de floats
    } else {
        // Operação com inteiros
        int right = popi();     // Desempilha o valor da direita como inteiro
        int left = popi();      // Desempilha o valor da esquerda como inteiro
        if (right == 0) {
            printf("Runtime Error: Division by zero.\n");
            exit(EXIT_FAILURE);
        }
        pushi(left / right);    // Empilha o resultado da divisão de inteiros
    }
}

void run_plus(AST *ast) {
    trace("plus");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    
    // Verifique os tipos dos nós
    if (get_node_type(get_child(ast, 0)) == FLOAT_TYPE_ || get_node_type(get_child(ast, 1)) == FLOAT_TYPE_) {
        // Operação com floats
        float right = popf();   // Desempilha o valor da direita como float
        float left = popf();    // Desempilha o valor da esquerda como float
        pushf(left + right);    // Empilha o resultado da soma de floats
    } else {
        // Operação com inteiros
        int right = popi();     // Desempilha o valor da direita como inteiro
        int left = popi();      // Desempilha o valor da esquerda como inteiro
        pushi(left + right);    // Empilha o resultado da soma de inteiros
    }
}

void run_program(AST *ast) {
    trace("program");
    rec_run_ast(get_child(ast, 0)); // run var_list
    rec_run_ast(get_child(ast, 1)); // run block
}

void run_read(AST *ast) {
    trace("read");
    int var_idx = get_data(get_child(ast, 0));  // Pega o índice da variável
    switch (get_node_type(ast)) {
        case INT_TYPE_:   read_int(var_idx);   break;
        case FLOAT_TYPE_: read_real(var_idx);  break;
        case BOOL_TYPE_:  read_bool(var_idx);  break;
        case STRING_TYPE_: read_str(var_idx);  break;
        default: printf("Runtime Error: Invalid read type.\n");
                 exit(EXIT_FAILURE);
    }
}

void run_real_val(AST *ast) {
    trace("float_val");
    pushf(get_float_data(ast));  // Empilha o valor float
}

void run_repeat(AST *ast) {
    trace("for");
    rec_run_ast(get_child(ast, 0));  // Inicialização (ex: i := 0)
    
    while (1) {
        rec_run_ast(get_child(ast, 1));  // Condição (ex: i < 5)
        
        if (!popi()) break;              // Se a condição for falsa, sai do loop
        
        rec_run_ast(get_child(ast, 3));  // Executa o bloco de código (ex: print)
        
        rec_run_ast(get_child(ast, 2));  // Atualização (ex: i = i + 1)
    }
}

void run_str_val(AST *ast) {
    trace("str_val");
    pushi(get_data(ast));
}

void run_times(AST *ast) {
    trace("times");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    
    // Verifique os tipos dos nós
    if (get_node_type(get_child(ast, 0)) == FLOAT_TYPE_ || get_node_type(get_child(ast, 1)) == FLOAT_TYPE_) {
        // Operação com floats
        float right = popf();   // Desempilha o valor da direita como float
        float left = popf();    // Desempilha o valor da esquerda como float
        pushf(left * right);    // Empilha o resultado da multiplicação de floats
    } else {
        // Operação com inteiros
        int right = popi();     // Desempilha o valor da direita como inteiro
        int left = popi();      // Desempilha o valor da esquerda como inteiro
        pushi(left * right);    // Empilha o resultado da multiplicação de inteiros
    }
}

void run_var_decl(AST *ast) {
    trace("var_decl");
    // Nothing to do, memory was already cleared upon initialization.
}

void run_var_use(AST *ast) {
    trace("var_use");
    int var_idx = get_data(ast);      // Pega o índice da variável
    switch (get_node_type(ast)) {
        case INT_TYPE_:   pushi(loadi(var_idx));   break;
        case FLOAT_TYPE_: pushf(loadf(var_idx));   break;
        case BOOL_TYPE_: pushi(loadi(var_idx));   break;
        case STRING_TYPE_: pushi(loadi(var_idx));   break;
        default: printf("Runtime Error: Invalid variable type.\n");
                 exit(EXIT_FAILURE);
    }
}

void run_write(AST *ast) {
    trace("write");
    rec_run_ast(get_child(ast, 0));  // Executa a expressão a ser escrita
    switch (get_node_type(get_child(ast, 0))) {
        case INT_TYPE_:   write_int();   break;
        case FLOAT_TYPE_: write_real();  break;
        case BOOL_TYPE_:  write_bool();  break;
        case STRING_TYPE_: write_str();  break;
        default: printf("Runtime Error: Invalid write type.\n");
                 exit(EXIT_FAILURE);
    }
}

void run_i2f(AST* ast) {
    trace("i2f");
    rec_run_ast(get_child(ast, 0));  // Executa a expressão
    int int_val = popi();            // Converte int para float
    pushf((float)int_val);
}

void run_f2i(AST* ast) {
    trace("f2i");
    rec_run_ast(get_child(ast, 0));  // Executa a expressão
    float float_val = popf();        // Converte float para int
    pushi((int)float_val);
}

int is_assign_context() {
    // Aqui você verifica se o nó atual está sendo usado no contexto de atribuição.
    // Isso pode depender de como o AST foi construído.
    return (current_context_node_kind == ASSIGN_NODE);  // Exemplo simples
}

void run_array_access(AST *ast) {
    trace("array_access");

    // Avalia a expressão que representa o índice do array
    rec_run_ast(get_child(ast, 1)); 
    int index = popi();  // Pega o índice do topo da pilha

    // Pega a variável do array
    int array_idx = get_data(get_child(ast, 0)); 

    // Verifica se o índice está dentro dos limites do array
    int array_size = load_arrayi(array_idx);  // Primeiro valor é o tamanho do array
    if (index < 0 || index >= array_size) {
        printf("Runtime Error: Array index out of boundss\n");
        exit(EXIT_FAILURE);
    }

    // Acessa o valor na posição correta do array
    pushi(load_arrayi(array_idx + index + 1));  
}

void run_array_decl(AST *ast) {
    trace("array_decl");
    
    // Avalia o número de posições do array
    rec_run_ast(get_child(ast, 1));
    int array_size = popi();  // Tamanho do array
    
    if (array_size <= 0) {
        printf("Runtime Error: Invalid array size\n");
        exit(EXIT_FAILURE);
    }

    // Pega o índice da variável do array
    int array_idx = get_data(get_child(ast, 0));

    // Armazena o tamanho do array na primeira posição do array_mem
    store_arrayi(array_idx, array_size);

    // Inicializa o array com valores padrão (por exemplo, 0)
    for (int i = 1; i <= array_size; i++) {
        store_arrayi(array_idx + i, 0);  // Inicializa cada posição com 0
    }
}

void run_func_decl(AST *ast) {
    // Placeholder function, pois a função já foi registrada na tabela de funções.
    trace("function declaration");
}



void run_func_list(AST *ast) {
    trace("function list");
    
    for (int i = 0; i < get_child_count(ast); i++) {
        rec_run_ast(get_child(ast, i));  // Processa a declaração de cada função
    }
}

void run_func_use(AST *ast) {
    trace("func_use");

    int func_idx = get_data(ast);  // Pega o índice da função
    AST *func_ast = ft->t[func_idx].ast_node;  // Pega a AST da função a partir da tabela
    //printf("DEBUG: Funcao '%s' chamada\n", get_func_name(ft, func_idx));

    // Passa os parâmetros para a função
    AST *arg_list = get_child(ast, 0);  // Pega a lista de argumentos da chamada
    AST *param_list = get_child(func_ast, 0);  // Pega a lista de parâmetros da definição da função

    // Faz a correspondência entre argumentos e parâmetros
    for (int i = 0; i < get_child_count(arg_list); i++) {
        //printf("DEBUG: Passando parametro %d\n", i);
        rec_run_ast(get_child(arg_list, i));  // Executa o argumento
        int param_idx = get_data(get_child(param_list, i));  // Pega o índice do parâmetro

        // Armazena o argumento na posição do parâmetro na memória
        if (get_node_type(get_child(param_list, i)) == FLOAT_TYPE_) {
            float arg_val = popf();
            storef(param_idx, arg_val);
        } else {
            int arg_val = popi();
            storei(param_idx, arg_val);
        }
    }

    // Executa o corpo da função (o bloco de código da função está no segundo filho do nó de função)
    rec_run_ast(get_child(func_ast, 1));  // Executa o corpo da função (block)

    // Verifica se a função encontrou um retorno
    if (return_encountered) {
        //printf("DEBUG: Retorno capturado da funcao '%s'\n", get_func_name(ft, func_idx));
        return_encountered = 0;  // Reseta o flag de retorno após captura
        
        // Coloca o valor de retorno de volta na pilha para ser usado pela função chamadora
        if (get_func_type(ft, func_idx) == FLOAT_TYPE_) {
            pushf(return_value.as_float);
        } else {
            pushi(return_value.as_int);
        }
    } else {
        //printf("DEBUG: Funcao '%s' nao tem retorno\n", get_func_name(ft, func_idx));
    }
}



void run_return(AST *ast) {
    trace("return");

    // Verifica se o nó de retorno tem um filho (expressão a ser retornada)
    if (get_child_count(ast) > 0) {
        //printf("DEBUG: Retorno sendo executado\n");
        
        // Executa a expressão de retorno (filho do RETURN_NODE)
        rec_run_ast(get_child(ast, 0));  // Pega o filho do RETURN_NODE (a expressão de retorno)
        
        // Armazena o valor de retorno dependendo do tipo da expressão
        if (get_node_type(get_child(ast, 0)) == FLOAT_TYPE_) {
            return_value.as_float = popf();
            //printf("DEBUG: Valor de retorno (float): %.2f\n", return_value.as_float);
        } else {
            return_value.as_int = popi();
            //printf("DEBUG: Valor de retorno (int): %d\n", return_value.as_int);
        }
    }
    
    // Marca que encontramos um retorno, sinalizando para o interpretador que a função deve ser encerrada
    return_encountered = 1;  
    //printf("DEBUG: Retorno encontrado, fim da funcao.\n");
}

void run_main(AST *ast) {
    trace("main");
    // O main tem apenas um filho, que é o bloco da função.
    AST *main_block = get_child(ast, 0);  // O filho do MAIN_NODE é o bloco de código.
    rec_run_ast(main_block);  // Executa o bloco da função main.
}

void run_rest(AST *ast) {
    trace("rest");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    int right = popi();              // Desempilha o valor da direita
    int left = popi();               // Desempilha o valor da esquerda
    pushi(left % right);             // Empilha o resultado do módulo
}

void run_less(AST *ast) {
    trace("less");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    int right = popi();              // Desempilha o valor da direita
    int left = popi();               // Desempilha o valor da esquerda
    pushi(left < right);             // Empilha o resultado da comparação
}

void run_more(AST *ast) {
    trace("more");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    int right = popi();              // Desempilha o valor da direita
    int left = popi();               // Desempilha o valor da esquerda
    pushi(left > right);             // Empilha o resultado da comparação
}

void run_less_equal(AST *ast) {
    trace("less_equal");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    int right = popi();              // Desempilha o valor da direita
    int left = popi();               // Desempilha o valor da esquerda
    pushi(left <= right);            // Empilha o resultado da comparação
}

void run_more_equal(AST *ast) {
    trace("more_equal");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    int right = popi();              // Desempilha o valor da direita
    int left = popi();               // Desempilha o valor da esquerda
    pushi(left >= right);            // Empilha o resultado da comparação
}

void run_difers(AST *ast) {
    trace("difers");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    int right = popi();              // Desempilha o valor da direita
    int left = popi();               // Desempilha o valor da esquerda
    pushi(left != right);            // Empilha o resultado da comparação
}

void run_and(AST *ast) {
    trace("and");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    int right = popi();              // Desempilha o valor da direita
    int left = popi();               // Desempilha o valor da esquerda
    pushi(left && right);            // Empilha o resultado da operação AND
}

void run_or(AST *ast) {
    trace("or");
    rec_run_ast(get_child(ast, 0));  // Executa o lado esquerdo
    rec_run_ast(get_child(ast, 1));  // Executa o lado direito
    int right = popi();              // Desempilha o valor da direita
    int left = popi();               // Desempilha o valor da esquerda
    pushi(left || right);            // Empilha o resultado da operação OR
}

void run_not(AST *ast) {
    trace("not");
    rec_run_ast(get_child(ast, 0));  // Executa a expressão
    int val = popi();                // Desempilha o valor
    pushi(!val);                     // Empilha o resultado da operação NOT
}

void run_short_assign(AST *ast) {
    trace("short_assign");

    rec_run_ast(get_child(ast, 1));  // Executa o lado direito da atribuição (ex: 0)
    int val = popi();                // Pega o valor do topo da pilha
    int addr = get_data(get_child(ast, 0));  // Pega o índice da variável

    storei(addr, val);  // Armazena o valor na memória
}



void rec_run_ast(AST *ast) {
    current_context_node_kind = get_kind(ast);
    switch(get_kind(ast)) {
        case ASSIGN_NODE:   run_assign(ast);    break;
        case SHORT_ASSIGN_NODE:   run_short_assign(ast);    break;
        case EQ_NODE:       run_eq(ast);        break;
        case BLOCK_NODE:    run_block(ast);     break;
        case BOOL_VAL_NODE: run_bool_val(ast);  break;
        case IF_NODE:       run_if(ast);        break;
        case INT_VAL_NODE:  run_int_val(ast);   break;
        case LESS_NODE:     run_lt(ast);        break;
        case MORE_NODE:     run_more(ast);      break;
        case LESS_EQUAL_NODE: run_less_equal(ast); break;
        case MORE_EQUAL_NODE: run_more_equal(ast); break;
        case DIFERS_NODE:   run_difers(ast);    break;
        case AND_NODE:      run_and(ast);       break;
        case OR_NODE:       run_or(ast);        break;
        case NOT_NODE:      run_not(ast);       break;
        case MINUS_NODE:    run_minus(ast);     break;
        case OVER_NODE:     run_over(ast);      break;
        case PLUS_NODE:     run_plus(ast);      break;
        case REST_NODE:     run_rest(ast);      break;
        case PROGRAM_NODE:  run_program(ast);   break;
        case READ_NODE:     run_read(ast);      break;
        case FLOAT_VAL_NODE: run_real_val(ast);  break;
        case FOR_NODE:   run_repeat(ast);    break;
        case STR_VAL_NODE:  run_str_val(ast);   break;
        case TIMES_NODE:    run_times(ast);     break;
        case VAR_DECL_NODE: run_var_decl(ast);  break;
        case VAR_USE_NODE:  run_var_use(ast);   break;
        case WRITE_NODE:    run_write(ast);     break;
        case ARRAY_ACCESS_NODE: run_array_access(ast); break;
        case ARRAY_DECL_NODE:   run_array_decl(ast); break;
        case FUNC_LIST_NODE:    run_func_list(ast);    break;
        case FUNC_USE_NODE:     run_func_use(ast);     break;
        case FUNC_DECL_NODE:    run_func_decl(ast);    break;
        case MAIN_NODE:    run_main(ast);   break;
        case RETURN_NODE:       run_return(ast);    break;


        case I2F_NODE:      run_i2f(ast);       break;
        case F2I_NODE:      run_f2i(ast);       break;    

        default:
            fprintf(stderr, "Invalid kind: %s!\n", kind2str(get_kind(ast)));
            exit(EXIT_FAILURE);
    }
}

// ----------------------------------------------------------------------------

void run_ast(AST *ast) {
    init_stack();
    init_mem();
    rec_run_ast(ast);
}