#ifndef CPUINTERNAL_H
#define CPUINTERNAL_H

#include <stdbool.h>

struct registers
{
    //Accumulator
    unsigned char A;
    //Indexes
    unsigned char X, Y;
    //Program Counter
    unsigned short PC;
    //Stack Pointer
    unsigned char SP;

    //Status Register
    bool C; //Carry Flag
    bool Z; //Zero Flag
    bool I; //Interrupt Disable
    bool D; //Decimal Mode - NES 2A03 doesn't support BCD calculations, no effect
    bool B; //Break Command
    bool V; //Overflow Flag
    bool N; //Negative Flag
};

#endif // CPUINTERNAL_H
