#include "opcode.h"
#include "frame_stack.h"

extern frame_stack_t *jvm_stack;

frame_t frame = peek_frame_stack(jvm_stack);

/**
* name: aconst_null
* desc: push a null reference onto the stack
* params: void
* return: void
**/

void aconst_null(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = REFERENCE;
    operand.val.reference_val.tag = OBJECT;
    operand.val.reference_val.val.object = NULL;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: iconst_m1
* desc: load the int value -1 onto the stack
* params: void
* return: void
**/
void iconst_m1(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = INT;
    operand.val.primitive_val.val.val32 = -1;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: iconst_0
* desc: load the int value 0 onto the stack
* params: void
* return: void
**/
void iconst_0(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = INT;
    operand.val.primitive_val.val.val32 = 0;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: iconst_1
* desc: load the int value 1 onto the stack
* params: void
* return: void
**/
void iconst_1(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = INT;
    operand.val.primitive_val.val.val32 = 1;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: iconst_2
* desc: load the int value 2 onto the stack
* params: void
* return: void
**/
void iconst_2(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = INT;
    operand.val.primitive_val.val.val32 = 2;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: iconst_3
* desc: load the int value 3 onto the stack
* params: void
* return: void
**/
void iconst_3(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = INT;
    operand.val.primitive_val.val.val32 = 3;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: iconst_4
* desc: load the int value 4 onto the stack
* params: void
* return: void
**/
void iconst_4(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = INT;
    operand.val.primitive_val.val.val32 = 4;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: iconst_5
* desc: load the int value 5 onto the stack
* params: void
* return: void
**/
void iconst_5(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = INT;
    operand.val.primitive_val.val.val32 = 5;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: lconst_0
* desc: load the long value 0 onto the stack
* params: void
* return: void
**/
void lconst_0(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = LONG;
    operand.val.primitive_val.val.val64 = 0;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: lconst_1
* desc: load the long value 1 onto the stack
* params: void
* return: void
**/
void lconst_1(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = LONG;
    operand.val.primitive_val.val.val64 = 1;

    push_operand_stack(&(frame->operand_stack), operand);
}


/**
* name: fconst_0
* desc: load the float value 0 onto the stack
* params: void
* return: void
**/
void fconst_0(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = FLOAT;
    operand.val.primitive_val.val.val_float = 0;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: fconst_1
* desc: load the float value 1 onto the stack
* params: void
* return: void
**/
void fconst_1(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = FLOAT;
    operand.val.primitive_val.val.val_float = 1;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: fconst_2
* desc: load the float value 2 onto the stack
* params: void
* return: void
**/
void fconst_2(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = FLOAT;
    operand.val.primitive_val.val.val_float = 2;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: dconst_0
* desc: load the double value 0 onto the stack
* params: void
* return: void
**/
void dconst_0(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = DOUBLE;
    operand.val.primitive_val.val.val_double = 0;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: dconst_1
* desc: load the double value 1 onto the stack
* params: void
* return: void
**/
void dconst_1(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = DOUBLE;
    operand.val.primitive_val.val.val_double = 1;

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: bipush
* desc: push a byte onto the stack as an integer value
* params: byte b
* return: void
**/
void bipush(/*como passar o byte???*/){
    // receber parametro b
    // int value = (int32_t) b;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = INT;
    operand.val.primitive_val.val.val32 = value;

    push_operand_stack(&(frame->operand_stack), operand);

}

/**
* name: sipush
* desc: push a short onto the stack
* params: byte b1, b2
* return: void
**/
void sipush(/*como passar o byte???*/){
    // receber parametros b1 e b2
    // int16_t aux = (b1 << 8) | b2;
    // int32_t value = (int32_t) aux;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.val.primitive_val.tag = INT;
    operand.val.primitive_val.val.val32 = value;

    push_operand_stack(&(frame->operand_stack), operand);
}

