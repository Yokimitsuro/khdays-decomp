/* Ov022_EnterBlockReaction -- hand a reaction slot over to the block state.
 *
 * Clears the actor's pending bit, stamps the actor's slot index and a fresh
 * sequence number onto the slot, then aims the slot at the actor's position
 * raised by a fixed height. The aim point goes through the notifier before it is
 * stored, so whoever is watching sees the same point the slot will use.
 *
 * Finally the slot is put into the blocking state: the block flag goes up, the
 * timer is cleared, the step is set to one and the hold bit is dropped.
 *
 * The angle carried over from the node makes a full round trip through the bias
 * the field is stored with, which leaves the halfword unchanged; the pair is
 * kept because the compiler emits both halves.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad000[0x80];
    u16 nAngle;                  /* 0x0080 */
};

/* Ov022Actor */
struct Actor {
    u8 pad000[0x20];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad024[0x42];
    short nSlotIndex;            /* 0x0066 */
    u8 pad068[0x424];
    struct VecFx32 vecPos;       /* 0x048c */
    u8 pad498[0x1fc];
    u8 nActorFlags694;           /* 0x0694 */
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 nKind;                    /* 0x000 */
    u8 pad001;
    u8 nSeq;                     /* 0x002 */
    u8 pad003[5];
    u16 nFlags;                  /* 0x008 */
    u8 pad00a[0x7a];
    u16 nAngle;                  /* 0x084 */
    u8 pad086[0x26];
    struct VecFx32 vecAim;       /* 0x0ac */
    u8 pad0b8[0x58];
    u8 nSlotIndex;               /* 0x110 */
    u8 pad111[7];
    u8 nState;                   /* 0x118 */
    u8 pad119[3];
    int nTimer;                  /* 0x11c */
    u8 pad120[8];
    int nStep;                   /* 0x128 */
    u8 pad12c[8];
    u8 nEntryFlagsLow;           /* 0x134, low byte of the entry flags word */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                   /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[11];/* 0x18 */
    struct ActorSlot *pSlot;     /* 0x44 */
    u8 pad48[0xc];
    int nTrack;                  /* 0x54 */
    struct Actor *pActor;        /* 0x58 */
};

#define BLOCK_RISE 0x119a
#define ANGLE_UNBIAS(a) ((u16)((a) - 0x8000))
#define ANGLE_BIAS(a) ((a) + 0x8000)

extern void func_ov022_0208a8bc(struct ReactionCtx *pCtx, int nTrack, u16 *pFlags,
                                int nBinding);
extern int func_ov022_0208acc4(int nKind, int nMode);
extern void func_ov022_0208acdc(struct ReactionCtx *pCtx, struct VecFx32 *pAim,
                                int nReaction);

void func_ov022_0208f888(struct ReactionCtx *pCtx)
{
    struct VecFx32 vecAim;
    struct Actor *pActor;
    struct ActorSlot *pSlot;
    u16 nAngle;
    int nReaction;

    pActor = pCtx->pActor;
    pSlot = pCtx->aSlots[pCtx->nSlot];
    nAngle = pActor->pNode->nAngle;
    pActor->nActorFlags694 &= ~0x40;
    pSlot->nSlotIndex = (u8)pActor->nSlotIndex;
    pSlot->nSeq = pSlot->nSeq + 1;
    vecAim = pActor->vecPos;
    vecAim.y += BLOCK_RISE;
    func_ov022_0208a8bc(pCtx, pCtx->nTrack + 4, &pSlot->nFlags, 0);
    nReaction = func_ov022_0208acc4(pSlot->nKind, 0);
    func_ov022_0208acdc(pCtx, &vecAim, nReaction);
    pSlot->vecAim = vecAim;
    pSlot->nAngle = ANGLE_BIAS(ANGLE_UNBIAS(nAngle));
    pSlot->nFlags |= 0x20;
    pSlot->nTimer = 0;
    pSlot->nStep = 1;
    pSlot->nState = 2;
    pSlot->nEntryFlagsLow &= ~8;
}
