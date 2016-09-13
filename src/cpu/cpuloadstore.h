#ifndef CPULOADSTORE_H
#define CPULOADSTORE_H

#include "cpuinternal.h"

void LDA(unsigned char opcode, int* cpucycles, struct registers* reg);
void LDX(unsigned char opcode, int* cpucycles, struct registers* reg);
void LDY(unsigned char opcode, int* cpucycles, struct registers* reg);
void STA(unsigned char opcode, int* cpucycles, struct registers* reg);
void STX(unsigned char opcode, int* cpucycles, struct registers* reg);
void STY(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPULOADSTORE_H
