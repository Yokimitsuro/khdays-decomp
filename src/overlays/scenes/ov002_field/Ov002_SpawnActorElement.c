
#include "nitro/types.h"
#include "nitro/fx_types.h"

extern char *Ov002_ClaimPoolEntry(char *pClass, int nSlot);
extern int Ov002_GetCtxTableByte(int nSlot);
extern int Actor_ArmWithMessage(int nNode, int nZero, void *pObj, void *pParams,
                         int nFlag);
extern int EntityMgr_ProbeGround(int nId, int nSpot, VecFx32 *pOut);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void Actor_SetVecAndSyncChild(char *pNode, VecFx32 *pPos);
extern short EntityMgr_GetCollEntryField14(int nId, int nSpot);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nSize);
extern void Ov002_PushBucketNode(int nBucket, char *pElement);
extern void *Ov002_ElementPhase_WatchStateBit(char *pElement);

/* Spawn one actor element of a class.
 *
 * Claims a pool entry, attaches its object and puts it either at a named spot
 * of the slot's context - offset by the caller's vector when there is one -
 * or straight at the caller's position and angle. The owner's cached vector is
 * copied in, the slot, handler, game-state descriptor and name are stamped,
 * and the class's kind decides which of the four modes get a track.
 */
char *Ov002_SpawnActorElement(char *pClass, int nSlot, int nBucket,
                          u16 wStateField, unsigned char bStateWidth,
                          const char *pName, signed char bTrackIndex,
                          int nSpot, VecFx32 *pPos, const VecFx32 *pBound,
                          short nAngle)
{
    char *pElement;
    char *pOwner;
    int nId;
    signed char nKind;
    VecFx32 vSpot;

    pElement = Ov002_ClaimPoolEntry(pClass, nSlot);
    pOwner = *(char **)(pElement + 8);
    nId = Ov002_GetCtxTableByte(nBucket);

    Actor_ArmWithMessage((int)(pElement + 0x1c), 0, pElement, 0, 1);

    if (nSpot != 0 && EntityMgr_ProbeGround(nId & 0xffff, nSpot, &vSpot) != 0) {
        if (pPos != 0) {
            VEC_Add(&vSpot, pPos, &vSpot);
        }
        Actor_SetVecAndSyncChild(pElement + 0x28, &vSpot);
        *(short *)(pElement + 0x18) = EntityMgr_GetCollEntryField14((u16)((u16)nId), nSpot);
    } else {
        Actor_SetVecAndSyncChild(pElement + 0x28, pPos);
        *(short *)(pElement + 0x18) = nAngle;
    }

    if (*(signed char *)(pOwner + 0x58) != 0) {
        *(VecFx32 *)(pElement + 0xdc) = *pBound;
    }

    *(unsigned char *)(pElement + 0x10) = (unsigned char)nBucket;
    *(int *)(pElement + 0x0c) = (int)Ov002_ElementPhase_WatchStateBit;
    *(u16 *)(pElement + 0x14) = wStateField;
    *(unsigned char *)(pElement + 0x16) = bStateWidth;
    *(unsigned char *)(pElement + 0x17) = 0;

    if (pName != 0) {
        strncpy(pElement + 0x1a0, pName, 0x20);
    } else {
        *(unsigned char *)(pElement + 0x1a0) = 0;
    }

    *(signed char *)(pElement + 0x1c0) = bTrackIndex;
    *(unsigned char *)(pElement + 0x1c1) = 0;

    nKind = *(signed char *)(pOwner + 0x80);
    switch (nKind) {
    case 1:
        *(signed char *)(pElement + 0x1c3) = -1;
        *(signed char *)(pElement + 0x1c4) = -1;
        *(signed char *)(pElement + 0x1c5) = 0;
        *(signed char *)(pElement + 0x1c6) = -1;
        break;
    case 2:
        *(signed char *)(pElement + 0x1c3) = 0;
        *(signed char *)(pElement + 0x1c4) = -1;
        *(signed char *)(pElement + 0x1c5) = 1;
        *(signed char *)(pElement + 0x1c6) = -1;
        break;
    case 4:
        *(signed char *)(pElement + 0x1c3) = 0;
        *(signed char *)(pElement + 0x1c4) = 1;
        *(signed char *)(pElement + 0x1c5) = 2;
        *(signed char *)(pElement + 0x1c6) = 3;
        break;
    }

    Ov002_PushBucketNode(nBucket, pElement);
    return pElement;
}
