#ifndef CPUFLAGS_H
#define CPUFLAGS_H

#include "cpuinternal.h"

void cpu_flags(unsigned char opcode, int* cpucycles, struct registers* reg);

#endif // CPUFLAGS_H
