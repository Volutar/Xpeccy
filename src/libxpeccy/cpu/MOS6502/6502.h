#ifndef _6502_H
#define _6502_H

#include "../cpu.h"

enum {
	M6502_REG_PC = 1,
	M6502_REG_AF,
	M6502_REG_S,
	M6502_REG_X,
	M6502_REG_Y
};

#define MFN 0x80	// negative
#define MFV 0x40	// b7 carry
#define MF5 0x20	// =1
#define MFB 0x10	// break
#define MFD 0x08	// bcd mode
#define MFI 0x04	// interrupt mask
#define MFZ 0x02	// zero
#define MFC 0x01	// carry

void m6502_reset(CPU*);
int m6502_exec(CPU*);
int m6502_int(CPU*);

xMnem m6502_mnem(CPU*, unsigned short, cbdmr, void*);
xAsmScan m6502_asm(const char*, char*);

void m6502_get_regs(CPU*, xRegBunch*);
void m6502_set_regs(CPU*, xRegBunch);

#endif
