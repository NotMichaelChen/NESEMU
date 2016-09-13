#ifndef CPUREGTRANS_H
#define CPUREGTRANS_H

#include "cpuinternal.h"

void TAX(unsigned char opcode, int* cpucycles, struct registers* reg);
void TAY(unsigned char opcode, int* cpucycles, struct registers* reg);
void TXA(unsigned char opcode, int* cpucycles, struct registers* reg);
void TYA(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPUREGTRANS_H
