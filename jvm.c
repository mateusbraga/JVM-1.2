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

pc_t jvm_pc = NULL;
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
    // check for handlers TODO

    // pop stack
    frame_t *frame = pop_frame_stack(&jvm_stack);
    if (frame == NULL) {
        printf("Exception não foi tratada. JVM será terminada.\n");
        exit(1);
    }
    
    // change PC
    jvm_pc = frame->return_address;

    // re-throw exception
    throwException();
    
    free(frame);
}

void returnFromFunction() {
    // pop stack
    frame_t *frame = pop_frame_stack(&jvm_stack);
    if (frame->return_address.method == NULL) {
        // Execução retornou da função main. Programa executado com sucesso
        exit(0);
    }

    // change PC
    jvm_pc = frame->return_address;
    jvm_pc.code_pc++;

    // put return value on the new frame's operand stack 
    // TODO testar esse código
    frame_t *invokerFrame = peek_frame_stack(jvm_stack);
    any_type_t *operand = pop_operand_stack(&(frame->operand_stack));
    push_operand_stack(&(invokerFrame->operand_stack), operand);

    free(frame);
}

int utf8_compare(u1* a, u1* b, u2 length) {
    int i = 0;
    for (i = 0; i < length; i++) {
        if(a[i] != b[i]) {
            return a[i] - b[i];
        }
    }
    return 0;
}

method_info_t* getMethod(class_t* class, u1* method_name) {
    if (class->status == CLASSE_NAO_CARREGADA) {
        loadClass(class);
    }
    if (class->status == CLASSE_NAO_LINKADA) {
        linkClass(class);
    }
    if (class->status == CLASSE_NAO_INICIALIZADA) {
        initializeClass(class);
    }

    int i = 0;
    for (i = 0; class->class_file.methods_count; i++) {
        method_info_t* method = &(class->class_file.methods[i]);
        u1* b = class->class_file.constant_pool[method->name_index].info.Utf8.bytes;
        u2 length = class->class_file.constant_pool[method->name_index].info.Utf8.length;

        if (utf8_compare(method_name, b, length) == 0) {
            return method;
        }
    }
    printf("ERROR: Could not find method");
    exit(1);
}

code_attribute_t* getCodeAttribute(class_t* class, method_info_t* method) {
    int i = 0;
    for (i = 0; method->attributes_count; i++) {
        attribute_info_t* attribute = &(method->attributes[i]);

        u1* b = class->class_file.constant_pool[attribute->attribute_name_index].info.Utf8.bytes;
        u2 length = class->class_file.constant_pool[attribute->attribute_name_index].info.Utf8.length;

        if (utf8_compare((u1*) "Code", b, length) == 0) {
            return &(attribute->info.code);
        }
    }
    printf("ERROR: Could not find Code attribute");
    exit(1);
}

void callMethod(class_t* class, method_info_t* method) {
    if (class->status == CLASSE_NAO_CARREGADA) {
        loadClass(class);
    }
    if (class->status == CLASSE_NAO_LINKADA) {
        linkClass(class);
    }
    if (class->status == CLASSE_NAO_INICIALIZADA) {
        initializeClass(class);
    }

    code_attribute_t* code_attribute = getCodeAttribute(class, method);

    frame_t *invokerFrame = peek_frame_stack(jvm_stack);
    frame_t *frame = (frame_t*) malloc(sizeof(frame_t));
    frame->current_class = class;
    frame->current_method = method;
    frame->return_address = jvm_pc;
    frame->local_var.size = code_attribute->max_locals; 
    frame->local_var.var = (uint32_t*) malloc(frame->local_var.size * sizeof(uint32_t));
    frame->operand_stack.depth = 0;
    frame->operand_stack.head = 0;
    frame->operand_stack.size = code_attribute->max_stack;
    frame->operand_stack.operand = (any_type_t**) malloc(frame->operand_stack.size * sizeof(any_type_t**));
    

    //TODO get number of arguments from classfile
    // pop them from operand stack
    // insert them on local_var

    push_frame_stack(&jvm_stack, frame);


    /*
     * criar frame usando tamanhos estabelecidos no classfile para method_name
     * preparar local variables e adicionar args no inicio(está na pilha de operando)
     * preparar operand stack
     * mudar pc
     */
    //TODO set pc
    return;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("Instrução: Rode com 'jvm class_identifier [args]'\n");
        return 1;
    }

    // passar argv[2:] como argumento (array de strings)
    any_type_t *args = (any_type_t*) malloc(sizeof(any_type_t)); 
    args->tag = REFERENCE;
    args->reference_val.tag = ARRAY;
    args->reference_val.array.length = argc-2;
    args->reference_val.array.components = (any_type_t *) malloc(args->reference_val.array.length * sizeof(any_type_t));

    uint32_t i = 0;
    for (i = 0; i < args->reference_val.array.length; i++) {
        args->reference_val.array.components[i].tag = REFERENCE;
        args->reference_val.array.components[i].reference_val.tag = ARRAY;
        args->reference_val.array.components[i].reference_val.array.length = strlen(argv[i+2]);
        args->reference_val.array.components[i].reference_val.array.components = (any_type_t *) malloc(strlen(argv[i+2]) * sizeof(any_type_t));

        // TODO add support to unicode, it's only supporting ascii arguments for now
        unsigned long j = 0;
        for (j = 0; j < strlen(argv[i+2]); j++) {
            args->reference_val.array.components[i].reference_val.array.components[j].tag = PRIMITIVE;
            args->reference_val.array.components[i].reference_val.array.components[j].primitive_val.tag = CHAR;
            args->reference_val.array.components[i].reference_val.array.components[j].primitive_val.val_char = argv[i+2][j];
        }
    }

    class_t *class = createClass(argv[1]);

    method_info_t *main_method = getMethod(class, (u1*) "main");

    // frame inicial
    frame_t *frame = (frame_t*) malloc(sizeof(frame_t));
    frame->current_class = class;
    frame->current_method = main_method;
    frame->return_address.method = NULL;
    frame->return_address.code_pc = 0;
    frame->local_var.size = 0;
    frame->local_var.var = NULL;
    frame->operand_stack.depth = 0;
    frame->operand_stack.head = 0;
    frame->operand_stack.size = 1;
    frame->operand_stack.operand = (any_type_t**) malloc(frame->operand_stack.size * sizeof(any_type_t**));

    push_frame_stack(&jvm_stack, frame);
    push_operand_stack(&(frame->operand_stack), args);

    callMethod(class, main_method);

    /*do {*/
        /*fetch an opcode;*/
        /*if (operands) fetch operands;*/
        /*execute the action for the opcode;*/
    /*} while (there is more to do);*/

    return 0;
}

