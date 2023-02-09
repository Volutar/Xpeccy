#include "filetypes.h"

int loadTRD(Computer* comp, const char* name, int drv) {
	Floppy* flp = comp->dif->fdc->flop[drv & 3];
	FILE* file = fopen(name, "rb");
	if (!file) return ERR_CANT_OPEN;
	int err = ERR_OK;
	size_t len = fgetSize(file);
	if (((len & 0xff) != 0) || (len == 0) || (len > 0xfe000)) { // 127 tracks
		err = ERR_TRD_LEN;
	} else {
//		diskFormat(flp);
		int trk = 0;
		char buf[0x1000];
		do {
			fread(buf, 0x1000, 1, file);
			flp_format_trk(flp, trk, 16, 256, buf);
			trk++;
		} while  (!feof(file));
		memset(buf, 0, 0x1000);
		while (trk < 168) {
			flp_format_trk(flp, trk, 16, 256, buf);
			trk++;
		}

		flp_insert(flp, name);
	}
	fclose(file);
	return err;
}

int saveTRD(Computer* comp, const char* name, int drv) {
	Floppy* flp = comp->dif->fdc->flop[drv & 3];
	unsigned char syssec[0x100];
	diskGetSectorData(flp, 0, 9, syssec, 256);
	int disksize;
	if (syssec[0xe7] == 0x10)
		disksize = syssec[0xe1] + syssec[0xe2]*16 + syssec[0xe5] + syssec[0xe6]*256;
	else
		disksize = 0;
	if (disksize < 2560) disksize = 2560; //80*2*16
	int tracks = (disksize + 15) / 16;

	unsigned char img[disksize*0x100];
	unsigned char* dptr = img;
	for (int i = 0; i < tracks; i++) {
		for (int j = 1; j < 17; j++) {
			if (!diskGetSectorData(flp, i, j, dptr, 256)) {
				return ERR_TRD_SNF;
			}
			dptr += 256;
		}
	}

	FILE* file = fopen(name, "wb");
	if (!file) return ERR_CANT_OPEN;
	fwrite((char*)img, disksize*0x100, 1, file);
	fclose(file);

	flp_set_path(flp, name);
	flp->changed = 0;
	return ERR_OK;
}
