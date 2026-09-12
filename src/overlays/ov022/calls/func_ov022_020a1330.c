/* Ov022_SendSweepHit -- turn a sweep contact into an ov107 hit packet
 * against the entry that was hit and record the outcome; returns 1 when
 * the entry took it.
 *
 * Only the local player sends. The packet carries the hit point, the spec's
 * flags, its kind as a mask (the kind bit, or the spec's mask when the
 * random-kind bit is up), the base damage, the actor id, the part node, the
 * spec's strength and extra byte. A bonus applies when the spec says so or,
 * under slot rule 0x36 while the actor is not shielded, when spec flag bit
 * 2 is up; a positive extra damage replaces the bonus with itself. A bonus
 * row lookup goes into the damage and, when positive, raises packet flag
 * bit 1 and caps the strength at 100. Without spec flag 3, charge kind 10
 * drops packet flag bit 0 and gives a 75 percent whiff: the point, damage
 * and strength go to zero under flags 200. Flag bit 16 raises packet bit 8;
 * an actor at 0 HP outside mode flag bit 2 sends no damage or strength.
 * A packet the entry does not take marks the actor's contact with bit 6
 * (and, unless a whiff, a first contact with an entry of flag bit 2 takes
 * its state, entry and point). A taken packet records: an answered hit
 * (result bit 0) marks contact bit 0 (and bit 5 under result bit 3); a
 * blocked one (result bit 1) outside mode flag bit 2, without flag bit 16
 * and under packet bit 9 ticks the tally's counter 0x196c or 0x196e (packet
 * bit 10) up to 10000; packet bit 1 marks contact bit 1 unless answered, a
 * whiff bit 4; the contact takes state 1, the entry and the point; a
 * positive damage that was neither answered nor a whiff advances the combo
 * gauge by 1 for a blocked hit, 2 for blocked with result bit 2, 0 for a
 * plain one -- never with result bit 2 alone.
 *
 * Lever: the flag-16 test before the packet fix-up is a 64-bit test cast to u32
 * ((u32)(ACTOR_FLAGS(pActor) & FLAG_BIT16)); the constant's low word lives in a
 * register above the branch and the bitfield mask is derived from it (sub #0x20000).
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
    u8 pad11[0x13];
    u8 nExtraByte;               /* 0x24 */
    u8 bBonus : 1;               /* 0x25 bit 0 */
    u8 bRandomKind : 1;          /* bit 1 */
    u8 nSpare25 : 6;
};

/* Ov107Shape: only the anchor position is read here */
struct Shape {
    u8 pad00[4];
    VecFx32 vecPos;              /* 0x04 */
};

/* Ov022PartNode */
struct PartNode {
    struct Shape *pShape;        /* 0x00 */
};

/* Ov022HitEntry */
struct Entry {
    u8 pad000[0x19f];
    u8 nGaugeArg;                /* 0x19f */
    u8 pad1a0[0xc];
    u16 wFlags1ac;               /* 0x1ac */
};

struct HitRecord {
    VecFx32 vecPos;              /* 0x00 */
};

/* Ov107HitPacket */
struct HitPacket {
    u32 nFlags : 16;             /* 0x00 */
    u32 nKindMask : 16;
    VecFx32 vecPos;              /* 0x04 */
    int nBase : 16;              /* 0x10 */
    int nDamage : 16;
    u32 nId : 16;                /* 0x14 */
    u32 nSpare16 : 16;
    struct PartNode *pNode;      /* 0x18 */
    signed char nStrength;       /* 0x1c */
    u8 nExtraByte;               /* 0x1d */
    u8 pad1e[6];
    u32 nResult : 16;            /* 0x24 */
    u32 nSpare24 : 16;
    u32 nField28;                /* 0x28 */
};

struct Actor;

/* Ov022SweepContact */
struct SweepContact {
    u32 nResult;                 /* 0x00 */
    int nKind;                   /* 0x04 */
    u8 nState;                   /* 0x08 */
    u8 pad09[3];
    VecFx32 vec;                 /* 0x0c */
    struct Entry *pEntry;        /* 0x18 */
};

