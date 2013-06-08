#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "structs.h"
#include "frame_stack.h"

#include "loader.h"
#include "linker.h"
#include "initializer.h"

#define MAX_NUM_OF_CLASSES 65535

void *jvm_pc;
frame_stack_t *jvm_stack;
/*heap_t *jvm_heap;*/
/*method_area_t *jvm_method_area;*/

// Array com as classes na memória
int jvm_number_of_classes = 0;
class_t *jvm_classes[MAX_NUM_OF_CLASSES];

/* Procura e retorna classe com nome
 *
 * input: class_name Nome da classe
 * return: class ou NULL se não achar
 */
class_t *getClass(char* class_name) {
    int i = 0;
    for (i = 0; i < jvm_number_of_classes; ++i) {
        if (strcmp(jvm_classes[i]->class_name, class_name) == 0) {
            return jvm_classes[i];
        }
    }
    return NULL;
}

/* Cria e retorna classe com nome
 *
 * input: class_name Nome da classe
 * return: Classe criada
 */
class_t *createClass(char* class_name) {
    jvm_number_of_classes++;
    jvm_classes[jvm_number_of_classes] = (class_t*) malloc(sizeof(class_t));
    jvm_classes[jvm_number_of_classes]->class_name = class_name;
    jvm_classes[jvm_number_of_classes]->status = CLASSE_NAO_CARREGADA;
    
    return jvm_classes[jvm_number_of_classes];
}


void throwException() {
    // check for handlers

    // pop stack
    frame_t *frame = pop_frame_stack(&jvm_stack);
    if (frame == NULL) {
        printf("Exception não foi tratada. JVM será terminada.\n");
        exit(1);
    }
    
    // change PC
    jvm_pc = frame->return_address;

    // re-throw exception
    
    free(frame);
}

void returnFromFunction(return_value_t *retval) {
    // pop stack
    frame_t *frame = pop_frame_stack(&jvm_stack);
    if (frame == NULL) {
        // Execução retornou da função main. Programa executado com sucesso
        exit(0);
    }

    // change PC
    jvm_pc = frame->return_address;

    // maybe put return value on the new frame's operand stack

    free(frame);
}

void callMethod(char* class_name, char* method_name, args_t args) {
    class_t *class = NULL;
    class = getClass(class_name);

    if (class == NULL || class->status == CLASSE_NAO_CARREGADA) {
        class = createClass(class_name);
        loadClass(class);
    }
    if (class->status == CLASSE_NAO_LINKADA) {
        linkClass(class);
    }
    if (class->status == CLASSE_NAO_INICIALIZADA) {
        initializeClass(class);
    }

    frame_t *frame = (frame_t*) malloc(sizeof(frame_t));
    /*
     * criar frame usando tamanhos estabelecidos no classfile para method_name
     * preparar local variables e adicionar args no inicio
     * preparar operand stack
     * mudar pc
     */
    return;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("Instrução: Rode com 'jvm class_identifier [args]'\n");
        return 1;
    }

    // passar argv[2:] como argumento (array de strings)
    args_t args;
    args.number_of_args = argc - 2;
    args.args = (void *) malloc(args.number_of_args * sizeof(void*));
    int i = 0;
    for (i = 0; i < args.number_of_args; ++i) {
        args.args[i] = argv[i + 2];
    }
    callMethod(argv[1], "main", args);

    /*do {*/
        /*fetch an opcode;*/
        /*if (operands) fetch operands;*/
        /*execute the action for the opcode;*/
    /*} while (there is more to do);*/

    return 0;
}

