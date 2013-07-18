#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "structs.h"
#include "frame_stack.h"

#include "loader.h"
#include "linker.h"
#include "initializer.h"

#define MAX_NUM_OF_CLASSES 65535

pc_t jvm_pc = {0, 0, 0, 0};
frame_stack_t *jvm_stack = NULL; 
extern void (*jvm_opcode[])(void);

// Array com as classes na memória
int jvm_number_of_classes = 0;
class_t *jvm_classes[MAX_NUM_OF_CLASSES];


// UTF8 STUFF - BEGIN

/** \addtogroup Funções-Utilitárias
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


any_type_t* createMultiArray(Utf8_info_t* type, int32_t* length, u1 dimension, any_type_t* arrayref) {
    DEBUG_PRINT("got into createMultiArray with arguments: %s, %d, %d, %p\n", utf8_to_string(type), length[dimension], dimension, (void*) arrayref);
    if(arrayref == NULL) {
        arrayref = (any_type_t*) malloc(sizeof(any_type_t));
    }

    Utf8_info_t* class_name = NULL;
    class_t *class = NULL;
    u2 i = 0;
    switch(type->bytes[dimension]) {
        case 'B': //byte
            arrayref->tag = PRIMITIVE;
            arrayref->val.primitive_val.tag = BYTE;
            arrayref->val.primitive_val.val.val8 = 0;
            break;
        case 'C': //char
            arrayref->tag = PRIMITIVE;
            arrayref->val.primitive_val.tag = CHAR;
            arrayref->val.primitive_val.val.val_char = 0;
            break;
        case 'D': //double
            arrayref->tag = PRIMITIVE;
            arrayref->val.primitive_val.tag = DOUBLE;
            arrayref->val.primitive_val.val.val_double = 0;
            break;
        case 'F': //float
            arrayref->tag = PRIMITIVE;
            arrayref->val.primitive_val.tag = FLOAT;
            arrayref->val.primitive_val.val.val_float = 0;
            break;
        case 'I': //integer
            arrayref[i].tag = PRIMITIVE;
            arrayref[i].val.primitive_val.tag = INT;
            arrayref[i].val.primitive_val.val.val32 = 0;
            DEBUG_PRINT("new int na array\n");
            break;
        case 'J': //long
            arrayref->tag = PRIMITIVE;
            arrayref->val.primitive_val.tag = LONG;
            arrayref->val.primitive_val.val.val64 = 0;
            break;
        case 'S': //short
            arrayref->tag = PRIMITIVE;
            arrayref->val.primitive_val.tag = SHORT;
            arrayref->val.primitive_val.val.val16 = 0;
            break;
        case 'Z': //boolean
            arrayref->tag = PRIMITIVE;
            arrayref->val.primitive_val.tag = BOOLEAN;
            arrayref->val.primitive_val.val.val_boolean = 0;
            break;
        case 'L': //reference
            class_name = (Utf8_info_t*) malloc(sizeof(Utf8_info_t));
            class_name->bytes = (u1*) malloc(sizeof(u1) * type->length - 1 - 1 -dimension);
            strncpy((char*)class_name->bytes, (char*) &(type->bytes[1 + dimension + 1]), type->length - 1 - 1 - dimension);
            class_name->length = type->length - 1 -1 -dimension;

            class = getClass(class_name);

            createObject(class, arrayref);
            break;
        case '[': //reference - array

            arrayref->tag = REFERENCE;
            arrayref->val.reference_val.tag = ARRAY;
            arrayref->val.reference_val.val.array.length = length[dimension];
            arrayref->val.reference_val.val.array.components = (any_type_t*) malloc(sizeof(any_type_t) * length[dimension]);

            for(i=0;i < length[dimension]; i++) {
                createMultiArray(type, length, dimension + 1, &(arrayref->val.reference_val.val.array.components[i]));
            }

            break;
        default:
            printf("Unexpected initial char on method descriptor: %s\n", utf8_to_string(type));
            exit(1);
    }

    DEBUG_PRINT("Done with createMultiArray with arguments\n");
    return arrayref;
}

any_type_t* createObject(class_t* class, any_type_t* objref) {
    if(objref == NULL) {
        objref = (any_type_t*) malloc(sizeof(any_type_t));
    }

    objref->tag = REFERENCE;
    objref->val.reference_val.tag = OBJECT;
    objref->val.reference_val.val.object.objClass = class;
    objref->val.reference_val.val.object.length = class->class_file.fields_count;
    objref->val.reference_val.val.object.attributes = (any_type_t*) malloc(sizeof(any_type_t) * class->class_file.fields_count);

    u2 i = 0;
    for(i=0;i <= class->class_file.fields_count; i++) {
        if ((class->class_file.fields[i].access_flags & ACC_STATIC) == 0) {
            any_type_t *operand = &(objref->val.reference_val.val.object.attributes[i]);
            u1* b = class->class_file.constant_pool[class->class_file.fields[i].descriptor_index].info.Utf8.bytes;
            switch(b[0]) {
                case 'B': //byte
                    operand->tag = PRIMITIVE;
                    operand->val.primitive_val.tag = BYTE;
                    operand->val.primitive_val.val.val8 = 0;
                    break;
                case 'C': //char
                    operand->tag = PRIMITIVE;
                    operand->val.primitive_val.tag = CHAR;
                    operand->val.primitive_val.val.val_char = 0;
                    break;
                case 'D': //double
                    operand->tag = PRIMITIVE;
                    operand->val.primitive_val.tag = DOUBLE;
                    operand->val.primitive_val.val.val_double = 0;
                    break;
                case 'F': //float
                    operand->tag = PRIMITIVE;
                    operand->val.primitive_val.tag = FLOAT;
                    operand->val.primitive_val.val.val_float = 0;
                    break;
                case 'I': //integer
                    operand->tag = PRIMITIVE;
                    operand->val.primitive_val.tag = INT;
                    operand->val.primitive_val.val.val32 = 0;
                    break;
                case 'J': //long
                    operand->tag = PRIMITIVE;
                    operand->val.primitive_val.tag = LONG;
                    operand->val.primitive_val.val.val64 = 0;
                    break;
                case 'S': //short
                    operand->tag = PRIMITIVE;
                    operand->val.primitive_val.tag = SHORT;
                    operand->val.primitive_val.val.val16 = 0;
                    break;
                case 'Z': //boolean
                    operand->tag = PRIMITIVE;
                    operand->val.primitive_val.tag = BOOLEAN;
                    operand->val.primitive_val.val.val_boolean = 0;
                    break;
                case 'L': //reference
                    operand->tag = REFERENCE;
                    operand->val.reference_val.tag = OBJECT;
                    operand->val.reference_val.val.object.length = 0;
                    operand->val.reference_val.val.object.attributes = NULL;
                    break;
                case '[': //reference - array
                    operand->tag = REFERENCE;
                    operand->val.reference_val.tag = ARRAY;
                    operand->val.reference_val.val.array.length = 0;
                    operand->val.reference_val.val.array.components = NULL;
                    break;
                default:
                    printf("Unexpected char on method descriptor: %c\n", b[0]);
                    exit(1);
            }
        }
    }
    return objref;
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

// UTF8 STUFF - END


// CLASS_T STUFF - BEGIN

/**
 * @brief Cria a estrutura class_t da classe com nome class_name
 *
 * @param Nome da classe em UTF8
 * @return Estrutura da classe criada
 */
