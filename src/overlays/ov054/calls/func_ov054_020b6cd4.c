/* Ov054_StepRiseState -- one frame of this boss's state 0x21 (the entry
 * dispatcher 020b3824 hands it back for message 0x21).
 *
 * The local player raises flag-2 bit 16 and flag-3 bit 16. With a valid
 * target the node turns to face it (flat direction, normalised, half a
 * turn away). The anchor delta drives the step: a vertical part becomes
 * the recoil, otherwise without input bit 2 flag bit 46 goes up and the
 * recoil is cleared; the flat part is added to the step vector. The
 * post-draw hook decides whether the animation is over. While the phase
 * mode is 0 and the boss is of kind 5, 6 or 1, its height picks the next
 * mode: outside 18.0..24.0 mode 1, inside it mode 2 with a network record
 * (kind 5) at the marked point in front of the boss; in any other mode the
 * animation counts as over from frame 33.0. In mode 0 an over animation
 * with the phase's hold flag set is restarted at 33.0 and flag bit 29 is
 * raised. Once over: mode 0 clears the step and motion vectors, raises
 * flag bit 2 and ends into state 0 through the pre-draw hook under input
 * bit 2 or into state 2 without it; any other mode ends into state 0x22.
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
    u8 pad0008[0x14];
    u16 nKind;                   /* 0x001c */
    u8 pad001e[2];
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
    u8 pad04a4[0x1c0];
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
};

/* the boss phase block at +0x2ca4 of the boss context */
struct BossPhase {
    u8 pad000[8];
    int nMode;                   /* 0x008 (0x2cac) */
    u8 pad00c[4];
    int bHold;                   /* 0x010 (0x2cb4) */
    u8 pad014[0x108];
    int nHeight;                 /* 0x11c (0x2dc0) */
    VecFx32 vecMark;             /* 0x120 (0x2dc8) */
};

struct BossCtx {
    u8 pad0000[0x2ca4];
    struct BossPhase phase;      /* 0x2ca4 */
};

#define FLAG_BIT2 (1ULL << 2)
#define FLAG_BIT29 (1ULL << 29)
#define FLAG_BIT46 (1ULL << 46)
#define FLAG2_BIT16 (1ULL << 16)
#define FLAG3_BIT16 (1ULL << 16)
#define INPUT_BIT2 0x4
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define KIND_A 5
#define KIND_B 6
#define KIND_C 1
#define HEIGHT_LOW 0x12000
#define HEIGHT_HIGH 0x18000
#define FRAME_END 0x21000
#define MODE_NONE 0
#define MODE_LOW 1
#define MODE_MARK 2
#define RECORD_MARK 5
#define PREDRAW_IDLE 0
#define STATE_IDLE 0
#define STATE_END 2
#define STATE_NEXT 0x22

extern struct BossCtx *data_ov054_020b74a0;                                    /* gpOv054Boss */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_ov022_020ad114(struct Actor *pActor);                           /* Ov022_ValidateTargetRef */
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);                      /* Ov022_GetTargetPos */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);                        /* VEC_Normalize */
extern int FX_Atan2(int y, int x);
extern void func_ov022_0209fe20(struct Actor *pActor, VecFx32 *pOut);           /* Ov022_StepAnchorDelta */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern VecFx32 func_ov054_020b648c(struct Actor *pActor);                       /* Ov054_GetMarkPoint */
extern void func_ov022_020ad208(struct Actor *pActor, int nRecord, VecFx32 *pAt, int nScale, int nAngle, int nKind);   /* Ov022_MarshalNetworkRecord */
extern void func_01fff774(u16 *pAnimFlags, int nIndex, int nFrame);             /* Anim_SetFrameWrapped */
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);               /* Ov022_ActorSetState */

int func_ov054_020b6cd4(struct Actor *pActor)
{
    VecFx32 vecDelta;
    VecFx32 vecStep;
    VecFx32 vecMark;
    VecFx32 vecFlat;
    struct BossPhase *pPhase;
    int nRet;
    VecFx32 *pTarget;
    u16 nAngle;
    struct ActorNode *pNode;
    int nKind;

    pPhase = &data_ov054_020b74a0->phase;
    nRet = 0;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT16;
    }
    if (func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT16;
    }
    if (func_ov022_020ad114(pActor) != 0) {
        pTarget = func_ov022_020ad0c0(pActor);
        VEC_Subtract(pTarget, &pActor->vecAim, &vecDelta);
        vecDelta.y = 0;
        if (VEC_Mag(&vecDelta) != 0) {
            func_01ff8d18(&vecDelta, &vecDelta);
        }
        nAngle = (u16)FX_Atan2(-vecDelta.x, -vecDelta.z);
        pNode = pActor->pNode;
        if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
            pNode->nAngle = nAngle + ANGLE_BIAS;
            pNode->nAnimFlags |= ANIM_HOLD;
        }
    }
    vecStep.y = 0;
    vecStep.z = 0;
    vecStep.x = 0;
    func_ov022_0209fe20(pActor, &vecStep);
    if (vecStep.y != 0) {
        pActor->nRecoil = vecStep.y;
    } else if ((pActor->nInputMask & INPUT_BIT2) == 0) {
        pActor->nFlags |= FLAG_BIT46;
        pActor->nRecoil = 0;
    }
    vecFlat = vecStep;
    vecFlat.y = 0;
    VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
    pActor->bStateOver = pActor->pfnPostDraw(pActor);
    if (pPhase->nMode == MODE_NONE) {
        nKind = pActor->nKind;
        if (nKind == KIND_A || nKind == KIND_B || nKind == KIND_C) {
            if (pPhase->nHeight >= HEIGHT_LOW && pPhase->nHeight <= HEIGHT_HIGH) {
                pPhase->nMode = MODE_MARK;
                vecMark = func_ov054_020b648c(pActor);
                func_ov022_020ad208(pActor, RECORD_MARK, &vecMark, 0x1000, (u16)(pActor->pNode->nAngle - ANGLE_BIAS), 0);
            } else {
                pPhase->nMode = MODE_LOW;
            }
        }
    } else if (pActor->nAnimFrame >= FRAME_END) {
        pActor->bStateOver = 1;
    }
    if (pPhase->nMode == MODE_NONE) {
        if (pActor->bStateOver != 0 && pPhase->bHold != 0) {
            pActor->bStateOver = 0;
            func_01fff774(&pActor->pNode->nAnimFlags, 0, FRAME_END);
            pActor->nAnimFrame = FRAME_END;
            pActor->nFlags |= FLAG_BIT29;
        }
    }
    if (pActor->bStateOver != 0) {
        if (pPhase->nMode != MODE_NONE) {
            nRet = func_ov022_020a35f4(pActor, STATE_NEXT);
        } else {
            pActor->vecStep.x = pActor->vecStep.y = pActor->vecStep.z = 0;
            pActor->vecMotion.x = pActor->vecMotion.y = pActor->vecMotion.z = 0;
            pActor->nFlags |= FLAG_BIT2;
            if ((pActor->nInputMask & INPUT_BIT2) != 0) {
                pActor->pfnPreDraw(pActor, PREDRAW_IDLE);
                nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
            } else {
                nRet = func_ov022_020a35f4(pActor, STATE_END);
            }
        }
    }
    return nRet;
}
