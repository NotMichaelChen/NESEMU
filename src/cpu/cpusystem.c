#include "cpuinternal.h"
#include "memory/memory.h"

//Contains system functions

//The BRK instruction forces the generation of an interrupt request.
//The program counter and processor status are pushed on the stack,
//then the IRQ interrupt vector at $FFFE/F is loaded into the PC,
//and the break flag in the status set to one.
//$00
void BRK(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    //Make sure to preemptively increment the PC so when execution begins PC is at the next instruction
    reg->PC += 1;

    unsigned char lower = reg->PC;
    unsigned char upper = (reg->PC) >> 0b1000;

    //little endian, push LSB first
    stack_push(lower, &(reg->SP));
    stack_push(upper, &(reg->SP));

    unsigned char status = 128 * reg->N +
                            64 * reg->V +
                            16 * reg->B +
                            8 * reg->D +
                            4 * reg->I +
                            2 * reg->Z +
                            1 * reg->C;

    stack_push(status, &(reg->SP));

    reg->PC = (readRAM(0xFFFF) << 8) + readRAM(0xFFFE);

    reg->B = 1;

    *cpucycles += 7;
}

//Causes no changes to the processor other than the normal incrementing of the program counter to the next instruction
//$EA
void NOP(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    *cpucycles += 2;
    reg->PC += 1;
}

//The RTI instruction is used at the end of an interrupt processing routine.
//It pulls the processor flags from the stack followed by the program counter.
//$40
void RTI(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned char status = stack_pop(&(reg->SP));

    reg->N = (status / 128) % 2;
    reg->V = (status / 64) % 2;
    reg->B = (status / 16) % 2;
    reg->D = (status / 8) % 2;
    reg->I = (status / 4) % 2;
    reg->Z = (status / 2) % 2;
    reg->C = status % 2;

    //lower got pushed first, so upper gets popped first
    unsigned char upper = stack_pop(&(reg->SP));
    unsigned char lower = stack_pop(&(reg->SP));

    //No need to increment PC - already did so in BRK
    reg->PC = (upper << 0b1000) + lower;

    *cpucycles += 6;
}
