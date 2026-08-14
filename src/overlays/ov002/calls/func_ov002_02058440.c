typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad0000[0x20];
    int nSurfaceStride;                 /* +0x20, surface10.strideTiles */
    u8 pad0024[0x20];
    int nUnitCost;                      /* +0x44 */
    u8 pad0048[0xa4];
    u16 wTotalUnits;                    /* +0xec */
    u16 wCurrentUnits;                  /* +0xee */
    u8 pad00f0[0x3c];
    u16 wRowsA0;                        /* +0x12c */
    u16 wRowsA1;                        /* +0x12e */
    u8 pad0130[0x18];
    u16 wRowsB0;                        /* +0x148 */
    u16 wRowsB1;                        /* +0x14a */
} Ov002SceneCtx;

extern Ov002SceneCtx *data_ov002_0207f618;

/* The quotient is the low half of the helper's long long return; writing `/`
 * emits _s32_div_f, which is not linkable here. */
extern long long func_02020400(int nNumerator, int nDenominator);
extern void func_ov002_02057a20(int nColumn, int nRows);
extern void func_ov002_02057888(int nSurface, int nRow, int nMode);
extern int func_ov002_02053558(int nId);
extern void func_ov002_020535a4(int nHandle);

void func_ov002_02058440(void) {
    Ov002SceneCtx *ctx = data_ov002_0207f618;
    int nScale = ctx->nUnitCost * 250;
    int nTotal = (int)func_02020400(ctx->wTotalUnits * 46, nScale);
    u16 wCurrent = ctx->wCurrentUnits;
    int nCurrent = (int)func_02020400(wCurrent * 46, nScale);
    int nBase;
    int nColumn;
    int nRows;
    int nLast;
    int i;

    if (wCurrent != 0 && nCurrent == 0) { nCurrent = 1; }

    nBase = nTotal / 46 * 46;
    nColumn = 46;
    if (nCurrent > nBase || nCurrent == 0) { nColumn = nTotal - nBase; }

    if (nCurrent <= 0) {
        nRows = 0;
    } else {
        nLast = nCurrent - 1;
        nRows = nLast % 46 + 1;
    }

    func_ov002_02057a20(nColumn, nRows);

    ctx->wRowsA0 = (u16)nCurrent;
    ctx->wRowsB0 = ctx->wRowsA0;
    ctx->wRowsA1 = ctx->wRowsA0;
    ctx->wRowsB1 = ctx->wRowsA0;

    for (i = 0; i < nRows; i++) {
        func_ov002_02057888(ctx->nSurfaceStride, i, 0);
    }

    func_ov002_020535a4(func_ov002_02053558(0x32));
}
