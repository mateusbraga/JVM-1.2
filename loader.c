#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"
#include "structs.h"
#include "jvm.h"

#define MAX_TAM 65535

/** \addtogroup Loader
 * @{
 */


/**
 * @brief Lê um arquivo e monta a tabela de atributos.
 *
 * @param classe - Ponteiro para uma classe
 * @param fp - Ponteiro para um arquivo .class de onde as informações serão lidas
 * @param attributesCount - Quantidade de elementos na tabela de atributos
 * @return ponteiro para a tabela de atributos
 */
attribute_info_t* GetAtributos(class_file_t* classe, FILE *fp, u2 attributesCount){
    attribute_info_t *atributos;
    Utf8_info_t* nome;
    u4 i, j;
    atributos = (attribute_info_t*)calloc(attributesCount, sizeof(attribute_info_t));

    for( i = 0; i < attributesCount ; i++){
        atributos[i].attribute_name_index = readu2(fp);
        atributos[i].attribute_length = readu4(fp);
        nome = &(classe->constant_pool[atributos[i].attribute_name_index].info.Utf8);
        /*printf("Nome do atributo: %s\n", utf8_to_string(nome));*/
        if(compare_utf8(nome, string_to_utf8("ConstantValue")) == 0) {
            atributos[i].info.constant_value.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.constant_value.attribute_length = atributos[i].attribute_length;
            atributos[i].info.constant_value.constantvalue_index = readu2(fp);
        } else if(compare_utf8(nome, string_to_utf8("Code")) == 0) {
            atributos[i].info.code.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.code.attribute_length = atributos[i].attribute_length;
            atributos[i].info.code.max_stack = readu2(fp);
            atributos[i].info.code.max_locals = readu2(fp);
            atributos[i].info.code.code_length = readu4(fp);
            atributos[i].info.code.code = (u1*)calloc(atributos[i].info.code.code_length, sizeof(u1));
            for(j=0; j < atributos[i].info.code.code_length; j++ ){
                atributos[i].info.code.code[j] = readu1(fp);
            }
            atributos[i].info.code.exception_table_length = readu2(fp);
            atributos[i].info.code.exception_table = (exception_table_t*)calloc(atributos[i].info.code.exception_table_length, sizeof(exception_table_t));
            for(j=0; j < atributos[i].info.code.exception_table_length; j++) {
                atributos[i].info.code.exception_table->start_pc = readu2(fp);
                atributos[i].info.code.exception_table->end_pc = readu2(fp);
                atributos[i].info.code.exception_table->handler_pc = readu2(fp);
                atributos[i].info.code.exception_table->catch_type = readu2(fp);
            }
            atributos[i].info.code.attributes_count = readu2(fp);
            atributos[i].info.code.attributes = GetAtributos(classe, fp,atributos[i].info.code.attributes_count);
        } else if(compare_utf8(nome, string_to_utf8("Exceptions")) == 0) {
            atributos[i].info.exception.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.exception.attribute_length = atributos[i].attribute_length;
            atributos[i].info.exception.number_of_exceptions = readu2(fp);
            atributos[i].info.exception.exception_index_table = (u2*)calloc(sizeof(u2*),atributos[i].info.exception.number_of_exceptions );
            for(j=0;j<atributos[i].info.exception.number_of_exceptions; j++){
                atributos[i].info.exception.exception_index_table[j] = readu2(fp);
            }
        } else if(compare_utf8(nome, string_to_utf8("InnerClasses")) == 0) {
            atributos[i].info. innerclasses.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.innerclasses.attribute_length = atributos[i].attribute_length;
            atributos[i].info. innerclasses.number_of_classes = readu2(fp);
            atributos[i].info. innerclasses.classes = (inner_class_t*)calloc(sizeof(inner_class_t*),atributos[i].info.innerclasses.number_of_classes);
            for(j=0; j< atributos[i].info. innerclasses.number_of_classes; j++) {
                atributos[i].info.innerclasses.classes[j].inner_class_info_index = readu2(fp);
                atributos[i].info.innerclasses.classes[j].outer_class_info_index = readu2(fp);
                atributos[i].info.innerclasses.classes[j].inner_name_index = readu2(fp);
                atributos[i].info.innerclasses.classes[j].inner_class_access_flags = readu2(fp);

            }
        }else if(compare_utf8(nome, string_to_utf8("Synthetic")) == 0) {
            atributos[i].info.synthetic.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.synthetic.attribute_length = atributos[i].attribute_length;
        }else if(compare_utf8(nome, string_to_utf8("SourceFile")) == 0) {
            atributos[i].info.sourcefile.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.sourcefile.attribute_length = atributos[i].attribute_length;
            atributos[i].info.sourcefile.sourcefile_index = readu2(fp);
        }else if(compare_utf8(nome, string_to_utf8("LineNumberTable")) == 0) {
            atributos[i].info.line_number_table.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.line_number_table.attribute_length = atributos[i].attribute_length;
            atributos[i].info.line_number_table.line_number_table_length = readu2(fp);
            atributos[i].info.line_number_table.line_number_table = (line_number_table_t*)calloc(sizeof(line_number_table_t*),atributos[i].info.line_number_table.line_number_table_length);
            for(j=0; j < atributos[i].info.line_number_table.line_number_table_length; j++) {
                atributos[i].info.line_number_table.line_number_table[j].start_pc = readu2(fp);
                atributos[i].info.line_number_table.line_number_table[j].line_number = readu2(fp);
            }
        }else if(compare_utf8(nome, string_to_utf8("LocalVariableTable")) == 0) {
            atributos[i].info.local_variable_table.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.local_variable_table.attribute_length = atributos[i].attribute_length;
            atributos[i].info.local_variable_table.local_variable_table_length = readu2(fp);
            atributos[i].info.local_variable_table.local_variable_table = (local_variable_table_t*)calloc(sizeof(local_variable_table_t*),atributos[i].info.local_variable_table.local_variable_table_length);
            for(j=0; j < atributos[i].info.local_variable_table.local_variable_table_length; j++) {
                atributos[i].info.local_variable_table.local_variable_table[j].start_pc = readu2(fp);
                atributos[i].info.local_variable_table.local_variable_table[j].length = readu2(fp);
                atributos[i].info.local_variable_table.local_variable_table[j].name_index = readu2(fp);
                atributos[i].info.local_variable_table.local_variable_table[j].descriptor_index = readu2(fp);
                atributos[i].info.local_variable_table.local_variable_table[j].index = readu2(fp);
            }

        }else if(compare_utf8(nome, string_to_utf8("Deprecated")) == 0) {
            atributos[i].info.deprecated.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.deprecated.attribute_length = atributos[i].attribute_length;
        }else if(compare_utf8(nome, string_to_utf8("Signature")) == 0) {
            atributos[i].info.signature.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.signature.attribute_length = atributos[i].attribute_length;
            atributos[i].info.signature.signature_index = readu2(fp);
        }else {
            printf("GetAttributos ignorou attributo: %s\n", utf8_to_string(nome));
        }

    }
    return atributos;
}
/*-----------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Lê a tabela de atributos e imprime ela na tela.
 *
 * @param classe - ponteiro para a classe
 * @param atributos - ponteiro para a tabela de atributos
 * @param qtd - quantidade de elementos da tabela
 * @return não retorna nada
 */
