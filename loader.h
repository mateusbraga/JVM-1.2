/* Estrutura do arquivo CLASS */

#ifndef LOADER_H_
#define LOADER_H_

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
#define ACC_FINAL                       0x0010
#define ACC_SUPER                       0x0020
#define ACC_INTERFACE                   0x0200
#define ACC_ABSTRACT                    0x0400

/* Data types */
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

/*
 * cp_info em si, formada por um byte que representa a tag
 * e a outra parte nao se sabe ate ler o arquivo, podendo ser
 * diferentes tipos de cp_infos, por isso uma union
 */
typedef struct cp_info
{
    u1 tag;
    union info
    {
        struct CONSTANT_Class_info
        {
            u2 name_index;
        } class_info;

        struct CONSTANT_Fieldref_info
        {
            u2 class_index;
            u2 name_and_type_index;
        } fieldref_info, methodref_info, interfacemethod_info;

        struct CONSTANT_String_info
        {
            u2 string_index;
        } string_info;

        struct CONSTANT_Integer_info
        {
            u4 bytes;
        } integer_info, float_info;

        struct CONSTANT_Long_info
        {
            u4 high_bytes;
            u4 low_bytes;
        } long_info, double_info;

        struct CONSTANT_NameAndType_info
        {
            u2 name_index;
            u2 descriptor_index;
        } nameandtype_info;

        struct Utf8_info
        {
            u2 length;
            u1 *bytes;
        } utf8_info;

    } info;
} t_cp_info;


typedef struct exception_table
{
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} t_exception_table;

typedef struct inner_class
{
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
} t_inner_class;

typedef struct line_number_table
{
    u2 start_pc;
    u2 line_number;
} t_line_number_table;

typedef struct local_variable_table
{
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
} t_local_variable_table;


typedef struct ConstantValue_attribute
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 constantvalue_index;
} t_info_constant_value;

typedef struct Code_attribute
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    t_exception_table *exception_table;
    u2 attributes_count;
    struct attribute_info *attributes;
} t_info_code;

typedef struct Exceptions_attribute
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_exceptions;
    u2 *exception_index_table;
} t_info_exception;

typedef struct InnerClasses_attribute
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
    t_inner_class *classes;
} t_info_innerclasses;

typedef struct Synthetic_attribute
{
    u2 attribute_name_index;
    u4 attribute_length;
} t_info_synthetic;

typedef struct SourceFile_attribute
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 sourcefile_index;
} t_info_sourcefile;

typedef struct Signature_attribute
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 signature_index;
} t_info_signature;

typedef struct LineNumberTable_attribute
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 line_number_table_length;
    t_line_number_table *line_number_table;
} t_info_line_number_table;

typedef struct LocalVariableTable_attribute
{
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_table_length;
    t_local_variable_table *local_variable_table;
} t_info_local_variable_table;

typedef struct Deprecated_attribute
{
    u2 attribute_name_index;
    u4 attribute_length;
} t_info_deprecated;


typedef struct attribute_info
{
    u2 attribute_name_index;
    u4 attribute_length;
    u1 *info;

    union u_info_att
    {
        t_info_constant_value constant_value;
        t_info_code code;
        t_info_exception exception;
        t_info_innerclasses innerclasses;
        t_info_synthetic synthetic;
        t_info_sourcefile sourcefile;
        t_info_line_number_table line_number_table;
        t_info_local_variable_table local_variable_table;
        t_info_deprecated deprecated;
        t_info_signature signature;

    } _info;
} t_attribute_info;

typedef struct constantvalue_attribute
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    t_attribute_info *attributes;
} t_constantvalue_attribute;


typedef struct code_attribute
{
    /* u2 attribute_name_index */
    /* u4 attribute_length */
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    t_exception_table *exception_table;
    u2 attributes_count;
    t_attribute_info *attributes;
} t_code_attribute;


typedef struct sourcefile_attribute
{
    /* Deixando sÛ os elementos dentro do info do attribute_info */
    /* u2 attribute_name_index; */
    /* u4 attribute_length; */
    u2 sourcefile_index;
} t_sourcefile_attribute;


typedef struct field_info
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    t_attribute_info *attributes;
} t_field_info;


typedef struct method_info
{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    t_attribute_info *attributes;
} t_method_info;

/*
 * Representa a estrutura de um arquivo CLASS.
 */
typedef struct class_file_f
{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    t_cp_info* constant_pool; /* Size of constant_pool_count */
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces; /* size of interfaces_count */
    u2 fields_count;
    t_field_info *fields; /* size of fields_count */
    u2 methods_count;
    t_method_info *methods; /* size of methods_count */
    u2 attributes_count;
    t_attribute_info *attributes; /* size of attributes_count */
} class_file;


void loadClass(class_t* class);

#endif /* LOADER_H_ */
 
