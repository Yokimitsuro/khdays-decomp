/* Ov022_ShapeMotionDelta -- bend a step's motion delta towards the combo
 * target.
 *
 * Without a valid target the delta passes through. The flat direction to
 * the target is taken (normalised when it has a length); an actor of ref
 * kind 3 below its target remembers being under it. Until the record's
 * window plus 2.0 (or under flag bit 32) the move rate is set by the recoil
 * pick and the node turned to the target. A record in contact passes the
 * delta through. Otherwise the delta is scaled by the combo's step (mode 0)
 * or chase (mode 1) rate and the current slot's offset, turned by the
 * facing, gives the reach: offset length plus the slot's radius. Inside
 * that reach the scaled delta is turned by the angle between the offset and
 * the target; in mode 1 a record without hold lifts or drops it by 0.09
 * (0.19 while holding a partner, never lifting from underneath) past 0.75
 * of height difference, and without flag bit 22 or being underneath a
 * sixteenth of the rate along the direction is added; then, without a sub
 * hold, a delta that would overshoot the target -- by its own length or
 * by the reach times the chase reach -- loses its flat part. Outside the
 * reach only mode 1 without bit 22 adds the direction share.
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

typedef struct {
    int a[9];
} MtxFx33;

/* Ov022ActorNode */
struct ActorNode {
    u32 nFlags;                  /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad06[0x7a];
    u16 nAngle;                  /* 0x80 */
};

/* the reach part of an Ov022ComboSlot */
struct SlotReach {
    VecFx32 vecOffset;           /* 0x00 */
    int nRadius;                 /* 0x0c */
};

/* Ov022ComboSlot */
struct ComboSlot {
    u8 pad00[0x18];
    struct SlotReach reach;      /* 0x18 */
    u8 pad28[0x20];
};

/* Ov022ComboRecord */
struct ComboRecord {
    u8 pad00[2];
    u8 nContactMode;             /* 0x02 */
    u8 pad03[5];
    int nWindowEnd;              /* 0x08 */
    u8 pad0c[0xc];
    int nSubHold;                /* 0x18 */
    int nHold;                   /* 0x1c */
    u8 nSlotIndex;               /* 0x20 */
    u8 pad21[0x13];
    struct ComboSlot *pSlots;    /* 0x34 */
};

/* Ov022ComboLock */
struct ComboLock {
    u8 pad00[0x14];
    struct ComboRecord *pRecord; /* 0x14 */
};

/* Ov022ComboState */
struct ComboState {
    u8 pad000[0x20];
    short nChaseReach;           /* 0x020 */
    u8 pad022[2];
    short nStepRate;             /* 0x024 */
    short nChaseRate;            /* 0x026 */
    u8 pad028[0x448];
    struct ComboLock *pComboLock;    /* 0x470 */
    u8 pad474[0xc];
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[0x18];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x440];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x20];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x18];
    int nMoveRate;               /* 0x04b0 */
    u8 pad04b4[0x3c];
    u8 nRefKind;                 /* 0x04f0 */
    u8 pad04f1[0x2bf];
    int nAnimFrame;              /* 0x07b0 */
    u8 pad07b4[0x15c];
    struct ComboState combo;     /* 0x0910 */
};

#define FLAG_BIT22 (1ULL << 22)
#define FLAG_BIT32 (1ULL << 32)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG2_BIT7 (1ULL << 7)
#define REF_KIND_UNDER 3
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define WINDOW_SLACK 0x2000
#define RATE_FAST 0x2400
#define RATE_SLOW 0x1800
#define HEIGHT_STEP 0xc00
#define LIFT 0x180
#define DIR_SHARE 0x100
#define MODE_STEP 0

extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick */
extern short data_0203d210[];               /* kFxSinCosTable: sin, cos pairs */

extern int func_ov022_020ad114(struct Actor *pActor);                           /* Ov022_ValidateTargetRef */
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);                      /* Ov022_GetTargetPos */
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);                        /* VEC_Normalize */
extern int FX_Atan2(int y, int x);
extern void func_01ffa724(int nFactor, VecFx32 *pSrc, VecFx32 *pDst);          /* ScaleVec3Fx12 */
extern void MTX_RotY33_(MtxFx33 *pMtx, int nSin, int nCos);                   /* MTX_RotY33_ */
extern void MTX_MultVec33(VecFx32 *pVec, MtxFx33 *pMtx, VecFx32 *pOut);         /* MTX_MultVec33 */
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}/* MWCC 3.0 build 139: preserve the conditional read of the previous flag.
 * Combined with the ternary below, this reproduces the original register
 * allocation without a redundant false-path instruction. Restore the caller's
 * compiler settings after this function.
 */
