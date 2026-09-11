/* Ov022_ApplyReactionHit -- deal the hit a reaction slot carries, by kind.
 *
 * Nothing happens unless the session is ready. Kind 0xc hits the actor itself:
 * the actor's level value plus 0x10, scaled by 0.6 and by the slot's power,
 * goes through the damage helper if the actor still has HP, and bit 40 of its
 * third flag word is raised. Kind 0xd arms the actor's damage-over-time record
 * instead: per-tick damage from the level value plus 0x1a scaled by 0.7 and the
 * power, the slot's repeat as the starting scale (kept twice), its repeat
 * maximum as the scale step, its homing delay as the period, its next power as
 * the duration, and a cleared carry. Kind 0xe hits every entry of the actor's
 * slot within the slot's radius of the aim point, with the level value plus
 * 0x1a scaled by 0.5 and the power, raising the same flag bit on each.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned long long u64;
typedef long long s64;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* the damage-over-time record after the actor body */
struct DotRecord {
    int nTimer;                      /* 0x00 */
    int nRemaining;                  /* 0x04 */
    int nPeriod;                     /* 0x08 */
    int nDamage;                     /* 0x0c */
    int nScale;                      /* 0x10 */
    int nScaleStep;                  /* 0x14 */
    int nScaleStart;                 /* 0x18 */
    u16 nCarry;                      /* 0x1c */
    u8 pad1e[2];
};

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x12];
    u16 nHp;                         /* 0x0012 */
    u8 pad0014[0x458];
    u64 nFlags3;                     /* 0x046c */
    u8 pad0474[0x278c];
    struct DotRecord dot;            /* 0x2c00 */
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 nKind;                        /* 0x000 */
    u8 pad001[0xab];
    struct VecFx32 vecAim;           /* 0x0ac */
    u8 pad0b8[0x58];
    s8 nSlotIndex;                   /* 0x110 */
    u8 pad111[0xf];
    int nPower;                      /* 0x120 */
    int nRadius;                     /* 0x124 */
    u8 pad128[0x10];
    int nRepeat;                     /* 0x138 */
    int nRepeatMax;                  /* 0x13c */
    int nHomingDelay;                /* 0x140 */
    int nPowerNext;                  /* 0x144 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0x58];
    struct Actor *pActor;            /* 0x58 */
};

#define KIND_SELF 0xc
#define KIND_DOT 0xd
#define KIND_AREA 0xe
#define FX32_ONE 0x1000
#define FX32_SHIFT 12
#define ACTION_LEVEL 0xc
#define SELF_BASE 0x10
#define HIT_BASE 0x1a
#define SELF_SCALE 0x99a
#define DOT_SCALE 0xb33
#define AREA_SCALE 0x800
#define FLAG3_HIT (1ULL << 40)

extern int func_02030694(void);
extern int func_ov022_020a216c(struct Actor *pActor, int nScale, int nActionLevel);
extern void func_ov022_020ace24(struct Actor *pActor, int nDamage, int nMode);
extern int func_ov022_020882f8(void);
extern int func_ov022_02088474(int nOwner);
extern struct VecFx32 *func_ov022_020881f8(int nOwner);
extern struct Actor *func_01fffde0(int nOwner);
extern void VEC_Subtract(struct VecFx32 *a, struct VecFx32 *b,
                         struct VecFx32 *pOut);
extern int VEC_Mag(struct VecFx32 *pVec);

static inline int FxMul(int nScale, int nValue)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

void func_ov022_0208fb34(struct ReactionCtx *pCtx, struct ActorSlot *pSlot)
{
    struct VecFx32 vecAim;
    struct VecFx32 vecDelta;
    struct Actor *pActor;
    int bArea;
    int nOwner;
    struct Actor *pTarget;
    int nDamage;
    struct DotRecord *pDot;
    int nScale;
    int nBase;

    pActor = pCtx->pActor;
    bArea = 0;
    if (func_02030694() == 0) {
        return;
    }
    vecAim = pSlot->vecAim;
    switch (pSlot->nKind) {
    case KIND_SELF:
        if (pActor->nHp != 0) {
            nBase = func_ov022_020a216c(pActor, FX32_ONE, ACTION_LEVEL) + SELF_BASE;
            func_ov022_020ace24(pActor,
                                FxMul(pSlot->nPower, nBase * SELF_SCALE) >> FX32_SHIFT,
                                0);
        }
        pActor->nFlags3 |= FLAG3_HIT;
        break;
    case KIND_DOT:
        pDot = &pActor->dot;
        nBase = func_ov022_020a216c(pActor, FX32_ONE, ACTION_LEVEL) + HIT_BASE;
        pDot->nDamage = FxMul(pSlot->nPower, nBase * DOT_SCALE) >> FX32_SHIFT;
        nScale = pSlot->nRepeat;
        pDot->nScaleStart = nScale;
        pDot->nScale = nScale;
        pDot->nScaleStep = pSlot->nRepeatMax;
        pDot->nPeriod = pSlot->nHomingDelay;
        pDot->nRemaining = pSlot->nPowerNext;
        pDot->nCarry = 0;
        break;
    case KIND_AREA:
        bArea = 1;
        break;
    }
    if (bArea == 0) {
        return;
    }
    nBase = func_ov022_020a216c(pActor, FX32_ONE, ACTION_LEVEL) + HIT_BASE;
    nDamage = FxMul(pSlot->nPower, nBase * AREA_SCALE) >> FX32_SHIFT;
    nOwner = 0;
    if (func_ov022_020882f8() <= 0) {
        return;
    }
    do {
        if (pSlot->nSlotIndex == func_ov022_02088474(nOwner)) {
            VEC_Subtract(func_ov022_020881f8(nOwner), &vecAim, &vecDelta);
            if (VEC_Mag(&vecDelta) <= pSlot->nRadius) {
                pTarget = func_01fffde0(nOwner);
                if (pTarget->nHp != 0) {
                    func_ov022_020ace24(pTarget, nDamage, 0);
                }
                pTarget->nFlags3 |= FLAG3_HIT;
            }
        }
        nOwner++;
    } while (nOwner < func_ov022_020882f8());
}
