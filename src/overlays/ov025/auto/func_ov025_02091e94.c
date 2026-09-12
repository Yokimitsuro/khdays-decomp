/* func_ov025_02091e94 -- Ov008_InitGridCell: reset one 40-byte grid cell to its
 * resting state at (nX, nY) with the given tile and palette. The four
 * scale fields are one chained assignment (the 0x10 constant is created before the
 * second zero store); the rest are plain stores in field order.
 */
typedef unsigned char u8;

typedef struct Ov008GridCell {
    int   nState;        /* 0x00 */
    u8    pad_04[8];
    short nX;            /* 0x0c */
    short nY;            /* 0x0e */
    short nTile;         /* 0x10 */
    short nScaleX;       /* 0x12 */
    short nScaleY;       /* 0x14 */
    short nShiftX;       /* 0x16 */
    short nShiftY;       /* 0x18 */
    short nBaseScaleX;   /* 0x1a */
    short nBaseScaleY;   /* 0x1c */
    short nPalette;      /* 0x1e */
    short nTimer;        /* 0x20 */
    u8    pad_22[2];
    int   nFlags;        /* 0x24 */
} Ov008GridCell;

#define SCALE_ONE 0x10

void func_ov025_02091e94(Ov008GridCell *pCell, short nX, short nY, short nTile, short nPalette)
{
    pCell->nState = 0;
    pCell->nShiftX = pCell->nShiftY = 0;
    pCell->nScaleX = pCell->nScaleY = pCell->nBaseScaleX = pCell->nBaseScaleY = SCALE_ONE;
    pCell->nX = nX;
    pCell->nY = nY;
    pCell->nTile = nTile;
    pCell->nPalette = nPalette;
    pCell->nTimer = pCell->nFlags = 0;
}
