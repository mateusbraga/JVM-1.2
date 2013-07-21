#include <stdio.h>
#include <stdlib.h>

#include "jvm.h"
#include "opcode.h"
#include "initializer.h"
#include "loader.h"
#include "linker.h"

extern pc_t jvm_pc;
extern void (*jvm_opcode[])(void);

/** \addtogroup Inicializar
 * @{
 */

/**
 * @brief Funcao que inincializa o metodo clinit.
 *
 * @param Classe que sera inicializada.
 *
 */
void initializeClass(class_t* class) {
    DEBUG_PRINT("Got in initializeClass with arguments: %s\n", utf8_to_string(class->class_name));

	if (class->status == CLASSE_NAO_CARREGADA) {
        loadClass(class);
    }
    if (class->status == CLASSE_NAO_LINKADA) {
        linkClass(class);
    }

	Utf8_info_t* name_clinit_utf8 = string_to_utf8("<clinit>");
	Utf8_info_t* method_name;
	u2 i;
	for (i = 0; i < class->class_file.methods_count; i++) {
		method_name = &(class->class_file.constant_pool[class->class_file.methods[i].name_index].info.Utf8); // Verifica se o metodo eh o <clinit>, se for executa ele.
		if (compare_utf8(name_clinit_utf8, method_name) == 0) {

			callMethod(class, &(class->class_file.methods[i]));
			jvm_pc.jumped = 0;

            code_attribute_t* code_attribute = NULL;
            while(1) {
                //fetch opcode
                code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
                u1 opcode = code_attribute->code[jvm_pc.code_pc];

                //execute the action for the opcode;
                DEBUG_PRINT("Going to execute %#x at %d (clinit)\n", opcode, jvm_pc.code_pc);
                jvm_opcode[opcode]();
                if (opcode == 0xb1) { // it's a return
                    break;
                }

                code_attribute = getCodeAttribute(jvm_pc.currentClass, jvm_pc.method);
                goToNextOpcode();
            }

			break;
		}
	}

	class->status = CLASSE_PRONTA;

	DEBUG_PRINT("Done initializeClass\n");
}
/** @} */
