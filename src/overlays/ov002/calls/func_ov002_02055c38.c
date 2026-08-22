/*
 * Ov002_BeginTextCrawl - bring up the surface the panel types its text onto,
 * once the offset tween has finished.
 *
 * The tween-finished bit gates the whole thing: while the panel is still
 * sliding there is nothing to build. Once it has settled the crawl's two tick
 * counts and its glyph index are cleared, the pen is parked at eight, and a
 * tiled surface is built from a template config over BG1's screen and the
 * context's own pixel block.
 *
 * The top 0x80 bytes of the BG1 and BG3 screens are then saved into the item
 * resources the panel owns, both at +0x700, so what they carry survives the
 * crawl; each resource is selected right after it is saved. Row zero is seeded
 * from the new surface and the panel is parked in state 4.
 *
 * ARM.
 */

typedef struct {
    char pad0000[0x18];
    int nVramTarget;                    /* +0x18 */
    char pad001c[4];
    void *pPixels;                      /* +0x20 */
    char pad0024[4];
} Ov002SurfaceCfg;

typedef struct {
    char pad0000[0x24];
    char aPixels[0xec];                 /* +0x024 sPixelBlock */
    unsigned int dwOffsetTweenFlags;    /* +0x110 Tween.dwFlags, bit 2 = finished */
    char pad0114[0x78];
    int nPanelState;                    /* +0x18c */
    char pad0190[0x30];
    int pCrawlText;                     /* +0x1c0 the text the crawl types */
    char pad01c4[0x80];
    int nCrawlIndex;                    /* +0x244 next glyph to type */
    int nCrawlPenX;                     /* +0x248 pen x it types at */
    int anCrawlClock[4];                /* +0x24c elapsed and last tick, both 64-bit */
    char pad025c[8];
    int aCrawlSurface[1];               /* +0x264 sCrawlSurface */
    char pad0268[0x38];
    int bRowsReady;                     /* +0x2a0 */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;
extern Ov002SurfaceCfg data_ov002_0207dc10;

extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuCopy16(void *pSrc, void *pDst, unsigned int nSize);
extern void func_0202ff8c(int *pSurface, const Ov002SurfaceCfg *pCfg);
extern void func_020300f8(int *pSurface);
extern int func_020303bc(int *pSurface, int nSource);
extern void func_ov002_020539f4(int nKey);
extern int func_ov002_02053bb8(int nId);
extern void func_ov002_02053cd4(int nId);
extern void func_ov002_02057454(int nRow, int nValue);

void func_ov002_02055c38(void)
{
    Ov002PanelContext *ctx;
    Ov002SurfaceCfg cfg;
    void *pScreen;

    cfg = data_ov002_0207dc10;
    ctx = data_ov002_0207f614;
    if (((unsigned int)((int)ctx->dwOffsetTweenFlags << 0x1d) >> 0x1f) == 0) {
        return;
    }

    ctx->anCrawlClock[0] = 0;
    ctx->anCrawlClock[1] = 0;
    ctx->anCrawlClock[2] = 0;
    ctx->anCrawlClock[3] = 0;
    ctx->nCrawlIndex = 0;
    ctx->nCrawlPenX = 8;

    cfg.nVramTarget = (int)G2_GetBG1ScrPtr();
    cfg.pPixels = &ctx->aPixels[0xc];
    func_ov002_020539f4(-1);
    func_0202ff8c(ctx->aCrawlSurface, &cfg);
    func_020300f8(ctx->aCrawlSurface);

    pScreen = G2_GetBG1ScrPtr();
    MIi_CpuCopy16((char *)pScreen + 0x700,
                  (char *)func_ov002_02053bb8(9) + 0x700, 0x80);
    pScreen = G2_GetBG3ScrPtr();
    MIi_CpuCopy16((char *)pScreen + 0x700,
                  (char *)func_ov002_02053bb8(0xb) + 0x700, 0x80);
    func_ov002_02053cd4(9);
    func_ov002_02053cd4(0xb);

    ctx->bRowsReady = 1;
    func_ov002_02057454(0, func_020303bc(ctx->aCrawlSurface, ctx->pCrawlText));
    func_ov002_020539f4(0);
    ctx->nPanelState = 4;
}
