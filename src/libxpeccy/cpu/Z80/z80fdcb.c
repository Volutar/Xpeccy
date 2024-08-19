#include <stdlib.h>
#include "../cpu.h"
#include "z80_macro.h"

// rlc reg,(iy+e)	[3rd] 4 5add 4rd 3wr
void fdcb00(CPU* cpu) {XDCBR(cpu->iy,z80_rlc,cpu->b);}
void fdcb01(CPU* cpu) {XDCBR(cpu->iy,z80_rlc,cpu->c);}
void fdcb02(CPU* cpu) {XDCBR(cpu->iy,z80_rlc,cpu->d);}
void fdcb03(CPU* cpu) {XDCBR(cpu->iy,z80_rlc,cpu->e);}
void fdcb04(CPU* cpu) {XDCBR(cpu->iy,z80_rlc,cpu->h);}
void fdcb05(CPU* cpu) {XDCBR(cpu->iy,z80_rlc,cpu->l);}
void fdcb06(CPU* cpu) {XDCB(cpu->iy,z80_rlc);}
void fdcb07(CPU* cpu) {XDCBR(cpu->iy,z80_rlc,cpu->a);}
// rrc reg,(iy+e)
void fdcb08(CPU* cpu) {XDCBR(cpu->iy,z80_rrc,cpu->b);}
void fdcb09(CPU* cpu) {XDCBR(cpu->iy,z80_rrc,cpu->c);}
void fdcb0A(CPU* cpu) {XDCBR(cpu->iy,z80_rrc,cpu->d);}
void fdcb0B(CPU* cpu) {XDCBR(cpu->iy,z80_rrc,cpu->e);}
void fdcb0C(CPU* cpu) {XDCBR(cpu->iy,z80_rrc,cpu->h);}
void fdcb0D(CPU* cpu) {XDCBR(cpu->iy,z80_rrc,cpu->l);}
void fdcb0E(CPU* cpu) {XDCB(cpu->iy,z80_rrc);}
void fdcb0F(CPU* cpu) {XDCBR(cpu->iy,z80_rrc,cpu->a);}
// rl reg,(iy+e)
void fdcb10(CPU* cpu) {XDCBR(cpu->iy,z80_rl,cpu->b);}
void fdcb11(CPU* cpu) {XDCBR(cpu->iy,z80_rl,cpu->c);}
void fdcb12(CPU* cpu) {XDCBR(cpu->iy,z80_rl,cpu->d);}
void fdcb13(CPU* cpu) {XDCBR(cpu->iy,z80_rl,cpu->e);}
void fdcb14(CPU* cpu) {XDCBR(cpu->iy,z80_rl,cpu->h);}
void fdcb15(CPU* cpu) {XDCBR(cpu->iy,z80_rl,cpu->l);}
void fdcb16(CPU* cpu) {XDCB(cpu->iy,z80_rl);}
void fdcb17(CPU* cpu) {XDCBR(cpu->iy,z80_rl,cpu->a);}
// rr reg,(iy+e)
void fdcb18(CPU* cpu) {XDCBR(cpu->iy,z80_rr,cpu->b);}
void fdcb19(CPU* cpu) {XDCBR(cpu->iy,z80_rr,cpu->c);}
void fdcb1A(CPU* cpu) {XDCBR(cpu->iy,z80_rr,cpu->d);}
void fdcb1B(CPU* cpu) {XDCBR(cpu->iy,z80_rr,cpu->e);}
void fdcb1C(CPU* cpu) {XDCBR(cpu->iy,z80_rr,cpu->h);}
void fdcb1D(CPU* cpu) {XDCBR(cpu->iy,z80_rr,cpu->l);}
void fdcb1E(CPU* cpu) {XDCB(cpu->iy,z80_rr);}
void fdcb1F(CPU* cpu) {XDCBR(cpu->iy,z80_rr,cpu->a);}
// sla reg,(iy+e)
void fdcb20(CPU* cpu) {XDCBR(cpu->iy,z80_sla,cpu->b);}
void fdcb21(CPU* cpu) {XDCBR(cpu->iy,z80_sla,cpu->c);}
void fdcb22(CPU* cpu) {XDCBR(cpu->iy,z80_sla,cpu->d);}
void fdcb23(CPU* cpu) {XDCBR(cpu->iy,z80_sla,cpu->e);}
void fdcb24(CPU* cpu) {XDCBR(cpu->iy,z80_sla,cpu->h);}
void fdcb25(CPU* cpu) {XDCBR(cpu->iy,z80_sla,cpu->l);}
void fdcb26(CPU* cpu) {XDCB(cpu->iy,z80_sla);}
void fdcb27(CPU* cpu) {XDCBR(cpu->iy,z80_sla,cpu->a);}
// sra reg,(iy+e)
void fdcb28(CPU* cpu) {XDCBR(cpu->iy,z80_sra,cpu->b);}
void fdcb29(CPU* cpu) {XDCBR(cpu->iy,z80_sra,cpu->c);}
void fdcb2A(CPU* cpu) {XDCBR(cpu->iy,z80_sra,cpu->d);}
void fdcb2B(CPU* cpu) {XDCBR(cpu->iy,z80_sra,cpu->e);}
void fdcb2C(CPU* cpu) {XDCBR(cpu->iy,z80_sra,cpu->h);}
void fdcb2D(CPU* cpu) {XDCBR(cpu->iy,z80_sra,cpu->l);}
void fdcb2E(CPU* cpu) {XDCB(cpu->iy,z80_sra);}
void fdcb2F(CPU* cpu) {XDCBR(cpu->iy,z80_sra,cpu->a);}
// sll reg,(iy+e)
void fdcb30(CPU* cpu) {XDCBR(cpu->iy,z80_sll,cpu->b);}
void fdcb31(CPU* cpu) {XDCBR(cpu->iy,z80_sll,cpu->c);}
void fdcb32(CPU* cpu) {XDCBR(cpu->iy,z80_sll,cpu->d);}
void fdcb33(CPU* cpu) {XDCBR(cpu->iy,z80_sll,cpu->e);}
void fdcb34(CPU* cpu) {XDCBR(cpu->iy,z80_sll,cpu->h);}
void fdcb35(CPU* cpu) {XDCBR(cpu->iy,z80_sll,cpu->l);}
void fdcb36(CPU* cpu) {XDCB(cpu->iy,z80_sll);}
void fdcb37(CPU* cpu) {XDCBR(cpu->iy,z80_sll,cpu->a);}
// srl reg,(iy+e)
void fdcb38(CPU* cpu) {XDCBR(cpu->iy,z80_srl,cpu->b);}
void fdcb39(CPU* cpu) {XDCBR(cpu->iy,z80_srl,cpu->c);}
void fdcb3A(CPU* cpu) {XDCBR(cpu->iy,z80_srl,cpu->d);}
void fdcb3B(CPU* cpu) {XDCBR(cpu->iy,z80_srl,cpu->e);}
void fdcb3C(CPU* cpu) {XDCBR(cpu->iy,z80_srl,cpu->h);}
void fdcb3D(CPU* cpu) {XDCBR(cpu->iy,z80_srl,cpu->l);}
void fdcb3E(CPU* cpu) {XDCB(cpu->iy,z80_srl);}
void fdcb3F(CPU* cpu) {XDCBR(cpu->iy,z80_srl,cpu->a);}

