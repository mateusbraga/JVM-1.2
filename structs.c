#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "structs.h"
#include "jvm.h"

/** \addtogroup Estruturas
 * @{
 */

/**
 * @brief Converte um char* para um Utf8_info_t*
 *
 * @param String a ser convertida
 * @return Estrutura Utf8 criada.
 */
Utf8_info_t* string_to_utf8(char* a) {
    Utf8_info_t* utf8 = (Utf8_info_t*) malloc(sizeof(Utf8_info_t));
    utf8->length = strlen(a);
    utf8->bytes = (u1*) a;
    return utf8;
}

/**
 * @brief Converte um Utf8_info_t* em um char*
 *
 * @param String utf8 a ser convertida
 * @return string criada.
 */
char* utf8_to_string(Utf8_info_t* utf8) {
    char* string = NULL;
    string = (char*) malloc(sizeof(char) * utf8->length + 1);
    strncpy(string, (char*) utf8->bytes, utf8->length);
    string[utf8->length] = '\0';
    return string;
}

/**
 * @brief Compara dois utf8.
 *
 * @param Primeiro utf8
 * @param Segundo utf8
 * @return 0 se os utf8s são iguais.
 */
int compare_utf8(Utf8_info_t* a, Utf8_info_t* b) {
    if (a->length == b->length) {
        return strncmp((char*) a->bytes,(char*) b->bytes, b->length);
    }
    return -1;
}

/**
 * @brief Retorna o numero de caracteres em utf8 representada na string.
 *
 * @param String com possíveis caracteres em utf8.
 * @return número de caractéres em utf8
 */
u2 get_utf8_length_from_char(char* string) {
    u2 counter = 0;
    u2 length = strlen(string);

    u2 i = 0;
    for (i = 0; i < length; ) {
        if((string[i] & 0xe0) == 0xe0) {
            counter++;
            i = i + 3;
        } else if((string[i] & 0xc0) == 0xc0) {
            counter++;
            i = i + 2;
        } else {
            counter++;
            i++;
        }
    }
    return counter;
}

/**
 * @brief Leia o próximo caractere que começa em pos. Altera pos para o possível próximo caractere a ler.
 *
 * @param String com possíveis caracteres em utf8.
 * @param Posição em string do caractere a ler
 * @return valor do caractere em u2
 */
u2 scan_utf8_char_from_char(char* string, u2 *pos) {
    u2 original_pos = *pos;

    if((string[original_pos] & 0xe0) == 0xe0) {
        // 3 bytes 
        *pos = *pos + 3;
        assert(original_pos + 2 < strlen(string));
        char x = string[original_pos];
        char y = string[original_pos + 1];
        char z = string[original_pos + 2];

        return ((x & 0xf) << 12) + ((y & 0x3f) << 6) + (z & 0x3f);
    } else if((string[original_pos] & 0xc0) == 0xc0) {
        // 2 bytes 
        *pos = *pos + 2;
        assert(original_pos + 1 < strlen(string));
        char x = string[original_pos];
        char y = string[original_pos + 1];

        return ((x & 0x1f) << 6) + (y & 0x3f);
    } else {
        // 1 bytes 
        *pos = *pos + 1;
        return string[original_pos];
    }
}

/**
 * @brief Cria um any_type_t que é uma array de caracteres a partir da string.
 *
 * @param String com caracteres
 * @return any_type_t* criada
 *
 * @see get_utf8_length_from_char, scan_utf8_char_from_char
 */
any_type_t* char_to_array_reference(char* string) {
    any_type_t* value = (any_type_t *) malloc(sizeof(any_type_t));

    u2 length = get_utf8_length_from_char(string);

    value->tag = REFERENCE;
    value->val.reference_val.tag = ARRAY;
    value->val.reference_val.val.array.length = length;
    value->val.reference_val.val.array.components = (any_type_t *) malloc(length * sizeof(any_type_t));

    u2 i = 0;
    u2 j = 0;
    for (i = 0; i < length && j < strlen(string); i++) {
        value->val.reference_val.val.array.components[i].tag = PRIMITIVE;
        value->val.reference_val.val.array.components[i].val.primitive_val.tag = CHAR;
        value->val.reference_val.val.array.components[i].val.primitive_val.val.val_char = scan_utf8_char_from_char(string, &j);
    }

    return value;
}

/**
 * @brief Cria um any_type_t que é uma array de caracteres a partir da utf8.
 *
 * @param UTF8 base
 * @return any_type_t* criada
 *
 * @see char_to_array_reference
 */
any_type_t* utf8_to_array_reference(Utf8_info_t* utf8) {
    char* string = (char*) malloc(utf8->length + 1);
    strncpy(string, (char*) utf8->bytes, utf8->length);
    string[utf8->length] = '\0';
    return char_to_array_reference(string);
}

