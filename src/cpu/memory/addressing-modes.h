#ifndef ADDRESSING_MODES_H
#define ADDRESSING_MODES_H

unsigned char mode_immediate(unsigned short* PC);
unsigned short mode_zeropage(unsigned short* PC);
unsigned short mode_zeropage_X(unsigned short* PC, unsigned char X);
unsigned short mode_zeropage_Y(unsigned short* PC, unsigned char Y);
char mode_relative(unsigned short* PC);
unsigned short mode_absolute(unsigned short* PC);
unsigned short mode_absolute_X(unsigned short* PC, unsigned char X);
unsigned short mode_absolute_Y(unsigned short* PC, unsigned char Y);
unsigned short mode_indirect(unsigned short* PC);
unsigned short mode_indexed_indirect(unsigned short* PC, unsigned char X);
unsigned short mode_indirect_indexed(unsigned short* PC, unsigned char Y);

#endif // ADDRESSING_MODES_H
