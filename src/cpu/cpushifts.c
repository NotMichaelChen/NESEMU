
#include "memory/addressing-modes.h"
#include "memory/memory.h"
#include "cpuinternal.h"

//Contains instructions involving logical bit shifts
//TODO: Reduce function count
//TODO: Rename to "cpubitshifts"

//This operation shifts all the bits of the accumulator or memory contents one bit left.
//Bit 0 is set to 0 and bit 7 is placed in the carry flag.
//The effect of this operation is to multiply the memory contents by 2 (ignoring 2's complement considerations),
//setting the carry if the result will not fit in 8 bits.
//$0A, $06, $16, $0E, $1E
void ASL(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address;

    switch(opcode)
    {
    //TODO: clean this up
    //Accumulator
    case 0x0A:
        //Set carry flag to contents of old bit 7
        reg->C = ((reg->A) / 128) % 2;

        reg->A = reg->A << 1;

        reg->Z = !(reg->A);
        reg->N = ((char)(reg->A)) < 0;

        *cpucycles += 2;
        (reg->PC)++;
        return;

    //Zero Page
    case 0x06:
        address = mode_zeropage(&(reg->PC));
        *cpucycles += 5;
        break;

    //Zero Page,X
    case 0x16:
        address = mode_zeropage_X(&(reg->PC), reg->X);
        *cpucycles += 6;
        break;

    //Absolute
    case 0x0E:
        address = mode_absolute(&(reg->PC));
        *cpucycles += 6;
        break;

    //Absolute,X
    case 0x1E:
        address = mode_absolute_X(&(reg->PC), reg->X);
        *cpucycles += 7;
        break;
    }

    unsigned char constant = readRAM(address);

    //Set carry flag to contents of old bit 7
    reg->C = ((constant / 128) % 2);

    constant = constant << 1;

    //For some reason the zero flag looks at A regardless of addressing mode
    reg->Z = !reg->A;
    reg->N = (char)constant < 0;

    writeRAM(constant, address);
}

//Each of the bits in A or M is shift one place to the right.
//The bit that was in bit 0 is shifted into the carry flag. Bit 7 is set to zero.
//$4A, $46, $56, $4E, $5E
void LSR(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address;

    switch(opcode)
    {
    //TODO: clean this up
    //Accumulator
    case 0x4A:
        //Set carry flag to contents of old bit 0
        reg->C = (reg->A) % 2;

        reg->A = (reg->A) >> 1;

        reg->Z = !(reg->A);
        reg->N = (char)(reg->A) < 0;

        *cpucycles += 2;
        (reg->PC)++;
        return;

    //Zero Page
    case 0x46:
        address = mode_zeropage(&(reg->PC));
        *cpucycles += 5;
        break;

    //Zero Page,X
    case 0x56:
        address = mode_zeropage_X(&(reg->PC), (reg->X));
        *cpucycles += 6;
        break;

    //Absolute
    case 0x4E:
        address = mode_absolute(&(reg->PC));
        *cpucycles += 6;
        break;

    //Absolute,X
    case 0x5E:
        address = mode_absolute_X(&(reg->PC), reg->X);
        *cpucycles += 7;
        break;
    }

    unsigned char constant = readRAM(address);

    //Set carry flag to contents of old bit 0
    reg->C = constant % 2;

    constant = constant >> 1;

    //For some reason the zero flag looks at A regardless of addressing mode
    reg->Z = !reg->A;
    reg->N = (char)constant < 0;

    writeRAM(constant, address);
}

//Move each of the bits in either A or M one place to the left.
//Bit 0 is filled with the current value of the carry flag whilst the old bit 7 becomes the new carry flag value.
//$2A, $26, $36, $2E, $3E
void ROL(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address;

    switch(opcode)
    {
    //TODO: clean this up
    //Accumulator
    case 0x2A:
        //Set carry flag to contents of old bit 7
        reg->C = ((reg->A) / 128) % 2;

        reg->A = reg->A << 1;
        //bit 0 become the value of the carry flag
        reg->A = reg->A | reg->C;

        reg->Z = !(reg->A);
        reg->N = (char)(reg->A) < 0;

        *cpucycles += 2;
        (reg->PC)++;
        return;

    //Zero Page
    case 0x26:
        address = mode_zeropage(&(reg->PC));
        *cpucycles += 5;
        break;

    //Zero Page,X
    case 0x36:
        address = mode_zeropage_X(&(reg->PC), reg->X);
        *cpucycles += 6;
        break;

    //Absolute
    case 0x2E:
        address = mode_absolute(&(reg->PC));
        *cpucycles += 6;
        break;

    //Absolute,X
    case 0x3E:
        address = mode_absolute_X(&(reg->PC), reg->X);
        *cpucycles += 7;
        break;
    }

    unsigned char constant = readRAM(address);

    //Set carry flag to contents of old bit 7
    reg->C = (constant / 128) % 2;

    constant = constant << 1;
    //bit 0 becomes the value of the carry flag
    constant = constant | reg->C;

    //For some reason the zero flag looks at A regardless of addressing mode
    reg->Z = !(reg->A);
    reg->N = (char)constant < 0;

    writeRAM(constant, address);
}

//Move each of the bits in either A or M one place to the left.
//Bit 0 is filled with the current value of the carry flag whilst the old bit 7 becomes the new carry flag value.
//$6A, $66, $76, $6E, $7E
void ROR(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address;

    switch(opcode)
    {
    //TODO: clean this up
    //Accumulator
    case 0x6A:
        //Set carry flag to contents of old bit 0
        reg->C = (reg->A) % 2;

        reg->A = (reg->A) >> 1;
        //bit 7 becomes the value of the carry flag
        reg->A = (reg->A) | ((reg->C) * 0b10000000);

        reg->Z = !(reg->A);
        reg->N = (char)(reg->A) < 0;

        *cpucycles += 2;
        (reg->PC)++;
        return;

    //Zero Page
    case 0x66:
        address = mode_zeropage(&(reg->PC));
        *cpucycles += 5;
        break;

    //Zero Page,X
    case 0x76:
        address = mode_zeropage_X(&(reg->PC), reg->X);
        *cpucycles += 6;
        break;

    //Absolute
    case 0x6E:
        address = mode_absolute(&(reg->PC));
        *cpucycles += 6;
        break;

    //Absolute,X
    case 0x7E:
        address = mode_absolute_X(&(reg->PC), reg->X);
        *cpucycles += 7;
        break;
    }

    unsigned char constant = readRAM(address);

    //Set carry flag to contents of old bit 0
    reg->C = (constant / 128) % 2;

    constant = constant >> 1;
    //bit 0 becomes the value of the carry flag
    constant = constant | ((reg->C) * 0b10000000);

    //For some reason the zero flag looks at A regardless of addressing mode
    reg->Z = !(reg->A);
    reg->N = (char)constant < 0;

    writeRAM(constant, address);
}