void print_any_type(any_type_t* anytype) {
    if (anytype == NULL) {
        DEBUG_PRINT("ERROR: anytype == NULL in print_any_type\n");
        exit(1);
    }
    switch (anytype->tag) {
        case PRIMITIVE:
            switch(anytype->val.primitive_val.tag) {
                case BOOLEAN:
                    DEBUG_PRINT("anytype is BOOLEAN == %d\n", anytype->val.primitive_val.val.val_boolean);
                    break;
                case CHAR:
                    DEBUG_PRINT("anytype is CHAR == %d\n", anytype->val.primitive_val.val.val_char);
                    break;
                case FLOAT:
                    DEBUG_PRINT("anytype is FLOAT == %f\n", anytype->val.primitive_val.val.val_float);
                    break;
                case DOUBLE:
                    DEBUG_PRINT("anytype is DOUBLE == %f\n", anytype->val.primitive_val.val.val_double);
                    break;
                case RETURN_ADDRESS:
                    DEBUG_PRINT("anytype is RETURN_ADDRESS == %ud\n", anytype->val.primitive_val.val.val_return_addr);
                    break;
                case BYTE:
                    DEBUG_PRINT("anytype is byte == %d\n", anytype->val.primitive_val.val.val8);
                    break;
                case SHORT:
                    DEBUG_PRINT("anytype is short == %d\n", anytype->val.primitive_val.val.val16);
                    break;
                case INT:
                    DEBUG_PRINT("anytype is int == %d\n", anytype->val.primitive_val.val.val32);
                    break;
                case LONG:
                    DEBUG_PRINT("anytype is long == %ld\n", anytype->val.primitive_val.val.val64);
                    break;
                default:
                    DEBUG_PRINT("anytype is invalid!\n");

            }
            break;
        case REFERENCE:
            switch(anytype->val.reference_val.tag) {
                case OBJECT:
                    DEBUG_PRINT("anytype is OBJECT of class %s\n", utf8_to_string(anytype->val.reference_val.val.object.objClass->class_name));
                    break;
                case ARRAY:
                    if ( anytype->val.reference_val.val.array.length > 0) {
                        switch (anytype->val.reference_val.val.array.components[0].tag) {
                            case PRIMITIVE:
                                switch(anytype->val.reference_val.val.array.components[0].val.primitive_val.tag) {
                                    case BOOLEAN:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type BOOLEAN \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    case CHAR:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type CHAR \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    case FLOAT:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type FLOAT \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    case DOUBLE:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type DOUBLE \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    case RETURN_ADDRESS:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type RETURN_ADDRESS \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    case BYTE:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type BYTE \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    case SHORT:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type SHORT \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    case INT:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type INT \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    case LONG:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type LONG \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    default:
                                        DEBUG_PRINT("anytype is array invalid!\n");
                                }
                                break;
                            case REFERENCE:
                                switch(anytype->val.reference_val.val.array.components[0].val.reference_val.tag) {
                                    case OBJECT:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type OBJECT \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    case ARRAY:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type ARRAY \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    case NULL_REFERENCE:
                                        DEBUG_PRINT("anytype is ARRAY of length %d and type NULL_REFERENCE \n", (anytype->val.reference_val.val.array.length));
                                        break;
                                    default:
                                        DEBUG_PRINT("anytype is array reference invalid!\n");
                                }
                                break;
                        }
                    } else {
                        DEBUG_PRINT("anytype is ARRAY of length %d\n", (anytype->val.reference_val.val.array.length));
                    }
                    break;
                case NULL_REFERENCE:
                    DEBUG_PRINT("anytype is NULL_REFERENCE\n");
                    break;
                default:
                    DEBUG_PRINT("anytype is invalid!\n");
            }
    }
}

/**
 * @brief Seta o valor default em variable do tipo representado no descriptor.
 *
 * @param Variável à setar
 * @param Descriptor do tipo da variável
 */
