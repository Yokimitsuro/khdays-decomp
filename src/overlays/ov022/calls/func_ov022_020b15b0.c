/* ov022: split a slot's video memory between its part blocks.
 *
 * Each character slot owns one fixed budget and the mode says how many parts
 * share it. Every row of the table adds up to the same 0x9000: one part takes
 * all of it, two split it 0x5000/0x4000, three take 0x5000/0x2000/0x2000 or
 * 0x4000/0x3000/0x2000. A zero size means that block is unused, and its base is
 * cleared rather than pointed anywhere.
 *
 * The bases are laid end to end, so each block starts where the previous one
 * finished.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct VramBlock {
    u8 pad00[0x2c];
    int nBase;                   /* 0x2c */
    u8 pad30[2];
    u16 nSize;                   /* 0x32 */
    u8 pad34[4];
};

struct VramSlot {
    struct VramBlock aBlock[3];
};

struct VramPool {
    int aBase[4];                /* 0x00 */
    struct VramSlot aSlot[4];    /* 0x10 */
};

struct SizeTable {
    int aRow[5][3];
};

extern const struct SizeTable data_ov022_020b2814;
extern struct VramPool *data_ov022_020b2eb8;

void func_ov022_020b15b0(int nId, int nMode)
{
    struct SizeTable sizes;
    struct VramPool *pPool;
    int nBase;
    int i;
    struct VramBlock *pBlock;

    sizes = data_ov022_020b2814;
    pPool = data_ov022_020b2eb8;
    nBase = pPool->aBase[nId];
    if (nBase == 0) {
        return;
    }
    pBlock = pPool->aSlot[nId].aBlock;
    for (i = 0; i < 3; i++) {
        pBlock->nSize = sizes.aRow[nMode][i];
        if (pBlock->nSize != 0) {
            pBlock->nBase = nBase;
        } else {
            pBlock->nBase = 0;
        }
        nBase += pBlock->nSize;
        pBlock++;
    }
}
