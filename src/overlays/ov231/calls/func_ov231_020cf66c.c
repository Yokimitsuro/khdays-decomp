/* func_ov231_020cf66c -- AI curved charge step (byte-identical in ov231 /
 * ov232 / ov263 / ov265 / ov280).  The anchor (+0x4) lifted by 0xd00 is the
 * command point; the velocity (+0x8) is the actor's facing (+0x390) scaled
 * by 0x750 (01ffa724).  Until the progress (+0x20) passes the duration
 * (+0x14) the turn is the actor's turn byte (+0x38c) times cos(progress *
 * pi / duration) * 50 degrees, afterwards -turn * 0x4e8a4 / 90; with a
 * duration the velocity rotates about Y by that angle (sin / cos from the
 * Q12 table at data_0203d210 through the 0x28be60db9391 index, MTX_RotY33_
 * / MTX_MultVec33) and the progress advances by the rotated z of
 * (0, 0, 0x750 / (delta / 0x88)), capped at the duration while below it.
 * The actor's volume (+0x74, 16 bytes) is tested against the world (020c8eb8
 * on +0x388): every hit whose kind bit (+0x2) is new in the hit mask
 * (+0x26) and accepted by 020ca918 (mode 0, the velocity) sets the bit,
 * sends command 0 at the command point (020c0b90) and reaction 6 to the
 * anchor (020c5af8 with +0x24); bits of hits no longer present drop out of
 * the mask.  The velocity's length accumulates in +0x1c; with a contact bit
 * (+0x17a bits 0 / 1) or 0x16000 travelled the charge ends: reaction 7,
 * command 0, the sub-state (+0x1c7) cleared and the slot (signed byte
 * +0x20) released (0203c634 with 0).  Codegen: the node is spilled and the
 * state kept in r6; the angle in fx radians goes through the 64-bit index
 * multiply; the loop counter is a signed char; the command point is passed
 * by value (x / y in r2 / r3, z on the stack); the zero flag of the calls
 * is the loop counter's zero kept in a register; declaration order i,
 * nCount, nMask, nBit.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef short          s16;
typedef int            fx32;

#define FX32_PI      0x3244
#define FX32_DEG50   0xdf6
#define CHARGE_SPEED 0x750
#define CHARGE_LIFT  0xd00
#define CHARGE_RANGE 0x16000
#define CMD_CHARGE   0
#define REACTION_HIT 6
#define REACTION_END 7

typedef struct Vec3 {
    fx32 x;
    fx32 y;
    fx32 z;
} Vec3;

typedef struct Vec4 {
    fx32 a[4];
} Vec4;

typedef struct Mtx33 {
    fx32 m[9];
} Mtx33;

typedef struct ChargeActor {
    u8    pad_000[0x74];
    Vec4  volume;             /* 0x074 */
    u8    pad_084[0x17a - 0x84];
    u8    bGrounded : 1;      /* 0x17a */
    u8    bBlocked : 1;
    u8    pad_17b[0x1c7 - 0x17b];
    u8    nSubState;          /* 0x1c7 */
    u8    pad_1c8[0x388 - 0x1c8];
    int   hWorld;             /* 0x388 */
    signed char nTurn;        /* 0x38c */
    u8    pad_38d[3];
    Vec3  vFacing;            /* 0x390 */
} ChargeActor;

typedef struct HitEntry {
    u8  pad_00[2];
    u16 nKind;                /* 0x02 */
} HitEntry;

typedef struct ChargeState {
    ChargeActor *pSelf;       /* 0x00 */
    Vec3 *pAnchor;            /* 0x04 */
    Vec3  vVel;               /* 0x08 */
    int   nDuration;          /* 0x14 */
    u8    pad_18[4];
    int   nTravel;            /* 0x1c */
    int   nProgress;          /* 0x20 */
    s16   nId;                /* 0x24 */
    u8    nHitMask;           /* 0x26 */
} ChargeState;

typedef struct ChargeNode {
    int  *pClock;             /* 0x00: +0x2c frame delta */
    ChargeState *pState;      /* 0x04 */
    u8    pad_08[0x20 - 8];
    signed char nSlot;        /* 0x20 */
} ChargeNode;