void ImprimeAtributos(class_file_t* classe, attribute_info_t * atributos, u2 qtd){
    Utf8_info_t* nome;
    u4 i, j;
    for( i = 0; i < qtd ; i++){
        printf("\nAttribute %d\n", i);
        printf("Attribute name index: cp_info #%hi <%s>\n", atributos[i].attribute_name_index, utf8_to_string(&(classe->constant_pool[atributos[i].attribute_name_index].info.Utf8)));
        printf("Attribute length: %i\n", atributos[i].attribute_length);
        nome = &(classe->constant_pool[atributos[i].attribute_name_index].info.Utf8);
        if(compare_utf8(nome, string_to_utf8("ConstantValue")) == 0) {
            printf("Constant Value Index: cp_info #%hi\n", atributos[i].info.constant_value.constantvalue_index);
            printf("\n");
        }else if(compare_utf8(nome, string_to_utf8("Code")) == 0) {
            printf("Maximum stack depth: %hi\n",atributos[i].info.code.max_stack);
            printf("Maximum local variables: %hi\n",atributos[i].info.code.max_locals);
            printf("Code length: %i\n",atributos[i].info.code.code_length);
            printf("...\n");
            for(j=0; j < atributos[i].info.code.code_length; j++ ){
                getNumberOfOpcodeOperandsInBytes(atributos[i].info.code[j]);
                printf("%c",atributos[i].info.code[j]);
            }
            printf("Excepion table length: %hi\n",atributos[i].info.code.exception_table_length);
            for(j=0; j < atributos[i].info.code.exception_table_length; j++) {
                printf("start_pc: %hi\n", atributos[i].info.code.exception_table->start_pc);
                printf("end_pc: %hi\n", atributos[i].info.code.exception_table->end_pc);
                printf("handler_pc: %hi\n",atributos[i].info.code.exception_table->handler_pc);
                printf("catch_pc: %hi\n",atributos[i].info.code.exception_table->catch_type);
            }
            printf("Nr attributes: %hi\n",atributos[i].info.code.attributes_count);
            ImprimeAtributos(classe,atributos[i].info.code.attributes, atributos[i].info.code.attributes_count);
            printf("\n");
        } else if(compare_utf8(nome, string_to_utf8("Exceptions")) == 0) {
            printf("catch_pc: %hi\n",atributos[i].info.exception.number_of_exceptions);
            for(j=0; j<atributos[i].info.exception.number_of_exceptions; j++){
                printf("Exception index table %d: %i\n",atributos[i].info.exception.exception_index_table[j],j);
            }
            printf("\n");
        } else {
            printf("...\n");
        }
    }
}

