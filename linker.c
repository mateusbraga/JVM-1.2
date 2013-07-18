#include <stdio.h>
#include <stdlib.h>

#include "loader.h"
#include "linker.h"
#include "structs.h"
#include "jvm.h"

/** \addtogroup Linker
 * @{
 */

// PREPARATION STUFF - BEGIN
/**
 * @brief Preparacao. Inicializa todos os campos estaticos com seus valores defaults.
 *
 * @param classe que sera preparada.
 * 
 */
void preparar (class_t* class) {
	class->static_fields = (any_type_t**) malloc(sizeof(any_type_t*) * class->class_file.fields_count);
	u2 i;
	for (i = 1; i < class->class_file.fields_count; i++) {
		if ((class->class_file.fields[i].access_flags & ACC_STATIC) == ACC_STATIC)  {
			any_type_t *operand = (any_type_t*) malloc(sizeof(any_type_t));
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
          	class->static_fields[i] = operand;
		}
	}
}
// PREPARATION STUFF - END

// VERIFICATION STUFF - BEGIN
/**
 * @brief Verificacao. Analisa se a classe final nao eh extendida. Se toda classe tem superclasse. Se tudo que aponta para a constant pool aponta para o local correto.
 *
 * @param classe que sera verificada
 * 
 */
void verificar (class_t* class) {
	if (class->status == CLASSE_NAO_CARREGADA) {
        loadClass(class);
    }
	//Verificar se os indices apontam para o lugar correto na Constant Pool
	u2 i;
	u1 tag;
	for (i = 1; i < (class->class_file.constant_pool_count); i++) {
		tag = class->class_file.constant_pool[i].tag;
		if (tag == CONSTANT_Class) {
			if (class->class_file.constant_pool[class->class_file.constant_pool[i].info.Class.name_index].tag != CONSTANT_Utf8) {
				printf("Erro: Indice apontado pela classe invalido.\n");
				exit(1);		
			}
		}
		if (tag == CONSTANT_Fieldref) {
			if (class->class_file.constant_pool[class->class_file.constant_pool[i].info.Fieldref.class_index].tag != CONSTANT_Class) {
				printf("Erro: Indice do class_index apontado pela fieldref invalido.\n");
				exit(1);
			}
			if (class->class_file.constant_pool[class->class_file.constant_pool[i].info.Fieldref.name_and_type_index].tag != CONSTANT_NameAndType) {
				printf("Erro: Indice do name_and_type_index apontado pela fieldref invalido.\n");
				exit(1);
			}
		}
		if (tag == CONSTANT_NameAndType) {
			if (class->class_file.constant_pool[class->class_file.constant_pool[i].info.Nameandtype.name_index].tag != CONSTANT_Utf8) {
				printf("Erro: Indice do name_index apontado pelo name_and_type invalido.\n");
				exit(1);
			}
			if (class->class_file.constant_pool[class->class_file.constant_pool[i].info.Nameandtype.descriptor_index].tag != CONSTANT_Utf8) {
				printf("Erro: Indice do descriptor_index apontado pela name_and_type invalido.\n");
				exit(1);
			}
		}
		if (tag == CONSTANT_Methodref) {
			if (class->class_file.constant_pool[class->class_file.constant_pool[i].info.Methodref.class_index].tag != CONSTANT_Class) {
				printf("Erro: Indice do class_index apontado pela methodref invalido.\n");
				exit(1);
			}
			if (class->class_file.constant_pool[class->class_file.constant_pool[i].info.Methodref.name_and_type_index].tag != CONSTANT_NameAndType) {
				printf("Erro: Indice do name_and_type_index apontado pela methodref invalido.\n");
				exit(1);
			}
		}
		if (tag == CONSTANT_InterfaceMethodref) {
			if (class->class_file.constant_pool[class->class_file.constant_pool[i].info.Interfacemethod.class_index].tag != CONSTANT_Class) {
				printf("Erro: Indice do class_index apontado pela interfacemethodref invalido.\n");
				exit(1);
			}
			if (class->class_file.constant_pool[class->class_file.constant_pool[i].info.Interfacemethod.name_and_type_index].tag != CONSTANT_NameAndType) {
				printf("Erro: Indice do name_and_type_index apontado pela interfacemethodref invalido.\n");
				exit(1);
			}
		}
		if (tag == CONSTANT_String) {
			if (class->class_file.constant_pool[class->class_file.constant_pool[i].info.String.string_index].tag != CONSTANT_Utf8) {
				printf("Erro: Indice apontado pela string invalido.\n");
				exit(1);		
			}
		}
	}
	//Verificar se classes Final nao estao sendo extendidas, ou Metodos Final estao sendo sobrescritos.
	if ((class->class_file.super_class >=  class->class_file.constant_pool_count) || (class->class_file.this_class < 0)) {
		printf("Erro: Indice da super classe eh maior ou menor que o tamanho da constante pool\n");
		exit(1);
	}
    class_t *super_class = getSuperClass(class);
    if (super_class != NULL && super_class->class_file.access_flags == ACC_FINAL) {
		printf("Erro: Class Final possui uma subclasse.\n");
		exit(1);
    }
	if (class->class_file.this_class >=  class->class_file.constant_pool_count) {
		printf("Erro: Índice da classe é maior que o tamanho da constante pool\n");
		exit(1);
	}
	
	//Verificar se toda classe (Menos Object) tem superclass.
	if (class->class_file.super_class == 0) {
		//Pego o nome em Utf8 da classe. Comparar se ela eh Object.
	    Utf8_info_t* object_class_name = string_to_utf8("java/lang/Object");
	    if (compare_utf8(class->class_name, object_class_name) != 0) {
	    	printf("Erro: Class nao possui super classe\n");
			exit(1);
	    }
	}
}
// VERIFICATION STUFF - END

/**
 * @brief Funcao que inincia o linker.
 *
 * @param Classe que sera linkada
 *
 */
void linkClass (class_t* class) {
    DEBUG_PRINT("Got in linkClass with arguments: %s\n", utf8_to_string(class->class_name));

	verificar(class);
	preparar(class);
	//resolver(class);
	
	class->status = CLASSE_NAO_INICIALIZADA; // Se nenhum erro ocorrer muda o estado da classe e retorna para a função.

	DEBUG_PRINT("Done linkClass\n");
}
/** @} */
