/* func_ov023_020845a0 -- Ov023_CmdRampActorTransition: script command that restarts an actor's
 * transition (Entity_StartTransition 0202bef4, mode 1) every frame with a duration eased from
 * operand 1 to operand 2 over operand 3 frames.  The frame count lives in the command block
 * itself (+0x24) and is counted down here; while it runs the eased duration (Anim_GetBlendFactor
 * 0202136c mode 2, Anim_Interpolate 02021404) is applied, the command is re-queued (020219b4)
 * and 0 returned; on the last frame the final duration is applied and 1 returned. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

typedef struct Ov023RampCmd {
    Ov023Operand aOperand[4]; /* 0x00: actor, from, to, frames */
    int  nField20;            /* 0x20 */
    int  nRemaining;          /* 0x24 */
} Ov023RampCmd;

extern int   func_02021980(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandInt */
extern int   func_02021994(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandFx32 */
extern void *func_0202bfcc(u16 nEntity);                            /* Entity_Get */
extern void  func_0202bef4(u16 nEntity, int bEnable, int nDuration); /* Entity_StartTransition */
extern int   func_0202136c(int nMode, int nTotal, int nRemaining);  /* Anim_GetBlendFactor */
extern int   func_02021404(int nFactor, int nFrom, int nTo);        /* Anim_Interpolate */
extern void  func_020219b4(void *pCtx, void *pCmd);                 /* ScriptVm_RequeueCommand */

int func_ov023_020845a0(void *pCtx, Ov023RampCmd *pCmd)
{
    int nActor;
    int nFrames;
    int nFrom;
    int nTo;

    nActor = func_02021980(pCtx, &pCmd->aOperand[0]);
    nFrames = func_02021980(pCtx, &pCmd->aOperand[3]);
    nFrom = func_02021994(pCtx, &pCmd->aOperand[1]);
    nTo = func_02021994(pCtx, &pCmd->aOperand[2]);
    func_0202bfcc((u16)nActor);
    pCmd->nRemaining--;
    if (pCmd->nRemaining == 0) {
        func_0202bef4((u16)nActor, 1, nTo);
        return 1;
    }
    func_0202bef4((u16)nActor, 1, func_02021404(func_0202136c(2, nFrames, pCmd->nRemaining), nTo, nFrom));
    func_020219b4(pCtx, pCmd);
    return 0;
}
