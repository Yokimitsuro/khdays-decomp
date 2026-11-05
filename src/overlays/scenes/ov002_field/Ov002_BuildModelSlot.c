
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/archive.h"

typedef struct Ov002ModelDesc {
    s8 nKind;               /* 1, 2 and 4 each start their own animation */
    u8 bEnabled;            /* zero means the slot is not built at all */
    u16 hTint;
    int nParams;
    char pad008[8];
    VecFx32 place;
} Ov002ModelDesc;

typedef struct Ov002ModelBase {
    char pad000[8];
    int nOrder;
    char pad00c[0x28];
    void *apSlots[8];
    s8 nCount;
} Ov002ModelBase;

extern Ov002ModelBase *data_ov002_0207fa10;

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void MI_CpuFill8(void *pDest, u8 nValue, u32 nSize);
extern void Actor_ArmWithMessage(void *p, int nSlot, int a2, int a3, int a4);
extern void Entity_Register(void *p, u32 nParam, int a2, int a3);
extern void Render_SubmitNode(void *p, int nId, int a2, void *pParams);
extern void Obj_SetFlagBit3(void *p, int nMode);
extern void BindAnimTrack(void *p, u16 nIndex, void *pOut, int nMode);

/* Builds the next model slot from a descriptor and starts its animation.  A
   descriptor that is not enabled is dropped without allocating anything. */
void Ov002_BuildModelSlot(Ov002ModelDesc *pDesc, int nId, int nFlag)
{
    Ov002ModelBase *pBase;
    char *pFlags;
    u16 hTint;
    char *pSub;
    int nSlot;
    int i;
    u16 nIdx;
    int nMode;

    pBase = data_ov002_0207fa10;
    nSlot = pBase->nCount;
    if (pDesc->bEnabled == 0) {
        return;
    }

    pBase->apSlots[nSlot] = NNSi_FndAllocFromDefaultExpHeap(0x184);
    MI_CpuFill8(pBase->apSlots[nSlot], 0, 0x184);
    Actor_ArmWithMessage(pBase->apSlots[nSlot], pBase->nCount, 0, 0, 0);
    Entity_Register(pBase->apSlots[nSlot],
                  (ARCHIVE_HANDLE(pBase->nOrder, 0))
                  | (pDesc->bEnabled & 0x1ff), 1, 0);
    *(int *)((char *)pBase->apSlots[nSlot] + 0x180) = 0x1000;
    pBase->nCount = (s8)(pBase->nCount + 1);
    Render_SubmitNode(pBase->apSlots[nSlot], (u16)nId, 0, &pDesc->nParams);

    hTint = pDesc->hTint;
    pFlags = (char *)pBase->apSlots[nSlot] + 0xc;
    if ((*(int *)pFlags & 0x20) == 0) {
        *(u16 *)(pFlags + 0x80) = hTint;
        *(u16 *)(pFlags + 4) = (u16)(*(u16 *)(pFlags + 4) | 0x20);
    }

    *(VecFx32 *)((char *)pBase->apSlots[nSlot] + 0xc0) = pDesc->place;

    switch (pDesc->nKind) {
    case 1:
        nMode = 0;
        if (nFlag == 0) {
            nMode = 1;
        }
        Obj_SetFlagBit3(pBase->apSlots[nSlot], nMode);
        for (i = 0; i < 5; i++) {
            if (*(s16 *)((char *)pBase->apSlots[nSlot] + 0xf0
                         + (u16)i * 2) > 0) {
                pSub = (char *)pBase->apSlots[nSlot] + 0x10;
                BindAnimTrack(pSub, (u16)i, pSub + 0xe0, 0);
            }
        }
        break;

    case 2:
    case 4:
        if (pDesc->nKind == 2) {
            if (nFlag != 0) {
                nMode = 0;
            } else {
                nMode = 1;
            }
        } else {
            nMode = (nFlag != 0) ? 0 : 2;
        }
        for (i = 0; i < 5; i++) {
            if (*(s16 *)((char *)pBase->apSlots[nSlot] + 0xf0
                         + (u16)i * 2) > 0) {
                pSub = (char *)pBase->apSlots[nSlot] + 0x10;
                BindAnimTrack(pSub, (u16)i, pSub + 0xe0, (s16)nMode);
            }
        }
        break;
    }
}
