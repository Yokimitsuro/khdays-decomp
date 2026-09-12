/* Ov022_StepAimJumpState -- one step of state 0xd, the aimed hop.
 *
 * The local player raises flags2 bit 11. On the first frame the jump count
 * goes up and the launch is built: the aim angle plus the angle bias (or
 * the node's facing without an aim) gives a flat push of 0xa00 (0xf00 in
 * mode 1) along the facing, the node turns to it, flags2 bit 54 goes up for
 * the local player and the reaction block copies its word. Later frames
 * take the velocity, normalised to the same speed, with a rise of 1/32
 * decayed by three quarters per extra jump. Without input bit 2 the recoil
 * takes the rise (unless flag bit 10), the node's 0x148 is set to 0xd00
 * and the flat launch is added to the step. Under rule 0x26 during anim
 * 0x13 an effect is requested at (0, rule 0x25 * 0x66, rule 0x25 * 0x133)
 * and, when taken and the contact allows, the aim is sent to it. Rule 0x24
 * with the combo block ready and button 0x800 goes straight to state 6 as
 * an aimed jump (flag bits 35 and 46, step rate 0xd00, move rate * 0.1).
 * Otherwise the post hook decides whether the state is over (flag bit 49,
 * animation poked, end request for the local player), and past 3.0 or
 * with input bits 2 or 7 the hop lands: input bit 2 ends into state 0x16;
 * else the motion takes 1/6.4 of the launch, the recoil its rise, input bit
 * 7 drops, and a ready combo block with button 0x800, an aim angle and the
 * reaction block in range 1 chains an aimed jump (state 6, step rate from
 * the jump rate, 1.5x in mode 1), anything else ending into state 2.
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
    int nField148;               /* 0x148 */
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
    u8 pad18[0x9c];
};

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
    VecFx32 vecVel;              /* 0x0028 */
    u8 pad0034[0x24];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0xc];
    short nAngleBias;            /* 0x0478 */
    u8 pad047a[0x1e];
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0xc];
    int nMoveRate;               /* 0x04b0 */
    u8 pad04b4[9];
    u8 bAimedJump;               /* 0x04bd */
    u8 pad04be[0xe];
    u32 nStateTimer;             /* 0x04cc */
    u8 pad04d0[0x198];
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
    int nAnimId;                 /* 0x06bc */
    u8 pad06c0[0xad8];
    u8 reactBlk[0x180];          /* 0x1198 */
    u8 comboBlk[0x962];          /* 0x1318 (0x974 long; nJumpRate sits inside it) */
    short nJumpRate;             /* 0x1c7a */
    u8 pad1c7c[0xa40];
    struct SweepContact contact; /* 0x26bc */
    u8 pad2770[0x34c];
    int nAimAngle;               /* 0x2abc */
    u8 pad2ac0[0xf0];
    u8 nJumpCount;               /* 0x2bb0 */
};

#define FLAG_BIT10 (1ULL << 10)
#define FLAG_BIT35 (1ULL << 35)
#define FLAG_BIT46 (1ULL << 46)
#define FLAG_BIT49 (1ULL << 49)
#define FLAG2_BIT1 (1ULL << 1)
#define FLAG2_BIT11 (1ULL << 11)
#define FLAG2_BIT54 (1ULL << 54)
#define INPUT_BIT2 0x4
#define INPUT_BIT7 0x80
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define NO_AIM (-1)
#define BUTTON_JUMP 0x800
#define CONTACT_NO_AIM 0x40
#define SPEED_FAST 0xf00
#define SPEED_SLOW 0xa00
#define RISE 0x80
#define NODE_VALUE_148 0xd00
#define ANIM_HOP 0x13
#define RULE_EFFECT 0x26
#define RULE_EFFECT_SIZE 0x25
#define RULE_JUMP 0x24
#define EFFECT_UP 0x66
#define EFFECT_BACK 0x133
#define STEP_RATE_JUMP 0xd00
#define MOVE_RATE_SHARE 0x19a
#define TIME_LAND 0x3000
#define LAND_SHARE 0x280
#define STATE_END 2
#define STATE_JUMP 6
#define STATE_LAND 0x16

extern short data_0203d210[];               /* kFxSinCosTable: sin, cos pairs */

extern int func_02023c40(void);                                                 /* LoadGlobalU8_0204c058 */
extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern void func_ov022_02092b54(u8 *pBlk);                                      /* ov022_CopyWord17cTo170 */
extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);                        /* VEC_Normalize */
extern void func_01ffa724(int nFactor, VecFx32 *pSrc, VecFx32 *pDst);          /* ScaleVec3Fx12 */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern void func_ov022_020ad62c(struct Actor *pActor, VecFx32 *pAt, struct EffectPlace *pPlace,
                                struct EffectRequest *pRequest);                /* Ov022_FillEffectBlocks */
extern int func_ov022_020a0fb8(struct Actor *pActor, struct EffectPlace *pPlace,
                               struct EffectRequest *pRequest);                 /* Ov022_RunCommandHandlers */
extern void func_ov022_0209cf58(struct Actor *pActor, VecFx32 *pFrom, VecFx32 *pTo, int nHeight,
                                int bCheck);                                    /* Ov022_SendAimAtTarget */
