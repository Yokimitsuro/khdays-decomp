/*
 * Ov002_ClosePanel - give back everything the panel built and put it back in
 * state 0.
 *
 * Nothing happens at all until the gate that guards the whole screen says so.
 * After that the crawl's surface is released and its flag cleared, the crawl
 * text is freed back to the default heap, and the two surfaces that carry
 * their own built flags - the item text at +0xbc and the labels at +0x6c - are
 * flushed. The skip flag is cleared last, so the next run starts clean.
 *
 * The doubled null test on the crawl text is the ROM's own: the free is itself
 * guarded, so the pointer is tested twice and cleared twice.
 *
 * ARM.
 */

typedef struct {
    char pad0000[0x44];
    int bLabelsBuilt;                   /* +0x044 */
    int bSkipCrawl;                     /* +0x048 */
    int bItemTextBuilt;                 /* +0x04c */
    char pad0050[0x1c];
    int aTextSurface[1];                /* +0x06c sTextSurface */
    char pad0070[0x4c];
    int aItemTextSurface[1];            /* +0x0bc */
    char pad00c0[0xcc];
    int nPanelState;                    /* +0x18c */
    char pad0190[0x30];
    void *pCrawlText;                   /* +0x1c0 */
    char pad01c4[0xa0];
    int aCrawlSurface[1];               /* +0x264 sCrawlSurface */
    char pad0268[0x38];
    int bRowsReady;                     /* +0x2a0 */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;

extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_0202ffbc(int *pSurface);
extern void func_020300f8(int *pSurface);
extern int func_ov002_02053840(void);

void func_ov002_02056118(void)
{
    Ov002PanelContext *ctx;

    ctx = data_ov002_0207f614;
    if (func_ov002_02053840() == 0) {
        return;
    }

    if (ctx->bRowsReady != 0) {
        func_0202ffbc(ctx->aCrawlSurface);
        ctx->bRowsReady = 0;
    }
    if (ctx->pCrawlText != 0) {
        if (ctx->pCrawlText != 0) {
            NNSi_FndFreeFromDefaultHeap(ctx->pCrawlText);
            ctx->pCrawlText = 0;
        }
        ctx->pCrawlText = 0;
    }
    if (ctx->bItemTextBuilt != 0) {
        func_020300f8(ctx->aItemTextSurface);
    }
    if (ctx->bLabelsBuilt != 0) {
        func_020300f8(ctx->aTextSurface);
    }
    ctx->nPanelState = 0;
    ctx->bSkipCrawl = 0;
}
