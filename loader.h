/* Estrutura do arquivo CLASS */

#ifndef LOADER_H_
#define LOADER_H_

#include "structs.h"


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

/*
 * cp_info em si, formada por um byte que representa a tag
 * e a outra parte nao se sabe ate ler o arquivo, podendo ser
 * diferentes tipos de cp_infos, por isso uma union
 */
typedef struct cp_info_struct
{
    u1 tag;
    union info
    {
        struct CONSTANT_Class_info_struct
        {
            u2 name_index;
        } class_info_t;

        struct CONSTANT_Fieldref_info_struct
        {
            u2 class_index;
            u2 name_and_type_index;
        } fieldref_info_t;;


        struct CONSTANT_Methodref_info_struct
        {
            u2 class_index;
            u2 name_and_type_index;
        } methodref_info_t;

        struct CONSTANT_InterfaceMethodref_info_struct
        {
            u2 class_index;
            u2 name_and_type_index;
        } interfacemethod_info_t;

        struct CONSTANT_String_info_struct
        {
            u2 string_index;
        } string_info_t;

        struct CONSTANT_Integer_info_struct
        {
            u4 bytes;
        } integer_info_t;

        struct CONSTANT_Float_info_struct
        {
            u4 bytes;
        } float_info_t;

        struct CONSTANT_Long_info_struct
        {
            u4 high_bytes;
            u4 low_bytes;
        } long_info_t;

        struct CONSTANT_Double_info_struct
        {
            u4 high_bytes;
            u4 low_bytes;
        } double_info_t;

        struct CONSTANT_NameAndType_info_struct
        {
            u2 name_index;
            u2 descriptor_index;
        } nameandtype_info_t;

        struct Utf8_info_struct
        {
            u2 length;
            u1 *bytes;
        } utf8_info_t;

    } info;
} cp_info_t;


typedef struct exception_table_struct
{
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} exception_table_t;

typedef struct inner_class_struct
{
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
} inner_class_t;

typedef struct line_number_table_struct
{
    u2 start_pc;
    u2 line_number;
} line_number_table_t;

typedef struct local_variable_table_struct
{
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
} local_variable_table_t;


typedef struct constantvalue_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 constantvalue_index;
} info_constant_value_t;

typedef struct code_attribute_struct
{
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
} info_code_t;

typedef struct Exceptions_attribute_stru    ct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_exceptions;
    u2 *exception_index_table;
} info_exception_t;

typedef struct InnerClasses_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
    inner_class_t *classes;
} info_innerclasses_t;

typedef struct Synthetic_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
} info_synthetic_t;

typedef struct Sourcefile_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 sourcefile_index;
} info_sourcefile_t;

/*typedef struct Signature_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 signature_index;
} info_signature_t;*/

typedef struct LineNumberTable_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 line_number_table_length;
    line_number_table_t *line_number_table;
} info_line_number_table_t;

typedef struct LocalVariableTable_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_table_length;
    local_variable_table_t *local_variable_table;
} info_local_variable_table_t;

typedef struct Deprecated_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
} info_deprecated_t;


typedef struct attribute_info_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u1 *info;

    union u_info_att
    {
        info_constant_value_t constant_value;
        info_code_t code;
        info_exception_t exception;
        info_innerclasses_t innerclasses;
        info_synthetic_t synthetic;
        info_sourcefile_t sourcefile;
        info_line_number_table_t line_number_table;
        info_local_variable_table_t local_variable_table;
        info_deprecated_t deprecated;
        info_signature_t signature;

    } _info;
} attribute_info_t;

typedef struct constantvalue_attribute_struct
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info_t *attributes;
} constantvalue_attribute_t;


typedef struct code_attribute_struct
{
    u2 attribute_name_index 
    u4 attribute_length 
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    exception_table_t *exception_table;
    u2 attributes_count;
    attribute_info_t *attributes;
} code_attribute_t;


typedef struct sourcefile_attribute_struct
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 sourcefile_index;
} sourcefile_attribute_t;


typedef struct field_info_struct
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info_t *attributes;
} field_info_t;


typedef struct method_info_struct
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info_t *attributes;
} method_info_t;

/*
 * Representa a estrutura de um arquivo CLASS.
 */
typedef struct class_file_struct
{
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


// todo tipo termina com _t: como em class_t
// toda struct termina com _struct como em class_struct
// olhar arquivo structs.h

void loadClass(class_t* class);

#endif /* LOADER_H_ */
 
