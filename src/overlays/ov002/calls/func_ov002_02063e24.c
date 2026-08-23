/*
 * Ov002_DrawPageNeedle - draw the sliding needle over the page's two tiles.
 *
 * The needle is eight columns of a nibble bitmap slid to wherever the value
 * puts it; every column outside that window, and every hole inside it, falls
 * back to the plain shade. Both tiles are filled a nibble at a time.
 *
 * The screen entries that carry the needle follow it a whole tile at a time,
 * and the two finished tiles are enqueued once.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    char pad000[0x14];
    u8 *pTiles;
} Ov002GlyphSheet;

typedef struct {
    char pad000[0x14];
    u8 *pNeedle;
    char pad018[0x10];
    Ov002GlyphSheet *pShape;
} Ov002PageContext;

extern Ov002PageContext *data_ov002_0207f634;

extern void GFXi_EnqueueCommand(int nCmd, int nDest, int nSrc, int nSize);
extern int func_ov002_02053bb8(int nId);
extern void func_ov002_02063bf8(u8 *pBuffer, int nColumn, int nRow, int nValue);

void func_ov002_02063e24(int nValue)
{
    Ov002PageContext *ctx;
    u16 *pScreen;
    u8 *pShape;
    u8 *pDest;
    u8 *pWrite;
    int nRow;
    int nCol;
    int nPhase;
    int nTile;
    int nCell;
    int nOffset;
    int nBase;
    int x;
    int d;
    int nShade;
    u8 bPair;

    ctx = data_ov002_0207f634;
    if (ctx->pShape == 0) {
        return;
    }

    pScreen = (u16 *)func_ov002_02053bb8(0x1a);
    pShape = ctx->pShape->pTiles;
    nCell = (nValue - 3) / 8;
    if (nCell < 0) {
        nPhase = 0;
        nCell = 0;
    } else {
        nPhase = (nValue + 5) % 8;
    }

    nOffset = 0;
    for (nTile = 0, nBase = 0; nTile < 2; nTile++) {
        pDest = ctx->pNeedle;
        for (nRow = 0; nRow < 8; nRow++) {
            for (nCol = 0; nCol < 8; nCol++) {
                pWrite = pDest + nOffset;
                x = nBase + nCol;
                if (nPhase <= x && x < nPhase + 8) {
                    d = x - nPhase;
                    bPair = pShape[(d + nRow * 8) / 2];
                    if (d % 2 == 0) {
                        nShade = bPair & 0xf;
                    } else {
                        nShade = (bPair >> 4) & 0xf;
                    }
                    if (nShade == 0) {
                        nShade = 3;
                    }
                } else {
                    nShade = 3;
                }
                func_ov002_02063bf8(pWrite, nCol, nRow, nShade);
            }
        }
        nOffset += 0x20;
        nBase += 8;
    }

    *(u16 *)((char *)pScreen + (nCell + 2) * 2 + 0x580) = 0xa070;
    *(u16 *)((char *)pScreen + (nCell + 3) * 2 + 0x580) = 0xa071;
    GFXi_EnqueueCommand(0x16, 0xe00, (int)ctx->pNeedle, 0x40);
}
