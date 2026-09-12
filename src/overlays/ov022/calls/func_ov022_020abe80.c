/* Ov022_StepRushState -- run one frame of the rush at the target and decide
 * whether the state is over.
 *
 * The local player raises flag-2 bit 36 every frame and bit 60 on the first
 * one. A lost target ends into state 0; a pending action takes over. Once the
 * rush clock runs (not the -0x1000 sentinel) it advances by the global step.
 * Within reach * 0x2c00 of the target, or with the rush speed under 0xcd, the
 * state ends into state 3. Otherwise the node turns toward the target
 * through the clamp and the move is the clamped facing at the rush speed.
 * Within 0x5000 of the target the rush clock starts (sampling the position)
 * and every 0x3000 of it the speed loses 0x80 (floored at 0) and the sample
 * is refreshed, remembering the previous one. The flat move is added to the
 * step and the state's own post-draw step runs. Without input bit 2 the move
 * becomes the motion, the recoil is 0x300 or 0x200 by the recoil pick and the
 * state ends into state 2. Past state time 0x1e000, or when a fresh sample
 * moved less than 0x1000, it ends into state 0.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Ov022ActorNode */
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
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x16];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x20];
    VecFx32 vecAim;              /* 0x048c */
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0x28];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0x198];
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x2c];
    VecFx32 vecMotion;           /* 0x0698 */
    VecFx32 vecRushSample;       /* 0x06a4 */
    u8 pad06b0[0x280];
    short nChaseReach;           /* 0x0930 */
    u8 pad0932[0x1d2e];
    int nRushSpeed;              /* 0x2660 */
    int nRushTime;               /* 0x2664 */
};

#define FLAG2_BIT36 (1ULL << 36)
#define FLAG2_BIT60 (1ULL << 60)
#define INPUT_BIT2 0x4
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4
#define RULE_RUSH 0x27
#define REACH_UNIT 0x2c00
#define SPEED_MIN 0xcd
#define SPEED_DROP 0x80
#define RUSH_NOT_STARTED (-0x1000)
#define RUSH_SAMPLE_EVERY 0x3000
#define DIST_SAMPLE 0x5000
#define DIST_STUCK 0x1000
#define TIME_END 0x1e000
#define RECOIL_FAST 0x300
#define RECOIL_SLOW 0x200
#define STATE_IDLE 0
#define STATE_END 2
#define STATE_REACHED 3

extern const short data_0203d210[];         /* sin, cos pairs by angle >> 4 */
extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick: picks the fast recoil and rates */

extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_ov022_020ad114(struct Actor *pActor);                           /* Ov022_ValidateTargetRef */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);              /* Ov022_ActorSetState */
extern int func_ov022_020983ec(struct Actor *pActor, int bEnabled);            /* Ov022_TryPendingAction */
extern int func_ov022_02083f90(void);                                           /* Ov022_GetGlobal34 */
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);                      /* Ov022_GetTargetPos */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int VEC_Mag(VecFx32 *pVec);
extern int FX_Atan2(int y, int x);
extern int func_ov022_020ad4e8(struct Actor *pActor, u32 nAngle);               /* Ov022_ClampAngleTowardTarget */
extern void func_01ffa724(int nFactor, VecFx32 *pSrc, VecFx32 *pDst);          /* ScaleVec3Fx12 */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);

int func_ov022_020abe80(struct Actor *pActor)
{
    VecFx32 vecPos;
    VecFx32 vecDelta;
    VecFx32 vecMove;
    VecFx32 vecTarget;
    VecFx32 vecFlat;
    int nRet;
    int nReach;
    int bSampled;
    int bDone;
    VecFx32 *pTarget;
    struct ActorNode *pNode;
    u16 nAngle;
    int nNewAngle;
    int nTrig;

    nReach = pActor->nChaseReach;
    func_020358f4(pActor->nId, RULE_RUSH);
    bSampled = 0;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT36;
    }
    if (pActor->nStateTimer == 0 && func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT60;
    }
    if (func_ov022_020ad114(pActor) == 0) {
        nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
    } else {
        nRet = func_ov022_020983ec(pActor, 0);
        if (nRet == 0) {
            if (pActor->nRushTime != RUSH_NOT_STARTED) {
                pActor->nRushTime += func_ov022_02083f90();
            }
            pTarget = func_ov022_020ad0c0(pActor);
            vecTarget = *pTarget;
            vecTarget.y = 0;
            vecPos = pActor->vecAim;
            vecPos.y = 0;
            VEC_Subtract(&vecTarget, &vecPos, &vecDelta);
            if (VEC_Mag(&vecDelta) < (int)(((long long)nReach * REACH_UNIT + 0x800) >> 12)
                || pActor->nRushSpeed < SPEED_MIN) {
                nRet = func_ov022_020a35f4(pActor, STATE_REACHED);
            } else {
                nAngle = FX_Atan2(-vecDelta.x, -vecDelta.z);
                nNewAngle = func_ov022_020ad4e8(pActor, nAngle);
                pNode = pActor->pNode;
                if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
                    pNode->nAngle = nNewAngle + ANGLE_BIAS;
                    pNode->nAnimFlags |= ANIM_HOLD;
                }
                nTrig = (nNewAngle >> ANGLE_STEP) * 2;
                vecMove.x = -data_0203d210[nTrig];
                vecMove.z = -data_0203d210[nTrig + 1];
                vecMove.y = 0;
                func_01ffa724(pActor->nRushSpeed, &vecMove, &vecMove);
                if (VEC_Mag(&vecDelta) < DIST_SAMPLE) {
                    if (pActor->nRushTime == RUSH_NOT_STARTED) {
                        pActor->nRushTime = 0;
                        pActor->vecRushSample = vecPos;
                    } else if (pActor->nRushTime % RUSH_SAMPLE_EVERY == 0) {
                        pActor->nRushSpeed -= SPEED_DROP;
                        vecTarget = pActor->vecRushSample;
                        pActor->vecRushSample = vecPos;
                        bSampled = 1;
                        if (pActor->nRushSpeed <= 0) {
                            pActor->nRushSpeed = 0;
                        }
                    }
                }
                vecFlat = vecMove;
                vecFlat.y = 0;
                VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
                pActor->pfnPostDraw(pActor);
                if ((pActor->nInputMask & INPUT_BIT2) == 0) {
                    pActor->vecMotion = vecMove;
                    pActor->nRecoil = data_ov022_020b2eb0 ? RECOIL_FAST : RECOIL_SLOW;
                    nRet = func_ov022_020a35f4(pActor, STATE_END);
                } else {
                    bDone = 0;
                    if ((int)pActor->nStateTimer >= TIME_END) {
                        bDone = 1;
                    } else if (bSampled) {
                        VEC_Subtract(&vecTarget, &vecPos, &vecDelta);
                        if (VEC_Mag(&vecDelta) < DIST_STUCK) {
                            bDone = 1;
                        }
                    }
                    if (bDone) {
                        nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
                    }
                }
            }
        }
    }
    return nRet;
}
