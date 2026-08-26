/*
 * Draws one entity's icon onto the map panel.
 *
 * The caller walks the entity list and, for every entity it wants shown,
 * converts the world position into a screen cell and passes that cell together
 * with the entity's icon kind. The kind selects both the bitmap, through a table
 * of byte offsets into the layer's character block, and the shape drawn: most
 * kinds paint a four-wide, eight-row block centred on the cell, while kind zero
 * and anything past the table paint a two-wide, four-row one sitting two rows
 * higher. Kinds three and seven draw nothing at all.
 *
 * The rows are four bytes apart in both shapes even though the small one reads
 * only two of them.
 *
 * The two origin subtractions are separate statements written after both
 * coordinates rather than folded into them, and that is load-bearing rather than
 * style. Folding either one back into its own coordinate statement swaps the two
 * scratch registers the prologue hands to the offset table and to the second
 * cell word, and moves seven instruction words. The neighbouring glyph plotter
 * in this cluster carries the same shape for the same reason.
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

extern Ov002PageLayer *data_ov002_0207f638;
extern const int data_ov002_0207e404[];

extern void func_ov002_02064d24(int nX, int nY, int nValue);

void func_ov002_020650bc(int nKind, const int *pCell)
{
    Ov002PageLayer *pCtx;
    const u8 *pRow;
    int nDrawX;
    int nDrawY;
    int nLine;

    pCtx = data_ov002_0207f638;
    if (nKind == 3) {
        return;
    }

    pRow = (const u8 *)pCtx->pGlyphs->pCharData + data_ov002_0207e404[nKind];
    nDrawX = (pCell[0] + 0x800) >> 12;
    nDrawY = (pCell[1] + 0x800) >> 12;
    nDrawX -= pCtx->nX;
    nDrawY -= pCtx->nY;

    switch (nKind) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        nDrawY -= 4;
        for (nLine = 0; nLine < 8; nLine++) {
            func_ov002_02064d24(nDrawX - 4, nDrawY + nLine, *pRow++);
            func_ov002_02064d24(nDrawX - 2, nDrawY + nLine, *pRow++);
            func_ov002_02064d24(nDrawX, nDrawY + nLine, *pRow++);
            func_ov002_02064d24(nDrawX + 2, nDrawY + nLine, *pRow++);
        }
        break;
    case 7:
        break;
    default:
        nDrawY -= 2;
        for (nLine = 0; nLine < 4; nLine++) {
            func_ov002_02064d24(nDrawX - 2, nDrawY + nLine, pRow[0]);
            func_ov002_02064d24(nDrawX, nDrawY + nLine, pRow[1]);
            pRow += 4;
        }
        break;
    }
}
