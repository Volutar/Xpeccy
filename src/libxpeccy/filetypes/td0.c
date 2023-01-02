#include <stdio.h>
#include "unpackers/lh1/public/lha_decoder.h"

#include "filetypes.h"

#pragma pack(push, 1)

typedef struct {
	char sign[2];	// td | TD
	unsigned char vol;
	unsigned char chk;
	unsigned char ver;	// 0x15
	unsigned char dens;	// 0x00
	unsigned char typ;
	unsigned char flag;	// b7:comment
	unsigned char dos;
	unsigned char sides;
	unsigned short crc;
} td0Head;

typedef struct {
	unsigned short crc;
	unsigned short len;
	unsigned char yr,mon,day,hr,min,sec;
} td0RemHead;

typedef struct {
	unsigned char nsec;
	unsigned char trk;
	unsigned char head;
	unsigned char crc;
} td0TrkHead;

typedef struct {
	unsigned char trk;
	unsigned char head;
	unsigned char sec;
	unsigned char secz;
	unsigned char ctrl;
	unsigned char crc;
} td0SecHead;

#pragma pack(pop)

size_t fGetData(void* buf, size_t len, void* data) {
	if (feof((FILE*)data)) return 0;
	if (buf == NULL) {
		fseek((FILE*)data,len,SEEK_CUR);
	} else {
		fread(buf, len, 1, (FILE*)data);
	}
	return len;
}

size_t lhaDepack(void* buf, size_t len, void* data) {
	size_t res;
	if (buf == NULL) {
		unsigned char* tbuf = (unsigned char*)malloc(len);
		res = lha_decoder_read((LHADecoder*)data, tbuf, len);
		free(tbuf);
	} else {
		res = lha_decoder_read((LHADecoder*)data, buf, len);
	}
	return res;
}

void doTD0(Floppy* flp, size_t(*getBytes)(void*, size_t,void*), void* dptr, int haveRem) {
	td0RemHead rhd;
	td0TrkHead thd;
	td0SecHead shd;
	Sector sec[256];
	//int work = 1;
	int idx;
	int i;
	int icnt;
	unsigned short dlen;
	unsigned char btype;
	unsigned short cnt;
	unsigned char ch1,ch2;
	unsigned char buf[8192];
	unsigned char* ptr;
//	for (i = 0; i < 256; i++) sec[i].data = NULL;
	if (haveRem) {		// skip comment
		getBytes(&rhd, sizeof(td0RemHead), dptr);
#ifdef WORDS_BIG_ENDIAN
		rhd.len = swap16(rhd.len);
#endif
		getBytes(NULL, rhd.len, dptr);
	}
	while (1) {
		idx = 0;
		getBytes(&thd, sizeof(td0TrkHead), dptr);
		//printf("== TRK %i:%i (nsec = %i)\n",thd.trk, thd.head, thd.nsec);
		if (thd.nsec == 0xff) break;
		for (i = 0; i < thd.nsec; i++) {
			//if (!work) break;
			getBytes(&shd, sizeof(td0SecHead), dptr);
			//printf("%i: sec %i (sz = %i, ctrl = %.2X)\n",idx, shd.sec, shd.secz, shd.ctrl);
			sec[idx].trk = shd.trk;
			sec[idx].head = shd.head;
			sec[idx].sec = shd.sec;
			sec[idx].sz = shd.secz;
			sec[idx].type = 0xfb;
			sec[idx].crc = -1;
			//if (!sec[idx].data) sec[idx].data = malloc(8192);
			memset(sec[idx].data, 0x00, 4096);
			if (shd.ctrl & 0x10) {				// empty sector
				idx++;
			} else {
				getBytes(&ch1, 1, dptr);
				getBytes(&ch2, 1, dptr);
				dlen = ch1 | (ch2 << 8);		// data size
				if ((idx > thd.nsec) || (shd.secz & 0xf8)) {
					getBytes(NULL, dlen, dptr);	// skip data
				} else {
					getBytes(&btype, 1, dptr);
					//printf("type = %i\n",btype);
					switch (btype) {
						case 0:
							getBytes(sec[idx].data, dlen-1, dptr);
							idx++;
							break;
						case 1:
							getBytes(&ch1, 1, dptr);
							getBytes(&ch2, 1, dptr);
							cnt = ch1 | (ch2 << 8);
							getBytes(&ch1, 1, dptr);
							getBytes(&ch2, 1, dptr);
							ptr = sec[idx].data;
							while (cnt > 0) {
								*(ptr++) = ch1;
								*(ptr++) = ch2;
								cnt--;
							}
							idx++;
							break;
						case 2:
							ptr = sec[idx].data;
							while (dlen > 1) {
								getBytes(&ch1, 1, dptr);
								getBytes(&ch2, 1, dptr);
								dlen -= 2;
								if (ch1 == 0) {
									getBytes(ptr, ch2, dptr);
									dlen -= ch2;
									ptr += ch2;
								} else {
									icnt = (1 << ch1);
									getBytes(buf, icnt, dptr);
									dlen -= icnt;
									while (ch2 > 0) {
										memcpy(ptr, buf, icnt);
										ptr += icnt;
										ch2--;
									}
								}
							}
							idx++;
							break;
					}
				}
			}
		}
		diskFormTrack(flp, (thd.trk << 1) + thd.head, sec, idx);
	}
	//for (i = 0; i < 256; i++) if (sec[i].data) free(sec[i].data);
}

int loadTD0(Computer* comp, const char* name, int drv) {
	Floppy* flp = comp->dif->fdc->flop[drv & 3];
	FILE* file = fopen(name, "rb");
	if (!file) return ERR_CANT_OPEN;

	int err = ERR_OK;
	td0Head hd;
	fread(&hd, sizeof(td0Head), 1, file);
	if (strncmp(hd.sign, "td", 2) && strncmp(hd.sign, "TD", 2)) {
		err = ERR_TD0_SIGN;
	} else if ((hd.dens != 0) || (hd.sides > 2)) {
		err = ERR_TD0_TYPE;
	} else if (hd.ver < 0x14) {
		err = ERR_TD0_VERSION;
	} else {
		if (strncmp(hd.sign,"TD",2)) {	// 1 on td (packed)
			LHADecoderType* decType;
			LHADecoder* dec = NULL;
			decType = lha_decoder_for_name("-lh1-");
			dec = lha_decoder_new(decType, fGetData, file, -1);
			doTD0(flp, lhaDepack, dec, hd.flag & 0x80);
			lha_decoder_free(dec);
		} else {
			doTD0(flp, fGetData, file, hd.flag & 0x80);
		}
		flp_insert(flp, name);
	}
	fclose(file);
	return err;
}
