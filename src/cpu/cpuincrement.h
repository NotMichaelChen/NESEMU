#ifndef CPUINCREMENT_H
#define CPUINCREMENT_H

#include "cpuinternal.h"

void INC(unsigned char opcode, int* cpucycles, struct registers* reg);
void INX(unsigned char opcode, int* cpucycles, struct registers* reg);
void INY(unsigned char opcode, int* cpucycles, struct registers* reg);
void DEC(unsigned char opcode, int* cpucycles, struct registers* reg);
void DEX(unsigned char opcode, int* cpucycles, struct registers* reg);
void DEY(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPUINCREMENT_H
