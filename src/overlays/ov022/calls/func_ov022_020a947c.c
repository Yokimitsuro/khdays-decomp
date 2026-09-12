/* Ov022_StepDodgeRollState -- one step of state 8, the dodge roll.
 *
 * The local player raises flags2 bit 14. Without input bit 2 the roll ends
 * into state 2. Otherwise, at the first frame with an aim angle, the node
 * turns to the aim plus the angle bias. The anchor delta scaled by the
 * follow speed becomes the flat step. Under slot rule 0x11, while the
 * state time is at most 9.0, an effect is requested at (0, rule 0x10 *
 * 0.05, rule 0x10 * 0.1) and, when a handler takes it and the contact
 * result lacks bit 6, the aim is sent from the impact point to the
 * effect's place. The post hook decides whether the state is over. Holding
 * button 0x800 with an aim past frame 9.0 chains another roll (flag bit 3):
 * a chained roll is over at frame 15.0; a plain one may cancel into a
 * pending action from frame 12.0 under rule 0x13 (flags2 bit 36 while it is
 * tried, unless rule 0x27 with a valid ref, local player only) and is over
 * at frame 18.0. When over: flag bit 49, the animation poked and the end
 * request raised by the local player. The end request either restarts the
 * roll (state 8, flags2 bit 31, frame and state time reset) for a chained
 * roll or runs the pre hook and ends into state 0; flag bit 3 drops.
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
typedef void (*PreDrawFn)(struct Actor *pActor, int nArg);

/* Ov022SweepContact */
struct SweepContact {
    u32 nResult;                 /* 0x00 */
    int nKind;                   /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 pad09[3];
    VecFx32 vec;                 /* 0x0c */
    u8 pad18[0x9c];
};

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
    u8 pad0028[0x43c];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0xc];
    short nAngleBias;            /* 0x0478 */
    u8 pad047a[0x1e];
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0x28];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0x194];
    PreDrawFn pfnPreDraw;        /* 0x0664 */
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x28];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nFlags694Rest : 6;
    u8 pad0695[0x11b];
    int nAnimFrame;              /* 0x07b0 */
    u8 pad07b4[0x9dc];
    short nFollowSpeed;          /* 0x1190 */
    u8 pad1192[0x152a];
    struct SweepContact contact; /* 0x26bc */
    u8 pad2770[0x34c];
    int nAimAngle;               /* 0x2abc */
};

#define FLAG_BIT3 (1ULL << 3)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT1 (1ULL << 1)
#define FLAG2_BIT14 (1ULL << 14)
#define FLAG2_BIT31 (1ULL << 31)
#define FLAG2_BIT36 (1ULL << 36)
#define INPUT_BIT2 0x4
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define NO_AIM (-1)
#define CONTACT_NO_AIM 0x40
#define BUTTON_ROLL 0x800
#define RULE_EFFECT 0x11
#define RULE_EFFECT_SIZE 0x10
#define RULE_CANCEL 0x13
#define RULE_NO_CANCEL_REF 0x27
#define TIME_EFFECT 0x9000
#define FRAME_CHAIN 0x9000
#define FRAME_CANCEL 0xc000
#define FRAME_CHAIN_OVER 0xf000
#define FRAME_OVER 0x12000
#define EFFECT_UP 0xcd
#define EFFECT_BACK 0x19a
#define STATE_IDLE 0
#define STATE_END 2
#define STATE_ROLL 8

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);              /* Ov022_ActorSetState */
extern void func_ov022_0209fe20(struct Actor *pActor, VecFx32 *pOut);           /* Ov022_StepAnchorDelta */
extern void func_01ffa724(int nFactor, VecFx32 *pSrc, VecFx32 *pDst);          /* ScaleVec3Fx12 */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern void func_ov022_020ad62c(struct Actor *pActor, VecFx32 *pAt, struct EffectPlace *pPlace,
                                struct EffectRequest *pRequest);                /* Ov022_FillEffectBlocks */
extern int func_ov022_020a0fb8(struct Actor *pActor, struct EffectPlace *pPlace,
                               struct EffectRequest *pRequest);                 /* Ov022_RunCommandHandlers */
