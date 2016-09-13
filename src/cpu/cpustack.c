#include "cpuinternal.h"
#include "memory/addressing-modes.h"
#include "memory/memory.h"

//Contains opcodes that manipulate the stack and stack pointer

//Copies the current contents of the stack register into the X register
//and sets the zero and negative flags as appropriate.
void TSX(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    reg->X = reg->SP;

    reg->Z = !(reg->X);
    reg->N = (char)(reg->X) < 0;

    (reg->PC)++;
    *cpucycles += 2;
}

//Copies the current contents of the X register into the stack register.
void TXS(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    reg->SP = reg->X;

    (reg->PC)++;
    *cpucycles += 2;
}

//Pushes a copy of the accumulator on to the stack.
void PHA(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    stack_push(reg->A, &(reg->SP));

    (reg->PC)++;
    *cpucycles += 3;
}

//Pushes a copy of the status flags on to the stack.
void PHP(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    //Encode the status flags into a byte
    unsigned char status = 128 * reg->N +
                            64 * reg->V +
                            16 * reg->B +
                            8 * reg->D +
                            4 * reg->I +
                            2 * reg->Z +
                            1 * reg->C;

    stack_push(status, &(reg->SP));

    (reg->PC)++;
    *cpucycles += 3;
}

//Pulls an 8 bit value from the stack and into the accumulator.
//The zero and negative flags are set as appropriate.
void PLA(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    reg->A = stack_pop(&(reg->SP));

    reg->Z = !(reg->A);
    reg->N = (char)(reg->A) < 0;

    (reg->PC)++;
    *cpucycles += 4;
}

//Pulls an 8 bit value from the stack and into the processor flags.
//The flags will take on new states as determined by the value pulled.
void PLP(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    //Decode byte into register flags
    unsigned char status = stack_pop(&(reg->SP));

    reg->N = (status / 128) % 2;
    reg->V = (status / 64) % 2;
    reg->B = (status / 16) % 2;
    reg->D = (status / 8) % 2;
    reg->I = (status / 4) % 2;
    reg->Z = (status / 2) % 2;
    reg->C = status % 2;

    (reg->PC)++;
    *cpucycles += 4;
}
