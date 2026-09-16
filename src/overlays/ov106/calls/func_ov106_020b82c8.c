/* func_ov106_020b82c8 -- Ov106_CmdStepLightFade: one frame of the light fade started by
 * Ov023_CmdStartLightFade (02086fac).  Operand 2 is the light.  The elapsed count (+0x24 of
 * the event block) advances, the level (+0x20) becomes from + elapsed * (to - from) / frames
 * clamped to 0..31 and is applied (Ov023_SetLightLevel 02089cdc).  Returns 1 once the elapsed
 * count reaches the frame count, else 0. *
 * PROVENANCE: byte-identical twin of ov023's Ov023_CmdStepLightFade (func_ov023_02087018), same code and
 * callees, verified byte-exact in this overlay. */
typedef unsigned char  u8;

typedef struct Ov023EventBlock {
    u8   pad_00[0x14];
    int  nFadeFrom;           /* 0x14 */
    int  nFadeTo;             /* 0x18 */
    int  nFadeFrames;         /* 0x1c */
    int  nFadeLevel;          /* 0x20 */
    int  nFadeElapsed;        /* 0x24 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

/* The quotient is the low half of the helper's long long return; writing `/` emits _s32_div_f,
 * which is not linkable here. */
extern long long func_02020400(int nNumerator, int nDenominator);
extern int  func_02021980(Ov023ScriptCtx *pCtx, void *pOperand);   /* ScriptVm_ReadOperandInt */
extern void func_ov106_020b8a4c(int nLevel, int nLight);            /* Ov023_SetLightLevel */

int func_ov106_020b82c8(Ov023ScriptCtx *pCtx, u8 *pOperand)
{
    Ov023EventBlock *pEvent;
    int nFrom;
    int nLight;

    nLight = func_02021980(pCtx, pOperand + 0x10);
    pCtx->pEvent->nFadeElapsed++;
    pEvent = pCtx->pEvent;
    nFrom = pEvent->nFadeFrom;
    pEvent->nFadeLevel = nFrom + (int)func_02020400(pEvent->nFadeElapsed * (pEvent->nFadeTo - nFrom), pEvent->nFadeFrames);
    if (pCtx->pEvent->nFadeLevel > 31) {
        pCtx->pEvent->nFadeLevel = 31;
    }
    if (pCtx->pEvent->nFadeLevel < 0) {
        pCtx->pEvent->nFadeLevel = 0;
    }
    func_ov106_020b8a4c(pCtx->pEvent->nFadeLevel, nLight);
    if (pCtx->pEvent->nFadeElapsed >= pCtx->pEvent->nFadeFrames) {
        return 1;
    }
    return 0;
}
