#include "stdbool.h"
#include "cpuinternal.h"
#include "memory/addressing-modes.h"
#include "memory/memory.h"

//ADC and SBC
void cpu_arithmetic(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned char constant;
    bool isSubtract = false;

    switch(opcode)
    {
    //Immediate
    case 0xE9:
        isSubtract = true;
    case 0x69:
        constant = mode_immediate(&(reg->PC));
        *cpucycles += 2;
        break;

    //Zero Page
    case 0xE5:
        isSubtract = true;
    case 0x65:
        constant = readRAM(mode_zeropage(&(reg->PC)));
        *cpucycles += 3;
        break;

    //Zero Page,X
    case 0xF5:
        isSubtract = true;
    case 0x75:
        constant = readRAM(mode_zeropage_X(&(reg->PC), reg->X));
        *cpucycles += 4;
        break;

    //Absolute
    case 0xED:
        isSubtract = true;
    case 0x6D:
        constant = readRAM(mode_absolute(&(reg->PC)));
        *cpucycles += 4;
        break;

    //Absolute,X
    case 0xFD:
        isSubtract = true;
    case 0x7D:
        constant = readRAM(mode_absolute_X(&(reg->PC), reg->X));
        *cpucycles += 4;
        break;

    //Absolute,Y
    case 0xF9:
        isSubtract = true;
    case 0x79:
        constant = readRAM(mode_absolute_Y(&(reg->PC), reg->Y));
        *cpucycles += 4;
        break;

    //Indirect X
    case 0xE1:
        isSubtract = true;
    case 0x61:
        constant = readRAM(mode_indexed_indirect(&(reg->PC), reg->X));
        *cpucycles += 6;
        break;

    //Indirect Y
    case 0xF1:
        isSubtract = true;
    case 0x71:
        constant = readRAM(mode_indirect_indexed(&(reg->PC), reg->Y));
        *cpucycles += 5;
        break;
    }

    //Allows us to use the same adding logic
    if(isSubtract)
        constant = constant ^ 0xFF;

    //short allows us to determine whether the result overflowed
    unsigned short result = reg->A + constant + reg->C;
    //result overflowed if 8th bit is set (count from 0)
    if(result >> 8 & 1)
    {
        reg->C = true;
        reg->V = true;
    }

    //carry bit is discarded
    reg->A = result;

    reg->Z = !(reg->A);
    reg->N = (char)(reg->A) < 0;
}

//TODO: Combine into one function

//Compares the contents of the accumulator with another memory held value and sets the zero and carry flags as appropriate.
//$C9, $C5, $D5, $CD, $DD, $D9, $C1, $D1
//For now, assuming that CMP does an unsigned comparison
void CMP(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned char constant;

    switch(opcode)
    {
    //Immediate
    case 0xC9:
        constant = mode_immediate(&(reg->PC));
        *cpucycles += 2;
        break;

    //Zero Page
    case 0xC5:
        constant = readRAM(mode_zeropage(&(reg->PC)));
        *cpucycles += 3;
        break;

    //Zero Page,X
    case 0xD5:
        constant = readRAM(mode_zeropage_X(&(reg->PC), reg->X));
        *cpucycles += 4;
        break;

    //Absolute
    case 0xCD:
        constant = readRAM(mode_absolute(&(reg->PC)));
        *cpucycles += 4;
        break;

    //Absolute,X
    case 0xDD:
        constant = readRAM(mode_absolute_X(&(reg->PC), reg->X));
        *cpucycles += 4;
        break;

    //Absolute,Y
    case 0xD9:
        constant = readRAM(mode_absolute_Y(&(reg->PC), reg->Y));
        *cpucycles += 4;
        break;

    //Indirect X
    case 0xC1:
        constant = readRAM(mode_indexed_indirect(&(reg->PC), reg->X));
        *cpucycles += 6;
        break;

    //Indirect Y
    case 0xD1:
        constant = readRAM(mode_indirect_indexed(&(reg->PC), reg->Y));
        *cpucycles += 5;
        break;
    }

    reg->C = (reg->A >= constant);
    reg->Z = (reg->A == constant);
    reg->N = (char)(reg->A - constant) < 0;
}

//Compares the contents of the X register with another memory held value and sets the zero and carry flags as appropriate.
//$E0, $E4, $EC
//For now, assuming that CMP does an unsigned comparison
void CPX(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned char constant;

    switch(opcode)
    {
    //Immediate
    case 0xE0:
        constant = mode_immediate(&(reg->PC));
        *cpucycles += 2;
        break;

    //Zero Page
    case 0xE4:
        constant = readRAM(mode_zeropage(&(reg->PC)));
        *cpucycles += 3;
        break;

    //Absolute
    case 0xEC:
        constant = readRAM(mode_absolute(&(reg->PC)));
        *cpucycles += 4;
        break;
    }

    reg->C = (reg->X >= constant);
    reg->Z = (reg->X == constant);
    reg->N = (char)(reg->X - constant) < 0;
}

//Compares the contents of the Y register with another memory held value and sets the zero and carry flags as appropriate.
//$C0, C4, CC
//For now, assuming that CMP does an unsigned comparison
void CPY(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned char constant;

    switch(opcode)
    {
    //Immediate
    case 0xC0:
        constant = mode_immediate(&(reg->PC));
        *cpucycles += 2;
        break;

    //Zero Page
    case 0xC4:
        constant = readRAM(mode_zeropage(&(reg->PC)));
        *cpucycles += 3;
        break;

    //Absolute
    case 0xCC:
        constant = readRAM(mode_absolute(&(reg->PC)));
        *cpucycles += 4;
        break;
    }

    reg->C = reg->Y >= constant;
    reg->Z = reg->Y == constant;
    reg->N = (char)(reg->Y - constant) < 0;
}
