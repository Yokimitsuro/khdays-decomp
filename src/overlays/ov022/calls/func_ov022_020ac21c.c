/* Ov022_StepLaunchState -- run one frame of the launched state and decide
 * whether it is over.
 *
 * On the first frame the move is set up: reaction 0x14 only gets a recoil of
 * 0x600; any other gets 0x500 and a move of 0x700 along the aim angle (biased,
 * which the node also turns to unless it is skipping its animation). Later
 * frames move by the velocity, which loses a 0x80 step along its own
 * direction every 3 units of state time from 6 on. The flat part of the move
 * is added to the step. The state's own step then answers whether it is
 * done: that raises flag bit 49, pokes the animation and raises the end
 * request for the local player. Past 12 units the state ends into state 2,
 * or 0 with input bit 2 held.
 *
 * Lever: the sin/cos table is const, so its two loads may move above the recoil
 * and vecMove.y stores (a non-const table keeps the stores hoisted above them).
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
    u8 pad0008[0x18];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    VecFx32 vecVel;              /* 0x0028 */
    u8 pad0034[0x24];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0xc];
    short nAngleBias;            /* 0x0478 */
    u8 pad047a[0x1e];
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0x28];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0x198];
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nFlags694Rest : 6;
    u8 pad0695[0x27];
    int nHitReaction;            /* 0x06bc */
    u8 pad06c0[0x23fc];
    int nAimAngle;               /* 0x2abc */
};

#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT1 (1ULL << 1)
#define INPUT_BIT2 0x4
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4
#define REACTION_HOP 0x14
#define RECOIL_HOP 0x600
#define RECOIL_LAUNCH 0x500
#define LAUNCH_SPEED 0x700
#define DRAG_STEP 0x80
#define TIME_DRAG_FROM 0x6000
#define TIME_DRAG_EVERY 0x3000
#define TIME_END 0xc000
#define STATE_IDLE 0
#define STATE_END 2

extern const short data_0203d210[];         /* sin, cos pairs by angle >> 4 */

extern void func_01ffa724(int nFactor, VecFx32 *pSrc, VecFx32 *pDst);         /* ScaleVec3Fx12 */
extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);                       /* VEC_Normalize */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void func_0202af1c(u16 *pAnimFlags);                                    /* SceneNode_Enable */
extern int func_02030788(void);
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);             /* Ov022_ActorSetState */

int func_ov022_020ac21c(struct Actor *pActor)
{
    VecFx32 vecMove;
    VecFx32 vecUnit;
    VecFx32 vecFlat;
    int nRet;
    u16 nAngle;
    int nTrig;
    short nSin;
    short nCos;
    int nSinNeg;
    int nCosNeg;
    u16 nBiased;
    struct ActorNode *pNode;

    nRet = 0;
    if (pActor->nStateTimer == 0) {
        vecMove.z = 0;
        vecMove.y = 0;
        vecMove.x = 0;
        if (pActor->nHitReaction == REACTION_HOP) {
            pActor->nRecoil = RECOIL_HOP;
        } else {
            nAngle = pActor->nAimAngle + pActor->nAngleBias;
            nTrig = (nAngle >> ANGLE_STEP) * 2;
            nSinNeg = -data_0203d210[nTrig];
            nCosNeg = -data_0203d210[nTrig + 1];
            pActor->nRecoil = RECOIL_LAUNCH;
            nBiased = nAngle + ANGLE_BIAS;
            vecMove.x = nSinNeg;
            vecMove.z = nCosNeg;
            vecMove.y = 0;
            pNode = pActor->pNode;
            if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
                pNode->nAngle = nBiased + ANGLE_BIAS;
                pNode->nAnimFlags |= ANIM_HOLD;
            }
            func_01ffa724(LAUNCH_SPEED, &vecMove, &vecMove);
        }
    } else {
        if ((int)pActor->nStateTimer >= TIME_DRAG_FROM
            && (int)pActor->nStateTimer % TIME_DRAG_EVERY == 0) {
            if (VEC_Mag(&pActor->vecVel) == 0) {
                vecUnit = pActor->vecVel;
            } else {
                func_01ff8d18(&pActor->vecVel, &vecUnit);
            }
            func_01ffa724(DRAG_STEP, &vecUnit, &vecUnit);
            VEC_Subtract(&pActor->vecVel, &vecUnit, &pActor->vecVel);
        }
        vecMove = pActor->vecVel;
    }
    vecFlat = vecMove;
    vecFlat.y = 0;
    VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
    pActor->bStateOver = pActor->pfnPostDraw(pActor);
    if (pActor->bStateOver != 0) {
        pActor->nFlags |= FLAG_BIT49;
        if ((pActor->pNode->nFlags & NODE_NO_ANIM) == 0) {
            func_0202af1c(&pActor->pNode->nAnimFlags);
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT1;
        }
    }
    if ((int)pActor->nStateTimer >= TIME_END) {
        if ((pActor->nInputMask & INPUT_BIT2) != 0) {
            nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
        } else {
            nRet = func_ov022_020a35f4(pActor, STATE_END);
        }
    }
    return nRet;
}
