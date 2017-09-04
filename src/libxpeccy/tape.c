#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tape.h"

#define	FRAMEDOTS	71680
#define SECDOTS		(FRAMEDOTS * 50)
#define	MSDOTS		(FRAMEDOTS / 20)

// NEW STUFF

Tape* tapCreate() {
	Tape* tap = (Tape*)malloc(sizeof(Tape));
	memset(tap,0x00,sizeof(Tape));
	tap->isData = 1;
	tap->path = NULL;
	tap->blkData = NULL;
	tap->tmpBlock.sigData = NULL;
	return tap;
}

void tapDestroy(Tape* tap) {
	if (tap->path) free(tap->path);
	tapEject(tap);
	if (tap->tmpBlock.sigData) free(tap->tmpBlock.sigData);
	free(tap);
}

// blocks

void blkClear(TapeBlock *blk) {
	blk->sigCount = 0;
	if(blk->sigData) free(blk->sigData);
	blk->sigData = NULL;
	blk->breakPoint = 0;
	blk->isHeader = 0;
	blk->hasBytes = 0;
	blk->dataPos = -1;
}

// add signal (1 level change)
void blkAddPulse(TapeBlock* blk, int len) {
	if ((blk->sigCount & 0xffff) == 0) {
		blk->sigData = (int*)realloc(blk->sigData,(blk->sigCount + 0x10000) * sizeof(int));	// allocate mem for next 0x10000 signals
	}
	blk->sigData[blk->sigCount] = len;
	blk->sigCount++;
}

// add pause. duration in ms
void blkAddPause(TapeBlock* blk, int len) {
	blkAddPulse(blk,len * MSDOTS * 2);
}

// add pulse (2 signals)
void blkAddWave(TapeBlock* blk, int len) {
	blkAddPulse(blk,len);
	blkAddPulse(blk,len);
}

// add byte. b0len/b1len = duration of 0/1 bits. When 0, it takes from block signals data
void blkAddByte(TapeBlock* blk, unsigned char data, int b0len, int b1len) {
	if (b0len == 0) b0len = blk->len0;
	if (b1len == 0) b1len = blk->len1;
	for (int msk = 0x80; msk > 0; msk >>= 1) {
		blkAddWave(blk, (data & msk) ? b1len : b0len);
	}
}

int tapGetBlockTime(Tape* tape, int blk, int pos) {
	long totsz = 0;
	int i;
	if (pos < 0) pos = tape->blkData[blk].sigCount;
	for (i = 0; i < pos; i++) totsz += tape->blkData[blk].sigData[i];
	return (totsz / SECDOTS);
}

int tapGetBlockSize(TapeBlock* block) {
	return (((block->sigCount - block->dataPos) >> 4) - 2);
}

unsigned char tapGetBlockByte(TapeBlock* block, int bytePos) {
	unsigned char res = 0x00;
	int i;
	int sigPos = block->dataPos + (bytePos << 4);
	for (i = 0; i < 8; i++) {
		res = res << 1;
		if (sigPos < (int)(block->sigCount - 1)) {
			if ((block->sigData[sigPos] == block->len1) && (block->sigData[sigPos + 1] == block->len1)) {
				res |= 1;
			}
			sigPos += 2;
		}
	}
	return res;
}

int tapGetBlockData(Tape* tape, int blockNum, unsigned char* dst,int maxsize) {
	TapeBlock* block = &tape->blkData[blockNum];
	unsigned int pos = block->dataPos;
	int bytePos = 0;
	do {
		dst[bytePos] = tapGetBlockByte(block,bytePos);
		bytePos++;
		pos += 16;
	} while ((pos < (block->sigCount - 1)) && (bytePos < maxsize));
	return bytePos;
}

char* tapGetBlockHeader(Tape* tap, int blk) {
	char* res = (char*)malloc(16 * sizeof(char));
	TapeBlock* block = &tap->blkData[blk];
	int i;
	if (block->isHeader) {
		if (tapGetBlockByte(block, 1)==0x00) {
			strcpy(res,"Prog:");
		} else {
			strcpy(res,"Code:");
		}
		for(i = 2; i < 12; i++) {
			res[i + 3] = tapGetBlockByte(block,i);
		}
		res[15] = 0x00;
	} else {
		res[0] = 0x00;
	}
	return res;
}

