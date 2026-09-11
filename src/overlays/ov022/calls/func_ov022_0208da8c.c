/* Ov022_StepFlyingPart -- one frame of a part in flight that chases a target.
 *
 * The part's timer takes the frame delta; past a threshold it starts to fall,
 * harder in hard mode. While the actor still has a valid target and the shot's
 * homing delay has passed, the velocity is steered toward the target: the flat
 * direction to it and the current flat velocity are both normalised, blended
 * by the shot's blend factor, and rescaled to the shot's speed (half again in
 * hard mode). The part is then moved along its velocity. In state two it also
 * ends its run once the shot's initial power is reached, casts its move ahead
 * and either ends the run on a stop or lands on a hit, and it takes a trail
 * every 0x36000 timer units. The sequence tracks are updated on the way out.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct Actor;

/* The shot block of a slot, which the ROM addresses through its own base. */
struct SlotShot {
    u8 nState;                       /* 0x00 */
    u8 pad01;
    s16 nTag;                        /* 0x02 blend toward the target */
    int nHalfBound;                  /* 0x04 */
    int nPower;                      /* 0x08 */
    int nRadius;                     /* 0x0c chase speed */
    short nPowerPending;             /* 0x10 */
    u8 pad12[6];
    int nPowerInit;                  /* 0x18 */
    int nField1c;                    /* 0x1c */
    int nRepeat;                     /* 0x20 */
    u8 pad24[4];
    int nHomingDelay;                /* 0x28 timer before the part homes */
    u8 pad2c[0x1c];
    int bTracked;                    /* 0x48 */
};

struct ActorSlot {
    u8 pad000[0x111];
    u8 nWeight;                      /* 0x111 */
    u8 pad112[2];
    u16 nOpen;                       /* 0x114 */
    u8 pad116[2];
    struct SlotShot shot;            /* 0x118 */
};

struct SlotPart {
    int nTimer;                      /* 0x000 */
    u8 pad004[0xc];
    struct VecFx32 vecVel;           /* 0x010 */
    u16 nSlotFlags;                  /* 0x01c */
    u8 pad01e[0xa2];
    struct VecFx32 vecAt;            /* 0x0c0 */
    int aBound[3];                   /* 0x0cc */
    u8 pad0d8[0x4c];
    u16 binding[2];                  /* 0x124 */
    u8 pad128[0x24];
    u8 nState;                       /* 0x14c */
    u8 nGroup : 3;                   /* 0x14d */
    u8 nSpare : 5;
    u8 bLive;                        /* 0x14e */
    u8 pad14f[1];
};

struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[15];    /* 0x18 */
    void *pOwner;                    /* 0x54 */
    struct Actor *pActor;            /* 0x58 */
};

/* The block the mover fills before asking the world where it stops. */
struct MoveProbe {
    struct VecFx32 vecPos;           /* 0x00 */
    struct VecFx32 vecDir;           /* 0x0c */
    int nRadius;                     /* 0x18 */
    int nDrop;                       /* 0x1c */
    int nSlotIndex;                  /* 0x20 */
    struct VecFx32 vecHit;           /* 0x24 */
};

#define SLOT_OPEN 0xffff
#define HIT_RISE 0x200
#define FALL_START 0xa000
#define MODE_HARD 1
#define GRAVITY_HARD 0x48
#define GRAVITY_NORMAL 0x30
#define FX32_ONE 0x1000
#define STATE_LIVE 2
#define REACTION_KIND 2
#define CAST_STOPPED 1
#define CAST_LANDED 2
#define TRAIL_PERIOD 0x36000

extern int func_02023c40(void);
extern int func_ov022_020ad114(struct Actor *pActor);
extern struct VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);
extern void VEC_Subtract(struct VecFx32 *pA, struct VecFx32 *pB,
                         struct VecFx32 *pOut);
extern int VEC_Mag(struct VecFx32 *pVec);
extern void func_01ff8d18(struct VecFx32 *pSrc, struct VecFx32 *pDst);
extern void func_01ffa724(int nFactor, struct VecFx32 *pSrc,
                          struct VecFx32 *pDst);
extern void VEC_MultAdd(int nScale, struct VecFx32 *pA, struct VecFx32 *pB,
                        struct VecFx32 *pOut);
