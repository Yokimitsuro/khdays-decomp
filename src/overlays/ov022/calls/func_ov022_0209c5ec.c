/* ov022: build the actor's own slot from its record.
 *
 * Opens the container the actor's kind names, resets both of its sub blocks,
 * builds the action table and runs the actor's own setup hook with the slot
 * kind from its record, then asks the slot allocator for the slot itself. The
 * path handed to the allocator is not a string at all: it is the packed file
 * spec built from the container's own address and the actor's base index. The
 * container goes back as soon as the slot exists.
 */

typedef unsigned char u8;
typedef unsigned int u32;

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

extern struct Record data_0204c678[];
extern char *data_02042a70[];
extern char data_ov022_020b2ce4[];

extern void OS_SPrintf(char *pszOut, char *pszFormat, char *pszName);
extern void *func_02024ee8(char *pszName, int nHeap);
extern void func_ov002_02051b20(struct SubBlock *pBlock);
extern void func_ov022_020b0720(u8 *pBlkActions, struct Actor *pActor,
                                int nKind, int nSlotKind);
extern void func_ov022_02092384(void **papSlots, int nId, int nIndex,
                                struct SlotInitParams *pParams);
extern void func_02024fd4(void *pContainer);

void func_ov022_0209c5ec(struct Actor *pActor)
{
    char szName[0x80];
    struct SlotInitParams params;
    struct Record *pRec;
    u32 nMask;
    int nBlock;
    struct SubBlock *pBlock;

    pRec = &data_0204c678[pActor->nId];
    OS_SPrintf(szName, data_ov022_020b2ce4, data_02042a70[pActor->nKind]);
    pActor->pContainer = func_02024ee8(szName, CONTAINER_HEAP);
    pBlock = pActor->aBlocks;
    for (nBlock = 0; nBlock < BLOCK_COUNT; nBlock++) {
        func_ov002_02051b20(pBlock);
        pBlock++;
    }
    func_ov022_020b0720(&pActor->blkActions, pActor, pActor->nKind,
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
    func_ov022_02092384(pActor->aSlots, pActor->nId, 0, &params);
    func_02024fd4(pActor->pContainer);
}
