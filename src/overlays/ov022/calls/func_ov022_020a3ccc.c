/* Ov022_SteerIdleByAim -- idle-state movement: steer the actor towards the
 * aim angle for one frame; returns the state change it made, or 0. Called
 * by the state-0 step when the idle step made no change.
 *
 * Without input bit 2 the local player raises flags2 bit 2. An actor that
 * is not held (flag bit 36 with flags2 bit 7) and has flags2 bit 2 adds its
 * flat motion to the step and ends into state 2. Otherwise it moves when
 * flags2 bit 19 is up without flag bit 43, or when held. Moving: the turn
 * rate is scaled by slot rule 0x2c (1.05, 1.11 or 1.2), the aim angle plus
 * the bias is clamped towards the target, the step rate eases up to the
 * rate by 0x80 (0xc0 under the recoil pick) or snaps to it, the node turns
 * unless it skips its animation, and the facing times the step rate is the
 * move (node step 0xd00), added flat to the step. A held actor then goes to
 * state 6 with the move as its motion and the hold timer cleared; button 2
 * resets the timers, keeps a fifth (a fourth under the pick) of the move as
 * the motion and arms the hold timer at 3.0; otherwise flag 0x40 is
 * configured with the rule scale (1.0 without one), the pre-draw hook runs
 * with 1 (0 under flag bit 61), the move becomes the motion, the hold timer
 * clears and, without input bit 2, the recoil takes 0.125 (0.19 under the
 * pick). Not moving: the step rate drops, the hold timer grows by 1.0 (1.5
 * under the pick) and past 1.5 the scale is reset, the pre-draw hook runs
 * with 14 (held, which also returns the held-end step) or 0 and the motion
 * clears; button 2 without a state change resets the timers. A frame with
 * no change raises flags2 bit 3 for the local player.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed long long s64;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Ov022ActorNode */
struct ActorNode {
    u32 nFlags;                  /* 0x000 */
    u16 nAnimFlags;              /* 0x004 */
    u8 pad006[0x7a];
    u16 nAngle;                  /* 0x080 */
    u8 pad082[0xc6];
    int nStep;                   /* 0x148 */
};

struct Actor;

typedef void (*ActorHookFn)(struct Actor *pActor, int nArg);   /* Ov022ActorHookFn */

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0xe];
    u16 nButtons;                /* 0x0018 */
    u8 pad001a[6];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0xc];
    short nAngleBias;            /* 0x0478 */
    u8 pad047a[0x1e];
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0x14];
    int nTurnRate;               /* 0x04b8 */
    u8 pad04bc[0xc];
    int nHoldTimer;              /* 0x04c8 */
    u8 pad04cc[0x198];
    ActorHookFn pfnPreDraw;      /* 0x0664 */
    u8 pad0668[0x30];
    VecFx32 vecMotion;           /* 0x0698 */
    u8 pad06a4[0x10];
    int nStepRate;               /* 0x06b4 */
};

#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT43 (1ULL << 43)
#define FLAG_BIT61 (1ULL << 61)
#define FLAG2_BIT2 (1ULL << 2)
#define FLAG2_BIT3 (1ULL << 3)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT19 (1ULL << 19)
#define INPUT_BIT2 0x4
#define BUTTON_2 0x2
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define RULE_TURN 0x2c
#define TURN_SCALE_1 0x10d8
#define TURN_SCALE_2 0x11c7
#define TURN_SCALE_3 0x1333
#define STEP_EASE_FAST 0xc0
#define STEP_EASE_SLOW 0x80
#define NODE_STEP_MOVE 0xd00
#define MOTION_SHARE_FAST 0x4cd
#define MOTION_SHARE_SLOW 0x333
#define HOLD_ARMED 0x3000
#define RECOIL_FAST 0x300
#define RECOIL_SLOW 0x200
#define HOLD_GROW_FAST 0x1800
#define HOLD_GROW_SLOW 0x1000
#define HOLD_LIMIT 0x1800
#define PREDRAW_HELD 0xe
#define STATE_END 2
#define STATE_JUMP 6

extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick */
extern short data_0203d210[];               /* kFxSinCosTable: sin, cos pairs */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);              /* Ov022_ActorSetState */
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_ov022_020ad4e8(struct Actor *pActor, u32 nAngle);               /* Ov022_ClampAngleTowardTarget */
extern int func_ov022_02097d50(struct Actor *pActor, int bSignal);              /* Ov022_ResetTimersAndMaybeSignal */
extern void func_ov022_020acebc(struct Actor *pActor, int nScale);              /* ConfigFlag40AndScale */
extern int func_ov022_020a98b4(struct Actor *pActor);                           /* the held-end state step */

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

