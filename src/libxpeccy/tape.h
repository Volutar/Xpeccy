#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ZX spectrum signal timings
// 1T ~ 284ns ~ 0.284mks @ 3.51MHz
// pilot	2168T	615 mks
// sync1	667T	189 mks
// sync2	735T	208 mks
// 0		855T	242 mks
// 1		1710T	485 mks
// sync3	954T	270 mks
#define	PILOTLEN	615
#define	SYNC1LEN	189
#define	SYNC2LEN	208
#define	SIGN0LEN	242
#define	SIGN1LEN	485
#define	SYNC3LEN	270

enum {
	TAPE_HEAD = 0,
	TAPE_DATA
};

typedef struct {
	unsigned breakPoint:1;

	int type;
	const char* name;
	int size;
	int time;
	int curtime;
} TapeBlockInfo;

typedef struct {
	int size;		// mks (1e6 = 1sec)
	unsigned char vol;
} TapeSignal;

typedef struct {
	unsigned breakPoint:1;
	unsigned hasBytes:1;
	unsigned isHeader:1;
	unsigned vol;

	int plen;
	int s1len;
	int s2len;
	int len0;
	int len1;
	int pdur;
	int dataPos;
	int sigCount;
	TapeSignal* data;
} TapeBlock;

typedef struct {
	unsigned on:1;
	unsigned rec:1;
	unsigned isData:1;
	unsigned wait:1;
	unsigned blkChange:1;
	unsigned newBlock:1;
	unsigned levRec:1;	// signal to tape
	unsigned oldRec:1;	// previous rec signal

	int time;
	unsigned char volPlay;
	int block;
	int pos;
	int sigLen;
	char* path;
	TapeBlock tmpBlock;
	int blkCount;
	TapeBlock* blkData;
} Tape;

Tape* tapCreate();
void tapDestroy(Tape*);

void tapEject(Tape*);
int tapPlay(Tape*);
void tapRec(Tape*);
void tapStop(Tape*);
void tapRewind(Tape*,int);

void tapSync(Tape*,int);
void tapNextBlock(Tape*);

TapeBlockInfo tapGetBlockInfo(Tape*,int);
int tapGetBlocksInfo(Tape*,TapeBlockInfo*);
int tapGetBlockData(Tape*,int,unsigned char*,int);
int tapGetBlockTime(Tape*,int,int);

void tapAddBlock(Tape*,TapeBlock);
void tapDelBlock(Tape*,int);
void tapSwapBlocks(Tape*,int,int);

void tapAddFile(Tape*,const char*,int,unsigned short,unsigned short,unsigned short,unsigned char*,int);

void blkClear(TapeBlock*);
void blkAddPulse(TapeBlock*, int, int);
void blkAddWave(TapeBlock*, int);
void blkAddByte(TapeBlock*, unsigned char, int, int);
void blkAddPause(TapeBlock*, int);

#ifdef __cplusplus
}
#endif
