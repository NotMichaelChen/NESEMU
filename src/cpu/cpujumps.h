#ifndef CPUJUMPS_H
#define CPUJUMPS_H

#include "cpuinternal.h"

void JMP(unsigned char opcode, int* cpucycles, struct registers* reg);
void JSR(unsigned char opcode, int* cpucycles, struct registers* reg);
void RTS(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPUJUMPS_H
