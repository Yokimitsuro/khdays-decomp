#pragma thumb on

/* Ov022_CreateSlotKind0c -- create a slot of pool kind 0xc from a template.
 *
 * The same shape as the reaction slot's constructor, for the smaller kind: ask
 * the channel pool for the slot, mark it live, bind the sequence it plays, then
 * fill in the live fields directly instead of copying a template block.
 *
 * The spread value is written once and carried across the other two words, the
 * power and its starting value come from the template, the reach, the interval
 * and the state start at zero, and the low bit of the template's flag word
 * becomes the slot's own flag.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_KIND 0xc
#define SLOT_TAG 0xc1
#define SLOT_SIZE 0x138
#define SEQ_TRACKS 5

struct SlotTemplate {
    int nPower;                  /* 0x00 */
    int pad04;
    int nPowerInit;              /* 0x08 */
    int pad0c[2];
    int nSpread;                 /* 0x14 */
    int pad18[2];
    int nFlags;                  /* 0x20 */
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000;
    u8 bLive;                    /* 0x001 */
    u8 pad002[6];
    u16 nSlotFlags;              /* 0x008 */
    u8 pad00a[0xae];
    int aEntryFlags[3];          /* 0x0b8 */
    u8 pad0c4[0x54];
    u8 nState;                   /* 0x118 */
    u8 pad119[7];
    int nPower;                  /* 0x120 */
    int nRadius;                 /* 0x124 */
    u8 pad128[4];
    int nInterval;               /* 0x12c */
    int nPowerInit;              /* 0x130 */
    u8 bSpreadFromTemplate : 1;  /* 0x134 bit 0 */
    u8 nRest134 : 7;
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[4];
};

extern struct ActorSlot *func_ov022_0208b71c(struct ReactionCtx *pCtx, int nKind,
                                             int nTag, int nSubKind, int nSize);
extern void func_0202a634(u16 *pFlags, void *pSeq, int nMode, int nTracks);

void func_ov022_0208f69c(struct ReactionCtx *pCtx, void *pSeq, int nSubKind,
                         const struct SlotTemplate *pTpl)
{
    struct ActorSlot *pSlot;

    pSlot = func_ov022_0208b71c(pCtx, SLOT_KIND, SLOT_TAG, nSubKind, SLOT_SIZE);
    pSlot->bLive = 1;
    func_0202a634(&pSlot->nSlotFlags, pSeq, 1, SEQ_TRACKS);
    pSlot->aEntryFlags[2] = pTpl->nSpread;
    pSlot->aEntryFlags[1] = pSlot->aEntryFlags[2];
    pSlot->aEntryFlags[0] = pSlot->aEntryFlags[1];
    pSlot->nPower = pTpl->nPower;
    pSlot->nRadius = 0;
    pSlot->nState = 0;
    pSlot->nInterval = 0;
    pSlot->nPowerInit = pTpl->nPowerInit;
    pSlot->bSpreadFromTemplate = pTpl->nFlags & 1;
}
