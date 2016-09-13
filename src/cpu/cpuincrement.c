#include "cpuinternal.h"
#include "memory/addressing-modes.h"
#include "memory/memory.h"

//Contains functions for all increment/decrement operations
//TODO: Reduce into fewer functions

//Adds one to the value held at a specified memory location setting the zero and negative flags as appropriate.
//$E6, $F6, $EE, $FE
void INC(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address;

    switch(opcode)
    {
    //Zero Page
    case 0xE6:
        address = mode_zeropage(&(reg->PC));
        *cpucycles += 5;
        break;

    //Zero Page,X
    case 0xF6:
        address = mode_zeropage_X(&(reg->PC), reg->X);
        *cpucycles += 6;
        break;

    //Absolute
    case 0xEE:
        address = mode_absolute(&(reg->PC));
        *cpucycles += 6;
        break;

    //Absolute,X
    case 0xFE:
        address = mode_absolute_X(&(reg->PC), cpucycles, reg->X);
        *cpucycles += 7;
        break;
    }

    unsigned char result = readRAM(address) + 1;

    reg->Z = !result;
    reg->N = (char)result < 0;

    writeRAM(result, address);
}

//Adds one to the X register setting the zero and negative flags as appropriate.
//$E8
void INX(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    (reg->X)++;
    reg->Z = !(reg->X);
    reg->N = (char)(reg->X) < 0;

    *cpucycles += 2;
    (reg->PC)++;
}

//Adds one to the Y register setting the zero and negative flags as appropriate.
//$88
void INY(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    (reg->Y)++;
    reg->Z = !(reg->Y);
    reg->N = (char)(reg->Y) < 0;

    *cpucycles += 2;
    (reg->PC)++;
}

//Subtracts one from the value held at a specified memory location setting the zero and negative flags as appropriate.
//$C6, $D6, $CE, $DE
void DEC(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address;

    switch(opcode)
    {
    //Zero Page
    case 0xC6:
        address = mode_zeropage(&(reg->PC));
        *cpucycles += 5;
        break;

    //Zero Page,X
    case 0xD6:
        address = mode_zeropage_X(&(reg->PC), reg->X);
        *cpucycles += 6;
        break;

    //Absolute
    case 0xCE:
        address = mode_absolute(&(reg->PC));
        *cpucycles += 6;
        break;

    //Absolute,X
    case 0xDE:
        address = mode_absolute_X(&(reg->PC), cpucycles, reg->X);
        *cpucycles += 7;
        break;
    }

    unsigned char result = readRAM(address) - 1;

    reg->Z = !result;
    reg->N = (char)result < 0;

    writeRAM(result, address);
}

//Subtracts one from the X register setting the zero and negative flags as appropriate.
//$CA
void DEX(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    (reg->X)--;
    reg->Z = !(reg->X);
    reg->N = (char)(reg->X) < 0;

    *cpucycles += 2;
    (reg->PC)++;
}

//Subtracts one from the Y register setting the zero and negative flags as appropriate.
//$88
void DEY(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    (reg->Y)--;
    reg->Z = !(reg->Y);
    reg->N = (char)(reg->Y) < 0;

    *cpucycles += 2;
    (reg->PC)++;
}
