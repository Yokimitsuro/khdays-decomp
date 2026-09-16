/* func_ov023_02086fac -- Ov023_CmdStartLightFade: script command that starts a fade of one of
 * the light levels (data_ov023_0208a7c0 slots, +0x68; Ov023_GetLightLevel 02089cec /
 * Ov023_SetLightLevel 02089cdc) in the event block's fade fields.  Operand 2 is the light,
 * whose current level becomes the fade's level (+0x20) and start (+0x14); operand 0 is the end
 * (+0x18), operand 1 the frame count (+0x1c) and the elapsed count (+0x24) is cleared.  The
 * command is re-queued (020219b4) for Ov023_CmdStepLightFade (02087018); with no frames the
 * end level is applied at once and 1 returned, else 0. */
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

extern int  func_02021980(Ov023ScriptCtx *pCtx, void *pOperand);   /* ScriptVm_ReadOperandInt */
extern int  func_ov023_02089cec(int nLight);                        /* Ov023_GetLightLevel */
extern void func_ov023_02089cdc(int nLevel, int nLight);            /* Ov023_SetLightLevel */
extern void func_020219b4(Ov023ScriptCtx *pCtx, void *pCmd);        /* ScriptVm_RequeueCommand */

int func_ov023_02086fac(Ov023ScriptCtx *pCtx, u8 *pOperand)
{
    int nLight;

    nLight = func_02021980(pCtx, pOperand + 0x10);
    pCtx->pEvent->nFadeLevel = func_ov023_02089cec(nLight);
    pCtx->pEvent->nFadeFrom = pCtx->pEvent->nFadeLevel;
    pCtx->pEvent->nFadeTo = func_02021980(pCtx, pOperand);
    pCtx->pEvent->nFadeFrames = func_02021980(pCtx, pOperand + 8);
    pCtx->pEvent->nFadeElapsed = 0;
    func_020219b4(pCtx, pOperand);
    if (pCtx->pEvent->nFadeFrames == 0) {
        func_ov023_02089cdc(pCtx->pEvent->nFadeTo, nLight);
        return 1;
    }
    return 0;
}