/*-----------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Lê um arquivo e monta a tabela de métodos.
 *
 * @param classe - Ponteiro para uma classe
 * @param fp - Ponteiro para um arquivo .class de onde as informações serão lidas
 * @param methodsCount - Quantidade de elementos na tabela de métodos
 * @return ponteiro para a tabela de métodos
 */

method_info_t* GetMetodo(class_file_t* classe,  FILE *fp, u2 methodsCount){
    method_info_t *metodos;
    u2 i;

    metodos = (method_info_t*)calloc(methodsCount, sizeof(method_info_t));
    for( i=0 ; i<methodsCount ; i++ ){
        metodos[i].access_flags = readu2(fp);
        metodos[i].name_index = readu2(fp);
        metodos[i].descriptor_index = readu2(fp);
        metodos[i].attributes_count = readu2(fp);
        metodos[i].attributes = GetAtributos(classe, fp, metodos[i].attributes_count);
    }

    return metodos;
}
/*-----------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Lê a tabela de métodos e imprime ela na tela.
 *
 * @param metodos - ponteiro para a tabela de métodos
 * @param qtd - quantidade de elementos da tabela
 * @return não retorna nada
 */
void ImprimeMetodos(class_file_t* classe){
    u2 qtd;
    method_info_t* metodos;
    metodos = classe->methods;
    register u2 i;
    qtd = classe->methods_count;
    for(i=0 ; i<qtd ; i++ ){
        printf("----------\nMethod %d\n", i);
        printf("    Acess flags: %#x\n",metodos[i].access_flags);
        printf("    Name index:  %hi <%s>\n",metodos[i].name_index, utf8_to_string(&(classe->constant_pool[metodos[i].name_index].info.Utf8)));
        printf("    Descriptor: %hi <%s>\n",metodos[i].descriptor_index, utf8_to_string(&(classe->constant_pool[metodos[i].descriptor_index].info.Utf8)));
        printf("    Attributes count: %hi\n",metodos[i].attributes_count);
        ImprimeAtributos(classe,metodos[i].attributes,metodos[i].attributes_count);
    }
}

