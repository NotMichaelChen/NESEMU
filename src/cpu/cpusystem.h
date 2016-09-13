#ifndef CPUSYSTEM_H
#define CPUSYSTEM_H

#include "cpuinternal.h"

void BRK(unsigned char opcode, int* cpucycles, struct registers* reg);
void NOP(unsigned char opcode, int* cpucycles, struct registers* reg);
void RTI(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPUSYSTEM_H
