/* Ov022_CreateSlotKind08 -- create a slot of pool kind 8 from a template.
 *
 * Kind 8 owns a single part. Its spawn interval is not a constant like the other
 * kinds: it is the sub-kind's own step scaled by a fixed factor. The rest is
 * filled like its siblings, the sequence is registered on the slot's animation
 * block and then on the part, and the part takes the template's entry value in
 * all three of its slots, the slot's tail as its owner, an idle state and its
 * place in the run as its index.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_KIND 8
#define SLOT_TAG 0xbd
#define SLOT_SIZE 0x174
#define SLOT_PARTS 1
#define ANIM_SEQ 5
#define START_STATE 8
#define PART_STRIDE 0x150
#define SPAWN_STEP 0x700
#define SPAWN_SCALE 0x119a

struct SlotTemplate {
    int nWord0;                  /* 0x00 */
    int nWord1;                  /* 0x04 */
    int nWord2;                  /* 0x08 */
    int nWord3;                  /* 0x0c */
    int nWord4;                  /* 0x10 */
    int nWord5;                  /* 0x14 */
    int nWord6;                  /* 0x18 */
    int nWord7;                  /* 0x1c */
    int nWord8;                  /* 0x20 */
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
    u8 nGroup : 3;               /* 0x14d bits 0 to 2 */
    u8 nIndex : 5;               /* bits 3 to 7 */
    u8 nField14e;                /* 0x14e */
    u8 pad14f;
};

/* the part of the slot from 0x118 on */
struct SlotTail {
    u8 nState;                   /* 0x00 */
    u8 pad01[3];
    int nSpawn;                  /* 0x04 */
    int nField08;                /* 0x08 */
    u8 pad0c[4];
    u16 nField10;                /* 0x10 */
    u16 pad12;
    int nField14;                /* 0x14 */
    int nField18;                /* 0x18 */
    int nField1c;                /* 0x1c */
    u8 pad20[8];
    int nField28;                /* 0x28 */
    int nField2c;                /* 0x2c */
    int nField30;                /* 0x30 */
    int nField34;                /* 0x34 */
    int nField38;                /* 0x38 */
    int nField3c;                /* 0x3c */
    int nField40;                /* 0x40 */
    u8 nLevel;                   /* 0x44 */
    u8 pad45[3];
    int nField48;                /* 0x48 */
    int nField4c;                /* 0x4c */
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000;
    u8 nParts;                   /* 0x001 */
    u8 pad002[6];
    struct AnimBlock anim;       /* 0x008 */
    u8 pad0c4[0x54];
    struct SlotTail tail;        /* 0x118 */
    struct SlotPart *pParts;     /* 0x168 */
    u8 pad16c[4];
    int bSeqPending;             /* 0x170 */
};

struct ReactionCtx {
    u8 pad00[4];
};

extern struct ActorSlot *func_ov022_0208b71c(struct ReactionCtx *pCtx, int nKind,
                                             int nTag, int nSubKind, int nSize);
extern void func_0202a634(int object, void *pSeq, int nMode, int nGroup);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);

void func_ov022_0208f14c(struct ReactionCtx *pCtx, void *pSeq, int nSubKind,
                         const struct SlotTemplate *pTpl)
{
    struct SlotTail *pTail;
    struct ActorSlot *pSlot;
    int nPart;
    struct SlotPart *pPart;
    int nOffset;

    pSlot = func_ov022_0208b71c(pCtx, SLOT_KIND, SLOT_TAG, nSubKind, SLOT_SIZE);
    pSlot->bSeqPending = 0;
    pSlot->nParts = SLOT_PARTS;
    pTail = &pSlot->tail;
    pTail->nField4c = pTpl->nWord8;
    pTail->nState = START_STATE;
    pTail->nSpawn = (int)(((long long)(nSubKind * SPAWN_STEP) * SPAWN_SCALE
                           + 0x800) >> 12);
    pTail->nField14 = 0xa000;
    pTail->nField08 = 0x25000;
    pTail->nField18 = 0xa000;
    pTail->nField10 = 0;
    pTail->nField1c = 0;
    pTail->nField28 = pTpl->nWord2;
    pTail->nField1c = pTpl->nWord3;
    pTail->nField2c = pTpl->nWord0;
    pTail->nLevel = (u8)(pTpl->nWord1 >> 12);
    pTail->nField30 = 8;
    pTail->nField34 = 0xb;
    pTail->nField48 = 1;
    pTail->nField38 = 0;
    pTail->nField3c = 0x300;
    pTail->nField40 = 0;
    func_0202a634((int)&pSlot->anim, pSeq, 1, ANIM_SEQ);
    pSlot->bSeqPending = 0;
    pSlot->pParts = (struct SlotPart *)NNSi_FndAllocFromDefaultExpHeap(
        pSlot->nParts * PART_STRIDE);
    nPart = 0;
    if (nPart < pSlot->nParts) {
        nOffset = 0;
        do {
            pPart = (struct SlotPart *)((u8 *)pSlot->pParts + nOffset);
            func_0202a634((int)&pPart->anim, pSeq, 1, ANIM_SEQ);
            pPart->anim.aEntryFlags[2] = pTpl->nWord5;
            pPart->anim.aEntryFlags[1] = pPart->anim.aEntryFlags[2];
            pPart->anim.aEntryFlags[0] = pPart->anim.aEntryFlags[1];
            pPart->pOwner = &pSlot->tail;
            pPart->nField14e = 0;
            pPart->nState = 0;
            pPart->nIndex = nPart;
            nOffset += PART_STRIDE;
            nPart++;
        } while (nPart < pSlot->nParts);
    }
}
