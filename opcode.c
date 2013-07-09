#include "opcode.h"
#include "frame_stack.h"
#include "structs.h"
#include "jvm.h"

extern frame_stack_t *jvm_stack;

extern pc_t jvm_pc;

/**
* name: aconst_null
* desc: push a null reference onto the stack
* params: void
* return: void
**/

void aconst_null(){
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = REFERENCE;
    operand->val.reference_val.tag = NULL_REFERENCE;
    operand->val.reference_val.val.val_null = NULL;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = -1;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 0;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 1;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 2;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 3;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 4;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = 5;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = 0;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = 1;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = 0;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = 1;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = 2;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = 0;

    frame_t* frame = peek_frame_stack(jvm_stack);
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

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = 1;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);
}

/**
* name: bipush
* desc: push a byte onto the stack as an integer value
* params: byte b
* return: void
**/
void bipush(){
    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 b = code_attribute->code[jvm_pc.code_pc+1];
    int value = (int32_t) b;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = value;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

/**
* name: sipush
* desc: push a short onto the stack
* params: byte b1, b2
* return: void
**/
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
* name: ldc
* desc: push a constant #index from a constant pool (String, int or float) onto the stack
* params: byte b
* return: void
**/
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
* name: ldc_w
* desc: push a constant #index from a constant pool (String, int or float) onto the stack (wide index is constructed as indexbyte1 << 8 + indexbyte2)
* params: byte b1, byte b2
* return: void
**/
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
* name: ldc2_w
* desc: push a constant #index from a constant pool (double or long) onto the stack (wide index is constructed as indexbyte1 << 8 + indexbyte2)
* params: byte b1, byte b2
* return: void
**/
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

void iload(){
    uint32_t *campo;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    *campo = frame->local_var[index].var;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = *campo;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void lload(){
    uint32_t *campo1;
    uint32_t *campo2;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo1 = frame->local_var[index].var;
    campo2 = frame->local_var[index+1].var;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = ((*campo1)<<8)|(*campo2);

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void fload(){
    uint32_t *campo;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    *campo = frame->local_var[index].var;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = *campo;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void dload(){
    uint32_t *campo1;
    uint32_t *campo2;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo1 = frame->local_var[index].var;
    campo2 = frame->local_var[index+1].var;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = ((*campo1)<<8)|(*campo2);

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void iload_0(){
    uint32_t *campo;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo = frame->local_var[0].var;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = *campo;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void iload_1(){
    uint32_t *campo;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo = frame->local_var[1].var;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = *campo;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void iload_2(){
    uint32_t *campo;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo = frame->local_var[2].var;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = *campo;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void iload_3(){}
    uint32_t *campo;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo = frame->local_var[3].var;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = INT;
    operand->val.primitive_val.val.val32 = *campo;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void lload_0(){
    uint32_t *campo1;
    uint32_t *campo2;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo1 = frame->local_var[0].var;
    campo2 = frame->local_var[1].var;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = ((*campo1)<<8)|(*campo2);

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void lload_1(){
    uint32_t *campo1;
    uint32_t *campo2;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo1 = frame->local_var[1].var;
    campo2 = frame->local_var[2].var;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = ((*campo1)<<8)|(*campo2);

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void lload_2(){
    uint32_t *campo1;
    uint32_t *campo2;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo1 = frame->local_var[2].var;
    campo2 = frame->local_var[3].var;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = ((*campo1)<<8)|(*campo2);

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void lload_3(){
    uint32_t *campo1;
    uint32_t *campo2;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo1 = frame->local_var[3].var;
    campo2 = frame->local_var[4].var;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = LONG;
    operand->val.primitive_val.val.val64 = ((*campo1)<<8)|(*campo2);

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void fload_0(){
    uint32_t *campo;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    *campo = frame->local_var[0].var;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = *campo;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void fload_1(){
    uint32_t *campo;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    *campo = frame->local_var[1].var;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = *campo;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void fload_2(){
    uint32_t *campo;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    *campo = frame->local_var[2].var;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = *campo;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void fload_3(){
    uint32_t *campo;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    *campo = frame->local_var[3].var;

    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = FLOAT;
    operand->val.primitive_val.val.val_float = *campo;

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void dload_0(){
    uint32_t *campo1;
    uint32_t *campo2;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo1 = frame->local_var[0].var;
    campo2 = frame->local_var[1].var;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = ((*campo1)<<8)|(*campo2);

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void dload_1(){
    uint32_t *campo1;
    uint32_t *campo2;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo1 = frame->local_var[1].var;
    campo2 = frame->local_var[2].var;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = ((*campo1)<<8)|(*campo2);

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void dload_2(){
    uint32_t *campo1;
    uint32_t *campo2;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo1 = frame->local_var[2].var;
    campo2 = frame->local_var[3].var;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = ((*campo1)<<8)|(*campo2);

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}

void dload_3(){
    uint32_t *campo1;
    uint32_t *campo2;

    code_attribute_t *code_attribute = getCodeAttribute(jvm_pc.code_pc, jvm_pc.method);
    u1 index = code_attribute->code[jvm_pc.code_pc+1];

    frame_t *frame = peek_frame_stack(jvm_stack);
    campo1 = frame->local_var[3].var;
    campo2 = frame->local_var[4].var;
    any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));

    operand->tag = PRIMITIVE;
    operand->val.primitive_val.tag = DOUBLE;
    operand->val.primitive_val.val.val_double = ((*campo1)<<8)|(*campo2);

    frame_t* frame = peek_frame_stack(jvm_stack);
    push_operand_stack(&(frame->operand_stack), operand);

}