extern void VEC_Add(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *pOut);
extern int func_ov022_0208acc4(int nState, int nReaction);
extern void func_ov022_0208a50c(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart, int nReaction);
extern int func_ov022_0208aa28(struct ReactionCtx *pCtx,
                               struct MoveProbe *pProbe);
extern void func_ov022_0208b400(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart,
                                struct VecFx32 *pAt, struct VecFx32 *pDir);
extern void func_ov022_0208a6b0(struct ReactionCtx *pCtx);
extern int func_0202a818(u16 *pFlags, int nDelta);

int func_ov022_0208da8c(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecDir;
    struct VecFx32 vecStep;
    struct MoveProbe probe;
    struct ActorSlot *pSlot;
    struct Actor *pActor;
    struct SlotShot *pShot;
    int nVelY;
    int nRise;
    int nGravity;
    int nScale;
    int bEnded;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    pShot = &pSlot->shot;
    nRise = pShot->nPower + HIT_RISE;
    pActor = pCtx->pActor;
    if (pSlot->nOpen == SLOT_OPEN) {
        pShot->bTracked = 0;
        pPart->nTimer = pPart->nTimer + nDelta;
        vecAt = pPart->vecAt;
        if (pPart->nTimer >= FALL_START) {
            if (func_02023c40() == MODE_HARD) {
                nGravity = GRAVITY_HARD;
            } else {
                nGravity = GRAVITY_NORMAL;
            }
            pPart->vecVel.y = pPart->vecVel.y - nGravity;
        }
        nVelY = pPart->vecVel.y;
        vecStep = pPart->vecVel;
        if (func_ov022_020ad114(pActor) != 0
            && pPart->nTimer >= pShot->nHomingDelay) {
            VEC_Subtract(func_ov022_020ad0c0(pActor), &vecAt, &vecDir);
            vecDir.y = 0;
            vecStep.y = 0;
            if (VEC_Mag(&pPart->vecVel) <= 0) {
                vecStep = vecDir;
            }
            func_01ff8d18(&vecDir, &vecDir);
            func_01ff8d18(&vecStep, &vecStep);
            func_01ffa724(pShot->nTag, &vecDir, &vecDir);
            VEC_MultAdd(FX32_ONE - pShot->nTag, &vecStep, &vecDir, &vecStep);
            if (func_02023c40() == MODE_HARD) {
                nScale = (pShot->nRadius * 3) / 2;
            } else {
                nScale = pShot->nRadius;
            }
            func_01ffa724(nScale, &vecStep, &vecStep);
            pPart->vecVel.x = vecStep.x;
            pPart->vecVel.z = vecStep.z;
        }
        vecStep.y = nVelY;
        pPart->vecVel = vecStep;
        if (pPart->nState == STATE_LIVE) {
            if (pPart->nTimer >= pShot->nPowerInit) {
                func_ov022_0208a50c(pCtx, pPart,
                                    func_ov022_0208acc4(pShot->nState,
                                                        REACTION_KIND));
            }
            probe.vecPos = vecAt;
            probe.vecDir = pPart->vecVel;
            probe.nRadius = pShot->nHalfBound;
            probe.nDrop = pShot->nPower;
            bEnded = 0;
            probe.nSlotIndex = pPart->nGroup;
            switch (func_ov022_0208aa28(pCtx, &probe)) {
            case CAST_STOPPED:
                bEnded = 1;
                break;
            case CAST_LANDED:
                vecAt = probe.vecHit;
                vecAt.y = vecAt.y + nRise;
                pPart->vecVel.y = 0;
                break;
            }
            if (bEnded != 0) {
                func_ov022_0208a50c(pCtx, pPart,
                                    func_ov022_0208acc4(pShot->nState,
                                                        REACTION_KIND));
            }
        }
        func_ov022_0208b400(pCtx, pPart, &vecAt, &pPart->vecVel);
        if (pPart->nState == STATE_LIVE) {
            VEC_Add(&vecAt, &pPart->vecVel, &vecAt);
            pPart->vecAt = vecAt;
        }
        if (pPart->nTimer % TRAIL_PERIOD == 0) {
            func_ov022_0208a6b0(pCtx);
        }
    }
    func_0202a818(&pPart->nSlotFlags, nDelta);
    return 0;
}
