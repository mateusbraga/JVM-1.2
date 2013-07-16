#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "frame_stack.h"
#include "structs.h"
#include "jvm.h"
#include "loader.h"
#include "linker.h"
#include "initializer.h"

extern frame_stack_t *jvm_stack;

extern pc_t jvm_pc;


/**
 * Empilha uma referência nula na pilha de operandos
 *
 */
void aconst_null(){
    printf("got into aconst_null\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = REFERENCE;
    operand->val.reference_val.tag = NULL_REFERENCE;
    operand->val.reference_val.val.val_null = NULL;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor int -1 na pilha de operandos
 *
 */
void iconst_m1(){
    printf("got into iconst_m1\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = -1;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor int 0 na pilha de operandos
 *
 */
void iconst_0(){
    printf("got into iconst_0\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 0;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor int 1 na pilha de operandos
 *
 */
void iconst_1(){
    printf("got into iconst_1\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 1;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor int 2 na pilha de operandos
 *
 */
void iconst_2(){
    printf("got into iconst_2\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 2;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor int 3 na pilha de operandos
 *
 */
void iconst_3(){
    printf("got into iconst_3\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 3;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor int 4 na pilha de operandos
 *
 */
void iconst_4(){
    printf("got into iconst_4\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 4;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor int 5 na pilha de operandos
 *
 */
void iconst_5(){
    printf("got into iconst_5\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 5;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor long 0 na pilha de operandos
 *
 */
void lconst_0(){
    printf("got into lconst_0\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = 0;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor long 1 na pilha de operandos
 *
 */
void lconst_1(){
    printf("got into lconst_1\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = 1;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}


/**
 * Empilha o valor float 0 na pilha de operandos
 *
 */
void fconst_0(){
    printf("got into fconst_0\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = 0;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor float 1 na pilha de operandos
 *
 */
void fconst_1(){
    printf("got into fconst_1\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = 1;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor float 2 na pilha de operandos
 *
 */
void fconst_2(){
    printf("got into fconst_2\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = 2;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor double 0 na pilha de operandos
 *
 */
void dconst_0(){
    printf("got into dconst_0\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = 0;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha o valor double 1 na pilha de operandos
 *
 */
void dconst_1(){
    printf("got into dconst_1\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = 1;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha byte b como int value na pilha de operandos.
 *
 */
void bipush(){
    printf("got into bipush\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b = code_attribute->code[jvm_pc.code_pc+1];
    int32_t value = (int32_t) b;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = value;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

/**
 * Empilha short b como int value na pilha de operandos.
 *
 */
void sipush(){
    printf("got into sipush\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    int16_t aux = (b1 << 8) | b2;
    int32_t value = (int32_t) aux;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = value;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}


/**
 * Empilha (String, Integer, Float) constant_pool[index] na pilha de operandos.
 *
 */
void ldc(){
    printf("got into ldc\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b = code_attribute->code[jvm_pc.code_pc+1];
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));
    u4 bytes;
    u2 bytes1;

    switch(jvm_pc.currentClass->class_file.constant_pool[b].tag){
        case CONSTANT_Integer:
            bytes = jvm_pc.currentClass->class_file.constant_pool[b].info.Integer.bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = INT;
            operand->val.primitive_val.val.val32 = bytes;
            break;
        case CONSTANT_Float:
            bytes = jvm_pc.currentClass->class_file.constant_pool[b].info.Float.bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = FLOAT;
            operand->val.primitive_val.val.val_float = bytes;
            break;
        case CONSTANT_String:
            bytes1 = jvm_pc.currentClass->class_file.constant_pool[b].info.String.string_index;
            Utf8_info_t *Utf8_cod = &(jvm_pc.currentClass->class_file.constant_pool[bytes1].info.Utf8);
            operand = utf8_to_array_reference(Utf8_cod);
            break;
        default:
            printf("Erro \n");
            break;
    }

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha (String, Integer, Float) constant_pool[wide_index] na pilha de operandos.
 *
 */
void ldc_w(){
    printf("got into ldc_w\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 b = (b1<<8)|b2;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    u4 bytes;
    u2 bytes1;
    switch(jvm_pc.currentClass->class_file.constant_pool[b].tag){
        case CONSTANT_Integer:
            bytes = jvm_pc.currentClass->class_file.constant_pool[b].info.Integer.bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = INT;
            operand->val.primitive_val.val.val32 = bytes;
            break;
        case CONSTANT_Float:
            bytes = jvm_pc.currentClass->class_file.constant_pool[b].info.Float.bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = FLOAT;
            operand->val.primitive_val.val.val_float = bytes;
            break;
        case CONSTANT_String:
            bytes1 = jvm_pc.currentClass->class_file.constant_pool[b].info.String.string_index;
            Utf8_info_t *Utf8_cod = &(jvm_pc.currentClass->class_file.constant_pool[bytes1].info.Utf8);
            operand = utf8_to_array_reference(Utf8_cod);
            break;
        default:
            printf("Erro \n");
            break;
    }

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha (Long, Double) constant_pool[index] na pilha de operandos.
 *
 */
void ldc2_w(){
    printf("got into ldc2_w\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 b = (b1<<8)|b2;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));
    uint64_t high_bytes;
    uint64_t low_bytes;

    switch(jvm_pc.currentClass->class_file.constant_pool[b].tag){
        case CONSTANT_Long:
            // Testado
            high_bytes = jvm_pc.currentClass->class_file.constant_pool[b].info.Long.high_bytes;
            low_bytes = jvm_pc.currentClass->class_file.constant_pool[b].info.Long.low_bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = LONG;
            operand->val.primitive_val.val.val64 = (high_bytes<<32)|low_bytes;
            break;
        case CONSTANT_Double:
            // Testado
            high_bytes = jvm_pc.currentClass->class_file.constant_pool[b].info.Long.high_bytes;
            low_bytes = jvm_pc.currentClass->class_file.constant_pool[b].info.Long.low_bytes;
            uint64_t double_bytes = (high_bytes<<32) | low_bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = DOUBLE;
            memmove(&(operand->val.primitive_val.val.val_double), &(double_bytes), sizeof(double));
            break;
        default:
            printf("Erro \n");
            break;
    }

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha na pilha de operandos any_type_t value de uma local_var[index]. Valida para todos os tload()
 *
 */
void tload(){
    printf("got into tload\n");
    any_type_t* operand;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];
    operand = (any_type_t*) malloc(sizeof(any_type_t));

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand = frame->local_var.var[index];

    push_operand_stack(&(frame->operand_stack), operand);

}

/**
 * Empilha na pilha de operandos any_type_t value de uma local_var[0]. Valida para todos os tload_0()
 *
 */
void tload_0(){
    printf("got into tload_0\n");
    any_type_t* operand;

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand = frame->local_var.var[0];

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha na pilha de operandos any_type_t value de uma local_var[1]. Valida para todos os tload_1()
 *
 */
void tload_1(){
    printf("got into tload_1\n");
    any_type_t* operand;

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand = frame->local_var.var[1];

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha na pilha de operandos any_type_t value de uma local_var[2]. Valida para todos os tload_2()
 *
 */
void tload_2(){
    printf("got into tload_2\n");
    any_type_t* operand;

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand = frame->local_var.var[2];

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha na pilha de operandos any_type_t value de uma local_var[3]. Valida para todos os tload_3()
 *
 */
void tload_3(){
    printf("got into tload_3\n");
    any_type_t* operand;

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand = frame->local_var.var[3];

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Carrega um anytype_t value de uma local_var[index]. Valida para todos os taload()
 *
 */
void taload(){
    printf("got into taload\n");
    any_type_t *index, *arrayref, *operand;
    uint32_t int_index;
    frame_t *frame = peek_frame_stack(jvm_stack);

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    arrayref = pop_operand_stack(&(frame->operand_stack));
    index = pop_operand_stack(&(frame->operand_stack));

    int_index = index->val.primitive_val.val.val32;

    *operand = arrayref->val.reference_val.val.array.components[int_index];
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Atribui any_type_t value a local_var[index]. Valida para todos os tstore()
 *
 */
void tstore(){
    printf("got into tstore\n");
    any_type_t *value;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    value = pop_operand_stack(&(frame->operand_stack));

    frame->local_var.var[index] = value;
    if(value->val.primitive_val.tag == LONG|| value->val.primitive_val.tag == DOUBLE)
            frame->local_var.var[index+1] = value;
}

/**
 * Atribui any_type_t value a local_var[index]. Valida para todos os tstore_0()
 *
 */
void tstore_0(){
    printf("got into tstore_0\n");
    any_type_t *value;

    frame_t *frame = peek_frame_stack(jvm_stack);
    value = pop_operand_stack(&(frame->operand_stack));

    frame->local_var.var[0] = value;
    if(value->val.primitive_val.tag == LONG|| value->val.primitive_val.tag == DOUBLE)
            frame->local_var.var[1] = value;
}

/**
 * Atribui any_type_t value a local_var[index]. Valida para todos os tstore_1()
 *
 */
void tstore_1(){
    printf("got into tstore_1\n");
    any_type_t *value;

    frame_t *frame = peek_frame_stack(jvm_stack);
    value = pop_operand_stack(&(frame->operand_stack));

    frame->local_var.var[1] = value;
    if(value->val.primitive_val.tag == LONG|| value->val.primitive_val.tag == DOUBLE)
            frame->local_var.var[2] = value;
}

/**
 * Atribui any_type_t value a local_var[index]. Valida para todos os tstore_2()
 *
 */
void tstore_2(){
    printf("got into tstore_2\n");
    any_type_t *value;

    frame_t *frame = peek_frame_stack(jvm_stack);
    value = pop_operand_stack(&(frame->operand_stack));

    frame->local_var.var[2] = value;
    if(value->val.primitive_val.tag == LONG|| value->val.primitive_val.tag == DOUBLE)
            frame->local_var.var[3] = value;
}

/**
 * Atribui any_type_t value a local_var[index]. Valida para todos os tstore_3()
 *
 */
void tstore_3(){
    printf("got into tstore_3\n");
    any_type_t *value;

    frame_t *frame = peek_frame_stack(jvm_stack);
    value = pop_operand_stack(&(frame->operand_stack));

    frame->local_var.var[3] = value;
    if(value->val.primitive_val.tag == LONG|| value->val.primitive_val.tag == DOUBLE)
            frame->local_var.var[4] = value;
}

void tastore(){
    printf("got into tastore\n");
    any_type_t *index, *arrayref, *value;
    uint32_t int_index;
    frame_t *frame = peek_frame_stack(jvm_stack);

    arrayref = pop_operand_stack(&(frame->operand_stack));
    index = pop_operand_stack(&(frame->operand_stack));
    value = pop_operand_stack(&(frame->operand_stack));

    int_index = index->val.primitive_val.val.val32;

    arrayref->val.reference_val.val.array.components[int_index] = *value;
}

void pop(){
    printf("got into pop\n");
    frame_t *frame = peek_frame_stack(jvm_stack);
    pop_operand_stack(&(frame->operand_stack));
}

void pop2(){
    printf("got into pop2\n");
    frame_t *frame = peek_frame_stack(jvm_stack);

    any_type_t *value = (any_type_t*) malloc(sizeof(any_type_t));
    value = pop_operand_stack(&(frame->operand_stack));
    if(value->val.primitive_val.tag != LONG && value->val.primitive_val.tag != DOUBLE)
        pop_operand_stack(&(frame->operand_stack));
}

void dup(){
    printf("got into dup\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand = pop_operand_stack(&(frame->operand_stack));

    push_operand_stack(&(frame->operand_stack), operand);
    push_operand_stack(&(frame->operand_stack), operand);

}

void dup_x1(){
    printf("got into dup_x1\n");
    any_type_t *operand1 = (any_type_t*) malloc(sizeof(any_type_t));
    any_type_t *operand2 = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);

    operand1 = pop_operand_stack(&(frame->operand_stack));
    operand2 = pop_operand_stack(&(frame->operand_stack));

    if(operand1->val.primitive_val.tag == LONG || operand2->val.primitive_val.tag == LONG || operand1->val.primitive_val.tag == DOUBLE || operand2->val.primitive_val.tag == DOUBLE)
        exit(1); //algum erro

    push_operand_stack(&(frame->operand_stack), operand1);
    push_operand_stack(&(frame->operand_stack), operand2);
    push_operand_stack(&(frame->operand_stack), operand1);


}

void dup_x2(){
    printf("got into dup_x2\n");
    any_type_t *operand1, *operand2, *operand3;
    frame_t *frame = peek_frame_stack(jvm_stack);

    operand1 = pop_operand_stack(&(frame->operand_stack));
    operand2 = pop_operand_stack(&(frame->operand_stack));
    operand3 = pop_operand_stack(&(frame->operand_stack));

    push_operand_stack(&(frame->operand_stack), operand1);
    if(operand2->val.primitive_val.tag != LONG && operand2->val.primitive_val.tag != DOUBLE)
        push_operand_stack(&(frame->operand_stack), operand3);
    push_operand_stack(&(frame->operand_stack), operand2);
    push_operand_stack(&(frame->operand_stack), operand1);

}

void dup2(){
    printf("got into dup2\n");
    any_type_t *operand1, *operand2;
    frame_t *frame = peek_frame_stack(jvm_stack);

    operand1 = pop_operand_stack(&(frame->operand_stack));
    operand2 = pop_operand_stack(&(frame->operand_stack));

    push_operand_stack(&(frame->operand_stack), operand1);
    if(operand1->val.primitive_val.tag != LONG && operand1->val.primitive_val.tag != DOUBLE)
        push_operand_stack(&(frame->operand_stack), operand2);
    push_operand_stack(&(frame->operand_stack), operand1);
    if(operand1->val.primitive_val.tag != LONG && operand1->val.primitive_val.tag != DOUBLE)
        push_operand_stack(&(frame->operand_stack), operand2);

}

void dup2_x1(){
    printf("got into dup2_x1\n");
    any_type_t *operand1, *operand2, *operand3;
    frame_t *frame = peek_frame_stack(jvm_stack);

    operand1 = pop_operand_stack(&(frame->operand_stack));
    operand2 = pop_operand_stack(&(frame->operand_stack));
    operand3 = pop_operand_stack(&(frame->operand_stack));

    push_operand_stack(&(frame->operand_stack), operand1);
    if(operand1->val.primitive_val.tag != LONG && operand1->val.primitive_val.tag != DOUBLE)
        push_operand_stack(&(frame->operand_stack), operand2);
    push_operand_stack(&(frame->operand_stack), operand3);
    push_operand_stack(&(frame->operand_stack), operand1);
    if(operand1->val.primitive_val.tag != LONG && operand1->val.primitive_val.tag != DOUBLE)
        push_operand_stack(&(frame->operand_stack), operand2);

}

void dup2_x2(){
    printf("got into dup2_x2\n");
    any_type_t *operand1, *operand2, *operand3, *operand4;
    frame_t *frame = peek_frame_stack(jvm_stack);

    operand1 = pop_operand_stack(&(frame->operand_stack));
    operand2 = pop_operand_stack(&(frame->operand_stack));
    operand3 = pop_operand_stack(&(frame->operand_stack));
    operand4 = pop_operand_stack(&(frame->operand_stack));

    push_operand_stack(&(frame->operand_stack), operand1);
    if(operand1->val.primitive_val.tag != LONG && operand1->val.primitive_val.tag != DOUBLE)
        push_operand_stack(&(frame->operand_stack), operand2);
    push_operand_stack(&(frame->operand_stack), operand3);
    if(operand3->val.primitive_val.tag != LONG && operand3->val.primitive_val.tag != DOUBLE)
        push_operand_stack(&(frame->operand_stack), operand4);
    push_operand_stack(&(frame->operand_stack), operand1);
    if(operand1->val.primitive_val.tag != LONG && operand1->val.primitive_val.tag != DOUBLE)
        push_operand_stack(&(frame->operand_stack), operand2);
}

void swap(){
    printf("got into swap\n");
    any_type_t *operand1 = (any_type_t*) malloc(sizeof(any_type_t));
    any_type_t *operand2 = (any_type_t*) malloc(sizeof(any_type_t));

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand1 = pop_operand_stack(&(frame->operand_stack));
    operand2 = pop_operand_stack(&(frame->operand_stack));

    if(operand1->val.primitive_val.tag == LONG || operand2->val.primitive_val.tag == LONG || operand1->val.primitive_val.tag == DOUBLE || operand2->val.primitive_val.tag == DOUBLE)
        exit(1); // algum erro

    push_operand_stack(&(frame->operand_stack), operand1);
    push_operand_stack(&(frame->operand_stack), operand2);
}

void iadd(){
    printf("got into iadd\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (op1->val.primitive_val.val.val32)+(op2->val.primitive_val.val.val32);

    push_operand_stack(&(frame->operand_stack), operand);
}

void ladd(){
    printf("got into ladd\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (op1->val.primitive_val.val.val64)+(op2->val.primitive_val.val.val64);

    push_operand_stack(&(frame->operand_stack), operand);
}

void fadd(){
    printf("got into fadd\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = (op1->val.primitive_val.val.val_float)+(op2->val.primitive_val.val.val_float);

    push_operand_stack(&(frame->operand_stack), operand);
}

void dadd(){
    printf("got into dadd\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = (op1->val.primitive_val.val.val_double)+(op2->val.primitive_val.val.val_double);

    push_operand_stack(&(frame->operand_stack), operand);
}

void isub(){
    printf("got into isub\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (op1->val.primitive_val.val.val32)-(op2->val.primitive_val.val.val32);

    push_operand_stack(&(frame->operand_stack), operand);
}

void lsub(){
    printf("got into lsub\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (op1->val.primitive_val.val.val64)-(op2->val.primitive_val.val.val64);

    push_operand_stack(&(frame->operand_stack), operand);
}

void fsub(){
    printf("got into fsub\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = (op1->val.primitive_val.val.val_float)-(op2->val.primitive_val.val.val_float);

    push_operand_stack(&(frame->operand_stack), operand);
}

void dsub(){
    printf("got into dsub\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = (op1->val.primitive_val.val.val_double)-(op2->val.primitive_val.val.val_double);

    push_operand_stack(&(frame->operand_stack), operand);
}

void imul(){
    printf("got into imul\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (op1->val.primitive_val.val.val32)*(op2->val.primitive_val.val.val32);

    push_operand_stack(&(frame->operand_stack), operand);
}

void lmul(){
    printf("got into lmul\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (op1->val.primitive_val.val.val64)*(op2->val.primitive_val.val.val64);

    push_operand_stack(&(frame->operand_stack), operand);
}

void fmul(){
    printf("got into fmul\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = (op1->val.primitive_val.val.val_float)*(op2->val.primitive_val.val.val_float);

    push_operand_stack(&(frame->operand_stack), operand);
}

void dmul(){
    printf("got into dmul\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = (op1->val.primitive_val.val.val_double)*(op2->val.primitive_val.val.val_double);

    push_operand_stack(&(frame->operand_stack), operand);
}

void idiv(){
    printf("got into idiv\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (op1->val.primitive_val.val.val32)/(op2->val.primitive_val.val.val32);

    push_operand_stack(&(frame->operand_stack), operand);
}

void ldiv_op(){
    printf("got into ldiv_op\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (op1->val.primitive_val.val.val64)/(op2->val.primitive_val.val.val64);

    push_operand_stack(&(frame->operand_stack), operand);
}

void fdiv(){
    printf("got into fdiv\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = (op1->val.primitive_val.val.val_float)/(op2->val.primitive_val.val.val_float);

    push_operand_stack(&(frame->operand_stack), operand);
}

void ddiv(){
    printf("got into ddiv\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = (op1->val.primitive_val.val.val_double)/(op2->val.primitive_val.val.val_double);

    push_operand_stack(&(frame->operand_stack), operand);
}

void irem(){
    printf("got into irem\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (op1->val.primitive_val.val.val32)-((op1->val.primitive_val.val.val32)/(op2->val.primitive_val.val.val32))*(op2->val.primitive_val.val.val32);

    push_operand_stack(&(frame->operand_stack), operand);
}

void lrem(){
    printf("got into lrem\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (op1->val.primitive_val.val.val64)-((op1->val.primitive_val.val.val64)/(op2->val.primitive_val.val.val64))*(op2->val.primitive_val.val.val64);

    push_operand_stack(&(frame->operand_stack), operand);
}

void frem(){
    printf("got into frem\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = (op1->val.primitive_val.val.val_float)-((op1->val.primitive_val.val.val_float)/(op2->val.primitive_val.val.val_float))*(op2->val.primitive_val.val.val_float);

    push_operand_stack(&(frame->operand_stack), operand);
}

void drem_op(){
    printf("got into drem_op\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = (op1->val.primitive_val.val.val_double)-((op1->val.primitive_val.val.val_double)/(op2->val.primitive_val.val.val_double))*(op2->val.primitive_val.val.val_double);

    push_operand_stack(&(frame->operand_stack), operand);
}


void ineg(){
    printf("got into ineg\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 0-(op1->val.primitive_val.val.val32);

    push_operand_stack(&(frame->operand_stack), operand);
}

void lneg(){
    printf("got into lneg\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = 0-(op1->val.primitive_val.val.val64);

    push_operand_stack(&(frame->operand_stack), operand);
}

void fneg(){
    printf("got into fneg\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = 0-(op1->val.primitive_val.val.val_float);

    push_operand_stack(&(frame->operand_stack), operand);
}

void dneg(){
    printf("got into dneg\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = 0-(op1->val.primitive_val.val.val_double);

    push_operand_stack(&(frame->operand_stack), operand);
}

void ishl(){
    printf("got into ishl\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int32_t value_op2;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op2 = op2->val.primitive_val.val.val32;
    value_op2 = (value_op2 & 0x00FF) & 0x001F;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (op1->val.primitive_val.val.val32 << value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}

void lshl(){
    printf("got into lshl\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int64_t value_op2;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op2 = op2->val.primitive_val.val.val64;
    value_op2 = (value_op2 & 0x00FF) & 0x003F;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (op1->val.primitive_val.val.val64 << value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}

void ishr(){
    printf("got into ishr\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int32_t value_op2;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op2 = op2->val.primitive_val.val.val32;
    value_op2 = (value_op2 & 0x00FF) & 0x001F;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (op1->val.primitive_val.val.val32 >> value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}

void lshr(){
    printf("got into lshr\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int64_t value_op2;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op2 = op2->val.primitive_val.val.val64;
    value_op2 = (value_op2 & 0x00FF) & 0x003F;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (op1->val.primitive_val.val.val64 >> value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}
void iushr(){
    printf("got into iushr\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    uint32_t value_op2;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op2 = (uint32_t) op2->val.primitive_val.val.val32;
    value_op2 = (value_op2 & 0x00FF) & 0x001F;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (op1->val.primitive_val.val.val32 >> value_op2);

    push_operand_stack(&(frame->operand_stack), operand);

}

void lushr(){
    printf("got into lushr\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    uint64_t value_op2;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op2 = (uint64_t) op2->val.primitive_val.val.val64;
    value_op2 = (value_op2 & 0x00FF) & 0x003F;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (op1->val.primitive_val.val.val64 >> value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}


void iand(){
    printf("got into iand\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int32_t value_op2, value_op1;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op1 = op1->val.primitive_val.val.val32;
    value_op2 = op2->val.primitive_val.val.val32;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (value_op1 & value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}

void land(){
    printf("got into land\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int64_t value_op2, value_op1;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op1 = op1->val.primitive_val.val.val64;
    value_op2 = op2->val.primitive_val.val.val64;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (value_op1 & value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}

void ior(){
    printf("got into ior\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int32_t value_op2, value_op1;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op1 = op1->val.primitive_val.val.val32;
    value_op2 = op2->val.primitive_val.val.val32;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (value_op1 | value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}

void lor(){
    printf("got into lor\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int64_t value_op2, value_op1;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op1 = op1->val.primitive_val.val.val64;
    value_op2 = op2->val.primitive_val.val.val64;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (value_op1 | value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}

void ixor(){
    printf("got into ixor\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int32_t value_op2, value_op1;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op1 = op1->val.primitive_val.val.val32;
    value_op2 = op2->val.primitive_val.val.val32;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (value_op1 ^ value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}

void lxor(){
    printf("got into lxor\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int64_t value_op2, value_op1;

    op1 = pop_operand_stack(&(frame->operand_stack));
    op2 = pop_operand_stack(&(frame->operand_stack));

    value_op1 = op1->val.primitive_val.val.val64;
    value_op2 = op2->val.primitive_val.val.val64;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (value_op1 ^ value_op2);

    push_operand_stack(&(frame->operand_stack), operand);
}

void i2l(){
    printf("got into i2l\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (int64_t) op1->val.primitive_val.val.val32;

    push_operand_stack(&(frame->operand_stack), operand);
}

void i2f(){
    printf("got into i2f\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = (float) op1->val.primitive_val.val.val32;

    push_operand_stack(&(frame->operand_stack), operand);
}

void i2d(){
    printf("got into i2d\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = (double) op1->val.primitive_val.val.val32;

    push_operand_stack(&(frame->operand_stack), operand);
}

void l2i(){
    printf("got into l2i\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (int32_t) op1->val.primitive_val.val.val64;

    push_operand_stack(&(frame->operand_stack), operand);
}

void l2f(){
    printf("got into l2f\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = (float) op1->val.primitive_val.val.val64;

    push_operand_stack(&(frame->operand_stack), operand);
}

void l2d(){
    printf("got into l2d\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_float = (double) op1->val.primitive_val.val.val64;

    push_operand_stack(&(frame->operand_stack), operand);
}

void f2i(){
    printf("got into f2i\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (int32_t) op1->val.primitive_val.val.val_float;

    push_operand_stack(&(frame->operand_stack), operand);
}

void f2l(){
    printf("got into f2l\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (int64_t) op1->val.primitive_val.val.val_float;

    push_operand_stack(&(frame->operand_stack), operand);
}

void f2d(){
    printf("got into f2d\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = (double) op1->val.primitive_val.val.val_float;

    push_operand_stack(&(frame->operand_stack), operand);
}

void d2i(){
    printf("got into d2i\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = (int32_t) op1->val.primitive_val.val.val_double;

    push_operand_stack(&(frame->operand_stack), operand);
}

void d2l(){
    printf("got into d2l\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = (int64_t) op1->val.primitive_val.val.val_double;

    push_operand_stack(&(frame->operand_stack), operand);
}

void d2f(){
    printf("got into d2f\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = (float) op1->val.primitive_val.val.val_double;

    push_operand_stack(&(frame->operand_stack), operand);
}

void i2b(){
    printf("got into i2b\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = BYTE;
    operand->val.primitive_val.val.val8 = (int8_t) op1->val.primitive_val.val.val32;

    push_operand_stack(&(frame->operand_stack), operand);
}

void i2c(){
    printf("got into i2c\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = CHAR;
    operand->val.primitive_val.val.val_char = (int8_t) op1->val.primitive_val.val.val32;

    push_operand_stack(&(frame->operand_stack), operand);
}

void i2s(){
    printf("got into i2s\n");
    any_type_t *op1, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);

    op1 = pop_operand_stack(&(frame->operand_stack));

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = SHORT;
    operand->val.primitive_val.val.val16 = (uint16_t) op1->val.primitive_val.val.val32;

    push_operand_stack(&(frame->operand_stack), operand);
}

void lcmp(){
    printf("got into lcmp\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int8_t value;

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    if(op1->val.primitive_val.val.val64 > op2->val.primitive_val.val.val64)
        value = 1;
    else if(op1->val.primitive_val.val.val64 < op2->val.primitive_val.val.val64)
        value = -1;
    else
        value = 0;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = value;

    push_operand_stack(&(frame->operand_stack), operand);
}

void fcmpl(){
    printf("got into fcmpl\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int8_t value;

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    if(op1->val.primitive_val.val.val_float == sqrt(-1) || op2->val.primitive_val.val.val_float == sqrt(-1))
        value = -1;
    else if(op1->val.primitive_val.val.val_float > op2->val.primitive_val.val.val_float)
        value = 1;
    else if(op1->val.primitive_val.val.val_float < op2->val.primitive_val.val.val_float)
        value = -1;
    else
        value = 0;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = value;

    push_operand_stack(&(frame->operand_stack), operand);
}

void fcmpg(){
    printf("got into fcmpg\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    uint8_t value;

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    if(op1->val.primitive_val.val.val_float == sqrt(-1) || op2->val.primitive_val.val.val_float == sqrt(-1))
        value = 1;
    else if(op1->val.primitive_val.val.val_float > op2->val.primitive_val.val.val_float)
        value = 1;
    else if(op1->val.primitive_val.val.val_float < op2->val.primitive_val.val.val_float)
        value = -1;
    else
        value = 0;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = value;

    push_operand_stack(&(frame->operand_stack), operand);
}

void dcmpl(){
    printf("got into dcmpl\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int8_t value;

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    if(op1->val.primitive_val.val.val_double == (double) sqrt(-1) || op2->val.primitive_val.val.val_double == (double) sqrt(-1))
        value = -1;
    else if(op1->val.primitive_val.val.val_double > op2->val.primitive_val.val.val_double)
        value = 1;
    else if(op1->val.primitive_val.val.val_double < op2->val.primitive_val.val.val_double)
        value = -1;
    else
        value = 0;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = value;

    push_operand_stack(&(frame->operand_stack), operand);
}

void dcmpg(){
    printf("got into dcmpl\n");
    any_type_t *op1, *op2, *operand;
    frame_t *frame = peek_frame_stack(jvm_stack);
    int8_t value;

    op2 = pop_operand_stack(&(frame->operand_stack));
    op1 = pop_operand_stack(&(frame->operand_stack));

    if(op1->val.primitive_val.val.val_double == (double) sqrt(-1) || op2->val.primitive_val.val.val_double == (double) sqrt(-1))
        value = 1;
    else if(op1->val.primitive_val.val.val_double > op2->val.primitive_val.val.val_double)
        value = 1;
    else if(op1->val.primitive_val.val.val_double < op2->val.primitive_val.val.val_double)
        value = -1;
    else
        value = 0;

    operand = (any_type_t*) malloc(sizeof(any_type_t));
    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = value;

    push_operand_stack(&(frame->operand_stack), operand);
}


void ifeq(){
    printf("got into ifeq\n");
    any_type_t *value = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value = pop_operand_stack(&(frame->operand_stack));
    if(value->val.primitive_val.val.val32 == 0){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void ifne(){
    printf("got into ifne\n");
    any_type_t *value = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value = pop_operand_stack(&(frame->operand_stack));
    if(value->val.primitive_val.val.val32 != 0){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void iflt(){
    printf("got into iflt\n");
    any_type_t *value = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value = pop_operand_stack(&(frame->operand_stack));
    if(value->val.primitive_val.val.val32 < 0){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void ifge(){
    printf("got into ifge\n");
    any_type_t *value = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value = pop_operand_stack(&(frame->operand_stack));
    printf("value is %d\n", value->val.primitive_val.val.val32);
    if(value->val.primitive_val.val.val32 >= 0){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;
    }
}


void ifgt(){
    printf("got into ifgt\n");
    any_type_t *value = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value = pop_operand_stack(&(frame->operand_stack));
    if(value->val.primitive_val.val.val32 > 0){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void ifle(){
    printf("got into ifle\n");
    any_type_t *value = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value = pop_operand_stack(&(frame->operand_stack));
    if(value->val.primitive_val.val.val32 <= 0){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void if_icmpeq(){
    printf("got into if_icmpeq\n");
    any_type_t *value1, *value2;
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value2 = pop_operand_stack(&(frame->operand_stack));
    value1 = pop_operand_stack(&(frame->operand_stack));

    if(value1->val.primitive_val.val.val32 == value2->val.primitive_val.val.val32){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void if_icmpne(){
    printf("got into if_icmpne\n");
    any_type_t *value1, *value2;
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value2 = pop_operand_stack(&(frame->operand_stack));
    value1 = pop_operand_stack(&(frame->operand_stack));

    if(value1->val.primitive_val.val.val32 != value2->val.primitive_val.val.val32){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void if_icmplt(){
    printf("got into if_icmplt\n");
    any_type_t *value1, *value2;
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value2 = pop_operand_stack(&(frame->operand_stack));
    value1 = pop_operand_stack(&(frame->operand_stack));

    if(value1->val.primitive_val.val.val32 < value2->val.primitive_val.val.val32){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void if_icmpge(){
    printf("got into if_icmpge\n");
    any_type_t *value1, *value2;
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value2 = pop_operand_stack(&(frame->operand_stack));
    value1 = pop_operand_stack(&(frame->operand_stack));

    if(value1->val.primitive_val.val.val32 >= value2->val.primitive_val.val.val32){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void if_icmpgt(){
    printf("got into if_icmpgt\n");
    any_type_t *value1, *value2;
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value2 = pop_operand_stack(&(frame->operand_stack));
    value1 = pop_operand_stack(&(frame->operand_stack));

    if(value1->val.primitive_val.val.val32 > value2->val.primitive_val.val.val32){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void if_icmple(){
    printf("got into if_icmple\n");
    any_type_t *value1, *value2;
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value2 = pop_operand_stack(&(frame->operand_stack));
    value1 = pop_operand_stack(&(frame->operand_stack));

    if(value1->val.primitive_val.val.val32 <= value2->val.primitive_val.val.val32){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];
        index = (indexh<<8)|indexl;

        jvm_pc.code_pc += index;
        jvm_pc.jumped = 1;

    }
}

void if_acmpeq(){
    printf("got into if_acmpeq\n");
    any_type_t *value1, *value2;
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value2 = pop_operand_stack(&(frame->operand_stack));
    value1 = pop_operand_stack(&(frame->operand_stack));

    switch(value1->val.reference_val.tag){
        case OBJECT:
            if(&(value1->val.reference_val.val.object) == &(value2->val.reference_val.val.object)){
                code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
                indexh = code_attribute->code[jvm_pc.code_pc+1];
                indexl = code_attribute->code[jvm_pc.code_pc+2];
                index = (indexh<<8)|indexl;

                jvm_pc.code_pc += index;
                jvm_pc.jumped = 1;
            }
            break;
        case ARRAY:
            if(&(value1->val.reference_val.val.array) == &(value2->val.reference_val.val.array)){
                code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
                indexh = code_attribute->code[jvm_pc.code_pc+1];
                indexl = code_attribute->code[jvm_pc.code_pc+2];
                index = (indexh<<8)|indexl;

                jvm_pc.code_pc += index;
                jvm_pc.jumped = 1;
            }
            break;
        case NULL_REFERENCE:
            if(value2->val.reference_val.tag == NULL_REFERENCE) {
                code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
                indexh = code_attribute->code[jvm_pc.code_pc+1];
                indexl = code_attribute->code[jvm_pc.code_pc+2];
                index = (indexh<<8)|indexl;

                jvm_pc.code_pc += index;
                jvm_pc.jumped = 1;
            }
        break;
    }

}

void if_acmpne(){
    printf("got into if_acmpne\n");
    any_type_t *value1, *value2;
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value2 = pop_operand_stack(&(frame->operand_stack));
    value1 = pop_operand_stack(&(frame->operand_stack));

    switch(value1->val.reference_val.tag){
        case OBJECT:
            if(&(value1->val.reference_val.val.object) != &(value2->val.reference_val.val.object)){
                code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
                indexh = code_attribute->code[jvm_pc.code_pc+1];
                indexl = code_attribute->code[jvm_pc.code_pc+2];
                index = (indexh<<8)|indexl;

                jvm_pc.code_pc += index;
                jvm_pc.jumped = 1;
            }
            break;
        case ARRAY:
            if(&(value1->val.reference_val.val.array) != &(value2->val.reference_val.val.array)){
                code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
                indexh = code_attribute->code[jvm_pc.code_pc+1];
                indexl = code_attribute->code[jvm_pc.code_pc+2];
                index = (indexh<<8)|indexl;

                jvm_pc.code_pc += index;
                jvm_pc.jumped = 1;
            }
            break;
        case NULL_REFERENCE:
            if(value2->val.reference_val.tag != NULL_REFERENCE) {
                code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
                indexh = code_attribute->code[jvm_pc.code_pc+1];
                indexl = code_attribute->code[jvm_pc.code_pc+2];
                index = (indexh<<8)|indexl;

                jvm_pc.code_pc += index;
                jvm_pc.jumped = 1;
            }
        break;
    }
}

void goto_op(){
    printf("got into goto_op\n");
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    indexh = code_attribute->code[jvm_pc.code_pc+1];
    indexl = code_attribute->code[jvm_pc.code_pc+2];
    index = (indexh<<8)|indexl;

    jvm_pc.code_pc = index;
    jvm_pc.jumped = 1;

}

void jsr(){
    printf("got into jsr\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = RETURN_ADDRESS;
    operand->val.primitive_val.val.val_return_addr = jvm_pc.code_pc;
    push_operand_stack(&(frame->operand_stack), operand);

    code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    indexh = code_attribute->code[jvm_pc.code_pc+1];
    indexl = code_attribute->code[jvm_pc.code_pc+2];
    index = (indexh<<8)|indexl;

    jvm_pc.code_pc = index;
    jvm_pc.jumped = 1;
}

void treturn(){
    printf("got into treturn\n");
    returnFromFunction();
}

void getstatic(){
    printf("got into getstatic\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Fieldref.class_index;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[class_index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    if(compare_utf8(class_name, string_to_utf8("java/lang/System")) == 0) {
        return;
    }
    class_t *class_field = getClass(class_name);
    if (class_field->status == CLASSE_NAO_CARREGADA) {
        loadClass(class_field);
    }
    if (class_field->status == CLASSE_NAO_LINKADA) {
        linkClass(class_field);
    }
    if (class_field->status == CLASSE_NAO_INICIALIZADA) {
        initializeClass(class_field);
    }

    u2 name_and_type_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Fieldref.name_and_type_index;
    u2 field_name_index = jvm_pc.currentClass->class_file.constant_pool[name_and_type_index].info.Nameandtype.name_index;
    Utf8_info_t *field_name = &(jvm_pc.currentClass->class_file.constant_pool[field_name_index].info.Utf8);

    u2 i = 0;
    for (i = 0; i < class_field->class_file.fields_count; i++) {
        u2 name_index = class_field->class_file.fields[i].name_index;
        if (compare_utf8(&(class_field->class_file.constant_pool[name_index].info.Utf8), field_name) == 0) {
            frame_t *frame = peek_frame_stack(jvm_stack);
            push_operand_stack(&(frame->operand_stack), class_field->static_fields[i]);
            return;
        }

    }


    assert(0);
    return;
}

void putstatic(){
    printf("got into putstatic\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Fieldref.class_index;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[class_index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *class_field = getClass(class_name);
    if (class_field->status == CLASSE_NAO_CARREGADA) {
        loadClass(class_field);
    }
    if (class_field->status == CLASSE_NAO_LINKADA) {
        linkClass(class_field);
    }
    if (class_field->status == CLASSE_NAO_INICIALIZADA) {
        initializeClass(class_field);
    }

    u2 name_and_type_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Fieldref.name_and_type_index;
    u2 field_name_index = jvm_pc.currentClass->class_file.constant_pool[name_and_type_index].info.Nameandtype.name_index;
    Utf8_info_t *field_name = &(jvm_pc.currentClass->class_file.constant_pool[field_name_index].info.Utf8);

    u2 i = 0;
    for (i = 0; i < class_field->class_file.fields_count; i++) {
        u2 name_index = class_field->class_file.fields[i].name_index;
        if (compare_utf8(&(class_field->class_file.constant_pool[name_index].info.Utf8), field_name) == 0) {
            frame_t *frame = peek_frame_stack(jvm_stack);
            class_field->static_fields[i] = pop_operand_stack(&(frame->operand_stack));
            return;
        }

    }

}

void new_op() {
    printf("got into new_op\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *object_class = getClass(class_name);

    any_type_t* object_ref = (any_type_t*) malloc(sizeof(any_type_t));
    object_ref->tag = REFERENCE;
    object_ref->val.reference_val.tag = OBJECT;
    object_ref->val.reference_val.val.object.objClass = object_class;
    object_ref->val.reference_val.val.object.length = object_class->class_file.fields_count;
    object_ref->val.reference_val.val.object.attributes = (any_type_t*) malloc(sizeof(any_type_t) * object_ref->val.reference_val.val.object.length);

    u2 i;
    for (i = 0; i < object_ref->val.reference_val.val.object.length; ++i) {
        any_type_t *operand = &(object_ref->val.reference_val.val.object.attributes[i]);
        u1* b = object_class->class_file.constant_pool[object_class->class_file.fields[i].descriptor_index].info.Utf8.bytes;
        switch(b[0]) {
            case 'B': //byte
                operand->tag = PRIMITIVE;
                operand->val.primitive_val.tag = BYTE;
                operand->val.primitive_val.val.val8 = 0;
                break;
            case 'C': //char
                operand->tag = PRIMITIVE;
                operand->val.primitive_val.tag = CHAR;
                operand->val.primitive_val.val.val_char = 0;
                break;
            case 'D': //double
                operand->tag = PRIMITIVE;
                operand->val.primitive_val.tag = DOUBLE;
                operand->val.primitive_val.val.val_double = 0;
                break;
            case 'F': //float
                operand->tag = PRIMITIVE;
                operand->val.primitive_val.tag = FLOAT;
                operand->val.primitive_val.val.val_float = 0;
                break;
            case 'I': //integer
                operand->tag = PRIMITIVE;
                operand->val.primitive_val.tag = INT;
                operand->val.primitive_val.val.val32 = 0;
                break;
            case 'J': //long
                operand->tag = PRIMITIVE;
                operand->val.primitive_val.tag = LONG;
                operand->val.primitive_val.val.val64 = 0;
                break;
            case 'S': //short
                operand->tag = PRIMITIVE;
                operand->val.primitive_val.tag = SHORT;
                operand->val.primitive_val.val.val16 = 0;
                break;
            case 'Z': //boolean
                operand->tag = PRIMITIVE;
                operand->val.primitive_val.tag = BOOLEAN;
                operand->val.primitive_val.val.val_boolean = 0;
                break;
            case 'L': //reference
                operand->tag = REFERENCE;
                operand->val.reference_val.tag = OBJECT;
                operand->val.reference_val.val.object.length = 0;
                operand->val.reference_val.val.object.attributes = NULL;
                operand->val.reference_val.val.object.objClass = NULL;
                break;
            case '[': //reference - array
                operand->tag = REFERENCE;
                operand->val.reference_val.tag = ARRAY;
                operand->val.reference_val.val.array.length = 0;
                operand->val.reference_val.val.array.components = NULL;
                break;
            default:
                printf("Unexpected char on method descriptor: %c\n", b[0]);
                exit(1);
        }
    }
    frame_t *frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), object_ref);
}

/*Utf8_info_t* name_init_utf8;*/
/*Utf8_info_t* name_method_utf8;*/
/*name_init_utf8 = string_to_utf8("<init>");*/
/*u2 i;*/
/*for (i = 1; i < object_class->class_file.methods_count; i++) {*/
/*name_method_utf8 = &(object_class->class_file.constant_pool[object_class->class_file.methods[i].name_index].info.Utf8); // Verifica se o metodo eh o <clinit>, se for executa ele.*/
/*if (compare_utf8(name_init_utf8, name_method_utf8) == 0) {*/
/*callMethod(object_class, &(object_class->class_file.methods[i]));*/
/*break;*/
/*}*/
/*}*/

void newarray(){
    printf("got into newarray\n");
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 atype = code_attribute->code[jvm_pc.code_pc+1];
    any_type_t *arrayref = (any_type_t*) malloc(sizeof(any_type_t));
    any_type_t *cont = pop_operand_stack(&(frame->operand_stack));
    int32_t contador, i = 0;

    contador = cont->val.primitive_val.val.val32;
    arrayref->tag = REFERENCE;
    arrayref->val.reference_val.tag = ARRAY;
    arrayref->val.reference_val.val.array.length = contador;
    arrayref->val.reference_val.val.array.components = (any_type_t*) malloc(sizeof(any_type_t) * contador);

    for(i=0; i<=contador; i++){
        arrayref->val.reference_val.val.array.components[i].tag = PRIMITIVE;
        switch(atype){
        case 4:
            arrayref->val.reference_val.val.array.components[i].val.primitive_val.tag = BOOLEAN;
            break;
        case 5:
            arrayref->val.reference_val.val.array.components[i].val.primitive_val.tag = CHAR;
            break;
        case 6:
            arrayref->val.reference_val.val.array.components[i].val.primitive_val.tag = FLOAT;
            break;
        case 7:
            arrayref->val.reference_val.val.array.components[i].val.primitive_val.tag = DOUBLE;
            break;
        case 8:
            arrayref->val.reference_val.val.array.components[i].val.primitive_val.tag = BYTE;
            break;
        case 9:
            arrayref->val.reference_val.val.array.components[i].val.primitive_val.tag = SHORT;
            break;
        case 10:
            arrayref->val.reference_val.val.array.components[i].val.primitive_val.tag = INT;
            break;
        case 11:
            arrayref->val.reference_val.val.array.components[i].val.primitive_val.tag = LONG;
            break;
        }
    }
    push_operand_stack(&(frame->operand_stack), arrayref);

}

void tableswitch() {
    printf("got into tableswitch\n");
    int offset = 0;
    u4 low, high, myDefault, targetOffset;
    u1 byte1 = 0;
    u1 byte2 = 0;
    u1 byte3 = 0;
    u1 byte4 = 0;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);

    offset += 4 - (jvm_pc.code_pc % 4); //allignment bytes

    byte1 = code_attribute->code[jvm_pc.code_pc + offset];
    byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
    byte3 = code_attribute->code[jvm_pc.code_pc + offset + 2];
    byte4 = code_attribute->code[jvm_pc.code_pc + offset + 3];
    myDefault = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    offset += 4; // count default

    byte1 = code_attribute->code[jvm_pc.code_pc + offset];
    byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
    byte3 = code_attribute->code[jvm_pc.code_pc + offset + 2];
    byte4 = code_attribute->code[jvm_pc.code_pc + offset + 3];
    low = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    offset += 4; // count low

    byte1 = code_attribute->code[jvm_pc.code_pc + offset];
    byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
    byte3 = code_attribute->code[jvm_pc.code_pc + offset + 2];
    byte4 = code_attribute->code[jvm_pc.code_pc + offset + 3];
    high = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    offset += 4; // count high

    frame_t *frame = peek_frame_stack(jvm_stack);
    any_type_t *operand = pop_operand_stack(&(frame->operand_stack));
    u4 index = operand->val.primitive_val.val.val32;

    if (index < low && index > high) {
        jvm_pc.code_pc = myDefault + jvm_pc.code_pc;
    } else {
        offset += index - low;

        byte1 = code_attribute->code[jvm_pc.code_pc + offset];
        byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
        byte3 = code_attribute->code[jvm_pc.code_pc + offset + 2];
        byte4 = code_attribute->code[jvm_pc.code_pc + offset + 3];
        targetOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

        jvm_pc.code_pc = targetOffset + jvm_pc.code_pc;
    }

    jvm_pc.jumped = 1;
}

void lookupswitch() {
    printf("got into lookupswitch\n");
    int offset = 0;
    u4 npairs, myDefault, targetOffset, match;
    u1 byte1 = 0;
    u1 byte2 = 0;
    u1 byte3 = 0;
    u1 byte4 = 0;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);

    offset += 4 - (jvm_pc.code_pc % 4); //allignment bytes

    byte1 = code_attribute->code[jvm_pc.code_pc + offset];
    byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
    byte3 = code_attribute->code[jvm_pc.code_pc + offset + 2];
    byte4 = code_attribute->code[jvm_pc.code_pc + offset + 3];
    myDefault = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    offset += 4; // count default

    byte1 = code_attribute->code[jvm_pc.code_pc + offset];
    byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
    byte3 = code_attribute->code[jvm_pc.code_pc + offset + 2];
    byte4 = code_attribute->code[jvm_pc.code_pc + offset + 3];
    npairs = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    offset += 4; // count npairs

    frame_t *frame = peek_frame_stack(jvm_stack);
    any_type_t *operand = pop_operand_stack(&(frame->operand_stack));
    u4 key = operand->val.primitive_val.val.val32;

    u4 i;
    for(i = 0; i < npairs; i++) {
        byte1 = code_attribute->code[jvm_pc.code_pc + offset];
        byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
        byte3 = code_attribute->code[jvm_pc.code_pc + offset + 2];
        byte4 = code_attribute->code[jvm_pc.code_pc + offset + 3];
        match = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

        if (match == key) {
            byte1 = code_attribute->code[jvm_pc.code_pc + offset + 4];
            byte2 = code_attribute->code[jvm_pc.code_pc + offset + 5];
            byte3 = code_attribute->code[jvm_pc.code_pc + offset + 6];
            byte4 = code_attribute->code[jvm_pc.code_pc + offset + 7];
            targetOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

            jvm_pc.code_pc = targetOffset + jvm_pc.code_pc;
            break;
        } else if (match > key) {
            jvm_pc.code_pc = myDefault + jvm_pc.code_pc;
            break;
        }

        offset += 8; // count match and offset pair
    }

    jvm_pc.jumped = 1;
}

void wide() {
    printf("got into wide\n");
    any_type_t* operand;
    int offset = 0;
    u2 index;
    int16_t inc;
    u1 opcode;
    u1 byte1 = 0;
    u1 byte2 = 0;

    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);

    offset += 1; //count wide opcode

    opcode = code_attribute->code[jvm_pc.code_pc + offset];

    offset += 1; //count operation opcode

    switch(opcode) {
        case 0x84: // caso iinc
            byte1 = code_attribute->code[jvm_pc.code_pc + offset];
            byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
            index = (byte1 << 8) | (byte2);

            offset += 2; // count index

            byte1 = code_attribute->code[jvm_pc.code_pc + offset];
            byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
            inc = (byte1 << 8) | (byte2);

            offset += 2; // count count

            operand = frame->local_var.var[index];
            switch (operand->val.primitive_val.tag) {
                case BYTE:
                    operand->val.primitive_val.val.val8 += inc;
                    break;
                case SHORT:
                    operand->val.primitive_val.val.val16 += inc;
                    break;
                case INT:
                    operand->val.primitive_val.val.val32 += inc;
                    break;
                case LONG:
                    operand->val.primitive_val.val.val64 += inc;
                    break;
                default:
                    printf("Unexpected primitive_val tag on iinc()\n");
                    break;
            }

            break;
        case 0x15: // caso iload
        case 0x17: // caso fload
        case 0x16: // caso lload
        case 0x18: // caso dload
        case 0x19: // caso aload
            byte1 = code_attribute->code[jvm_pc.code_pc + offset];
            byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
            index = (byte1 << 8) | (byte2);

            offset += 2; // count index

            operand = frame->local_var.var[index];
            push_operand_stack(&(frame->operand_stack), operand);
            break;
        case 0x36: // caso istore
        case 0x37: // caso lstore
        case 0x38: // caso fstore
        case 0x39: // caso dstore
        case 0x3a: // caso astore
            byte1 = code_attribute->code[jvm_pc.code_pc + offset];
            byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
            index = (byte1 << 8) | (byte2);

            offset += 2; // count index

            operand = pop_operand_stack(&(frame->operand_stack));

            frame->local_var.var[index] = operand;
            if(operand->val.primitive_val.tag == LONG|| operand->val.primitive_val.tag == DOUBLE)
                frame->local_var.var[index+1] = operand;
            break;
        case 0xa9: // caso ret
            byte1 = code_attribute->code[jvm_pc.code_pc + offset];
            byte2 = code_attribute->code[jvm_pc.code_pc + offset + 1];
            index = (byte1 << 8) | (byte2);

            offset += 2; // count index

            operand = frame->local_var.var[index];
            switch (operand->val.primitive_val.tag) {
                case BYTE:
                    jvm_pc.code_pc = operand->val.primitive_val.val.val8;
                    break;
                case SHORT:
                    jvm_pc.code_pc = operand->val.primitive_val.val.val16;
                    break;
                case INT:
                    jvm_pc.code_pc = operand->val.primitive_val.val.val32;
                    break;
                case LONG:
                    jvm_pc.code_pc = operand->val.primitive_val.val.val64;
                    break;
                default:
                    printf("Unexpected primitive_val tag on ret()\n");
                    break;
            }

            jvm_pc.jumped = 1;

            break;
    }
}

void ret() {
    printf("got into ret\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    frame_t* frame = peek_frame_stack(jvm_stack);

    u1 index = code_attribute->code[jvm_pc.code_pc + 1];

    any_type_t* operand = frame->local_var.var[index];
    switch (operand->val.primitive_val.tag) {
        case BYTE:
            jvm_pc.code_pc = operand->val.primitive_val.val.val8;
            break;
        case SHORT:
            jvm_pc.code_pc = operand->val.primitive_val.val.val16;
            break;
        case INT:
            jvm_pc.code_pc = operand->val.primitive_val.val.val32;
            break;
        case LONG:
            jvm_pc.code_pc = operand->val.primitive_val.val.val64;
            break;
        default:
            printf("Unexpected primitive_val tag on ret()\n");
            break;
    }

    jvm_pc.jumped = 1;
}

void iinc() {
    printf("got into iinc\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    frame_t* frame = peek_frame_stack(jvm_stack);

    u1 index = code_attribute->code[jvm_pc.code_pc + 1];
    int8_t inc = code_attribute->code[jvm_pc.code_pc + 2];

    any_type_t* operand = frame->local_var.var[index];
    switch (operand->val.primitive_val.tag) {
        case BYTE:
            operand->val.primitive_val.val.val8 += inc;
            break;
        case SHORT:
            operand->val.primitive_val.val.val16 += inc;
            break;
        case INT:
            operand->val.primitive_val.val.val32 += inc;
            break;
        case LONG:
            operand->val.primitive_val.val.val64 += inc;
            break;
        default:
            printf("Unexpected primitive_val tag on iinc()\n");
            break;
    }
}

void getfield() {
    printf("got into getfield\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Fieldref.class_index;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[class_index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *class_field = getClass(class_name);

    u2 name_and_type_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Fieldref.name_and_type_index;
    u2 field_name_index = jvm_pc.currentClass->class_file.constant_pool[name_and_type_index].info.Nameandtype.name_index;
    Utf8_info_t *field_name = &(jvm_pc.currentClass->class_file.constant_pool[field_name_index].info.Utf8);

    u2 i = 0;
    for (i = 0; i < class_field->class_file.fields_count; i++) {
        u2 name_index = class_field->class_file.fields[i].name_index;
        if (compare_utf8(&(class_field->class_file.constant_pool[name_index].info.Utf8), field_name) == 0) {
            frame_t *frame = peek_frame_stack(jvm_stack);
            any_type_t* objref = pop_operand_stack(&(frame->operand_stack));
            push_operand_stack(&(frame->operand_stack), &(objref->val.reference_val.val.object.attributes[i]));
            return;
        }

    }


    assert(0);
    return;
}
void putfield() {
    printf("got into putfield\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Fieldref.class_index;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[class_index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *class_field = getClass(class_name);

    u2 name_and_type_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Fieldref.name_and_type_index;
    u2 field_name_index = jvm_pc.currentClass->class_file.constant_pool[name_and_type_index].info.Nameandtype.name_index;
    Utf8_info_t *field_name = &(jvm_pc.currentClass->class_file.constant_pool[field_name_index].info.Utf8);


    u2 i = 0;
    for (i = 0; i < class_field->class_file.fields_count; i++) {
        u2 name_index = class_field->class_file.fields[i].name_index;
        if (compare_utf8(&(class_field->class_file.constant_pool[name_index].info.Utf8), field_name) == 0) {
            frame_t *frame = peek_frame_stack(jvm_stack);
            any_type_t* objref = pop_operand_stack(&(frame->operand_stack));
            any_type_t* value = pop_operand_stack(&(frame->operand_stack));
            memmove(&(objref->val.reference_val.val.object.attributes[i]), value, sizeof(any_type_t));
            return;
        }

    }

    assert(0);
    return;
}
void invokevirtual() {
    printf("got into invokevirtual\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Methodref.class_index;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[class_index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *class_method = getClass(class_name);

    u2 name_and_type_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Methodref.name_and_type_index;
    u2 method_name_index = jvm_pc.currentClass->class_file.constant_pool[name_and_type_index].info.Nameandtype.name_index;
    Utf8_info_t *method_name = &(jvm_pc.currentClass->class_file.constant_pool[method_name_index].info.Utf8);

    u2 descriptor_index = jvm_pc.currentClass->class_file.constant_pool[name_and_type_index].info.Nameandtype.descriptor_index;
    Utf8_info_t *descriptor = &(jvm_pc.currentClass->class_file.constant_pool[descriptor_index].info.Utf8);

    if(compare_utf8(string_to_utf8("java/io/PrintStream"), class_name) == 0 &&
            compare_utf8(string_to_utf8("println"), method_name) == 0) {

        frame_t *frame = peek_frame_stack(jvm_stack);
        any_type_t *arg = pop_operand_stack(&(frame->operand_stack));

        if (compare_utf8(descriptor, string_to_utf8("(I)V")) == 0) {
            printf("%d\n", arg->val.primitive_val.val.val32);
        } else if (compare_utf8(descriptor, string_to_utf8("(J)V")) == 0) {
            printf("%ld\n", arg->val.primitive_val.val.val64);
        } else if (compare_utf8(descriptor, string_to_utf8("(S)V")) == 0) {
            printf("%d\n", arg->val.primitive_val.val.val16);
        } else if (compare_utf8(descriptor, string_to_utf8("(D)V")) == 0) {
            printf("%f\n", arg->val.primitive_val.val.val_double);
        } else if (compare_utf8(descriptor, string_to_utf8("(F)V")) == 0) {
            printf("%f\n", arg->val.primitive_val.val.val_float);
        } else if (compare_utf8(descriptor, string_to_utf8("(Ljava/lang/String;)V")) == 0) {
            u2 k = 0;
            for(k = 0; k < arg->val.reference_val.val.array.length; k++) {
                printf("%c", arg->val.reference_val.val.array.components[k].val.primitive_val.val.val_char);
            }
            printf("\n");
        }
        return;
    }

    u2 i = 0;
    for (i = 0; i < class_method->class_file.methods_count; i++) {
        u2 name_index = class_method->class_file.methods[i].name_index;
        if (compare_utf8(&(class_method->class_file.constant_pool[name_index].info.Utf8), method_name) == 0) {
            callMethod(class_method, &(class_method->class_file.methods[i]));
            return;
        }

    }

    assert(0);
    return;
}
void invokespecial() {
    printf("got into invokespecial\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Methodref.class_index;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[class_index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *class_method = getClass(class_name);
    if (class_method == NULL) {
        return;
    }

    u2 name_and_type_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Methodref.name_and_type_index;
    u2 method_name_index = jvm_pc.currentClass->class_file.constant_pool[name_and_type_index].info.Nameandtype.name_index;
    Utf8_info_t *method_name = &(jvm_pc.currentClass->class_file.constant_pool[method_name_index].info.Utf8);

    u2 i = 0;
    for (i = 0; i < class_method->class_file.methods_count; i++) {
        u2 name_index = class_method->class_file.methods[i].name_index;
        if (compare_utf8(&(class_method->class_file.constant_pool[name_index].info.Utf8), method_name) == 0) {
            callMethod(class_method, &(class_method->class_file.methods[i]));
            return;
        }

    }

    assert(0);
    return;
}
void invokestatic() {
    printf("got into invokestatic\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Methodref.class_index;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[class_index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *class_method = getClass(class_name);

    u2 name_and_type_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Methodref.name_and_type_index;
    u2 method_name_index = jvm_pc.currentClass->class_file.constant_pool[name_and_type_index].info.Nameandtype.name_index;
    Utf8_info_t *method_name = &(jvm_pc.currentClass->class_file.constant_pool[method_name_index].info.Utf8);

    u2 i = 0;
    for (i = 0; i < class_method->class_file.methods_count; i++) {
        u2 name_index = class_method->class_file.methods[i].name_index;
        if (compare_utf8(&(class_method->class_file.constant_pool[name_index].info.Utf8), method_name) == 0) {
            callMethod(class_method, &(class_method->class_file.methods[i]));
            return;
        }

    }

    assert(0);
    return;
}
void invokeinterface() {
    printf("got into invokeinterface\n");
    // TODO verificar se esta certa (esta igual as anteriores)
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Methodref.class_index;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[class_index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *class_method = getClass(class_name);

    u2 name_and_type_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Methodref.name_and_type_index;
    u2 method_name_index = jvm_pc.currentClass->class_file.constant_pool[name_and_type_index].info.Nameandtype.name_index;
    Utf8_info_t *method_name = &(jvm_pc.currentClass->class_file.constant_pool[method_name_index].info.Utf8);

    u2 i = 0;
    for (i = 0; i < class_method->class_file.methods_count; i++) {
        u2 name_index = class_method->class_file.methods[i].name_index;
        if (compare_utf8(&(class_method->class_file.constant_pool[name_index].info.Utf8), method_name) == 0) {
            callMethod(class_method, &(class_method->class_file.methods[i]));
            return;
        }

    }

    assert(0);
    return;
}
void invokedynamic() {
    printf("got into invokedynamic\n");
    //TODO
}
void anewarray() {
    printf("got into anewarray\n");
    frame_t *frame = peek_frame_stack(jvm_stack);
    any_type_t *arrayref = (any_type_t*) malloc(sizeof(any_type_t));
    any_type_t *cont = pop_operand_stack(&(frame->operand_stack));
    int32_t contador, i = 0;

    contador = cont->val.primitive_val.val.val32;
    arrayref->tag = REFERENCE;
    arrayref->val.reference_val.tag = ARRAY;
    arrayref->val.reference_val.val.array.length = contador;
    arrayref->val.reference_val.val.array.components = (any_type_t*) malloc(sizeof(any_type_t) * contador);

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *object_class = getClass(class_name);

    for(i=0; i<=contador; i++){
        arrayref->val.reference_val.val.array.components[i].tag = REFERENCE;
        arrayref->val.reference_val.val.array.components[i].val.reference_val.tag = OBJECT;
        arrayref->val.reference_val.val.array.components[i].val.reference_val.val.object.objClass = object_class;
        arrayref->val.reference_val.val.array.components[i].val.reference_val.val.object.length = object_class->class_file.fields_count;
        arrayref->val.reference_val.val.array.components[i].val.reference_val.val.object.attributes = (any_type_t*) malloc(sizeof(any_type_t) * object_class->class_file.fields_count);
    }
    push_operand_stack(&(frame->operand_stack), arrayref);
}
void arraylength() {
    printf("got into arraylength\n");
    frame_t *frame = peek_frame_stack(jvm_stack);
    any_type_t *arrayref = pop_operand_stack(&(frame->operand_stack));

    any_type_t *length = (any_type_t*) malloc(sizeof(any_type_t));
    length->tag = PRIMITIVE;
    length->val.primitive_val.tag = INT;
    length->val.primitive_val.val.val32 = arrayref->val.reference_val.val.array.length;

    push_operand_stack(&(frame->operand_stack), length);
}
void athrow() {
    printf("got into athrow\n");
    frame_t *frame = peek_frame_stack(jvm_stack);
    any_type_t *objref = pop_operand_stack(&(frame->operand_stack));
    throwException(objref->val.reference_val.val.object.objClass);
}
void checkcast() {
    printf("got into checkcast\n");
    // TODO acho que esta errado, parece que tem que botar eh um objref de volta na pilha e nao um boolean
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Methodref.class_index;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[class_index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *class_obj = getClass(class_name);
    frame_t *frame = peek_frame_stack(jvm_stack);
    any_type_t *objref = pop_operand_stack(&(frame->operand_stack));

    any_type_t *boolean = (any_type_t*) malloc(sizeof(any_type_t));
    boolean->tag = PRIMITIVE;
    boolean->val.primitive_val.tag = BOOLEAN;

    if ( class_obj == objref->val.reference_val.val.object.objClass) {
        boolean->val.primitive_val.val.val_boolean = 1;
    } else {
        boolean->val.primitive_val.val.val_boolean = 0;
    }
    push_operand_stack(&(frame->operand_stack), boolean);
}

void instanceof() {
    printf("got into instanceof\n");
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 index = (b1<<8)|b2;

    u2 class_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Methodref.class_index;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[class_index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);

    class_t *class_obj = getClass(class_name);
    frame_t *frame = peek_frame_stack(jvm_stack);
    any_type_t *objref = pop_operand_stack(&(frame->operand_stack));

    any_type_t *boolean = (any_type_t*) malloc(sizeof(any_type_t));
    boolean->tag = PRIMITIVE;
    boolean->val.primitive_val.tag = BOOLEAN;

    if ( class_obj == objref->val.reference_val.val.object.objClass) {
        boolean->val.primitive_val.val.val_boolean = 1;
    } else {
        boolean->val.primitive_val.val.val_boolean = 0;
    }
    push_operand_stack(&(frame->operand_stack), boolean);
}

void monitorenter() {
    printf("got into monitorenter\n");
    printf("ERROR: monitorenter is not implemented!\n");
    exit(1);
}
void monitorexit() {
    printf("got into monitorexit\n");
    printf("ERROR: monitorexit is not implemented!\n");
    exit(1);
}
void multianewarray() {
    printf("got into multianewarray\n");
    frame_t *frame = peek_frame_stack(jvm_stack);
    any_type_t *arrayref = (any_type_t*) malloc(sizeof(any_type_t));
    int32_t contador;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u1 dimension = code_attribute->code[jvm_pc.code_pc+3];
    u2 index = (b1<<8)|b2;
    u2 class_name_index = jvm_pc.currentClass->class_file.constant_pool[index].info.Class.name_index;
    Utf8_info_t *class_name = &(jvm_pc.currentClass->class_file.constant_pool[class_name_index].info.Utf8);
    class_t *object_class = getClass(class_name);

    any_type_t *cont = pop_operand_stack(&(frame->operand_stack));
    contador = cont->val.primitive_val.val.val32;

    createMultiArray(arrayref, contador, dimension, object_class);

    push_operand_stack(&(frame->operand_stack), arrayref);
}
void ifnull() {
    printf("got into ifnull\n");
    any_type_t *value = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value = pop_operand_stack(&(frame->operand_stack));
    if(value->val.reference_val.tag == NULL_REFERENCE){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc = index;
        jvm_pc.jumped = 1;

    }
}
void ifnonnull() {
    printf("got into ifnonnull\n");
    any_type_t *value = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);
    code_attribute_t *code_attribute;
    u1 indexh, indexl;
    u2 index;

    value = pop_operand_stack(&(frame->operand_stack));
    if(value->val.reference_val.tag != NULL_REFERENCE){
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        indexh = code_attribute->code[jvm_pc.code_pc+1];
        indexl = code_attribute->code[jvm_pc.code_pc+2];

        index = (indexh<<8)|indexl;

        jvm_pc.code_pc = index;
        jvm_pc.jumped = 1;
    }
}
void goto_w() {
    printf("got into goto_w\n");
    u1 byte1 = 0;
    u1 byte2 = 0;
    u1 byte3 = 0;
    u1 byte4 = 0;
    u2 index;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);

    byte1 = code_attribute->code[jvm_pc.code_pc + 1];
    byte2 = code_attribute->code[jvm_pc.code_pc + 2];
    byte3 = code_attribute->code[jvm_pc.code_pc + 3];
    byte4 = code_attribute->code[jvm_pc.code_pc + 4];

    index = ((byte1 << 24)|(byte2 << 16)|(byte3 << 8)|(byte4));

    jvm_pc.code_pc = index;
    jvm_pc.jumped = 1;
}
void jsr_w() {
    printf("got into jsr_w\n");
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));
    frame_t *frame = peek_frame_stack(jvm_stack);
    u1 byte1 = 0;
    u1 byte2 = 0;
    u1 byte3 = 0;
    u1 byte4 = 0;
    u2 index;

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = RETURN_ADDRESS;
    operand->val.primitive_val.val.val_return_addr = jvm_pc.code_pc;
    push_operand_stack(&(frame->operand_stack), operand);

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);

    byte1 = code_attribute->code[jvm_pc.code_pc + 1];
    byte2 = code_attribute->code[jvm_pc.code_pc + 2];
    byte3 = code_attribute->code[jvm_pc.code_pc + 3];
    byte4 = code_attribute->code[jvm_pc.code_pc + 4];

    index = ((byte1 << 24)|(byte2 << 16)|(byte3 << 8)|(byte4));

    jvm_pc.code_pc = index;
    jvm_pc.jumped = 1;
}
void breakpoint() {
    printf("got into breakpoint\n");
    printf("ERROR: breakpoint is not implemented!\n");
    exit(1);
}
void impdep1() {
    printf("got into impdep1\n");
    printf("ERROR: impdep1 is not implemented!\n");
    exit(1);
}
void impdep2() {
    printf("got into impdep2\n");
    printf("ERROR: impdep2 is not implemented!\n");
    exit(1);
}

void (*jvm_opcode[])(void) = {
    NULL,aconst_null,iconst_m1,iconst_0,iconst_1,iconst_2,iconst_3,iconst_4,iconst_5,lconst_0,lconst_1,fconst_0,fconst_1,fconst_2,dconst_0,
    dconst_1,bipush,sipush,ldc,ldc_w,ldc2_w,tload,tload,tload,tload,tload,tload_0,tload_1,tload_2,tload_3,tload_0,tload_1,tload_2,tload_3,
    tload_0,tload_1,tload_2,tload_3,tload_0,tload_1,tload_2,tload_3,tload_0,tload_1,tload_2,tload_3,taload,taload,taload,taload,taload,taload,
    taload,taload,tstore,tstore,tstore,tstore,tstore,tstore_0,tstore_1,tstore_2, tstore_3,tstore_0,tstore_1,tstore_2,tstore_3,tstore_0,tstore_1,
    tstore_2,tstore_3,tstore_0,tstore_1,tstore_2,tstore_3,tstore_0,tstore_1,tstore_2,tstore_3,tastore,tastore,tastore,tastore,tastore,tastore,
    tastore,tastore,pop,pop2,dup,dup_x1,dup_x2,dup2,dup2_x1,dup2_x2,swap,iadd,ladd,fadd,dadd,isub,lsub,fsub,dsub,imul,lmul,fmul,dmul,idiv,ldiv_op,
    fdiv,ddiv,irem,lrem,frem,drem_op,ineg,lneg,fneg,dneg,ishl,lshl,ishr,lshr,iushr,lushr,iand,land,ior,lor,ixor,lxor,iinc,i2l,i2f,i2d,l2i,l2f,l2d,
    f2i,f2l,f2d,d2i,d2l,d2f,i2b,i2c,i2s,lcmp,fcmpl,fcmpg,dcmpl,dcmpg,ifeq,ifne,iflt,ifge,ifgt,ifle,if_icmpeq,if_icmpne,if_icmplt,if_icmpge,if_icmpgt,
    if_icmple,if_acmpeq,if_acmpne,goto_op,jsr,ret,tableswitch,lookupswitch,treturn,treturn,treturn,treturn,treturn,treturn,getstatic,putstatic,
    getfield,putfield,invokevirtual,invokespecial,invokestatic,invokeinterface,invokedynamic,new_op,newarray,anewarray,arraylength,athrow,checkcast,
    instanceof,monitorenter,monitorexit,wide,multianewarray,ifnull,ifnonnull,goto_w	,jsr_w,breakpoint
};

