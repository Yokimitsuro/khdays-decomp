/* Ov022_ComputeDamageTaken -- the damage an incoming hit request does to
 * the actor, in whole units.
 *
 * Request flag 8 passes the damage through; flag 11 makes it a tenth of the
 * max HP. Flag 1 under mode flag bit 2 with a tally kind marks a drain hit.
 * Unless the request is a percent hit without flag 5, the defence -- the
 * base stat for charge kind 9, otherwise the kind record's defence plus the
 * actor's bonus, capped at 999 and raised by 12.5 percent when shielded
 * under rule 0x3c (a drain hit multiplies it by 8 and the damage by 0.25 or
 * 1.0 by the tally kind) -- shapes the damage as (2 * damage + 46) over
 * (0.1 * defence - 0.07 * damage + 11), never under 1. A percent hit adds
 * the damage's share of 100 less the kind's resistance (a drain hit takes
 * 1/256 or 1/8 of it), halved under flag 5 with a floor of 1. Charge kind 3
 * pushed up or on a percent hit multiplies by 3, charge kind 2 by 1.2,
 * shielded under rule 0x3e halves, then the difficulty field 0x20ea scales
 * by 0.7 (0) or 1.75 (2) unless mode flag bit 1, which adds the panel
 * threshold's percent. A blocked run halves it, mode flag bit 2 with
 * request flag 0 multiplies by 1.5, a non-percent (or flag 5) hit is at
 * least 1, and under the same mode the tally's seventh byte raises a hit
 * of at least 1 to 10 or 50. Rule 0x39 at full HP (a roll under 100)
 * thirds a hit of 3 or more and floors a smaller one to 1. Flag 7 zeroes
 * it.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed long long s64;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Ov022HitRequest */
struct HitRequest {
    u32 nFlags;                  /* 0x00 */
    VecFx32 vecPush;             /* 0x04 */
    int nDamage;                 /* 0x10 */
    int nKind;                   /* 0x14 */
};

/* Ov002MissionMember: per-id table of 0x104-byte records (kOv022KindRecords) */
struct Record {
    u8 pad0000[0xc];
    u16 nDefense;                /* 0x000c body.nDefense */
    u8 pad000e[0xf6];
};

/* Ov022StatBlock: the actor's stat bonuses (combo state + 8) */
struct Stats {
    u8 nField0;                  /* 0x00 */
    u8 nResourceBase;            /* 0x01 */
    short nStrengthBonus;        /* 0x02 */
    short nMagicBonus;           /* 0x04 */
    short nDefenseBonus;         /* 0x06 */
};

/* Ov002PanelThresholds */
struct PanelThresholds {
    u8 pad00[6];
    u8 nDamagePercent;           /* 0x06 */
};

/* Ov002TallyRules */
struct TallyRules {
    u8 nKind;                    /* 0x00 */
    u8 pad01[6];
    u8 nDamageFloor;             /* 0x07 */
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[8];
    u16 nHp;                     /* 0x0012 */
    u16 nBaseDefense;            /* 0x0014 */
    u16 nHpMax;                  /* 0x0016 */
    u8 pad0018[0x900];
    struct Stats stats;          /* 0x0918 */
    u8 pad0920[0x19d8];
    u32 run[0xdc];               /* 0x22f8 Ov022ActionOwner */
};

