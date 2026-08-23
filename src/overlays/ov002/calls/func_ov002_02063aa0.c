/*
 * Ov002_BlitPageIconCell - copy one 4x8 icon half-tile into the page strip.
 *
 * The cell number picks the quadrant of the 2x2 strip, counted back to front, so
 * cell 0 lands in the far corner. The source is the glyph sheet entry the slot
 * names. Both sides are walked a row at a time, two bytes per row, because the
 * rows are half as wide as the tiles they sit in.
 *
 * ARM.
 */

typedef struct {
    char pad000[0x14];
    char *pTiles;
} Ov002GlyphSheet;

typedef struct {
    char pad000[0x1c];
    char *pStrip;
    char pad020[0xc];
    Ov002GlyphSheet *pSheet;
} Ov002PageContext;

extern Ov002PageContext *data_ov002_0207f634;

extern void MIi_CpuCopy16(const void *pSrc, void *pDst, unsigned int nSize);

void func_ov002_02063aa0(int nCell, int nSlot)
{
    Ov002PageContext *ctx;
    int i;
    char *pDst;
    char *pSrc;
    int nRow;

    ctx = data_ov002_0207f634;
    nRow = nCell / 2 + 1;
    pDst = ctx->pStrip + (2 - nRow) * 32 + (1 - nCell % 2) * 2;
    pSrc = ctx->pSheet->pTiles + nSlot * 32;

    for (i = 0; i < 8; i++) {
        MIi_CpuCopy16(pSrc, pDst, 2);
        pSrc += 4;
        pDst += 4;
    }
}
