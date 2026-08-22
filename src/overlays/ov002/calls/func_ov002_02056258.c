/*
 * Ov002_ReturnFromMapToPanel - come back from the map and take the screen
 * again, unless a panel request is already waiting.
 *
 * The scroll tween finishing retunes the ambient emitter, and that runs before
 * the gate. Past it, a pending request short-circuits the whole thing: the
 * state drops to 0 and the screen is given up, which lets whatever asked for
 * the panel start it from the top.
 *
 * Otherwise the map snapshot is taken back, the entry selection is dropped,
 * the blend fades to 0x10 over 300, the screen is claimed and the state moves
 * to 0xb. The label surface is flushed on the way out if it was ever built.
 *
 * ARM.
 */

typedef struct {
    char pad0000[0x3c];
    int nPanelRequestValue;             /* +0x03c */
    int bOwnsScreen;                    /* +0x040 */
    int bLabelsBuilt;                   /* +0x044 */
    char pad0048[0x24];
    int aTextSurface[1];                /* +0x06c sTextSurface */
    char pad0070[0xbc];
    unsigned int dwScrollTweenFlags;    /* +0x12c Tween.dwFlags, bit 2 = finished */
    char pad0130[0x5c];
    int nPanelState;                    /* +0x18c */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;

extern void func_020300f8(int *pSurface);
extern void func_ov002_020537bc(int a, int b, int nDuration);
extern void func_ov002_02053a64(void);
extern void func_ov002_020539f4(int nKey);
extern void func_ov002_020554f0(void);
extern void func_ov002_0205ddac(void);
extern int func_ov002_0205f488(void);

void func_ov002_02056258(void)
{
    Ov002PanelContext *ctx;

    ctx = data_ov002_0207f614;
    if (((unsigned int)((int)ctx->dwScrollTweenFlags << 0x1d) >> 0x1f) != 0) {
        func_ov002_020554f0();
    }
    if (func_ov002_0205f488() == 0) {
        return;
    }

    if (ctx->nPanelRequestValue != 0) {
        ctx->nPanelState = 0;
        ctx->bOwnsScreen = 0;
        return;
    }

    func_ov002_02053a64();
    func_ov002_020539f4(-1);
    func_ov002_0205ddac();
    func_ov002_020537bc(0, 0x10, 300);
    ctx->bOwnsScreen = 1;
    ctx->nPanelState = 0xb;
    if (ctx->bLabelsBuilt != 0) {
        func_020300f8(ctx->aTextSurface);
    }
}
