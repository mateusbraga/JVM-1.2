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

void ldc();
void ldc_w();
void ldc2_w();

void tload();
void tload_0();
void tload_1();
void tload_2();
void tload_3();

void taload();

void tstore();
void tstore_0();
void tstore_1();
void tstore_2();
void tstore_3();

void tastore();
// ------- Opcode array -------

void (*jvm_opcode[])(void) = {
    NULL ,aconst_null, iconst_m1, iconst_0, iconst_1, iconst_2, iconst_3, iconst_4, iconst_5, lconst_0, lconst_1,
    fconst_0, fconst_1, dconst_0, dconst_1, bipush, sipush, ldc, ldc_w, ldc2_w, tload, tload_0, tload_1, tload_2,
    tload_3, taload, tstore, tstore_0, tstore_1, tstore_3, tastore
    };

