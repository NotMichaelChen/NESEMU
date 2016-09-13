#include <stdio.h>
#include <stdbool.h>

#include "Memory/memory.h"
#include "Memory/addressing-modes.h"

#include "cpuloadstore.h"
#include "cpuregtrans.h"
#include "cpustack.h"
#include "cpulogical.h"
#include "cpuarithmetic.h"
#include "cpuincrement.h"
#include "cpushifts.h"
#include "cpujumps.h"
#include "cpubranch.h"
#include "cpuflags.h"
#include "cpusystem.h"

#include "cpuinternal.h"

//TODO: address page crossing affecting cpu cycle count
//NOTE: page crossing refers to when there is a carry when adding a register to an address

struct registers reg;

void powerOn()
{
    reg.C = false;
    reg.Z = false;
    reg.I = true;
    reg.D = false;
    reg.B = true;
    reg.V = false;
    reg.N = false;

    reg.A = reg.X = reg.Y = 0;
    reg.SP = 0xFF;
    reg.PC = 0;
}

int executeROM()
{
    int cpucycles = 0;
    while(1)
    {
        unsigned char opcode = readPRGROM(reg.PC);
        printf("%X\n", opcode);
        switch(opcode)
        {
        case 0xA9:
        case 0xA5:
        case 0xB5:
        case 0xAD:
        case 0xBD:
        case 0xB9:
        case 0xA1:
        case 0xB1:
            LDA(opcode, &cpucycles, &reg);
            break;

        case 0xA2:
        case 0xA6:
        case 0xB6:
        case 0xAE:
        case 0xBE:
            LDX(opcode, &cpucycles, &reg);
            break;

        case 0xA0:
        case 0xA4:
        case 0xB4:
        case 0xAC:
        case 0xBC:
            LDY(opcode, &cpucycles, &reg);
            break;

        case 0x85:
        case 0x95:
        case 0x8D:
        case 0x9D:
        case 0x99:
        case 0x81:
        case 0x91:
            STA(opcode, &cpucycles, &reg);
            break;

        case 0x86:
        case 0x96:
        case 0x8E:
            STX(opcode, &cpucycles, &reg);
            break;

        case 0x84:
        case 0x94:
        case 0x8C:
            STY(opcode, &cpucycles, &reg);
            break;

        case 0xAA:
            TAX(opcode, &cpucycles, &reg);
            break;

        case 0xA8:
            TAY(opcode, &cpucycles, &reg);
            break;

        case 0x8A:
            TXA(opcode, &cpucycles, &reg);
            break;

        case 0x98:
            TYA(opcode, &cpucycles, &reg);
            break;

        case 0xBA:
            TSX(opcode, &cpucycles, &reg);
            break;

        case 0x9A:
            TXS(opcode, &cpucycles, &reg);
            break;

        case 0x48:
            PHA(opcode, &cpucycles, &reg);
            break;

        case 0x08:
            PHP(opcode, &cpucycles, &reg);
            break;

        case 0x68:
            PLA(opcode, &cpucycles, &reg);
            break;

        case 0x28:
            PLP(opcode, &cpucycles, &reg);
            break;

        case 0x29:
        case 0x25:
        case 0x35:
        case 0x2D:
        case 0x3D:
        case 0x39:
        case 0x21:
        case 0x31:
            AND(opcode, &cpucycles, &reg);
            break;

        case 0x49:
        case 0x45:
        case 0x55:
        case 0x4D:
        case 0x5D:
        case 0x59:
        case 0x41:
        case 0x51:
            EOR(opcode, &cpucycles, &reg);
            break;

        case 0x09:
        case 0x05:
        case 0x15:
        case 0x0D:
        case 0x1D:
        case 0x19:
        case 0x01:
        case 0x11:
            ORA(opcode, &cpucycles, &reg);
            break;

        case 0x24:
        case 0x2C:
            BIT(opcode, &cpucycles, &reg);
            break;

        //ADC
        case 0x69:
        case 0x65:
        case 0x75:
        case 0x6D:
        case 0x7D:
        case 0x79:
        case 0x61:
        case 0x71:
        //SBC
        case 0xE9:
        case 0xE5:
        case 0xF5:
        case 0xED:
        case 0xFD:
        case 0xF9:
        case 0xE1:
        case 0xF1:
            cpu_arithmetic(opcode, &cpucycles, &reg);
            break;

        case 0xC9:
        case 0xC5:
        case 0xD5:
        case 0xCD:
        case 0xDD:
        case 0xD9:
        case 0xC1:
        case 0xD1:
            CMP(opcode, &cpucycles, &reg);
            break;

        case 0xE0:
        case 0xE4:
        case 0xEC:
            CPX(opcode, &cpucycles, &reg);
            break;

        case 0xC0:
        case 0xC4:
        case 0xCC:
            CPY(opcode, &cpucycles, &reg);
            break;

        case 0xE6:
        case 0xF6:
        case 0xEE:
        case 0xFE:
            INC(opcode, &cpucycles, &reg);
            break;

        case 0xE8:
            INX(opcode, &cpucycles, &reg);
            break;

        case 0xC8:
            INY(opcode, &cpucycles, &reg);
            break;

        case 0xC6:
        case 0xD6:
        case 0xCE:
        case 0xDE:
            DEC(opcode, &cpucycles, &reg);
            break;

        case 0xCA:
            DEX(opcode, &cpucycles, &reg);
            break;

        case 0x88:
            DEY(opcode, &cpucycles, &reg);
            break;

        case 0x0A:
        case 0x06:
        case 0x16:
        case 0x0E:
        case 0x1E:
            ASL(opcode, &cpucycles, &reg);
            break;

        case 0x4A:
        case 0x46:
        case 0x56:
        case 0x4E:
        case 0x5E:
            LSR(opcode, &cpucycles, &reg);
            break;

        case 0x2A:
        case 0x26:
        case 0x36:
        case 0x2E:
        case 0x3E:
            ROL(opcode, &cpucycles, &reg);
            break;

        case 0x6A:
        case 0x66:
        case 0x76:
        case 0x6E:
        case 0x7E:
            ROR(opcode, &cpucycles, &reg);
            break;

        case 0x4C:
        case 0x6C:
            JMP(opcode, &cpucycles, &reg);
            break;

        case 0x20:
            JSR(opcode, &cpucycles, &reg);
            break;

        case 0x60:
            RTS(opcode, &cpucycles, &reg);
            break;

        case 0x90:
        case 0xB0:
        case 0xF0:
        case 0x30:
        case 0xD0:
        case 0x10:
        case 0x50:
        case 0x70:
            cpu_branch(opcode, &cpucycles, &reg);
            break;

        case 0x18:
        case 0xD8:
        case 0x58:
        case 0xB8:
        case 0x38:
        case 0xF8:
        case 0x78:
            cpu_flags(opcode, &cpucycles, &reg);
            break;

        case 0x00:
            BRK(opcode, &cpucycles, &reg);
            break;

        case 0xEA:
            NOP(opcode, &cpucycles, &reg);
            break;

        case 0x40:
            RTI(opcode, &cpucycles, &reg);
            break;

        default:
            return opcode;
        }
    }

    return 0;
}
