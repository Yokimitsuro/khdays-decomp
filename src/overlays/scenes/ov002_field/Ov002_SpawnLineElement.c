
#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 data_0204c240;

extern char *Ov002_ClaimPoolEntry(void *pClass, int nSlot);
extern void Actor_ArmWithMessage(char *pObj, int a, void *pOwner, int c, int d);
extern void Actor_SetVecAndSyncChild(char *pNode, const VecFx32 *pPos);
extern void Ov002_PushBucketNode(int nRoom, char *pElement);
extern void strcpy(void *pDst, const void *pSrc);

extern void Ov002_ElementGatherActors(void);
extern void Ov002_ElementPromptStep(void);

/* Spawn one line element of a class.
 *
 * Claims an entry, binds its object, puts the node at the caller's position and
 * keeps that position where the element can find it again. The step handler
 * depends on the global gate: with it closed the element gathers actors first,
 * with it open it goes straight to the prompt. The element starts with its
 * pending bit raised, no pose and no progress, and takes the caller's prompt
 * text when there is one.
 */
char *Ov002_SpawnLineElement(char *pClass, int nSlot, int nRoom, u16 wStateField,
                          u8 bStateWidth, const VecFx32 *pPos, short nAngle,
                          const void *pText)
{
    char *pElement;
    void (*pfnStep)(void);

    pElement = Ov002_ClaimPoolEntry(pClass, nSlot);

    Actor_ArmWithMessage(pElement + 0x2c, 0, pElement, 0, 0);

    *(int *)(pElement + 0x1ac) = 0x1000;
    Actor_SetVecAndSyncChild(pElement + 0x38, pPos);

    *(short *)(pElement + 0x18) = nAngle;
    *(VecFx32 *)(pElement + 0x1c) = *(VecFx32 *)(pElement + 0xe0);

    *(int *)(pElement + 0x28) = *(short *)(pClass + 0x68);
    *(u8 *)(pElement + 0x10) = (u8)nRoom;

    if ((data_0204c240 & 4) != 0) {
        pfnStep = Ov002_ElementGatherActors;
    } else {
        pfnStep = Ov002_ElementPromptStep;
    }
    *(int *)(pElement + 0x0c) = (int)pfnStep;

    *(u16 *)(pElement + 0x14) = wStateField;
    *(u8 *)(pElement + 0x16) = bStateWidth;
    *(u8 *)(pElement + 0x17) = 0;

    Ov002_PushBucketNode(nRoom, pElement);

    *(u8 *)(pElement + 0x1b5) = 0x80;
    *(signed char *)(pElement + 0x1b4) = -1;
    *(int *)(pElement + 0x1b0) = 0;

    if (pText != 0) {
        strcpy(pElement + 0x1bb, pText);
    }

    return pElement;
}