#define REQ_BIT0 0x1
#define REQ_BIT1 0x2
#define REQ_HALF 0x20
#define REQ_PERCENT 0x40
#define REQ_ZERO 0x80
#define REQ_RAW 0x100
#define REQ_TENTH 0x800
#define MODE_FLAG_BIT1 0x2
#define MODE_FLAG_BIT2 0x4
#define DEFENSE_CAP 0x3e7000
#define SHIELD_DEFENSE 0x1200
#define DRAIN_DEFENSE_SHIFT 3
#define DRAIN_DAMAGE_A 0x400
#define DRAIN_DAMAGE_B 0x1000
#define DRAIN_PART_A 0x10
#define DRAIN_PART_B 0x200
#define DEFENSE_SHARE 0x19a
#define DAMAGE_SHARE_DIFF 0x7b
#define DIVISOR_BIAS 0xb000
#define DAMAGE_DOUBLE 0x2000
#define DAMAGE_BIAS 0x2e000
#define PERCENT_ONE 0x64000
#define CHARGE_KIND_BASE 9
#define CHARGE_KIND_TRIPLE 3
#define CHARGE_KIND_BOOST 2
#define TRIPLE 0x3000
#define BOOST 0x1333
#define RULE_SHIELD_DEFENSE 0x3c
#define RULE_SHIELD_HALF 0x3e
#define RULE_FULL_HP 0x39
#define DIFFICULTY_FIELD 0x20ea
#define EASY_SCALE 0xb33
#define HARD_SCALE 0x1c00
#define DRAIN_SCALE 0x1800
#define FLOOR_A 0xa000
#define FLOOR_B 0x32000
#define ONE 0x1000
#define THREE 0x3000

extern struct Record data_0204c678[];              /* kOv022KindRecords */
extern u8 data_0204c240;                           /* g_modeAndDayClock.nModeFlags */
extern struct TallyRules data_0204c248;            /* Ov002TallyRules */
extern struct PanelThresholds data_0204c254;       /* g_ov002PanelThresholds */

extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_ov022_0209bd04(struct Actor *pActor);                           /* Ov022_GetChargeKind */
extern int func_ov022_020ad7b0(struct Actor *pActor);                           /* Ov022_IsShielded */
extern int FX_Inv(int nNumerator, int nDenominator);
extern int func_0203581c(int nId, int nKind);                                   /* Load2DArrayU8_c690 */
extern int func_020235d0(int nField, int nWidth);                               /* GameState_GetField */
extern int func_ov022_02095524(u32 *pRun);                                      /* ov022_IsState9Or6WithFlag200 */
extern u32 func_020307f4(int nRange);                                           /* Session_RandNextScaled */

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

