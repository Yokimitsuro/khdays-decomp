typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    unsigned long long qwStart;         /* +0x00 */
    unsigned long long qwInterval;      /* +0x08 */
    int bActive;                        /* +0x10 */
    int nPhase;                         /* +0x14 */
} Ov002GaugeSlot;

typedef struct {
    u16 wA;
    u16 wB;
} Ov002CountPair;

/* The row array starts at 0207ddfc; the ROM reaches it through its third word,
 * so the linked symbol is that word's own label. */
typedef struct {
    int nScale;                         /* +0x08 of the 0207ddfc row */
    int nField0004;
    int nField0008;
} Ov002PresetRow;

typedef struct {
    int aHandles[4];                    /* +0x00 */
    u8 pad0010[0xbc];
    Ov002CountPair aCounts[4];          /* +0xcc */
    u8 pad00dc[0x36];
    u16 wCount0112;                     /* +0x112 */
} Ov002SceneCtx;

typedef void (*Ov002DrawFn)(int nHandle, int nIndex, int nValue);

extern Ov002SceneCtx *data_ov002_0207f618;
extern Ov002PresetRow data_ov002_0207de04[];

/* The quotient is the low half of the helper's long long return; writing `/`
 * emits _s32_div_f, which is not linkable here (same as at 0205a830). */
extern long long func_02020400(int nNumerator, int nDenominator);
extern unsigned long long func_020031d4(void);
extern void func_ov002_0205779c(int nHandle, int nIndex, int nValue);
extern void func_ov002_02057848(int nHandle, int nIndex, int nValue);
extern void func_ov002_020582d0(int nHandle, int nIndex, int nValue,
                                Ov002DrawFn pDraw, int nMode);

int func_ov002_02058340(int nIndex, Ov002GaugeSlot *pSlot) {
    int nResult;
    Ov002SceneCtx *ctx = data_ov002_0207f618;
    unsigned long long qwNow = func_020031d4();
    int nValue;
    Ov002DrawFn pDraw;
    u16 wCount;

    nResult = 0;
    if (pSlot->bActive == 0) { goto done; }
    if (pSlot->qwInterval > qwNow - pSlot->qwStart) { goto done; }

    pSlot->nPhase = pSlot->nPhase ^ 1;
    if (nIndex == 0) {
        nValue = ctx->wCount0112;
        if (nValue == 0 && ctx->aCounts[0].wB != 0) { nValue = 1; }
        pDraw = func_ov002_0205779c;
    } else {
        wCount = ctx->aCounts[nIndex].wB;
        nValue = (u16)func_02020400(wCount * data_ov002_0207de04[nIndex].nScale,
                                    ctx->aCounts[nIndex].wA);
        if (nValue == 0 && wCount != 0) { nValue = 1; }
        pDraw = func_ov002_02057848;
    }
    func_ov002_020582d0(ctx->aHandles[nIndex], nIndex, nValue, pDraw,
                        pSlot->nPhase != 0 ? 0 : 2);
    pSlot->qwStart = qwNow;
    nResult = 1;
done:
    return nResult;
}
