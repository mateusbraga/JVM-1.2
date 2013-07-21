#include <stdlib.h>
#include <stdio.h>

#include "frame_stack.h"

/** \addtogroup Operacoes com as frames
 * @{
 */
// --------------- Frame stack Stuff -----------------

/**
 * @brief Pega um frame da pilha retirando ele do topo.
 *
 * @param stack para buscar o frame
 * @return o frame da pilha
 */

frame_t* pop_frame_stack(frame_stack_t **stack) {
    frame_stack_t *oldStackHead = (*stack);
    frame_t *frame = (*stack)->frame;

    if ((*stack) != NULL) {
        *stack = (*stack)->previous;
        (*stack)->next = NULL;

        free(oldStackHead);

        return frame;
    } else {
        return NULL;
    }
}
/**
 * @brief Coloca um frame na pilha
 *
 * @param pilha
 * @param frame
 * 
 */
void push_frame_stack(frame_stack_t **stack, frame_t *frame) {
    frame_stack_t *newStackHead = (frame_stack_t*) malloc(sizeof(frame_stack_t));

    newStackHead->frame = frame;
    newStackHead->next = NULL;
    newStackHead->previous = (*stack);


    if ((*stack) != NULL) {
        (*stack)->next = newStackHead;
        (*stack) = newStackHead;
    } else {
        (*stack) = newStackHead;
    }

    return;
}
/**
 * @brief pega um frame da pilha mas nao retira da pilha
 *
 * @param pilha
 * 
 */
frame_t* peek_frame_stack(frame_stack_t *stack) {
    if (stack != NULL) {
        return stack->frame;
    } else {
        return NULL;
    }
}

// --------------- Operand stack Stuff -----------------
/**
 * @brief Pega um operando da pilha retirando ele do topo.
 *
 * @param stack para buscar o frame
 * @return o operando da pilha
 */
any_type_t *pop_operand_stack(operand_stack_t *stack) {
    if (stack->head == -1) {
        printf("ERRO: Pop operand stack sem elementos\n");
        exit(1);
    }

    any_type_t *operand = stack->operand[stack->head];
    (stack->head)--;

    return operand;
}
/**
 * @brief Coloca um operando na pilha
 *
 * @param pilha
 * @param oprerando
 * 
 */
void push_operand_stack(operand_stack_t *stack, any_type_t *operand) {
    if (stack->head == stack->size - 1) {
        printf("ERRO: Push operand stack overflow\n");
        exit(1);
    }

    (stack->head)++;
    stack->operand[stack->head] = operand;
}

