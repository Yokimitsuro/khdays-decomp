/*
 * Ov002_RequestPanelScreen - ask for the mission panel, with the text it should
 * crawl and how long to hold it afterwards.
 *
 * Nothing happens unless the panel is idle: a non-zero state means one is
 * already running and the request is dropped on the floor. Otherwise the state
 * moves to 1, the skip flag is cleared, and the hand-off flag and item id the
 * caller passed are stored.
 *
 * The crawl text is copied onto the default heap - a fresh block of one more
 * halfword than the string is long - and whatever was there before is freed
 * first. The hold arrives as two words because it is a 64-bit tick count.
 *
 * The offset tween then slides the panel in from 0 to 0x18000 over 300 and the
 * blend fades all the way out over the same 300.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    char pad0000[0x48];
    int bSkipCrawl;                     /* +0x048 */
    char pad004c[8];
    int nLevelSlot;                     /* +0x054 */
    char pad0058[0xa0];
    char aOffsetTween[0x1c];            /* +0x0f8 */
    char pad0114[0x78];
    int nPanelState;                    /* +0x18c */
    char pad0190[8];
    int nItemId;                        /* +0x198 */
    char pad019c[0x24];
    u16 *pCrawlText;                    /* +0x1c0 */
    char pad01c4[0x98];
    u32 nCrawlHoldLo;                   /* +0x25c */
    u32 nCrawlHoldHi;                   /* +0x260 */
    char pad0264[0x40];
    int bTextHandOff;                   /* +0x2a4 */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int nSize);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern int func_020200c8(const u16 *pText);
extern void func_020200e4(u16 *pDst, const u16 *pSrc);
extern void func_02035fb0(void *pTween, int nMode, int nFrom, int nTo,
                          int nDuration);
extern void func_02035ffc(void *pTween);
extern void func_ov002_020537bc(int a, int b, int nDuration);

void func_ov002_02056edc(u16 *pText, u32 nHoldLo, u32 nHoldHi,
                         int bTextHandOff, int nItemId)
{
    Ov002PanelContext *ctx;

    ctx = data_ov002_0207f614;
    if (ctx->nPanelState != 0) {
        return;
    }

    ctx->nPanelState = 1;
    ctx->bSkipCrawl = 0;
    ctx->bTextHandOff = bTextHandOff;
    ctx->nItemId = nItemId;
    if (ctx->pCrawlText != 0) {
        NNSi_FndFreeFromDefaultHeap(ctx->pCrawlText);
        ctx->pCrawlText = 0;
    }
    ctx->pCrawlText =
        (u16 *)NNSi_FndAllocFromDefaultExpHeap((func_020200c8(pText) + 1) * 2);
    func_020200e4(ctx->pCrawlText, pText);
    ctx->nCrawlHoldLo = nHoldLo;
    ctx->nCrawlHoldHi = nHoldHi;

    func_02035fb0(ctx->aOffsetTween, 1, 0, 0x18000, 300);
    func_02035ffc(ctx->aOffsetTween);
    func_ov002_020537bc(-1, 0, 300);
    ctx->nLevelSlot = 1;
}
