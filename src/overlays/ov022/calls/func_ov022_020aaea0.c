/* Ov022_StepHeldMoveState -- run one frame of state 0x12, a held action
 * that moves, and decide whether it is over.
 *
 * The local player raises flag-2 bit 12, and flag-3 bit 7 too when flag bit
 * 36 and flag-2 bit 7 are both up. At frame 3.0 with a valid target the
 * node turns to face it. Without the reaction context enabled the frame is
 * held at 18.0. The anchor delta drives the step: with input bit 2 it is
 * added flat unless the state timer is ahead of the frame (then the timer
 * is pulled back); without it, flag bit 10 zeroes the delta, the recoil
 * takes its height (or 0 when the timer is pulled back) and flag bit 46 is
 * raised under bit 36 with flag-2 bit 7. The state's own step then answers
 * whether it is done: that raises flag bit 49, pokes the animation and
 * raises the end request for the local player. Once the request is up the
 * state ends: with bit 36 and flag-2 bit 7 it drops flag bit 2, runs the
 * pre-draw hook with 14 and ends into state 6; with input bit 2 it drops
 * bit 2 and, by the slot move mode of the held arg, ends into state 0x16
 * (mode 0x19, models other than 2 and 0xd) or into state 0 through the
 * pre-draw hook; otherwise bit 2 goes up, the motion is cleared, the
 * recoil takes the delta's height and it ends into state 2. A state that
 * did not end raises flag-3 bit 12; one that did clears the context's busy
 * flag.
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

typedef void (*PreDrawFn)(struct Actor *pActor, int nReplay);
typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[4];
    int nModelId;                /* 0x000c */
    u8 pad0010[0x10];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[0x18];
    VecFx32 vecAim;              /* 0x048c */
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0x28];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0x14];
    u16 nHeldArg;                /* 0x04e4 */
    u8 pad04e6[0x17e];
    PreDrawFn pfnPreDraw;        /* 0x0664 */
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nFlags694Rest : 6;
    u8 pad0695[3];
    VecFx32 vecMotion;           /* 0x0698 */
    u8 pad06a4[0x10c];
    int nAnimFrame;              /* 0x07b0 */
    u8 pad07b4[0x1ad4];
    u16 reactionCtx[0x38];       /* 0x2288 Ov022ReactionCtx */
};

#define FLAG_BIT2 (1ULL << 2)
#define FLAG_BIT10 (1ULL << 10)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT46 (1ULL << 46)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT1 (1ULL << 1)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT12 (1ULL << 12)
#define FLAG3_BIT7 (1ULL << 7)
#define FLAG3_BIT12 (1ULL << 12)
#define INPUT_BIT2 0x4
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define FRAME_FACE 0x3000
#define FRAME_HOLD 0x12000
#define PREDRAW_HELD 0xe
#define PREDRAW_IDLE 0
#define MOVE_MODE_LAND 0x19
#define MODEL_2 2
#define MODEL_D 0xd
#define STATE_IDLE 0
#define STATE_END 2
#define STATE_HELD_END 6
#define STATE_LAND 0x16

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_ov022_020ad114(struct Actor *pActor);                           /* Ov022_ValidateTargetRef */
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);                      /* Ov022_GetTargetPos */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int FX_Atan2(int y, int x);
extern int func_ov022_02090308(u16 *pCtx);                                      /* Ov022_IsEnabledAndFlag100Set */
extern void func_ov022_02097038(struct Actor *pActor, int nFrame);              /* SetField7b0AndDispatch */
extern void func_ov022_0209fe20(struct Actor *pActor, VecFx32 *pOut);           /* Ov022_StepAnchorDelta */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void func_0202af1c(u16 *pAnimFlags);                                     /* SceneNode_Enable */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);              /* Ov022_ActorSetState */
extern int func_ov022_02090978(u16 *pCtx, int nArg);                            /* Ov022_GetSlotMoveMode */
extern void func_ov022_02090338(u16 *pCtx);                                     /* ClearFlag100IfBusy */

