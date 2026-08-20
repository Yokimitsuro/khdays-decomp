/* Retunes the ambient emitter from the current level value.
 *
 * The two low bits of the global mode byte pick the curve. In mode 2 the
 * spread ramps with the level, level + 0x110 in Q12, and the rate scales with
 * it as well, clamping to a fixed spread and 12000 once the level reaches
 * 0xf6. Every other mode holds the rate at 18000 and uses the clamp as a plain
 * on-off: zero spread below 0xf6, full spread at or above it.
 *
 * The phase byte then advances: it resets to 1 while the context is idle and
 * otherwise cycles 0, 1, 2. */
typedef unsigned char u8;

typedef struct {
    u8 pad0000[0x64];
    u8 nPhase;                      /* +0x64 */
    u8 pad0065[0xaf];
    int nEmitter;                   /* +0x114 */
    u8 pad0118[0xb4];
    int *pLevel;                    /* +0x1cc */
    u8 pad01d0[0x68];
    int nActive;                    /* +0x238 */
} Ov002FxCtx;

extern unsigned char data_0204c240;
extern Ov002FxCtx *data_ov002_0207f614;

extern void func_02035fb0(void *pEmitter, int a, int b, int nSpread, int nRate);
extern void func_02035ffc(void *pEmitter);

void func_ov002_020554f0(void) {
    Ov002FxCtx *ctx = data_ov002_0207f614;
    int *pLevel = ctx->pLevel;
    int nSpread;
    int nRate;
    int v;

    if ((data_0204c240 & 6) == 2) {
        v = *pLevel;
        if (v >= 0xf6) {
            nSpread = 0x200000;
            nRate = 12000;
        } else {
            nSpread = (v + 0x110) << 12;
            nRate = ((v + 0x110) * 12000) / 512;
        }
    } else {
        v = *pLevel;
        nRate = 18000;
        if (v < 0xf6) {
            nSpread = 0;
        } else {
            nSpread = 0x200000;
        }
    }

    if (ctx->nActive == 0) {
        ctx->nPhase = 1;
    } else {
        ctx->nPhase = (u8)((ctx->nPhase + 1) % 3);
    }

    func_02035fb0(&ctx->nEmitter, 0, 0, nSpread, nRate);
    func_02035ffc(&ctx->nEmitter);
}
