/*
 * Ov002_BuildPanelLabels - build the panel's text surface and draw the four
 * entry labels onto it.
 *
 * The surface is set up from a template config with the item's VRAM target and
 * the context's own pixel block, then the cell handles it hands back are kept:
 * the first from the surface itself and the next three from cell zero, plus one
 * from cell one that the teardown selects at the end.
 *
 * Each of the four entries names a string id. A negative id ends the run early.
 * With either of the two mode bits set, ids 0x53 and 0x54 are swapped for 0x75
 * and 0x76 - the alternative wording - and everything else is looked up as it
 * stands. Each label is drawn twice, one pixel apart and in two different
 * modes, which is the drop shadow; a line wider than 0x4f shifts both by one.
 *
 * THUMB.
 */

typedef unsigned char u8;

typedef struct {
    char pad0000[0x18];
    int nVramTarget;                    /* +0x18 */
    char pad001c[4];
    void *pPixels;                      /* +0x20 */
    char pad0024[4];
} Ov002SurfaceCfg;

typedef struct {
    char pad0000[0x24];
    char aPixels[0x20];                 /* +0x024 */
    int bBuilt;                         /* +0x044 */
    char pad0048[0x24];
    char aSurface[0x20];                /* +0x06c */
    int pFont;                          /* +0x08c */
    int pFontData;                      /* +0x090 */
    char pad0094[0x14];
    void *apCells[5];                   /* +0x0a8 */
    char pad00bc[0xc4];
    short *pEntryIds;                   /* +0x180 */
} Ov002PanelCtx;

extern Ov002PanelCtx *data_ov002_0207f614;
extern u8 data_0204c240;
extern Ov002SurfaceCfg data_ov002_0207dc38;
extern int data_ov002_0207e8dc;
extern int data_ov002_0207e8f4;

extern void func_0202ff58(void *pField, const void *pTable);
extern void func_0202ff7c(void *pField);
extern void func_0202ff8c(void *pSurface, const Ov002SurfaceCfg *pCfg);
extern void *func_0202fff8(void *pSurface, int nCell);
extern void func_02030094(void *pSurface, void *pItem, int a);
extern void func_020301c8(void *pSurface, int nX, int nY, int nMode,
                          unsigned int nFlags, int *pRec);
extern void *func_020303b4(void *pSurface);
extern int func_02013768(int a, int b, int *pRec, int d);
extern void func_02030158(void *pSurface);

extern int func_ov002_020573f8(void);
extern void func_ov002_0205280c(void *pThis, void *pTable);
extern void func_ov002_02052834(void *pThis);
extern int *func_ov002_02052844(void *pThis, int nId);
extern int func_ov002_02053bb8(int nId);
extern void func_ov002_02053cd4(int nId);
extern void func_ov002_02055968(void *pSurface, int a, void *b, int *pRec);

void func_ov002_02055984(void)
{
    Ov002PanelCtx *ctx;
    Ov002PanelCtx *pWalk;
    int i;
    int nId;
    int nFont;
    int nOffset;
    int nShift;
    void *pSurface;
    int *pRec;
    Ov002SurfaceCfg cfg;
    int aRecords[3];
    int aBind[3];

    ctx = data_ov002_0207f614;
    pWalk = ctx;
    cfg = data_ov002_0207dc38;
    func_0202ff58(aBind, &data_ov002_0207e8dc);
    nFont = func_ov002_020573f8();
    func_ov002_0205280c(aRecords, &data_ov002_0207e8f4);
    cfg.nVramTarget = func_ov002_02053bb8(9);
    cfg.pPixels = ctx->aPixels;
    func_0202ff8c(ctx->aSurface, &cfg);
    func_02030158(ctx->aSurface);
    ctx->apCells[0] = func_020303b4(ctx->aSurface);

    /* One cell handle per entry lives at +0xa8, four bytes apart, so the
       cursor walks the context itself. The first came from the surface; the
       other three are cell zero handed out again. */
    i = 1;
    pWalk = (Ov002PanelCtx *)((char *)ctx + 4);
    for (; i < 4; i++) {
        pWalk->apCells[0] = func_0202fff8(ctx->aSurface, 0);
        pWalk = (Ov002PanelCtx *)((char *)pWalk + 4);
    }
    ctx->apCells[4] = func_0202fff8(ctx->aSurface, 1);

    i = 0;
    nOffset = 0;
    pWalk = ctx;
    pSurface = ctx->aSurface;
    do {
        nId = *(short *)((char *)ctx->pEntryIds + nOffset);
        if (nId < 0) {
            break;
        }
        if ((data_0204c240 & 4) != 0 || (data_0204c240 & 8) != 0) {
            switch (nId) {
            case 0x53:
                pRec = func_ov002_02052844(aRecords, 0x75);
                break;
            case 0x54:
                pRec = func_ov002_02052844(aRecords, 0x76);
                break;
            default:
                pRec = func_ov002_02052844(aRecords, nId);
                break;
            }
        } else {
            pRec = func_ov002_02052844(aRecords, nId);
        }
        if (pRec != 0) {
            nShift = 0;
            func_02030094(pSurface, pWalk->apCells[0], nShift);
            func_ov002_02055968(pSurface, nFont, aBind, pRec);
            if (func_02013768(ctx->pFont, ctx->pFontData, pRec, nShift) >= 0x50) {
                nShift = 1;
            }
            func_020301c8(pSurface, nShift + 0x50, 1, 1, 0x821, pRec);
            func_020301c8(pSurface, nShift + 0x4f, 0, 2, 0x821, pRec);
        }
        nOffset += 2;
        pWalk = (Ov002PanelCtx *)((char *)pWalk + 4);
        i++;
    } while (i < 4);

    func_ov002_02052834(aRecords);
    func_02030094(ctx->aSurface, ctx->apCells[4], 0);
    ctx->bBuilt = 1;
    func_ov002_02053cd4(9);
    func_0202ff7c(aBind);
}
