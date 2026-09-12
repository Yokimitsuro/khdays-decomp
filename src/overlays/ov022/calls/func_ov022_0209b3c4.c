/* ov022: spend the actor's guard on a hit, or fall through to the reactions.
 *
 * Works out what the hit costs, the same way the opener does, then either
 * charges it or, when nothing is left to charge, runs whichever reaction the
 * actor's current state calls for.
 *
 * A few kinds are special: one restores the previously pending kind and stops
 * there, one is free while the actor is nearly down, and one is free once the
 * charge has already been released. A kind past the end of the table is free
 * too.
 *
 * Charging it records the kind as pending and, for the one kind that ends the
 * exchange, raises a flag in the third word.
 *
 * Levers: as the opener (Ov022_ArmGuardWindow) -- the scale multiply is
 * FX_Mul(0x1000 - (nTrait << 9), nCost) with the scale as the LEFT operand expression,
 * so the trait call's result stays in r0 as the smull multiplier and the product pair
 * is created above it.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define ACTOR_FLAGS2(p) (*(unsigned long long *)(p)->aFlags2)
#define ACTOR_FLAGS3(p) (*(unsigned long long *)(p)->aFlags3)

#define FULL_COST 0x64000
#define TRAIT_FULL 0x5d
#define TRAIT_SCALE 0x5c

struct Request {
    int nFlags;                  /* 0x00 */
    u8 pad04[0x10];
    int nKind;                   /* 0x14 */
    u8 nWeight;                  /* 0x18 */
    u8 pad19[0xb];
    int nFlags2;                 /* 0x24 */
};

struct Charge {
    signed char nPendingKind;    /* 0x00 */
    signed char nPrevKind;       /* 0x01 */
    u8 pad02[2];
    int nMeter;                  /* 0x04 */
    int nSpent;                  /* 0x08 */
    u8 bReleased : 1;            /* 0x0c */
    u8 nRest : 7;
    u8 pad0d[3];
    int nStreak;                 /* 0x10 */
};

struct Actor {
    u32 aFlags[2];               /* 0x0000 */
    u8 pad008;
    u8 nId;                      /* 0x0009 */
    u8 pad00a[8];
    u16 nHealth;                 /* 0x0012 */
    u8 pad014[0x450];
    u32 aFlags2[2];              /* 0x0464 */
    u32 aFlags3[2];              /* 0x046c */
    u8 pad474[0xc];
    int nStagger;                /* 0x0480 */
    u8 pad484[0x1e74];
    u8 cue[4];                   /* 0x22f8 */
    u8 pad22fc[0x474];
    struct Charge charge;        /* 0x2770 */
};

struct TraitTable {
    u8 aTrait[14];
};

extern const struct TraitTable data_ov022_020b25b4;
extern int func_020358f4(int nId, int nTrait);
extern int func_0203581c(int nId, int nKind);
extern int func_0203084c(void);
extern int func_02030788(void);
extern int func_ov022_02095524(u8 *pCue);
extern int func_ov022_0209bd04(struct Actor *pActor);
extern void func_ov022_0209b1e8(struct Actor *pActor);
extern void func_ov022_0209be44(struct Actor *pActor);
extern void func_ov022_020acc94(struct Actor *pActor, int nAmount);
extern void func_ov002_0206df6c(int nId, int nMode);

static inline int FX_Mul(int v1, int v2)
{
    return (int)(((long long)v1 * v2 + 0x800) >> 12);
}

void func_ov022_0209b3c4(struct Actor *pActor, struct Request *pReq, int bFull)
{
    struct TraitTable traits;
    struct Charge *pCharge;
    int nCost;
    int nKind;
    int bLive;
    int bPinned;
    int bAlt;
    int nTrait;
    int nPrev;

    pCharge = &pActor->charge;
    nKind = pReq->nKind;
    nCost = 0;
    bPinned = func_020358f4(pActor->nId, TRAIT_FULL) != 0;
    bLive = 1;
    bAlt = 0;
    if (func_ov022_02095524(pActor->cue) != 0) {
        return;
    }
    if ((ACTOR_FLAGS2(pActor) & 0x10000) != 0) {
        return;
    }
    switch (nKind) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 9:
    case 0xa:
    case 0xb:
    case 0xc:
        traits = data_ov022_020b25b4;
        if (traits.aTrait[nKind] != 0) {
            bAlt = func_020358f4(pActor->nId, traits.aTrait[nKind]) != 0;
        }
        break;
    case 8:
        if (nKind == func_ov022_0209bd04(pActor)) {
            pCharge->nPendingKind = pCharge->nPrevKind;
        }
        bLive = 0;
        break;
    default:
        bLive = 0;
        break;
    }
    if (bLive != 0 && bAlt == 0) {
        nCost = FULL_COST;
        if (bFull == 0) {
            nTrait = ((0x64 - func_0203581c(pActor->nId, nKind)) << 12) / 100;
            nCost = nTrait * pReq->nWeight;
        }
    }
    if (bLive != 0 && bPinned != 0 && pReq->nWeight != 0 && nKind != 0xe) {
        nCost = FULL_COST;
    }
    if (nKind == 7 && pActor->nHealth <= 1) {
        nCost = 0;
    }
    if (nKind == 0xb && pCharge->bReleased == 1) {
        nCost = 0;
    }
    if (nCost <= 0) {
        if (func_ov022_0209bd04(pActor) == 3) {
            int bWake = 0;

            if ((pReq->nFlags & 0x40) != 0) {
                bWake = 1;
            }
            if (pActor->nStagger > 0) {
                bWake = 1;
            }
            if (bWake != 0) {
                func_ov022_0209b1e8(pActor);
            }
        }
        if (func_ov022_0209bd04(pActor) != 2) {
            return;
        }
        if (pCharge->nMeter <= 0) {
            return;
        }
        func_ov022_0209b1e8(pActor);
        return;
    }
    if (nKind == 5 && (pActor->aFlags[0] & 0x10000) != 0) {
        return;
    }
    if (bPinned == 0 && func_020358f4(pActor->nId, TRAIT_SCALE) != 0) {
        nTrait = func_020358f4(pActor->nId, TRAIT_SCALE);
        nCost = FX_Mul(0x1000 - (nTrait << 9), nCost);
    }
    if (nKind == pCharge->nPendingKind) {
        return;
    }
    if (func_0203084c() * 0x64 > nCost) {
        return;
    }
    pReq->nFlags2 |= 2;
    if (nKind == 4) {
        func_ov022_020acc94(pActor, (u32)pActor->nHealth >> 1);
        return;
    }
    pCharge->nMeter = 0;
    pCharge->nSpent = 0;
    pCharge->nStreak = 0;
    func_ov022_0209be44(pActor);
    nPrev = pCharge->nPendingKind;
    if (nPrev == 0xc && nKind != 0xc) {
        func_ov002_0206df6c(pActor->nId, 0);
    } else if (nPrev != 0xc && nKind == 0xc) {
        func_ov002_0206df6c(pActor->nId, 1);
    }
    pCharge->nPendingKind = nKind;
    if (nKind != 7) {
        return;
    }
    if (func_02030788() != 0) {
        return;
    }
    ACTOR_FLAGS3(pActor) |= 0x400000000000000;
}
