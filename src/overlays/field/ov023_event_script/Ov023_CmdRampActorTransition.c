/* Ov023_CmdRampActorTransition -- Ov023_CmdRampActorTransition: script command that restarts an actor's
 * transition (Entity_StartTransition 0202bef4, mode 1) every frame with a duration eased from
 * operand 1 to operand 2 over operand 3 frames.  The frame count lives in the command block
 * itself (+0x24) and is counted down here; while it runs the eased duration (Anim_GetBlendFactor
 * 0202136c mode 2, Anim_Interpolate 02021404) is applied, the command is re-queued (020219b4)
 * and 0 returned; on the last frame the final duration is applied and 1 returned. */

#include "nitro/types.h"

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

typedef struct Ov023RampCmd {
    Ov023Operand aOperand[4]; /* 0x00: actor, from, to, frames */
    int  nField20;            /* 0x20 */
    int  nRemaining;          /* 0x24 */
} Ov023RampCmd;

extern int   ScriptVm_ReadOperandInt(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandInt */
extern int   ScriptVm_ReadOperandFx32(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandFx32 */
extern void *ArrayEntryPtrD0(int nEntity);                            /* Entity_Get */
extern void  EntityMgr_SetTransition(int nEntity, int bEnable, int nDuration); /* Entity_StartTransition */
extern int   Anim_GetBlendFactor(int nMode, int nTotal, int nRemaining);  /* Anim_GetBlendFactor */
extern int   ScaleAroundPivot(int nFactor, int nFrom, int nTo);        /* Anim_Interpolate */
extern void  Slot48_StoreAtCurrentIndex(void *pCtx, void *pCmd);                 /* ScriptVm_RequeueCommand */

int Ov023_CmdRampActorTransition(void *pCtx, Ov023RampCmd *pCmd)
{
    int nActor;
    int nFrames;
    int nFrom;
    int nTo;

    nActor = ScriptVm_ReadOperandInt(pCtx, &pCmd->aOperand[0]);
    nFrames = ScriptVm_ReadOperandInt(pCtx, &pCmd->aOperand[3]);
    nFrom = ScriptVm_ReadOperandFx32(pCtx, &pCmd->aOperand[1]);
    nTo = ScriptVm_ReadOperandFx32(pCtx, &pCmd->aOperand[2]);
    ArrayEntryPtrD0((u16)((u16)nActor));
    pCmd->nRemaining--;
    if (pCmd->nRemaining == 0) {
        EntityMgr_SetTransition(nActor & 0xffff, 1, nTo);
        return 1;
    }
    EntityMgr_SetTransition(nActor & 0xffff, 1, ScaleAroundPivot(Anim_GetBlendFactor(2, nFrames, pCmd->nRemaining), nTo, nFrom));
    Slot48_StoreAtCurrentIndex(pCtx, pCmd);
    return 0;
}
