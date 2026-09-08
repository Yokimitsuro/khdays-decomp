/* ov022: apply an end-of-run message on the side that receives it.
 *
 * This is the other half of Ov022_EndPartRun. The message names the actor in
 * two bits, so the first job is to resolve it and reach its reaction context;
 * a message for an actor that is not around any more is simply dropped.
 *
 * The class picks what to do with the rest. Four of the six classes only raise
 * a flag or record a number, and each of those first asks the session the same
 * question the poster asks and requires the opposite answer, so they never take
 * effect twice on the side that sent the message. The two classes that touch a
 * slot ask nothing and run either way: one hands a part's landing to the hit
 * handler, the other ends a slot's whole run -- clearing its timer, replaying
 * its aim, re-arming its three entry flags from the slot's repeat word and
 * leaving it in the finished state.
 *
 * Both of those check the same thing first: the part or slot must still be in
 * one of the two live states. The ROM tests that as one unsigned compare over
 * the biased byte rather than as two equality tests, so the check is written
 * the way it is computed -- adding the bias, keeping it in eight bits, and
 * comparing the width of the range.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define CTX_IN_ACTOR 0x2288
#define FLAG_CLASS0 0x4
#define FLAG_CLASS1 0x20
#define FLAG_CLASS5 0x200
#define GUARD_KIND 7
#define SLOT_DONE 3
#define ANIM_MODE 2

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022EndMessage -- the four bytes Ov022_EndPartRun posts */
struct EndMessage {
    u16 nKind : 3;               /* bits 0..2 */
    u16 nOwner : 2;              /* bits 3..4 */
    u16 nSlot : 5;               /* bits 5..9 */
    u16 nClass : 3;              /* bits 10..12 */
    u16 nSpare : 3;
    u8 nIndex;                   /* 0x02 */
    u8 nReaction;                /* 0x03 */
};

/* Ov022AnimBlock -- the same block sits in a slot and in each of its parts */
struct AnimBlock {
    u8 pad00[0xa4];
    struct VecFx32 vecAt;        /* 0x00a4 */
    int aEntryFlags[3];          /* 0x00b0 */
};

/* Ov022SlotPart */
struct SlotPart {
    u8 pad000[0x1c];
    struct AnimBlock anim;       /* 0x001c */
    u8 pad0d8[0x74];
    u8 nState;                   /* 0x014c */
    u8 pad14d[3];
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000[8];
    struct AnimBlock anim;       /* 0x0008 */
    u8 pad0c4[0x54];
    u8 nState;                   /* 0x0118 */
    u8 pad119[3];
    int nTimer;                  /* 0x011c */
    u8 pad120[0x18];
    int nRepeat;                 /* 0x0138 */
    u8 pad13c[0x2c];
    struct SlotPart *pParts;     /* 0x0168 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u16 wFlags;                  /* 0x00 */
    u8 nGuard;                   /* 0x02 */
    u8 pad03[9];
    int nSlot;                   /* 0x0c */
    u8 pad10[4];
    int nKind;                   /* 0x14 */
    struct ActorSlot *aSlots[11];/* 0x18 */
    u8 pad44[0x10];
    u8 *pTrack;                  /* 0x54 */
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[CTX_IN_ACTOR];
    struct ReactionCtx ctx;      /* 0x2288 */
};

extern struct Actor *func_01fffde0(int nOwner);
extern int func_02030694(void);
extern void func_ov022_0208b6c0(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                                struct VecFx32 *pAt, int nReaction);
extern void func_ov022_0208acdc(struct ReactionCtx *pCtx, struct VecFx32 *pAim,
                                int nReaction);
extern void func_ov022_0208a8bc(struct ReactionCtx *pCtx, u8 *pTrack,
                                struct AnimBlock *pAnim, int nMode);
extern void func_ov022_0208a6b0(struct ReactionCtx *pCtx);
extern void func_ov022_0208a6d0(struct ReactionCtx *pCtx);

void func_ov022_0208a2b4(struct EndMessage *pMsg)
{
    struct ReactionCtx *pCtx;
    struct ActorSlot *pSlot;
    struct SlotPart *pPart;
    struct Actor *pActor;
    int nSeed;

    pActor = func_01fffde0(pMsg->nOwner);
    if (pActor == 0) {
        return;
    }
    pCtx = &pActor->ctx;
    switch (pMsg->nClass) {
    case 0:
        if (func_02030694() != 0) {
            return;
        }
        pCtx->wFlags = pCtx->wFlags | FLAG_CLASS0;
        pCtx->nSlot = pMsg->nSlot;
        break;
    case 5:
        if (func_02030694() != 0) {
            return;
        }
        pCtx->wFlags = pCtx->wFlags | FLAG_CLASS5;
        break;
    case 1:
        if (pCtx->nGuard != GUARD_KIND) {
            return;
        }
        if (func_02030694() != 0) {
            return;
        }
        pCtx->wFlags = pCtx->wFlags | FLAG_CLASS1;
        break;
    case 2:
        pSlot = pCtx->aSlots[pMsg->nSlot];
        pPart = &pSlot->pParts[pMsg->nIndex];
        if ((u8)(pPart->nState + 0xff) > 1) {
            return;
        }
        func_ov022_0208b6c0(pCtx, pPart, &pPart->anim.vecAt, pMsg->nReaction);
        break;
    case 4:
        pSlot = pCtx->aSlots[pMsg->nSlot];
        if ((u8)(pSlot->nState + 0xff) > 1) {
            return;
        }
        pSlot->nTimer = 0;
        func_ov022_0208acdc(pCtx, &pSlot->anim.vecAt, pMsg->nReaction);
        func_ov022_0208a8bc(pCtx, pCtx->pTrack + 4, &pSlot->anim, ANIM_MODE);
        nSeed = pSlot->nRepeat;
        pSlot->anim.aEntryFlags[2] = nSeed;
        pSlot->anim.aEntryFlags[1] = nSeed;
        pSlot->anim.aEntryFlags[0] = nSeed;
        func_ov022_0208a6b0(pCtx);
        pSlot->nState = SLOT_DONE;
        break;
    case 3:
        if (func_02030694() != 0) {
            return;
        }
        pCtx->nKind = pMsg->nSlot;
        func_ov022_0208a6d0(pCtx);
        break;
    }
}
