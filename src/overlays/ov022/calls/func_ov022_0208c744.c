/* Ov022_StepFlightPart -- the step a slot part runs while it is in flight.
 *
 * Nothing happens at all unless the slot is marked open. When it is, the part's
 * timer takes the frame and the part moves by its own velocity.
 *
 * Before it moves, a part that has waited long enough and still has turns left
 * may be re-aimed: the direction to the actor's mark is normalised, scaled by
 * the owner's rate -- half as much again in one of the two modes -- and becomes
 * the new velocity, with the vertical halved. That costs a turn, shortens the
 * owner's window by the time already spent, resets the timer and puts the part
 * back into the waiting state.
 *
 * After moving, a part still in flight ends its run when it has gone too far,
 * when the window has closed, or when the last turn is spent and the timer is
 * past the mark.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_OPEN 0xffff

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022AnimBlock */
struct AnimBlock {
    u16 nFlags;                  /* 0x00 */
    u8 pad02[0xa2];
    struct VecFx32 vecAt;        /* 0xa4 */
    int aEntryFlags[3];          /* 0xb0 */
};

/* Ov022SlotTail */
struct SlotTail {
    u8 nState;                   /* 0x00 */
    u8 pad01;
    short nTag;                  /* 0x02 */
    u8 pad04[8];
    int nRate;                   /* 0x0c */
    u8 pad10[4];
    int nReach;                  /* 0x14 */
    int nWindow;                 /* 0x18 */
    u8 pad1c[0xc];
    int nMark;                   /* 0x28 */
};

/* Ov022SlotPart */
struct SlotPart {
    int nTimer;                  /* 0x000 */
    struct VecFx32 vecPos;       /* 0x004 */
    struct VecFx32 vecVel;       /* 0x010 */
    struct AnimBlock anim;       /* 0x01c */
    u8 pad0d8[0x70];
    struct SlotTail *pOwner;     /* 0x148 */
    u8 nState;                   /* 0x14c */
    u8 pad14d[3];
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000[0x114];
    u16 nOpen;                   /* 0x114 */
    u8 pad116[0x62];
    int nMarkNext;               /* 0x178 */
};

struct Actor;

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                   /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[11];/* 0x18 */
    u8 pad44[0x14];
    struct Actor *pActor;        /* 0x58 */
};

extern int func_ov022_020ad114(struct Actor *pActor);
extern struct VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);
extern void VEC_Subtract(struct VecFx32 *pA, struct VecFx32 *pB,
                         struct VecFx32 *pOut);
extern void VEC_Add(struct VecFx32 *pA, struct VecFx32 *pB,
                    struct VecFx32 *pOut);
extern int func_01ff8d18(struct VecFx32 *pOut, struct VecFx32 *pIn);
extern int func_02023c40(void);
extern void func_01ffa724(int nScale, struct VecFx32 *pIn, struct VecFx32 *pOut);
extern int func_01ff8e94(struct VecFx32 *pA, struct VecFx32 *pB);
extern void func_ov022_0208b400(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                                struct VecFx32 *pAt, struct VecFx32 *pDir);
extern int func_ov022_0208acc4(int nKind, int nMode);
extern void func_ov022_0208a50c(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                                int nReaction);
extern void func_ov022_0208a6b0(struct ReactionCtx *pCtx);
extern int func_0202a818(u16 *pFlags, int nDelta);

int func_ov022_0208c744(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecDir;
    struct VecFx32 vecStep;
    struct Actor *pActor;
    struct SlotTail *pOwner;
    struct ActorSlot *pSlot;
    int nScale;
    int nDist;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    pActor = pCtx->pActor;
    pOwner = pPart->pOwner;
    if (pSlot->nOpen == SLOT_OPEN) {
        pPart->nTimer = pPart->nTimer + nDelta;
        vecAt = pPart->anim.vecAt;
        vecStep = pPart->vecVel;
        if (func_ov022_020ad114(pActor) != 0
            && pPart->nTimer >= pOwner->nMark
            && pOwner->nTag > 0) {
            VEC_Subtract(func_ov022_020ad0c0(pActor), &vecAt, &vecDir);
            func_01ff8d18(&vecDir, &vecDir);
            if (func_02023c40() == 1) {
                nScale = pOwner->nRate * 3 / 2;
            } else {
                nScale = pOwner->nRate;
            }
            func_01ffa724(nScale, &vecDir, &pPart->vecVel);
            pPart->vecVel.y = pPart->vecVel.y / 2;
            pOwner->nTag = pOwner->nTag - 1;
            pOwner->nWindow = pOwner->nWindow - pPart->nTimer;
            pPart->nTimer = 0;
            pPart->nState = 1;
            pOwner->nMark = pSlot->nMarkNext;
            func_ov022_0208a6b0(pCtx);
        }
        VEC_Add(&vecAt, &vecStep, &vecAt);
        pPart->anim.vecAt = vecAt;
        func_ov022_0208b400(pCtx, pPart, &vecAt, &pPart->vecVel);
        if (pPart->nState == 2) {
            nDist = func_01ff8e94(&pPart->vecPos, &vecAt);
            if (nDist > pOwner->nReach
                || pPart->nTimer >= pOwner->nWindow
                || (pPart->nTimer >= pOwner->nMark && pOwner->nTag == 0)) {
                func_ov022_0208a50c(pCtx, pPart,
                                    func_ov022_0208acc4(pOwner->nState, 2));
            }
        }
    }
    func_0202a818(&pPart->anim.nFlags, nDelta);
    return 0;
}
