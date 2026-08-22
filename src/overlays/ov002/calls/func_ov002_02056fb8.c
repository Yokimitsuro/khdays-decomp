/*
 * Ov002_HoldPanelScreen - park the panel while something else owns the screen,
 * and put it back afterwards.
 *
 * A request that matches the hold the panel is already in does nothing, and so
 * does one that arrives with no context at all. Both tweens are suspended or
 * resumed to match.
 *
 * Going on hold, the BG2 palette and screen are saved into the two blocks the
 * screen owns. Coming back, the palette is uploaded again, BG2's screen is
 * wiped and reloaded from the saved copy, and that copy is freed. A non-zero
 * second argument means the panel is not coming back at all: the map snapshot
 * is popped, the selection dropped and the state reset to 0.
 *
 * What is drawn next depends on where the panel stands. Outside its live
 * states BG3 is refilled from the item resource; inside them, and only if the
 * crawl surface is up, the crawl is retyped from the start up to the glyph it
 * had reached and the surface is flushed and uploaded by hand.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    char pad0000[0xf8];
    char aOffsetTween[0x1c];            /* +0x0f8 */
    char aScrollTween[0x1c];            /* +0x114 */
    char pad0130[0x5c];
    int nPanelState;                    /* +0x18c */
    char pad0190[0x20];
    int nHeld;                          /* +0x1b0 */
    char pad01b4[0xc];
    u16 *pCrawlText;                    /* +0x1c0 */
    char pad01c4[0x14];
    void *pSavedBg2Scr;                 /* +0x1d8 */
    char pad01dc[0x40];
    void *hSavedBg2Plt;                 /* +0x21c */
    char pad0220[0x24];
    int nCrawlIndex;                    /* +0x244 */
    char pad0248[0x1c];
    int aCrawlSurface[1];               /* +0x264 */
    char pad0268[8];
    u32 nCrawlSize;                     /* +0x270 */
    int nCrawlDst;                      /* +0x274 */
    char pad0278[4];
    void **ppCrawlObj;                  /* +0x27c */
    char pad0280[0x20];
    int bRowsReady;                     /* +0x2a0 */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;

extern void DC_FlushRange(void *pAddr, u32 nSize);
extern void GX_LoadBG1Char(void *pSrc, int nOffset, u32 nSize);
extern void GX_LoadBG2Scr(void *pSrc, int nOffset, u32 nSize);
extern void GX_LoadBGPltt(void *pSrc, int nOffset, u32 nSize);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern void MIi_CpuCopyFast(const void *pSrc, void *pDst, u32 nSize);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 nSize, int nAlign);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_02030158(int *pSurface);
extern int func_02030194(int *pSurface, int nX, int nY, int nStyle, int nGlyph);
extern void func_02036104(void *pTween, int bHold);
extern void func_ov002_020539f4(int nKey);
extern void func_ov002_02053a64(void);
extern void *func_ov002_02053bb8(int nId);
extern void func_ov002_02053cd4(int nId);
extern void func_ov002_02053dac(int nHold);
extern void func_ov002_020553ec(int a);
extern void func_ov002_0205f3f4(void);
extern void func_ov002_0205f56c(void);

void func_ov002_02056fb8(int nHold, int bLeaving)
{
    Ov002PanelContext *ctx;
    int i;
    int nPen;
    void *pSaved;
    void *pBg2;
    void *pBg3;

    ctx = data_ov002_0207f614;
    nPen = 8;
    if (ctx == 0 || ctx->nHeld == nHold) {
        return;
    }
    func_ov002_02053dac(nHold);

    if (nHold != 0) {
        ctx->pSavedBg2Scr = NNS_FndAllocFromDefaultExpHeapEx(0x800, 4);
        MIi_CpuCopyFast((const void *)0x05000000, ctx->hSavedBg2Plt, 0x200);
        pSaved = ctx->pSavedBg2Scr;
        pBg2 = G2_GetBG2ScrPtr();
        MIi_CpuCopyFast(pBg2, pSaved, 0x800);
        func_02036104(ctx->aOffsetTween, 1);
        func_02036104(ctx->aScrollTween, 1);
    } else {
        func_ov002_020553ec(bLeaving);
        GX_LoadBGPltt(ctx->hSavedBg2Plt, 0, 0x200);
        MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
        GX_LoadBG2Scr(ctx->pSavedBg2Scr, 0, 0x800);
        if (ctx->pSavedBg2Scr != 0) {
            NNSi_FndFreeFromDefaultHeap(ctx->pSavedBg2Scr);
            ctx->pSavedBg2Scr = 0;
        }
        if (bLeaving != 0) {
            func_ov002_0205f3f4();
            func_ov002_02053a64();
            func_ov002_020539f4(-1);
            ctx->nPanelState = 0;
        }
        if (ctx->nPanelState >= 1 && ctx->nPanelState <= 8) {
            if (ctx->bRowsReady != 0) {
                func_02030158(ctx->aCrawlSurface);
                i = 0;
                if (ctx->nCrawlIndex > 0) {
                    do {
                        if (ctx->pCrawlText[i] == 0) {
                            break;
                        }
                        nPen += func_02030194(ctx->aCrawlSurface, nPen, 3, 2,
                                              ctx->pCrawlText[i]);
                        i++;
                    } while (i < ctx->nCrawlIndex);
                }
                DC_FlushRange(ctx->ppCrawlObj[8], ctx->nCrawlSize);
                GX_LoadBG1Char(ctx->ppCrawlObj[8], ctx->nCrawlDst, ctx->nCrawlSize);
            }
        } else {
            pBg3 = G2_GetBG3ScrPtr();
            MIi_CpuCopyFast(func_ov002_02053bb8(0xb), pBg3, 0x800);
            func_ov002_02053cd4(0xb);
        }

        if (ctx->nPanelState >= 9 && ctx->nPanelState <= 0xb) {
            func_ov002_0205f56c();
        }
        func_02036104(ctx->aOffsetTween, 0);
        func_02036104(ctx->aScrollTween, 0);
    }

    ctx->nHeld = nHold;
}