// bit n,(iy+e)
void fdcb46(CPU* cpu) {BITX(cpu->iy,0);}
void fdcb4E(CPU* cpu) {BITX(cpu->iy,1);}
void fdcb56(CPU* cpu) {BITX(cpu->iy,2);}
void fdcb5E(CPU* cpu) {BITX(cpu->iy,3);}
void fdcb66(CPU* cpu) {BITX(cpu->iy,4);}
void fdcb6E(CPU* cpu) {BITX(cpu->iy,5);}
void fdcb76(CPU* cpu) {BITX(cpu->iy,6);}
void fdcb7E(CPU* cpu) {BITX(cpu->iy,7);}

// res 0,reg,(iy+e)
void fdcb80(CPU* cpu) {RESXR(cpu->iy,0,cpu->b);}
void fdcb81(CPU* cpu) {RESXR(cpu->iy,0,cpu->c);}
void fdcb82(CPU* cpu) {RESXR(cpu->iy,0,cpu->d);}
void fdcb83(CPU* cpu) {RESXR(cpu->iy,0,cpu->e);}
void fdcb84(CPU* cpu) {RESXR(cpu->iy,0,cpu->h);}
void fdcb85(CPU* cpu) {RESXR(cpu->iy,0,cpu->l);}
void fdcb86(CPU* cpu) {RESX(cpu->iy,0);}
void fdcb87(CPU* cpu) {RESXR(cpu->iy,0,cpu->a);}
// res 1,reg,(iy+e)
void fdcb88(CPU* cpu) {RESXR(cpu->iy,1,cpu->b);}
void fdcb89(CPU* cpu) {RESXR(cpu->iy,1,cpu->c);}
void fdcb8A(CPU* cpu) {RESXR(cpu->iy,1,cpu->d);}
void fdcb8B(CPU* cpu) {RESXR(cpu->iy,1,cpu->e);}
void fdcb8C(CPU* cpu) {RESXR(cpu->iy,1,cpu->h);}
void fdcb8D(CPU* cpu) {RESXR(cpu->iy,1,cpu->l);}
void fdcb8E(CPU* cpu) {RESX(cpu->iy,1);}
void fdcb8F(CPU* cpu) {RESXR(cpu->iy,1,cpu->a);}
// res 2,reg,(iy+e)
void fdcb90(CPU* cpu) {RESXR(cpu->iy,2,cpu->b);}
void fdcb91(CPU* cpu) {RESXR(cpu->iy,2,cpu->c);}
void fdcb92(CPU* cpu) {RESXR(cpu->iy,2,cpu->d);}
void fdcb93(CPU* cpu) {RESXR(cpu->iy,2,cpu->e);}
void fdcb94(CPU* cpu) {RESXR(cpu->iy,2,cpu->h);}
void fdcb95(CPU* cpu) {RESXR(cpu->iy,2,cpu->l);}
void fdcb96(CPU* cpu) {RESX(cpu->iy,2);}
void fdcb97(CPU* cpu) {RESXR(cpu->iy,2,cpu->a);}
// res 3,reg,(iy+e)
void fdcb98(CPU* cpu) {RESXR(cpu->iy,3,cpu->b);}
void fdcb99(CPU* cpu) {RESXR(cpu->iy,3,cpu->c);}
void fdcb9A(CPU* cpu) {RESXR(cpu->iy,3,cpu->d);}
void fdcb9B(CPU* cpu) {RESXR(cpu->iy,3,cpu->e);}
void fdcb9C(CPU* cpu) {RESXR(cpu->iy,3,cpu->h);}
void fdcb9D(CPU* cpu) {RESXR(cpu->iy,3,cpu->l);}
void fdcb9E(CPU* cpu) {RESX(cpu->iy,3);}
void fdcb9F(CPU* cpu) {RESXR(cpu->iy,3,cpu->a);}
// res 4,reg,(iy+e)
void fdcbA0(CPU* cpu) {RESXR(cpu->iy,4,cpu->b);}
void fdcbA1(CPU* cpu) {RESXR(cpu->iy,4,cpu->c);}
void fdcbA2(CPU* cpu) {RESXR(cpu->iy,4,cpu->d);}
void fdcbA3(CPU* cpu) {RESXR(cpu->iy,4,cpu->e);}
void fdcbA4(CPU* cpu) {RESXR(cpu->iy,4,cpu->h);}
void fdcbA5(CPU* cpu) {RESXR(cpu->iy,4,cpu->l);}
void fdcbA6(CPU* cpu) {RESX(cpu->iy,4);}
void fdcbA7(CPU* cpu) {RESXR(cpu->iy,4,cpu->a);}
// res 5,reg,(iy+e)
void fdcbA8(CPU* cpu) {RESXR(cpu->iy,5,cpu->b);}
void fdcbA9(CPU* cpu) {RESXR(cpu->iy,5,cpu->c);}
void fdcbAA(CPU* cpu) {RESXR(cpu->iy,5,cpu->d);}
void fdcbAB(CPU* cpu) {RESXR(cpu->iy,5,cpu->e);}
void fdcbAC(CPU* cpu) {RESXR(cpu->iy,5,cpu->h);}
void fdcbAD(CPU* cpu) {RESXR(cpu->iy,5,cpu->l);}
void fdcbAE(CPU* cpu) {RESX(cpu->iy,5);}
void fdcbAF(CPU* cpu) {RESXR(cpu->iy,5,cpu->a);}
// res 6,reg,(iy+e)
void fdcbB0(CPU* cpu) {RESXR(cpu->iy,6,cpu->b);}
void fdcbB1(CPU* cpu) {RESXR(cpu->iy,6,cpu->c);}
void fdcbB2(CPU* cpu) {RESXR(cpu->iy,6,cpu->d);}
void fdcbB3(CPU* cpu) {RESXR(cpu->iy,6,cpu->e);}
void fdcbB4(CPU* cpu) {RESXR(cpu->iy,6,cpu->h);}
void fdcbB5(CPU* cpu) {RESXR(cpu->iy,6,cpu->l);}
void fdcbB6(CPU* cpu) {RESX(cpu->iy,6);}
void fdcbB7(CPU* cpu) {RESXR(cpu->iy,6,cpu->a);}
// res 7,reg,(iy+e)
void fdcbB8(CPU* cpu) {RESXR(cpu->iy,7,cpu->b);}
void fdcbB9(CPU* cpu) {RESXR(cpu->iy,7,cpu->c);}
void fdcbBA(CPU* cpu) {RESXR(cpu->iy,7,cpu->d);}
void fdcbBB(CPU* cpu) {RESXR(cpu->iy,7,cpu->e);}
void fdcbBC(CPU* cpu) {RESXR(cpu->iy,7,cpu->h);}
void fdcbBD(CPU* cpu) {RESXR(cpu->iy,7,cpu->l);}
void fdcbBE(CPU* cpu) {RESX(cpu->iy,7);}
void fdcbBF(CPU* cpu) {RESXR(cpu->iy,7,cpu->a);}

