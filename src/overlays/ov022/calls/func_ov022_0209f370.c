/* Ov022_StepComboMotion -- turn this frame's anchor delta into the actor's
 * step and recoil under the combo record's rules.
 *
 * Without flag bit 10 the delta is taken from the anchor (marking flag-2 bit
 * 35 for the local player) and shaped by the motion filter, in mode 1 while
 * the combo state is neither open nor closed. The actor counts as held while
 * a phase is picked, the frame is within the record's longest slot, or the
 * state is open.
 *
 * A record with its first flag lets the frame run past its hold plus the
 * global slack only while input bit 2 is down; otherwise the motion is
 * dropped and only the tail runs. A held actor with a vertical delta turns it
 * into recoil (over 1.5 units when the fast pick is on) and raises flag bit
 * 21, unless the record already released; an open state past the record's
 * limit releases it and takes the record's own recoil instead. Under flag bit
 * 36 with flag-2 bit 7 and no hold left, the recoil is cleared again when the
 * motion does not carry the actor up, or the target is not above the aim.
 * The horizontal delta is added to the step; the tail raises flag bit 46 for
 * that same pair and keeps the delta.
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

/* Ov022ComboRecord */
struct ComboRecord {
    u8 pad00[0x1c];
    int nHold;                   /* 0x1c */
    u8 pad20[4];
    int nLimit;                  /* 0x24 negative: no limit */
    int nRecoil;                 /* 0x28 */
    u8 pad2c[0x10];
    u8 bRunOver : 1;             /* 0x3c bit 0: may run past the hold */
    u8 bReleased : 1;            /* 0x3c bit 1: recoil already given */
    u8 nRest3c : 6;
};

/* Ov022ComboLock */
struct ComboLock {
    u8 pad00[0x14];
    struct ComboRecord *pRecord; /* 0x14 */
};

/* Ov022ComboState: the actor's combo block at 0x910 */
struct ComboState {
    u32 nFlags;                  /* 0x000 */
    u8 pad004[0x46c];
    struct ComboLock *pComboLock;/* 0x470 */
    u8 pad474[8];
    int nPhase;                  /* 0x47c */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[0x1c];
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x30];
    int nRecoil;                 /* 0x0058 */
    u8 pad005c[0x408];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x20];
    VecFx32 vecAim;              /* 0x048c */
    VecFx32 vecStep;             /* 0x0498 */
    u8 pad04a4[0x1f4];
    VecFx32 vecMotion;           /* 0x0698 */
    u8 pad06a4[0x10c];
    int nAnimFrame;              /* 0x07b0 */
    u8 pad07b4[0x15c];
    struct ComboState combo;     /* 0x0910 */
};

#define FLAG_BIT10 (1ULL << 10)
#define FLAG_BIT21 (1ULL << 21)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT46 (1ULL << 46)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT35 (1ULL << 35)
#define INPUT_BIT2 0x4
#define RECOIL_SPAN 0x1800

extern u8 data_ov022_020b2eb0;              /* gOv022RecoilPick: picks the fast recoil and rates */

extern int func_ov022_020b0b58(struct ComboState *pCombo);
extern int func_02030788(void);
extern void func_ov022_0209fe20(struct Actor *pActor, VecFx32 *pOut);
extern void *func_ov022_020b0e20(struct ComboState *pCombo);
extern void func_ov022_020a5ff4(VecFx32 *pOut, struct Actor *pActor, VecFx32 *pIn, int nMode);
extern int func_ov022_02083f90(void);
extern int FX_Inv(int nNumerator, int nDenominator);
extern int func_ov022_020ad114(struct Actor *pActor);
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);

void func_ov022_0209f370(struct Actor *pActor)
{
    VecFx32 vecDelta;
    VecFx32 vecTarget;
    VecFx32 vecFlat;
    struct ComboRecord *pRecord;
    int bHeld;
    int bInSlots;
    int nLongest;
    int nHold;

    pRecord = pActor->combo.pComboLock->pRecord;
    bHeld = 0;
    bInSlots = 0;
    nLongest = func_ov022_020b0b58(&pActor->combo);
    if (pActor->nAnimFrame <= nLongest) {
        bInSlots = 1;
    }
    vecDelta.z = 0;
    vecDelta.y = 0;
    vecDelta.x = 0;
    if ((pActor->nFlags & FLAG_BIT10) == 0) {
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT35;
        }
        func_ov022_0209fe20(pActor, &vecDelta);
        func_ov022_020a5ff4(&vecDelta, pActor, &vecDelta,
                            func_ov022_020b0e20(&pActor->combo) == 0);
    }
    if (pActor->combo.nPhase != 0) {
        bHeld = 1;
    }
    if (bInSlots) {
        bHeld = 1;
    }
    if (func_ov022_020b0e20(&pActor->combo) != 0) {
        bHeld = 1;
    }
    nHold = pActor->combo.pComboLock->pRecord->nHold;
    if (pRecord->bRunOver) {
        if (pActor->nAnimFrame > nHold + func_ov022_02083f90()) {
            if ((pActor->nInputMask & INPUT_BIT2) == 0 || pRecord->bRunOver != 1) {
                goto done;
            }
        }
    }
    if (bHeld && vecDelta.y != 0) {
        if (!pRecord->bReleased) {
            if (data_ov022_020b2eb0 != 0) {
                vecDelta.y = FX_Inv(vecDelta.y, RECOIL_SPAN);
            }
            pActor->nRecoil = vecDelta.y;
            pActor->nFlags |= FLAG_BIT21;
        }
    }
    if (func_ov022_020b0e20(&pActor->combo) != 0 && !pRecord->bReleased) {
        if (pActor->nAnimFrame >= pRecord->nLimit && pRecord->nLimit >= 0) {
            pRecord->bReleased = 1;
            pActor->nRecoil = pRecord->nRecoil;
            pActor->nFlags |= FLAG_BIT21;
        }
    }
    if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0
        && pActor->combo.pComboLock->pRecord->nHold <= 0) {
        vecTarget.x = 0;
        vecTarget.y = 0;
        vecTarget.z = 0;
        if (func_ov022_020ad114(pActor) != 0) {
            vecTarget = *func_ov022_020ad0c0(pActor);
        }
        if ((!((pActor->nFlags & FLAG_BIT21) != 0 && bHeld) || pRecord->bReleased
             || vecDelta.y <= 0)
            && (vecTarget.y - pActor->vecAim.y >= 0 || vecDelta.y >= 0 || !bHeld
                || pRecord->bReleased)) {
            pActor->nRecoil = 0;
        }
    }
    vecFlat = vecDelta;
    vecFlat.y = 0;
    VEC_Add(&pActor->vecStep, &vecFlat, &pActor->vecStep);
done:
    if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
        pActor->nFlags |= FLAG_BIT46;
    }
    pActor->vecMotion = vecDelta;
}
