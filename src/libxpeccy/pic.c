// https://wiki.osdev.org/PIC
// http://www.brokenthorn.com/Resources/OSDevPic.html

#include "pic.h"

void pic_reset(PIC* pic) {
	pic->imr = 0xff;
	pic->isr = 0;
	pic->irr = 0;
	pic->oint = 0;
}

void pic_int(PIC* pic, int num) {
	int mask = (1 << (num & 7));
	pic->irr |= mask;
	mask &= ~pic->imr;
	mask &= ~pic->isr;
	if (!mask) return;
	unsigned char msk = 0x01;			// TODO: priority
	pic->vec = pic->icw2 & 0xf8;
	for (int i = 0; i < 8; i++) {
		if (pic->isr & msk) {
			pic->oint = 0;
			i = 8;
		} else if ((pic->isr & msk) && !(pic->imr & msk)) {
			// on INTA set isr bit, reset pic->oint
			if (pic->master && (pic->icw3 & msk))
				pic->vec = -1;		// it means vector is given by slave controller
			pic->mask = msk;
			pic->oint = 1;
			i = 8;
		} else {
			pic->vec++;
			if (!(pic->vec & 7)) pic->vec = 0;
			msk <<= 1;
			if (!msk)
				msk = 0x01;
		}
	}
}

// return vector for int with hightst priority with bits irr=1 imr=0 & isr=0
int pic_ack(PIC* pic) {
	pic->isr |= pic->mask;	// not set on AEOI mode
	pic->oint = 0;
	return pic->vec;
}

void pic_eoi(PIC* pic) {
	pic->isr &= ~pic->mask;
	pic->irr &= ~pic->mask;
}

// rd/wr

void pic_wr(PIC* pic, int adr, int data) {
	if (adr & 1) {		// wr data
		switch(pic->mode) {
			case PIC_OCWX:
				pic->imr = data & 0xff;
				break;
			case PIC_ICW2:
				pic->icw2 = data & 0xff;
				if (data & 2) {
					pic->icw3 = 0;
					pic->mode = (pic->icw1 & 1) ? PIC_ICW4 : PIC_OCWX;
				} else {
					pic->mode = PIC_ICW3;
				}
				break;
			case PIC_ICW3:
				pic->icw3 = data & 0xff;
				pic->mode = (pic->icw1 & 1) ? PIC_ICW4 : PIC_OCWX;
				break;
			case PIC_ICW4:
				pic->icw4 = data & 0xff;
				pic->mode = PIC_OCWX;
				break;
		}
	} else {		// wr command
		if (data & 0x10) {		// init
			pic->icw1 = data & 0xff;
			pic->mode = PIC_ICW2;
		} else if (data & 0x08) {	// ocw

		}
	}
}

int pic_rd(PIC* pic, int adr) {
	int res = -1;
	if (adr & 1) {	// rd data
		if (pic->mode == PIC_OCWX)
			res = pic->imr;
	} else {	// rd command
	}
	return res;
}