// set 0,reg,(iy+e)
void fdcbC0(CPU* cpu) {SETXR(cpu->iy,0,cpu->b);}
void fdcbC1(CPU* cpu) {SETXR(cpu->iy,0,cpu->c);}
void fdcbC2(CPU* cpu) {SETXR(cpu->iy,0,cpu->d);}
void fdcbC3(CPU* cpu) {SETXR(cpu->iy,0,cpu->e);}
void fdcbC4(CPU* cpu) {SETXR(cpu->iy,0,cpu->h);}
void fdcbC5(CPU* cpu) {SETXR(cpu->iy,0,cpu->l);}
void fdcbC6(CPU* cpu) {SETX(cpu->iy,0);}
void fdcbC7(CPU* cpu) {SETXR(cpu->iy,0,cpu->a);}
// set 1,reg,(iy+e)
void fdcbC8(CPU* cpu) {SETXR(cpu->iy,1,cpu->b);}
void fdcbC9(CPU* cpu) {SETXR(cpu->iy,1,cpu->c);}
void fdcbCA(CPU* cpu) {SETXR(cpu->iy,1,cpu->d);}
void fdcbCB(CPU* cpu) {SETXR(cpu->iy,1,cpu->e);}
void fdcbCC(CPU* cpu) {SETXR(cpu->iy,1,cpu->h);}
void fdcbCD(CPU* cpu) {SETXR(cpu->iy,1,cpu->l);}
void fdcbCE(CPU* cpu) {SETX(cpu->iy,1);}
void fdcbCF(CPU* cpu) {SETXR(cpu->iy,1,cpu->a);}
// set 2,reg,(iy+e)
void fdcbD0(CPU* cpu) {SETXR(cpu->iy,2,cpu->b);}
void fdcbD1(CPU* cpu) {SETXR(cpu->iy,2,cpu->c);}
void fdcbD2(CPU* cpu) {SETXR(cpu->iy,2,cpu->d);}
void fdcbD3(CPU* cpu) {SETXR(cpu->iy,2,cpu->e);}
void fdcbD4(CPU* cpu) {SETXR(cpu->iy,2,cpu->h);}
void fdcbD5(CPU* cpu) {SETXR(cpu->iy,2,cpu->l);}
void fdcbD6(CPU* cpu) {SETX(cpu->iy,2);}
void fdcbD7(CPU* cpu) {SETXR(cpu->iy,2,cpu->a);}
// set 3,reg,(iy+e)
void fdcbD8(CPU* cpu) {SETXR(cpu->iy,3,cpu->b);}
void fdcbD9(CPU* cpu) {SETXR(cpu->iy,3,cpu->c);}
void fdcbDA(CPU* cpu) {SETXR(cpu->iy,3,cpu->d);}
void fdcbDB(CPU* cpu) {SETXR(cpu->iy,3,cpu->e);}
void fdcbDC(CPU* cpu) {SETXR(cpu->iy,3,cpu->h);}
void fdcbDD(CPU* cpu) {SETXR(cpu->iy,3,cpu->l);}
void fdcbDE(CPU* cpu) {SETX(cpu->iy,3);}
void fdcbDF(CPU* cpu) {SETXR(cpu->iy,3,cpu->a);}
// set 4,reg,(iy+e)
void fdcbE0(CPU* cpu) {SETXR(cpu->iy,4,cpu->b);}
void fdcbE1(CPU* cpu) {SETXR(cpu->iy,4,cpu->c);}
void fdcbE2(CPU* cpu) {SETXR(cpu->iy,4,cpu->d);}
void fdcbE3(CPU* cpu) {SETXR(cpu->iy,4,cpu->e);}
void fdcbE4(CPU* cpu) {SETXR(cpu->iy,4,cpu->h);}
void fdcbE5(CPU* cpu) {SETXR(cpu->iy,4,cpu->l);}
void fdcbE6(CPU* cpu) {SETX(cpu->iy,4);}
void fdcbE7(CPU* cpu) {SETXR(cpu->iy,4,cpu->a);}
// set 5,reg,(iy+e)
void fdcbE8(CPU* cpu) {SETXR(cpu->iy,5,cpu->b);}
void fdcbE9(CPU* cpu) {SETXR(cpu->iy,5,cpu->c);}
void fdcbEA(CPU* cpu) {SETXR(cpu->iy,5,cpu->d);}
void fdcbEB(CPU* cpu) {SETXR(cpu->iy,5,cpu->e);}
void fdcbEC(CPU* cpu) {SETXR(cpu->iy,5,cpu->h);}
void fdcbED(CPU* cpu) {SETXR(cpu->iy,5,cpu->l);}
void fdcbEE(CPU* cpu) {SETX(cpu->iy,5);}
void fdcbEF(CPU* cpu) {SETXR(cpu->iy,5,cpu->a);}
// set 6,reg,(iy+e)
void fdcbF0(CPU* cpu) {SETXR(cpu->iy,6,cpu->b);}
void fdcbF1(CPU* cpu) {SETXR(cpu->iy,6,cpu->c);}
void fdcbF2(CPU* cpu) {SETXR(cpu->iy,6,cpu->d);}
void fdcbF3(CPU* cpu) {SETXR(cpu->iy,6,cpu->e);}
void fdcbF4(CPU* cpu) {SETXR(cpu->iy,6,cpu->h);}
void fdcbF5(CPU* cpu) {SETXR(cpu->iy,6,cpu->l);}
void fdcbF6(CPU* cpu) {SETX(cpu->iy,6);}
void fdcbF7(CPU* cpu) {SETXR(cpu->iy,6,cpu->a);}
// set 7,reg,(iy+e)
void fdcbF8(CPU* cpu) {SETXR(cpu->iy,7,cpu->b);}
void fdcbF9(CPU* cpu) {SETXR(cpu->iy,7,cpu->c);}
void fdcbFA(CPU* cpu) {SETXR(cpu->iy,7,cpu->d);}
void fdcbFB(CPU* cpu) {SETXR(cpu->iy,7,cpu->e);}
void fdcbFC(CPU* cpu) {SETXR(cpu->iy,7,cpu->h);}
void fdcbFD(CPU* cpu) {SETXR(cpu->iy,7,cpu->l);}
void fdcbFE(CPU* cpu) {SETX(cpu->iy,7);}
void fdcbFF(CPU* cpu) {SETXR(cpu->iy,7,cpu->a);}

