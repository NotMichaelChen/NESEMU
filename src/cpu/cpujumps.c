#include "cpuinternal.h"
#include "memory/addressing-modes.h"
#include "memory/memory.h"

//Sets the program counter to the address specified by the operand.
//$4C, $6C
void JMP(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address;

    switch(opcode)
    {
    //Absolute
    case 0x4C:
        address = mode_absolute(&(reg->PC));
        *cpucycles += 3;
        break;

    //Indirect
    case 0x6C:
        address = mode_indirect(&(reg->PC));
        *cpucycles += 5;
        break;
    }

    reg->PC = address;
}

//Pushes the address (minus one) of the return point on to the stack
//and then sets the program counter to the target memory address.
//$20
void JSR(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    unsigned short address = mode_absolute(&(reg->PC));
    //Specifications require a minus one of the return point
    (reg->PC)--;

    unsigned char lower = reg->PC;
    unsigned char upper = (reg->PC) >> 0b1000;

    //little endian, push LSB first
    stack_push(lower, &(reg->SP));
    stack_push(upper, &(reg->SP));

    reg->PC = address;
    *cpucycles += 6;
}

//Used at the end of a subroutine to return to the calling routine.
//It pulls the program counter (minus one) from the stack.
//$60
void RTS(unsigned char opcode, int* cpucycles, struct registers* reg)
{
    //lower got pushed first, so upper gets popped first
    unsigned char upper = stack_pop(&(reg->SP));
    unsigned char lower = stack_pop(&(reg->SP));

    //Plus one to offset the minus one when pushed onto the stack
    reg->PC = (upper << 0b1000) + lower + 1;

    *cpucycles += 6;
}
