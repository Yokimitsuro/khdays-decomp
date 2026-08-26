/*
 * Ov002_PlotPageGlyph - draw one entity's glyph into the page's tile buffer.
 *
 * The glyph is thirty-two bytes, four per row over eight rows, picked out of the
 * layer's character block by the height band the entity is standing in. Every
 * byte carries two pixels and a per-entity mask decides which of them survive.
 *
 * The cell position arrives in 20.12 fixed point, is rounded to whole pixels,
 * pulled back four cells so the glyph sits centred on the cell, and moved into
 * the page's own frame by subtracting the layer origin.
 *
 * Four things here are load-bearing rather than style.
 *
 * The two origin subtractions are separate statements written x then y, and the
 * compiler emits that pair the other way round, which is what puts the y block
 * ahead of the row pointer and the x subtraction behind it. Folding either back
 * into its own coordinate statement reorders the whole window.
 *
 * The row pointer is built before the coordinates, not after them.
 *
 * The pixel rounding subtracts four before the origin, never the other way
 * round: a register subtrahend written first would let the shift ride into an
 * rsb and cost two instructions less than the ROM spends.
 *
 * The masked byte is cast to u8 before the call, which is what emits the
 * truncation after each mask, and the fourth byte is read through its own cursor
 * so the row advance lands after that read.
 *
 * ARM.
 */

typedef unsigned char u8;

typedef struct Ov002PageChars {
    char pad000[0x10];
    int nCharSize;
    void *pCharData;
} Ov002PageChars;

typedef struct Ov002PageLayer {
    char pad000[8];
    int nX;
    int nY;
    char pad010[8];
    Ov002PageChars *pGlyphs;
} Ov002PageLayer;

typedef struct Ov002CellPos {
    int x;
    int y;
} Ov002CellPos;

extern Ov002PageLayer *data_ov002_0207f638;
extern const u8 data_ov002_0207e3fc[];

extern void func_ov002_02064d24(int nX, int nY, int nValue);

void func_ov002_02064f00(int nSelf, const Ov002CellPos *pCell, int nHeight)
{
    Ov002PageLayer *pCtx;
    int nBand;
    u8 bMask;
    int nLine;
    int nDrawX;
    int nDrawY;
    const u8 *pRow;
    const u8 *pTail;

    nBand = ((nHeight + 0x1000) / 0x2000) % 8;
    bMask = data_ov002_0207e3fc[nSelf];
    pCtx = data_ov002_0207f638;
    pRow = (const u8 *)pCtx->pGlyphs->pCharData + nBand * 0x20;
    nDrawX = ((pCell->x + 0x800) >> 12) - 4;
    nDrawY = ((pCell->y + 0x800) >> 12) - 4;
    nDrawX -= pCtx->nX;
    nDrawY -= pCtx->nY;

    for (nLine = 0; nLine < 8; nLine++) {
        func_ov002_02064d24(nDrawX, nDrawY + nLine, (u8)(bMask & pRow[0]));
        func_ov002_02064d24(nDrawX + 2, nDrawY + nLine, (u8)(bMask & pRow[1]));
        func_ov002_02064d24(nDrawX + 4, nDrawY + nLine, (u8)(bMask & pRow[2]));
        pTail = pRow;
        pRow += 4;
        func_ov002_02064d24(nDrawX + 6, nDrawY + nLine, (u8)(bMask & pTail[3]));
    }

}
