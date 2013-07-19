#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "structs.h"
#include "opcode.h"
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

/** \addtogroup JVM-Core
 * @{
 */

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

    DEBUG_PRINT("head=%d\n", frame->operand_stack.head);
    // put return value on the new frame's operand stack if any
    if(hasReturnValue(frame->current_class, frame->current_method)) {
        frame_t *invokerFrame = peek_frame_stack(jvm_stack);
        any_type_t *operand = pop_operand_stack(&(frame->operand_stack));
        push_operand_stack(&(invokerFrame->operand_stack), operand);
    }

    free(frame);
    DEBUG_PRINT("done with returnFromFunction %s\n", utf8_to_string(current_method_name));
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
    DEBUG_PRINT("number_of_arguments = %d\n", number_of_arguments);

    // pop arguments from operand stack and
    // insert them on local_var
    int i = 0;
    int local_var_index = 0;
    operand_stack_t aux_operand_stack;
    aux_operand_stack.depth = 0;
    aux_operand_stack.head = -1;
    aux_operand_stack.size = number_of_arguments;
    aux_operand_stack.operand = (any_type_t**) malloc(number_of_arguments * sizeof(any_type_t**));
    for (i = 0; i < number_of_arguments; i++) {
        any_type_t *operand = pop_operand_stack(&(invokerFrame->operand_stack));
        push_operand_stack(&(aux_operand_stack), operand);
    }
    for (i = 0; i < number_of_arguments; i++) {
        any_type_t *operand = pop_operand_stack(&(aux_operand_stack));

        frame->local_var.var[local_var_index] = operand;
        local_var_index++;
        if(operand->val.primitive_val.tag == DOUBLE ||operand->val.primitive_val.tag == LONG) 
            local_var_index++;
    }
    free(aux_operand_stack.operand);


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