int func_ov022_020aaea0(struct Actor *pActor)
{
    VecFx32 vecDelta;
    VecFx32 vecToTarget;
    VecFx32 vecFlatA;
    VecFx32 vecFlatB;
    int nRet;
    VecFx32 *pTarget;
    u16 nAngle;
    struct ActorNode *pNode;
    int nMode;

    nRet = 0;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT12;
    }
    if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0
        && func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT7;
    }
    if (pActor->nAnimFrame == FRAME_FACE && func_ov022_020ad114(pActor) != 0) {
        pTarget = func_ov022_020ad0c0(pActor);
        VEC_Subtract(pTarget, &pActor->vecAim, &vecToTarget);
        vecToTarget.y = 0;
        nAngle = FX_Atan2(-vecToTarget.x, -vecToTarget.z);
        pNode = pActor->pNode;
        if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
            pNode->nAngle = nAngle + ANGLE_BIAS;
            pNode->nAnimFlags |= ANIM_HOLD;
        }
    }
    if (func_ov022_02090308(pActor->reactionCtx) == 0 && pActor->nAnimFrame >= FRAME_HOLD) {
        func_ov022_02097038(pActor, FRAME_HOLD);
    }
    func_ov022_0209fe20(pActor, &vecDelta);
    if ((pActor->nInputMask & INPUT_BIT2) != 0) {
        if ((int)pActor->nStateTimer > pActor->nAnimFrame) {
            pActor->nStateTimer = pActor->nAnimFrame;
        } else {
            vecFlatA = vecDelta;
            vecFlatA.y = 0;
            VEC_Add(&pActor->vecStep, &vecFlatA, &pActor->vecStep);
        }
    } else {
        if ((pActor->nFlags & FLAG_BIT10) != 0) {
            vecDelta.x = vecDelta.y = vecDelta.z = 0;
        }
        if ((int)pActor->nStateTimer <= pActor->nAnimFrame) {
            pActor->nRecoil = vecDelta.y;
            vecFlatB = vecDelta;
            vecFlatB.y = 0;
            VEC_Add(&pActor->vecStep, &vecFlatB, &pActor->vecStep);
        } else {
            pActor->nStateTimer = pActor->nAnimFrame;
            pActor->nRecoil = 0;
        }
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
            pActor->nFlags |= FLAG_BIT46;
        }
    }
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
    if ((pActor->nFlags2 & FLAG2_BIT1) != 0) {
        if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
            pActor->nFlags &= ~FLAG_BIT2;
            pActor->pfnPreDraw(pActor, PREDRAW_HELD);
            nRet = func_ov022_020a35f4(pActor, STATE_HELD_END);
        } else if ((pActor->nInputMask & INPUT_BIT2) != 0) {
            pActor->nFlags &= ~FLAG_BIT2;
            nMode = func_ov022_02090978(pActor->reactionCtx, pActor->nHeldArg);
            if (nMode != MOVE_MODE_LAND) {
                pActor->pfnPreDraw(pActor, PREDRAW_IDLE);
                nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
            } else if (pActor->nModelId == MODEL_2 || pActor->nModelId == MODEL_D) {
                pActor->pfnPreDraw(pActor, PREDRAW_IDLE);
                nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
            } else {
                nRet = func_ov022_020a35f4(pActor, STATE_LAND);
            }
        } else {
            pActor->nFlags |= FLAG_BIT2;
            pActor->vecMotion.x = pActor->vecMotion.y = pActor->vecMotion.z = 0;
            pActor->nRecoil = vecDelta.y;
            nRet = func_ov022_020a35f4(pActor, STATE_END);
        }
    }
    if (nRet == 0) {
        pActor->nFlags3 |= FLAG3_BIT12;
    } else {
        func_ov022_02090338(pActor->reactionCtx);
    }
    return nRet;
}
