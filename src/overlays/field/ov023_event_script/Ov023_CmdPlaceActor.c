/* Ov023_CmdPlaceActor -- Ov023_CmdPlaceActor: script command that places an actor.  Operand 0
 * is the actor (resolved by 02020d10), operand 1 the placement mode, operands 3..5 the position.
 * Without operand 2 the position is applied directly (Entity_SetPosition 0202ba78) with the
 * facing of operand 6 in degrees (x 65536 / 360) stored on the entity (0202bfcc; +0x80, flag
 * bit 5 of +4) unless its bit 5 at +0 is set.  With an "AnchorPos<n>" operand the position is
 * rotated by anchor n's angle (event block +0x474, sin / cos from FX_SinCosTable_) and offset
 * by its position (+0x444), the entity taking the anchor's angle; any other name is passed to
 * the setter as the anchor.  The entity is then shown (0202beb8 1) and, when the actor table
 * (+0x440) exists and the entity's bit 5 (0202c424) is clear, the actor's model is placed too
 * (Ov023_PlaceActorModel 020887dc).  Returns 1. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov023Actor {
    u8   pad_0000[0x1a64];
} Ov023Actor;

typedef struct Ov023EventBlock {
    u8   pad_000[0x440];
    Ov023Actor *pActors;      /* 0x440 */
    VecFx32 aAnchorPos[4];    /* 0x444 */
    int  aAnchorAngle[4];     /* 0x474 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04 */
    u8   pad_06[0x80 - 0x06];
    u16  nAngle;              /* 0x80 */
} Ov023Entity;

extern int   ScriptVm_ReadOperandInt(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandInt */
extern char *ByteCode_ResolveOperand(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandString */
extern int   ScriptVm_ReadOperandFx32(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandFx32 */
extern int   ScriptVm_ResolveActorIndex(Ov023ScriptCtx *pCtx, int nIndex);      /* resolve an actor index */
/* The quotient is the low half of the helper's long long return; writing `/` emits _s32_div_f,
 * which is not linkable here. */
extern long long func_02020400(int nNumerator, int nDenominator);
/* Defined taking nEntity as int, nMode as int: declared narrower here, which is what makes mwcc truncate the
 * argument at the call as the ROM does (declared as defined, the code comes out different). */
extern void  Entity_SubmitRenderNode(u16 nEntity, u16 nMode, char *pszAnchor, VecFx32 *pPos); /* Entity_SetPosition */
extern Ov023Entity *ArrayEntryPtrD0(int nEntity);                     /* Entity_Get */
extern void  Entity_SetVisible(int nEntity, int bVisible);              /* Entity_SetVisible */
extern int   LoadArrayU8At0cc(int nEntity);                            /* Entity_GetFlags */
extern int   strncmp(const char *pA, const char *pB, int nCount);
extern int   func_020200b4(char *pszNumber);                        /* parse a number */
extern int   FX_Mul(int nA, int nB);                           /* FX_Mul */
extern void  Ov023_PlaceActorModel(Ov023Actor *pActor, char *pszAnchor, VecFx32 *pPos, int nMode, int nActor); /* Ov023_PlaceActorModel */
extern const short data_0203d210[];                                 /* FX_SinCosTable_: sin, cos pairs */
extern char  gOv023AnchorPosName[];                                 /* "AnchorPos" */

int Ov023_CmdPlaceActor(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand)
{
    VecFx32 vPos;
    int nActor;
    int nMode;
    char *pszAnchor;
    int nAngle;
    int nAnchor;
    int nX;
    int nSin;
    s16 nCos;
    int nZ;
    Ov023Entity *pEntity;

    nActor = ScriptVm_ResolveActorIndex(pCtx, ScriptVm_ReadOperandInt(pCtx, pOperand));
    nMode = ScriptVm_ReadOperandInt(pCtx, pOperand + 1);
    vPos.x = ScriptVm_ReadOperandFx32(pCtx, pOperand + 3);
    vPos.y = ScriptVm_ReadOperandFx32(pCtx, pOperand + 4);
    vPos.z = ScriptVm_ReadOperandFx32(pCtx, pOperand + 5);
    if (pOperand[2].nType == 0) {
        pszAnchor = 0;
        nAngle = (u16)func_02020400(ScriptVm_ReadOperandInt(pCtx, pOperand + 6) << 16, 360);
        Entity_SubmitRenderNode((u16)nActor, (u16)nMode, 0, &vPos);
        pEntity = ArrayEntryPtrD0((u16)((u16)nActor));
        if (!(pEntity->nFlags & 0x20)) {
            pEntity->nAngle = nAngle;
            pEntity->wFlags |= 0x20;
        }
    } else {
        pszAnchor = ByteCode_ResolveOperand(pCtx, pOperand + 2);
        if (strncmp(pszAnchor, gOv023AnchorPosName, 9) == 0) {
            pszAnchor += 9;
            nAnchor = func_020200b4(pszAnchor);
            nSin = data_0203d210[(pCtx->pEvent->aAnchorAngle[nAnchor] >> 4) * 2];
            nCos = data_0203d210[(pCtx->pEvent->aAnchorAngle[nAnchor] >> 4) * 2 + 1];
            nX = pCtx->pEvent->aAnchorPos[nAnchor].x + FX_Mul(nCos, vPos.x) + FX_Mul(nSin, vPos.z);
            nZ = pCtx->pEvent->aAnchorPos[nAnchor].z + FX_Mul(-nSin, vPos.x) + FX_Mul(nCos, vPos.z);
            vPos.x = nX;
            vPos.z = nZ;
            vPos.y = vPos.y + pCtx->pEvent->aAnchorPos[nAnchor].y;
            Entity_SubmitRenderNode((u16)nActor, (u16)nMode, 0, &vPos);
            nAngle = pCtx->pEvent->aAnchorAngle[nAnchor];
            pEntity = ArrayEntryPtrD0((u16)((u16)nActor));
            if (!(pEntity->nFlags & 0x20)) {
                pEntity->nAngle = nAngle;
                pEntity->wFlags |= 0x20;
            }
            pszAnchor = 0;
        } else {
            Entity_SubmitRenderNode((u16)nActor, (u16)nMode, pszAnchor, &vPos);
        }
    }
    Entity_SetVisible((u16)((u16)nActor), 1);
    if (pCtx->pEvent->pActors != 0 && !(LoadArrayU8At0cc(nActor & 0xffff) & 0x20)) {
        Ov023_PlaceActorModel(&pCtx->pEvent->pActors[nActor], pszAnchor, &vPos, nMode, nActor);
    }
    return 1;
}
