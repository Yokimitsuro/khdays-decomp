/* Ov022_StepFlyingPart -- one frame of a part in flight that chases a target.
 *
 * The part's timer takes the frame delta; past a threshold it starts to fall,
 * harder at 20 fps. While the actor still has a valid target and the shot's
 * homing delay has passed, the velocity is steered toward the target: the flat
 * direction to it and the current flat velocity are both normalised, blended
 * by the shot's blend factor, and rescaled to the shot's speed (half again at
 * 20 fps). The part is then moved along its velocity. In state two it also
 * ends its run once the shot's initial power is reached, casts its move ahead
 * and either ends the run on a stop or lands on a hit, and it takes a trail
 * every 0x36000 timer units. The sequence tracks are updated on the way out.
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

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
    VecFx32 vecVel;           /* 0x010 */
    u16 nSlotFlags;                  /* 0x01c */
    u8 pad01e[0xa2];
    VecFx32 vecAt;            /* 0x0c0 */
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
    void *pLevelAnim;                    /* 0x54: the cast's level animation (its grid entry) */
    struct Actor *pActor;            /* 0x58 */
};

/* The block the mover fills before asking the world where it stops. */
struct MoveProbe {
    VecFx32 vecPos;           /* 0x00 */
    VecFx32 vecDir;           /* 0x0c */
    int nRadius;                     /* 0x18 */
    int nDrop;                       /* 0x1c */
    int nSlotIndex;                  /* 0x20 */
    VecFx32 vecHit;           /* 0x24 */
};

#define SLOT_OPEN 0xffff
#define HIT_RISE 0x200
#define FALL_START 0xa000
#define FRAME_RATE_20FPS 1   /* GetFrameRateMode(): 0 = 30 fps, 1 = 20 fps, 2 = 60 fps */
#define GRAVITY_20FPS 0x48
#define GRAVITY_NORMAL 0x30
#define FX32_ONE 0x1000
#define STATE_LIVE 2
#define REACTION_KIND 2
#define CAST_STOPPED 1
#define CAST_LANDED 2
#define TRAIL_PERIOD 0x36000

extern int Ov022_ValidateTargetRef(struct Actor *pActor);
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB,
                         VecFx32 *pOut);
extern int VEC_Mag(VecFx32 *pVec);
extern void VEC_Normalize(VecFx32 *pSrc, VecFx32 *pDst);
extern void ScaleVec3Fx12(int nFactor, VecFx32 *pSrc,
                          VecFx32 *pDst);
extern void VEC_MultAdd(int nScale, VecFx32 *pA, VecFx32 *pB,
                        VecFx32 *pOut);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *pOut);
extern int Ov022_ClampReactionForKind10(int nState, int nReaction);
extern void Ov022_EndPartRun(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart, int nReaction);
extern int Ov022_CastMove(struct ReactionCtx *pCtx,
                               struct MoveProbe *pProbe);
extern void Ov022_MovePartTo(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart,
                                VecFx32 *pAt, VecFx32 *pDir);
extern void func_ov022_0208a6b0(struct ReactionCtx *pCtx);
extern unsigned short Sequence_UpdateTracks(u16 *pFlags, int nDelta);

int Ov022_StepFlyingPart(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta)
{
    VecFx32 vecAt;
    VecFx32 vecDir;
    VecFx32 vecStep;
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
            if (GetFrameRateMode() == FRAME_RATE_20FPS) {
                nGravity = GRAVITY_20FPS;
            } else {
                nGravity = GRAVITY_NORMAL;
            }
            pPart->vecVel.y = pPart->vecVel.y - nGravity;
        }
        nVelY = pPart->vecVel.y;
        vecStep = pPart->vecVel;
        if (Ov022_ValidateTargetRef(pActor) != 0
            && pPart->nTimer >= pShot->nHomingDelay) {
            VEC_Subtract(func_ov022_020ad0c0(pActor), &vecAt, &vecDir);
            vecDir.y = 0;
            vecStep.y = 0;
            if (VEC_Mag(&pPart->vecVel) <= 0) {
                vecStep = vecDir;
            }
            VEC_Normalize(&vecDir, &vecDir);
            VEC_Normalize(&vecStep, &vecStep);
            ScaleVec3Fx12(pShot->nTag, &vecDir, &vecDir);
            VEC_MultAdd(FX32_ONE - pShot->nTag, &vecStep, &vecDir, &vecStep);
            if (GetFrameRateMode() == FRAME_RATE_20FPS) {
                nScale = (pShot->nRadius * 3) / 2;
            } else {
                nScale = pShot->nRadius;
            }
            ScaleVec3Fx12(nScale, &vecStep, &vecStep);
            pPart->vecVel.x = vecStep.x;
            pPart->vecVel.z = vecStep.z;
        }
        vecStep.y = nVelY;
        pPart->vecVel = vecStep;
        if (pPart->nState == STATE_LIVE) {
            if (pPart->nTimer >= pShot->nPowerInit) {
                Ov022_EndPartRun(pCtx, pPart,
                                    Ov022_ClampReactionForKind10(pShot->nState,
                                                        REACTION_KIND));
            }
            probe.vecPos = vecAt;
            probe.vecDir = pPart->vecVel;
            probe.nRadius = pShot->nHalfBound;
            probe.nDrop = pShot->nPower;
            bEnded = 0;
            probe.nSlotIndex = pPart->nGroup;
            switch (Ov022_CastMove(pCtx, &probe)) {
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
                Ov022_EndPartRun(pCtx, pPart,
                                    Ov022_ClampReactionForKind10(pShot->nState,
                                                        REACTION_KIND));
            }
        }
        Ov022_MovePartTo(pCtx, pPart, &vecAt, &pPart->vecVel);
        if (pPart->nState == STATE_LIVE) {
            VEC_Add(&vecAt, &pPart->vecVel, &vecAt);
            pPart->vecAt = vecAt;
        }
        if (pPart->nTimer % TRAIL_PERIOD == 0) {
            func_ov022_0208a6b0(pCtx);
        }
    }
    Sequence_UpdateTracks(&pPart->nSlotFlags, nDelta);
    return 0;
}
