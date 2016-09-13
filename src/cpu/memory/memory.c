#include <stdlib.h>
#include <stdio.h>

const unsigned short Stackoffset = 0x100;
const unsigned short RAMoffset = 0x200;
const unsigned short PPUoffset = 0x2000;
const unsigned short APUoffset = 0x4000;

unsigned char* PRGROM;
unsigned char PRGbanks;
unsigned char* CHRROM;
unsigned char CHRbanks;

unsigned char* RAM;
unsigned char* Stack;
unsigned char* ZeroPage;

unsigned char* PPUregisters;
unsigned char* APUregisters;

int load_CPU_memory(unsigned char* NESROM, long ROMsize)
{
    PRGbanks = NESROM[4];
    if(PRGbanks > 2)
        return 1; //TODO: Support memory mapping later

    CHRbanks = NESROM[5];

    unsigned char controlbyte1 = NESROM[6];
    //Gets bit 2 of the control byte
    unsigned char hasTrainer = ((controlbyte1 / 4) % 2);

    PRGROM = NESROM+16;
    if(hasTrainer)
        PRGROM += 512;

    //16k per PRGbank, offset correctly
    CHRROM = PRGROM + (PRGbanks * 0x4000);

    //Initialize RAM
    RAM = malloc(0x600);
    Stack = malloc(0x100);
    ZeroPage = malloc(0x100);

    PPUregisters = malloc(0x08);
    APUregisters = malloc(0x18);

    return 0;
}

unsigned char readPRGROM(unsigned short address)
{
    return PRGROM[address];
}

//TODO: optimize memory mirroring

unsigned char readRAM(unsigned short address)
{

    if(address < 0x2000)
    {
        //Only look at the first 11 bits of the number
        address &= 0x07FF;

        if(address < 0x100)
            return ZeroPage[address];

        //Just in case
        else if(address < 0x200)
            return Stack[address - Stackoffset];

        else
            return RAM[address - RAMoffset];
    }

    else if(address < 0x4000)
    {
        address = (address & 0x007) + PPUoffset;
        return PPUregisters[address - PPUoffset];
    }

    else
    {
        return APUregisters[address - APUoffset];
    }

    //TODO: figure out what to throw here
    return 0;
}

void writeRAM(unsigned char data, unsigned short address)
{
    if(address < 0x2000)
    {
        //Only look at the first 11 bits of the number
        address &= 0x07FF;

        if(address < 0x100)
            ZeroPage[address] = data;

        //Just in case
        else if(address < 0x200)
            Stack[address - Stackoffset] = data;

        else
            RAM[address - RAMoffset] = data;
    }
    else if(address < 0x4000)
    {
        address = (address & 0x007) + PPUoffset;
        PPUregisters[address - PPUoffset] = data;
    }
    else
    {
        APUregisters[address - APUoffset] = data;
    }
}

void stack_push(unsigned char data, unsigned char* SP)
{
    //Remember, SP points to the next free location, so we should write then decrement
    Stack[*SP] = data;
    (*SP)--;
}

unsigned char stack_pop(unsigned char* SP)
{
    return Stack[++(*SP)];
}
