#ifndef _STACK_DEF
#define _STACK_DEF 

#include <stdint.h>

#include "structs.h"

// --------------- Operand stack Stuff -----------------

typedef struct operand_stack_struct {
    uint32_t *operand;
    unsigned int head;
    unsigned int size;
} operand_stack_t;

uint32_t pop_operand_stack(operand_stack_t *stack);
void push_operand_stack(operand_stack_t *stack, uint32_t operand);

// --------------- Local variables Stuff -----------------

typedef struct local_variables_struct {
    uint32_t *var;
    unsigned int size;
} local_variables_t;

// --------------- Frame Stuff -----------------

typedef struct frame_struct {
    local_variables_t local_var;
    operand_stack_t operand_stack;
    void *constant_pool;
    char *current_method;
    class_t *current_class;
    void *return_address;
} frame_t;

// --------------- Frame stack Stuff -----------------

typedef struct frame_stack_struct {
    frame_t *frame;
    struct frame_stack_struct *next;
    struct frame_stack_struct *previous;
} frame_stack_t;

frame_t* pop_frame_stack(frame_stack_t **stack);
void push_frame_stack(frame_stack_t **stack, frame_t *frame);

#endif
