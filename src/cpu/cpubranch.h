#ifndef CPUBRANCH_H
#define CPUBRANCH_H

#include "cpuinternal.h"

void cpu_branch(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPUBRANCH_H
