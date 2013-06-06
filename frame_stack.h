#ifndef _STACK_DEF
#define _STACK_DEF 

#include <stdint.h>

typedef struct frame_struct {
    uint32_t *local_var;
    int operand_stack;
    void *constant_pool;
    char *current_method;
    char *current_class;
    void *return_address;
} frame_t;

typedef struct frame_stack_struct {
    frame_t *frame;
    struct frame_stack_struct *next;
    struct frame_stack_struct *previous;
} frame_stack_t;

frame_t* pop_stack(frame_stack_t **stack);
void push_stack(frame_stack_t **stack, frame_t *frame);

#endif
