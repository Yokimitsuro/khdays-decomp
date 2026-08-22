/*
 * Ov002_UpdatePanelScroll - work out this frame's scroll and hook arguments.
 *
 * Nothing happens while the panel context is held. The vertical offset is
 * resampled from its own Tween until that Tween reports finished, and each
 * sample is handed to the notify handler along with the value just stored. Once
 * both Tweens have finished there is nothing left to move and the frame is
 * skipped outright.
 *
 * The horizontal scroll comes from the second Tween and wraps around the level:
 * while the level is below 0xf6 and the scroll has run past level + 0x10, the
 * scroll jumps forward to the far side of the 0x100 span. What is left of the
 * 0x200 span after the scroll gives the clamp, held between 1 and 0xff, and how
 * far the vertical offset still is below 0x28 gives the margin.
 *
 * Those two fill the four hook arguments, differently for each emitter phase,
 * and only in phase 2 - and only while the scroll and the level together still
 * fit inside 0x1e0 - does the panel actually flip to the other level slot. The
 * flip is provisional: with the gate at +0x00 raised the new slot is offered to
 * the loader, and a refusal flips it straight back while an acceptance releases
 * the surface the old slot was holding. Either way the ambient emitter is
 * retuned to the level the flip left behind.
 *
 * ARM. The phase switch has no default: with a phase byte of 3 or more the four
 * hook arguments are stored uninitialised, which is what the original does.
 *
 * The notify handler really does take two arguments. Called with one, mwcc has
 * r1 free and loads the handler pointer into it; the second argument is what
 * keeps the offset alive in r1 and pushes the pointer out to r2 the way the ROM
 * has it. The declaration order of the seven register variables below is the
 * other half of this match - mwcc hands out r4 upwards strictly in that order,
 * but only while the block is contiguous.
 */

typedef unsigned char u8;

typedef struct {
    int nFlipGate;                   /* +0x000 */
    u8 pad0004[0x50];
    int nLevelSlot;                  /* +0x054 which of aLevels is current */
    u8 pad0058[0xc];
    u8 nEmitPhase;                   /* +0x064 */
    u8 pad0065[0x93];
    u8 aOffsetTween[0x18];           /* +0x0f8 Tween body */
    unsigned int dwOffsetTweenFlags; /* +0x110 Tween.dwFlags, bit 2 = finished */
    u8 aScrollTween[0x18];           /* +0x114 Tween body */
    unsigned int dwScrollTweenFlags; /* +0x12c Tween.dwFlags, bit 2 = finished */
    u8 pad0130[0x60];
    int nScrollShadow;               /* +0x190 */
    int nVertOffset;                 /* +0x194 */
    u8 pad0198[0x18];
    int nHeld;                       /* +0x1b0 */
    u8 pad01b4[0x10];
    int aLevels[2];                  /* +0x1c4 */
    int *pLevel;                     /* +0x1cc points into aLevels */
    u8 pad01d0[0x60];
    void *pScrollHook;               /* +0x230 */
    void (*pfnOffsetNotify)(int, int); /* +0x234 */
    void *pFlipHook;                 /* +0x238 */
    u8 pad023c[0x6c];
    int bScrollPending;              /* +0x2a8 */
    int nScrollA;                    /* +0x2ac */
    int nScrollB;                    /* +0x2b0 */
    int nHook2A;                     /* +0x2b4 */
    int nHook2B;                     /* +0x2b8 */
    int nHook3A;                     /* +0x2bc */
    int nHook3B;                     /* +0x2c0 */
} Ov002PanelCtx;

extern void func_0203602c(void *pTween, int *pValue);
extern int func_ov002_02063814(int nSlot);
extern void func_ov002_02063350(int nSlot);
extern void func_ov002_020554f0(void);

extern unsigned char data_0204c240;
extern Ov002PanelCtx *data_ov002_0207f614;

void func_ov002_02054e54(void)
{
    Ov002PanelCtx *ctx;
    int nMargin;
    int nScroll;
    int nHook3A;
    int nHook2B;
    int nHook2A;
    int nHook3B;
    int bOffsetDone;
    int nWrapAt;
    int nRoom;
    int nClamp;
    int nSlot;
    int nScrollSample;
    int nOffsetSample;

    ctx = data_ov002_0207f614;
    if (ctx->nHeld != 0) {
        return;
    }

    bOffsetDone = (ctx->dwOffsetTweenFlags << 29) >> 31;
    if (bOffsetDone == 0) {
        func_0203602c(ctx->aOffsetTween, &nOffsetSample);
        ctx->nVertOffset = nOffsetSample >> 12;
        ctx->pfnOffsetNotify(0, ctx->nVertOffset);
    }

    if (ctx->nVertOffset > 0x28) {
        nMargin = 0;
    } else {
        nMargin = 0x28 - ctx->nVertOffset;
    }

    if (bOffsetDone != 0 && ((ctx->dwScrollTweenFlags << 29) >> 31) != 0) {
        return;
    }

    func_0203602c(ctx->aScrollTween, &nScrollSample);
    nScroll = nScrollSample >> 12;
    if (*ctx->pLevel < 0xf6) {
        nWrapAt = *ctx->pLevel + 0x10;
        if (nScroll > nWrapAt) {
            nScroll += 0x100 - nWrapAt;
        }
    }

    nRoom = 0x200 - nScroll;
    if (nRoom > 0xff) {
        nClamp = 0xff;
    } else if (nRoom < 1) {
        nClamp = 1;
    } else {
        nClamp = nRoom;
    }

    ctx->nScrollA = nScroll;
    ctx->nScrollB = ctx->nVertOffset + 0xd8;

    if ((data_0204c240 & 6) == 2) {
        switch (ctx->nEmitPhase) {
        case 0:
            nHook2A = 0;
            nHook2B = nClamp;
            nHook3A = 1;
            if (nClamp == 0xff) {
                nMargin = 0;
            }
            nHook3B = nMargin;
            break;
        case 1:
            nHook3B = nMargin;
            nHook2A = nMargin;
            nHook3A = 1;
            nHook2B = 0xff;
            break;
        case 2:
            nHook3A = nClamp;
            nHook3B = 0;
            if (ctx->pFlipHook != 0 && nScroll > 0
                && nRoom + *ctx->pLevel <= 0x1e0) {
                nSlot = ctx->nLevelSlot ^ 1;
                ctx->nLevelSlot = nSlot;
                ctx->pLevel = &ctx->aLevels[nSlot == 0];
                if (ctx->nFlipGate != 0) {
                    if (func_ov002_02063814(ctx->nLevelSlot) == 0) {
                        ctx->nLevelSlot = ctx->nLevelSlot ^ 1;
                    } else {
                        func_ov002_02063350(ctx->nLevelSlot);
                    }
                }
                func_ov002_020554f0();
                nHook2A = 0;
            } else {
                nHook2A = nMargin;
            }
            nHook2B = 0xff;
            break;
        }
    } else {
        nHook3B = nMargin;
        nHook2A = nMargin;
        nHook3A = 1;
        nHook2B = 0xff;
    }

    ctx->nHook2A = nHook2A;
    ctx->nHook2B = nHook2B;
    ctx->nHook3A = nHook3A;
    ctx->nHook3B = nHook3B;
    ctx->nScrollShadow = nScroll;
    ctx->bScrollPending = 1;
}
