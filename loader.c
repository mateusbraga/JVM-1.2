

#include "loader.h"

/*-----------------------------------------------------------------------------------------------------------------*/

attribute_info_t* GetAtributos(class_file* classe, FILE *fp, int attributesCount){
    attribute_info_t *atributos;
    char *nome;
    int i, j;
    atributos = (attribute_info_t*)calloc(attributesCount, sizeof(attribute_info_t));
       
    for( i = 0; i < attributesCount ; i++){
                atributos[i].attribute_name_index = readu2(fp);
                atributos[i].attribute_length = readu4(fp);
                nome = (char*)(( Utf8_info_t*)classe->cp_info_t[atributos[i].attribute_name_index].info)->bytes;
                if(strcmp(nome, "constant_value") == 0) {
                        atributos[i].info = malloc(sizeof(constantvalue_attribute_t));
                        ((constantvalue_attribute_t*)atributos[i].info)->attribute_name_index = atributos[i].attribute_name_index;
                        ((constantvalue_attribute_t*)atributos[i].info)->attribute_length = atributos[i].attribute_length;
                        ((constantvalue_attribute_t*)atributos[i].info)->constantvalue_index = readu2(fp);
                } else if(strcmp(nome, "code") == 0) {
                        atributos[i].info = malloc(sizeof(code_attribute_t));
                        ((code_attribute_t*)atributos[i].info)->attribute_name_index = atributos[i].attribute_name_index;
                        ((code_attribute_t*)atributos[i].info)->attribute_length = atributos[i].attribute_length;
                        ((code_attribute_t*)atributos[i].info)->max_stack = readu2(fp);
                        ((code_attribute_t*)atributos[i].info)->max_locals = readu2(fp);
                        ((code_attribute_t*)atributos[i].info)->code_length = readu4(fp);
                        ((code_attribute_t*)atributos[i].info)->code = (u1*)calloc(((code_attribute_t*)atributos[i].info)->code_length, sizeof(u1));
                        for(j=0; j < ((code_attribute_t*)atributos[i].info)->code_length; j++ ){
                                ((code_attribute_t*)atributos[i].info)->code[j] = readu1(fp);
                        }
                        ((code_attribute_t*)atributos[i].info)->exception_table_length = readu2(fp);
                        ((code_attribute_t*)atributos[i].info)->exception_table = (exception_table_t*)calloc(((code_attribute_t*)atributos[i].info)->exception_table_length, sizeof(exception_table_t));
                        for(j=0; j < ((code_attribute_t*)atributos[i].info)->exception_table_length; j++) {
                                ((code_attribute_t*)atributos[i].info)->exception_table_t->start_pc = readu2(fp);
                                ((code_attribute_t*)atributos[i].info)->exception_table_t->end_pc = readu2(fp);
                                ((code_attribute_t*)atributos[i].info)->exception_table_t->handler_pc = readu2(fp);
                                ((code_attribute_t*)atributos[i].info)->exception_table_t->catch_type = readu2(fp);
                        }
                        ((code_attribute_t*)atributos[i].info)->attributes_count = readu2(fp);
                        ((code_attribute_t*)atributos[i].info)->attributes = GetAtributos(classe, fp,((code_attribute_t*)atributos[i].info)->attributes_count);
                } else if(strcmp(nome, "exceptions") == 0) {
                        atributos[i].info = malloc(sizeof(exceptions_attribute_t));
                        ((exceptions_attribute_t*)atributos[i].info)->attribute_name_index = atributos[i].attribute_name_index;
                        ((exceptions_attribute_t*)atributos[i].info)->attribute_length = atributos[i].attribute_length;
                        ((exceptions_attribute_t*)atributos[i].info)->number_of_exceptions = readu2(fp);
                        ((exceptions_attribute_t*)atributos[i].info)->exception_index_table = (u2*)calloc(sizeof(u2*),((exceptions_attribute_t*)atributos[i].info)->number_of_exceptions );
                        for(j=0;j<((exceptions_attribute_t*)atributos[i].info)->number_of_exceptions; j++){
                                ((exceptions_attribute_t*)atributos[i].info)->exception_index_table[j] = readu2(fp);
                        }
                
                } else {
                        atributos[i].info = (u1*)calloc(sizeof(u1), atributos[i].attribute_length);
                        for(j = 0; j < atributos[i].attribute_length; j++){
                                ((u1*)(atributos[i].info))[j] = readu1(fp);                      
                        }
                }
       
    }
    return atributos;
}

/*-----------------------------------------------------------------------------------------------------------------*/

method_info_t* GetMetodo(class_file* classe,  FILE *fp, int methodsCount){
        method_info_t *metodos;
        int i;

        metodos = (method_info_t*)calloc(methodsCount, sizeof(method_info_t));
        for( i=0 ; i<methodsCount ; i++ ){
                metodos[i].acess_flags = readu2(fp);
                metodos[i].name_index = readu2(fp);
                metodos[i].descriptor_index = readu2(fp);
                metodos[i].attributes_count = readu2(fp);
                metodos[i].attributes = GetAtributos(classe, fp, metodos[i].attributes_count);
        }

        return metodos;
}

