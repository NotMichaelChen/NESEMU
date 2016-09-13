#ifndef CPUSTACK_H
#define CPUSTACK_H

#include "cpuinternal.h"

void TSX(unsigned char opcode, int* cpucycles, struct registers* reg);
void TXS(unsigned char opcode, int* cpucycles, struct registers* reg);
void PHA(unsigned char opcode, int* cpucycles, struct registers* reg);
void PHP(unsigned char opcode, int* cpucycles, struct registers* reg);
void PLA(unsigned char opcode, int* cpucycles, struct registers* reg);
void PLP(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPUSTACK_H
