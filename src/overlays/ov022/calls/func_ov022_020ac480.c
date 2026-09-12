/* Ov022_StepWalkState -- run one frame of the walk state and decide whether
 * it is over.
 *
 * Input bit 2 tries to end into state 0x16 first. Without button-2 bit 1 the
 * state ends into state 2; with it a pending action is tried (once, flag bit
 * 2 marks it) and a taken action ends the state. Otherwise the aim angle,
 * biased and clamped toward the target, gives the walk direction (the node
 * turns to it unless it is skipping its animation), scaled by the fast or
 * slow step rate; that becomes the actor's motion, whose flat part is added
 * to the step. The state's own step then runs; a finished step under hit
 * reaction 3 dispatches frame 0x10000. A negative recoil is scaled by 5/8.
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
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x10];
    u16 nButtons2;               /* 0x001a */
    u8 pad001c[4];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x41c];
    short nAngleBias;            /* 0x0478 */
    u8 pad047a[0x1e];
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0x1c4];
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nFlags694Rest : 6;
    u8 pad0695[3];
    VecFx32 vecMotion;           /* 0x0698 */
    u8 pad06a4[0x10];
    int nStepRate;               /* 0x06b4 */
    u8 pad06b8[4];
    int nHitReaction;            /* 0x06bc */
    u8 pad06c0[0x23fc];
    int nAimAngle;               /* 0x2abc */
};

#define FLAG_BIT2 (1ULL << 2)
#define INPUT_BIT2 0x4
#define BUTTON2_BIT1 0x2
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define RULE_WALK 0x2e
#define STATE_END 2
#define STATE_WALK_END 0x16
#define AIM_NONE (-1)
#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4
#define RATE_FAST 0x4cd
#define RATE_SLOW 0x333
#define HIT_REACTION_3 3
#define FRAME_DISPATCH 0x10000
#define RECOIL_SCALE 0xa00

extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick: picks the fast recoil and rates */
extern short data_0203d210[];               /* sin, cos pairs by angle >> 4 */

extern int func_020358f4(int nId, int nRule);
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);             /* Ov022_ActorSetState */
extern int func_ov022_020983ec(struct Actor *pActor, int nArg);               /* Ov022_TryPendingAction */
extern int func_ov022_020ad4e8(struct Actor *pActor, u32 nAngle);             /* Ov022_ClampAngleTowardTarget */
extern void func_01ffa724(int nFactor, VecFx32 *pSrc, VecFx32 *pDst);         /* ScaleVec3Fx12 */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void func_ov022_02097038(struct Actor *pActor, int nFrame);

static inline int FX_MulInline(int nA, int nB)
{
    return (int)(((long long)nA * nB + 0x800LL) >> 12);
}

int func_ov022_020ac480(struct Actor *pActor)
{
    VecFx32 vecMove;
    VecFx32 vecFlat;
    int nRet;
    int nAngle;
    int nTrig;
    struct ActorNode *pNode;
    int nRate;

    nRet = 0;
    func_020358f4(pActor->nId, RULE_WALK);
    if ((pActor->nInputMask & INPUT_BIT2) != 0) {
        nRet = func_ov022_020a35f4(pActor, STATE_WALK_END);
        if (nRet != 0) {
            goto done;
        }
    }
    if ((pActor->nButtons2 & BUTTON2_BIT1) == 0) {
        nRet = func_ov022_020a35f4(pActor, STATE_END);
        if (!nRet) {
        } else {
            goto done;
        }
    } else {
        if ((pActor->nFlags & FLAG_BIT2) == 0) {
            nRet = func_ov022_020983ec(pActor, 0);
        }
        if (nRet != 0) {
            pActor->nFlags |= FLAG_BIT2;
            goto done;
        }
    }
    vecMove.z = 0;
    vecMove.y = 0;
    vecMove.x = 0;
    if (pActor->nAimAngle != AIM_NONE) {
        nAngle = func_ov022_020ad4e8(pActor, (u16)(pActor->nAimAngle + pActor->nAngleBias));
        nTrig = (nAngle >> ANGLE_STEP) * 2;
        vecMove.x = -data_0203d210[nTrig];
        vecMove.z = -data_0203d210[nTrig + 1];
        vecMove.y = 0;
        pNode = pActor->pNode;
        if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
            pNode->nAngle = nAngle + ANGLE_BIAS;
            pNode->nAnimFlags |= ANIM_HOLD;
        }
        nRate = data_ov022_020b2eb0 ? RATE_FAST : RATE_SLOW;
        pActor->nStepRate = nRate;
        func_01ffa724(nRate, &vecMove, &vecMove);
    }
    pActor->vecMotion.x = vecMove.x;
    pActor->vecMotion.z = vecMove.z;
    vecFlat = pActor->vecMotion;
    vecFlat.y = 0;
    VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
    pActor->bStateOver = pActor->pfnPostDraw(pActor);
    if (pActor->bStateOver != 0 && pActor->nHitReaction == HIT_REACTION_3) {
        func_ov022_02097038(pActor, FRAME_DISPATCH);
    }
    if (pActor->nRecoil < 0) {
        pActor->nRecoil = FX_MulInline(pActor->nRecoil, RECOIL_SCALE);
    }
done:
    return nRet;
}
