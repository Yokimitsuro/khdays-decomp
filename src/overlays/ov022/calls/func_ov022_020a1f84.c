/* Ov022_ComputeStrengthDamage -- the actor's physical damage at this scale.
 *
 * Strength is the kind record's stat plus the actor's own bonus, in whole
 * units and capped at 999; magic is gathered the same way. Slot rule 0x38
 * raises strength by 7% at full HP, rule 0x35 averages it with 0.8125 of
 * magic. The caller's scale is applied, then rule 0x3b adds 7% while the HP
 * check passes, rule 0x37 adds 0x60 per combo hit rounded up to a whole
 * unit, and rule 0x50 another 7% in rumble state 3. The answer is handed
 * back in whole units.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed long long s64;

#define VALUE_CAP 0x3e7000
#define BOOST_7PCT 0x1120
#define MAGIC_SHARE 0xd00
#define COMBO_HIT_SHARE 0x60
#define FRAC_MASK 0xfff
#define WHOLE_MASK 0x7ffff000
#define ONE 0x1000
#define RULE_FULL_HP 0x38
#define RULE_MAGIC_MIX 0x35
#define RULE_LOW_HP 0x3b
#define RULE_COMBO 0x37
#define RULE_STATE3 0x50
#define RUMBLE_STATE_3 3

/* Ov002MissionMember: per-id table of 0x104-byte records (kOv022KindRecords) */
struct Record {
    u8 pad0000[8];
    u16 nStrength;               /* 0x0008 body.nStrength */
    u16 nMagic;                  /* 0x000a body.nMagic */
    u8 pad000c[0xf8];
};

/* Ov022StatBlock: the actor's stat bonuses (combo state + 8) */
struct Stats {
    u8 nField0;                  /* 0x00 */
    u8 nResourceBase;            /* 0x01 */
    short nStrengthBonus;        /* 0x02 */
    short nMagicBonus;           /* 0x04 */
};

struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[8];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[2];
    u16 nHpMax;                  /* 0x0016 */
    u8 pad0018[0x900];
    struct Stats stats;          /* 0x0918 combo.stats */
    u8 pad091e[0x46a];
    int nComboHits;              /* 0x0d88 combo.nComboHits */
    u8 pad0d8c[0x1d28];
    u8 nRumbleState;             /* 0x2ab4 rumble.nState */
};

extern struct Record data_0204c678[];      /* kOv022KindRecords */

extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_ov022_020ad7b0(struct Actor *pActor);                           /* IsField12LeShifted16 */

static inline int FxMul(int nValue, int nScale)
{
    return (int)(((s64)nValue * nScale + 0x800) >> 12);
}

int func_ov022_020a1f84(struct Actor *pActor, int nScale)
{
    struct Record *pRec;
    struct Stats *pStats;
    int nStrength;
    int nMagic;
    int nRuleCombo;
    int nDamage;
    int nRuleLowHp;
    int nBoost;

    pRec = &data_0204c678[pActor->nId];
    nStrength = 0;
    nMagic = 0;
    nStrength += pRec->nStrength << 12;
    nMagic += pRec->nMagic << 12;
    pStats = &pActor->stats;
    nStrength += pStats->nStrengthBonus << 12;
    nMagic += pStats->nMagicBonus << 12;
    if (nStrength >= VALUE_CAP) {
        nStrength = VALUE_CAP;
    }
    if (func_020358f4(pActor->nId, RULE_FULL_HP) != 0 && pActor->nHp == pActor->nHpMax) {
        nStrength = FxMul(nStrength, BOOST_7PCT);
    }
    if (func_020358f4(pActor->nId, RULE_MAGIC_MIX) != 0) {
        nStrength = (nStrength + FxMul(nMagic, MAGIC_SHARE)) / 2;
    }
    nDamage = FxMul(nStrength, nScale);
    nRuleLowHp = func_020358f4(pActor->nId, RULE_LOW_HP);
    nRuleCombo = func_020358f4(pActor->nId, RULE_COMBO);
    if (nRuleLowHp > 0 && func_ov022_020ad7b0(pActor)) {
        nDamage = FxMul(nDamage, BOOST_7PCT);
    }
    if (nRuleCombo > 0 && pActor->nComboHits > 0) {
        nBoost = FxMul(nDamage, pActor->nComboHits * COMBO_HIT_SHARE);
        if ((nBoost & FRAC_MASK) > 0) {
            nBoost = (nBoost & WHOLE_MASK) + ONE;
        }
        nDamage += nBoost;
    }
    if (func_020358f4(pActor->nId, RULE_STATE3) != 0 && pActor->nRumbleState == RUMBLE_STATE_3) {
        nDamage = FxMul(nDamage, BOOST_7PCT);
    }
    return nDamage >> 12;
}
