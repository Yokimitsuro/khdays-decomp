/*
 * Ov002_PlotPagePair - draw a byte's two pixels into the page's tile buffer.
 *
 * The low nibble goes at the column asked for and the high nibble at the one
 * after it, so one call paints two pixels side by side. Either half is skipped
 * when it is transparent or would fall off the edge, and the neighbour nibble
 * sharing the byte is always kept.
 *
 * The buffer is fifteen tiles across, tiles are the usual 4bpp 8x8, and the
 * whole thing is bounded to 0x78 by 0x50 pixels.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    char pad000[0x1c];
    u8 *pPixels;
} Ov002PageLayer;

extern Ov002PageLayer *data_ov002_0207f638;

void func_ov002_02064d24(int nX, int nY, int nValue)
{
    Ov002PageLayer *ctx;
    u8 *pByte;
    u8 *pTile;
    int nRow;
    int nSubY;
    int nCell;
    int nShift;
    u16 nMask;

    ctx = data_ov002_0207f638;
    if (nValue == 0) {
        return;
    }
    if (nX + 1 < 0) {
        return;
    }
    if (nX >= 0x78) {
        return;
    }
    if (nY < 0) {
        return;
    }
    if (nY >= 0x50) {
        return;
    }

    nRow = nY / 8;
    nSubY = nY % 8;

    if (nX >= 0) {
        if ((u8)(nValue & 0xf) != 0) {
            nCell = nX % 8 + nSubY * 8;
            nShift = nCell % 2 * 4;
            pTile = &ctx->pPixels[(nRow * 15 + nX / 8) * 32];
            pByte = &pTile[nCell / 2];
            nMask = (u16)(0xf << (nShift ^ 4));
            *pByte = (u8)((*pByte & nMask) | ((nValue & 0xf) << nShift));
        }
    }

    if (nX + 1 >= 0x78) {
        return;
    }
    if ((u8)(nValue >> 4) == 0) {
        return;
    }

    nCell = (nX + 1) % 8 + nSubY * 8;
    nShift = nCell % 2 * 4;
    pTile = &ctx->pPixels[(nRow * 15 + (nX + 1) / 8) * 32];
    pByte = &pTile[nCell / 2];
    nMask = (u16)(0xf << (nShift ^ 4));
    *pByte = (u8)((*pByte & nMask) | ((nValue >> 4) << nShift));
}
