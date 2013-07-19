#ifndef OPCODE_H_
#define OPCODE_H_

#include "structs.h"
#include "frame_stack.h"

int getNumberOfOpcodeOperandsInBytes(u1* code, u2 index);
void goToNextOpcode();

#endif 
