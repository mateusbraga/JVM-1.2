#ifndef _STACK_DEF
#define _STACK_DEF 

#include <stdint.h>

#include "structs.h"

// --------------- JVM types -----------------

typedef enum any_type_tag_enum {PRIMITIVE, REFERENCE} any_type_tag_t;
typedef enum reference_type_tag_enum {ARRAY, OBJECT} reference_type_tag_t;
typedef enum primitive_type_tag_enum {BYTE, SHORT, INT, LONG, CHAR} primitive_type_tag_t;

typedef struct any_type_struct any_type_t;

typedef struct array_struct {
    uint32_t length;
    any_type_t *components;
} array_t;

typedef struct object_struct {
    uint32_t length;
    any_type_t *atributes;
} object_t;

typedef struct primitive_type_struct {
    primitive_type_tag_t tag;
    union {
        int8_t val8;
        int16_t val16;
        int32_t val32;
        int64_t val64;
        uint16_t val_char;
    };
} primitive_type_t;

typedef struct reference_type_struct {
    reference_type_tag_t tag;
    union {
        array_t array;
        object_t object;
    };
} reference_type_t;

struct any_type_struct {
    any_type_tag_t tag;
    union {
        primitive_type_t primitive_val;
        reference_type_t reference_val;
    };
};

// --------------- Operand stack Stuff -----------------

typedef struct operand_stack_struct {
    any_type_t **operand;
    unsigned int head;
    unsigned int size;
    uint32_t depth;
} operand_stack_t;

any_type_t *pop_operand_stack(operand_stack_t *stack);
void push_operand_stack(operand_stack_t *stack, any_type_t *operand);

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
frame_t* peek_frame_stack(frame_stack_t *stack);

#endif