TapeBlockInfo tapGetBlockInfo(Tape* tap, int blk) {
	TapeBlock* block = &tap->blkData[blk];
	TapeBlockInfo inf;
	inf.name = tapGetBlockHeader(tap,blk);
	inf.type = (strcmp(inf.name,"") == 0) ? TAPE_DATA : TAPE_HEAD;
	inf.size = tapGetBlockSize(block);
	inf.time = tapGetBlockTime(tap,blk,-1);
	inf.curtime = (tap->block == blk) ? tapGetBlockTime(tap,blk,tap->pos) : -1;
	inf.breakPoint = block->breakPoint;
	return inf;
}

int tapGetBlocksInfo(Tape* tap, TapeBlockInfo* dst) {
	int cnt = 0;
	int i;
	for (i=0; i < (int)tap->blkCount; i++) {
		dst[cnt] = tapGetBlockInfo(tap,i);
		cnt++;
	}
	return cnt;
}

void tapNormSignals(TapeBlock* block) {
	int low,hi;
	int i;
	for (i = 0; i < (int)block->sigCount; i++) {
		low = block->sigData[i] - 10;
		hi = block->sigData[i] + 10;
		if ((block->plen > low) && (block->plen < hi)) block->sigData[i] = block->plen;
		if ((block->s1len > low) && (block->s1len < hi)) block->sigData[i] = block->s1len;
		if ((block->s2len > low) && (block->s2len < hi)) block->sigData[i] = block->s2len;
		if ((block->len0 > low) && (block->len0 < hi)) block->sigData[i] = block->len0;
		if ((block->len1 > low) && (block->len1 < hi)) block->sigData[i] = block->len1;
	}
}

void tapSwapBlocks(Tape* tap, int b1, int b2) {
	if ((b1 < tap->blkCount) && (b2 < tap->blkCount)) {
		TapeBlock tmp = tap->blkData[b1];
		tap->blkData[b1] = tap->blkData[b2];
		tap->blkData[b2] = tmp;
	}
}

void tapDelBlock(Tape* tap, int blk) {
	if (blk < tap->blkCount) {
		int idx = blk;
		free(tap->blkData[idx].sigData);
		while (idx < tap->blkCount - 1) {
			tap->blkData[idx] = tap->blkData[idx+1];
			idx++;
		}
		tap->blkCount--;
//		tap->data.erase(tap->data.begin() + blk);		// TODO: do
	}
}

// tape

void tapStoreBlock(Tape* tap) {
	unsigned int i,j;
	int same;
	int diff;
	int siglens[10];
	int cnt = 0;
	TapeBlock* tblk = &tap->tmpBlock;
	if (tblk->sigCount == 0) return;
	tblk->sigData[tblk->sigCount-1] = 1000 * MSDOTS;		// last signal is 1 sec (pause)
	for (i=0; i < tblk->sigCount; i++) {
		same = 0;
		for (j = 0; j < cnt; j++) {
			diff = tblk->sigData[i] - siglens[j];
			if ((diff > -20) && (diff < 20)) {
				same = 1;
			}
		}
		if ((same == 0) && (cnt < 10)) {
			siglens[cnt] = tblk->sigData[i];
			cnt++;
		}
	}

//	printf("size: %i\n",cnt);
//	for (i=0; i<cnt;i++) printf("\t%i",siglens[i]);
//	printf("\n");

	if (cnt == 5) {
		siglens[5] = siglens[4];
		siglens[4] = siglens[3];
		siglens[3] = (siglens[3] > 1000) ? SIGN0LEN : SIGN1LEN;
	}
	tblk->breakPoint = 0;
	tblk->hasBytes = 0;
	tblk->isHeader = 0;
	if (cnt == 6) {
		tblk->plen = siglens[0];
		tblk->s1len = siglens[1];
		tblk->s2len = siglens[2];
		if (siglens[4] > siglens[3]) {
			tblk->len0 = siglens[3];
			tblk->len1 = siglens[4];
		} else {
			tblk->len0 = siglens[4];
			tblk->len1 = siglens[3];
		}
		tblk->hasBytes = 1;
	} else {
		tblk->plen = PILOTLEN;
		tblk->s1len = SYNC1LEN;
		tblk->s2len = SYNC2LEN;
		tblk->len0 = SIGN0LEN;
		tblk->len1 = SIGN1LEN;
	}
	tblk->dataPos = -1;
	i = 1;
	while ((i < tblk->sigCount) && (tblk->sigData[i] != tblk->s2len)) i++;
	if (i < tblk->sigCount) tblk->dataPos = i + 1;
	tapNormSignals(tblk);
	if (tblk->dataPos != -1) {
		if (tapGetBlockByte(tblk,0) == 0) {
			tblk->isHeader = 1;
		}
	}
	tapAddBlock(tap,tap->tmpBlock);

	blkClear(tblk);
	tap->wait = 1;
}