extern short data_0203d210[];                                          /* Q12 sin / cos table */
extern void  func_01ffa724(int nScale, const Vec3 *pSrc, Vec3 *pDst);   /* ScaleVec3Fx12 */
extern long long func_02020400(int nNum, int nDen);                    /* _s32_div_f */
extern void  MTX_RotY33_(Mtx33 *pMtx, fx32 nSin, fx32 nCos);
extern void  MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern int   FX_Inv(int nNumer, int nDenom);                            /* fx32 divide */
extern int   func_ov107_020c8eb8(int hWorld, Vec4 *pVolume, HitEntry **apHit);
extern int   func_ov107_020ca918(HitEntry *pHit, ChargeActor *pSelf, int hWorld, int nMode, Vec3 *pDir, int nFlag);
extern void  func_ov107_020c0b90(int hWorld, int nCmd, Vec3 vAt, int nFlag);
extern void  func_ov107_020c5af8(ChargeActor *pSelf, int nId, int nReaction, Vec3 *pAt);
extern int   VEC_Mag(const Vec3 *pVec);
extern void  func_0203c634(ChargeNode *pNode, int nSlot, void *pValue); /* SetIndexedSlot */

static inline fx32 FX_Mul(fx32 a, fx32 b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

static inline int Ai_AngleIndex(fx32 nAngle)
{
    int idx;

    idx = (int)(((long long)nAngle * 0x28be60db9391LL + (0x800LL << 32)) >> 32);
    return (int)((unsigned)(idx << 4) >> 16) >> 4;
}

void func_ov231_020cf66c(ChargeNode *pNode)
{
    Vec4 volume;
    HitEntry *apHit[4];
    Mtx33 mtx;
    Vec3 vLocal;
    Vec3 vAt;
    ChargeState *pState;
    ChargeActor *pActor;
    fx32 nAngle;
    int nIndex;
    signed char i;
    int nCount;
    u8 nMask;
    u8 nBit;
    int nDuration;

    pState = pNode->pState;
    vAt = *pState->pAnchor;
    vAt.y += CHARGE_LIFT;
    nMask = 0;
    func_01ffa724(CHARGE_SPEED, &pState->pSelf->vFacing, &pState->vVel);
    nDuration = pState->nDuration;
    if (pState->nProgress <= nDuration) {
        nAngle = pState->pSelf->nTurn
               * FX_Mul(data_0203d210[Ai_AngleIndex((int)func_02020400(pState->nProgress * FX32_PI, nDuration)) * 2 + 1], FX32_DEG50);
    } else {
        nAngle = -pState->pSelf->nTurn * 0x4e8a4 / 90;
    }
    if (nDuration != 0) {
        nIndex = Ai_AngleIndex(nAngle);
        MTX_RotY33_(&mtx, data_0203d210[nIndex * 2], data_0203d210[nIndex * 2 + 1]);
        MTX_MultVec33(&pState->vVel, &mtx, &pState->vVel);
        vLocal.z = FX_Mul(FX_Inv(pNode->pClock[0x2c / 4], 0x88), CHARGE_SPEED);
        vLocal.x = 0;
        vLocal.y = 0;
        MTX_MultVec33(&vLocal, &mtx, &vLocal);
        if (pState->nProgress < pState->nDuration) {
            pState->nProgress += vLocal.z;
            if (pState->nProgress > pState->nDuration) {
                pState->nProgress = pState->nDuration;
            }
        } else {
            pState->nProgress += vLocal.z;
        }
    }
    volume = pState->pSelf->volume;
    nCount = func_ov107_020c8eb8(pState->pSelf->hWorld, &volume, apHit);
    for (i = 0; i < nCount; i++) {
        nBit = 1 << apHit[i]->nKind;
        nMask |= nBit;
        if ((pState->nHitMask & nBit) == 0
            && func_ov107_020ca918(apHit[i], pState->pSelf, pState->pSelf->hWorld, 0, &pState->vVel, 0) != 0) {
            pState->nHitMask |= nBit;
            func_ov107_020c0b90(pState->pSelf->hWorld, CMD_CHARGE, vAt, 0);
            func_ov107_020c5af8(pState->pSelf, pState->nId, REACTION_HIT, pState->pAnchor);
        }
    }
    pState->nHitMask &= nMask;
    pState->nTravel += VEC_Mag(&pState->vVel);
    pActor = pState->pSelf;
    if (pActor->bGrounded == 0 && pActor->bBlocked == 0 && pState->nTravel < CHARGE_RANGE) {
        return;
    }
    func_ov107_020c5af8(pState->pSelf, pState->nId, REACTION_END, pState->pAnchor);
    func_ov107_020c0b90(pState->pSelf->hWorld, CMD_CHARGE, vAt, 0);
    pState->pSelf->nSubState = 0;
    func_0203c634(pNode, pNode->nSlot, 0);
}