/* the tally source record */
struct TallySource {
    u8 pad0000[0x196c];
    u16 nBlockedA;               /* 0x196c */
    u16 nBlockedB;               /* 0x196e */
};

/* Ov022Actor */
struct Actor {
    u32 nFlagsLo;                /* 0x0000 */
    u32 nFlagsHi;                /* 0x0004 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[8];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[0x4d8];
    void *pSub;                  /* 0x04ec */
    u8 pad04f0[0x21cc];
    struct SweepContact contact; /* 0x26bc */
};

#define FLAG_BIT16 0x10000
#define ACTOR_FLAGS(p) (*(unsigned long long *)&(p)->nFlagsLo)
#define MODE_FLAG_BIT2 0x4
#define SPEC_BIT2 0x4
#define SPEC_BIT3 0x8
#define SPEC_BIT5 0x20
#define PKT_BIT0 0x1
#define PKT_BONUS 0x2
#define PKT_BIT8 0x100
#define PKT_BIT9 0x200
#define PKT_BIT10 0x400
#define PKT_WHIFF 200
#define RES_ANSWERED 0x1
#define RES_BLOCKED 0x2
#define RES_BIT2 0x4
#define RES_BIT3 0x8
#define RULE_BONUS 0x36
#define STRENGTH_CAP 100
#define CHARGE_KIND_WHIFF 10
#define WHIFF_CHANCE 0x4b
#define ENTRY_FLAG_BIT2 0x4
#define CONTACT_ANSWERED 0x1
#define CONTACT_BONUS 0x2
#define CONTACT_WHIFF 0x10
#define CONTACT_BIT5 0x20
#define CONTACT_UNTAKEN 0x40
#define CONTACT_STATE_HIT 1
#define TALLY_LIMIT 10000

extern u8 data_0204c240;                    /* g_modeAndDayClock.nModeFlags */
extern struct TallySource *data_0204be18;   /* g_pTallySource */

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_ov022_020ad7b0(struct Actor *pActor);                           /* Ov022_IsShielded */
extern int func_ov022_020a2230(struct Actor *pActor, int bAlt, int bBonus);     /* Ov022_LookupRowValue */
extern int func_ov022_0209bd04(struct Actor *pActor);                           /* Ov022_GetChargeKind */
extern u32 func_020307f4(int nRange);                                           /* Session_RandNextScaled */
extern int func_ov107_020c5cfc(struct Entry *pEntry, void *pSub, struct HitPacket *pPacket);
extern void func_ov022_0209c4e0(struct Actor *pActor, int nStep, int nArg);     /* Ov022_AdvanceComboGauge */

int func_ov022_020a1330(struct Actor *pActor, struct HitSpec *pSpec, struct Entry *pEntry,
                        struct PartNode *pNode, struct HitRecord *pHit)
{
    struct HitPacket pkt;
    int nRet;
    int bWhiff;
    int bBonus;
    int nBonus;
    int bAlt;
    int nChance;
    int nStep;
    u32 nResult;
    u32 nBlocked;

