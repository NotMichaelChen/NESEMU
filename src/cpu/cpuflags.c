#include "cpuinternal.h"

//Contains function for changing system flags

void cpu_flags(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    switch(opcode)
    {
    case 0x38:
        reg->C = true;
        break;

    case 0x18:
        reg->C = false;
        break;

    case 0x78:
        reg->I = true;
        break;

    case 0x58:
        reg->I = false;
        break;

    case 0xF8:
        reg->D = true;
        break;

    case 0xD8:
        reg->D = false;
        break;

    case 0xB8:
        reg->V = false;
        break;
    }

    *cpucycles += 2;
    reg->PC += 1;
}
