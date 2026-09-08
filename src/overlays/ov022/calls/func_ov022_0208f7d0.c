/* Ov022_CreateSlotKind0e -- create a slot of pool kind 0xe from a template.
 *
 * The last and largest of the slot constructors, one step up from kind 0xd:
 * ask the pool for the slot, set its part count, bind the sequence it plays,
 * then write the live fields straight from the template.
 *
 * The spread value is carried across all three words, the reach interval starts
 * at a fixed 0xa000, the low bit of the template's flag word becomes the slot's
 * third flag, the repeat maximum arrives as a fixed-point value that is shifted
 * down to whole units, and the three trailing words this kind adds follow.
 */

typedef unsigned char u8;
typedef unsigned short u16;

#define SLOT_KIND 0xe
#define SLOT_TAG 0xc3
#define SLOT_SIZE 0x154
#define SEQ_TRACKS 5
#define START_INTERVAL 0xa000

struct SlotTemplate {
    int nWord0;                  /* 0x00 */
    int nWord1;                  /* 0x04 */
    int nWord2;                  /* 0x08 */
    int nWord3;                  /* 0x0c */
    int nWord4;                  /* 0x10 */
    int nWord5;                  /* 0x14 */
    int nWord6;                  /* 0x18 */
    int pad1c;
    int nWord8;                  /* 0x20 */
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
    u8 pad119[0xb];
    int nRadius;                 /* 0x124 */
    u8 pad128[4];
    int nInterval;               /* 0x12c */
    u8 pad130[4];
    u8 nRest134 : 2;             /* 0x134 bits 0 and 1 */
    u8 bFlag2 : 1;               /* 0x134 bit 2 */
    u8 nRest134b : 5;
    u8 pad135[3];
    int nRepeat;                 /* 0x138 */
    int nRepeatMax;              /* 0x13c */
    int nField140;               /* 0x140 */
    int nPowerNext;              /* 0x144 */
    int nField148;               /* 0x148 */
    int nField14c;               /* 0x14c */
    int nField150;               /* 0x150 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[4];
};

extern struct ActorSlot *func_ov022_0208b71c(struct ReactionCtx *pCtx, int nKind,
                                             int nTag, int nSubKind, int nSize);
extern void func_0202a634(u16 *pFlags, void *pSeq, int nMode, int nTracks);

void func_ov022_0208f7d0(struct ReactionCtx *pCtx, void *pSeq, int nSubKind,
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
    pSlot->nInterval = START_INTERVAL;
    pSlot->bFlag2 = pTpl->nWord8 & 1;
    pSlot->nField140 = pTpl->nWord0;
    pSlot->nPowerNext = pTpl->nWord1;
    pSlot->nRadius = pTpl->nWord2;
    pSlot->nRepeatMax = pTpl->nWord3 >> 12;
    pSlot->nField148 = pTpl->nWord4;
    pSlot->nField14c = pTpl->nWord6;
    pSlot->nField150 = pTpl->nWord5;
}
