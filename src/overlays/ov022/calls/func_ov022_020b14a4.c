/* ov022: take a grid entry for a part model and start it loading.
 *
 * Only a free entry, or one that has finished, can be taken; anything else
 * leaves the caller with nothing. A finished entry is wiped before it is reused.
 *
 * The wipe test runs before the null test, so it reads through a pointer that
 * may be null. That is what the original does.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct GridEntry {
    u8 nFlags;                   /* 0x00 */
    u8 pad01[2];
    u8 nStage;                   /* 0x03 */
    u8 pad04[0x34];
};

struct GridSlot {
    struct GridEntry aEntry[3];
};

struct GridPool {
    int aBase[4];                /* 0x00 */
    struct GridSlot aSlot[4];    /* 0x10 */
};

extern struct GridPool *data_ov022_020b2eb8;
extern void func_ov022_020b11e8(struct GridEntry *pEntry, const char *pPath,
                                u16 *pBlock);

struct GridEntry *func_ov022_020b14a4(const char *pPath, int nId, int nIndex,
                                      u16 *pBlock)
{
    struct GridEntry *pEntry;
    struct GridEntry *pSlot;

    pSlot = &data_ov022_020b2eb8->aSlot[nId].aEntry[nIndex];
    pEntry = 0;
    if (pSlot->nStage == 0 || pSlot->nStage == 3) {
        pEntry = pSlot;
    }
    if (pEntry->nStage == 3) {
        pEntry->nFlags = 0;
        pEntry->nStage = 0;
    }
    if (pEntry != 0) {
        func_ov022_020b11e8(pEntry, pPath, pBlock);
    }
    return pEntry;
}
