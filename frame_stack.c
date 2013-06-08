#include <stdlib.h>

#include "frame_stack.h"

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
