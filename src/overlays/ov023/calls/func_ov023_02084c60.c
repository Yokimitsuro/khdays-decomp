/* func_ov023_02084c60 -- Ov023_CmdStartBrightnessFade: script command that starts a master
 * brightness fade in the event block (+0x128 of the context).  The current fade level
 * (0201e428) becomes the fade's start (+0x14) and level (+0x20), operand 0 less 16 its end
 * (+0x18), operand 1 its frame count (+0x1c) and the elapsed count (+0x24) is cleared; the
 * level is applied to both engines (0201e374 / 0201e3cc), the command re-queued (020219b4)
 * for Ov023_CmdStepBrightnessFade (02084cc4) and 0 returned. */
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

extern int  func_0201e428(void);                                    /* the current fade level */
extern int  func_02021980(Ov023ScriptCtx *pCtx, void *pOperand);   /* ScriptVm_ReadOperandInt */
extern void func_0201e374(int nLevel);                              /* set the main brightness */
extern void func_0201e3cc(int nLevel);                              /* set the sub brightness */
extern void func_020219b4(Ov023ScriptCtx *pCtx, void *pCmd);        /* ScriptVm_RequeueCommand */

int func_ov023_02084c60(Ov023ScriptCtx *pCtx, u8 *pOperand)
{
    pCtx->pEvent->nBrightness = func_0201e428();
    pCtx->pEvent->nFadeFrom = pCtx->pEvent->nBrightness;
    pCtx->pEvent->nFadeTo = func_02021980(pCtx, pOperand) - 16;
    pCtx->pEvent->nFadeFrames = func_02021980(pCtx, pOperand + 8);
    pCtx->pEvent->nFadeElapsed = 0;
    func_0201e374(pCtx->pEvent->nBrightness);
    func_0201e3cc(pCtx->pEvent->nBrightness);
    func_020219b4(pCtx, pOperand);
    return 0;
}
