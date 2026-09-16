/* func_ov023_02084cc4 -- Ov023_CmdStepBrightnessFade: one frame of the master brightness fade
 * started by Ov023_CmdStartBrightnessFade (02084c60).  The elapsed count (+0x24 of the event
 * block) advances and the level (+0x20) becomes from + elapsed * (to - from) / frames, clamped to
 * -16..16, then goes to both engines (0201e374 / 0201e3cc); in global mode 0xc (02020a9c) it is
 * also pushed onto both fade tweens (02083d2c 0 / 1, no duration).  Returns 1 once the elapsed
 * count reaches the frame count, else 0. */
typedef unsigned char  u8;

typedef struct Ov023EventBlock {
    u8   pad_00[0x14];
    int  nFadeFrom;           /* 0x14 */
    int  nFadeTo;             /* 0x18 */
    int  nFadeFrames;         /* 0x1c */
    int  nBrightness;         /* 0x20 */
    int  nFadeElapsed;        /* 0x24 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

/* The quotient is the low half of the helper's long long return; writing `/` emits _s32_div_f,
 * which is not linkable here. */
extern long long func_02020400(int nNumerator, int nDenominator);
extern void func_0201e374(int nLevel);                              /* set the main brightness */
extern void func_0201e3cc(int nLevel);                              /* set the sub brightness */
extern int  func_02020a9c(void);                                    /* the global mode halfword */
extern void func_ov023_02083d2c(int nIndex, int nTarget, int nDuration); /* Ov023_PushTween */

int func_ov023_02084cc4(Ov023ScriptCtx *pCtx)
{
    Ov023EventBlock *pEvent;
    int nFrom;

    pCtx->pEvent->nFadeElapsed++;
    pEvent = pCtx->pEvent;
    nFrom = pEvent->nFadeFrom;
    pEvent->nBrightness = nFrom + (int)func_02020400(pEvent->nFadeElapsed * (pEvent->nFadeTo - nFrom), pEvent->nFadeFrames);
    if (pCtx->pEvent->nBrightness > 16) {
        pCtx->pEvent->nBrightness = 16;
    }
    if (pCtx->pEvent->nBrightness < -16) {
        pCtx->pEvent->nBrightness = -16;
    }
    func_0201e374(pCtx->pEvent->nBrightness);
    func_0201e3cc(pCtx->pEvent->nBrightness);
    if (func_02020a9c() == 0xc) {
        func_ov023_02083d2c(0, pCtx->pEvent->nBrightness, 0);
        func_ov023_02083d2c(1, pCtx->pEvent->nBrightness, 0);
    }
    if (pCtx->pEvent->nFadeElapsed >= pCtx->pEvent->nFadeFrames) {
        return 1;
    }
    return 0;
}
