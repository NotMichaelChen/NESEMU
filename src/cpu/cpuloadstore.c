#include "cpuinternal.h"
#include "memory/addressing-modes.h"
#include "memory/memory.h"

//Contains instructions transferring data between memory and registers
//TODO: reduce function count

//Loads a byte of memory into the accumulator setting the zero and negative flags as appropriate.
void LDA(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    switch(opcode)
    {
    //Immediate
    case 0xA9:
        reg->A = mode_immediate(&(reg->PC));
        *cpucycles += 2;
        break;

    case 0xA5:
        reg->A = mode_zeropage(&(reg->PC));
        *cpucycles += 3;
        break;

    case 0xB5:
        reg->A = mode_zeropage_X(&(reg->PC), reg->X);
        *cpucycles += 4;
        break;

    case 0xAD:
        reg->A = mode_absolute(&(reg->PC));
        *cpucycles += 4;
        break;

    case 0xBD:
        reg->A = mode_absolute_X(&(reg->PC), cpucycles, reg->X);
        *cpucycles += 4;
        break;

    case 0xB9:
        reg->A = mode_absolute_Y(&(reg->PC), cpucycles, reg->Y);
        *cpucycles += 4;
        break;

    case 0xA1:
        reg->A = mode_indexed_indirect(&(reg->PC), reg->X);
        *cpucycles += 6;
        break;

    case 0xB1:
        reg->A = mode_indirect_indexed(&(reg->PC), cpucycles, reg->Y);
        *cpucycles += 5;
        break;
    }

    reg->Z = !(reg->A);
    reg->N = (char)(reg->A) < 0;
}

//Loads a byte of memory into the X register setting the zero and negative flags as appropriate.
void LDX(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    switch(opcode)
    {
    //Immediate
    case 0xA2:
        reg->X = mode_immediate(&(reg->PC));
        *cpucycles += 2;
        break;

    case 0xA6:
        reg->X = mode_zeropage(&(reg->PC));
        *cpucycles += 3;
        break;

    case 0xB6:
        reg->X = mode_zeropage_Y(&(reg->PC), reg->Y);
        *cpucycles += 4;
        break;

    case 0xAE:
        reg->X = mode_absolute(&(reg->PC));
        *cpucycles += 4;
        break;

    case 0xBE:
        reg->X = mode_absolute_Y(&(reg->PC), cpucycles, reg->Y);
        *cpucycles += 4;
        break;
    }

    reg->Z = !(reg->X);
    reg->N = (char)(reg->X) < 0;
}

//Loads a byte of memory into the Y register setting the zero and negative flags as appropriate.
void LDY(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    switch(opcode)
    {
    //Immediate
    case 0xA0:
        reg->Y = mode_immediate(&(reg->PC));
        *cpucycles += 2;
        break;

    case 0xA4:
        reg->Y = mode_zeropage(&(reg->PC));
        *cpucycles += 3;
        break;

    case 0xB4:
        reg->Y = mode_zeropage_X(&(reg->PC), reg->X);
        *cpucycles += 4;
        break;

    case 0xAC:
        reg->Y = mode_absolute(&(reg->PC));
        *cpucycles += 4;
        break;

    case 0xBC:
        reg->Y = mode_absolute_X(&(reg->PC), cpucycles, reg->X);
        *cpucycles += 4;
        break;
    }

    reg->Z = !(reg->Y);
    reg->N = (char)(reg->Y) < 0;
}

//Stores the contents of the accumulator into memory
//$85, $95, $8D, $9D, $99, $81, $91
void STA(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address;

    switch(opcode)
    {
    case 0x85:
        address = mode_zeropage(&(reg->PC));
        *cpucycles += 3;
        break;

    case 0x95:
        address = mode_zeropage_X(&(reg->PC), reg->X);
        *cpucycles += 4;
        break;

    case 0x8D:
        address = mode_absolute(&(reg->PC));
        *cpucycles += 4;
        break;

    case 0x9D:
        address = mode_absolute_X(&(reg->PC), cpucycles, reg->X);
        *cpucycles += 5;
        break;

    case 0x99:
        address = mode_absolute_Y(&(reg->PC), cpucycles, reg->X);
        *cpucycles += 5;
        break;

    case 0x81:
        address = mode_indexed_indirect(&(reg->PC), reg->X);
        *cpucycles += 6;
        break;

    case 0x91:
        address = mode_indirect_indexed(&(reg->PC), cpucycles, reg->Y);
        *cpucycles += 6;
        break;
    }

    writeRAM(reg->A, address);
}

//Stores the contents of the X register into memory.
void STX(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address;

    switch(opcode)
    {
    case 0x86:
        address = mode_zeropage(&(reg->PC));
        *cpucycles += 3;
        break;

    case 0x96:
        address = mode_zeropage_Y(&(reg->PC), reg->Y);
        *cpucycles += 4;
        break;

    case 0x8E:
        address = mode_absolute(&(reg->PC));
        *cpucycles += 4;
        break;
    }

    writeRAM(reg->X, address);
}

//Stores the contents of the Y register into memory.
void STY(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address;

    switch(opcode)
    {
    case 0x84:
        address = mode_zeropage(&(reg->PC));
        *cpucycles += 3;
        break;

    case 0x94:
        address = mode_zeropage_X(&(reg->PC), reg->X);
        *cpucycles += 4;
        break;

    case 0x8C:
        address = mode_absolute(&(reg->PC));
        *cpucycles += 4;
        break;
    }

    writeRAM(reg->Y, address);
}