class_t *createClass(Utf8_info_t* class_name) {
    int index = jvm_number_of_classes;
    jvm_number_of_classes++;
    jvm_classes[index] = (class_t*) malloc(sizeof(class_t));
    jvm_classes[index]->class_name = class_name;
    jvm_classes[index]->status = CLASSE_NAO_CARREGADA;

    return jvm_classes[index];
}

/**
 * @brief Retorna a classe com nome class_name
 *
 * @param Nome da classe em UTF8
 * @return Classe procurada
 *
 * @see compare_utf8, createClass
 */
class_t *getClass(Utf8_info_t* class_name) {
    DEBUG_PRINT("got into getClass with arguments: %s\n", utf8_to_string(class_name));
    if(compare_utf8(class_name, string_to_utf8("java/lang/Object")) == 0) {
        return NULL;
    }

    int i = 0;
    for (i = 0; i < jvm_number_of_classes; ++i) {
        if(compare_utf8(jvm_classes[i]->class_name, class_name) == 0) {
            return jvm_classes[i];
        }
    }
    return createClass(class_name);
}

/**
 * @brief Retorna a classe pai da classe sub_class
 *
 * @param Classe subclasse
 * @return Classe superclasse
 *
 * @see getClass
 */
class_t* getSuperClass(class_t* sub_class) {
    DEBUG_PRINT("got into getSuperClass with arguments: %s\n", utf8_to_string(sub_class->class_name));
    u2 class_name_index = sub_class->class_file.constant_pool[sub_class->class_file.super_class].info.Class.name_index;
    return getClass(&(sub_class->class_file.constant_pool[class_name_index].info.Utf8));
}

