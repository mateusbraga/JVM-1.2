#include "opcode.h"
#include "frame_stack.h"

extern frame_t *frame;

/*
 * Adiciona uma refêrencia NULL na pilha de operandos
 */

void aconst_null(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = REFERENCE;
    operand.reference_val.tag = OBJECT;
    operand.reference_val.object = NULL;

    push_operand_stack(&(frame->operand_stack), operand);
}

/*
*   Adiciona o valor int -1 na pilha de operandos
*/
void iconst_m1(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.primitive_val.tag = INT;
    operand.primitive_val.val32 = -1;

    push_operand_stack(&(frame->operand_stack), operand);
}

/*
*   Adiciona o valor int 0 na pilha de operandos
*/
void iconst_0(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.primitive_val.tag = INT;
    operand.primitive_val.val32 = 0;

    push_operand_stack(&(frame->operand_stack), operand);
}

/*
*   Adiciona o valor int 1 na pilha de operandos
*/
void iconst_1(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.primitive_val.tag = INT;
    operand.primitive_val.val32 = 1;

    push_operand_stack(&(frame->operand_stack), operand);
}

/*
*   Adiciona o valor int 2 na pilha de operandos
*/
void iconst_2(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.primitive_val.tag = INT;
    operand.primitive_val.val32 = 2;

    push_operand_stack(&(frame->operand_stack), operand);
}

/*
*   Adiciona o valor int 3 na pilha de operandos
*/
void iconst_3(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.primitive_val.tag = INT;
    operand.primitive_val.val32 = 3;

    push_operand_stack(&(frame->operand_stack), operand);
}

/*
*   Adiciona o valor int 4 na pilha de operandos
*/
void iconst_4(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.primitive_val.tag = INT;
    operand.primitive_val.val32 = 4;

    push_operand_stack(&(frame->operand_stack), operand);
}

/*
*   Adiciona o valor int 5 na pilha de operandos
*/
void iconst_5(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.primitive_val.tag = INT;
    operand.primitive_val.val32 = 5;

    push_operand_stack(&(frame->operand_stack), operand);
}

/*
*   Adiciona o valor long 0 na pilha de operandos
*/
void lconst_0(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.primitive_val.tag = LONG;
    operand.primitive_val.val32 = 0;

    push_operand_stack(&(frame->operand_stack), operand);
}

/*
*   Adiciona o valor long 1 na pilha de operandos
*/
void lconst_1(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand.tag = PRIMITIVE;
    operand.primitive_val.tag = LONG;
    operand.primitive_val.val32 = 1;

    push_operand_stack(&(frame->operand_stack), operand);
}
