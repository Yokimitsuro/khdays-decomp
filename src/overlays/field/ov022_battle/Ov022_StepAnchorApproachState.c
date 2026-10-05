/* Ov022_StepAnchorApproachState -- run one frame of the anchor approach:
 * turn to face the target, then hand over to the anchored action or give up.
 *
 * Flag-2 bit 36 raises flag-3 bit 36 for the local player. Without input
 * bit 2 the state ends into state 0. Otherwise the move rate is picked
 * (0x2400 fast, 0x1800 slow) and, for the local player only, the target's
 * position is taken when the target reference holds. Anchor phase 1 measures
 * the flat angle to the target (a lost target raises the give-up request,
 * flag-2 bit 18) and moves to phase 2, which turns the node toward that
 * angle through the clamp; once within the turn limit (0x1200 fast, 0xc00
 * slow) the reachable test raises the proceed request (flag-2 bit 17) or the
 * give-up request. The proceed request sets phase 3 and resets the timers
 * with a signal; the give-up request clears the phase and ends into state
 * 0xe. Any change drops flag-3 bit 36. The state's own post-draw step then
 * answers whether it is over.
 */

/* Ov022ActorNode */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct ActorNode {
    u32 nFlags;                  /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad06[0x7a];
    u16 nAngle;                  /* 0x80 */
};

struct Actor;

typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x20];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x43c];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[0x18];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x18];
    int nMoveRate;               /* 0x04b0 */
    u8 pad04b4[0x1b4];
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nFlags694Rest : 6;
    u8 pad0695[0x11f];
    u8 nAnchorPhase;             /* 0x07b4 */
    u8 pad07b5[1];
    u16 nAnchorAngle;            /* 0x07b6 */
};

#define FLAG2_BIT17 (1ULL << 17)
#define FLAG2_BIT18 (1ULL << 18)
#define FLAG2_BIT36 (1ULL << 36)
#define FLAG3_BIT36 (1ULL << 36)
#define INPUT_BIT2 0x4
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define RATE_FAST 0x2400
#define RATE_SLOW 0x1800
#define TURN_LIMIT_FAST 0x1200
#define TURN_LIMIT_SLOW 0xc00
#define PHASE_MEASURE 1
#define PHASE_TURN 2
#define PHASE_ANCHOR 3
#define STATE_IDLE 0
#define STATE_GIVE_UP 0xe

extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick: picks the fast recoil and rates */

extern int Session_GetLocalPlayerIndex(void);                                                 /* Session_GetLocalPlayerIndex */
extern int Ov022_ActorSetState(struct Actor *pActor, int nState);              /* Ov022_ActorSetState */
extern int Ov022_ValidateTargetRef(struct Actor *pActor);                           /* Ov022_ValidateTargetRef */
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);                      /* Ov022_GetTargetPos */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int VEC_Mag(VecFx32 *pVec);
extern void VEC_Normalize(VecFx32 *pSrc, VecFx32 *pDst);                        /* VEC_Normalize */
extern int FX_Atan2Idx(int y, int x);
extern int Ov022_ClampAngleTowardTarget(struct Actor *pActor, u32 nAngle);               /* Ov022_ClampAngleTowardTarget */
extern int Ov022_TestAnchorReachable(struct Actor *pActor);                           /* Ov022_TestAnchorReachable */
extern int Ov022_ResetTimersAndMaybeSignal(struct Actor *pActor, int bSignal);              /* Ov022_ResetTimersAndMaybeSignal */

int Ov022_StepAnchorApproachState(struct Actor *pActor)
{
    VecFx32 vecTarget = {0, 0, 0};
    VecFx32 vecDelta;
    int nRet;
    VecFx32 *pAim;
    VecFx32 *pTarget;
    struct ActorNode *pNode;
    u16 nAngle;
    u16 nNewAngle;
    int nDelta;
    int nLimit;

    nRet = 0;
    if ((pActor->nFlags2 & FLAG2_BIT36) != 0 && Session_GetLocalPlayerIndex() == 0) {
        pActor->nFlags3 |= FLAG3_BIT36;
    }
    if ((pActor->nInputMask & INPUT_BIT2) == 0) {
        nRet = Ov022_ActorSetState(pActor, STATE_IDLE);
    } else {
        pActor->nMoveRate = data_ov022_020b2eb0 ? RATE_FAST : RATE_SLOW;
        if (Session_GetLocalPlayerIndex() == 0) {
            pAim = &pActor->vecAim;
            if (Ov022_ValidateTargetRef(pActor) != 0) {
                pTarget = func_ov022_020ad0c0(pActor);
                vecTarget = *pTarget;
            }
            switch (pActor->nAnchorPhase) {
            case PHASE_MEASURE:
                if (Ov022_ValidateTargetRef(pActor) == 0) {
                    if (Session_GetLocalPlayerIndex() == 0) {
                        pActor->nFlags2 |= FLAG2_BIT18;
                    }
                    break;
                }
                VEC_Subtract(&vecTarget, pAim, &vecDelta);
                vecDelta.y = 0;
                if (VEC_Mag(&vecDelta) != 0) {
                    VEC_Normalize(&vecDelta, &vecDelta);
                }
                pActor->nAnchorAngle = FX_Atan2Idx(-vecDelta.x, -vecDelta.z);
                pActor->nAnchorPhase = PHASE_TURN;
                /* fall through */
            case PHASE_TURN:
                if (Ov022_ValidateTargetRef(pActor) == 0) {
                    if (Session_GetLocalPlayerIndex() == 0) {
                        pActor->nFlags2 |= FLAG2_BIT18;
                    }
                } else {
                    nAngle = pActor->nAnchorAngle;
                    nNewAngle = Ov022_ClampAngleTowardTarget(pActor, nAngle);
                    pNode = pActor->pNode;
                    if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
                        pNode->nAngle = nNewAngle + ANGLE_BIAS;
                        pNode->nAnimFlags |= ANIM_HOLD;
                    }
                    nDelta = nAngle - nNewAngle;
                    if (nDelta < 0) {
                        nDelta = -nDelta;
                    }
                    nLimit = data_ov022_020b2eb0 ? TURN_LIMIT_FAST : TURN_LIMIT_SLOW;
                    if (nDelta <= nLimit) {
                        if (Ov022_TestAnchorReachable(pActor) != 0) {
                            if (Session_GetLocalPlayerIndex() == 0) {
                                pActor->nFlags2 |= FLAG2_BIT17;
                            }
                        } else {
                            if (Session_GetLocalPlayerIndex() == 0) {
                                pActor->nFlags2 |= FLAG2_BIT18;
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    if ((pActor->nFlags2 & FLAG2_BIT17) != 0) {
        pActor->nAnchorPhase = PHASE_ANCHOR;
        nRet = Ov022_ResetTimersAndMaybeSignal(pActor, 1);
    }
    if ((pActor->nFlags2 & FLAG2_BIT18) != 0) {
        pActor->nAnchorPhase = 0;
        nRet = Ov022_ActorSetState(pActor, STATE_GIVE_UP);
    }
    if (nRet != 0) {
        pActor->nFlags3 &= ~FLAG3_BIT36;
    }
    pActor->bStateOver = pActor->pfnPostDraw(pActor);
    return nRet;
}