/*-----------------------------------------------------------------------------------------------------------------*/

field_info_t* GetFields(class_file* classe, FILE *fp, int fieldCount){
    field_info_t *fields;
    int j;
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

cp_info_t* GetConstantes(FILE *fp, int constantCount){
    class_info_t *classAux;
    utf8_info_t *utf8Aux;
    long_info_t *LongAux;
    double_info_t *doubleAux;
    string_info_t *stringAux;
    nameandtype_info_t *nameAndTypeAux;
    fieldref_info_t *FieldAux;
    methodref_info_t *MethodAux;
    interfacemethod_info_t *InterfaceAux;
    integer_info_t *intAux;
    float_info_t *FloatAux;
    cp_info_t *constantes;
    int i, j;    

    constantes = (cp_info_t*)calloc(constantCount, sizeof(cp_info_t));
    for(i=1;i<constantCount;i++){
                constantes[i].tag = readu1(fp);
                switch(constantes[i].tag){
                        case CONSTANT_Class:
                                        constantes[i].info = malloc(sizeof(class_info_t));
                                        classAux = (class_info_t*)constantes[i].info;
                                        classAux->name_index = readu2(fp);
                                        break;                  
                        case CONSTANT_Fieldref :
                        				constantes[i].info = malloc(sizeof(fieldref_info_t));
                                        FieldAux = (fieldref_info_t*)constantes[i].info; //
                                        FieldAux->class_index = readu2(fp);
                                        FieldAux->name_and_type_index = readu2(fp);
                                        break;
                        case CONSTANT_Methodref :
                        				constantes[i].info = malloc(sizeof(methodref_info_t));
                                        MethodAux = (methodref_info_t*)constantes[i].info; //
                                        MethodAux->class_index = readu2(fp);
                                        MethodAux->name_and_type_index = readu2(fp);
                                        break;
                        case CONSTANT_InterfaceMethodref :
                                        constantes[i].info = malloc(sizeof(interfacemethod_info_t));
                                        InterfaceAux = (interfacemethod_info_t*)constantes[i].info; //
                                        InterfaceAux->class_index = readu2(fp);
                                        InterfaceAux->name_and_type_index = readu2(fp);
                                        break;
                        case CONSTANT_NameAndType :
                                        constantes[i].info = malloc(sizeof(nameandtype_info_t));
                                        nameAndTypeAux = (nameandtype_info_t*)constantes[i].info;
                                        nameAndTypeAux->name_index = readu2(fp);
                                        nameAndTypeAux->descriptor_index = readu2(fp);
                                        break;
                        case CONSTANT_Utf8    :
                                        constantes[i].info = malloc(sizeof(utf8_info_t));
                                        utf8Aux = (utf8_info_t*)constantes[i].info;
                       
                                        utf8Aux->length = readu2(fp);
                                        utf8Aux->bytes = (u1*)calloc(utf8Aux->length + 1, sizeof(u1));
                                        for(j = 0; j < utf8Aux->length; j++){
                                                utf8Aux->bytes[j] = readu1(fp);
                                        }
                                        utf8Aux->bytes[j] = '\0';
                                        break;
                        case CONSTANT_String:
                                        constantes[i].info = malloc(sizeof(string_info_t));
                                        stringAux = (string_info_t*)constantes[i].info;
                                        stringAux->string_index = readu2(fp);
                                        break;
                        case CONSTANT_Integer :
                        				constantes[i].info = malloc(sizeof(integer_info_t));
                                		intAux = (integer_info_t*)constantes[i].info;
                                		intAux->bytes = readu4(fp);
                                		break;

                        case CONSTANT_Float :
                               			constantes[i].info = malloc(sizeof(float_info_t));
                                		FloatAux = (float_info_t*)constantes[i].info;
                                		FloatAux->bytes = readu4(fp);
                                		break;
                        case CONSTANT_Long  :
                        				constantes[i].info = malloc(sizeof(long_info_t));
                                        LongAux = (long_info_t*)constantes[i].info;
                                		LongAux->high_bytes = readu4(fp);
                                		LongAux->low_bytes = readu4(fp);
                                		++i;
                                		break;

                        case CONSTANT_Double :
                                		constantes[i].info = malloc(sizeof(double_info_t));
                                		doubleAux = (double_info_t*)constantes[i].info;
                                		doubleAux->high_bytes = readu4(fp);
                                		doubleAux->low_bytes = readu4(fp);
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

class_file* class_file(char* filename){
    int i;
    FILE *fp;
    class_file *classe;

    if( (fp = fopen(filename, "rb")) == NULL){
                printf("Erro! Nao foi possivel abrir o arquivo!\n");
                exit(1);
    }

    classe = (class_file*)malloc(sizeof(class_file));
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
       
    return classe;
}


