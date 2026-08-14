/* Blit one glyph into a column of a pool entry's tile buffer.
 *
 * The glyph sheet lives behind the pool's font descriptor; each glyph is a
 * 0x20-byte tile and the sheet's second half (+0x200) holds the alternate row.
 * A wide column copies all eight words, a narrow one only seven.
 */
typedef unsigned char u8;

typedef struct {
    u8 pad0000[0x10];
    char *pBufferA;             /* +0x10 */
} Ov002PoolEntry;

typedef struct {
    u8 pad0000[0x14];
    char *pTiles;               /* +0x14 */
} Ov002GlyphSheet;

typedef struct {
    u8 pad0000[8];
    Ov002GlyphSheet *pFont;     /* +0x08 */
} Ov002EntryPool;

extern Ov002EntryPool *data_ov002_0207f61c;

void func_ov002_0205979c(Ov002PoolEntry *pEntry, int nColumn, char cGlyph,
                         int bLower, int nWords) {
    int nOffset;
    char *pTiles;
    char *pSrc;
    int i;
    char *pDst;

    pTiles = data_ov002_0207f61c->pFont->pTiles;

    if (bLower != 0) {
        nOffset = 0x200;
    } else {
        nOffset = 0;
    }

    if (nWords != 0) {
        nWords = 8;
    } else {
        nWords = 7;
    }

    pSrc = pTiles + (cGlyph + 1) * 0x20;
    pDst = pEntry->pBufferA;
    pSrc = pSrc + nOffset;
    pDst = pDst + nColumn * 0x20;

    for (i = 0; i < nWords; i++) {
        *(int *)(pDst + i * 4) = *(int *)(pSrc + i * 4);
    }
}
