/* Ov022_DeliverHit -- turn a hit spec into a hit request against the actor,
 * deliver it through the owner, and record the contact.
 *
 * A spec with flag bit 4 is ignored. The request carries the base plus
 * extra damage, the push direction (normalised, its length capped at
 * 0x1666), the spec's kind -- or a random one of the kinds in its mask when
 * the random-kind bit is up -- its strength, and the actor. A bonus applies
 * when the spec says so or, under slot rule 0x36 while the actor is not
 * shielded, when spec flag bit 2 is up; a non-positive row lookup cancels it,
 * otherwise it is added to the damage. Spec flags 2, 3, 11 and 7 map to
 * request flags 5, 6, 7 and 4|9; kind 0xb under flag 3 also sets bit 3.
 * Spec flag 6 sets request bit 11; without it the request is only sent when
 * the actor has flag bit 12 and the owner's value is negative (a global of
 * 1 also zeroes the strength). Without spec flag 3, charge kind 10 gives a
 * 75 percent whiff: nothing is sent, the request becomes a zero push of
 * flags 0x90. A sent request that is neither taken nor answered marks the
 * contact with bit 6. The contact then takes the owner's point, state 3 and
 * the owner; for the local player a whiff marks bit 4, a taken bonus hit
 * bit 1, and under flag bit 12 an answered request bit 2.
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

/* Ov022HitSpec */
struct HitSpec {
    int nBase;                   /* 0x00 */
    int nExtra;                  /* 0x04 */
    u32 nFlags;                  /* 0x08 */
    int nKind;                   /* 0x0c: the kind, or a mask of kinds under bRandomKind */
    u8 nStrength;                /* 0x10 */
    u8 pad11[0x14];
    u8 bBonus : 1;               /* 0x25 bit 0 */
    u8 bRandomKind : 1;          /* bit 1 */
    u8 nSpare25 : 6;
};

struct Actor;

/* Ov022HitRequest */
struct HitRequest {
    u32 nFlags;                  /* 0x00 */
    VecFx32 vecPush;             /* 0x04 */
    int nDamage;                 /* 0x10 */
    int nKind;                   /* 0x14 */
    u8 nStrength;                /* 0x18 */
    u8 pad19[3];
    struct Actor *pActor;        /* 0x1c */
    int nField20;                /* 0x20 */
    u32 nResult;                 /* 0x24 */
};

/* Ov022SweepContact */
struct SweepContact {
    u32 nResult;                 /* 0x00 */
    int nKind;                   /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 pad09[3];
    VecFx32 vec;                 /* 0x0c */
    struct Actor *pOwner;        /* 0x18 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x26b2];
    struct SweepContact contact; /* 0x26bc */
};

#define FLAG_BIT12 (1ULL << 12)
#define SPEC_SKIP 0x10
#define SPEC_BIT2 0x4
#define SPEC_BIT3 0x8
#define SPEC_BIT5 0x20
#define SPEC_BIT6 0x40
#define SPEC_BIT7 0x80
#define SPEC_BIT11 0x800
#define KIND_COUNT 14
#define KIND_SPECIAL 0xb
#define REQ_BASE 0x2
#define REQ_BIT3 0x8
#define REQ_BIT5 0x20
#define REQ_BIT6 0x40
#define REQ_BIT7 0x80
#define REQ_BITS4_9 0x210
#define REQ_BIT11 0x800
#define REQ_WHIFF 0x90
#define REQ_ANSWERED 0x1
#define PUSH_MAX 0x1666
#define RULE_BONUS 0x36
#define CHARGE_KIND_WHIFF 10
#define WHIFF_CHANCE 0x4b
#define CONTACT_BONUS 0x2
#define CONTACT_ANSWERED 0x4
#define CONTACT_WHIFF 0x10
#define CONTACT_UNTAKEN 0x40
#define CONTACT_STATE_HIT 3

extern u8 data_0204c248;
extern const VecFx32 data_02041dc8;        /* kVecZero */

extern int func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);                         /* VEC_Normalize */
extern void func_01ffa724(int nFactor, VecFx32 *pSrc, VecFx32 *pDst);          /* ScaleVec3Fx12 */
extern int func_020307f4(int nRange);                                           /* Session_RandNextScaled */
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_ov022_020ad7b0(struct Actor *pActor);                           /* Ov022_IsShielded */
extern int func_ov022_020a2230(struct Actor *pActor, int bAlt, int bBonus);     /* Ov022_LookupRowValue */
extern int func_ov002_02072a38(int nId);
extern int func_ov022_0209bd04(struct Actor *pActor);                           /* Ov022_GetChargeKind */
extern int func_ov022_020a08a8(struct Actor *pOwner, struct HitRequest *pReq);
extern void func_ov022_020ad44c(VecFx32 *pOut, struct Actor *pActor);          /* CopyVec3FromSub948 */
extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */

