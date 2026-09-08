#pragma thumb on

/* Ov022_CreateSlotKind07 -- create a slot of pool kind 7 from a template.
 *
 * Kind 7 is the one that owns six parts. The slot itself is built and filled
 * like the other kinds, its sequence registered on its own animation block,
 * and then the parts are allocated in one run and each given the same
 * sequence, the template's entry value in all three of its slots, an idle
 * state and the slot's tail as its owner. What is left is the arming pair the
 * part driver reads: nothing armed yet, no timer, and the template's delay.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_KIND 7
#define SLOT_TAG 0xbc
#define SLOT_SIZE 0x19c
#define SLOT_PARTS 6
#define SLOT_SEQ 5
#define START_STATE 7
#define PART_STRIDE 0x150

struct SlotTemplate {
    int nWord0;                  /* 0x00 */
    int nWord1;                  /* 0x04 */
    int nWord2;                  /* 0x08 */
    int nWord3;                  /* 0x0c */
    int nWord4;                  /* 0x10 */
    int nWord5;                  /* 0x14 */
};

/* Ov022AnimBlock */
struct AnimBlock {
    u16 nFlags;                  /* 0x00 */
    u8 pad02[0xa2];
    int vecAt[3];                /* 0xa4 */
    int aEntryFlags[3];          /* 0xb0 */
};

/* Ov022SlotPart */
struct SlotPart {
    u8 pad000[0x1c];
    struct AnimBlock anim;       /* 0x01c */
    u8 pad0d8[0x70];
    void *pOwner;                /* 0x148 */
    u8 nState;                   /* 0x14c */
    u8 pad14d[3];
};

/* the part of the slot from 0x118 on */
struct SlotTail {
    u8 nState;                   /* 0x00 */
    u8 pad01[3];
    int nSpawn;                  /* 0x04 */
    int nField08;                /* 0x08 */
    u8 pad0c[8];
    int nField14;                /* 0x14 */
    int nField18;                /* 0x18 */
    u8 pad1c[8];
    int nField24;                /* 0x24 */
    u8 pad28[4];
    int nField2c;                /* 0x2c */
    int nField30;                /* 0x30 */
    int nField34;                /* 0x34 */
    int nField38;                /* 0x38 */
    int nField3c;                /* 0x3c */
    int nField40;                /* 0x40 */
    u8 nLevel;                   /* 0x44 */
    u8 pad45[3];
    int nField48;                /* 0x48 */
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000;
    u8 nParts;                   /* 0x001 */
    u8 nSeq;                     /* 0x002 */
    u8 pad003[5];
    struct AnimBlock anim;       /* 0x008 */
    u8 pad0c4[0x54];
    struct SlotTail tail;        /* 0x118 */
    u8 pad164[0x4];
    struct SlotPart *pParts;     /* 0x168 */
    u8 pad16c[4];
    int bSeqPending;             /* 0x170 */
    u8 nTurns;                   /* 0x174 */
    u8 nArmed;                   /* 0x175 */
    u8 nArmMax;                  /* 0x176 */
    u8 pad177;
    int nMarkNext;               /* 0x178 */
    int nArmDelay;               /* 0x17c */
    int nField180;               /* 0x180 */
    int nField184;               /* 0x184 */
    int nField188;               /* 0x188 */
};

struct ReactionCtx {
    u8 pad00[4];
};

extern struct ActorSlot *func_ov022_0208b71c(struct ReactionCtx *pCtx, int nKind,
                                             int nTag, int nSubKind, int nSize);
extern void func_0202a634(int object, void *pSeq, int nMode, int nGroup);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);

void func_ov022_0208edb8(struct ReactionCtx *pCtx, void *pSeq, int nSubKind,
                         const struct SlotTemplate *pTpl)
{
    struct ActorSlot *pSlot;
    struct SlotTail *pTail;
    struct SlotPart *pPart;
    int nPart;
    int nOffset;

    pSlot = func_ov022_0208b71c(pCtx, SLOT_KIND, SLOT_TAG, nSubKind, SLOT_SIZE);
    pSlot->bSeqPending = 0;
    pSlot->nParts = SLOT_PARTS;
    pSlot->nSeq = SLOT_SEQ;
    pTail = &pSlot->tail;
    pTail->nState = START_STATE;
    pTail->nSpawn = 0x700;
    pTail->nField14 = 0xa000;
    pTail->nField08 = 0x25000;
    pTail->nField18 = 0xa000;
    pTail->nField24 = 0;
    pTail->nField2c = pTpl->nWord0;
    pTail->nLevel = (u8)(pTpl->nWord1 >> 12);
    pTail->nField30 = 8;
    pTail->nField34 = 0xb;
    pTail->nField48 = 1;
    pTail->nField38 = 0;
    pTail->nField3c = 0x100;
    pTail->nField40 = 0;
    func_0202a634((int)&pSlot->anim, pSeq, 1, SLOT_SEQ);
    pSlot->bSeqPending = 0;
    pSlot->pParts = (struct SlotPart *)NNSi_FndAllocFromDefaultExpHeap(
        pSlot->nParts * PART_STRIDE);
    nPart = 0;
    if (nPart < pSlot->nParts) {
        nOffset = 0;
        do {
            pPart = (struct SlotPart *)((u8 *)pSlot->pParts + nOffset);
            func_0202a634((int)&pPart->anim, pSeq, 1, SLOT_SEQ);
            pPart->anim.aEntryFlags[2] = pTpl->nWord5;
            pPart->anim.aEntryFlags[1] = pPart->anim.aEntryFlags[2];
            pPart->anim.aEntryFlags[0] = pPart->anim.aEntryFlags[1];
            pPart->nState = 0;
            pPart->pOwner = &pSlot->tail;
            nOffset += PART_STRIDE;
            nPart++;
        } while (nPart < pSlot->nParts);
    }
    pSlot->nTurns = 0;
    pSlot->nMarkNext = 0;
    pSlot->nField180 = 0x2000;
    pSlot->nField184 = 0x2000;
    pSlot->nArmDelay = pTpl->nWord2;
    pSlot->nArmMax = (u8)(pTpl->nWord3 >> 12);
    pSlot->nField188 = pTpl->nWord4;
}
