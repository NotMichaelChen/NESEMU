#ifndef CPUARITHMETIC_H
#define CPUARITHMETIC_H

#include "cpuinternal.h"

void cpu_arithmetic(unsigned char opcode, int* cpucycles, struct registers* reg);
void CMP(unsigned char opcode, int* cpucycles, struct registers* reg);
void CPX(unsigned char opcode, int* cpucycles, struct registers* reg);
void CPY(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPUARITHMETIC_H