void func_ov022_020a1870(struct Actor *pActor, struct HitSpec *pSpec, struct Actor *pOwner, VecFx32 *pDir)
{
    struct HitRequest req;
    int aKinds[KIND_COUNT];
    VecFx32 vecPoint;
    int bTaken;
    int bSend;
    int bWhiff;
    int bBonus;
    int bAlt;
    int nLen;
    int nCount;
    int i;
    int nBonus;
    u32 nChance;

    if ((pSpec->nFlags & SPEC_SKIP) != 0) {
        return;
    }
    bTaken = 0;
    req.nDamage = pSpec->nBase + pSpec->nExtra;
    req.vecPush = *pDir;
    req.nFlags = REQ_BASE;
    bWhiff = 0;
    bBonus = 0;
    req.nResult = 0;
    req.nField20 = 0;
    bSend = 1;
    nLen = func_01ff8d18(&req.vecPush, &req.vecPush);
    if (nLen >= PUSH_MAX) {
        nLen = PUSH_MAX;
    }
    func_01ffa724(nLen, &req.vecPush, &req.vecPush);
    if (!pSpec->bRandomKind) {
        req.nKind = pSpec->nKind;
    } else {
        for (i = 0, nCount = 0; i < KIND_COUNT; i++) {
            if ((pSpec->nKind & (1 << i)) != 0) {
                aKinds[nCount++] = i;
            }
        }
        if (nCount > 0) {
            req.nKind = aKinds[func_020307f4(nCount)];
        }
    }
    req.nStrength = pSpec->nStrength;
    req.pActor = pActor;
    if (pSpec->bBonus) {
        bBonus = 1;
    }
    if (func_020358f4(pActor->nId, RULE_BONUS) != 0 && func_ov022_020ad7b0(pActor) == 0
        && (pSpec->nFlags & SPEC_BIT2) != 0) {
        bBonus = 1;
    }
    if (bBonus) {
        bAlt = 0;
        if ((pSpec->nFlags & SPEC_BIT5) != 0) {
            bAlt = 1;
        }
        nBonus = func_ov022_020a2230(pActor, bAlt, pSpec->bBonus);
        if (nBonus <= 0) {
            bBonus = 0;
        }
        req.nDamage += nBonus;
    }
    if ((pSpec->nFlags & SPEC_BIT2) != 0) {
        req.nFlags |= REQ_BIT5;
    }
    if ((pSpec->nFlags & SPEC_BIT3) != 0) {
        req.nFlags |= REQ_BIT6;
    }
    if (pSpec->nKind == KIND_SPECIAL && (pSpec->nFlags & SPEC_BIT3) != 0) {
        req.nFlags |= REQ_BIT3;
    }
    if ((pSpec->nFlags & SPEC_BIT11) != 0) {
        req.nFlags |= REQ_BIT7;
    }
    if ((pSpec->nFlags & SPEC_BIT7) != 0) {
        req.nFlags |= REQ_BITS4_9;
    }
    if ((pSpec->nFlags & SPEC_BIT6) != 0) {
        req.nFlags |= REQ_BIT11;
    } else if ((pActor->nFlags & FLAG_BIT12) != 0) {
        if (data_0204c248 == 1) {
            req.nStrength = 0;
        }
        if (func_ov002_02072a38(pOwner->nId) >= 0) {
            bSend = 0;
        }
    } else {
        bSend = 0;
    }
    if ((pSpec->nFlags & SPEC_BIT3) == 0) {
        nChance = -1;
        if (func_ov022_0209bd04(pActor) == CHARGE_KIND_WHIFF) {
            nChance = WHIFF_CHANCE;
        }
        if (nChance != -1 && (u32)func_020307f4(100) < nChance) {
            bSend = 0;
            req.nDamage = 0;
            req.vecPush = data_02041dc8;
            req.nFlags = REQ_WHIFF;
            req.nStrength = 0;
            bWhiff = 1;
        }
    }
    if (bSend) {
        if (func_ov022_020a08a8(pOwner, &req) != 0) {
            bTaken = 1;
        } else if ((req.nResult & REQ_ANSWERED) != 0) {
            bTaken = 1;
        } else {
            pActor->contact.nResult |= CONTACT_UNTAKEN;
        }
    }
    func_ov022_020ad44c(&vecPoint, pOwner);
    pActor->contact.vec = vecPoint;
    pActor->contact.nState = CONTACT_STATE_HIT;
    pActor->contact.pOwner = pOwner;
    if ((bTaken || bWhiff) && func_02030788() == 0) {
        if (bWhiff) {
            pActor->contact.nResult |= CONTACT_WHIFF;
        } else if (bTaken && bBonus) {
            pActor->contact.nResult |= CONTACT_BONUS;
        }
    }
    if ((pActor->nFlags & FLAG_BIT12) == 0) {
        return;
    }
    if ((req.nResult & REQ_ANSWERED) == 0) {
        return;
    }
    pActor->contact.nResult |= CONTACT_ANSWERED;
}
