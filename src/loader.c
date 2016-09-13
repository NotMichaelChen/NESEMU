#include <stdio.h>
#include <stdlib.h>

//Loads a .nes file into memory
int loadROM(char* filename, unsigned char** NESROM, long* ROMsize)
{
    FILE* f = fopen(filename, "rb");
    if(f == NULL)
        return 1;

    //Get size of file by seeking to end and checking index
    fseek(f, 0, SEEK_END);
    *ROMsize = ftell(f);
    rewind(f);

    //Allocate memory to hold the ROM and read the file into memory
    *NESROM = malloc(*ROMsize);
    fread(*NESROM, 1, *ROMsize, f);

    if((*NESROM)[3] != 0x1A)
        return 2;

    fclose(f);

    return 0;
}
