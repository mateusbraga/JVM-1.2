#include <stdlib.h>
// Lista de opcode utilizada: http://en.wikipedia.org/wiki/Java_bytecode_instruction_listings
// ------- Opcode functions ------

void aconst_null();

void iconst_m1();
void iconst_0();
void iconst_1();
void iconst_2();
void iconst_3();
void iconst_4();
void iconst_5();

void lconst_0();
void lconst_1();

void fconst_0();
void fconst_1();

void dconst_0();
void dconst_1();

void bipush();
void sipush();

// ------- Opcode array -------

void (*jvm_opcode[])(void) = {
    NULL ,aconst_null, iconst_m1, iconst_0, iconst_1, iconst_2, iconst_3, iconst_4, iconst_5, lconst_0, lconst_1,
    fconst_0, fconst_1, dconst_0, dconst_1, bipush, sipush
    };

