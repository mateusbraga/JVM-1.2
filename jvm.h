#ifndef JVM_H_
#define JVM_H_

#include "structs.h"
#include "frame_stack.h"

// CLASS_T STUFF
class_t *getClass(Utf8_info_t* class_name);
class_t *createClass(Utf8_info_t* class_name);
class_t *getSuperClass(class_t* sub_class);
int isSameClass(class_t* a, class_t* b);
int isSuperClassOf(class_t* super_class, class_t* sub_class);

// METHOD STUFF
void callMethod(class_t* class, method_info_t* method);
method_info_t* getMethod(class_t* class, Utf8_info_t* method_name, Utf8_info_t* descriptor);
int getNumberOfArguments(class_t* class, method_info_t* method);
int hasReturnValue(class_t* class, method_info_t* method);
code_attribute_t* getCodeAttribute(class_t* class, method_info_t* method);

// OTHERS
void returnFromFunction();
void throwException(class_t* exception_class);

#endif 
