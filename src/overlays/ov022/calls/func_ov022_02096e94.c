#pragma thumb on

/* Ov022_ApplyMissionLevelStats -- give an actor the stat line its mission
 * level earns, once per mission.
 *
 * The actor always takes the character's level-zero row first: that row's
 * nStatC is latched as the actor's base figure, and the mission member's own
 * stored HP maximum becomes the actor's, which packed parameter 0x42 can force
 * to one.
 *
 * The rest runs only while the mission flag is still clear, and only when there
 * is a level to apply: the session level, while the member's tally still
 * reaches it, or half the tally for an actor carrying the marked flag. The
 * member's bonus -- its stored row minus the row its own tally earns -- is then
 * added to the row one level below; every figure floors at zero except the HP
 * maximum, which floors at one. The result is written back over the member's
 * stored row, becomes the actor's HP maximum again, and the mission flag is set
 * so the bonus cannot be applied twice.
 *
 * The member's address is spelled as a byte offset held in nIndex, and nIndex
 * is then reused for the level index: that is what leaves the out-row address
 * in place before the table lookup, as the original does.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

#define FLAGS_RESCALE 0x8000000000ULL   /* bit 39: rescale to half the tally */
#define MODE_MISSION 2
#define PARAM_FORCE_ONE 0x42
#define BONUS_FLAG 0x20ec

/* One row of a character's stat table: one row per level, 16 bytes each. */
struct StatRow {
    u16 nStatA;                      /* 0x00 */
    u16 nStatB;                      /* 0x02 */
    u16 nStatC;                      /* 0x04 */
    u16 nHpMax;                      /* 0x06 */
    u16 nStatE;                      /* 0x08 */
    u16 pad0a;
    int nStatWord;                   /* 0x0c */
};

struct MissionMember {
    u8 pad00[2];
    u8 nTally;                       /* 0x02: the level this member has earned */
    u8 pad03[5];
    struct StatRow row;              /* 0x08: the member's own stored row */
    u8 pad018[0xec];
};

struct Ov022Actor {
    u64 nFlags;                      /* 0x0000 */
    u8 pad008;
    u8 nId;                          /* 0x0009: index into the member table */
    u8 pad00a[2];
    int nCharacterId;                /* 0x000c */
    u8 pad010[4];
    u16 nBaseStatC;                  /* 0x0014 */
    u16 nHpMax;                      /* 0x0016 */
};

extern struct MissionMember data_0204c678[];   /* the mission member table */
extern u8 data_0204c240;                       /* mode and day clock */
extern u16 data_0204c254[];                    /* panel thresholds */
extern struct StatRow data_0204c680;           /* member 0's stored row */

/* StatTable_GetLevelRow */
extern void func_02035730(int nCharacterId, int nLevel, struct StatRow *pRow);
/* Slot_EvalPackedParam */
extern unsigned int func_020358f4(int nId, int nKey);
/* GameState_IsFlagSet / GameState_SetFlag */
extern int func_02023588(int nFlag);
extern void func_020235a8(int nFlag);

void func_ov022_02096e94(struct Ov022Actor *pActor)
{
    struct StatRow rowAtTally;
    struct StatRow rowBelow;
    struct MissionMember *pMember;
    struct StatRow *pRow;
    int nLevel;
    int nSessionLevel;
    int nIndex;
    int nBonusA;
    int nBonusB;
    int nBonusC;
    int nBonusD;
    int nBonusE;
    int nBonusF;
    int nValue;

    nLevel = -1;
    func_02035730(pActor->nCharacterId, 0, &rowAtTally);
    pActor->nBaseStatC = rowAtTally.nStatC;
    pMember = &data_0204c678[pActor->nId];
    pActor->nHpMax = pMember->row.nHpMax;
    if (func_020358f4(pActor->nId, PARAM_FORCE_ONE) != 0) {
        pActor->nHpMax = 1;
    }
    if (func_02023588(BONUS_FLAG) == 0) {
    if ((data_0204c240 & MODE_MISSION) != 0 && data_0204c254[1] != 0) {
        nSessionLevel = data_0204c254[1];
        nLevel = nSessionLevel;
        pMember = &data_0204c678[pActor->nId];
        if (pMember->nTally <= nSessionLevel - 1) {
            nLevel = -1;
        }
    }
    if ((pActor->nFlags & FLAGS_RESCALE) != 0) {
        pMember = &data_0204c678[pActor->nId];
        nLevel = (unsigned int)pMember->nTally >> 1;
        if (nLevel < 1) {
            nLevel = -1;
        }
    }
    if (nLevel > 0) {
    nIndex = pActor->nId * sizeof(struct MissionMember);
    pMember = (struct MissionMember *)((u8 *)data_0204c678 + nIndex);
    pRow = &pMember->row;
    func_02035730(pActor->nCharacterId, pMember->nTally, &rowAtTally);
    nBonusA = pMember->row.nStatA - rowAtTally.nStatA;
    nBonusB = pRow->nStatB - rowAtTally.nStatB;
    nBonusC = pRow->nStatC - rowAtTally.nStatC;
    nBonusD = pRow->nHpMax - rowAtTally.nHpMax;
    nBonusE = pRow->nStatE - rowAtTally.nStatE;
    nBonusF = pRow->nStatWord - rowAtTally.nStatWord;
    nIndex = nLevel - 1;
    if (nIndex < 0) {
        nIndex = 0;
    }
    func_02035730(pActor->nCharacterId, nIndex, &rowBelow);
    nValue = nBonusA + rowBelow.nStatA;
    if (nValue <= 0) {
        nValue = 0;
    }
    rowBelow.nStatA = (u16)nValue;
    nValue = nBonusB + rowBelow.nStatB;
    if (nValue <= 0) {
        nValue = 0;
    }
    rowBelow.nStatB = (u16)nValue;
    nValue = nBonusC + rowBelow.nStatC;
    if (nValue <= 0) {
        nValue = 0;
    }
    rowBelow.nStatC = (u16)nValue;
    nValue = nBonusD + rowBelow.nHpMax;
    if (nValue <= 0) {
        nValue = 1;
    }
    rowBelow.nHpMax = (u16)nValue;
    nValue = nBonusE + rowBelow.nStatE;
    if (nValue <= 0) {
        nValue = 0;
    }
    rowBelow.nStatE = (u16)nValue;
    nValue = nBonusF + rowBelow.nStatWord;
    if (nValue <= 0) {
        nValue = 0;
    }
    rowBelow.nStatWord = nValue;
    *(struct StatRow *)((u8 *)&data_0204c680
                        + pActor->nId * sizeof(struct MissionMember)) = rowBelow;
    pActor->nHpMax = rowBelow.nHpMax;
    if (func_020358f4(pActor->nId, PARAM_FORCE_ONE) != 0) {
        pActor->nHpMax = 1;
    }
    func_020235a8(BONUS_FLAG);
    }
    }
}
