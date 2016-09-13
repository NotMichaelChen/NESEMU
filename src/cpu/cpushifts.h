#ifndef CPUSHIFTS_H
#define CPUSHIFTS_H

#include "cpuinternal.h"

void ASL(unsigned char opcode, int* cpucycles, struct registers* reg);
void LSR(unsigned char opcode, int* cpucycles, struct registers* reg);
void ROL(unsigned char opcode, int* cpucycles, struct registers* reg);
void ROR(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPUSHIFTS_H
