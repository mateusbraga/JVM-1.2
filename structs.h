#ifndef _STRUCTS_DEF
#define _STRUCTS_DEF

#include <stdint.h>

// CLASS FILE FORMAT STUFF - BEGIN

/* Tags */
#define CONSTANT_Utf8                   1
#define CONSTANT_Integer                3
#define CONSTANT_Float                  4
#define CONSTANT_Long                   5
#define CONSTANT_Double                 6
#define CONSTANT_Class                  7
#define CONSTANT_String                 8
#define CONSTANT_Fieldref               9
#define CONSTANT_Methodref              10
#define CONSTANT_InterfaceMethodref     11
#define CONSTANT_NameAndType            12

/* Access Flags */
#define ACC_PUBLIC                      0x0001
#define ACC_PRIVATE                     0x0002
#define ACC_PROTECTED                   0x0004
#define ACC_STATIC                      0x0008
#define ACC_FINAL                       0x0010
#define ACC_SUPER                       0x0020
#define ACC_VOLATILE                    0x0040
#define ACC_TRANSIENT                   0x0080
#define ACC_NATIVE                      0x0100
#define ACC_INTERFACE                   0x0200
#define ACC_ABSTRACT                    0x0400
#define ACC_STRICT                      0x0800


/* Data types */
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

typedef struct Utf8_info_struct {
    u2 length;
    u1 *bytes;
} Utf8_info_t;

typedef struct cp_info_struct
{
    u1 tag;
    union cp_info_union {
        struct CONSTANT_Class_info_struct {
            u2 name_index;
        } Class;

        struct CONSTANT_Fieldref_info_struct {
            u2 class_index;
            u2 name_and_type_index;
        } Fieldref;

        struct CONSTANT_Methodref_info_struct {
            u2 class_index;
            u2 name_and_type_index;
        } Methodref;

        struct CONSTANT_InterfaceMethodref_info_struct {
            u2 class_index;
            u2 name_and_type_index;
        } Interfacemethod;

        struct CONSTANT_String_info_struct {
            u2 string_index;
        } String;

        struct CONSTANT_Integer_info_struct {
            u4 bytes;
        } Integer;

        struct CONSTANT_Float_info_struct {
            u4 bytes;
        } Float;

        struct CONSTANT_Long_info_struct {
            u4 high_bytes;
            u4 low_bytes;
        } Long;

        struct CONSTANT_Double_info_struct {
            u4 high_bytes;
            u4 low_bytes;
        } Double;

        struct CONSTANT_NameAndType_info_struct {
            u2 name_index;
            u2 descriptor_index;
        } Nameandtype;

        Utf8_info_t Utf8;

    } info;
} cp_info_t;

typedef struct exception_table_struct {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} exception_table_t;

//typedef struct inner_class_struct {
    //u2 inner_class_info_index;
    //u2 outer_class_info_index;
    //u2 inner_name_index;
    //u2 inner_class_access_flags;
//} inner_class_t;

//typedef struct line_number_table_struct {
    //u2 start_pc;
    //u2 line_number;
//} line_number_table_t;

//typedef struct local_variable_table_struct {
    //u2 start_pc;
    //u2 length;
    //u2 name_index;
    //u2 descriptor_index;
    //u2 index;
//} local_variable_table_t;

typedef struct constantvalue_attribute_struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 constantvalue_index;
} constantvalue_attribute_t;

typedef struct code_attribute_struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    exception_table_t *exception_table;
    u2 attributes_count;
    struct attribute_info_struct *attributes;
} code_attribute_t;

typedef struct exceptions_attribute_struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_exceptions;
    u2 *exception_index_table;
} exceptions_attribute_t;

// TODO talvez nao precisa implementar
//typedef struct InnerClasses_attribute_struct {
    //u2 attribute_name_index;
    //u4 attribute_length;
    //u2 number_of_classes;
    //inner_class_t *classes;
//} info_innerclasses_t;

// TODO talvez nao precisa implementar
//typedef struct Synthetic_attribute_struct {
    //u2 attribute_name_index;
    //u4 attribute_length;
//} info_synthetic_t;

// TODO talvez nao precisa implementar
//typedef struct Sourcefile_attribute_struct {
    //u2 attribute_name_index;
    //u4 attribute_length;
    //u2 sourcefile_index;
//} info_sourcefile_t;

/*typedef struct Signature_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 signature_index;
} info_signature_t;*/

