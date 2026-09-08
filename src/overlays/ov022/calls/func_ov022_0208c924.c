#pragma thumb on

/* Ov022_CreateSlotKind05 -- create a slot of pool kind 5 from a template.
 *
 * The same constructor shape as the reaction slots use, for the kind the pool
 * tags 0xba: ask for the slot, set its part count, bind the sequence it plays, then
 * write the live fields straight from the template.
 *
 * The spread value is carried across all three words and kept again in the flag
 * word, the power, the reach and the pending flag come from the template, and
 * the level is the whole part of the template's second word.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_KIND 5
#define SLOT_TAG 0xba
#define SLOT_SIZE 0x140
#define SEQ_TRACKS 5

struct SlotTemplate {
    int nWord0;                  /* 0x00 */
    int nWord1;                  /* 0x04 */
    int nWord2;                  /* 0x08 */
    int nWord3;                  /* 0x0c */
    int nWord4;                  /* 0x10 */
    int pad14;
    int nWord6;                  /* 0x18 */
    int nWord7;                  /* 0x1c */
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000;
    u8 nParts;                   /* 0x001, how many parts the slot owns */
    u8 pad002[6];
    u16 nSlotFlags;              /* 0x008 */
    u8 pad00a[0xae];
    int aEntryFlags[3];          /* 0x0b8 */
    u8 pad0c4[0x54];
    u8 nState;                   /* 0x118 */
    u8 pad119[7];
    int nPower;                  /* 0x120 */
    int nRadius;                 /* 0x124 */
    int bPowerPending;           /* 0x128 */
    u8 pad12c[4];
    int nPowerInit;              /* 0x130 */
    int nEntryFlags;             /* 0x134 */
    int nRepeat;                 /* 0x138 */
    u8 nLevel;                   /* 0x13c */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[4];
};

extern struct ActorSlot *func_ov022_0208b71c(struct ReactionCtx *pCtx, int nKind,
                                             int nTag, int nSubKind, int nSize);
extern void func_0202a634(u16 *pFlags, void *pSeq, int nMode, int nTracks);

void func_ov022_0208c924(struct ReactionCtx *pCtx, void *pSeq, int nSubKind,
                         const struct SlotTemplate *pTpl)
{
    struct ActorSlot *pSlot;

    pSlot = func_ov022_0208b71c(pCtx, SLOT_KIND, SLOT_TAG, nSubKind, SLOT_SIZE);
    pSlot->nParts = 1;
    func_0202a634(&pSlot->nSlotFlags, pSeq, 1, SEQ_TRACKS);
    pSlot->aEntryFlags[2] = pTpl->nWord6;
    pSlot->aEntryFlags[1] = pSlot->aEntryFlags[2];
    pSlot->aEntryFlags[0] = pSlot->aEntryFlags[1];
    pSlot->nState = 0;
    pSlot->nPower = pTpl->nWord2;
    pSlot->nRadius = pTpl->nWord3;
    pSlot->bPowerPending = pTpl->nWord4;
    pSlot->nPowerInit = pTpl->nWord0;
    pSlot->nLevel = (u8)(pTpl->nWord1 >> 12);
    pSlot->nRepeat = pTpl->nWord7;
    pSlot->nEntryFlags = pTpl->nWord6;
}
