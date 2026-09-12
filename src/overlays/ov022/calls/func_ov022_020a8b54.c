/* Ov022_StepLungeState -- run one frame of the lunge state: hold the pose,
 * let a button press launch a decaying lunge along the facing, and decide
 * whether the state is over.
 *
 * The local player raises flag-2 bit 9 every frame; once the animation frame
 * reaches its entry limit (0209d7a4) it also raises flag-2 bit 32 and flag-3
 * bit 32. Under slot rule 0x19: without flag bit 40, button-2 bit 11 past
 * frame 0x3000 arms a lunge of 0x1200 and raises flag bit 40; with it, while
 * the lunge is left, the move is the facing (node angle less the bias) at the
 * frame's speed (0x900 in mode 1, 0x600 otherwise, capped by what is left),
 * scaled by the inverse anchor scale when that is not one. The flat move is
 * added to the step. Without input bit 2 the state ends into state 2: flag
 * bit 32 drops, the move becomes the motion, the recoil is 0x300 or 0x200 by
 * the recoil pick, flag-2 bit 9 drops and the drift is cleared unless flag
 * bit 4 or 13 is up. The state's own post-draw step runs; flag-2 bit 26 (kept
 * in flag-3) or frame 0x9000 (dropping flag-2 bit 9) ends into state 0xc.
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
    u8 pad00[0x80];
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
    u8 pad005c[0x3fc];
    int nAnchorScale;            /* 0x0458 */
    u8 pad045c[8];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[8];
    VecFx32 vecDrift;            /* 0x047c */
    u8 pad0488[0x10];
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0x1c4];
    PostDrawFn pfnPostDraw;      /* 0x0668 */
    u8 pad066c[0x2c];
    VecFx32 vecMotion;           /* 0x0698 */
    u8 pad06a4[0xc];
    int nLungeLeft;              /* 0x06b0 */
    u8 pad06b4[0xfc];
    int nAnimFrame;              /* 0x07b0 */
};

#define FLAG_BIT4 (1ULL << 4)
#define FLAG_BIT13 (1ULL << 13)
#define FLAG_BIT32 (1ULL << 32)
#define FLAG_BIT40 (1ULL << 40)
#define FLAG2_BIT9 (1ULL << 9)
#define FLAG2_BIT26 (1ULL << 26)
#define FLAG2_BIT32 (1ULL << 32)
#define FLAG3_BIT26 (1ULL << 26)
#define FLAG3_BIT32 (1ULL << 32)
#define BUTTON2_BIT11 0x800
#define INPUT_BIT2 0x4
#define RULE_LUNGE 0x19
#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4
#define FX32_ONE 0x1000
#define FRAME_ARM 0x3000
#define FRAME_END 0x9000
#define LUNGE_TOTAL 0x1200
#define LUNGE_FAST 0x900
#define LUNGE_SLOW 0x600
#define RECOIL_FAST 0x300
#define RECOIL_SLOW 0x200
#define STATE_END 2
#define STATE_NEXT 0xc

extern const short data_0203d210[];               /* sin, cos pairs by angle >> 4 */
extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick: picks the fast recoil and rates */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_ov022_0209d7a4(struct Actor *pActor);                           /* Ov022_IsAnimPastEntry */
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_02023c40(void);                                                 /* LoadGlobalU8_0204c058 */
extern int FX_Inv(int nNum, int nDen);
extern void func_01ffa724(int nFactor, VecFx32 *pSrc, VecFx32 *pDst);          /* ScaleVec3Fx12 */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);              /* Ov022_ActorSetState */

int func_ov022_020a8b54(struct Actor *pActor)
{
    VecFx32 vecMove;
    VecFx32 vecFlat;
    int nRet;
    int nSpeed;
    int nLeft;
    u16 nAngle;
    int nTrig;

    nRet = 0;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT9;
    }
    vecMove.z = 0;
    vecMove.y = 0;
    vecMove.x = 0;
    if (func_ov022_0209d7a4(pActor) != 0) {
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT32;
        }
        if (func_02030788() == 0) {
            pActor->nFlags3 |= FLAG3_BIT32;
        }
    }
    if (func_020358f4(pActor->nId, RULE_LUNGE) != 0) {
        if ((pActor->nFlags & FLAG_BIT40) == 0) {
            if (pActor->nAnimFrame >= FRAME_ARM && (pActor->nButtons2 & BUTTON2_BIT11) != 0) {
                pActor->nLungeLeft = LUNGE_TOTAL;
                pActor->nFlags |= FLAG_BIT40;
            }
        } else if (pActor->nLungeLeft > 0) {
            nAngle = pActor->pNode->nAngle - ANGLE_BIAS;
            nTrig = (nAngle >> ANGLE_STEP) * 2;
            vecMove.x = -data_0203d210[nTrig];
            vecMove.y = 0;
            vecMove.z = -data_0203d210[nTrig + 1];
            nSpeed = func_02023c40() == 1 ? LUNGE_FAST : LUNGE_SLOW;
            nLeft = pActor->nLungeLeft;
            if (nSpeed > nLeft) {
                pActor->nLungeLeft = 0;
                nSpeed = nLeft;
            } else {
                pActor->nLungeLeft = nLeft - nSpeed;
            }
            if (pActor->nAnchorScale != FX32_ONE) {
                nSpeed = (int)(((long long)nSpeed * FX_Inv(FX32_ONE, pActor->nAnchorScale) + 0x800) >> 12);
            }
            func_01ffa724(nSpeed, &vecMove, &vecMove);
        }
    }
    vecFlat = vecMove;
    vecFlat.y = 0;
    VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
    if ((pActor->nInputMask & INPUT_BIT2) == 0) {
        pActor->nFlags &= ~FLAG_BIT32;
        pActor->vecMotion.x = vecMove.x;
        pActor->vecMotion.z = vecMove.z;
        pActor->nRecoil = data_ov022_020b2eb0 ? RECOIL_FAST : RECOIL_SLOW;
        nRet = func_ov022_020a35f4(pActor, STATE_END);
        pActor->nFlags2 &= ~FLAG2_BIT9;
        if ((pActor->nFlags & FLAG_BIT4) == 0 && (pActor->nFlags & FLAG_BIT13) == 0) {
            pActor->vecDrift.z = 0;
            pActor->vecDrift.y = 0;
            pActor->vecDrift.x = 0;
        }
    }
    pActor->pfnPostDraw(pActor);
    if ((pActor->nFlags2 & FLAG2_BIT26) != 0) {
        pActor->nFlags3 |= FLAG3_BIT26;
        nRet = func_ov022_020a35f4(pActor, STATE_NEXT);
    } else if (pActor->nAnimFrame >= FRAME_END) {
        pActor->nFlags2 &= ~FLAG2_BIT9;
        nRet = func_ov022_020a35f4(pActor, STATE_NEXT);
    }
    return nRet;
}
