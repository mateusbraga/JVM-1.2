#include <stdlib.h>
#include <stdio.h>

#include "frame_stack.h"
#include "jvm.h"

extern frame_stack_t *jvm_stack;

// --------------- Frame stack Stuff -----------------

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

frame_t* peek_frame_stack(frame_stack_t *stack) {
    if (stack != NULL) {
        return stack->frame;
    } else {
        return NULL;
    }
}

// --------------- Operand stack Stuff -----------------

any_type_t *pop_operand_stack(operand_stack_t *stack) {
    if (stack->head == -1) {
        printf("ERRO: Pop operand stack sem elementos\n");
        exit(1);
    }

    any_type_t *operand = stack->operand[stack->head];
    (stack->head)--;

    DEBUG_PRINT("poped at %d: ", stack->head + 1);
    print_any_type(operand);
    return operand;
}
void push_operand_stack(operand_stack_t *stack, any_type_t *operand) {
    if (stack->head == stack->size - 1) {
        printf("ERRO: Push operand stack overflow - max_stack = %d\n", stack->size);
        u1 i = 0;
        for(i = 0; i < stack->size; i++) {
            print_any_type(pop_operand_stack(stack));
        }
        exit(1);
    }

    (stack->head)++;
    stack->operand[stack->head] = operand;

    DEBUG_PRINT("pushed at %d: ", stack->head);
    print_any_type(operand);
}