extern void func_ov022_0209cf58(struct Actor *pActor, VecFx32 *pFrom, VecFx32 *pTo, int nHeight,
                                int bCheck);                                    /* Ov022_SendAimAtTarget */
extern int func_ov022_020ad1b4(struct Actor *pActor);                           /* GetField4f4UnlessState5 */
extern int func_ov022_020983ec(struct Actor *pActor, int nArg);                 /* Ov022_TryPendingAction */
extern void func_0202af1c(u16 *pAnimFlags);                                     /* SceneNode_Enable */
extern void func_ov022_02097038(struct Actor *pActor, int nFrame);              /* SetField7b0AndDispatch */

int func_ov022_020a947c(struct Actor *pActor)
{
    VecFx32 vecDelta;
    struct EffectPlace place;
    struct EffectRequest request;
    VecFx32 vecOffset;
    VecFx32 vecFlat;
    int nRet;
    int nAim;
    int nSize;
    struct ActorNode *pNode;

    nRet = 0;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT14;
    }
    if ((pActor->nInputMask & INPUT_BIT2) == 0) {
        nRet = func_ov022_020a35f4(pActor, STATE_END);
    } else {
        nAim = pActor->nAimAngle;
        if (nAim != NO_AIM && pActor->nStateTimer == 0) {
            nAim = (u16)(nAim + pActor->nAngleBias);
            pNode = pActor->pNode;
            if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
                pNode->nAngle = nAim + ANGLE_BIAS;
                pNode->nAnimFlags |= ANIM_HOLD;
            }
        }
        func_ov022_0209fe20(pActor, &vecDelta);
        func_01ffa724(pActor->nFollowSpeed, &vecDelta, &vecDelta);
        vecFlat = vecDelta;
        vecFlat.y = 0;
        VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
        if (func_020358f4(pActor->nId, RULE_EFFECT) != 0 && (int)pActor->nStateTimer <= TIME_EFFECT) {
            nSize = func_020358f4(pActor->nId, RULE_EFFECT_SIZE);
            vecOffset.x = 0;
            vecOffset.z = nSize * EFFECT_BACK;
            vecOffset.y = nSize * EFFECT_UP;
            func_ov022_020ad62c(pActor, &vecOffset, &place, &request);
            if (func_ov022_020a0fb8(pActor, &place, &request) != 0
                && (pActor->contact.nResult & CONTACT_NO_AIM) == 0) {
                func_ov022_0209cf58(pActor, &pActor->contact.vec, &place.vecAt, 0, 1);
            }
        }
        pActor->bStateOver = pActor->pfnPostDraw(pActor);
        if ((pActor->nButtons & BUTTON_ROLL) == BUTTON_ROLL && nAim != NO_AIM
            && pActor->nAnimFrame > FRAME_CHAIN) {
            pActor->nFlags |= FLAG_BIT3;
        }
        if ((pActor->nFlags & FLAG_BIT3) != 0) {
            if (pActor->nAnimFrame >= FRAME_CHAIN_OVER) {
                pActor->bStateOver = 1;
            }
        } else {
            if (func_020358f4(pActor->nId, RULE_CANCEL) != 0 && pActor->nAnimFrame >= FRAME_CANCEL) {
                if ((func_020358f4(pActor->nId, RULE_NO_CANCEL_REF) == 0 || func_ov022_020ad1b4(pActor) == 0)
                    && func_02030788() == 0) {
                    pActor->nFlags2 |= FLAG2_BIT36;
                }
                nRet = func_ov022_020983ec(pActor, 0);
                if (nRet != 0) {
                    goto done;
                }
                pActor->nFlags2 &= ~FLAG2_BIT36;
            }
            if (pActor->nAnimFrame >= FRAME_OVER) {
                pActor->bStateOver = 1;
            }
        }
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
            if ((pActor->nFlags & FLAG_BIT3) != 0) {
                if (func_02030788() == 0) {
                    pActor->nFlags2 |= FLAG2_BIT31;
                }
                nRet = func_ov022_020a35f4(pActor, STATE_ROLL);
                func_ov022_02097038(pActor, 0);
                pActor->nStateTimer = 0;
            } else {
                pActor->pfnPreDraw(pActor, 0);
                nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
            }
            pActor->nFlags &= ~FLAG_BIT3;
        }
    }
done:
    return nRet;
}
