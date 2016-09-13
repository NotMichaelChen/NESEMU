#include <stdio.h>
#include <stdlib.h>

#include "loader.h"
#include "CPU/cpu.h"
#include "CPU/Memory/memory.h"

int main()
{
    //Load a ROM dump from the specified .nes file
    unsigned char* NESROM;
    long ROMsize;
    loadROM("Mario Bros. (World).nes", &NESROM, &ROMsize);

    //Load the ROM dump into cpu memory and initialize other parts of memory
    load_CPU_memory(NESROM, ROMsize);

    powerOn();

    int error = executeROM();

    printf("%X", error);

    return 0;
}