/*-----------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Lê um arquivo e monta a tabela de campos.
 *
 * @param classe - Ponteiro para uma classe
 * @param fp - Ponteiro para um arquivo .classe de onde as informações serão lidas
 * @param fieldCount - Quantidade de elementos na tabela de campos
 * @return ponteiro para a tabela de campos
 */

field_info_t* GetFields(class_file_t* classe, FILE *fp, u2 fieldCount){
    field_info_t *fields;
    u2 j;
    fields = (field_info_t*)calloc(fieldCount, sizeof(field_info_t));

    for( j = 0; j < fieldCount ; j++){
        fields[j].access_flags = readu2(fp);
        fields[j].name_index = readu2(fp);
        fields[j].descriptor_index = readu2(fp);
        fields[j].attributes_count = readu2(fp);
        fields[j].attributes = GetAtributos(classe, fp, fields[j].attributes_count);
    }

    return fields;
}

/**
 * @brief Lê a tabela de campos e imprime ela na tela.
 *
 * @param fields - ponteiro para a tabela de campos
 * @param qtd - quantidade de elementos da tabela
 * @return não retorna nada
 */
void ImprimeFields(class_file_t* classe){
    u2 qtd;
    field_info_t* fields;
    fields = classe->fields;
    register u2 j;

    qtd = classe->fields_count;
    for(j = 0; j < qtd ; j++){
        printf("---------\nField %d\n", j);
        printf("    Access flags: %#x\n",fields[j].access_flags);
        printf("    Name index: %hi <%s>\n",fields[j].name_index, utf8_to_string(&(classe->constant_pool[fields[j].name_index].info.Utf8)));
        printf("    Descriptor: %hi <%s>\n", fields[j].descriptor_index, utf8_to_string(&(classe->constant_pool[fields[j].descriptor_index].info.Utf8)));
        printf("    Attributes count: %hi\n",fields[j].attributes_count);
        ImprimeAtributos(classe,fields[j].attributes,fields[j].attributes_count);
    }
}


/*-----------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Lê um arquivo e monta a tabela de constantes a partir dele.
 *
 * @param fp - Um ponteiro para o arquivo .class de onde sera lido
 * @param constantCount - um inteiro que indica a quantidade de elementos da tabela
 * @return ponteiro para a tabela de constantes
 */

cp_info_t* GetConstantes(FILE *fp, u2 constantCount){
    cp_info_t *constantes;
    u2 i, j;

    constantes = (cp_info_t*)calloc(constantCount, sizeof(cp_info_t));
    for(i=1;i<constantCount;i++){
        constantes[i].tag = readu1(fp);
        switch(constantes[i].tag){
            case CONSTANT_Class:
                constantes[i].info.Class.name_index = readu2(fp);
                break;
            case CONSTANT_Fieldref :
                constantes[i].info.Fieldref.class_index = readu2(fp);
                constantes[i].info.Fieldref.name_and_type_index = readu2(fp);
                break;
            case CONSTANT_Methodref :
                constantes[i].info.Methodref.class_index = readu2(fp);
                constantes[i].info.Methodref.name_and_type_index = readu2(fp);
                break;
            case CONSTANT_InterfaceMethodref :
                constantes[i].info.Interfacemethod.class_index = readu2(fp);
                constantes[i].info.Interfacemethod.name_and_type_index = readu2(fp);
                break;
            case CONSTANT_NameAndType :
                constantes[i].info.Nameandtype.name_index = readu2(fp);
                constantes[i].info.Nameandtype.descriptor_index = readu2(fp);
                break;
            case CONSTANT_Utf8    :
                constantes[i].info.Utf8.length = readu2(fp);
                constantes[i].info.Utf8.bytes = (u1*)calloc(constantes[i].info.Utf8.length, sizeof(u1));
                for(j = 0; j < constantes[i].info.Utf8.length; j++){
                    constantes[i].info.Utf8.bytes[j] = readu1(fp);
                }
                break;
            case CONSTANT_String:
                constantes[i].info.String.string_index = readu2(fp);
                break;
            case CONSTANT_Integer :
                constantes[i].info.Integer.bytes = readu4(fp);
                break;

            case CONSTANT_Float :
                constantes[i].info.Float.bytes = readu4(fp);
                break;
            case CONSTANT_Long  :
                constantes[i].info.Long.high_bytes = readu4(fp);
                constantes[i].info.Long.low_bytes = readu4(fp);
                ++i;
                break;
            case CONSTANT_Double :
                constantes[i].info.Double.high_bytes = readu4(fp);
                constantes[i].info.Double.low_bytes = readu4(fp);
                ++i;
                break;
            default :
                printf("\n Erro! Problemas na leitura do constant pool \n");
                break;
        }
    }
    return constantes;
}
/*-----------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Lê a tabela de constantes e mostra de acordo com a especificacão e baseado no programa jclasslib.
 *
 * @param constantes - Um ponteiro para a tabela de constantes
 * @param qtd - Quantidade de elementos desta tabela
 * @return não retorna nada
 */
