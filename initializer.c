#include <stdio.h>
#include <stdlib.h>

#include "initializer.h"
#include "loader.h"
#include "linker.h"

/**
 * @brief Funcao que inincializa o metodo clinit.
 *
 * @param Classe que sera inicializada.
 *
 */
void initializeClass(class_t* class) {
	if (class->status == CLASSE_NAO_CARREGADA) {
        loadClass(class);
    }
    if (class->status == CLASSE_NAO_INICIALIZADA) {
        linkClass(class);
    }
	u2 i;
	Utf8_info_t* name_clinit_utf8;
	Utf8_info_t* name_method_utf8;
	name_clinit_utf8 = string_to_utf8("<clinit>");
	for (i = 1; i < class->class_file.methods_count; i++) {
		name_method_utf8 = &(class->class_file.constant_pool[class->class_file.methods[i].name_index].info.Utf8); // Verifica se o metodo eh o <clinit>, se for executa ele.
		if (compare_utf8(name_clinit_utf8, name_method_utf8) == 0) {
			callMethod(class, &(class->class_file.methods[i]));
		}
	}
	class->status = CLASSE_PRONTA;
}
