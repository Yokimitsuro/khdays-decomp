/*
 * Ov002_ClosePanelScreen - give back everything the panel screen holds and
 * drop the context pointer.
 *
 * The three surfaces go back first, each behind its own built flag, then the
 * character copy, the two bound resources and the step node. The crawl text,
 * the two help palettes of each of the four slots, the scratch block and the
 * spare at +0x1d8 are all freed straight to the default heap, and every class
 * the screen instantiated is released - the one at +0x14 before the rest, in
 * the order the ROM releases them.
 *
 * The main display control loses its window bits on the way out and the
 * context pointer is cleared, which is what tells the rest of the overlay the
 * screen is gone.
 *
 * THUMB.
 */

typedef unsigned int u32;

typedef struct {
    void *hFlipClass;                   /* +0x000 */
    void *hClass0004;                   /* +0x004 */
    void *hClass0008;                   /* +0x008 */
    void *hClass000c;                   /* +0x00c */
    void *hClass0010;                   /* +0x010 */
    void *hClass0014;                   /* +0x014 */
    void *hClass0018;                   /* +0x018 */
    void *hClass001c;                   /* +0x01c */
    void *hClass0020;                   /* +0x020 */
    char aBoundResA[0xc];               /* +0x024 */
    char aBoundResB[0xc];               /* +0x030 */
    char pad003c[8];
    int bLabelsBuilt;                   /* +0x044 */
    char pad0048[4];
    int bItemTextBuilt;                 /* +0x04c */
    char pad0050[0x1c];
    int aTextSurface[1];                /* +0x06c */
    char pad0070[0x4c];
    int aItemTextSurface[1];            /* +0x0bc */
    char pad00c0[0x100];
    void *pCrawlText;                   /* +0x1c0 */
    char pad01c4[0x10];
    void *pCharCopy;                    /* +0x1d4 */
    void *pUnk01d8;                     /* +0x1d8 */
    void *ahHelpPltA[4];                /* +0x1dc */
    void *ahHelpPltB[4];                /* +0x1ec */
    char pad01fc[0x20];
    void *hScratch021c;                 /* +0x21c */
    char pad0220[0x20];
    void *hStepNode;                    /* +0x240 */
    char pad0244[0x20];
    int aCrawlSurface[1];               /* +0x264 */
    char pad0268[0x38];
    int bRowsReady;                     /* +0x2a0 */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;

extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void WM_EndKeySharing_0x02023ad0(void *hClass);
extern void func_0202ff7c(void *pField);
extern void func_0202ffbc(int *pSurface);
extern void func_ov002_02053904(void *hNode);

void func_ov002_02056808(void)
{
    Ov002PanelContext *ctx;
    Ov002PanelContext *pWalk;
    int i;
    volatile u32 *pDispCnt;

    ctx = data_ov002_0207f614;
    if (ctx->bLabelsBuilt != 0) {
        func_0202ffbc(ctx->aTextSurface);
    }
    if (ctx->bItemTextBuilt != 0) {
        func_0202ffbc(ctx->aItemTextSurface);
    }
    if (ctx->pCharCopy != 0) {
        NNSi_FndFreeFromDefaultHeap(ctx->pCharCopy);
        ctx->pCharCopy = 0;
    }
    func_0202ff7c(ctx->aBoundResA);
    func_0202ff7c(ctx->aBoundResB);
    func_ov002_02053904(ctx->hStepNode);
    if (ctx->pCrawlText != 0) {
        NNSi_FndFreeFromDefaultHeap(ctx->pCrawlText);
    }
    if (ctx->bRowsReady != 0) {
        func_0202ffbc(ctx->aCrawlSurface);
        ctx->bRowsReady = 0;
    }

    i = 0;
    pWalk = ctx;
    do {
        if (pWalk->ahHelpPltA[0] != 0) {
            NNSi_FndFreeFromDefaultHeap(pWalk->ahHelpPltA[0]);
        }
        if (pWalk->ahHelpPltB[0] != 0) {
            NNSi_FndFreeFromDefaultHeap(pWalk->ahHelpPltB[0]);
        }
        i++;
        pWalk = (Ov002PanelContext *)((char *)pWalk + 4);
    } while (i < 4);

    if (ctx->hScratch021c != 0) {
        NNSi_FndFreeFromDefaultHeap(ctx->hScratch021c);
    }
    if (ctx->pUnk01d8 != 0) {
        NNSi_FndFreeFromDefaultHeap(ctx->pUnk01d8);
    }
    if (ctx->hClass0014 != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->hClass0014);
    }
    if (ctx->hFlipClass != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->hFlipClass);
    }
    if (ctx->hClass0004 != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->hClass0004);
    }
    if (ctx->hClass0008 != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->hClass0008);
    }
    if (ctx->hClass000c != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->hClass000c);
    }
    if (ctx->hClass0010 != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->hClass0010);
    }
    if (ctx->hClass0018 != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->hClass0018);
    }
    if (ctx->hClass001c != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->hClass001c);
    }
    if (ctx->hClass0020 != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->hClass0020);
    }

    pDispCnt = (volatile u32 *)0x04000000;
    *pDispCnt &= 0xffff1fff;
    data_ov002_0207f614 = 0;
}