// TODO talvez nao precisa implementar
//typedef struct LineNumberTable_attribute_struct {
    //u2 attribute_name_index;
    //u4 attribute_length;
    //u2 line_number_table_length;
    //line_number_table_t *line_number_table;
//} info_line_number_table_t;

// TODO talvez nao precisa implementar
//typedef struct LocalVariableTable_attribute_struct {
    //u2 attribute_name_index;
    //u4 attribute_length;
    //u2 local_variable_table_length;
    //local_variable_table_t *local_variable_table;
//} info_local_variable_table_t;

// TODO talvez nao precisa implementar
//typedef struct Deprecated_attribute_struct {
    //u2 attribute_name_index;
    //u4 attribute_length;
//} info_deprecated_t;

typedef struct attribute_info_struct {
    u2 attribute_name_index;
    u4 attribute_length;

    union attribute_info_struct_union {
        constantvalue_attribute_t constant_value;
        code_attribute_t code;
        exceptions_attribute_t exception;
        //info_innerclasses_t innerclasses;
        //info_synthetic_t synthetic;
        //info_sourcefile_t sourcefile;
        //info_line_number_table_t line_number_table;
        //info_local_variable_table_t local_variable_table;
        //info_deprecated_t deprecated;
        //info_signature_t signature;
    } info;
} attribute_info_t;

//typedef struct constantvalue_attribute_real_struct { TODO
    //u2 access_flags;
    //u2 name_index;
    //u2 descriptor_index;
    //u2 attributes_count;
    //attribute_info_t *attributes;
//} constantvalue_attribute_t;

//typedef struct sourcefile_attribute_struct {
    //u2 attribute_name_index;
    //u4 attribute_length;
    //u2 sourcefile_index;
//} sourcefile_attribute_t;


typedef struct field_info_struct {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info_t *attributes;
} field_info_t;


typedef struct method_info_struct {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info_t *attributes;
} method_info_t;

/*
 * Representa a estrutura de um arquivo CLASS.
 */
typedef struct class_file_struct {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info_t* constant_pool; /* Size of constant_pool_count */
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces; /* size of interfaces_count */
    u2 fields_count;
    field_info_t *fields; /* size of fields_count */
    u2 methods_count;
    method_info_t *methods; /* size of methods_count */
    u2 attributes_count;
    attribute_info_t *attributes; /* size of attributes_count */
} class_file_t;

// CLASS FILE FORMAT STUFF - END

// JVM Types - BEGIN

typedef enum any_type_tag_enum {PRIMITIVE, REFERENCE} any_type_tag_t;
typedef enum reference_type_tag_enum {ARRAY, OBJECT, NULL_REFERENCE} reference_type_tag_t;
typedef enum primitive_type_tag_enum {BOOLEAN, BYTE, SHORT, INT, LONG, CHAR, FLOAT, DOUBLE} primitive_type_tag_t;

typedef struct any_type_struct any_type_t;

typedef struct array_struct {
    uint32_t length;
    any_type_t *components;
} array_t;

typedef struct object_struct {
    uint32_t length;
    any_type_t *atributes;
} object_t;

typedef struct primitive_type_struct {
    primitive_type_tag_t tag;
    union primitive_type_struct_union{
        uint8_t val_boolean;
        int8_t val8;
        int16_t val16;
        int32_t val32;
        int64_t val64;
        uint16_t val_char;

        float val_float;
        double val_double;
    } val;
} primitive_type_t;

typedef struct reference_type_struct {
    reference_type_tag_t tag;
    union reference_type_struct_union {
        array_t array;
        object_t object;
        void* val_null;
    } val;
} reference_type_t;

struct any_type_struct {
    any_type_tag_t tag;
    union any_type_struct_union {
        primitive_type_t primitive_val;
        reference_type_t reference_val;
    } val;
};

// JVM Types - END

typedef enum {CLASSE_NAO_CARREGADA, CLASSE_NAO_LINKADA, CLASSE_NAO_INICIALIZADA, CLASSE_PRONTA } class_status_t;

typedef struct class_struct {
    Utf8_info_t *class_name;
    class_status_t status;
    class_file_t class_file;
    any_type_t** static_fields; // Array de ponteiros para campos estaticos
    u2 static_field_length;
    //method* method_table; //TODO
} class_t;

typedef struct pc_struct {
    class_t* class;
    method_info_t* method;
    u2 code_pc;
} pc_t;


#endif