void ImprimeConstantes(cp_info_t *constantes, u2 qtd){
    u2 i;
    u2 index;
    u2 index2;
    u2 index3;


    for(i=1;i<qtd;i++){
        switch(constantes[i].tag){
            case CONSTANT_Class:
                printf("tag: %u (CONSTANT_Class)\n", constantes[i].tag);
                index = constantes[i].info.Class.name_index;
                printf("name_index: %u <%s>\n", index, utf8_to_string(&(constantes[index].info.Utf8)));
                printf("\n");
                break;
            case CONSTANT_Fieldref:
                printf("tag: %u (CONSTANT_Fieldref)\n", constantes[i].tag);
                index = constantes[i].info.Fieldref.class_index;
                index2 = constantes[index].info.Class.name_index;
                printf("class_index: %u <%s>\n", index, utf8_to_string(&(constantes[index2].info.Utf8)));

                index = constantes[i].info.Fieldref.name_and_type_index;
                index2 = constantes[index].info.Nameandtype.name_index;
                index3 = constantes[index].info.Nameandtype.descriptor_index;
                printf("name_and_type_index: %u <%s - %s>\n", index, utf8_to_string(&(constantes[index2].info.Utf8)), utf8_to_string(&(constantes[index3].info.Utf8)));
                printf("\n");
                break;
            case CONSTANT_NameAndType:
                printf("tag: %u (CONSTANT_NameAndType)\n", constantes[i].tag);
                index = constantes[i].info.Nameandtype.name_index;
                printf("nameIndex: %u <%s>\n", index, utf8_to_string(&(constantes[index].info.Utf8)));
                index = constantes[i].info.Nameandtype.descriptor_index;
                printf("descriptorIndex: %u <%s>\n", index, utf8_to_string(&(constantes[index].info.Utf8)));
                printf("\n");
                break;
            case CONSTANT_Utf8:
                printf("tag: %u (CONSTANT_Utf8)\n", constantes[i].tag);
                printf("length: %u\n", constantes[i].info.Utf8.length);
                printf("string: %s\n", constantes[i].info.Utf8.bytes);
                printf("\n");
                break;
            case CONSTANT_Methodref:
                printf("tag: %u (CONSTANT_Methodref)\n", constantes[i].tag);
                index = constantes[i].info.Methodref.class_index;
                index2 = constantes[index].info.Class.name_index;
                printf("class_index: %u <%s>\n", index,utf8_to_string(&(constantes[index2].info.Utf8)));
                index = constantes[i].info.Methodref.name_and_type_index;
                index2 = constantes[index].info.Nameandtype.name_index;
                index3 = constantes[index].info.Nameandtype.descriptor_index;
                printf("name_and_type_index: %u <%s - %s>\n", index, utf8_to_string(&(constantes[index2].info.Utf8)) , utf8_to_string(&(constantes[index3].info.Utf8)));
                printf("\n");
                break;
            case CONSTANT_Double:
                printf("tag: %u (CONSTANT_Double)\n", constantes[i].tag);
                printf("high_bytes : %x\n", constantes[i].info.Double.high_bytes);
                printf("low_bytes : %x\n", constantes[i].info.Double.low_bytes);
                getchar();
                printf("\n");
                ++i;
                break;
            case CONSTANT_Long:
                printf("tag: %u (CONSTANT_Long)\n", constantes[i].tag);
                printf("high_bytes : %u\n", constantes[i].info.Long.high_bytes);
                printf("low_bytes : %u\n", constantes[i].info.Long.low_bytes );
                printf("\n");
                ++i;
                break;
            case CONSTANT_Float:
                printf("tag: %u (CONSTANT_Float)\n", constantes[i].tag);
                printf("bytes : %u \n", constantes[i].info.Float.bytes 	);
                printf("\n");
                break;
            case CONSTANT_Integer:
                printf("tag: %u (CONSTANT_Integer)\n", constantes[i].tag);
                printf("bytes : %u\n", constantes[i].info.Integer.bytes);
                printf("\n");
                break;
            case CONSTANT_String:
                printf("tag: %u (CONSTANT_String)\n", constantes[i].tag);
                index = constantes[i].info.String.string_index;
                printf("string_index: %u <%s>\n", index, utf8_to_string(&(constantes[index].info.Utf8)));
                printf("\n");
                break;
            case CONSTANT_InterfaceMethodref:
                printf("tag: %u (CONSTANT_InterfaceMethodref)\n", constantes[i].tag);
                index = constantes[i].info.Interfacemethod.class_index;
                index2 = constantes[index].info.Class.name_index;
                printf("class_index: %u <%s>\n", index, utf8_to_string(&(constantes[index2].info.Utf8)));

                index = constantes[i].info.Interfacemethod.name_and_type_index;
                index2 = constantes[index].info.Nameandtype.name_index;
                index3 = constantes[index].info.Nameandtype.descriptor_index;
                printf("name_and_type_index: %u <%s-%s>\n", index, utf8_to_string(&(constantes[index2].info.Utf8)) , utf8_to_string(&(constantes[index3].info.Utf8)));
                printf("\n");
                break;
        }
    }
}

