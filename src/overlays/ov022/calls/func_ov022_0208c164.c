/* Ov022_StepHomingPart -- the step a homing slot part runs while it falls.
 *
 * Like the plain flight step, nothing happens unless the slot is open, and the
 * part moves by its own velocity each frame with gravity pulling the vertical
 * down -- by a different amount in each of the two modes.
 *
 * What it adds is steering. While the owner still has turns, the actor's mark
 * is valid and the part is already on its way down, the horizontal heading is
 * blended toward the mark: both the heading and the direction to the mark are
 * flattened and normalised, the mark's share is the owner's turn count out of
 * one, and the result is rescaled by the owner's rate -- half as much again in
 * one of the two modes. Only the horizontal is replaced; the fall is untouched.
 *
 * A part still in flight ends its run once the owner's window has closed.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_OPEN 0xffff
#define ONE 0x1000

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
    u8 pad10[8];
    int nWindow;                 /* 0x18 */
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
extern void VEC_MultAdd(int nScale, struct VecFx32 *pA, struct VecFx32 *pB,
                        struct VecFx32 *pOut);
extern int func_01ff8d18(struct VecFx32 *pOut, struct VecFx32 *pIn);
extern int func_02023c40(void);
extern void func_01ffa724(int nScale, struct VecFx32 *pIn, struct VecFx32 *pOut);
extern void func_ov022_0208b400(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                                struct VecFx32 *pAt, struct VecFx32 *pDir);
extern int func_ov022_0208acc4(int nKind, int nMode);
extern void func_ov022_0208a50c(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                                int nReaction);
extern int func_0202a818(u16 *pFlags, int nDelta);

int func_ov022_0208c164(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecFlat;
    struct VecFx32 vecDir;
    struct VecFx32 vecStep;
    struct VecFx32 vecHeading;
    struct VecFx32 vecMark;
    struct Actor *pActor;
    struct SlotTail *pOwner;
    struct ActorSlot *pSlot;
    int nFall;
    int nScale;
    int nFallStep;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    pActor = pCtx->pActor;
    pOwner = pPart->pOwner;
    if (pSlot->nOpen == SLOT_OPEN) {
        pPart->nTimer = pPart->nTimer + nDelta;
        vecAt = pPart->anim.vecAt;
        nFall = pPart->vecVel.y;
        if (pOwner->nTag != 0 && func_ov022_020ad114(pActor) != 0
            && pPart->vecVel.y < 0) {
            vecFlat = vecAt;
            vecMark = *func_ov022_020ad0c0(pActor);
            vecHeading = pPart->vecVel;
            vecHeading.y = 0;
            vecFlat.y = 0;
            vecMark.y = 0;
            VEC_Subtract(&vecMark, &vecFlat, &vecDir);
            func_01ff8d18(&vecDir, &vecDir);
            func_01ff8d18(&vecHeading, &vecHeading);
            func_01ffa724(pOwner->nTag, &vecDir, &vecDir);
            VEC_MultAdd(ONE - pOwner->nTag, &vecHeading, &vecDir, &vecHeading);
            func_01ff8d18(&vecHeading, &vecHeading);
            if (func_02023c40() == 1) {
                nScale = pOwner->nRate * 3 / 2;
            } else {
                nScale = pOwner->nRate;
            }
            func_01ffa724(nScale, &vecHeading, &vecHeading);
            pPart->vecVel.x = vecHeading.x;
            pPart->vecVel.z = vecHeading.z;
        }
        vecStep = pPart->vecVel;
        vecStep.y = nFall;
        pPart->vecVel.y = nFall;
        VEC_Add(&vecAt, &vecStep, &vecAt);
        pPart->anim.vecAt = vecAt;
        if (func_02023c40() == 1) {
            nFallStep = 0x48;
        } else {
            nFallStep = 0x30;
        }
        pPart->vecVel.y = pPart->vecVel.y - nFallStep;
        func_ov022_0208b400(pCtx, pPart, &vecAt, &pPart->vecVel);
        if (pPart->nState == 2 && pPart->nTimer >= pOwner->nWindow) {
            func_ov022_0208a50c(pCtx, pPart,
                                func_ov022_0208acc4(pOwner->nState, 2));
        }
    }
    func_0202a818(&pPart->anim.nFlags, nDelta);
    return 0;
}