    nRet = 0;
    if (func_02030788() == 0) {
        pkt.vecPos = pHit->vecPos;
        bWhiff = 0;
        bBonus = 0;
        pkt.nBase = pSpec->nBase;
        pkt.nDamage = 0;
        pkt.nFlags = pSpec->nFlags;
        if (!pSpec->bRandomKind) {
            pkt.nKindMask = 1 << pSpec->nKind;
        } else {
            pkt.nKindMask = pSpec->nKind;
        }
        pkt.pNode = pNode;
        pkt.nId = pActor->nId;
        pkt.nStrength = pSpec->nStrength;
        pkt.nExtraByte = pSpec->nExtraByte;
        if (pSpec->bBonus) {
            bBonus = 1;
        }
        if (func_020358f4(pActor->nId, RULE_BONUS) != 0 && func_ov022_020ad7b0(pActor) == 0
            && (pSpec->nFlags & SPEC_BIT2) != 0) {
            bBonus = 1;
        }
        if (pSpec->nExtra > 0) {
            pkt.nDamage = pSpec->nExtra;
            bBonus = 0;
        }
        if (bBonus) {
            bAlt = 0;
            if ((pSpec->nFlags & SPEC_BIT5) != 0) {
                bAlt = 1;
            }
            nBonus = func_ov022_020a2230(pActor, bAlt, pSpec->bBonus);
            pkt.nDamage = nBonus;
            if (pkt.nDamage > 0) {
                pkt.nFlags |= PKT_BONUS;
                if (pkt.nStrength > 0) {
                    pkt.nStrength = STRENGTH_CAP;
                }
            }
        }
        if ((pSpec->nFlags & SPEC_BIT3) == 0) {
            nChance = -1;
            if (func_ov022_0209bd04(pActor) == CHARGE_KIND_WHIFF) {
                pkt.nFlags &= ~PKT_BIT0;
                nChance = WHIFF_CHANCE;
            }
            if (nChance != -1 && func_020307f4(100) < (u32)nChance) {
                pkt.vecPos.x = pkt.vecPos.y = pkt.vecPos.z = 0;
                pkt.nBase = 0;
                pkt.nDamage = 0;
                pkt.nFlags = PKT_WHIFF;
                pkt.nKindMask = 0;
                pkt.nStrength = 0;
                bWhiff = 1;
            }
        }
        if ((u32)(ACTOR_FLAGS(pActor) & FLAG_BIT16) != 0) {
            pkt.nFlags |= PKT_BIT8;
        }
        if ((data_0204c240 & MODE_FLAG_BIT2) == 0 && pActor->nHp == 0) {
            pkt.nBase = 0;
            pkt.nDamage = 0;
            pkt.nStrength = 0;
        }
        if (func_ov107_020c5cfc(pEntry, pActor->pSub, &pkt) != 0) {
            nRet = 1;
            nResult = pkt.nResult;
            if (nResult != 0) {
                if ((nResult & RES_ANSWERED) != 0) {
                    pActor->contact.nResult |= CONTACT_ANSWERED;
                    if ((pkt.nResult & RES_BIT3) != 0) {
                        pActor->contact.nResult |= CONTACT_BIT5;
                    }
                } else if ((data_0204c240 & MODE_FLAG_BIT2) == 0 && (nResult & RES_BLOCKED) != 0
                           && (pActor->nFlagsLo & FLAG_BIT16) == 0 && (pkt.nFlags & PKT_BIT9) != 0) {
                    u16 *pCount;

                    if ((pkt.nFlags & PKT_BIT10) != 0) {
                        pCount = &data_0204be18->nBlockedB;
                    } else {
                        pCount = &data_0204be18->nBlockedA;
                    }
                    *pCount += 1;
                    if (*pCount > TALLY_LIMIT) {
                        *pCount = TALLY_LIMIT;
                    }
                }
            }
            if ((pActor->contact.nResult & CONTACT_ANSWERED) == 0 && (pkt.nFlags & PKT_BONUS) != 0) {
                pActor->contact.nResult |= CONTACT_BONUS;
            }
            if (bWhiff) {
                pActor->contact.nResult |= CONTACT_WHIFF;
            }
            pActor->contact.nState = CONTACT_STATE_HIT;
            pActor->contact.pEntry = pEntry;
            pActor->contact.vec = pNode->pShape->vecPos;
            if ((pkt.nResult & RES_ANSWERED) == 0 && bWhiff != 1 && pkt.nBase > 0) {
                nBlocked = pkt.nResult & RES_BLOCKED;
                nStep = 0;
                if (nBlocked != 0) {
                    nStep = 1;
                }
                if ((pkt.nResult & RES_BIT2) != 0) {
                    nStep = -1;
                    if (nBlocked != 0) {
                        nStep = 2;
                    }
                }
                if (nStep >= 0) {
                    func_ov022_0209c4e0(pActor, nStep, pEntry->nGaugeArg);
                }
            }
        } else {
            if (!bWhiff && (pEntry->wFlags1ac & ENTRY_FLAG_BIT2) != 0 && pActor->contact.nState == 0) {
                pActor->contact.nState = CONTACT_STATE_HIT;
                pActor->contact.pEntry = pEntry;
                pActor->contact.vec = pNode->pShape->vecPos;
            }
            pActor->contact.nResult |= CONTACT_UNTAKEN;
        }
    }
    return nRet;
}