int func_ov022_020a2424(struct Actor *pActor, struct HitRequest *pReq)
{
    struct Record *pRec;
    u32 nFlags;
    int nResult;
    int bDrain;
    struct Stats *pStats;
    int nDamage;
    u16 nDefBase;
    int nDefense;
    int nDivisor;
    int nResist;
    int nPart;
    int bBoost;
    int nCap;
    int nRule;

    nFlags = pReq->nFlags;
    nResult = 0;
    pRec = &data_0204c678[pActor->nId];
    bDrain = 0;
    pStats = &pActor->stats;
    if ((nFlags & REQ_RAW) != 0) {
        return pReq->nDamage;
    }
    if ((nFlags & REQ_TENTH) != 0) {
        return pActor->nHpMax / 10;
    }
    if ((nFlags & REQ_BIT1) != 0) {
        if ((data_0204c240 & MODE_FLAG_BIT2) != 0 && data_0204c248.nKind != 0) {
            bDrain = 1;
        }
    }
    if ((nFlags & REQ_PERCENT) == 0 || (nFlags & REQ_HALF) != 0) {
        nRule = func_020358f4(pActor->nId, RULE_SHIELD_DEFENSE);
        nDamage = pReq->nDamage << 12;
        nDefBase = pRec->nDefense;
        if (func_ov022_0209bd04(pActor) == CHARGE_KIND_BASE) {
            nDefense = pActor->nBaseDefense * ONE;
        } else {
            nDefense = ((u32)nDefBase << 12) + (pStats->nDefenseBonus << 12);
        }
        if (nDefense >= DEFENSE_CAP) {
            nDefense = DEFENSE_CAP;
        }
        if (nRule > 0 && func_ov022_020ad7b0(pActor)) {
            nDefense = FxMul(nDefense, SHIELD_DEFENSE);
        }
        if (bDrain) {
            nDefense <<= DRAIN_DEFENSE_SHIFT;
            if (data_0204c248.nKind == 1) {
                nDamage = FxMul(nDamage, DRAIN_DAMAGE_A);
            } else {
                nDamage = FxMul(nDamage, DRAIN_DAMAGE_B);
            }
        }
        nDivisor = FxMul(nDefense, DEFENSE_SHARE) - FxMul(nDamage, DEFENSE_SHARE - DAMAGE_SHARE_DIFF) + DIVISOR_BIAS;
        if (nDivisor < ONE) {
            nDivisor = ONE;
        }
        nResult = FX_Inv(FxMul(nDamage, DAMAGE_DOUBLE) + DAMAGE_BIAS, nDivisor);
    }
    if ((pReq->nFlags & REQ_PERCENT) != 0) {
        nResist = 100 - func_0203581c(pActor->nId, pReq->nKind);
        nPart = FX_Inv(pReq->nDamage << 12, PERCENT_ONE); nPart *= nResist;
        if (bDrain) {
            if (data_0204c248.nKind == 1) {
                nPart = FxMul(nPart, DRAIN_PART_A);
            } else {
                nPart = FxMul(nPart, DRAIN_PART_B);
            }
        }
        nResult += nPart;
        if ((pReq->nFlags & REQ_HALF) != 0) {
            nResult /= 2;
            if (nResult <= 0) {
                nResult = ONE;
            }
        }
    }
    if (func_ov022_0209bd04(pActor) == CHARGE_KIND_TRIPLE) {
        bBoost = 0;
        if ((pReq->nFlags & REQ_PERCENT) != 0) {
            bBoost = 1;
        }
        if (pReq->vecPush.y > 0) {
            bBoost = 1;
        }
        if (bBoost) {
            nResult = FxMul(nResult, TRIPLE);
        }
    }
    if (func_ov022_0209bd04(pActor) == CHARGE_KIND_BOOST) {
        nResult = FxMul(nResult, BOOST);
    }
    if (func_020358f4(pActor->nId, RULE_SHIELD_HALF) != 0 && func_ov022_020ad7b0(pActor)) {
        nResult /= 2;
    }
    if ((data_0204c240 & MODE_FLAG_BIT1) != 0) {
        if (data_0204c254.nDamagePercent != 0) {
            nResult += (nResult / 100) * data_0204c254.nDamagePercent;
        }
    } else {
        switch (func_020235d0(DIFFICULTY_FIELD, 2)) {
        case 0:
            nResult = FxMul(nResult, EASY_SCALE);
            break;
        case 1:
            break;
        case 2:
            nResult = FxMul(nResult, HARD_SCALE);
            break;
        }
    }
    if (func_ov022_02095524(pActor->run) != 0) {
        nResult /= 2;
    }
    if ((data_0204c240 & MODE_FLAG_BIT2) != 0 && (pReq->nFlags & REQ_BIT0) != 0) {
        nResult = FxMul(nResult, DRAIN_SCALE);
    }
    nFlags = pReq->nFlags;
    if (((nFlags & REQ_PERCENT) == 0 || (nFlags & REQ_HALF) != 0) && nResult < ONE) {
        nResult = ONE;
    }
    if ((data_0204c240 & MODE_FLAG_BIT2) != 0 && (nFlags & REQ_BIT0) != 0) {
        nCap = 0;
        switch (data_0204c248.nDamageFloor) {
        case 1:
            nCap = FLOOR_A;
            break;
        case 2:
            nCap = FLOOR_B;
            break;
        }
        if (nCap > 0 && nResult < nCap && nResult >= ONE) {
            nResult = nCap;
        }
    }
    if (func_020358f4(pActor->nId, RULE_FULL_HP) != 0 && pActor->nHp == pActor->nHpMax
        && func_020307f4(100) < 100) {
        if (nResult >= THREE) {
            nResult /= 3;
        } else {
            if (nResult >= ONE) {
                nResult = ONE;
            }
        }
    }
    if ((pReq->nFlags & REQ_ZERO) != 0) {
        nResult = 0;
    }
    return nResult >> 12;
}
