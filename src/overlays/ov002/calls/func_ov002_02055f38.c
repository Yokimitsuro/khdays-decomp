/*
 * Ov002_HoldAfterTextCrawl - wait out the pause at the end of the crawl, then
 * hand the panel to the fade-in.
 *
 * The scroll tween finishing is what retunes the ambient emitter, and that is
 * checked every frame regardless. The panel then leaves this state either
 * because the hold has run out - a zero hold means there is none, so only the
 * skip can end it - or because the skip flag is set.
 *
 * ARM.
 */

typedef unsigned long long u64;

typedef struct {
    char pad0000[0x48];
    int bSkipCrawl;                     /* +0x048 */
    char pad004c[0xe0];
    unsigned int dwScrollTweenFlags;    /* +0x12c Tween.dwFlags, bit 2 = finished */
    char pad0130[0x5c];
    int nPanelState;                    /* +0x18c */
    char pad0190[0xc4];
    u64 nCrawlLastTick;                 /* +0x254 */
    u64 nCrawlHoldTicks;                /* +0x25c */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;

extern u64 func_020031d4(void);
extern void func_ov002_020554f0(void);
extern void func_ov002_020555c8(void);

void func_ov002_02055f38(void)
{
    Ov002PanelContext *ctx;
    u64 nNow;
    u64 nElapsed;

    ctx = data_ov002_0207f614;
    nNow = func_020031d4();
    nElapsed = nNow - ctx->nCrawlLastTick;
    if (((unsigned int)((int)ctx->dwScrollTweenFlags << 0x1d) >> 0x1f) != 0) {
        func_ov002_020554f0();
    }

    if ((ctx->nCrawlHoldTicks != 0 && ctx->nCrawlHoldTicks <= nElapsed) ||
        ctx->bSkipCrawl != 0) {
        func_ov002_020555c8();
        ctx->nPanelState = 6;
    }
}
