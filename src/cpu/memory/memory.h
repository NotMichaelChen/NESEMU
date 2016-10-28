#ifndef MEMORY_H
#define MEMORY_H

int load_CPU_memory(unsigned char* NESROM, long ROMsize);

unsigned char readPRGROM(unsigned short address);

unsigned char readRAM(unsigned short address);
void writeRAM(unsigned char data, unsigned short address);

void stack_push(unsigned char data, unsigned char* SP);
unsigned char stack_pop(unsigned char* SP);

unsigned char* getPPUregisters();

#endif // MEMORY_H
