/* Render a signed value into a pool entry's tile buffer, right-aligned, then
 * hand the buffer to the graphics queue.
 *
 * Kinds 0 and 4 size the field from the value itself and clamp it to five
 * digits; every other kind uses the entry's own width. Kind 0 also draws a sign
 * glyph. Digits are emitted least-significant first, walking left, and whatever
 * is left of the field is blanked with the -1 glyph. Zero is a special case:
 * one zero digit plus one blank, and no sign.
 */
typedef unsigned char u8;

typedef struct {
    u8 bKey;                /* +0x00 */
    u8 bWidth;              /* +0x01 */
    u8 pad0002[2];
    int nKind;              /* +0x04 */
    int nTarget;            /* +0x08 */
    int nSize;              /* +0x0c */
    void *pBufferA;         /* +0x10 */
} Ov002PoolEntry;

typedef struct {
    u8 pad0000[0xc];
    int nQueue;             /* +0x0c */
} Ov002EntryPool;

extern Ov002EntryPool *data_ov002_0207f61c;

extern void MI_CpuFill8(void *pDest, int nValue, unsigned int nSize);
extern int func_ov002_02059810(int nValue);
extern void func_ov002_0205979c(Ov002PoolEntry *pEntry, int nColumn, char cGlyph,
                                int nFlagA, int nFlagB);
extern void GFXi_EnqueueCommand(int nQueue, int nTarget, void *pSrc, int nSize);

void func_ov002_0205a248(Ov002PoolEntry *pEntry, int nValue) {
    Ov002EntryPool *pPool = data_ov002_0207f61c;
    int bFlush = 1;
    int nCol;
    int nAbs;

    if (pEntry != 0) {
        MI_CpuFill8(pEntry->pBufferA, 0, pEntry->nSize);

        if (nValue < 0) {
            nAbs = -nValue;
        } else {
            nAbs = nValue;
        }

        if (pEntry->nKind == 0 || pEntry->nKind == 4) {
            if (nAbs > 99999) {
                nAbs = 99999;
            }
            nCol = func_ov002_02059810(nAbs);
            bFlush = 1;
        } else {
            nCol = pEntry->bWidth - 1;
        }

        if (nAbs == 0) {
            func_ov002_0205979c(pEntry, nCol, 0, 0, bFlush);
            func_ov002_0205979c(pEntry, nCol - 1, -1, 0, bFlush);
        } else {
            while (nAbs > 0) {
                func_ov002_0205979c(pEntry, nCol, nAbs % 10, 0, bFlush);
                nAbs = nAbs / 10;
                nCol--;
            }
            if (pEntry->nKind == 0) {
                func_ov002_0205979c(pEntry, nCol, nValue > 0 ? 0xc : 0xd, 0, bFlush);
                nCol--;
            }
            while (nCol >= 0) {
                func_ov002_0205979c(pEntry, nCol, -1, 0, bFlush);
                nCol--;
            }
        }

        GFXi_EnqueueCommand(pPool->nQueue, pEntry->nTarget, pEntry->pBufferA,
                            pEntry->nSize);
    }
}
