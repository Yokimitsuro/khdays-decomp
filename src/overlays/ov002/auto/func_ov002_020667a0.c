/*
 * Ov002_FillScreenBlock - lay a tile canvas out on a background screen.
 *
 * The canvas' tiles are numbered from its own base, row by row, and every
 * screen entry is stamped with the palette the caller names. The block starts
 * at the column and row given and is as big as the canvas says it is.
 *
 * The pragma keeps the row offset recomputed from the row counter instead of
 * being carried in a scaled register, which is how the original was built.
 *
 * ARM.
 */

#pragma opt_strength_reduction off

typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    char pad000[4];
    u16 wBaseTile;
    u8 nWidthTiles;
    u8 nHeightTiles;
} Ov002TileCanvas;

void func_ov002_020667a0(Ov002TileCanvas *pCanvas, u16 *pScreen, int nCol,
                         int nRow, u8 nPal)
{
    int i;
    int j;

    for (j = 0; j < pCanvas->nHeightTiles; j++) {
        for (i = 0; i < pCanvas->nWidthTiles; i++) {
            pScreen[nCol + nRow * 32 + i] =
                (u16)(pCanvas->wBaseTile + j * pCanvas->nWidthTiles + i) |
                (nPal << 12);
        }
        nRow++;
    }
}
