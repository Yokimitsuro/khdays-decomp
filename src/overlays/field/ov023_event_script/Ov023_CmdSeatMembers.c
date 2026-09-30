/* Ov023_CmdSeatMembers -- Ov023_CmdSeatMembers: script command that seats the party actors.
 * A copy of the 13 seat heights (data_ov023_02089ddc) is taken.  Without operand 0 all 13
 * seats are filled: actor i gets the chair resource (gOv023MiOb0CPath, 0202b914 1 / 0xd),
 * is placed on the spot "chair<i>" (Ov023_FormatSeatName 02086c90, 0202ba78) at the seat's
 * height + 0xda01 above the origin, and its model is placed at the entity's position
 * (0202bfcc +0xa8, 020887dc).  With operand 0 (the actor) and operand 1 (an extra height)
 * only that actor is moved to its chair spot (0202c3e4) raised by the extra, the seat height
 * and 0xda01 (0202b450).  Returns 1. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

typedef struct Ov023Entity {
    u8   pad_00[0xa8];
    VecFx32 vPos;             /* 0xa8 */
} Ov023Entity;

typedef struct Ov023Actor {
    u8   pad_0000[0x1a64];
} Ov023Actor;

typedef struct Ov023EventBlock {
    u8   pad_000[0x440];
    Ov023Actor *pActors;      /* 0x440 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

typedef struct Ov023SeatHeights {
    int  aHeight[13];         /* 0x00 */
} Ov023SeatHeights;

extern int   ScriptVm_ReadOperandInt(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandInt */
extern int   ScriptVm_ReadOperandFx32(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandFx32 */
extern void  TailForwardTrackEntry(int nEntity, void *pTable, int nA, int nB); /* Entity_BindResource */
extern char *Ov023_FormatIndex(int nIndex);                       /* Ov023_FormatSeatName */
extern void  strcpy(char *pszDst, const char *pszSrc);       /* STD_CopyString */
/* Defined taking nEntity as int, nMode as int: declared narrower here, which is what makes mwcc truncate the
 * argument at the call as the ROM does (declared as defined, the code comes out different). */
extern void  Entity_SubmitRenderNode(u16 nEntity, u16 nMode, char *pszSpot, VecFx32 *pPos); /* Entity_SetPosition */
extern Ov023Entity *ArrayEntryPtrD0(int nEntity);                     /* Entity_Get */
extern void  Ov023_PlaceActorModel(Ov023Actor *pActor, char *pszAnchor, VecFx32 *pPos, int nMode, int nActor); /* Ov023_PlaceActorModel */
extern void  EntityMgr_ProbeGround(int nModel, char *pszSpot, VecFx32 *pOut); /* Model_GetSpotPosition */
extern void  Actor_SetVecAndSyncChild(Ov023Entity *pEntity, VecFx32 *pPos);   /* Entity_SetPositionNow */
extern const Ov023SeatHeights data_ov023_02089ddc;                  /* the seat heights */
extern const VecFx32 data_02041dc8;                                 /* the zero vector */
extern char  gOv023MiOb0CPath[];                                 /* "/mi/ob/0C.z", the chair model */

int Ov023_CmdSeatMembers(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand)
{
    VecFx32 vPos;
    char szSpot[0x40];
    Ov023SeatHeights heights;
    int i;
    int nActor;
    int nExtra;
    Ov023Entity *pEntity;

    heights = data_ov023_02089ddc;
    if (pOperand->nType == 0) {
        VecFx32 vOffset;

        vOffset = data_02041dc8;
        for (i = 0; i < 13; i++) {
            TailForwardTrackEntry(i & 0xffff, gOv023MiOb0CPath, 1, 0xd);
            vOffset.y = heights.aHeight[i] + 0xda01;
            strcpy(szSpot, Ov023_FormatIndex(i));
            Entity_SubmitRenderNode((u16)i, 0, szSpot, &vOffset);
            vPos = ArrayEntryPtrD0((u16)((u16)i))->vPos;
            Ov023_PlaceActorModel(&pCtx->pEvent->pActors[i], 0, &vPos, 0, i);
        }
    } else {
        nExtra = ScriptVm_ReadOperandFx32(pCtx, pOperand + 1);
        nActor = ScriptVm_ReadOperandInt(pCtx, pOperand);
        pEntity = ArrayEntryPtrD0((u16)((u16)nActor));
        strcpy(szSpot, Ov023_FormatIndex(nActor));
        EntityMgr_ProbeGround((u16)0, szSpot, &vPos);
        vPos.y += nExtra + (heights.aHeight[nActor] + 0xda01);
        Actor_SetVecAndSyncChild(pEntity, &vPos);
    }
    return 1;
}
