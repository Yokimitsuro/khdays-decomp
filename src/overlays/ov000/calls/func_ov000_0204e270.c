/* func_ov000_0204e270 -- fade the ov000 menu back in after a re-entry.
 *
 * The state func_ov000_0204df98 hands control to on a non-fresh entry into scene 1, i.e.
 * every time the player comes back to the menu from somewhere else.  Both screens start
 * blacked out and this state walks them back up over roughly a second and a half:
 *
 *   - first tick only (layoutReady): run the one-shot setup, main master brightness to 0
 *     and sub to full, DISPCNT display mode 1, seed both animation tracks from the frame
 *     counter, main blend brightness at full, then func_ov000_0204d7a0;
 *   - if func_ov000_0204d338 reports the fade should be skipped, jump straight to the end
 *     state: snap the counter to 0x79 and both tracks to their last frame, clear every
 *     blend, refresh the menu and go to func_ov000_0204e5b0;
 *   - otherwise ramp.  Below frame 0x3c nothing is shown yet; from 0x3c the main blend
 *     brightness drops one step every two frames until it reaches 0, and the sub screen
 *     master brightness follows the same slope between 0x3c and 0x5c while the two layers
 *     cross-fade.  When the node animation reports done (bit 0 of func_0202a928) the entry
 *     tick is stamped and the next state is func_ov000_0204e5b0; otherwise tick the counter.
 *
 * CODEGEN NOTE -- `level` has to be computed BEFORE the DISPCNT write.  The write goes
 * through a pointer, so mwcc has to assume it can alias ctx->counter and reloads it; with
 * the read first, the value the `>= 0x3c` test already loaded is reused, which is the
 * ROM's one-instruction-shorter form.
 */
typedef unsigned char u8;
typedef unsigned int  u32;
typedef volatile u32  vu32;
typedef void         *StateFn;

typedef struct Ov000MenuContext {
    int       counter;
    u8        pad_0004[8];
    u8        node[0x108];
    u8        scrollBounds[0x4b28];
    int       layoutReady;
    u8        pad_4c40[0x24];
    long long enterTick;
} Ov000MenuContext;

extern Ov000MenuContext *NNSi_FndGetCurrentRootHeap(void);
extern void      func_ov000_0204d354(void);
extern void      func_ov000_0204e0c8(void);
extern void      func_0201e374(int brightness);
extern void      func_0201e3cc(int brightness);
extern int       func_01fff774(void *node, int track, int frame);
extern void      G2x_SetBlendBrightnessExt_(u32 reg, int a, int b, int c, int d, int e);
extern void      G2x_SetBlendAlpha_(u32 reg, int a, int b, int c, int d);
extern void      func_02033fb4(int a, int b);
extern void      func_ov000_0204d7a0(void);
extern int       func_ov000_0204d338(void);
extern int       func_0202aef8(void *node, int track);
extern void      func_ov000_0204e1dc(int level);
extern void      func_ov000_0204cc90(void);
extern void      func_ov000_0204d208(void);
extern void      func_02023d70(void *bounds, int a, int b, int c, int d);
extern void      func_0202aa9c(void *node);
extern long long func_020031d4(void);
extern int       func_0202a818(void *node, int mask);
extern int       func_0202a928(void *node, int mask);
extern void      func_ov000_0204e5b0(void);

StateFn func_ov000_0204e270(void) {
    Ov000MenuContext *ctx;
    int level;
    vu32 *dispcnt = (vu32 *)0x04000000;

    ctx = NNSi_FndGetCurrentRootHeap();
    func_ov000_0204d354();
    if (ctx->layoutReady == 0) {
        func_ov000_0204e0c8();
        func_0201e374(0);
        func_0201e3cc(0x10);
        *dispcnt = (*dispcnt & ~0x1f00) | 0x100;
        func_01fff774(ctx->node, 0, ctx->counter << 12);
        func_01fff774(ctx->node, 2, ctx->counter << 12);
        G2x_SetBlendBrightnessExt_(0x04000050, 2, 2, 0, 0x10, 0);
        func_02033fb4(0, 0);
        func_ov000_0204d7a0();
        ctx->layoutReady = 1;
    }

    if (func_ov000_0204d338() != 0) {
        ctx->counter = 0x79;
        func_01fff774(ctx->node, 0, func_0202aef8(ctx->node, 0) - 1);
        func_01fff774(ctx->node, 2, func_0202aef8(ctx->node, 2) - 1);
        *dispcnt = (*dispcnt & ~0x1f00) | 0x300;
        G2x_SetBlendBrightnessExt_(0x04000050, 2, 0x20, 0, 0, 0);
        func_0201e3cc(0);
        func_ov000_0204e1dc(0);
        G2x_SetBlendAlpha_(0x04001050, 0x10, 0x22, 0x10, 0);
        func_ov000_0204cc90();
        func_ov000_0204d208();
        func_02023d70(ctx->scrollBounds, 0x3b33, -0x3b33, -0x4d9a, 0x4d9a);
        func_0202aa9c(ctx->node);
        ctx->enterTick = func_020031d4();
        return (StateFn)func_ov000_0204e5b0;
    }

    if (ctx->counter >= 0x3c) {
        level = 0x10 - (ctx->counter - 0x3c) / 2;
        *dispcnt = (*dispcnt & ~0x1f00) | 0x300;
        if (level < 0) {
            level = 0;
        }
        G2x_SetBlendBrightnessExt_(0x04000050, 2, 2, 0x10 - level, level, 0);
        func_ov000_0204e1dc(level);
    } else {
        G2x_SetBlendBrightnessExt_(0x04000050, 2, 0x20, 0, 0, 0);
        func_ov000_0204e1dc(0x10);
    }

    if (ctx->counter < 0x3c) {
        func_0201e3cc(0x10);
    } else if (ctx->counter <= 0x5c) {
        func_0201e3cc(0x10 - (ctx->counter - 0x3c) / 2);
        G2x_SetBlendAlpha_(0x04001050, 0x10, 0x22, (ctx->counter - 0x3c) / 2,
                           0x10 - (ctx->counter - 0x3c) / 2);
    } else {
        func_0201e3cc(0);
        G2x_SetBlendAlpha_(0x04001050, 0x10, 0x22, 0x10, 0);
    }

    func_ov000_0204cc90();
    func_ov000_0204d208();
    func_02023d70(ctx->scrollBounds, 0x3b33, -0x3b33, -0x4d9a, 0x4d9a);
    func_0202aa9c(ctx->node);
    func_0202a818(ctx->node, 0x1000);
    if ((func_0202a928(ctx->node, 0x1000) & 1) != 0) {
        ctx->enterTick = func_020031d4();
        return (StateFn)func_ov000_0204e5b0;
    }
    ctx->counter = ctx->counter + 1;
    return 0;
}
