#include "cpu/memory/memory.h"

unsigned char* PPUCTRL;
unsigned char* PPUMASK;
unsigned char* PPUSTATUS;
unsigned char* OAMADDR;
unsigned char* OAMDATA;
unsigned char* PPUSCROLL;
unsigned char* PPUADDR;
unsigned char* PPUDATA;

void ppu_init()
{
    unsigned char* regaddr = getPPUregisters();

    PPUCTRL = regaddr;
    PPUMASK = regaddr + 1;
    PPUSTATUS = regaddr + 2;
    OAMADDR = regaddr + 3;
    OAMDATA = regaddr + 4;
    PPUSCROLL = regaddr + 5;
    PPUADDR = regaddr + 6;
    PPUDATA = regaddr + 7;

    *PPUSTATUS = 0xA0;
}
