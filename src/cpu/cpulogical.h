#ifndef CPULOGICAL_H
#define CPULOGICAL_H

#include "cpuinternal.h"

void AND(unsigned char opcode, int* cpucycles, struct registers* reg);
void EOR(unsigned char opcode, int* cpucycles, struct registers* reg);
void ORA(unsigned char opcode, int* cpucycles, struct registers* reg);
void BIT(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPULOGICAL_H