void setDefault(any_type_t* variable, char* descriptor) {
    DEBUG_PRINT("got in setDefault\n");
    Utf8_info_t* class_name = NULL;
    switch(descriptor[0]) {
        case 'B': //byte
            variable->tag = PRIMITIVE;
            variable->val.primitive_val.tag = BYTE;
            variable->val.primitive_val.val.val8 = 0;
            break;
        case 'C': //char
            variable->tag = PRIMITIVE;
            variable->val.primitive_val.tag = CHAR;
            variable->val.primitive_val.val.val_char = 0;
            break;
        case 'D': //double
            variable->tag = PRIMITIVE;
            variable->val.primitive_val.tag = DOUBLE;
            variable->val.primitive_val.val.val_double = 0;
            break;
        case 'F': //float
            variable->tag = PRIMITIVE;
            variable->val.primitive_val.tag = FLOAT;
            variable->val.primitive_val.val.val_float = 0;
            break;
        case 'I': //integer
            variable->tag = PRIMITIVE;
            variable->val.primitive_val.tag = INT;
            variable->val.primitive_val.val.val32 = 0;
            break;
        case 'J': //long
            variable->tag = PRIMITIVE;
            variable->val.primitive_val.tag = LONG;
            variable->val.primitive_val.val.val64 = 0;
            break;
        case 'S': //short
            variable->tag = PRIMITIVE;
            variable->val.primitive_val.tag = SHORT;
            variable->val.primitive_val.val.val16 = 0;
            break;
        case 'Z': //boolean
            variable->tag = PRIMITIVE;
            variable->val.primitive_val.tag = BOOLEAN;
            variable->val.primitive_val.val.val_boolean = 0;
            break;
        case 'L': //reference
            variable->tag = REFERENCE;
            variable->val.reference_val.tag = OBJECT;
            u2 i = 0;
            for (i = 1; descriptor[i] != ';'; i++);
            class_name = (Utf8_info_t*) malloc(sizeof(Utf8_info_t));
            class_name->bytes = (u1*) malloc(sizeof(u1) * i - 1);
            strncpy((char*)class_name->bytes, descriptor, i - 1);
            class_name->length = i - 1;
            
            variable->val.reference_val.val.object.objClass = getClass(class_name);
            variable->val.reference_val.val.object.length = 0;
            variable->val.reference_val.val.object.attributes = NULL;
            break;
        case '[': //reference - array
            variable->tag = REFERENCE;
            variable->val.reference_val.tag = ARRAY;
            variable->val.reference_val.val.array.length = 0;
            variable->val.reference_val.val.array.components = NULL;
            break;
        default:
            printf("Unexpected char on descriptor: %c\n", descriptor[0]);
            exit(1);
    }
}

/**
 * @brief Cria uma array de várias dimensões, com tipo type, comprimento length. Cria um novo anytype ou usa arrayref.
 *
 * @param Tipo da última dimensão da array
 * @param Array com os comprimentos de cada dimensão
 * @param Dimensão a ser criada
 * @param any_type_t já alocado, ou NULL para criar novo any_type_t
 * @return any_type_t da arrayref criada.
 */
any_type_t* createMultiArray(Utf8_info_t* type, int32_t* length, u1 dimension, any_type_t* arrayref) {
    DEBUG_PRINT("got into createMultiArray with arguments: %s, %d, %d, %p\n", utf8_to_string(type), length[dimension], dimension, (void*) arrayref);
    if(arrayref == NULL) {
        arrayref = (any_type_t*) malloc(sizeof(any_type_t));
    }

    setDefault(arrayref, (char*) &(type->bytes[dimension]));

    if (type->bytes[dimension] == '[') { //reference - array
            arrayref->tag = REFERENCE;
            arrayref->val.reference_val.tag = ARRAY;
            arrayref->val.reference_val.val.array.length = length[dimension];
            arrayref->val.reference_val.val.array.components = (any_type_t*) malloc(sizeof(any_type_t) * length[dimension]);

            int32_t i = 0;
            for(i=0;i < length[dimension]; i++) {
                createMultiArray(type, length, dimension + 1, &(arrayref->val.reference_val.val.array.components[i]));
            }
    }

    DEBUG_PRINT("Done with createMultiArray\n");
    return arrayref;
}

/**
 * @brief Cria um objeto da classe class. Aloca um novo any_type_t ou usa objref.
 *
 * @param Classe do objeto a ser criado
 * @param any_type_t já alocado, ou NULL para criar novo any_type_t
 * @return any_type_t do objref criado.
 */
any_type_t* createObject(class_t* class, any_type_t* objref) {
    DEBUG_PRINT("got into createObject with arguments: %s\n", utf8_to_string(class->class_name));
    if(objref == NULL) {
        objref = (any_type_t*) malloc(sizeof(any_type_t));
    }

    objref->tag = REFERENCE;
    objref->val.reference_val.tag = OBJECT;
    objref->val.reference_val.val.object.objClass = class;
    objref->val.reference_val.val.object.length = class->class_file.fields_count;
    objref->val.reference_val.val.object.attributes = (any_type_t*) malloc(sizeof(any_type_t) * class->class_file.fields_count);

    u2 i = 0;
    for(i=0;i < class->class_file.fields_count; i++) {
        if ((class->class_file.fields[i].access_flags & ACC_STATIC) == 0) { // somente setar os campos que não são estáticos
            u1* b = class->class_file.constant_pool[class->class_file.fields[i].descriptor_index].info.Utf8.bytes;
            setDefault(&(objref->val.reference_val.val.object.attributes[i]), (char*) b);
        }
    }

    return objref;
}


/** @} */
