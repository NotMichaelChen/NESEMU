#include "memory.h"

//Returns a char instead of an address, since there's no RAM address to read from
unsigned char mode_immediate(unsigned short* PC)
{
    unsigned char result = readPRGROM(*PC+1);
    *PC += 2;
    return result;
}

unsigned short mode_zeropage(unsigned short* PC)
{
    //This mode only can access zero page memory, so a char is large enough
    unsigned char address = readPRGROM(*PC+1);
    *PC += 2;
    return address;
}

unsigned short mode_zeropage_X(unsigned short* PC, unsigned char X)
{
    //This mode only can access zero page memory, so a char is large enough
    unsigned char address = readPRGROM(*PC+1) + X;
    *PC += 2;
    return address;
}

unsigned short mode_zeropage_Y(unsigned short* PC, unsigned char Y)
{
    //This mode only can access zero page memory, so a char is large enough
    unsigned char address = readPRGROM(*PC+1) + Y;
    *PC += 2;
    return address;
}

//Used by branch functions to move PC by a relative amount
//Must be signed to allow for negative PC movement
//(this is because PC is a short while result is a char)
char mode_relative(unsigned short* PC)
{
    //Page crossing handled by calling function
    char result = readPRGROM(*PC+1);
    *PC += 2;
    return result;
}

unsigned short mode_absolute(unsigned short* PC)
{
    unsigned short address = (readPRGROM(*PC+2) << 8) + readPRGROM(*PC+1);
    *PC += 3;
    return address;
}

unsigned short mode_absolute_X(unsigned short* PC, int* cpucycles, unsigned char X)
{
    unsigned char upper = readPRGROM(*PC+2);
    unsigned short address = (upper << 8) + readPRGROM(*PC+1) + X;
    *PC += 3;
    //Page crossing
    if(address >> 0b1000 != upper)
        *cpucycles += 1;
    return address;
}

unsigned short mode_absolute_Y(unsigned short* PC, int* cpucycles, unsigned char Y)
{
    unsigned char upper = readPRGROM(*PC+2);
    unsigned short address = (upper << 8) + readPRGROM(*PC+1) + Y;
    *PC += 3;
    //Page crossing
    if(address >> 0b1000 != upper)
        *cpucycles += 1;
    return address;
}

unsigned short mode_indirect(unsigned short* PC)
{
    unsigned short ramaddress = (readPRGROM(*PC+2) << 8) + readPRGROM(*PC+1);
    unsigned short address = (readRAM(ramaddress+2) << 8) + readRAM(ramaddress+1);
    *PC += 3;
    return address;
}

//Indirect X
unsigned short mode_indexed_indirect(unsigned short* PC, unsigned char X)
{
    unsigned short ramaddress = readPRGROM(*PC+1) + X;
    unsigned short address = (readRAM(ramaddress+2) << 8) + readRAM(ramaddress+1);
    *PC += 2;
    return address;
}

//Indirect Y
unsigned short mode_indirect_indexed(unsigned short* PC, int* cpucycles, unsigned char Y)
{
    unsigned short ramaddress = readPRGROM(*PC+1);
    unsigned char upper = readRAM(ramaddress+2);
    unsigned short address = (upper << 8) + readRAM(ramaddress+1) + Y;
    //Page crossing
    if(address >> 0b1000 != upper)
        *cpucycles += 1;
    *PC += 2;
    return address;
}
