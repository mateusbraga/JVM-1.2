#include "frame_stack.h";

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

// ------- Opcode array -------

void (*opcode[])(void) = {aconst_null, iconst_m1, iconst_0, iconst_1, iconst_2, iconst_3, iconst_4, iconst_5, lconst_0, lconst_1};

