#include <stdbool.h>

#include "Memory/addressing-modes.h"
#include "cpuinternal.h"

//Contains function for all branch-related cpu opcodes

void cpu_branch(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    //TODO: make cpucycles more correct
    *cpucycles += 2;

    bool condition;
    switch(opcode)
    {
    case 0xB0: //BCS
        condition = reg->C;
        break;

    case 0xF0: //BEQ
        condition = reg->Z;
        break;

    case 0x30: //BMI
        condition = reg->N;
        break;

    case 0x70: //BVS
        condition = reg->V;
        break;

    case 0x90: //BCC
        condition = !(reg->C);
        break;

    case 0xD0: //BNE
        condition = !(reg->Z);
        break;

    case 0x10: //BPL
        condition = !(reg->N);
        break;

    case 0x50: //BVC
        condition = !(reg->V);
        break;
    }

    char offset = mode_relative(&(reg->PC));
    //offset is added from after PC is incremented by 2
    //If the check fails, PC is still offset by 2 (from mode_relative) to continue normal execution
    reg->PC += offset * condition;
}
