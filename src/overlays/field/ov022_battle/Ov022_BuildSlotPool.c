/* ov022: build every slot the actor owns, one per kind.
 *
 * Loads the shared template archive once, takes a local copy of the model-name
 * table, then walks the fifteen slot kinds. For each kind the actor is asked
 * how many parts it has of it; nothing is built when the answer is zero, and
 * five is the most any kind can hold. The name table gives the model the kind
 * draws with, the count picks one of that kind's five templates out of the
 * archive, and the kind's own constructor is called through the table. Each
 * built slot has its counter cleared and its mark set to none, and the pool
 * records the kind in its mask. The archive goes back once every kind is done.
 */

#include "nitro/types.h"

#define SLOT_KINDS 15
#define MAX_PARTS 5
#define TEMPLATE_HEAP 6

struct SlotTemplate {
    u8 abData[0x24];
};

struct Slot {
    u8 pad0000[4];
    int nCount;                    /* 0x0004 */
    u8 pad0008[0x108];
    signed char nMark;             /* 0x0110 */
};

struct SlotPool {
    u16 nFlags;                    /* 0x0000 */
    u8 pad0002[6];
    u32 nKindMask;                 /* 0x0008 */
    u8 pad000c[0xc];
    struct Slot *apSlots[16];      /* 0x0018 */
    void *pActor;                  /* 0x0058 */
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                        /* 0x0009 */
};

/* One model name per kind, three kinds to a name. */
struct NameTable {
    char *ap[18];
};

typedef void (*SlotCreateFn)(struct SlotPool *pPool, char *pszModel,
                             int nParts, struct SlotTemplate *pTpl);

extern char gOv022BaChMpPath[];             /* "ba/ch/mp.z" */
extern char gOv022BaMaPackPathFmt[];             /* "ba/ma/%s.p.z" */
extern struct NameTable data_ov022_020b23dc;
extern SlotCreateFn data_ov022_020b29e4[];

extern struct SlotTemplate *Archive_LoadFile(char *pszName, int nHeap);
extern int Slot_EvalPackedParam(int nId, int nKind);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);

void Ov022_BuildSlotPool(struct SlotPool *pPool, struct Actor *pActor)
{
    char szModel[0x80];
    struct NameTable names;
    struct SlotTemplate *pTemplates;
    int nKind;
    int nParts;

    pPool->pActor = pActor;
    pPool->nFlags |= 1;
    pTemplates = Archive_LoadFile(gOv022BaChMpPath, TEMPLATE_HEAP);
    names = data_ov022_020b23dc;
    for (nKind = 0; nKind < SLOT_KINDS; nKind++) {
        nParts = Slot_EvalPackedParam(pActor->nId, nKind + 1);
        if (nParts > 0) {
            if (nParts > MAX_PARTS) {
                nParts = MAX_PARTS;
            }
            OS_SPrintf(szModel, gOv022BaMaPackPathFmt, names.ap[nKind]);
            data_ov022_020b29e4[nKind](pPool, szModel, nParts,
                                       &pTemplates[nParts - 1
                                                   + nKind * MAX_PARTS]);
            pPool->apSlots[nKind]->nCount = 0;
            pPool->apSlots[nKind]->nMark = -1;
            pPool->nKindMask |= 1 << nKind;
        }
    }
    NNSi_FndFreeFromDefaultHeap(pTemplates);
}
