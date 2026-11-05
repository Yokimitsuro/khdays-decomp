
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
extern void Ov002_TravelElementStep(void);

/* Spawn one travelling element of a class.
 *
 * Claims a pool entry for the slot, places its scene node with the class's
 * placement parameters, builds the start position from the requested one and
 * syncs the child actor. Then stamps the angle, position, extent, bucket, the
 * travel step hook, the travel parameter and the state field descriptor. A
 * negative travel parameter starts the element hidden. The travel state is
 * cleared out - no step, no track, no distance and no entry - and the element
 * is pushed into its bucket.
 */
char *Ov002_SpawnTravelElement(char *pClass, u16 wSlot, u16 wBucket,
                          u16 wStateField, u8 bStateWidth, VecFx32 *pPos,
                          s16 nAngle, s16 nTravelParam)
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
    *(void **)(pElement + 0x0c) = (void *)Ov002_TravelElementStep;
    *(s16 *)(pElement + 0x2c4) = nTravelParam;
    if (nTravelParam < 0) {
        *(u16 *)(pElement + 0x12) &= ~8;
    } else {
        *(u16 *)(pElement + 0x12) |= 8;
    }
    *(u8 *)(pElement + 0x17) = 1;
    *(s16 *)(pElement + 0x14) = (s16)wStateField;
    *(u8 *)(pElement + 0x16) = bStateWidth;
    *(u8 *)(pElement + 0x2c1) = 0;
    *(u8 *)(pElement + 0x2c0) = 0;
    *(int *)(pElement + 0x2bc) = 0;
    *(int *)(pElement + 0x2b8) = 0;
    *(u8 *)(pElement + 0x2c2) = 0xff;
    *(u8 *)(pElement + 0x2c3) = 0;

    Ov002_PushBucketNode(wBucket, pElement);
    return pElement;
}
