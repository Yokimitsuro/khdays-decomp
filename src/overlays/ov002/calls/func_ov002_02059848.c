/* Build the entry's OAM row and hand it to the sprite layer.
 *
 * One halfword per tile, numbered from the entry's own tile base and tagged with
 * palette 7. The row is placed by column and line, counting back from the
 * entry's width so it grows leftwards.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad0000[1];
    u8 bWidth;                          /* +0x01 */
    u8 pad0002[6];
    int nTarget;                        /* +0x08 */
    int nSize;                          /* +0x0c */
    u8 pad0010[4];
    u16 *pBufferB;                      /* +0x14 */
} Ov002PoolEntry;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int nSize);
extern void func_ov002_02053c18(int nTarget, int nOffset, u16 *pSrc, int nSize);

void func_ov002_02059848(Ov002PoolEntry *pEntry, int nColumn, int nRow,
                         int nTarget) {
    int nTileBase = pEntry->nTarget + 0x1f;
    int nTiles = (unsigned int)(pEntry->nSize + 0x1f) >> 5 & 0xff;
    int nBytes = nTiles * 2;
    int i;
    int nCell;
    int nLine;

    pEntry->pBufferB = (u16 *)NNSi_FndAllocFromDefaultExpHeap(nBytes);

    for (i = 0; i < nTiles; i++) {
        pEntry->pBufferB[i] =
            i + ((unsigned int)nTileBase >> 5) | 0x7000;
    }

    nCell = nColumn - pEntry->bWidth - 1;
    func_ov002_02053c18(nTarget, nCell * 2 + nRow * 0x40, pEntry->pBufferB, nBytes);
}
