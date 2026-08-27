/*
 * Plots one pixel on a tiled four-bit canvas.
 *
 * A value of zero is transparent and draws nothing; 0xff stands for the
 * background colour and is written as zero. Anything outside the canvas is
 * dropped.
 *
 * The canvas is a grid of eight by eight tiles laid out one after another,
 * thirty-two bytes each, so the byte holding a pixel is found by picking the
 * tile and then the pixel's own place inside it. The two pixels sharing a byte
 * take the low nibble first and the high nibble second.
 *
 * Five things here are load-bearing rather than style.
 *
 * Both canvas dimensions and both of their times-eight extents are read into
 * variables before the bounds test, so their loads and shifts come out
 * unconditional rather than predicated on the first half of the test.
 *
 * The tile row and column truncate after the shift, not before it. Truncating
 * first costs an extra shift on each.
 *
 * The tile index and the pointer built from it are deliberately not variables.
 * Written out at the store they stay compiler temporaries; declared as locals
 * they claim callee-saved registers and rotate the whole allocation by one.
 *
 * The byte within the tile is reached by dividing the position by two rather
 * than shifting it down. The compiler can see the position is not negative, so
 * the division folds into a single logical shift in the addressing mode, while
 * the shift written out on the same expression emits an arithmetic one.
 *
 * The position inside the tile, by contrast, is a signed remainder, and the
 * rounding correction it carries is in the original.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002TileCanvas {
    char pad000[4];
    u16 wBaseTile;
    u8 nWidthTiles;
    u8 nHeightTiles;
    u8 *pPixels;
} Ov002TileCanvas;

void func_ov002_020662d4(Ov002TileCanvas *pCanvas, int nX, int nY, int nValue)
{
    u16 nPos;
    u16 nShift;
    int nW;
    int nH;
    u16 nW8;
    u16 nH8;

    if (nValue == 0) {
        return;
    }
    if (nValue == 0xff) {
        nValue = 0;
    }

    nW = pCanvas->nWidthTiles;
    nH = pCanvas->nHeightTiles;
    nW8 = (u16)(nW * 8);
    nH8 = (u16)(nH * 8);
    if ((u32)nX >= nW8 || (u32)nY >= nH8) {
        return;
    }

    nPos = (u16)((u16)(nY % 8) * 8 + (u16)(nX % 8));
    nShift = (u16)((nPos % 2) * 4);

    (pCanvas->pPixels + ((u16)((u16)(nY >> 3) * nW + (u16)(nX >> 3))) * 32)[nPos / 2] = (u8)(((pCanvas->pPixels + ((u16)((u16)(nY >> 3) * nW + (u16)(nX >> 3))) * 32)[nPos / 2] & (u16)(0xf << (nShift ^ 4)))
                            | (nValue << nShift));
}
