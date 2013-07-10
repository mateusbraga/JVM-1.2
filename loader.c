#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"
#include "structs.h"
#include "jvm.h"

attribute_info_t* GetAtributos(class_file_t* classe, FILE *fp, u2 attributesCount){
    attribute_info_t *atributos;
    Utf8_info_t* nome;
    u4 i, j;
    atributos = (attribute_info_t*)calloc(attributesCount, sizeof(attribute_info_t));

    for( i = 0; i < attributesCount ; i++){
        atributos[i].attribute_name_index = readu2(fp);
        atributos[i].attribute_length = readu4(fp);
        nome = &(classe->constant_pool[atributos[i].attribute_name_index].info.Utf8);
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
            /*atributos[i].info.code.attributes = GetAtributos(classe, fp,atributos[i].info.code.attributes_count);*/
        } else if(compare_utf8(nome, string_to_utf8("Exceptions")) == 0) {
            atributos[i].info.exception.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.exception.attribute_length = atributos[i].attribute_length;
            atributos[i].info.exception.number_of_exceptions = readu2(fp);
            atributos[i].info.exception.exception_index_table = (u2*)calloc(sizeof(u2*),atributos[i].info.exception.number_of_exceptions );
            for(j=0;j<atributos[i].info.exception.number_of_exceptions; j++){
                atributos[i].info.exception.exception_index_table[j] = readu2(fp);
            }
        } else {
            printf("GetAttributos ignorou attributo\n");
            /*atributos[i].info = (u1*)calloc(sizeof(u1), atributos[i].attribute_length);*/
            /*for(j = 0; j < atributos[i].attribute_length; j++){*/
                /*((u1*)(atributos[i].info))[j] = readu1(fp);                      */
            /*}*/
        }

    }
    return atributos;
}

/*-----------------------------------------------------------------------------------------------------------------*/

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

/*-----------------------------------------------------------------------------------------------------------------*/

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
        printf("Erro! Nao foi possivel abrir o arquivo!\n");
        exit(1);
    }

    classe = &(class->class_file);
    classe->magic = readu4(fp);

    if ( classe->magic != 0xcafebabe){
        printf("Erro! Assinatura nao identificada ( CAFEBABE )\n %x\n", classe->magic);
        exit(1);
    }
    /*Checar versão correta, se não for apresentar erro */
    classe->minor_version = readu2(fp);
    classe->major_version = readu2(fp);
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

void loadClass(class_t* class){
    set_class_file(class);
    class->status = CLASSE_NAO_LINKADA;
}


