
/* The shot block of a slot, which the ROM addresses through its own base. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

struct SlotShot {
    u8 nState;                       /* 0x00 */
    u8 pad01[3];
    int nHalfBound;                  /* 0x04 */
    int nPower;                      /* 0x08 */
    int nRadius;                     /* 0x0c */
    short nPowerPending;             /* 0x10 */
    u8 pad12[6];
    int nPowerInit;                  /* 0x18 */
    int nField1c;                    /* 0x1c */
    int nRepeat;                     /* 0x20 */
    u8 pad24[4];
    int nField28;                    /* 0x28 */
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
    void *pActor;                    /* 0x58 */
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
#define MARGIN_LIMIT 0x59a
#define HIT_RISE 0x200
#define FRAME_RATE_20FPS 1   /* GetFrameRateMode(): 0 = 30 fps, 1 = 20 fps, 2 = 60 fps */
#define STATE_LIVE 2
#define REACTION_KIND 2
#define WEIGHT_LIGHT 3
#define CAST_STOPPED 1
#define CAST_LANDED 2
#define CAST_BLOCKED 3
#define BIND_LANDED 3

extern int func_ov022_0208a9ac(int nRadius, int nPending, int nTimer);
extern void ScaleVec3Fx12(int nFactor, VecFx32 *pSrc,
                          VecFx32 *pDst);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *pOut);
extern void Ov022_MovePartTo(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart,
                                VecFx32 *pAt, VecFx32 *pDir);
extern int Ov022_ClampReactionForKind10(int nState, int nReaction);
extern void Ov022_EndPartRun(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart, int nReaction);
extern int Ov022_CastMove(struct ReactionCtx *pCtx,
                               struct MoveProbe *pProbe);
extern void Ov022_BindBlockAnimations(struct ReactionCtx *pCtx, u16 *pBinding,
                                u16 *pFlags, int nIndex);
extern unsigned short Sequence_UpdateTracks(u16 *pFlags, int nDelta);

int Ov022_StepBoundPart(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta)
{
    VecFx32 vecAt;
    VecFx32 vecStep;
    struct MoveProbe probe;
    struct ActorSlot *pSlot;
    struct SlotShot *pShot;
    int nRise;
    int nScale;
    int nGravity;
    int nBound;
    int bEnded;
    int nResult;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    pShot = &pSlot->shot;
    nRise = pShot->nPower + HIT_RISE;
    if (pSlot->nOpen == SLOT_OPEN) {
        pShot->bTracked = 0;
        pPart->nTimer = pPart->nTimer + nDelta;
        vecAt = pPart->vecAt;
        vecStep = pPart->vecVel;
        if (pPart->nTimer >= pShot->nField28 && pPart->bLive != 0) {
            nScale = func_ov022_0208a9ac(pShot->nRadius, pShot->nPowerPending,
                                         pPart->nTimer);
            ScaleVec3Fx12(nScale, &pPart->vecVel, &vecStep);
            if (nScale <= MARGIN_LIMIT) {
                if (pSlot->nWeight <= WEIGHT_LIGHT) {
                    if (GetFrameRateMode() == FRAME_RATE_20FPS) {
                        nGravity = 0x180;
                    } else {
                        nGravity = 0x100;
                    }
                    vecStep.y = vecStep.y - nGravity;
                } else {
                    if (GetFrameRateMode() == FRAME_RATE_20FPS) {
                        nGravity = 0x300;
                    } else {
                        nGravity = 0x200;
                    }
                    vecStep.y = vecStep.y - nGravity;
                }
            }
        }
        VEC_Add(&vecAt, &vecStep, &vecAt);
        pPart->vecAt = vecAt;
        Ov022_MovePartTo(pCtx, pPart, &vecAt, &pPart->vecVel);
        if (pPart->nState == STATE_LIVE
            && pPart->nTimer >= pShot->nPowerInit) {
            Ov022_EndPartRun(pCtx, pPart,
                                Ov022_ClampReactionForKind10(pShot->nState,
                                                    REACTION_KIND));
        }
        if (pPart->bLive != 0 && pPart->nState == STATE_LIVE) {
            probe.vecPos = vecAt;
            probe.vecDir = pPart->vecVel;
            probe.vecDir.y = vecStep.y;
            probe.nRadius = pShot->nHalfBound;
            probe.nDrop = pShot->nPower;
            bEnded = 0;
            probe.nSlotIndex = pPart->nGroup;
            nResult = Ov022_CastMove(pCtx, &probe);
            switch (nResult) {
            case CAST_STOPPED:
                pPart->vecVel.z = 0;
                pPart->vecVel.y = 0;
                pPart->vecVel.x = 0;
                Ov022_BindBlockAnimations(pCtx, pPart->binding, &pPart->nSlotFlags,
                                    BIND_LANDED);
                nBound = pShot->nRepeat;
                pPart->aBound[2] = nBound;
                pPart->aBound[1] = nBound;
                pPart->aBound[0] = nBound;
                pShot->nHalfBound = pShot->nField1c;
                pPart->bLive = 0;
                break;
            case CAST_LANDED:
                vecAt = probe.vecHit;
                vecAt.y = vecAt.y + nRise;
                pPart->vecAt = vecAt;
                Ov022_BindBlockAnimations(pCtx, pPart->binding, &pPart->nSlotFlags,
                                    BIND_LANDED);
                nBound = pShot->nRepeat;
                pPart->aBound[2] = nBound;
                pPart->aBound[1] = nBound;
                pPart->aBound[0] = nBound;
                pShot->nHalfBound = pShot->nField1c;
                pPart->bLive = 0;
                pPart->vecVel.z = 0;
                pPart->vecVel.y = 0;
                pPart->vecVel.x = 0;
                break;
            case CAST_BLOCKED:
                bEnded = 1;
                break;
            }
            if (bEnded != 0) {
                Ov022_EndPartRun(pCtx, pPart,
                                    Ov022_ClampReactionForKind10(pShot->nState,
                                                        REACTION_KIND));
            }
        }
    }
    Sequence_UpdateTracks(&pPart->nSlotFlags, nDelta);
    return 0;
}
