#ifndef JVM_H_
#define JVM_H_

#include "structs.h"
#include "frame_stack.h"

// UTF8 STUFF - BEGIN
Utf8_info_t* string_to_utf8(char* a);
char* utf8_to_string(Utf8_info_t* utf8);
int compare_utf8(Utf8_info_t* a, Utf8_info_t* b);
u2 get_utf8_length_from_char(char* string);
u2 scan_utf8_char_from_char(char* string, u2 *pos);
any_type_t* char_to_array_reference(char* string);
any_type_t* utf8_to_array_reference(Utf8_info_t* utf8);
// UTF8 STUFF - END

// CLASS_T STUFF - BEGIN
class_t *getClass(Utf8_info_t* class_name);
class_t *createClass(Utf8_info_t* class_name);
class_t *getSuperClass(class_t* sub_class);
int isSameClass(class_t* a, class_t* b);
int isSuperClassOf(class_t* super_class, class_t* sub_class);
// CLASS_T STUFF - END

// METHOD STUFF - BEGIN
code_attribute_t* getCodeAttribute(class_t* class, method_info_t* method);
int hasReturnValue(class_t* class, method_info_t* method);
method_info_t* getMethod(class_t* class, Utf8_info_t* method_name, Utf8_info_t* descriptor);
int getNumberOfArguments(class_t* class, method_info_t* method);
// METHOD STUFF - END

// OPCODE STUFF - BEGIN
int getNumberOfOpcodeOperandsInBytes(u1* code, u2 index);
void goToNextOpcode();
// OPCODE STUFF - END

void createMultiArray(any_type_t *arrayref, u1 tamanho, u1 dimensao, class_t *tipo);

// JVM OPERATION STUFF - BEGIN
void throwException(class_t* exception_class);
void returnFromFunction();
void callMethod(class_t* class, method_info_t* method);
// JVM OPERATION STUFF - END

#endif 