/*-----------------------------------------------------------------------------------------------------------------*/
/**
 * @brief A partir do nome no argumento a função lê um arquivo e monta a classe a partir dele.
 *
 * @param class - estrutura de uma classe
 * @return nada
 */
void set_class_file(class_t* class){
    u2 i;
    FILE *fp;
    class_file_t *classe;
    char* filename = NULL;

    filename = (char*) malloc(sizeof(char) * class->class_name->length + 6 + 1);
    strncpy(filename, (char*) class->class_name->bytes, class->class_name->length);
    filename[class->class_name->length] = '.';
    filename[class->class_name->length + 1] = 'c';
    filename[class->class_name->length + 2] = 'l';
    filename[class->class_name->length + 3] = 'a';
    filename[class->class_name->length + 4] = 's';
    filename[class->class_name->length + 5] = 's';
    filename[class->class_name->length + 6] = '\0';

    if( (fp = fopen(filename, "rb")) == NULL){
        printf("Erro! Nao foi possivel abrir o arquivo %s!\n", filename);
        exit(1);
    }

    classe = &(class->class_file);
    classe->magic = readu4(fp);

    if ( classe->magic != 0xcafebabe){
        printf("Erro! Assinatura nao identificada ( CAFEBABE )\n %x\n", classe->magic);
        exit(1);
    }
    /*Checar versão correta, se não for apresentar erro. Versão correta: Entre 45.0 e 46.0 */
    classe->minor_version = readu2(fp);
    classe->major_version = readu2(fp);
    if((classe->major_version < 45) || (classe->major_version > 46)){
        printf("Erro! Problema na versao da classe\n %x.%x\n", classe->major_version, classe->minor_version);
        exit(1);
    }
    else {
        if (classe->major_version == 46) {
            if(classe->minor_version != 0) {
                printf("Erro! Problema na versao da classe\n %x.%x\n", classe->major_version, classe->minor_version);
                exit(1);
            }
        }
    }
    classe->constant_pool_count = readu2(fp);
    classe->constant_pool = GetConstantes(fp, classe->constant_pool_count);
    classe->access_flags = readu2(fp);
    classe->this_class  = readu2(fp);
    classe->super_class = readu2(fp);
    classe->interfaces_count = readu2(fp);
    classe->interfaces = (u2*)calloc(classe->interfaces_count, sizeof(u2));

    for (i = 0; i< classe->interfaces_count; i++ ){
        ((u2*)classe->interfaces)[i] = readu2(fp);
    }

    classe->fields_count = readu2(fp);
    classe->fields = GetFields(classe, fp, classe->fields_count);
    classe->methods_count = readu2(fp);
    classe->methods = GetMetodo(classe, fp, classe->methods_count);
    classe->attributes_count = readu2(fp);
    classe->attributes = GetAtributos(classe, fp , classe->attributes_count);


}

