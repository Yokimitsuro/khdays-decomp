typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 wTotal;                         /* +0x00 */
    u16 wDrawn;                         /* +0x02 */
} Ov002CountPair;

typedef struct {
    int nField0000;
    int nField0004;
    int nField0008;
} Ov002GaugeRow;

typedef void (*Ov002CellFn)(int nTarget, int nCell, int bClearing);

typedef struct {
    int aHandles[4];                    /* +0x00 */
    u8 pad0010[0x18];
    u8 bStateFlags;                     /* +0x28 */
    u8 pad0029[0x11];
    u16 wShown003a;                     /* +0x3a */
    u8 pad003c[0x10];
    unsigned long long aHold[4];        /* +0x4c */
    u8 pad006c[0x60];
    Ov002CountPair aCounts[4];          /* +0xcc */
    u8 pad00dc[0x18];
    u8 aTweenA[0x1c];                   /* +0xf4 */
    u8 aTweenB[2];                      /* +0x110 */
    u16 wCount0112;                     /* +0x112 */
    u16 wCount0114;                     /* +0x114 */
} Ov002SceneCtx;

extern Ov002SceneCtx *data_ov002_0207f618;
extern const Ov002GaugeRow data_ov002_0207de04[];

extern long long func_02020400(int nNumerator, int nDenominator);
extern unsigned long long func_020031d4(void);
extern void func_ov002_02057260(int nIndex, int nMode);
extern void func_ov002_020593b4(int nIndex, int nShown);
extern void func_ov002_02057d74(void *pDst, u16 *pSrc, int nValue, void *pDraw,
                                int nHandle, int nA, int nB);
extern int func_ov002_02058778(int nTarget, int nValue, int nScale,
                               Ov002CountPair *pPair, Ov002CellFn pDraw,
                               int bRebuild);
extern void func_ov002_02057848(int nHandle, int nCell, int nValue);
extern void func_ov002_0205779c(int nHandle, int nCell, int nValue);
extern void func_ov002_02057808(int nHandle, int nCell, int nValue);
extern void func_ov002_02057ca4(int nCount);

void func_ov002_02058b9c(int nIndex, unsigned int nValue, int nFlags, int bImmediate,
                         int bRebuild) {
    Ov002SceneCtx *ctx = data_ov002_0207f618;
    u16 wShown;
    int nCells;
    int bChanged = 1;
    int nScale;

    if (bImmediate != 0 && nValue == ctx->aCounts[nIndex].wDrawn) {
        return;
    }
    if (ctx->aCounts[nIndex].wDrawn == 0 && nValue != 0) {
        func_ov002_02057260(nIndex, 0);
    }

    if (nIndex == 0) {
        if (bImmediate != 0) {
            wShown = ctx->wCount0112;
            nScale = data_ov002_0207de04[nIndex].nField0000;
            nCells = (u16)func_02020400(nValue * nScale, ctx->aCounts[nIndex].wTotal);
            if (nCells == 0 && nValue != 0) {
                nCells = 1;
            }
            if (wShown == nCells && ctx->aCounts[nIndex].wDrawn > nValue) {
                func_ov002_02057260(nIndex, 1);
                ctx->aHold[nIndex] = func_020031d4();
                ctx->aCounts[nIndex].wDrawn = (u16)nValue;
                return;
            }
            ctx->aCounts[nIndex].wDrawn = (u16)nValue;
            func_ov002_02057d74(ctx->aTweenB, (u16 *)ctx->aTweenA, nCells,
                                func_ov002_0205779c, ctx->aHandles[0], 1, 0);
            ctx->wShown003a = (u16)nCells;
        } else {
            nScale = data_ov002_0207de04[nIndex].nField0000;
            bChanged = func_ov002_02058778(ctx->aHandles[nIndex], nValue, (u16)nScale,
                                           &ctx->aCounts[nIndex], func_ov002_02057808,
                                           bRebuild);
            nCells = (int)func_02020400(nValue * nScale,
                                        ctx->aCounts[nIndex].wTotal);
            if (nValue != 0 && nCells == 0) {
                ctx->wShown003a = ctx->wCount0112 = ctx->wCount0114 = 1;
            } else {
                ctx->wCount0114 = (u16)nCells;
                ctx->wShown003a = ctx->wCount0112 = ctx->wCount0114;
            }
        }
    } else {
        if (bImmediate != 0 && ctx->aCounts[nIndex].wDrawn > nValue) {
            if (nValue == 0) {
                func_ov002_020593b4(nIndex, 0);
                func_ov002_02057260(nIndex, 2);
            } else {
                func_ov002_02057260(nIndex, 1);
                ctx->aHold[nIndex] = func_020031d4();
            }
        }
        nScale = data_ov002_0207de04[nIndex].nField0000;
        bChanged = func_ov002_02058778(ctx->aHandles[nIndex], nValue, (u16)nScale,
                                       &ctx->aCounts[nIndex], func_ov002_02057848,
                                       bRebuild);
    }

    if (bChanged == 0) {
        return;
    }
    if (nFlags >= 0) {
        ctx->bStateFlags = ctx->bStateFlags | (1 << (nIndex + 3));
    }
}