void tapEject(Tape* tap) {
	int i;
	tap->isData = 1;
	tap->block = 0;
	tap->pos = 0;
	free(tap->path);
	tap->path = NULL;
	if (tap->blkData) {
		for (i = 0; i < tap->blkCount; i++) {
			if (tap->blkData[i].sigData) free(tap->blkData[i].sigData);
		}
		free(tap->blkData);
	}
	tap->blkCount = 0;
	tap->blkData = NULL;
}

void tapStop(Tape* tap) {
	if (tap->on) {
		tap->on = 0;
		if (tap->rec) tapStoreBlock(tap);
		tap->pos = 0;
	}
}

int tapPlay(Tape* tap) {
	if (tap->block < tap->blkCount) {
		tap->rec = 0;
		tap->on = 1;
	}
	return tap->on;
}

void tapRec(Tape* tap) {
	tap->on = 1;
	tap->rec = 1;
	tap->wait = 1;
	tap->levRec = 0;
	tap->oldRec = tap->levRec;
	tap->tmpBlock.sigCount = 0;
	if (tap->tmpBlock.sigData) free(tap->tmpBlock.sigData);
}

void tapRewind(Tape* tap, int blk) {
	if (blk < tap->blkCount) {
		tap->block = blk;
		tap->pos = 0;
	} else {
		tap->on = 0;
	}
}

// input : tks is time (ns) to sync
void tapSync(Tape* tap,int tks) {
	tks = tks / 280;		// and here is T-states (@ 3.5MHz)
	if (tap->on) {
		if (tap->rec) {
			if (tap->wait) {
				if (tap->oldRec != tap->levRec) {
					tap->oldRec = tap->levRec;
					tap->wait = 0;
					blkAddPulse(&tap->tmpBlock,0);
				}
			} else {
				if (tap->oldRec != tap->levRec) {
					tap->oldRec = tap->levRec;
					blkAddPulse(&tap->tmpBlock,tks);
				} else {
					tap->tmpBlock.sigData[tap->tmpBlock.sigCount - 1] += tks;
				}
				if (tap->tmpBlock.sigData[tap->tmpBlock.sigCount - 1] > FRAMEDOTS) {
					tapStoreBlock(tap);
				}
			}
		} else {
			tap->sigLen -= tks;
			while (tap->sigLen < 1) {
				tap->levPlay ^= 1;
				tap->sigLen += tap->blkData[tap->block].sigData[tap->pos];
				tap->pos++;
				if (tap->pos >= (int)tap->blkData[tap->block].sigCount) {
					tap->blkChange = 1;
					tap->block++;
					tap->pos = 0;
					if (tap->block >= (int)tap->blkCount) {
						tap->on = 0;
					} else {
						if (tap->blkData[tap->block].breakPoint) tap->on = 0;
					}
				}
			}
		}
	} else {
		tap->sigLen -= tks;
		while (tap->sigLen < 1) {
			tap->levPlay ^= 1;
			tap->sigLen += FRAMEDOTS * 25;	// .5 sec
		}
	}
}

