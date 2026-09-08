#pragma thumb on

/* Ov022_SetUpDustEffect -- prepare the dust an actor kicks up.
 *
 * An actor carrying the heavy flag gets the full nine blocks: each is bound to
 * the shared sequence, its three tracks are pointed at the block's own store,
 * and all three are started at the same random point so the nine do not move as
 * one. That actor also gets its own object built from the shared template.
 *
 * The level then picks a row out of the table of nine: the row is copied whole
 * onto the effect, and a heavy actor trebles the row's first figure and forces
 * the second. The table is released again, the effect is switched on and its
 * counter cleared.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

#define FLAGS_BIT36 0x1000000000ULL

#define EFFECT_ON 1
#define EFFECT_HEAVY 4
#define BLOCKS 9
#define MIN_LEVEL 5
#define MAX_LEVEL 9
#define ROW_STRIDE 0x14
#define SPIN_RANGE 0xf000
#define HEAVY_SECOND 0x666

struct SeqBlock {
    u8 pad000[0xe0];
    u8 track[0x28];                  /* 0x0e0 */
};

struct DustRow {
    short nFirst;                    /* 0x00 */
    short nSecond;                   /* 0x02 */
    int nField04;                    /* 0x04 */
    int nField08;                    /* 0x08 */
    int nField0c;                    /* 0x0c */
    int nField10;                    /* 0x10 */
};

struct ObjectParams {
    int aWords[5];
};

struct Effect {
    u8 nFlags;                       /* 0x000 */
    u8 pad001[3];
    struct SeqBlock aBlocks[BLOCKS]; /* 0x004 */
    void *pObject;                   /* 0x94c */
    u8 pad950[8];
    int nField958;                   /* 0x958 */
    u8 pad95c[4];
    struct DustRow row;              /* 0x960 */
};

struct Owner {
    u64 nFlags;                      /* 0x00 */
};

extern u8 data_ov022_020b2bcc[];
extern const struct ObjectParams data_ov022_020b24fc;
extern u8 data_ov022_020b2930[];
extern u8 data_ov022_020b2bdc[];

extern int func_0203084c(void);
extern int func_02005418(int nValue, int nScale);
extern void func_0202a634(struct SeqBlock *pBlock, void *pSeq, int nMode,
                          int nGroup);
extern void func_0202accc(struct SeqBlock *pBlock, int nTrack, u8 *pStore,
                          int nArg);
extern void func_01fff774(struct SeqBlock *pBlock, int nTrack, int nFrame);
extern void *func_02023930(void *pClass, struct ObjectParams *pParams);
extern void *func_0201ef9c(void *pFile, int nKind);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);

void func_ov022_02092e8c(struct Effect *pEffect, int nLevel,
                         struct Owner *pOwner)
{
    struct ObjectParams params;
    struct SeqBlock *pBlock;
    struct DustRow *pRow;
    struct DustRow *pDst;
    void *pTable;
    int nIndex;
    int nFrame;

    if ((pOwner->nFlags & FLAGS_BIT36) != 0) {
        pEffect->nFlags |= EFFECT_HEAVY;
        if (nLevel < MIN_LEVEL) {
            nLevel = MIN_LEVEL;
        }
        nIndex = 0;
        pBlock = pEffect->aBlocks;
        do {
            nFrame = func_02005418(func_0203084c(), SPIN_RANGE);
            func_0202a634(pBlock, data_ov022_020b2bcc, 1, 0);
            func_0202accc(pBlock, 0, pBlock->track, 0);
            func_0202accc(pBlock, 2, pBlock->track, 0);
            func_0202accc(pBlock, 3, pBlock->track, 0);
            func_01fff774(pBlock, 0, nFrame);
            func_01fff774(pBlock, 2, nFrame);
            func_01fff774(pBlock, 3, nFrame);
            nIndex++;
            pBlock++;
        } while (nIndex < BLOCKS);
        params = data_ov022_020b24fc;
        pEffect->pObject = func_02023930(data_ov022_020b2930, &params);
    }
    if (nLevel > 0) {
        pTable = func_0201ef9c(data_ov022_020b2bdc, 6);
        if (nLevel > MAX_LEVEL) {
            nLevel = MAX_LEVEL;
        }
        pRow = (struct DustRow *)((u8 *)pTable + (nLevel - 1) * ROW_STRIDE);
        pEffect->row = *pRow;
        if ((pOwner->nFlags & FLAGS_BIT36) != 0) {
            pDst = &pEffect->row;
            pDst->nFirst = pDst->nFirst * 3;
            pEffect->row.nSecond = HEAVY_SECOND;
        }
        NNSi_FndFreeFromDefaultHeap(pTable);
        pEffect->nFlags |= EFFECT_ON;
        pEffect->nField958 = 0;
    }
}
