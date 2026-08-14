typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad0000[0x3c];
    int nRowCount;                      /* +0x3c */
    u8 pad0040[4];
    int nUnitCost;                      /* +0x44 */
    u8 pad0048[0xa4];
    u16 wTotalUnits;                    /* +0xec */
    u16 wCurrentUnits;                  /* +0xee */
} Ov002SceneCtx;

extern Ov002SceneCtx *data_ov002_0207f618;

/* The quotient is the low half of the helper's long long return; writing `/`
 * emits _s32_div_f, which is not linkable here. */
extern long long func_02020400(int nNumerator, int nDenominator);
extern int func_ov002_02053558(int nId);
extern void func_ov002_02053534(int nHandle, int nFlag);
extern void func_ov002_020578f4(int nRow, int bFilled, int bLast);

void func_ov002_02058568(void) {
    Ov002SceneCtx *ctx = data_ov002_0207f618;
    int nScale;
    int nTotal;
    int nCurrent;
    int nRowsTotal;
    int nRowsCurrent;
    int i;

    for (i = 0; i < (ctx->nRowCount + 1) / 2; i++) {
        func_ov002_02053534(func_ov002_02053558((u16)(i + 50000)), 1);
    }

    nScale = ctx->nUnitCost * 250;
    nTotal = (int)func_02020400(ctx->wTotalUnits * 46, nScale);
    nCurrent = (int)func_02020400(ctx->wCurrentUnits * 46, nScale);

    if (nTotal <= 0) {
        nRowsTotal = 0;
    } else {
        nRowsTotal = (nTotal - 1) / 46;
    }
    if (nCurrent <= 0) {
        nRowsCurrent = 0;
    } else {
        nRowsCurrent = (nCurrent - 1) / 46;
    }

    if (nRowsTotal > 0) {
        for (i = 0; i < nRowsTotal - 1; i++) {
            func_ov002_020578f4(i, i < nRowsCurrent, 0);
        }
        func_ov002_020578f4(nRowsTotal - 1, nRowsTotal - 1 < nRowsCurrent, 1);
    }

    ctx->nRowCount = nRowsTotal;
}
