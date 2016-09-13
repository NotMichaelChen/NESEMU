#include "cpuinternal.h"
#include "memory/addressing-modes.h"
#include "memory/memory.h"

//Contains opcodes that move registers around
//TODO: reduce function count

//Copies the current contents of the accumulator into the X register
//and sets the zero and negative flags as appropriate.
void TAX(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    reg->X = reg->A;

    reg->Z = !(reg->X);
    reg->N = (char)(reg->X) < 0;

    (reg->PC)++;
    *cpucycles += 2;
}

//Copies the current contents of the accumulator into the Y register
//and sets the zero and negative flags as appropriate.
void TAY(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    reg->Y = reg->A;

    reg->Z = !(reg->Y);
    reg->N = (char)(reg->Y) < 0;

    (reg->PC)++;
    *cpucycles += 2;
}

//Copies the current contents of the X register into the accumulator
//and sets the zero and negative flags as appropriate.
void TXA(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    reg->A = reg->X;

    reg->Z = !(reg->A);
    reg->N = (char)(reg->A) < 0;

    (reg->PC)++;
    *cpucycles += 2;
}

//Copies the current contents of the Y register into the accumulator
//and sets the zero and negative flags as appropriate.
void TYA(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    reg->A = reg->Y;

    reg->Z = !(reg->A);
    reg->N = (char)(reg->A) < 0;

    (reg->PC)++;
    *cpucycles += 2;
}
