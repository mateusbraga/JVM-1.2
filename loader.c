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
        printf("Nome do atributo: %s\n", utf8_to_string(nome));
        if(compare_utf8(nome, string_to_utf8("ConstantValue")) == 0) {
            atributos[i].info.constant_value.attribute_name_index = atributos[i].attribute_name_index;
            atributos[i].info.constant_value.attribute_length = atributos[i].attribute_length;
            atributos[i].info.constant_value.constantvalue_index = readu2(fp);
        } else if(compare_utf8(nome, string_to_utf8("Code")) == 0) {
            printf("Nome do atributo: %s\n", utf8_to_string(nome));

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
        } else {
           printf("GetAttributos ignorou attributo: %s\n", utf8_to_string(nome));
        }

    }
    return atributos;
}
/*-----------------------------------------------------------------------------------------------------------------*/
void ImprimeAtributos(class_file_t* classe, attribute_info_t * atributos, u2 qtd){    
    Utf8_info_t* nome;
    u4 i, j;
    for( i = 0; i < qtd ; i++){
        printf("\nAttribute %d\n", i);
        printf("Attribute name index: cp_info #%hi <%s>\n", atributos[i].attribute_name_index, (char*)(&(classe->constant_pool[atributos[i].attribute_name_index].info.Utf8)));
        printf("Attribute length: %i\n", atributos[i].attribute_length);
        nome = &(classe->constant_pool[atributos[i].attribute_name_index].info.Utf8);
        if(compare_utf8(nome, string_to_utf8("ConstantValue")) == 0) {
			 printf("Constant Value Index: cp_info #%hi\n", atributos[i].info.constant_value.constantvalue_index);
             printf("\n");
		}else if(compare_utf8(nome, string_to_utf8("Code")) == 0) {
			 printf("Maximum stack depth: %hi\n",atributos[i].info.code.max_stack);
             printf("Maximum local variables: %hi\n",atributos[i].info.code.max_locals);
             printf("Code length: %i\n",atributos[i].info.code.code_length);
             for(j=0; j < atributos[i].info.code.code_length; j++ ){
                                //printf("%c",atributos[i].info.code[j]);  
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
                                printf("Exception index table %d: %hi\n",atributos[i].info.exception.exception_index_table[j],j);
                        }
            printf("\n");
              } else {
            printf("Attribute length: %i\n",atributos[i].attribute_length);
                        for(j = 0; j < atributos[i].attribute_length; j++){
                                //printf("%c",((u1*)(atributos[i].info))[j]);                  
            }

    }
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
        Utf8_info_t* method_name = &(classe->constant_pool[metodos[i].name_index].info.Utf8);
        printf("Method %s - %d atributos\n", utf8_to_string(method_name), metodos[i].attributes_count);
        metodos[i].attributes = GetAtributos(classe, fp, metodos[i].attributes_count);
        printf("Done2\n");
    }

    return metodos;
}
/*-----------------------------------------------------------------------------------------------------------------*/