extern int func_ov022_02093008(u8 *pBlk);                                       /* Ov022_IsActiveAndCounterZero */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);              /* Ov022_ActorSetState */
extern void func_0202af1c(u16 *pAnimFlags);                                     /* SceneNode_Enable */
extern int func_ov022_02092dc8(u8 *pBlk, int nArg);                             /* CheckState135Range */

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}int func_ov022_020a74d0(struct Actor *pActor)
{
    VecFx32 vecLaunch;
    struct EffectPlace place;
    struct EffectRequest request;
    VecFx32 vecOffset;
    VecFx32 vecFlat;
    int nRet;
    int nSpeed;
    u16 nAngle;
    int nIndex;
    struct ActorNode *pNode;
    int nDecay;
    int i;
    int nSize;
    int nRate;

    nRet = 0;
    nSpeed = func_02023c40() == 1 ? SPEED_FAST : SPEED_SLOW;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT11;
    }
    if (pActor->nStateTimer == 0) {
        pActor->nJumpCount++;
        {
            /* The node angle is read once through a const view before the aim test; the
             * mutable node lookup below is a separate load (a plain read is CSE-folded). */
            const struct Actor *pRead = pActor;
            nAngle = pRead->pNode->nAngle;
        }
        if (pActor->nAimAngle == NO_AIM) {
            nAngle = nAngle - ANGLE_BIAS;
        } else {
            nAngle = pActor->nAimAngle + pActor->nAngleBias;
            pNode = pActor->pNode;
            if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
                pNode->nAngle = nAngle + ANGLE_BIAS;
                pNode->nAnimFlags |= ANIM_HOLD;
            }
        }
        nIndex = nAngle >> 4;
        vecLaunch.x = FxMul(nSpeed, -data_0203d210[nIndex * 2]);
        vecLaunch.y = 0;
        vecLaunch.z = FxMul(nSpeed, -data_0203d210[nIndex * 2 + 1]);
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT54;
        }
        func_ov022_02092b54(pActor->reactBlk);
    } else {
        vecLaunch = pActor->vecVel;
        if (VEC_Mag(&vecLaunch) != 0) {
            func_01ff8d18(&vecLaunch, &vecLaunch);
            func_01ffa724(nSpeed, &vecLaunch, &vecLaunch);
        }
        vecLaunch.y = RISE;
        nDecay = 0x1000;
        for (i = 0; i < pActor->nJumpCount - 1; i++) {
            nDecay = nDecay * 3 / 4;
        }
        vecLaunch.y = FxMul(vecLaunch.y, nDecay);
    }
    if ((pActor->nInputMask & INPUT_BIT2) == 0) {
        if ((pActor->nFlags & FLAG_BIT10) == 0) {
            pActor->nRecoil = vecLaunch.y;
        }
        pActor->pNode->nField148 = NODE_VALUE_148;
        vecFlat = vecLaunch;
        vecFlat.y = 0;
        VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
    }
    if (func_020358f4(pActor->nId, RULE_EFFECT) != 0 && pActor->nAnimId == ANIM_HOP) {
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
    if (func_020358f4(pActor->nId, RULE_JUMP) != 0 && func_ov022_02093008(pActor->comboBlk)
        && (pActor->nButtons2 & BUTTON_JUMP) != 0
        && (nRet = func_ov022_020a35f4(pActor, STATE_JUMP)) != 0) {
        pActor->bAimedJump = 1;
        pActor->nFlags |= FLAG_BIT35;
        pActor->nStepRate = STEP_RATE_JUMP;
        pActor->nMoveRate = FxMul(pActor->nMoveRate, MOVE_RATE_SHARE);
        pActor->nFlags |= FLAG_BIT46;
    } else {
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
        if ((int)pActor->nStateTimer >= TIME_LAND || (pActor->nInputMask & INPUT_BIT2) != 0
            || (pActor->nInputMask & INPUT_BIT7) != 0) {
            if ((pActor->nInputMask & INPUT_BIT2) == 0) {
                func_01ffa724(LAND_SHARE, &vecLaunch, &pActor->vecMotion);
                pActor->vecMotion.y = 0;
                pActor->nRecoil = vecLaunch.y;
                pActor->nInputMask &= ~INPUT_BIT7;
                if (func_ov022_02093008(pActor->comboBlk) && (pActor->nButtons2 & BUTTON_JUMP) != 0
                    && pActor->nAimAngle != NO_AIM && func_ov022_02092dc8(pActor->reactBlk, 1) != 0) {
                    pActor->bAimedJump = 1;
                    if (func_02023c40() == 1) {
                        nRate = pActor->nJumpRate * 3 / 2;
                    } else {
                        nRate = pActor->nJumpRate;
                    }
                    pActor->nStepRate = nRate;
                    nRet = func_ov022_020a35f4(pActor, STATE_JUMP);
                } else {
                    nRet = func_ov022_020a35f4(pActor, STATE_END);
                }
            } else {
                nRet = func_ov022_020a35f4(pActor, STATE_LAND);
            }
        }
    }
    return nRet;
}