//====
// opcode fetch doesn't eat 4T?

opCode fdcbTab[256]={
	{0,0,fdcb00,NULL,"rlc b,(iy:5)"},
	{0,0,fdcb01,NULL,"rlc c,(iy:5)"},
	{0,0,fdcb02,NULL,"rlc d,(iy:5)"},
	{0,0,fdcb03,NULL,"rlc e,(iy:5)"},
	{0,0,fdcb04,NULL,"rlc h,(iy:5)"},
	{0,0,fdcb05,NULL,"rlc l,(iy:5)"},
	{0,0,fdcb06,NULL,"rlc (iy:5)"},
	{0,0,fdcb07,NULL,"rlc a,(iy:5)"},

	{0,0,fdcb08,NULL,"rrc b,(iy:5)"},
	{0,0,fdcb09,NULL,"rrc c,(iy:5)"},
	{0,0,fdcb0A,NULL,"rrc d,(iy:5)"},
	{0,0,fdcb0B,NULL,"rrc e,(iy:5)"},
	{0,0,fdcb0C,NULL,"rrc h,(iy:5)"},
	{0,0,fdcb0D,NULL,"rrc l,(iy:5)"},
	{0,0,fdcb0E,NULL,"rrc (iy:5)"},
	{0,0,fdcb0F,NULL,"rrc a,(iy:5)"},

	{0,0,fdcb10,NULL,"rl b,(iy:5)"},
	{0,0,fdcb11,NULL,"rl c,(iy:5)"},
	{0,0,fdcb12,NULL,"rl d,(iy:5)"},
	{0,0,fdcb13,NULL,"rl e,(iy:5)"},
	{0,0,fdcb14,NULL,"rl h,(iy:5)"},
	{0,0,fdcb15,NULL,"rl l,(iy:5)"},
	{0,0,fdcb16,NULL,"rl (iy:5)"},
	{0,0,fdcb17,NULL,"rl a,(iy:5)"},

	{0,0,fdcb18,NULL,"rr b,(iy:5)"},
	{0,0,fdcb19,NULL,"rr c,(iy:5)"},
	{0,0,fdcb1A,NULL,"rr d,(iy:5)"},
	{0,0,fdcb1B,NULL,"rr e,(iy:5)"},
	{0,0,fdcb1C,NULL,"rr h,(iy:5)"},
	{0,0,fdcb1D,NULL,"rr l,(iy:5)"},
	{0,0,fdcb1E,NULL,"rr (iy:5)"},
	{0,0,fdcb1F,NULL,"rr a,(iy:5)"},

	{0,0,fdcb20,NULL,"sla b,(iy:5)"},
	{0,0,fdcb21,NULL,"sla c,(iy:5)"},
	{0,0,fdcb22,NULL,"sla d,(iy:5)"},
	{0,0,fdcb23,NULL,"sla e,(iy:5)"},
	{0,0,fdcb24,NULL,"sla h,(iy:5)"},
	{0,0,fdcb25,NULL,"sla l,(iy:5)"},
	{0,0,fdcb26,NULL,"sla (iy:5)"},
	{0,0,fdcb27,NULL,"sla a,(iy:5)"},

	{0,0,fdcb28,NULL,"sra b,(iy:5)"},
	{0,0,fdcb29,NULL,"sra c,(iy:5)"},
	{0,0,fdcb2A,NULL,"sra d,(iy:5)"},
	{0,0,fdcb2B,NULL,"sra e,(iy:5)"},
	{0,0,fdcb2C,NULL,"sra h,(iy:5)"},
	{0,0,fdcb2D,NULL,"sra l,(iy:5)"},
	{0,0,fdcb2E,NULL,"sra (iy:5)"},
	{0,0,fdcb2F,NULL,"sra a,(iy:5)"},

	{0,0,fdcb30,NULL,"sll b,(iy:5)"},
	{0,0,fdcb31,NULL,"sll c,(iy:5)"},
	{0,0,fdcb32,NULL,"sll d,(iy:5)"},
	{0,0,fdcb33,NULL,"sll e,(iy:5)"},
	{0,0,fdcb34,NULL,"sll h,(iy:5)"},
	{0,0,fdcb35,NULL,"sll l,(iy:5)"},
	{0,0,fdcb36,NULL,"sll (iy:5)"},
	{0,0,fdcb37,NULL,"sll a,(iy:5)"},

	{0,0,fdcb38,NULL,"srl b,(iy:5)"},
	{0,0,fdcb39,NULL,"srl c,(iy:5)"},
	{0,0,fdcb3A,NULL,"srl d,(iy:5)"},
	{0,0,fdcb3B,NULL,"srl e,(iy:5)"},
	{0,0,fdcb3C,NULL,"srl h,(iy:5)"},
	{0,0,fdcb3D,NULL,"srl l,(iy:5)"},
	{0,0,fdcb3E,NULL,"srl (iy:5)"},
	{0,0,fdcb3F,NULL,"srl a,(iy:5)"},

	{0,0,fdcb46,NULL,"bit 0,(iy:5)"},
	{0,0,fdcb46,NULL,"bit 0,(iy:5)"},
	{0,0,fdcb46,NULL,"bit 0,(iy:5)"},
	{0,0,fdcb46,NULL,"bit 0,(iy:5)"},
	{0,0,fdcb46,NULL,"bit 0,(iy:5)"},
	{0,0,fdcb46,NULL,"bit 0,(iy:5)"},
	{0,0,fdcb46,NULL,"bit 0,(iy:5)"},
	{0,0,fdcb46,NULL,"bit 0,(iy:5)"},

	{0,0,fdcb4E,NULL,"bit 1,(iy:5)"},
	{0,0,fdcb4E,NULL,"bit 1,(iy:5)"},
	{0,0,fdcb4E,NULL,"bit 1,(iy:5)"},
	{0,0,fdcb4E,NULL,"bit 1,(iy:5)"},
	{0,0,fdcb4E,NULL,"bit 1,(iy:5)"},
	{0,0,fdcb4E,NULL,"bit 1,(iy:5)"},
	{0,0,fdcb4E,NULL,"bit 1,(iy:5)"},
	{0,0,fdcb4E,NULL,"bit 1,(iy:5)"},

	{0,0,fdcb56,NULL,"bit 2,(iy:5)"},
	{0,0,fdcb56,NULL,"bit 2,(iy:5)"},
	{0,0,fdcb56,NULL,"bit 2,(iy:5)"},
	{0,0,fdcb56,NULL,"bit 2,(iy:5)"},
	{0,0,fdcb56,NULL,"bit 2,(iy:5)"},
	{0,0,fdcb56,NULL,"bit 2,(iy:5)"},
	{0,0,fdcb56,NULL,"bit 2,(iy:5)"},
	{0,0,fdcb56,NULL,"bit 2,(iy:5)"},

	{0,0,fdcb5E,NULL,"bit 3,(iy:5)"},
	{0,0,fdcb5E,NULL,"bit 3,(iy:5)"},
	{0,0,fdcb5E,NULL,"bit 3,(iy:5)"},
	{0,0,fdcb5E,NULL,"bit 3,(iy:5)"},
	{0,0,fdcb5E,NULL,"bit 3,(iy:5)"},
	{0,0,fdcb5E,NULL,"bit 3,(iy:5)"},
	{0,0,fdcb5E,NULL,"bit 3,(iy:5)"},
	{0,0,fdcb5E,NULL,"bit 3,(iy:5)"},

	{0,0,fdcb66,NULL,"bit 4,(iy:5)"},
	{0,0,fdcb66,NULL,"bit 4,(iy:5)"},
	{0,0,fdcb66,NULL,"bit 4,(iy:5)"},
	{0,0,fdcb66,NULL,"bit 4,(iy:5)"},
	{0,0,fdcb66,NULL,"bit 4,(iy:5)"},
	{0,0,fdcb66,NULL,"bit 4,(iy:5)"},
	{0,0,fdcb66,NULL,"bit 4,(iy:5)"},
	{0,0,fdcb66,NULL,"bit 4,(iy:5)"},

	{0,0,fdcb6E,NULL,"bit 5,(iy:5)"},
	{0,0,fdcb6E,NULL,"bit 5,(iy:5)"},
	{0,0,fdcb6E,NULL,"bit 5,(iy:5)"},
	{0,0,fdcb6E,NULL,"bit 5,(iy:5)"},
	{0,0,fdcb6E,NULL,"bit 5,(iy:5)"},
	{0,0,fdcb6E,NULL,"bit 5,(iy:5)"},
	{0,0,fdcb6E,NULL,"bit 5,(iy:5)"},
	{0,0,fdcb6E,NULL,"bit 5,(iy:5)"},

	{0,0,fdcb76,NULL,"bit 6,(iy:5)"},
	{0,0,fdcb76,NULL,"bit 6,(iy:5)"},
	{0,0,fdcb76,NULL,"bit 6,(iy:5)"},
	{0,0,fdcb76,NULL,"bit 6,(iy:5)"},
	{0,0,fdcb76,NULL,"bit 6,(iy:5)"},
	{0,0,fdcb76,NULL,"bit 6,(iy:5)"},
	{0,0,fdcb76,NULL,"bit 6,(iy:5)"},
	{0,0,fdcb76,NULL,"bit 6,(iy:5)"},

	{0,0,fdcb7E,NULL,"bit 7,(iy:5)"},
	{0,0,fdcb7E,NULL,"bit 7,(iy:5)"},
	{0,0,fdcb7E,NULL,"bit 7,(iy:5)"},
	{0,0,fdcb7E,NULL,"bit 7,(iy:5)"},
	{0,0,fdcb7E,NULL,"bit 7,(iy:5)"},
	{0,0,fdcb7E,NULL,"bit 7,(iy:5)"},
	{0,0,fdcb7E,NULL,"bit 7,(iy:5)"},
	{0,0,fdcb7E,NULL,"bit 7,(iy:5)"},

	{0,0,fdcb80,NULL,"res 0,b,(iy:5)"},
	{0,0,fdcb81,NULL,"res 0,c,(iy:5)"},
	{0,0,fdcb82,NULL,"res 0,d,(iy:5)"},
	{0,0,fdcb83,NULL,"res 0,e,(iy:5)"},
	{0,0,fdcb84,NULL,"res 0,h,(iy:5)"},
	{0,0,fdcb85,NULL,"res 0,l,(iy:5)"},
	{0,0,fdcb86,NULL,"res 0,(iy:5)"},
	{0,0,fdcb87,NULL,"res 0,a,(iy:5)"},

	{0,0,fdcb88,NULL,"res 1,b,(iy:5)"},
	{0,0,fdcb89,NULL,"res 1,c,(iy:5)"},
	{0,0,fdcb8A,NULL,"res 1,d,(iy:5)"},
	{0,0,fdcb8B,NULL,"res 1,e,(iy:5)"},
	{0,0,fdcb8C,NULL,"res 1,h,(iy:5)"},
	{0,0,fdcb8D,NULL,"res 1,l,(iy:5)"},
	{0,0,fdcb8E,NULL,"res 1,(iy:5)"},
	{0,0,fdcb8F,NULL,"res 1,a,(iy:5)"},

	{0,0,fdcb90,NULL,"res 2,b,(iy:5)"},
	{0,0,fdcb91,NULL,"res 2,c,(iy:5)"},
	{0,0,fdcb92,NULL,"res 2,d,(iy:5)"},
	{0,0,fdcb93,NULL,"res 2,e,(iy:5)"},
	{0,0,fdcb94,NULL,"res 2,h,(iy:5)"},
	{0,0,fdcb95,NULL,"res 2,l,(iy:5)"},
	{0,0,fdcb96,NULL,"res 2,(iy:5)"},
	{0,0,fdcb97,NULL,"res 2,a,(iy:5)"},

	{0,0,fdcb98,NULL,"res 3,b,(iy:5)"},
	{0,0,fdcb99,NULL,"res 3,c,(iy:5)"},
	{0,0,fdcb9A,NULL,"res 3,d,(iy:5)"},
	{0,0,fdcb9B,NULL,"res 3,e,(iy:5)"},
	{0,0,fdcb9C,NULL,"res 3,h,(iy:5)"},
	{0,0,fdcb9D,NULL,"res 3,l,(iy:5)"},
	{0,0,fdcb9E,NULL,"res 3,(iy:5)"},
	{0,0,fdcb9F,NULL,"res 3,a,(iy:5)"},

	{0,0,fdcbA0,NULL,"res 4,b,(iy:5)"},
	{0,0,fdcbA1,NULL,"res 4,c,(iy:5)"},
	{0,0,fdcbA2,NULL,"res 4,d,(iy:5)"},
	{0,0,fdcbA3,NULL,"res 4,e,(iy:5)"},
	{0,0,fdcbA4,NULL,"res 4,h,(iy:5)"},
	{0,0,fdcbA5,NULL,"res 4,l,(iy:5)"},
	{0,0,fdcbA6,NULL,"res 4,(iy:5)"},
	{0,0,fdcbA7,NULL,"res 4,a,(iy:5)"},

	{0,0,fdcbA8,NULL,"res 5,b,(iy:5)"},
	{0,0,fdcbA9,NULL,"res 5,c,(iy:5)"},
	{0,0,fdcbAA,NULL,"res 5,d,(iy:5)"},
	{0,0,fdcbAB,NULL,"res 5,e,(iy:5)"},
	{0,0,fdcbAC,NULL,"res 5,h,(iy:5)"},
	{0,0,fdcbAD,NULL,"res 5,l,(iy:5)"},
	{0,0,fdcbAE,NULL,"res 5,(iy:5)"},
	{0,0,fdcbAF,NULL,"res 5,a,(iy:5)"},

	{0,0,fdcbB0,NULL,"res 6,b,(iy:5)"},
	{0,0,fdcbB1,NULL,"res 6,c,(iy:5)"},
	{0,0,fdcbB2,NULL,"res 6,d,(iy:5)"},
	{0,0,fdcbB3,NULL,"res 6,e,(iy:5)"},
	{0,0,fdcbB4,NULL,"res 6,h,(iy:5)"},
	{0,0,fdcbB5,NULL,"res 6,l,(iy:5)"},
	{0,0,fdcbB6,NULL,"res 6,(iy:5)"},
	{0,0,fdcbB7,NULL,"res 6,a,(iy:5)"},

	{0,0,fdcbB8,NULL,"res 7,b,(iy:5)"},
	{0,0,fdcbB9,NULL,"res 7,c,(iy:5)"},
	{0,0,fdcbBA,NULL,"res 7,d,(iy:5)"},
	{0,0,fdcbBB,NULL,"res 7,e,(iy:5)"},
	{0,0,fdcbBC,NULL,"res 7,h,(iy:5)"},
	{0,0,fdcbBD,NULL,"res 7,l,(iy:5)"},
	{0,0,fdcbBE,NULL,"res 7,(iy:5)"},
	{0,0,fdcbBF,NULL,"res 7,a,(iy:5)"},

	{0,0,fdcbC0,NULL,"set 0,b,(iy:5)"},
	{0,0,fdcbC1,NULL,"set 0,c,(iy:5)"},
	{0,0,fdcbC2,NULL,"set 0,d,(iy:5)"},
	{0,0,fdcbC3,NULL,"set 0,e,(iy:5)"},
	{0,0,fdcbC4,NULL,"set 0,h,(iy:5)"},
	{0,0,fdcbC5,NULL,"set 0,l,(iy:5)"},
	{0,0,fdcbC6,NULL,"set 0,(iy:5)"},
	{0,0,fdcbC7,NULL,"set 0,a,(iy:5)"},

	{0,0,fdcbC8,NULL,"set 1,b,(iy:5)"},
	{0,0,fdcbC9,NULL,"set 1,c,(iy:5)"},
	{0,0,fdcbCA,NULL,"set 1,d,(iy:5)"},
	{0,0,fdcbCB,NULL,"set 1,e,(iy:5)"},
	{0,0,fdcbCC,NULL,"set 1,h,(iy:5)"},
	{0,0,fdcbCD,NULL,"set 1,l,(iy:5)"},
	{0,0,fdcbCE,NULL,"set 1,(iy:5)"},
	{0,0,fdcbCF,NULL,"set 1,a,(iy:5)"},

	{0,0,fdcbD0,NULL,"set 2,b,(iy:5)"},
	{0,0,fdcbD1,NULL,"set 2,c,(iy:5)"},
	{0,0,fdcbD2,NULL,"set 2,d,(iy:5)"},
	{0,0,fdcbD3,NULL,"set 2,e,(iy:5)"},
	{0,0,fdcbD4,NULL,"set 2,h,(iy:5)"},
	{0,0,fdcbD5,NULL,"set 2,l,(iy:5)"},
	{0,0,fdcbD6,NULL,"set 2,(iy:5)"},
	{0,0,fdcbD7,NULL,"set 2,a,(iy:5)"},

	{0,0,fdcbD8,NULL,"set 3,b,(iy:5)"},
	{0,0,fdcbD9,NULL,"set 3,c,(iy:5)"},
	{0,0,fdcbDA,NULL,"set 3,d,(iy:5)"},
	{0,0,fdcbDB,NULL,"set 3,e,(iy:5)"},
	{0,0,fdcbDC,NULL,"set 3,h,(iy:5)"},
	{0,0,fdcbDD,NULL,"set 3,l,(iy:5)"},
	{0,0,fdcbDE,NULL,"set 3,(iy:5)"},
	{0,0,fdcbDF,NULL,"set 3,a,(iy:5)"},

	{0,0,fdcbE0,NULL,"set 4,b,(iy:5)"},
	{0,0,fdcbE1,NULL,"set 4,c,(iy:5)"},
	{0,0,fdcbE2,NULL,"set 4,d,(iy:5)"},
	{0,0,fdcbE3,NULL,"set 4,e,(iy:5)"},
	{0,0,fdcbE4,NULL,"set 4,h,(iy:5)"},
	{0,0,fdcbE5,NULL,"set 4,l,(iy:5)"},
	{0,0,fdcbE6,NULL,"set 4,(iy:5)"},
	{0,0,fdcbE7,NULL,"set 4,a,(iy:5)"},

	{0,0,fdcbE8,NULL,"set 5,b,(iy:5)"},
	{0,0,fdcbE9,NULL,"set 5,c,(iy:5)"},
	{0,0,fdcbEA,NULL,"set 5,d,(iy:5)"},
	{0,0,fdcbEB,NULL,"set 5,e,(iy:5)"},
	{0,0,fdcbEC,NULL,"set 5,h,(iy:5)"},
	{0,0,fdcbED,NULL,"set 5,l,(iy:5)"},
	{0,0,fdcbEE,NULL,"set 5,(iy:5)"},
	{0,0,fdcbEF,NULL,"set 5,a,(iy:5)"},

	{0,0,fdcbF0,NULL,"set 6,b,(iy:5)"},
	{0,0,fdcbF1,NULL,"set 6,c,(iy:5)"},
	{0,0,fdcbF2,NULL,"set 6,d,(iy:5)"},
	{0,0,fdcbF3,NULL,"set 6,e,(iy:5)"},
	{0,0,fdcbF4,NULL,"set 6,h,(iy:5)"},
	{0,0,fdcbF5,NULL,"set 6,l,(iy:5)"},
	{0,0,fdcbF6,NULL,"set 6,(iy:5)"},
	{0,0,fdcbF7,NULL,"set 6,a,(iy:5)"},

	{0,0,fdcbF8,NULL,"set 7,b,(iy:5)"},
	{0,0,fdcbF9,NULL,"set 7,c,(iy:5)"},
	{0,0,fdcbFA,NULL,"set 7,d,(iy:5)"},
	{0,0,fdcbFB,NULL,"set 7,e,(iy:5)"},
	{0,0,fdcbFC,NULL,"set 7,h,(iy:5)"},
	{0,0,fdcbFD,NULL,"set 7,l,(iy:5)"},
	{0,0,fdcbFE,NULL,"set 7,(iy:5)"},
	{0,0,fdcbFF,NULL,"set 7,a,(iy:5)"},
};
