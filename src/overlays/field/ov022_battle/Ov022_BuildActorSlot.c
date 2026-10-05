/* ov022: build the actor's own slot from its record.
 *
 * Opens the container the actor's kind names, resets both of its sub blocks,
 * builds the action table and runs the actor's own setup hook with the slot
 * kind from its record, then asks the slot allocator for the slot itself. The
 * path handed to the allocator is not a string at all: it is the packed file
 * spec built from the container's own address and the actor's base index. The
 * container goes back as soon as the slot exists.
 */

#include "nitro/types.h"

#define CONTAINER_HEAP 6
#define BLOCK_COUNT 2
#define KIND_DEFAULT 2
#define KIND_ALT 4

/* Ov022SlotInitParams */
struct SlotInitParams {
    char *pszResourcePath;       /* 0x00 */
    int nResourceKind;           /* 0x04 */
    int aReserved[3];            /* 0x08 */
};

/* Per-id table of 0x104-byte records. */
struct Record {
    u8 pad0000[4];
    u8 nSlotKind;                /* 0x0004 */
    u8 pad0005[0xff];
};

struct SubBlock {
    u8 pad0000[0x164];
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[2];
    int nKind;                   /* 0x000c */
    u8 pad0010[0x668];
    void (*pfnSetup)(struct Actor *pActor, u8 nSlotKind);   /* 0x0678 */
    u8 pad067c[0x294];
    u8 blkActions;               /* 0x0910 */
    u8 pad0911[8];
    u8 nBase;                    /* 0x0919 */
    u8 pad091a[0x48e];
    struct SubBlock aBlocks[BLOCK_COUNT];    /* 0x0da8 */
    u8 pad1070[0x15d8];
    void *aSlots[1];             /* 0x2648 */
    u8 pad264c[0x584];
    void *pContainer;            /* 0x2bd0 */
};

extern struct Record gPartyMembers[];
extern char *data_02042a70[];
extern char gOv022BaChWPathFmt[];

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader(char *pszName, int nHeap);
extern void Ov002_ClearBytes01AndWord160(struct SubBlock *pBlock);
extern void Ov022_BuildActionTable(u8 *pBlkActions, struct Actor *pActor,
                                int nKind, int nSlotKind);
extern void Ov022_AllocateSlotWithClass(void **papSlots, int nId, int nIndex,
                                struct SlotInitParams *pParams);
extern void ZeroHalfThenFree(void *pContainer);

void Ov022_BuildActorSlot(struct Actor *pActor)
{
    char szName[0x80];
    struct SlotInitParams params;
    struct Record *pRec;
    u32 nMask;
    int nBlock;
    struct SubBlock *pBlock;

    pRec = &gPartyMembers[pActor->nId];
    OS_SPrintf(szName, gOv022BaChWPathFmt, data_02042a70[pActor->nKind]);
    pActor->pContainer = Msg_OpenContainerAndReadHeader(szName, CONTAINER_HEAP);
    pBlock = pActor->aBlocks;
    for (nBlock = 0; nBlock < BLOCK_COUNT; nBlock++) {
        Ov002_ClearBytes01AndWord160(pBlock);
        pBlock++;
    }
    Ov022_BuildActionTable(&pActor->blkActions, pActor, pActor->nKind,
                        pRec->nSlotKind);
    pActor->pfnSetup(pActor, pRec->nSlotKind);
    /* The mask is one value: the ROM loads 0xfffffc once and shifts it right
     * by fifteen for the index mask. */
    nMask = 0xfffffc;
    params.pszResourcePath = (char *)(
            ((((u32)pActor->pContainer + 0x8000) & nMask) << 7) | 0x80000000
            | ((pActor->nBase + 0xa0) & (nMask >> 15)));
    params.nResourceKind = KIND_DEFAULT;
    if (pActor->nKind == 2) {
        params.nResourceKind = KIND_ALT;
    }
    Ov022_AllocateSlotWithClass(pActor->aSlots, pActor->nId, 0, &params);
    ZeroHalfThenFree(pActor->pContainer);
}