int func_ov022_020a3ccc(struct Actor *pActor, int nAimAngle)
{
    VecFx32 vecMove;
    VecFx32 vecHalt;
    VecFx32 vecFlat;
    int nRet;
    int bHold;
    int bMove;
    int nRate;
    int nRule;
    int nScale;
    int nAngle;
    int nIndex;
    struct ActorNode *pNode;
    int nPick;
    int nShare;
    int nEase;

    nRet = 0;
    bHold = 0;
    bMove = 0;
    if ((pActor->nInputMask & INPUT_BIT2) == 0 && func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT2;
    }
    if (!((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0)
        && (pActor->nFlags2 & FLAG2_BIT2) != 0) {
        vecHalt = pActor->vecMotion;
        vecHalt.y = 0;
        VEC_Add(&pActor->vecStep, &vecHalt, &pActor->vecStep);
        nRet = func_ov022_020a35f4(pActor, STATE_END);
    } else {
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
            bHold = 1;
        }
        if ((pActor->nFlags2 & FLAG2_BIT19) != 0) {
            bMove = 1;
            if ((pActor->nFlags & FLAG_BIT43) != 0) {
                bMove = 0;
            }
            if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
                bMove = 1;
            }
        }
        if (bMove) {
            nRule = func_020358f4(pActor->nId, RULE_TURN);
            nRate = pActor->nTurnRate;
            nScale = 0;
            if (nRule > 0) {
                switch (nRule) {
                case 1:
                    nScale = TURN_SCALE_1;
                    break;
                case 2:
                    nScale = TURN_SCALE_2;
                    break;
                case 3:
                    nScale = TURN_SCALE_3;
                    break;
                }
                nRate = FxMul(nRate, nScale);
            }
            nAngle = func_ov022_020ad4e8(pActor, (u16)(nAimAngle + pActor->nAngleBias));
            if (pActor->nStepRate < nRate) {
                nEase = data_ov022_020b2eb0 ? STEP_EASE_FAST : STEP_EASE_SLOW;
                pActor->nStepRate += nEase;
            } else {
                pActor->nStepRate = nRate;
            }
            nIndex = nAngle >> 4;
            vecMove.x = -data_0203d210[nIndex * 2];
            vecMove.z = -data_0203d210[nIndex * 2 + 1];
            vecMove.y = 0;
            pNode = pActor->pNode;
            if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
                pNode->nAngle = nAngle + ANGLE_BIAS;
                pNode->nAnimFlags |= ANIM_HOLD;
            }
            vecMove.x = FxMul(vecMove.x, pActor->nStepRate);
            vecMove.z = FxMul(vecMove.z, pActor->nStepRate);
            vecMove.y = 0;
            pActor->pNode->nStep = NODE_STEP_MOVE;
            vecFlat = vecMove;
            vecFlat.y = 0;
            VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
            if (bHold) {
                nRet = func_ov022_020a35f4(pActor, STATE_JUMP);
                pActor->vecMotion.x = vecMove.x;
                pActor->vecMotion.z = vecMove.z;
                pActor->vecMotion.y = vecMove.y;
                pActor->nHoldTimer = 0;
            } else if ((pActor->nButtons & BUTTON_2) == BUTTON_2) {
                nRet = func_ov022_02097d50(pActor, 0);
                nPick = data_ov022_020b2eb0;
                nShare = nPick ? MOTION_SHARE_FAST : MOTION_SHARE_SLOW;
                pActor->vecMotion.x = FxMul(vecMove.x, nShare);
                nShare = nPick ? MOTION_SHARE_FAST : MOTION_SHARE_SLOW;
                pActor->vecMotion.z = FxMul(vecMove.z, nShare);
                pActor->nHoldTimer = HOLD_ARMED;
            } else {
                nRate = 0x1000;
                if (nScale > 0) {
                    nRate = nScale;
                }
                func_ov022_020acebc(pActor, (short)nRate);
                if ((pActor->nFlags & FLAG_BIT61) != 0) {
                    pActor->pfnPreDraw(pActor, 0);
                } else {
                    pActor->pfnPreDraw(pActor, 1);
                }
                pActor->vecMotion.x = vecMove.x;
                pActor->vecMotion.z = vecMove.z;
                pActor->nHoldTimer = 0;
                if ((pActor->nInputMask & INPUT_BIT2) == 0) {
                    pActor->nRecoil = data_ov022_020b2eb0 ? RECOIL_FAST : RECOIL_SLOW;
                }
            }
        } else {
            pActor->nStepRate = 0;
            pActor->nHoldTimer += data_ov022_020b2eb0 ? HOLD_GROW_FAST : HOLD_GROW_SLOW;
            if (pActor->nHoldTimer > HOLD_LIMIT) {
                func_ov022_020acebc(pActor, 0x1000);
                if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
                    pActor->pfnPreDraw(pActor, PREDRAW_HELD);
                    nRet = (int)func_ov022_020a98b4;
                } else {
                    pActor->pfnPreDraw(pActor, 0);
                }
                pActor->vecMotion.x = pActor->vecMotion.y = pActor->vecMotion.z = 0;
            }
            if ((pActor->nButtons & BUTTON_2) == BUTTON_2 && nRet == 0) {
                nRet = func_ov022_02097d50(pActor, 0);
            }
        }
    }
    if (nRet == 0 && func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT3;
    }
    return nRet;
}
