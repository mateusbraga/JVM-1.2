#include "opcode.h"
#include "frame_stack.h"
#include "structs.h"
#include "jvm.h"

extern frame_stack_t *jvm_stack;

extern pc_t jvm_pc;

/**
 * Empilha uma referÍncia nula na pilha de operandos
 *
 */
void aconst_null(){
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
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
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
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
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
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 b = code_attribute->code[jvm_pc.code_pc+1];
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));
    u4 bytes;
    u2 bytes1;

    switch(jvm_pc.class->class_file.constant_pool[b].tag){
        case CONSTANT_Integer:
            bytes = jvm_pc.class->class_file.constant_pool[b].info.Integer.bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = INT;
            operand->val.primitive_val.val.val32 = bytes;
            break;
        case CONSTANT_Float:
            bytes = jvm_pc.class->class_file.constant_pool[b].info.Float.bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = FLOAT;
            operand->val.primitive_val.val.val_float = bytes;
            break;
        case CONSTANT_String:
            bytes1 = jvm_pc.class->class_file.constant_pool[b].info.String.string_index;
            Utf8_info_t *Utf8_cod = &(jvm_pc.class->class_file.constant_pool[bytes1].info.Utf8);
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
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 b = (b1<<8)|b2;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    u4 bytes;
    u2 bytes1;
    switch(jvm_pc.class->class_file.constant_pool[b].tag){
        case CONSTANT_Integer:
            bytes = jvm_pc.class->class_file.constant_pool[b].info.Integer.bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = INT;
            operand->val.primitive_val.val.val32 = bytes;
            break;
        case CONSTANT_Float:
            bytes = jvm_pc.class->class_file.constant_pool[b].info.Float.bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = FLOAT;
            operand->val.primitive_val.val.val_float = bytes;
            break;
        case CONSTANT_String:
            bytes1 = jvm_pc.class->class_file.constant_pool[b].info.String.string_index;
            Utf8_info_t *Utf8_cod = &(jvm_pc.class->class_file.constant_pool[bytes1].info.Utf8);
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
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 b1 = code_attribute->code[jvm_pc.code_pc+1];
    u1 b2 = code_attribute->code[jvm_pc.code_pc+2];
    u2 b = (b1<<8)|b2;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));
    u4 high_bytes;
    u4 low_bytes;

    switch(jvm_pc.class->class_file.constant_pool[b].tag){
        case CONSTANT_Long:
            high_bytes = jvm_pc.class->class_file.constant_pool[b].info.Long.high_bytes;
            low_bytes = jvm_pc.class->class_file.constant_pool[b].info.Long.low_bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = LONG;
            operand->val.primitive_val.val.val32 = (high_bytes<<8)|low_bytes;
            break;
        case CONSTANT_Double:
            high_bytes = jvm_pc.class->class_file.constant_pool[b].info.Long.high_bytes;
            low_bytes = jvm_pc.class->class_file.constant_pool[b].info.Long.low_bytes;
            operand->tag = PRIMITIVE;
            operand->val.primitive_val.tag = DOUBLE;
            operand->val.primitive_val.val.val32 = (high_bytes<<8)|low_bytes;
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
    any_type_t* operand;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
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
    any_type_t* operand;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];
    operand = (any_type_t*) malloc(sizeof(any_type_t));

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand = frame->local_var.var[0];

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha na pilha de operandos any_type_t value de uma local_var[1]. Valida para todos os tload_1()
 *
 */
void tload_1(){
    any_type_t* operand;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];
    operand = (any_type_t*) malloc(sizeof(any_type_t));

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand = frame->local_var.var[1];

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha na pilha de operandos any_type_t value de uma local_var[2]. Valida para todos os tload_2()
 *
 */
void tload_2(){
    any_type_t* operand;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];
    operand = (any_type_t*) malloc(sizeof(any_type_t));

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand = frame->local_var.var[2];

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Empilha na pilha de operandos any_type_t value de uma local_var[3]. Valida para todos os tload_3()
 *
 */
void tload_3(){
    any_type_t* operand;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];
    operand = (any_type_t*) malloc(sizeof(any_type_t));

    frame_t *frame = peek_frame_stack(jvm_stack);
    operand = frame->local_var.var[3];

    push_operand_stack(&(frame->operand_stack), operand);
}

/**
 * Carrega um anytype_t value de uma local_var[index]. Valida para todos os taload()
 *
 */
void taload(){
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
    any_type_t *value;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
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
    any_type_t *value;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

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
    any_type_t *value;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

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
    any_type_t *value;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

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
    any_type_t *value;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);

    frame_t *frame = peek_frame_stack(jvm_stack);
    value = pop_operand_stack(&(frame->operand_stack));

    frame->local_var.var[3] = value;
    if(value->val.primitive_val.tag == LONG|| value->val.primitive_val.tag == DOUBLE)
            frame->local_var.var[4] = value;
}

void tastore(){
    any_type_t *index, *arrayref, *value;
    uint32_t int_index;
    frame_t *frame = peek_frame_stack(jvm_stack);

    arrayref = pop_operand_stack(&(frame->operand_stack));
    index = pop_operand_stack(&(frame->operand_stack));
    value = pop_operand_stack(&(frame->operand_stack));

    int_index = index->val.primitive_val.val.val32;

    arrayref->val.reference_val.val.array.components[int_index] = *value;
}
