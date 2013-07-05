#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "structs.h"
#include "frame_stack.h"

#include "loader.h"
#include "linker.h"
#include "initializer.h"

#define MAX_NUM_OF_CLASSES 65535

pc_t jvm_pc = {0, 0, 0};
frame_stack_t *jvm_stack;
/*heap_t *jvm_heap;*/
/*method_area_t *jvm_method_area;*/

// Array com as classes na memória
int jvm_number_of_classes = 0;
class_t *jvm_classes[MAX_NUM_OF_CLASSES];

Utf8_info_t* utf8_from_string(char* a) {
    Utf8_info_t* utf8 = (Utf8_info_t*) malloc(sizeof(Utf8_info_t));
    utf8->length = strlen(a);
    utf8->bytes = (u1*) a;
    return utf8;
}

int compare_utf8(Utf8_info_t* a, Utf8_info_t* b) {
    if (a->length == b->length) {
        return strncmp((char*) a->bytes,(char*) b->bytes, b->length);
    }
    return -1;
}


/* Procura e retorna classe com nome
 *
 * input: class_name Nome da classe
 * return: class ou NULL se não achar
 */
class_t *getClass(Utf8_info_t* class_name) {
    int i = 0;
    for (i = 0; i < jvm_number_of_classes; ++i) {
        if(compare_utf8(jvm_classes[i]->class_name, class_name) == 0) {
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
class_t *createClass(Utf8_info_t* class_name) {
    jvm_number_of_classes++;
    jvm_classes[jvm_number_of_classes] = (class_t*) malloc(sizeof(class_t));
    jvm_classes[jvm_number_of_classes]->class_name = class_name;
    jvm_classes[jvm_number_of_classes]->status = CLASSE_NAO_CARREGADA;

    return jvm_classes[jvm_number_of_classes];
}

code_attribute_t* getCodeAttribute(class_t* class, method_info_t* method) {
    int i = 0;
    for (i = 0; method->attributes_count; i++) {
        attribute_info_t* attribute = &(method->attributes[i]);

        u1* b = class->class_file.constant_pool[attribute->attribute_name_index].info.Utf8.bytes;
        u2 length = class->class_file.constant_pool[attribute->attribute_name_index].info.Utf8.length;

        if (strncmp("Code", (char*) b, length) == 0) {
            return &(attribute->info.code);
        }
    }
    printf("ERROR: Could not find Code attribute");
    exit(1);
}

int isSuperClassOf(class_t* super_class, class_t* sub_class) {
    //TODO
}

int isSameClass(class_t* a, class_t* b) {
    return (compare_utf8(a->class_name, b->class_name) == 0);
}


void throwException(class_t* exception_class) {
    // check for handlers 
    code_attribute_t* code_attribute = getCodeAttribute(jvm_pc.class, jvm_pc.method);
    u2 exception_table_length = code_attribute->exception_table_length;
    u2 i = 0;
    for (i = 0; i< exception_table_length; i++) {
        u2 catch_exception_class_index = jvm_pc.class->class_file.constant_pool[code_attribute->exception_table[i].catch_type].info.Class.name_index;
        class_t* catch_exception_class = getClass(&(jvm_pc.class->class_file.constant_pool[catch_exception_class_index].info.Utf8));
        if (code_attribute->exception_table[i].catch_type == 0 || (isSameClass(exception_class, catch_exception_class) || isSuperClassOf(catch_exception_class, exception_class))) {
            if (code_attribute->exception_table[i].start_pc >= jvm_pc.code_pc && code_attribute->exception_table[i].end_pc < jvm_pc.code_pc) {
                // Executar catch code
                jvm_pc.code_pc = code_attribute->exception_table[i].handler_pc;
                return;
            }
        }
    }

    //Exception não foi tratada
    // pop stack
    frame_t *frame = pop_frame_stack(&jvm_stack);
    if (frame == NULL) {
        printf("Exception não foi tratada. JVM será terminada.\n");
        exit(1);
    }

    // change PC
    jvm_pc = frame->return_address;

    // re-throw exception
    throwException(exception_class);

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
    frame_t *invokerFrame = peek_frame_stack(jvm_stack);
    any_type_t *operand = pop_operand_stack(&(frame->operand_stack));
    push_operand_stack(&(invokerFrame->operand_stack), operand);

    free(frame);
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

        if (strncmp((char*) method_name, (char*) b, length) == 0) {
            return method;
        }
    }
    printf("ERROR: Could not find method");
    exit(1);
}


int getNumberOfArguments(class_t* class, method_info_t* method) {
    u1* b = class->class_file.constant_pool[method->descriptor_index].info.Utf8.bytes;
    u2 length = class->class_file.constant_pool[method->descriptor_index].info.Utf8.length;

    int counter = 0;
    int i = 1;
    for (i = 1; i < length; i++) {
        switch (b[i]) {
            case 'B': //byte
            case 'C': //char
            case 'D': //double
            case 'F': //float
            case 'I': //integer
            case 'J': //long
            case 'S': //short
            case 'Z': //boolean
                counter++;
                break;
            case 'L': //reference
                for(;i < length && b[i] != ';'; i++); //go until ';'
                i++; // jump ';'

                counter++;

                break;
            case '[': //reference - array
                break;
            default:
                printf("Unexpected char on method descriptor: %c\n", b[i]);
                exit(1);
        }
    }
    return counter;
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


    //get number of arguments from classfile
    int number_of_arguments = getNumberOfArguments(class, method);

    // pop arguments from operand stack and
    // insert them on local_var
    int i = 0;
    int local_var_index = 0;
    for (i = 0; i < number_of_arguments; i++) {
        any_type_t *operand = pop_operand_stack(&(invokerFrame->operand_stack));
        frame->local_var.var[local_var_index] = (uint32_t) operand;
        local_var_index++;
    }
    assert(local_var_index == frame->local_var.size);


    push_frame_stack(&jvm_stack, frame);

    //set pc
    jvm_pc.class = class;
    jvm_pc.method = method;
    jvm_pc.code_pc = 0;

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
    args->val.reference_val.tag = ARRAY;
    args->val.reference_val.val.array.length = argc-2;
    args->val.reference_val.val.array.components = (any_type_t *) malloc(args->val.reference_val.val.array.length * sizeof(any_type_t));

    uint32_t i = 0;
    for (i = 0; i < args->val.reference_val.val.array.length; i++) {
        args->val.reference_val.val.array.components[i].tag = REFERENCE;
        args->val.reference_val.val.array.components[i].val.reference_val.tag = ARRAY;
        args->val.reference_val.val.array.components[i].val.reference_val.val.array.length = strlen(argv[i+2]);
        args->val.reference_val.val.array.components[i].val.reference_val.val.array.components = (any_type_t *) malloc(strlen(argv[i+2]) * sizeof(any_type_t));

        // TODO add support to unicode, it's only supporting ascii arguments for now
        unsigned long j = 0;
        for (j = 0; j < strlen(argv[i+2]); j++) {
            args->val.reference_val.val.array.components[i].val.reference_val.val.array.components[j].tag = PRIMITIVE;
            args->val.reference_val.val.array.components[i].val.reference_val.val.array.components[j].val.primitive_val.tag = CHAR;
            args->val.reference_val.val.array.components[i].val.reference_val.val.array.components[j].val.primitive_val.val.val_char = argv[i+2][j];
        }
    }

    class_t *class = createClass(utf8_from_string(argv[1]));

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

// Example code of how to work with any_type_t
/*pop them from operand stack*/
/*insert them on local_var*/
/*int i = 0;*/
/*int local_var_index = 0;*/

/*array_t* array = NULL;*/
/*object_t* object = NULL;*/
/*primitive_type_t* primitive = NULL;*/

/*for (i = 0; i < number_of_arguments; i++) {*/
/*any_type_t *operand = pop_operand_stack(&(invokerFrame->operand_stack));*/
/*switch(operand->tag) {*/
/*case REFERENCE:*/
/*switch(operand->val.reference_val.tag) {*/
/*case ARRAY:*/
/*array = &(operand->val.reference_val.val.array);*/
/*frame->local_var.var[local_var_index] = (uint32_t) array;*/
/*local_var_index++;*/
/*break;*/
/*case OBJECT:*/
/*object = &(operand->val.reference_val.val.object);*/
/*frame->local_var.var[local_var_index] = (uint32_t) object;*/
/*local_var_index++;*/
/*break;*/
/*}*/
/*break;*/
/*case PRIMITIVE:*/
/*primitive = &operand->val.primitive_val;*/
/*switch (primitive->tag) {*/
/*case BYTE:*/
/*frame->local_var.var[local_var_index] = (uint32_t) primitive->val.val8;*/
/*local_var_index++;*/
/*break;*/
/*case SHORT:*/
/*frame->local_var.var[local_var_index] = (uint32_t) primitive->val.val16;*/
/*local_var_index++;*/
/*break;*/
/*case INT:*/
/*frame->local_var.var[local_var_index] = (uint32_t) primitive->val.val32;*/
/*local_var_index++;*/
/*break;*/
/*case CHAR:*/
/*frame->local_var.var[local_var_index] = (uint32_t) primitive->val.val16;*/
/*local_var_index++;*/
/*break;*/
/*case LONG:*/
/*frame->local_var.var[local_var_index] = (uint32_t) (primitive->val.val64 >> 32);*/
/*local_var_index++;*/
/*frame->local_var.var[local_var_index] = (uint32_t) ((primitive->val.val64 << 32) >> 32);*/
/*local_var_index++;*/
/*break;*/
/*}*/
/*break;*/
/*}*/
/*}*/
/*assert(local_var_index == frame->local_var.size);*/
