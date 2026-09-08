#pragma thumb on

/* Ov022_CreateSlotKind03 -- create a slot of pool kind 3 from a template.
 *
 * The same shape as the kind 0 constructor and the same tail, filled through a
 * pointer to it: clear the trailing word, set the part count to one, hand the
 * sequence to the shared binder with two of the template's words, then write
 * the tail.
 *
 * This kind starts in state 3 rather than 0, scales its spawn value by a
 * different factor, and carries two extra fields past the tail: a level byte and
 * one more template word.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_KIND 3
#define SLOT_TAG 0xb8
#define SLOT_SIZE 0x17c
#define START_STATE 3
#define SPAWN_SCALE 0x4cd
#define SPAWN_BIAS 0x266

struct SlotTemplate {
    int nWord0;                  /* 0x00 */
    int nWord1;                  /* 0x04 */
    int nWord2;                  /* 0x08 */
    int nWord3;                  /* 0x0c */
    int nWord4;                  /* 0x10 */
    int nWord5;                  /* 0x14 */
    int nWord6;                  /* 0x18 */
    int nWord7;                  /* 0x1c */
};

/* the part of the slot from 0x118 on, shared with pool kind 0 */
struct SlotTail {
    u8 nState;                   /* 0x00 */
    u8 pad01[3];
    int nSpawn;                  /* 0x04 */
    int nField08;                /* 0x08 */
    int nField0c;                /* 0x0c */
    u16 nField10;                /* 0x10 */
    u8 pad12[2];
    int nField14;                /* 0x14 */
    u8 pad18[4];
    int nField1c;                /* 0x1c */
    int nField20;                /* 0x20 */
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
    u8 nParts;                   /* 0x001, how many parts the slot owns */
    u8 pad002[0x116];
    struct SlotTail tail;        /* 0x118 */
    u8 pad164[0xc];
    int nField170;               /* 0x170 */
    u8 nLevel174;                /* 0x174 */
    u8 pad175[3];
    int nField178;               /* 0x178 */
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

void func_ov022_0208c37c(struct ReactionCtx *pCtx, void *pSeq, int nSubKind,
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
    pTail->nField0c = 0x600;
    pTail->nField10 = 0;
    pTail->nField1c = 0;
    pTail->nField20 = pTpl->nWord7;
    pTail->nField48 = 1;
    pTail->nField14 = 0x12000;
    pTail->nField24 = pTpl->nWord3;
    pTail->nField30 = 8;
    pTail->nField34 = 3;
    pTail->nField2c = pTpl->nWord0;
    pTail->nLevel = (u8)(pTpl->nWord1 >> 12);
    pTail->nField38 = 0x100;
    pTail->nField3c = 0;
    pTail->nField40 = 0x100;
    pSlot->nLevel174 = (u8)(pTpl->nWord4 >> 12);
    pSlot->nField178 = pTpl->nWord2;
}
