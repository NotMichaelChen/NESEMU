#include "cpuinternal.h"
#include "memory/addressing-modes.h"
#include "memory/memory.h"

//TODO: Reduce into one function

//A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory
//$29, $25, $35, $2D, $3D, $39, $21, $31
void AND(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned char constant;

    switch(opcode)
    {
    //Immediate
    case 0x29:
        constant = mode_immediate(&(reg->PC));
        *cpucycles += 2;
        break;

    //Zero Page
    case 0x25:
        constant = readRAM(mode_zeropage(&(reg->PC)));
        *cpucycles += 3;
        break;

    //Zero Page,X
    case 0x35:
        constant = readRAM(mode_zeropage_X(&(reg->PC), reg->X));
        *cpucycles += 4;
        break;

    //Absolute
    case 0x2D:
        constant = readRAM(mode_absolute(&(reg->PC)));
        *cpucycles += 4;
        break;

    //Absolute,X
    case 0x3D:
        constant = readRAM(mode_absolute_X(&(reg->PC), reg->X));
        *cpucycles += 4;
        break;

    //Absolute,Y
    case 0x39:
        constant = readRAM(mode_absolute_Y(&(reg->PC), reg->Y));
        *cpucycles += 4;
        break;

    //Indirect X
    case 0x21:
        constant = readRAM(mode_indexed_indirect(&(reg->PC), reg->X));
        *cpucycles += 6;
        break;

    //Indirect Y
    case 0x31:
        constant = readRAM(mode_indirect_indexed(&reg->PC, reg->Y));
        *cpucycles += 5;
        break;
    }

    reg->A = reg->A & constant;

    reg->Z = !(reg->A);
    reg->N = (char)(reg->A) < 0;
}

//An exclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
//$49, $45, $55, $4D, $5D, $59, $41, $51
void EOR(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned char constant;

    switch(opcode)
    {
    //Immediate
    case 0x49:
        constant = mode_immediate(&(reg->PC));
        *cpucycles += 2;
        break;

    //Zero Page
    case 0x45:
        constant = readRAM(mode_zeropage(&(reg->PC)));
        *cpucycles += 3;
        break;

    //Zero Page,X
    case 0x55:
        constant = readRAM(mode_zeropage_X(&(reg->PC), reg->X));
        *cpucycles += 4;
        break;

    //Absolute
    case 0x4D:
        constant = readRAM(mode_absolute(&(reg->PC)));
        *cpucycles += 4;
        break;

    //Absolute,X
    case 0x5D:
        constant = readRAM(mode_absolute_X(&(reg->PC), reg->X));
        *cpucycles += 4;
        break;

    //Absolute,Y
    case 0x59:
        constant = readRAM(mode_absolute_Y(&(reg->PC), reg->Y));
        *cpucycles += 4;
        break;

    //Indirect X
    case 0x41:
        constant = readRAM(mode_indexed_indirect(&(reg->PC), reg->X));
        *cpucycles += 6;
        break;

    //Indirect Y
    case 0x51:
        constant = readRAM(mode_indirect_indexed(&reg->PC, reg->Y));
        *cpucycles += 5;
        break;
    }

    reg->A = reg->A ^ constant;

    reg->Z = !(reg->A);
    reg->N = (char)(reg->A) < 0;
}

//An exclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
//$09, $05, $15, $0D, $1D, $19, $01, $11
void ORA(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned char constant;

    switch(opcode)
    {
    //Immediate
    case 0x09:
        constant = mode_immediate(&(reg->PC));
        *cpucycles += 2;
        break;

    //Zero Page
    case 0x05:
        constant = readRAM(mode_zeropage(&(reg->PC)));
        *cpucycles += 3;
        break;

    //Zero Page,X
    case 0x15:
        constant = readRAM(mode_zeropage_X(&(reg->PC), reg->X));
        *cpucycles += 4;
        break;

    //Absolute
    case 0x0D:
        constant = readRAM(mode_absolute(&(reg->PC)));
        *cpucycles += 4;
        break;

    //Absolute,X
    case 0x1D:
        constant = readRAM(mode_absolute_X(&(reg->PC), reg->X));
        *cpucycles += 4;
        break;

    //Absolute,Y
    case 0x19:
        constant = readRAM(mode_absolute_Y(&(reg->PC), reg->Y));
        *cpucycles += 4;
        break;

    //Indirect X
    case 0x01:
        constant = readRAM(mode_indexed_indirect(&(reg->PC), reg->X));
        *cpucycles += 6;
        break;

    //Indirect Y
    case 0x11:
        constant = readRAM(mode_indirect_indexed(&reg->PC, reg->Y));
        *cpucycles += 5;
        break;
    }

    reg->A = reg->A | constant;

    reg->Z = !(reg->A);
    reg->N = (char)(reg->A) < 0;
}

//Used to test if one or more bits are set in a target memory location.
//The mask pattern in A is ANDed with the value in memory to set or clear the zero flag,
//but the result is not kept.
//Bits 7 and 6 of the value from memory are copied into the N and V flags.
//$24, $2C
void BIT(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned char constant;

    switch(opcode)
    {
    //Zero Page
    case 0x24:
        constant = mode_zeropage(&(reg->PC));
        *cpucycles += 3;
        break;

    //Absolute
    case 0x2C:
        constant = mode_absolute(&(reg->PC));
        *cpucycles += 4;
        break;
    }

    reg->Z = !(reg->A & constant);

    reg->V = (constant / 64) % 2;
    reg->N = (constant / 128) % 2;

    //nothing is written to memory
}