/**
 * @brief Retorna se as classes são as mesmas
 *
 * @param Classe
 * @param Classe
 * @return 1 ou 0
 *
 * @see compare_utf8
 */
int isSameClass(class_t* a, class_t* b) {
    return (compare_utf8(a->class_name, b->class_name) == 0);
}

/**
 * @brief Retorna se a classe super_class é uma classe ancestral de sub_class
 *
 * @param Classe
 * @param Classe
 * @return 1 ou 0
 *
 * @see string_to_utf8, compare_utf8, getSuperClass, isSameClass
 */
int isSuperClassOf(class_t* super_class, class_t* sub_class) {
    class_t* class = sub_class;
    while(compare_utf8(string_to_utf8("java/lang/Object"), class->class_name) != 0) {
        if(isSameClass(super_class, getSuperClass(class))) {
            return 1;
        }
        class = getSuperClass(class);
    }
    return 0;
}
// CLASS_T STUFF - END

// METHOD STUFF - BEGIN

/**
 * @brief Retorna Code attribute do método method da classe class.
 *
 * @param Classe do método
 * @param Método do code attribute
 * @return Code attribute
 */
code_attribute_t* getCodeAttribute(class_t* class, method_info_t* method) {
    int i = 0;
    for (i = 0; method->attributes_count; i++) {
        attribute_info_t* attribute = &(method->attributes[i]);

        u1* b = class->class_file.constant_pool[attribute->attribute_name_index].info.Utf8.bytes;
        u2 length = class->class_file.constant_pool[attribute->attribute_name_index].info.Utf8.length;

        if (strncmp("Code", (char*) b, length) == 0) {
            return &(attribute->info.code);
        }
    }
    printf("ERROR: Could not find Code attribute");
    exit(1);
}

/**
 * @brief Retorna se método retorna algo
 *
 * @param Classe do método
 * @param Método
 * @return 1 ou 0
 */
