/* ov022: open the guard window against a hit, if the hit is worth guarding.
 *
 * Works out how much of the actor's guard the hit would cost, and only arms the
 * window when that cost clears the floor the scene reports. A hit of the kind
 * already pending never re-arms it.
 *
 * The cost starts at the full amount for the kind the caller flags, otherwise it
 * scales with how much of the move is left and the hit's own weight. One trait
 * pins it back to full; another scales it down by a percentage.
 *
 * Levers: the guard-kind test is a switch (an if/else predicates); pinned is read from
 * the first call before the other flags are raised; the scale multiply is
 * FX_Mul(0x1000 - (nTrait << 9), nCost) with the scale as the LEFT operand expression,
 * so the product temporaries are created before the scale value and the smull
 * RdLo/RdHi != Rm rule lands them in r2/r1 with the rounded high word in r0.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define ACTOR_FLAGS2(p) (*(unsigned long long *)(p)->aFlags2)

#define FULL_COST 0x64000
#define GUARD_KIND 8
#define TRAIT_FULL 0x5d
#define TRAIT_SCALE 0x5c

struct Request {
    u8 pad00[0x14];
    int nKind;                   /* 0x14 */
    u8 nWeight;                  /* 0x18 */
    u8 pad19[0xb];
    int nFlags2;                 /* 0x24 */
};

struct Actor {
    u8 pad000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad00a[0x45a];
    u32 aFlags2[2];              /* 0x0464 */
    u8 pad46c[0x1e8c];
    u8 cue[4];                   /* 0x22f8 */
    u8 pad22fc[0x474];
    signed char nPendingKind;    /* 0x2770 */
    signed char nPrevKind;       /* 0x2771 */
};

extern int func_020358f4(int nId, int nTrait);
extern int func_0203581c(int nId, int nKind);
extern int func_0203084c(void);
extern int func_ov022_02095524(u8 *pCue);

static inline int FX_Mul(int v1, int v2)
{
    return (int)(((long long)v1 * v2 + 0x800) >> 12);
}

void func_ov022_0209b250(struct Actor *pActor, struct Request *pReq, int bFull)
{
    int nCost;
    int nKind;
    int bGuard;
    int bLive;
    int bPinned;
    int nTrait;

    nCost = 0;
    nKind = pReq->nKind;
    bPinned = func_020358f4(pActor->nId, TRAIT_FULL) != 0;
    bGuard = 0;
    bLive = 1;
    if (func_ov022_02095524(pActor->cue) != 0) {
        return;
    }
    if ((ACTOR_FLAGS2(pActor) & 0x10000) != 0) {
        return;
    }
    switch (nKind) {
    case GUARD_KIND:
        bGuard = bLive;
        break;
    default:
        bLive = 0;
        break;
    }
    if (bGuard != 0) {
        nCost = FULL_COST;
        if (bFull == 0) {
            nTrait = ((0x64 - func_0203581c(pActor->nId, nKind)) << 12) / 100;
            nCost = nTrait * pReq->nWeight;
        }
    }
    if (bLive != 0 && pReq->nWeight != 0 && bPinned != 0) {
        nCost = FULL_COST;
    }
    if (nCost <= 0) {
        return;
    }
    if (bLive == 0) {
        return;
    }
    if (bPinned == 0 && func_020358f4(pActor->nId, TRAIT_SCALE) != 0) {
        nTrait = func_020358f4(pActor->nId, TRAIT_SCALE);
        nCost = FX_Mul(0x1000 - (nTrait << 9), nCost);
    }
    if (nKind == pActor->nPendingKind) {
        return;
    }
    if (func_0203084c() * 0x64 > nCost) {
        return;
    }
    pReq->nFlags2 |= 2;
    pActor->nPrevKind = pActor->nPendingKind;
    pActor->nPendingKind = nKind;
}