#pragma push
#pragma opt_propagation off
void func_ov022_020a5ff4(VecFx32 *pOut, struct Actor *pActor, VecFx32 *pIn, int nMode)
{
    VecFx32 vecDir;
    VecFx32 vecTarget;
    VecFx32 vecIn;
    VecFx32 vecOffset;
    VecFx32 vecScaled;
    VecFx32 vecRot;
    MtxFx33 mtx;
    VecFx32 vecOut;
    struct ComboRecord *pRecord;
    struct SlotReach *pReach;
    struct ActorNode *pNode;
    u32 nDist;
    int bUnder;
    int nRate;
    int nReach;
    int nRadius;
    int nIndex;
    int nLimit;
    int nDy;
    int nLift;
    int nExtra;
    u16 nFacing;
    u16 nAngle;
    u16 nAngleRot;
    u16 nAngleDir;

    pRecord = pActor->combo.pComboLock->pRecord;
    vecIn = *pIn;
    bUnder = 0;
    if (func_ov022_020ad114(pActor) == 0) {
        *pOut = vecIn;
        return;
    }
    vecTarget = *func_ov022_020ad0c0(pActor);
    VEC_Subtract(&vecTarget, &pActor->vecAim, &vecDir);
    vecDir.y = 0;
    nDist = VEC_Mag(&vecDir);
    if (VEC_Mag(&vecDir) != 0) {
        func_01ff8d18(&vecDir, &vecDir);
    }
    if (pActor->nRefKind == REF_KIND_UNDER) {
        bUnder = vecDir.y > 0 ? 1 : bUnder;
    }
    if (pActor->combo.pComboLock->pRecord->nWindowEnd + WINDOW_SLACK >= pActor->nAnimFrame
        || (pActor->nFlags & FLAG_BIT32) != 0) {
        pActor->nMoveRate = data_ov022_020b2eb0 ? RATE_FAST : RATE_SLOW;
        nAngle = FX_Atan2(-vecDir.x, -vecDir.z);
        pNode = pActor->pNode;
        if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
            pNode->nAngle = nAngle + ANGLE_BIAS;
            pNode->nAnimFlags |= ANIM_HOLD;
        }
    }
    nFacing = pActor->pNode->nAngle - ANGLE_BIAS;
    if (pRecord->nContactMode != 0) {
        *pOut = vecIn;
        return;
    }
    pReach = &pRecord->pSlots[pRecord->nSlotIndex].reach;
    nReach = pActor->combo.nChaseReach;
    nRate = nMode == MODE_STEP ? pActor->combo.nStepRate : pActor->combo.nChaseRate;
    vecScaled = *pIn;
    func_01ffa724(nRate, &vecScaled, &vecScaled);
    nIndex = nFacing >> 4;
    vecOut = vecScaled;
    vecOffset = pReach->vecOffset;
    nRadius = pReach->nRadius;
    MTX_RotY33_(&mtx, -data_0203d210[nIndex * 2], -data_0203d210[nIndex * 2 + 1]);
    MTX_MultVec33(&vecOffset, &mtx, &vecRot);
    vecRot.y = 0;
    nRadius += VEC_Mag(&vecRot);
    if (nRadius > (int)nDist) {
        nAngleRot = FX_Atan2(-vecRot.x, -vecRot.z);
        nAngleDir = FX_Atan2(-vecDir.x, -vecDir.z);
        nIndex = (u16)(nAngleDir - nAngleRot) >> 4;
        MTX_RotY33_(&mtx, data_0203d210[nIndex * 2], data_0203d210[nIndex * 2 + 1]);
        MTX_MultVec33(&vecScaled, &mtx, &vecScaled);
        if (nMode != MODE_STEP && pActor->combo.pComboLock->pRecord->nHold == 0) {
            nDy = vecTarget.y - (pActor->vecAim.y + HEIGHT_STEP + vecScaled.y);
            nLift = 0;
            nExtra = LIFT;
            if ((pActor->nFlags & FLAG_BIT36) == 0 || (pActor->nFlags2 & FLAG2_BIT7) == 0) {
                nExtra = 0;
            }
            if (nDy > HEIGHT_STEP) {
                if (bUnder == 0) {
                    nLift = nExtra + LIFT;
                }
            } else if (nDy < -HEIGHT_STEP) {
                nLift = -(nExtra + LIFT);
            }
            vecScaled.y += nLift;
        }
        if (nMode != MODE_STEP && (pActor->nFlags & FLAG_BIT22) == 0 && bUnder == 0) {
            func_01ffa724(FxMul(nRate, DIR_SHARE), &vecDir, &vecDir);
            VEC_Add(&vecDir, &vecScaled, &vecScaled);
        }
        nLimit = FxMul(nRadius, nReach);
        vecOut = vecScaled;
        if (pRecord->nSubHold == 0) {
            if (VEC_Mag(&vecScaled) > (int)nDist || nLimit > (int)nDist) {
                vecOut.z = 0;
                vecOut.x = 0;
            }
        }
    } else if (nMode != MODE_STEP && (pActor->nFlags & FLAG_BIT22) == 0) {
        if (bUnder == 0) {
            func_01ffa724(FxMul(nRate, DIR_SHARE), &vecDir, &vecDir);
            VEC_Add(&vecDir, &vecScaled, &vecScaled);
        }
        vecOut = vecScaled;
    }
    *pOut = vecOut;
}
#pragma pop
