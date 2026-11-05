/* Ov016_HazardCreate -- Ov016_HazardCreate: take a hazard piece from the class table (ov002
 * 02076a38), touch the bucket's seat slot (ov002 0207285c), set the render node up (+0x2c,
 * 0202b87c with the piece as owner, mode 1) and put it at pPos (0202b450 on +0x38); then fill
 * the piece: facing (+0x18), active (+0x2bc), the start position copied from +0xe0 to +0x1c,
 * the class's sequence (+0x28 from def +0x6e), bucket (+0x10), the step function (+0xc =
 * Ov016_HazardStep 02082444), +0x17 = 0 and the GameState field / bit (+0x14 / +0x16); finally
 * register the piece (02076480). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov016HazardDef {
    u8 pad_00[0x6e];
    short nSequence;          /* 0x6e */
} Ov016HazardDef;

typedef struct Ov016Hazard {
    u8 pad_000[0xc];
    void *pfnStep;            /* 0x0c */
    u8  nRoom;              /* 0x10 */
    u8  pad_011[3];
    u16 nStateField;          /* 0x14: GameState field */
    u8  nStateBit;            /* 0x16 */
    u8  nField17;             /* 0x17 */
    short nFacing;            /* 0x18 */
    u8  pad_01a[2];
    VecFx32 start;            /* 0x1c */
    int nSequence;            /* 0x28 */
    u8  renderNode[0x38 - 0x2c]; /* 0x2c */
    u8  transform[0xe0 - 0x38];  /* 0x38 */
    VecFx32 position;         /* 0xe0 */
    u8  pad_0ec[0x2bc - 0xec];
    u8  bActive;              /* 0x2bc */
} Ov016Hazard;

extern Ov016Hazard *Ov002_ClaimPoolEntry(Ov016HazardDef *pClass, int nSlot); /* take a piece from the class table */
extern int   Ov002_GetCtxTableByte(int nRoom);                            /* bucket -> seat slot */
extern void  Actor_ArmWithMessage(void *pNode, int nA, void *pOwner, void *pB, int nMode);
extern void  Actor_SetVecAndSyncChild(void *pTransform, VecFx32 *pVec);              /* Actor_SetVecAndSyncChild */
extern void  Ov002_PushBucketNode(int nRoom, void *pPiece);              /* register the piece */
extern void *Ov016_HazardStep(Ov016Hazard *pSelf);                     /* Ov016_HazardStep */

Ov016Hazard *Ov016_HazardCreate(Ov016HazardDef *pClass, u16 nSlot, u8 nRoom, u16 nField, u8 nBit, VecFx32 *pPos, short nFacing)
{
    Ov016Hazard *pPiece;

    pPiece = Ov002_ClaimPoolEntry(pClass, nSlot);
    Ov002_GetCtxTableByte(nRoom);
    Actor_ArmWithMessage(pPiece->renderNode, 0, pPiece, 0, 1);
    Actor_SetVecAndSyncChild(pPiece->transform, pPos);
    pPiece->nFacing = nFacing;
    pPiece->bActive = 1;
    pPiece->start = pPiece->position;
    pPiece->nSequence = pClass->nSequence;
    pPiece->nRoom = nRoom;
    pPiece->pfnStep = (void *)Ov016_HazardStep;
    pPiece->nField17 = 0;
    pPiece->nStateField = nField;
    pPiece->nStateBit = nBit;
    Ov002_PushBucketNode(nRoom, pPiece);
    return pPiece;
}