void ImprimeMetodos(class_file_t* classe){
    u2 qtd;
    method_info_t* metodos;
    metodos = classe->methods;
    register u2 i;
    qtd = classe->methods_count;
        for(i=0 ; i<qtd ; i++ ){
        printf("\nMethod %d\n", i);
                printf("    Acess flags: %hi\n",metodos[i].access_flags);
                printf("    Name index:  %hi <%s>\n",metodos[i].name_index, (char*)(&(classe->constant_pool[metodos[i].name_index].info.Utf8)));
                printf("    Descriptor: %hi\n",metodos[i].descriptor_index);
                printf("    Attributes count: %hi\n",metodos[i].attributes_count);
                ImprimeAtributos(classe,metodos[i].attributes,metodos[i].attributes_count);
        }
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
/*------------------------------------------------------------------------------------------------------------------*/
void ImprimeFields(class_file_t* classe){
    u2 qtd;
    field_info_t* fields;
    fields = classe->fields;
    register u2 j;
   
    qtd = classe->fields_count;
    for(j = 0; j < qtd ; j++){
        printf("\nField %d\n", j);
                printf("    Access flags: %hi\n",fields[j].access_flags);
                printf("    Name index: %hi <%s>\n",fields[j].name_index, (char*)(&(classe->constant_pool[fields[j].name_index].info.Utf8)));
                printf("    Descriptor: %hi\n",fields[j].descriptor_index);
                printf("    Attributes count: %hi\n",fields[j].attributes_count);
                ImprimeAtributos(classe,fields[j].attributes,fields[j].attributes_count);
    }
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
void ImprimeConstantes(cp_info_t *constantes, u2 qtd){
	/*Fieldref_t* fieldrefAux;
	Class_t* classAux;
	Nameandtype_t* nameAndTypeAux;
	Methodref_t* methodrefAux;
	String_t* stringAux;
	Interfacemethod_t* interfaceMethodrefAux;*/
	
    u2 i, j;  
    
    
     for(i=1;i<qtd;i++){
                switch(constantes[i].tag){
					 case 7:
                                printf("tag: %u (CONSTANT_Class)\n", constantes[i].tag);
                                printf("name_index: %u <%s>\n", constantes[i].info.Class.name_index, &(constantes[Class.name_index].info.Utf8));
                                printf("\n");
                                break;
                     case 9:
                                printf("tag: %u (CONSTANT_Fieldref)\n", constantes[i].tag);                    
                                printf("class_index: %u <%s>\n", constantes[i].info.Fieldref.class_index, &(constantes[constantes[fieldrefAux.class_index].info.Class.name_index].info.Utf8));
                                printf("name_and_type_index: %u <%s%s>\n", constantes[i].info.Fieldref.name_and_type_index, &(constantes[constantes[fieldrefAux.name_and_type_index].info.Nameandtype.name_index].info.Utf8), &(constantes[constantes[fieldrefAux.name_and_type_index].info.Nameandtype.descriptor_index].info.Utf8));
                                printf("\n");
                                break;
                    case 12:
                                printf("tag: %u (CONSTANT_NameAndType)\n", constantes[i].tag);
                                printf("nameIndex: %u <%s>\n", constantes[i].info.Nameandtype.name_index, &(constantes[nameAndTypeAux.name_index].info.Utf8));
                                printf("descriptorIndex: %u <%s>\n", constantes[i].info.Nameandtype.descriptor_index, &(constantes[nameAndTypeAux.descriptor_index].info.Utf8));
                                printf("\n");
                                break;
                     case 1:
                                printf("tag: %u (CONSTANT_Utf8)\n", constantes[i].tag);
                                printf("length: %u\n", constantes[i].info.Utf8.length);
                                printf("string: %s\n", constantes[i].info.Utf8.bytes);
                                printf("\n");
                                break;
                    case 10:
                                printf("tag: %u (CONSTANT_Methodref)\n", constantes[i].tag);
                                printf("class_index: %u <%s>\n", constantes[i].info.Methodref.class_index,&(constantes[constantes[methodrefAux.class_index].info.Class.name_index].info.Utf8));
                                printf("name_and_type_index: %u <%s%s>\n", constantes[i].info.Methodref.name_and_type_index ,&(constantes[constantes[methodrefAux.name_and_type_index].info.Nameandtype.name_index].info.Utf8) , &(constantes[constantes[methodrefAux.name_and_type_index].info.Nameandtype.descriptor_index].info.Utf8));
                                printf("\n");
                                break;
                    case 6:
                                printf("tag: %u (CONSTANT_Double)\n", constantes[i].tag);
                                printf("high_bytes : %x\n", constantes[i].info.Double.high_bytes);
                                printf("low_bytes : %x\n", constantes[i].info.Double.low_bytes);
                                getchar();
                                printf("\n");
                                ++i;
                                break;
                    case 5:
                                printf("tag: %u (CONSTANT_Long)\n", constantes[i].tag);
                                printf("high_bytes : %u\n", constantes[i].info.Long.high_bytes);
                                printf("low_bytes : %u\n", constantes[i].info.Long.low_bytes );
                                printf("\n");
                                ++i;
                                break;
                    case 4:
                                printf("tag: %u (CONSTANT_Float)\n", constantes[i].tag);
                                printf("bytes : %u \n", constantes[i].info.Float.bytes 	);
                                printf("\n");
                                break;
                    case 3:
                                printf("tag: %u (CONSTANT_Integer)\n", constantes[i].tag);
                                printf("bytes : %u\n", constantes[i].info.Integer.bytes);
                                printf("\n");
                                break;
                    case 8:
                                printf("tag: %u (CONSTANT_String)\n", constantes[i].tag);
                                printf("string_index: %u <%s>\n", constantes[i].info.String.string_index, &(constantes[stringAux.string_index].info.Utf8));
                                printf("\n");
                                break;
                    case 11:
                                printf("tag: %u (CONSTANT_InterfaceMethodref)\n", constantes[i].tag);
                                printf("class_index: %u <%s>\n", constantes[i].info.Interfacemethod.class_index, &(constantes[constantes[methodrefAux.class_index].info.Class.name_index].info.Utf8));
                                printf("name_and_type_index: %u <%s%s>\n", constantes[i].info.Interfacemethod.name_and_type_index,&(constantes[constantes[interfaceMethodrefAux.name_and_type_index].info.Nameandtype.name_index].info.Utf8) , &(constantes[constantes[interfaceMethodrefAux.name_and_type_index].info.Nameandtype.descriptor_index].info.Utf8));
                                printf("\n");
                                break;
							}
				}
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
    printf("Done\n");
    classe->attributes_count = readu2(fp);
    classe->attributes = GetAtributos(classe, fp , classe->attributes_count);
}

/*-----------------------------------------------------------------------------------------------------------------*/

void MostraClasse(class_file_t* classe){
    register u2 i;
   
    printf("Magic: %x\n", classe->magic);
    printf("minor_version: %hi\n", classe->minor_version);
    printf("major_version: %hi\n", classe->major_version);


    printf("constant_pool_count: %hi\n", classe->constant_pool_count);
    printf("acess_flags: %hi\n", classe->access_flags);
    printf("this_class: %hi\n", classe->this_class);
    printf("super_class: %hi\n", classe->super_class);
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
    set_class_file(class);
    class->status = CLASSE_NAO_LINKADA;
    printf("Done loadClass\n");
}