int hasReturnValue(class_t* class, method_info_t* method) {
    u1* b = class->class_file.constant_pool[method->descriptor_index].info.Utf8.bytes;
    u2 length = class->class_file.constant_pool[method->descriptor_index].info.Utf8.length;

    int i = 0;
    for (i = 0; i < length; i++) {
        if (b[i] == 'V') {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Retorna método com nome method_name da classe sem ser recursivo
 *
 * @param Classe do método
 * @param Nome do método em utf8
 * @param Descriptor do método em utf8
 * @return Método
 *
 * @see compare_utf8
 */
method_info_t* getMethodOnThisClass(class_t* class, Utf8_info_t* method_name, Utf8_info_t* descriptor) {
    DEBUG_PRINT("got into getMethodOnThisClass with arguments: %s, %s, %s\n", utf8_to_string(class->class_name), utf8_to_string(method_name), utf8_to_string(descriptor));

    int i = 0;
    for (i = 0; i < class->class_file.methods_count; i++) {
        method_info_t* method = &(class->class_file.methods[i]);
        Utf8_info_t* method_name_aux = &(class->class_file.constant_pool[method->name_index].info.Utf8);

        if (compare_utf8(method_name, method_name_aux) == 0) {
            Utf8_info_t* descriptor_aux = &(class->class_file.constant_pool[method->descriptor_index].info.Utf8);
            if (compare_utf8(descriptor, descriptor_aux) == 0) {
                DEBUG_PRINT("Done with getMethodOnThisClass with arguments: %s, %s, %s. Found method.\n", utf8_to_string(class->class_name), utf8_to_string(method_name), utf8_to_string(descriptor));
                return method;
            }
        }
    }
    DEBUG_PRINT("Done with getMethodOnThisClass with arguments: %s, %s, %s. DID NOT Found method.\n", utf8_to_string(class->class_name), utf8_to_string(method_name), utf8_to_string(descriptor));
    return NULL;
}

/**
 * @brief Retorna método com nome method_name da classe fazendo resolução completa
 *
 * @param Classe do método
 * @param Nome do método em utf8
 * @param Descriptor do método em utf8
 * @return Método
 *
 * @see getSuperClass, getMethodOnThisClass
 */
method_info_t* getMethod(class_t* class, Utf8_info_t* method_name, Utf8_info_t* descriptor) {
    DEBUG_PRINT("got into getMethod with arguments: %s, %s, %s\n", utf8_to_string(class->class_name), utf8_to_string(method_name), utf8_to_string(descriptor));

    if (class->status == CLASSE_NAO_CARREGADA) {
        loadClass(class);
    }
    if (class->status == CLASSE_NAO_LINKADA) {
        linkClass(class);
    }
    if (class->status == CLASSE_NAO_INICIALIZADA) {
        initializeClass(class);
    }

    method_info_t* method = getMethodOnThisClass(class, method_name, descriptor);
    while (method == NULL) {
        class = getSuperClass(class);
        if (class == NULL) {
            printf("ERROR: Method %s not found\n", utf8_to_string(method_name));
            exit(1);
        }

        if ((method->access_flags & ACC_PRIVATE) == ACC_PRIVATE) {
            printf("ERROR: Founded method is private\n");
            exit(1);
        }
    }

    DEBUG_PRINT("Done with getMethod with arguments: %s, %s, %s\n", utf8_to_string(class->class_name), utf8_to_string(method_name), utf8_to_string(descriptor));

    return method;
}

/**
 * @brief Retorna o número de argumentos que o método precisa
 *
 * @param Classe do método
 * @param Método
 * @return Número de argumentos
 */
int getNumberOfArguments(class_t* class, method_info_t* method) {
    u1* b = class->class_file.constant_pool[method->descriptor_index].info.Utf8.bytes;
    u2 length = class->class_file.constant_pool[method->descriptor_index].info.Utf8.length;

    int counter = 0;

    if ((method->access_flags & ACC_STATIC) != ACC_STATIC) {
        counter++;
    }

    int i = 1;
    for (i = 1; i < length; i++) {
        switch (b[i]) {
            case 'B': //byte
            case 'C': //char
            case 'D': //double
            case 'F': //float
            case 'I': //integer
            case 'J': //long
            case 'S': //short
            case 'Z': //boolean
                counter++;
                break;
            case 'L': //reference
                for(;i < length && b[i] != ';'; i++); //go until ';'

                counter++;

                break;
            case '[': //reference - array
                break;
            case ')':
                return counter;
            default:
                printf("Unexpected char on method descriptor: %c\n", b[i]);
                exit(1);
        }
    }
    printf("ERROR: Could not find ')' in method description");
    exit(1);
}

// METHOD STUFF - END

// OPCODE STUFF - BEGIN

/**
 * @brief Retorna o número de bytes com operandos do opcode que começa em code[index]
 *
 * @param Array dos opcode
 * @param Index do opcode
 * @return Número de bytes com operandos
 */
int getNumberOfOpcodeOperandsInBytes(u1* code, u2 index) {
    int counter = 0;
    int padding = 0;
    u4 low = 0;
    u4 high = 0;
    u4 npairs = 0;
    u1 byte1 = 0;
    u1 byte2 = 0;
    u1 byte3 = 0;
    u1 byte4 = 0;

    switch(code[index]) {
        case 0xb9:
        case 0xba:
        case 0xc8:
        case 0xc9:
            return 4;
        case 0xaa: //tableswitch is special
            counter = 1;
            padding = 4 - (index % 4) - 1;
            counter += padding; // 1 byte do opcode + allignment bytes

            counter += 4; // jump default

            byte1 = code[index + counter];
            byte2 = code[index + counter + 1];
            byte3 = code[index + counter + 2];
            byte4 = code[index + counter + 3];
            low = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

            counter += 4; // count low

            byte1 = code[index + counter];
            byte2 = code[index + counter + 1];
            byte3 = code[index + counter + 2];
            byte4 = code[index + counter + 3];
            high = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

            counter += 4; // count high

            counter += (4 * (high - low + 1)); // count the x offsets

            return counter;
        case 0xab: //lookupswitch is special
            counter = 1;
            padding = 4 - (index % 4) - 1;
            counter += padding; // 1 byte do opcode + allignment bytes

            counter += 4; //ignore default_offset

            byte1 = code[index + counter];
            byte2 = code[index + counter + 1];
            byte3 = code[index + counter + 2];
            byte4 = code[index + counter + 3];
            npairs = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

            counter += 4; // count the npairs

            counter += (8 * npairs); // count all the key:offset pairs

            return counter;
        case 0xc5:
            return 3;
        case 0xc4: //wide is special
            if (code[index + 1] == 0x84) {
                // forma com iinc
                return 5;
            } else {
                return 3;
            }
        case 0xbd:
        case 0xc0:
        case 0xc1:
        case 0xb7:
        case 0xb8:
        case 0xb6:
        case 0x13:
        case 0x14:
        case 0xbb:
        case 0xb5:
        case 0xb3:
        case 0xb4:
        case 0xb2:
        case 0x84:
        case 0x11:
        case 0xa7:
        case 0xa5:
        case 0xa6:
        case 0x9f:
        case 0xa2:
        case 0xa3:
        case 0xa4:
        case 0xa1:
        case 0xa0:
        case 0x99:
        case 0x9c:
        case 0x9d:
        case 0x9e:
        case 0x9b:
        case 0x9a:
        case 0xc7:
        case 0xc6:
        case 0xa8:
            return 2;
        case 0x19:
        case 0x3a:
        case 0x18:
        case 0x39:
        case 0x17:
        case 0x38:
        case 0x15:
        case 0x36:
        case 0x12:
        case 0x16:
        case 0x37:
        case 0xa9:
        case 0x10:
        case 0xbc:
            return 1;
        default:
            return 0;
    }
    return 0;
}

/**
 * @brief Avança jvm_pc.code_pc para o próximo opcode
 *
 * @see getCodeAttribute, getNumberOfOpcodeOperandsInBytes
 */
void goToNextOpcode() {
    if (jvm_pc.jumped) {
        jvm_pc.jumped = 0;
        return;
    }

    jvm_pc.jumped = 0;

    code_attribute_t* code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);

    jvm_pc.code_pc += getNumberOfOpcodeOperandsInBytes(code_attribute->code, jvm_pc.code_pc) + 1;
}
// OPCODE STUFF - END

// JVM OPERATION STUFF - START

/**
 * @brief Levanta uma exceção
 *
 * @param Classe da exceção
 *
 * @see getClass, isSameClass, isSuperClassOf, getCodeAttribute
 */
void throwException(class_t* exception_class) {
    // check for handlers 
    code_attribute_t* code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    u2 exception_table_length = code_attribute->exception_table_length;
    u2 i = 0;
    for (i = 0; i< exception_table_length; i++) {
        u2 catch_exception_class_index = jvm_pc.currentClass->class_file.constant_pool[code_attribute->exception_table[i].catch_type].info.Class.name_index;
        class_t* catch_exception_class = getClass(&(jvm_pc.currentClass->class_file.constant_pool[catch_exception_class_index].info.Utf8));
        if (code_attribute->exception_table[i].catch_type == 0 || (isSameClass(exception_class, catch_exception_class) || isSuperClassOf(catch_exception_class, exception_class))) {
            if (code_attribute->exception_table[i].start_pc >= jvm_pc.code_pc && code_attribute->exception_table[i].end_pc < jvm_pc.code_pc) {
                // Executar catch code
                jvm_pc.code_pc = code_attribute->exception_table[i].handler_pc;
                return;
            }
        }
    }

    //Exception não foi tratada
    // pop stack
    frame_t *frame = pop_frame_stack(&jvm_stack);
    if (frame == NULL) {
        printf("Exception não foi tratada. JVM será terminada.\n");
        exit(1);
    }

    // change PC
    jvm_pc = frame->return_address;

    // re-throw exception
    throwException(exception_class);

    free(frame);
}

/**
 * @brief Retorna da função atual
 *
 * @see hasReturnValue
 */
void returnFromFunction() {
    DEBUG_PRINT("got into returnFromFunction\n");

    // pop stack
    frame_t *frame = pop_frame_stack(&jvm_stack);

    Utf8_info_t* current_method_name = &(frame->current_class->class_file.constant_pool[frame->current_method->name_index].info.Utf8);

    if (compare_utf8(current_method_name, string_to_utf8("<clinit>")) == 0) {
        // Executou clinit da classe da funcao main
        return;
    } else if (compare_utf8(current_method_name, string_to_utf8("main")) == 0) {
        // Execução retornou da função main. Programa executado com sucesso
        exit(0);
    }

    // change PC
    jvm_pc = frame->return_address;

    // put return value on the new frame's operand stack if any
    if(hasReturnValue(frame->current_class, frame->current_method)) {
        frame_t *invokerFrame = peek_frame_stack(jvm_stack);
        any_type_t *operand = pop_operand_stack(&(frame->operand_stack));
        push_operand_stack(&(invokerFrame->operand_stack), operand);
    }

    free(frame);
    DEBUG_PRINT("done with returnFromFunction\n");
}


/**
 * @brief Chama método
 *
 * @param Classe do método
 * @param Método a ser chamado
 *
 * @see getCodeAttribute, getNumberOfArguments
 */
void callMethod(class_t* class, method_info_t* method) {
    Utf8_info_t* method_name = &(class->class_file.constant_pool[method->name_index].info.Utf8);
    DEBUG_PRINT("got into callMethod with arguments: %s , %s\n", utf8_to_string(class->class_name), utf8_to_string(method_name));
    if (class->status == CLASSE_NAO_CARREGADA) {
        loadClass(class);
    }
    if (class->status == CLASSE_NAO_LINKADA) {
        linkClass(class);
    }
    if (class->status == CLASSE_NAO_INICIALIZADA && compare_utf8(method_name, string_to_utf8("<clinit>")) != 0) {
        initializeClass(class);
    }

    code_attribute_t* code_attribute = getCodeAttribute(class, method);

    frame_t *invokerFrame = peek_frame_stack(jvm_stack);
    frame_t *frame = (frame_t*) malloc(sizeof(frame_t));
    frame->current_class = class;
    frame->current_method = method;
    frame->return_address = jvm_pc;
    frame->local_var.size = code_attribute->max_locals; 
    frame->local_var.var = (any_type_t**) malloc(frame->local_var.size * sizeof(any_type_t*));
    frame->operand_stack.depth = 0;
    frame->operand_stack.head = -1;
    frame->operand_stack.size = code_attribute->max_stack;
    frame->operand_stack.operand = (any_type_t**) malloc(frame->operand_stack.size * sizeof(any_type_t**));


    //get number of arguments from classfile
    int number_of_arguments = getNumberOfArguments(class, method);

    // pop arguments from operand stack and
    // insert them on local_var
    int i = 0;
    int local_var_index = 0;
    for (i = 0; i < number_of_arguments; i++) {
        any_type_t *operand = pop_operand_stack(&(invokerFrame->operand_stack));
        push_operand_stack(&(frame->operand_stack), operand);
    }
    for (i = 0; i < number_of_arguments; i++) {
        any_type_t *operand = pop_operand_stack(&(frame->operand_stack));

        frame->local_var.var[local_var_index] = operand;
        local_var_index++;
        if(operand->val.primitive_val.tag == DOUBLE ||operand->val.primitive_val.tag == LONG) 
            local_var_index++;
    }


    push_frame_stack(&jvm_stack, frame);

    //set pc
    jvm_pc.currentClass = class;
    jvm_pc.method = method;
    jvm_pc.code_pc = 0;
    jvm_pc.jumped = 1;

    DEBUG_PRINT("Done with callMethod with arguments: %s , %s\n", utf8_to_string(class->class_name), utf8_to_string(method_name));
    return;
}
/** @} */
// JVM OPERATION STUFF - END

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
 * @brief Função main. Inicio da JVM
 *
 * @param Tamanho do argv
 * @param Argumentos passados por linha de comando
 *
 * @see string_to_utf8, char_to_array_reference, createClass, getCodeAttribute, getMethod, goToNextOpcode, callMethod
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Instrução: Rode com 'jvm class_identifier [args]'\n");
        printf("                ou: 'jvm -p class_identifier'\n");
        return 1;
    }

    if (strncmp(argv[1], "-p", 2) == 0) {
        class_t *class = createClass(string_to_utf8(argv[2]));
        loadClass(class);
        MostraClasse(&(class->class_file));
        return 0;
    }

    class_t *class = createClass(string_to_utf8(argv[1]));

    // frame init
    frame_t *frame = (frame_t*) malloc(sizeof(frame_t));
    frame->current_class = class;
    push_frame_stack(&jvm_stack, frame);

    frame->current_method = getMethod(class, string_to_utf8("main"), string_to_utf8("([Ljava/lang/String;)V"));
    frame->return_address.method = NULL;
    frame->return_address.code_pc = 0;
    frame->local_var.size = 0;
    frame->local_var.var = NULL;
    frame->operand_stack.depth = 0;
    frame->operand_stack.head = -1;
    frame->operand_stack.size = 1;
    frame->operand_stack.operand = (any_type_t**) malloc(frame->operand_stack.size * sizeof(any_type_t**));


    // Criar array de strings com argumentos passados (argv[2:]) e colocar na pilha de operandos
    any_type_t *args = (any_type_t*) malloc(sizeof(any_type_t)); 
    args->tag = REFERENCE;
    args->val.reference_val.tag = ARRAY;
    args->val.reference_val.val.array.length = argc-2;
    args->val.reference_val.val.array.components = (any_type_t *) malloc(args->val.reference_val.val.array.length * sizeof(any_type_t));
    uint32_t i = 0;
    for (i = 0; i < args->val.reference_val.val.array.length; i++) {
        args->val.reference_val.val.array.components[i] = *(char_to_array_reference(argv[i+2]));
    }
    push_operand_stack(&(frame->operand_stack), args);


    // Chamar main
    callMethod(frame->current_class, frame->current_method);
    jvm_pc.jumped = 0;

    code_attribute_t* code_attribute = NULL;
    do {
        //fetch opcode
        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
        u1 opcode = code_attribute->code[jvm_pc.code_pc];

        //execute the action for the opcode;
        DEBUG_PRINT("Going to execute %#x at %d\n", opcode, jvm_pc.code_pc);
        jvm_opcode[opcode]();

        goToNextOpcode();

        code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
    } while(jvm_pc.code_pc < code_attribute->code_length);

    return 0;
}
