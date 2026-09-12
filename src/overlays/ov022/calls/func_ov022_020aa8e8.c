/* Ov022_ApplyItemEffect -- apply an item of the given kind and level to the
 * actor, then forward kinds 6 and up to the mission side for the local
 * player.
 *
 * Kinds 0 and 1 (local player only): the level picks a tally count (0: 1,
 * 1: 8, 2: 0x1e, 10: 5, 11: 10, 12: 0x14), flag-3 bit 42 is raised and the
 * tally is added under 7 for kind 0 or 0 for kind 1. Kind 2 heals: one
 * percent of the max HP, grown by a third per slot-rule 0x4d point, doubled
 * in mode 0 or scaled by 0xb33 in mode 2 (the mode is 1 under global bit 1,
 * else state field 0x20ea/2), at least one unit; level 0 heals that, level
 * 1 three times the raw amount (at least three units); a live actor takes
 * the heal as negative damage (or a plain HP set when it would not heal) and
 * raises flag-3 bit 40. Kind 3 (local player only) adds tally 4 by level (1,
 * 5, 10) to a live actor. Kinds 6..0xc enable resource nLevel for the owner
 * and, on a remote player with an unfilled slot, drive the owned sound.
 * Kind 0xd enables the resource and sets its global half for a live actor.
 * Kind 0xf (local player only) applies the mode.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* Ov022Actor */
struct Actor {
    u8 pad0000[8];
    u8 nOwner;                   /* 0x0008 */
    u8 nId;                      /* 0x0009 */
    u8 pad000a[8];
    u16 nHp;                     /* 0x0012 */
    u8 pad0014[2];
    u16 nHpMax;                  /* 0x0016 */
    u8 pad0018[0x454];
    u64 nFlags3;                 /* 0x046c */
};

#define FLAG3_BIT40 (1ULL << 40)
#define FLAG3_BIT42 (1ULL << 42)
#define FX32_ONE 0x1000
#define FX32(n) ((n) << 12)
#define FXMUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))
#define GLOBAL_BIT1 0x2
#define STATE_HEAL_MODE 0x20ea
#define HEAL_DOUBLE 0x2000
#define HEAL_MODE2 0xb33
#define RULE_HEAL 0x4d
#define TALLY_KIND0 7
#define TALLY_KIND1 0
#define TALLY_KIND3 4

extern u8 data_0204c240;

extern int func_02030788(void);                                                 /* Session_GetLocalPlayerIndex */
extern void func_ov002_0206bbb8(int nWho, int nKind, int nCount);              /* Ov002_AddMissionTally */
extern int func_020358f4(int nId, int nRule);                                   /* Slot_EvalPackedParam */
extern int func_020235d0(int nField, int nWidth);                               /* GameState_GetField */
extern void func_ov022_020ace24(struct Actor *pActor, int nDamage, int nMode);  /* Ov022_ApplyDamageAndFlagHit */
extern void func_ov022_020acc94(struct Actor *pActor, int nValue);             /* Ov022_ActorSetHp */
extern void func_ov002_02056de0(int nResource, int bEnabled);
extern int func_02035924(int nId);                                              /* Slot_AllEntriesFilled */
extern void func_ov022_020aa824(struct Actor *pActor, int nParam, int nKind, int nDelta);   /* Ov022_DriveOwnedSound */
extern void func_ov022_020ad5f4(struct Actor *pActor, int nHalf, int bSet);    /* SetGlobalHalfBool */
extern void func_ov002_0206e5fc(int nMode);
extern void func_ov002_0206dc70(int nWho, int nParam, u32 nKind, int nLevel);

void func_ov022_020aa8e8(struct Actor *pActor, int nParam, u32 nKind, int nLevel)
{
    int nValue;
    int nHeal;
    int nCount;
    int nUnits;
    int nMode;
    int nRule;
    int nHp;

    nValue = 0;
    switch (nKind) {
    case 0:
    case 1:
        if (func_02030788() == 0) {
            switch (nLevel) {
            case 0:
                nValue = 1;
                break;
            case 1:
                nValue = 8;
                break;
            case 2:
                nValue = 0x1e;
                break;
            case 10:
                nValue = 5;
                break;
            case 11:
                nValue = 10;
                break;
            case 12:
                nValue = 0x14;
                break;
            }
            pActor->nFlags3 |= FLAG3_BIT42;
            if (func_02030788() == 0) {
                func_ov002_0206bbb8(pActor->nId, nKind == 0 ? TALLY_KIND0 : TALLY_KIND1, nValue);
            }
        }
        break;
    case 2:
        nHeal = FX32(pActor->nHpMax) / 100;
        nRule = func_020358f4(pActor->nId, RULE_HEAL);
        if (nRule > 0) {
            nHeal = FXMUL(nHeal, FX32(nRule) / 3 + FX32_ONE);
        }
        if (func_02030788() == 0) {
            if ((data_0204c240 & GLOBAL_BIT1) != 0) {
                nMode = 1;
            } else {
                nMode = func_020235d0(STATE_HEAL_MODE, 2);
            }
            switch (nMode) {
            case 0:
                nHeal = FXMUL(nHeal, HEAL_DOUBLE);
                break;
            case 1:
                break;
            case 2:
                nHeal = FXMUL(nHeal, HEAL_MODE2);
                break;
            }
            nUnits = nHeal >> 12;
            if (nUnits < 1) {
                nUnits = 1;
            }
            switch (nLevel) {
            case 0:
                nValue = nUnits;
                break;
            case 1:
                nValue = (nHeal * 3) >> 12;
                if (nValue < nUnits * 3) {
                    nValue = nUnits * 3;
                }
                break;
            }
            nHp = pActor->nHp;
            if (nHp != 0) {
                if (nHp + nValue < 0) {
                    nValue = 1 - nHp;
                }
                if (nValue > 0) {
                    func_ov022_020ace24(pActor, nValue, 0);
                } else {
                    func_ov022_020acc94(pActor, nHp + nValue);
                }
                pActor->nFlags3 |= FLAG3_BIT40;
            }
        }
        break;
    case 3:
        if (func_02030788() == 0) {
            switch (nLevel) {
            case 0:
                nCount = 1;
                break;
            case 1:
                nCount = 5;
                break;
            case 2:
                nCount = 10;
                break;
            }
            if (pActor->nHp != 0) {
                func_ov002_0206bbb8(pActor->nId, TALLY_KIND3, nCount);
            }
        }
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        if (pActor->nOwner == func_02030788()) {
            func_ov002_02056de0(nLevel, 1);
        }
        if (func_02035924(pActor->nId) == 0 && func_02030788() != 0) {
            func_ov022_020aa824(pActor, nParam, nLevel, 1);
        }
        break;
    case 13:
        if (pActor->nHp != 0) {
            func_ov002_02056de0(nLevel, 1);
            func_ov022_020ad5f4(pActor, nLevel, 1);
        }
        break;
    case 15:
        if (func_02030788() == 0) {
            func_ov002_0206e5fc(nLevel);
        }
        break;
    }
    if (func_02030788() != 0) {
        return;
    }
    if (nKind < 6) {
        return;
    }
    func_ov002_0206dc70(pActor->nId, nParam, nKind, nLevel);
}
