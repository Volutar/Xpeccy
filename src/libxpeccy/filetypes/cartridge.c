#include "filetypes.h"

void detectType(xCartridge* slot) {
	int test, radr, adr;
	sltSetMaper(slot, slot->mapType);
	if (slot->memMask < 0x8000) {
		sltSetMaper(slot, MAP_MSX_NOMAPPER);		// 16/32K : no mapper
	} else {
		for (adr = 0; adr < 0x4000; adr++) {
			radr = adr & slot->memMask;
			test = slot->data[radr++] << 16;
			test |= slot->data[radr++] << 8;
			test |= slot->data[radr];
			if ((test == 0x320050) || (test == 0x3200b0)) {
				sltSetMaper(slot, MAP_MSX_KONAMI5);
				break;
			} else if ((test == 0x320068) || (test == 0x320078)) {
				sltSetMaper(slot, MAP_MSX_ASCII8);
				break;
			} else if (test == 0x3200a0) {
				sltSetMaper(slot, MAP_MSX_KONAMI4);
				break;
			}
		}
	}
}

int loadSlot(xCartridge* slot, const char* name) {
	FILE* file = fopen(name, "rb");
	if (!file) return ERR_CANT_OPEN;
	fseek(file,0,SEEK_END);
	size_t siz = ftell(file);
	rewind(file);
	int err = ERR_OK;
	if (siz > (4 * 1024 * 1024)) {
		err = ERR_RAW_LONG;
		fclose(file);
	} else {
		int tsiz = 1;
		while (tsiz < siz) {tsiz <<= 1;}		// get nearest 2^n >= siz
		slot->data = realloc(slot->data, tsiz);
		slot->memMask = tsiz - 1;
		strcpy(slot->name, name);
		fread(slot->data, tsiz, 1, file);
		for (tsiz = 0; tsiz < 8; tsiz++) {
			slot->memMap[tsiz] = 0;
		}
		detectType(slot);
		fclose(file);
		char rname[FILENAME_MAX];
		strcpy(rname, name);
		strcat(rname, ".ram");
		file = fopen(rname, "rb");
		if (file) {
			fread(slot->ram, 0x8000, 1, file);
			fclose(file);
		} else {
			memset(slot->ram, 0x00, 0x8000);
		}
		err = ERR_OK;
	}
	return err;
}
