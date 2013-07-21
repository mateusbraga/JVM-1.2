#ifndef _STACK_DEF
#define _STACK_DEF 

#include <stdint.h>

#include "structs.h"

/** \addtogroup Estruturas da frame
 * @{
 */

// --------------- Operand stack Stuff -----------------
/**
 * @struct operand_stack_struct
 * 
 */
typedef struct operand_stack_struct {
    any_type_t **operand;
    int head;
    int size;
    uint32_t depth;
} operand_stack_t;

any_type_t *pop_operand_stack(operand_stack_t *stack);
void push_operand_stack(operand_stack_t *stack, any_type_t *operand);

// --------------- Local variables Stuff -----------------
/**
 * @struct local_variables_struct
 * 
 */
typedef struct local_variables_struct {
    any_type_t* var; // Array de any_type_t
    unsigned int size;
} local_variables_t;

// --------------- Frame Stuff -----------------
/**
 * @struct frame_struct
 * 
 */
typedef struct frame_struct {
    local_variables_t local_var;
    operand_stack_t operand_stack;
    method_info_t *current_method;
    class_t *current_class;
    pc_t return_address;
} frame_t;

// --------------- Frame stack Stuff -----------------
/**
 * @struct frame_stack_struct
 * 
 */
typedef struct frame_stack_struct {
    frame_t *frame;
    struct frame_stack_struct *next;
    struct frame_stack_struct *previous;
} frame_stack_t;

frame_t* pop_frame_stack(frame_stack_t **stack);
void push_frame_stack(frame_stack_t **stack, frame_t *frame);
frame_t* peek_frame_stack(frame_stack_t *stack);

#endif
