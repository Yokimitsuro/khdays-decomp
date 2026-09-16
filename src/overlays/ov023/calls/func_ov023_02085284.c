/* func_ov023_02085284 -- Ov023_CmdStartScreenBlend: script command that starts a screen blend
 * (the weight at +0x2c of the event block, applied by Ov023_ApplyScreenBlend 020838b8).  The
 * weight becomes the fade's level (+0x20) and start (+0x14), operand 0 its end (+0x18),
 * operand 1 its frame count (+0x1c) and the elapsed count (+0x24) is cleared.  Starting from
 * a full weight of 16 in global mode 4 (02020a9c) VRAM bank D goes to the LCDC and a plain
 * capture is armed (DISPCAPCNT 0xc0330010), and the game flag set (02023560 1).  With no frames
 * the end weight is applied at once (Ov023_ScreenBlendDone 02085258) and 1 returned, else the
 * command is re-queued (020219b4) for Ov023_CmdStepScreenBlend (02085310) and 0 returned. */
typedef unsigned char  u8;
typedef unsigned int   u32;

static volatile u32 *const REG_DISPCAPCNT = (volatile u32 *)0x04000064;

typedef struct Ov023EventBlock {
    u8   pad_00[0x14];
    int  nFadeFrom;           /* 0x14 */
    int  nFadeTo;             /* 0x18 */
    int  nFadeFrames;         /* 0x1c */
    int  nFadeLevel;          /* 0x20 */
    int  nFadeElapsed;        /* 0x24 */
    int  nField28;            /* 0x28 */
    int  nBlendWeight;        /* 0x2c */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

extern int  func_02021980(Ov023ScriptCtx *pCtx, void *pOperand);   /* ScriptVm_ReadOperandInt */
extern int  func_02020a9c(void);                                    /* the global mode halfword */
extern void GX_SetBankForLCDC(int nBanks);
extern void func_02023560(int nFlag);
extern void func_ov023_02085258(int nWeight);                       /* Ov023_ScreenBlendDone */
extern void func_020219b4(Ov023ScriptCtx *pCtx, void *pCmd);        /* ScriptVm_RequeueCommand */

int func_ov023_02085284(Ov023ScriptCtx *pCtx, u8 *pOperand)
{
    pCtx->pEvent->nFadeLevel = pCtx->pEvent->nBlendWeight;
    pCtx->pEvent->nFadeFrom = pCtx->pEvent->nFadeLevel;
    pCtx->pEvent->nFadeTo = func_02021980(pCtx, pOperand);
    pCtx->pEvent->nFadeFrames = func_02021980(pCtx, pOperand + 8);
    pCtx->pEvent->nFadeElapsed = 0;
    if (pCtx->pEvent->nBlendWeight == 16) {
        if (func_02020a9c() == 4) {
            GX_SetBankForLCDC(8);
            *REG_DISPCAPCNT = 0xc0330010;
        }
        func_02023560(1);
    }
    if (pCtx->pEvent->nFadeFrames == 0) {
        pCtx->pEvent->nBlendWeight = pCtx->pEvent->nFadeTo;
        func_ov023_02085258(pCtx->pEvent->nBlendWeight);
        return 1;
    }
    func_020219b4(pCtx, pOperand);
    return 0;
}
