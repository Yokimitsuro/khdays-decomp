/* Ov022_StepChaseState -- run one frame of the chase state: close in on the
 * target, then decide whether the state is over.
 *
 * The interrupt charge is held at 0x3000 or more. Under slot rule 0x2b, while
 * the state time is under 0x3000, an effect is requested at (0, 0x800, 0x800)
 * with flag bit 0 and scale 0x2800; when a handler takes it and the contact
 * result lacks bit 6, the aim is sent from the contact point to the effect's
 * place. A negative recoil is cleared. With a valid target under rule 0x2a
 * the actor chases: the flat direction to the target, scaled by 0xa00,
 * becomes the motion (the node turns to face it unless it skips its
 * animation), except within reach * 0x2c00 of the target or past state time
 * 0x3000, where the motion is cleared. The flat motion is added to the step.
 * The state's own post-draw step then answers whether it is over: that raises
 * flag bit 49, pokes the animation and raises the end request for the local
 * player. The end request drops flag bit 2, resets the reach block and ends
 * into state 2.
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

/* Ov022EffectPlace */
struct EffectPlace {
    VecFx32 vecAt;               /* 0x00 */
    int nScaleX;                 /* 0x0c */
    int nSlotIndex;              /* 0x10 */
    VecFx32 vecFace;             /* 0x14 */
    int nScaleZ;                 /* 0x20 */
    void *pTail;                 /* 0x24 */
    int nField28;                /* 0x28 */
};

/* Ov022EffectRequest */
struct EffectRequest {
    u8 pad00[8];
    int nFlags;                  /* 0x08 */
    u8 pad0c[8];
    VecFx32 vecAt;               /* 0x14 */
    int nCount;                  /* 0x20 */
    u8 pad24[4];
};

struct Actor;

typedef int (*PostDrawFn)(struct Actor *pActor);

/* Ov022SweepContact */
struct SweepContact {
    u32 nResult;                 /* 0x00 */
    int nKind;                   /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 pad09[3];
    VecFx32 vec;                 /* 0x0c */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x16];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x34];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x20];
    VecFx32 vecAim;              /* 0x048c */
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0x10];
    int nInterruptCharge;        /* 0x04b4 */
    u8 pad04b8[0x14];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0x198];
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nFlags694Rest : 6;
    u8 pad0695[3];
    VecFx32 vecMotion;           /* 0x0698 */
    u8 pad06a4[0x28c];
    short nChaseReach;           /* 0x0930 */
    u8 pad0932[0x135a];
    u8 blkReach[0x110];          /* 0x1c8c */
    u8 pad1d9c[0x920];
    struct SweepContact contact; /* 0x26bc */
};

#define FLAG_BIT2 (1ULL << 2)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT1 (1ULL << 1)
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define CONTACT_NO_AIM 0x40
#define RULE_EFFECT 0x2b
#define RULE_CHASE 0x2a
#define CHARGE_MIN 0x3000
#define TIME_EFFECT 0x3000
#define TIME_CHASE 0x3000
#define EFFECT_UP 0x800
#define EFFECT_SCALE 0x2800
#define REQUEST_FLAG0 1
#define REACH_UNIT 0x2c00
#define CHASE_SPEED 0xa00
#define STATE_END 2

extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern void func_ov022_020ad62c(struct Actor *pActor, VecFx32 *pAt, struct EffectPlace *pPlace,
                                struct EffectRequest *pRequest);                /* Ov022_FillEffectBlocks */
extern int func_ov022_020a0fb8(struct Actor *pActor, struct EffectPlace *pPlace,
                               struct EffectRequest *pRequest);                 /* Ov022_RunCommandHandlers */
extern void func_ov022_0209cf58(struct Actor *pActor, VecFx32 *pFrom, VecFx32 *pTo, int nHeight,
                                int bCheck);                                    /* Ov022_SendAimAtTarget */
extern int func_ov022_020ad114(struct Actor *pActor);                           /* Ov022_ValidateTargetRef */
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);                      /* Ov022_GetTargetPos */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);                        /* VEC_Normalize */
extern void func_01ffa724(int nFactor, VecFx32 *pSrc, VecFx32 *pDst);          /* ScaleVec3Fx12 */
extern int FX_Atan2(int y, int x);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void func_0202af1c(u16 *pAnimFlags);                                     /* SceneNode_Enable */
extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern void func_ov022_02094160(u8 *pBlk);
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);              /* Ov022_ActorSetState */

int func_ov022_020abb6c(struct Actor *pActor)
{
    struct EffectPlace place;
    struct EffectRequest request;
    VecFx32 vecOffset;
    VecFx32 vecDelta;
    VecFx32 vecFlat;
    int nRet;
    int bChase;
    int nReach;
    VecFx32 *pTarget;
    u16 nAngle;
    struct ActorNode *pNode;

    nRet = 0;
    if (pActor->nInterruptCharge < CHARGE_MIN) {
        pActor->nInterruptCharge = CHARGE_MIN;
    }
    if (func_020358f4(pActor->nId, RULE_EFFECT) != 0 && (int)pActor->nStateTimer < TIME_EFFECT) {
        vecOffset.x = 0;
        vecOffset.z = EFFECT_UP;
        vecOffset.y = EFFECT_UP;
        func_ov022_020ad62c(pActor, &vecOffset, &place, &request);
        place.nScaleX = EFFECT_SCALE;
        request.nFlags |= REQUEST_FLAG0;
        if (func_ov022_020a0fb8(pActor, &place, &request) != 0
            && (pActor->contact.nResult & CONTACT_NO_AIM) == 0) {
            func_ov022_0209cf58(pActor, &pActor->contact.vec, &place.vecAt, 0, 1);
        }
    }
    if (pActor->nRecoil < 0) {
        pActor->nRecoil = 0;
    }
    if (func_ov022_020ad114(pActor) != 0 && func_020358f4(pActor->nId, RULE_CHASE) != 0) {
        nReach = pActor->nChaseReach;
        bChase = 1;
        pTarget = func_ov022_020ad0c0(pActor);
        VEC_Subtract(pTarget, &pActor->vecAim, &vecDelta);
        if ((int)pActor->nStateTimer > TIME_CHASE) {
            bChase = 0;
        }
        if (VEC_Mag(&vecDelta) < (int)(((long long)nReach * REACH_UNIT + 0x800) >> 12)) {
            bChase = 0;
        }
        if (bChase) {
            vecDelta.y = 0;
            if (VEC_Mag(&vecDelta) != 0) {
                func_01ff8d18(&vecDelta, &vecDelta);
            }
            func_01ffa724(CHASE_SPEED, &vecDelta, &pActor->vecMotion);
            nAngle = FX_Atan2(-vecDelta.x, -vecDelta.z);
            pNode = pActor->pNode;
            if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
                pNode->nAngle = nAngle + ANGLE_BIAS;
                pNode->nAnimFlags |= ANIM_HOLD;
            }
        } else {
            pActor->vecMotion.z = 0;
            pActor->vecMotion.y = 0;
            pActor->vecMotion.x = 0;
        }
    }
    vecFlat = pActor->vecMotion;
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
    if ((pActor->nFlags2 & FLAG2_BIT1) != 0) {
        pActor->nFlags &= ~FLAG_BIT2;
        func_ov022_02094160(pActor->blkReach);
        nRet = func_ov022_020a35f4(pActor, STATE_END);
    }
    return nRet;
}