void tapNextBlock(Tape* tap) {
	tap->block++;
	tap->blkChange = 1;
	if (tap->block < tap->blkCount) return;
	tap->block = 0;
	tapStop(tap);

}

// add file to tape

TapeBlock makeTapeBlock(unsigned char* ptr, int ln, int hd) {
	TapeBlock nblk;
	int i;
	int pause;
	unsigned char tmp;
	unsigned char crc;
	nblk.plen = PILOTLEN;
	nblk.s1len = SYNC1LEN;
	nblk.s2len = SYNC2LEN;
	nblk.len0 = SIGN0LEN;
	nblk.len1 = SIGN1LEN;
	nblk.breakPoint = 0;
	nblk.hasBytes = 1;
	nblk.isHeader = 0;
	nblk.sigCount = 0;
	nblk.sigData = NULL;
	if (hd) {
		nblk.pdur = 8063;
		pause = 500 * MSDOTS;
		nblk.isHeader = 1;
		crc = 0x00;
	} else {
		nblk.pdur = 3223;
		pause = 1000 * MSDOTS;
		crc = 0xff;
	}
	for (i=0; i < nblk.pdur; i++)
		blkAddPulse(&nblk,nblk.plen);
	if (nblk.s1len != 0)
		blkAddPulse(&nblk,nblk.s1len);
	if (nblk.s2len != 0)
		blkAddPulse(&nblk,nblk.s2len);
	nblk.dataPos = nblk.sigCount;
	blkAddByte(&nblk,crc,0,0);
	for (i=0; i < ln; i++) {
		tmp = *ptr;
		crc ^= tmp;
		blkAddByte(&nblk,tmp,0,0);
		ptr++;
	}
	blkAddByte(&nblk,crc,0,0);
	blkAddPulse(&nblk,SYNC3LEN);
	blkAddPulse(&nblk,pause);
	return nblk;
}

// tapeAddFile(tape, filename, type(0,3 = basic,code), start, lenght, autostart, pointer to data, is header)
void tapAddFile(Tape* tap, const char* nm, int tp, unsigned short st, unsigned short ln, unsigned short as, unsigned char* ptr, int hdr) {
	TapeBlock block;
	if (hdr) {
		unsigned char hdbuf[19];
		hdbuf[0] = tp & 0xff;						// type (0:basic, 3:code)
		memset(&hdbuf[1],10,' ');
		memcpy(&hdbuf[1],nm,(strlen(nm) < 10) ? strlen(nm) : 10);
		if (tp == 0) {
			hdbuf[11] = st & 0xff; hdbuf[12] = ((st & 0xff00) >> 8);
			hdbuf[13] = as & 0xff; hdbuf[14] = ((as & 0xff00) >> 8);
			hdbuf[15] = ln & 0xff; hdbuf[16] = ((ln & 0xff00) >> 8);
		} else {
			hdbuf[11] = ln & 0xff; hdbuf[12] = ((ln & 0xff00) >> 8);
			hdbuf[13] = st & 0xff; hdbuf[14] = ((st & 0xff00) >> 8);
			hdbuf[15] = as & 0xff; hdbuf[16] = ((as & 0xff00) >> 8);
		}
		block = makeTapeBlock(hdbuf,17,1);
		tapAddBlock(tap,block);
		blkClear(&block);
	}
	block = makeTapeBlock(ptr,ln,0);
	tapAddBlock(tap,block);
	blkClear(&block);
}

void tapAddBlock(Tape* tap, TapeBlock block) {
	if (block.sigCount == 0) return;
	TapeBlock blk = block;
	blk.sigData = (int*)malloc(blk.sigCount * sizeof(int));
	memcpy(blk.sigData,block.sigData,blk.sigCount * sizeof(int));

	tap->blkCount++;
	tap->blkData = (TapeBlock*)realloc(tap->blkData,tap->blkCount * sizeof(TapeBlock));
	tap->blkData[tap->blkCount - 1] = blk;

	tap->newBlock = 1;
}
