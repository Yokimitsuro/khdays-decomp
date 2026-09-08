#pragma thumb on

/* Ov022_CreateSlotKind0a -- create a slot of pool kind 0xa from a template.
 *
 * The sibling of the kind 9 constructor: same shape, same tail, and the same
 * habit of working a field out from the sub-kind -- here a range that grows by
 * thirty a step from a hundred and fifty, all in twelfths.
 *
 * The template's ninth word is kept in the tail and then read straight back:
 * its second bit is what decides whether the halfword near the top stays at
 * zero.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_KIND 0xa
#define SLOT_TAG 0xbf
#define SLOT_SIZE 0x174
#define START_STATE 0xa
#define SPAWN_SCALE 0x800
#define SPAWN_BIAS 0x666

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

/* the part of the slot from 0x118 on, shared with the other pool kinds */
struct SlotTail {
    u8 nState;                   /* 0x00 */
    u8 pad01;
    u16 nField02;                /* 0x02 */
    int nSpawn;                  /* 0x04 */
    int nField08;                /* 0x08 */
    int nField0c;                /* 0x0c */
    u16 nField10;                /* 0x10 */
    u8 pad12[2];
    int nField14;                /* 0x14 */
    int nField18;                /* 0x18 */
    int nField1c;                /* 0x1c */
    int nField20;                /* 0x20 */
    int nField24;                /* 0x24 */
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
    u8 nParts;                   /* 0x001, how many parts the slot owns */
    u8 pad002[0x116];
    struct SlotTail tail;        /* 0x118 */
    u8 pad168[8];
    int nField170;               /* 0x170 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[4];
};

extern struct ActorSlot *func_ov022_0208b71c(struct ReactionCtx *pCtx, int nKind,
                                             int nTag, int nSubKind, int nSize);
extern void func_ov022_0208b758(struct ActorSlot *pSlot, void *pSeq, int nFirst,
                                int nSecond);
extern int func_02005418(int nScale, int nValue);

void func_ov022_0208d6a8(struct ReactionCtx *pCtx, void *pSeq, int nSubKind,
                         const struct SlotTemplate *pTpl)
{
    struct ActorSlot *pSlot;
    struct SlotTail *pTail;

    pSlot = func_ov022_0208b71c(pCtx, SLOT_KIND, SLOT_TAG, nSubKind, SLOT_SIZE);
    pSlot->nField170 = 0;
    pSlot->nParts = 1;
    func_ov022_0208b758(pSlot, pSeq, pTpl->nWord5, pTpl->nWord6);
    pTail = &pSlot->tail;
    pTail->nState = START_STATE;
    pTail->nSpawn = func_02005418(SPAWN_SCALE, pTpl->nWord5) + SPAWN_BIAS;
    pTail->nField08 = 0x800;
    pTail->nField0c = 0x800;
    pTail->nField10 = 0x80;
    pTail->nField1c = 0;
    pTail->nField14 = 0x8000;
    pTail->nField24 = 0x1000;
    pTail->nField20 = pTpl->nWord7;
    pTail->nField18 = (0x1e * nSubKind + 0x96) << 12;
    pTail->nField28 = 0;
    pTail->nField2c = pTpl->nWord0;
    pTail->nLevel = (u8)(pTpl->nWord1 >> 12);
    pTail->nField30 = 8;
    pTail->nField34 = 2;
    pTail->nField48 = 1;
    pTail->nField38 = 0x10;
    pTail->nField3c = 0x2000;
    pTail->nField40 = 0x10;
    pTail->nField0c = pTpl->nWord2;
    pTail->nField4c = pTpl->nWord8;
    pTail->nField02 = 0;
    if ((pTail->nField4c & 2) != 0) {
        pTail->nField02 = SPAWN_BIAS / 2;
    }
}
