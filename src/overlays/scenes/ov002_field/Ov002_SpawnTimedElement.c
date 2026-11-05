
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern char *Ov002_ClaimPoolEntry(char *pClass, int nSlot);
extern int Ov002_PlaceElementNode(void *pObj, int nNode, void *pOut,
                                int nUnused, int nKind, int nParamA,
                                int nParamB, int nParamC,
                                int nAngle, int nFlag);
extern void Ov002_BuildSpawnPosition(VecFx32 *pOut, VecFx32 *pPos, int *pIn);
extern void Ov002_PushBucketNode(int nRoom, char *pElement);
extern void Ov002_ElementTickTimer(void);

/* Spawn one timed element of a class.
 *
 * Claims a pool entry for the slot, places its scene node with the class's
 * placement parameters, builds the start position from the requested one and
 * syncs the child actor. Then stamps the angle, position, extent, bucket, the
 * timer tick hook, the flags and the state field descriptor, pushes the node
 * into its bucket and clears the phase and the elapsed counter.
 */
char *Ov002_SpawnTimedElement(char *pClass, u16 wSlot, u16 wBucket,
                          u16 wStateField, u8 bStateWidth, VecFx32 *pPos,
                          s16 nAngle)
{
    VecFx32 vStart;
    int aPlace[5];
    char *pElement;

    pElement = Ov002_ClaimPoolEntry(pClass, wSlot);
    Ov002_PlaceElementNode(pElement, (int)(pElement + 0x2c), aPlace, wSlot,
                        *(s8 *)(pClass + 0x6c),
                        *(s16 *)(pClass + 0x6e),
                        *(s16 *)(pClass + 0x70),
                        *(s16 *)(pClass + 0x72),
                        nAngle, 1);
    Ov002_BuildSpawnPosition(&vStart, pPos, aPlace);
    Actor_SetVecAndSyncChild(pElement + 0x38, pPos);

    *(s16 *)(pElement + 0x18) = nAngle;
    *(VecFx32 *)(pElement + 0x1c) = vStart;
    *(int *)(pElement + 0x28) = aPlace[2];
    *(u8 *)(pElement + 0x10) = (u8)wBucket;
    *(void **)(pElement + 0x0c) = (void *)Ov002_ElementTickTimer;
    *(u16 *)(pElement + 0x12) |= 0x48;
    *(s16 *)(pElement + 0x14) = (s16)wStateField;
    *(u8 *)(pElement + 0x16) = bStateWidth;
    *(u8 *)(pElement + 0x17) = 0;
    *(u8 *)(pElement + 0x1b9) = 0;
    *(u8 *)(pElement + 0x1b8) = 0;

    Ov002_PushBucketNode(wBucket, pElement);

    *(u8 *)(pElement + 0x1bb) = 0;
    *(int *)(pElement + 0x1b4) = 0;
    return pElement;
}