/*-----------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Lê a classe passada (que foi montada a partir da função "void set_class_file" e imprime a sua estrutura na tela.
 *
 * @param classe - Ponteiro para a classe que será mostrada
 * @return não retorna nada
*/
void MostraClasse(class_file_t* classe){
    register u2 i;

    u2 index;

    index = classe->constant_pool[classe->this_class].info.Class.name_index;
    printf("------------\nClasse %s:\n", utf8_to_string(&(classe->constant_pool[index].info.Utf8)));
    printf("Magic: %#x\n", classe->magic);
    printf("minor_version: %hi\n", classe->minor_version);
    printf("major_version: %hi\n", classe->major_version);
    printf("constant_pool_count: %hi\n", classe->constant_pool_count);
    printf("acess_flags: %#x\n", classe->access_flags);

    index = classe->constant_pool[classe->this_class].info.Class.name_index;
    printf("this_class: cp_info #%hi <%s>\n", classe->this_class, utf8_to_string(&(classe->constant_pool[index].info.Utf8)));

    index = classe->constant_pool[classe->super_class].info.Class.name_index;
    printf("super_class: cp_info #%hi <%s>\n", classe->super_class, utf8_to_string(&(classe->constant_pool[index].info.Utf8)));
    printf("interfaces_count: %hi\n", classe->interfaces_count);
    printf("fields_count: %hi\n",classe->fields_count);
    printf("methods_count: %hi\n",classe->methods_count);
    printf("attributes_count: %hi\n",classe->attributes_count);

    for (i = 0; i< classe->interfaces_count; i++ ){
        printf("     interface.%d: %hi\n",i, classe->interfaces[i]);
    }

    printf("\n----Constant Pool----\n");
    ImprimeConstantes(classe->constant_pool, classe->constant_pool_count);
    printf("\n----Fields----\n");
    ImprimeFields(classe);
    printf("\n----Methods----\n");
    ImprimeMetodos(classe);
    printf("\n----Atributos----\n");
    ImprimeAtributos(classe, classe->attributes, classe->attributes_count);
}

/*-----------------------------------------------------------------------------------------------------------------*/
void loadClass(class_t* class){
    u2 index_class;
    char *nome_classe, *nome_lido, *pch, nome_aux[MAX_TAM];
    DEBUG_PRINT("Got in loadClass with arguments: %s\n", utf8_to_string(class->class_name));
    set_class_file(class);

    index_class = class->class_file.constant_pool[class->class_file.this_class].info.Class.name_index;
    nome_classe = utf8_to_string(class->class_name);
    nome_lido = utf8_to_string(&(class->class_file.constant_pool[index_class].info.Utf8));
    pch = strtok (nome_classe,"/");
    while (pch != NULL) {
        strcpy(nome_aux, pch);
        pch = strtok (NULL, "/");
    }

    if (strcmp(nome_aux, nome_lido) != 0) {
        printf("Erro! Nome lido da classe e nome recebido da classe diferentes. \nnome classe = %s\nnome lido = %s\n", nome_aux, nome_lido);
        exit(1);
    }
    class->status = CLASSE_NAO_LINKADA;
    DEBUG_PRINT("Done loadClass\n");
}
/** @} */
