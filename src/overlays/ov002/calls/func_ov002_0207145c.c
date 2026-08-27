typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Ov002Vec3 {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct Ov002ModelDesc {
    s8 nKind;               /* 1, 2 and 4 each start their own animation */
    u8 bEnabled;            /* zero means the slot is not built at all */
    u16 hTint;
    int nParams;
    char pad008[8];
    Ov002Vec3 place;
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
extern void func_0202b87c(void *p, int nSlot, int a2, int a3, int a4);
extern void func_0202b930(void *p, u32 nParam, int a2, int a3);
extern void func_0202ba9c(void *p, u16 nId, int a2, void *pParams);
extern void func_0202bedc(void *p, int nMode);
extern void func_0202accc(void *p, u16 nIndex, void *pOut, int nMode);

/* Builds the next model slot from a descriptor and starts its animation.  A
   descriptor that is not enabled is dropped without allocating anything. */
void func_ov002_0207145c(Ov002ModelDesc *pDesc, int nId, int nFlag)
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
    func_0202b87c(pBase->apSlots[nSlot], pBase->nCount, 0, 0, 0);
    func_0202b930(pBase->apSlots[nSlot],
                  ((((pBase->nOrder + 0x8000) & 0xfffffc) << 7) | 0x80000000)
                  | (pDesc->bEnabled & 0x1ff), 1, 0);
    *(int *)((char *)pBase->apSlots[nSlot] + 0x180) = 0x1000;
    pBase->nCount = (s8)(pBase->nCount + 1);
    func_0202ba9c(pBase->apSlots[nSlot], (u16)nId, 0, &pDesc->nParams);

    hTint = pDesc->hTint;
    pFlags = (char *)pBase->apSlots[nSlot] + 0xc;
    if ((*(int *)pFlags & 0x20) == 0) {
        *(u16 *)(pFlags + 0x80) = hTint;
        *(u16 *)(pFlags + 4) = (u16)(*(u16 *)(pFlags + 4) | 0x20);
    }

    *(Ov002Vec3 *)((char *)pBase->apSlots[nSlot] + 0xc0) = pDesc->place;

    switch (pDesc->nKind) {
    case 1:
        nMode = 0;
        if (nFlag == 0) {
            nMode = 1;
        }
        func_0202bedc(pBase->apSlots[nSlot], nMode);
        for (i = 0; i < 5; i++) {
            if (*(s16 *)((char *)pBase->apSlots[nSlot] + 0xf0
                         + (u16)i * 2) > 0) {
                pSub = (char *)pBase->apSlots[nSlot] + 0x10;
                func_0202accc(pSub, (u16)i, pSub + 0xe0, 0);
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
                func_0202accc(pSub, (u16)i, pSub + 0xe0, (s16)nMode);
            }
        }
        break;
    }
}
