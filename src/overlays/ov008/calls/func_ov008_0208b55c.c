/* func_ov008_0208b55c -- Ov008_FindNewlyEarnedReward: scan the two reward
 * lists (param table entries 3 and 4, 0x34-byte records) for the first reward
 * that is not yet flagged (game flag 0x8db + 0x28 * list + index), whose item
 * (when set) has a non-zero parameter word, whose rank requirement (+0x10) is
 * within the player's rank (GameState field 0x44e) and whose price (+0x8) is
 * covered by the matching reward total (0x196a for list 0, 0x1968 for list 1).
 * That reward's flag is set, its bit is cleared from the game state's unlock
 * summary word (indices below 32) and the record is returned; 0 when none.
 * Codegen: the inner counter is a plain int (a u32 with (int) casts keeps
 * its original register and rotates four callee-saved names) and the flag
 * base is declared after it; the per-list total is read inline from the
 * stack array so the compiler hoists it itself.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define LIST_COUNT       2
#define LIST_FIRST       3
#define FLAG_REWARD_BASE 0x8db
#define FLAGS_PER_LIST   0x28
#define FIELD_RANK       0x44e
#define SUMMARY_BITS     0x20

typedef struct Ov008ItemDef {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
} Ov008ItemDef;

typedef struct Ov008RewardRecord {
    u8            pad_00[8];
    u32           nPrice;       /* 0x08 */
    Ov008ItemDef *pItemDef;     /* 0x0c */
    u16           nLevel;       /* 0x10: rank required */
    u8            pad_12[0x34 - 0x12];
} Ov008RewardRecord;

typedef struct Ov008ParamTable {
    u32                aCount[5];        /* 0x00 */
    Ov008RewardRecord *apRecords[5];     /* 0x14 */
} Ov008ParamTable;

typedef struct GameState {
    u8  pad_0000[0x1160];
    u32 aUnlockSummary[LIST_COUNT];       /* 0x1160 */
    u8  pad_1168[0x1968 - 0x1168];
    u16 mode8RewardTotal;     /* 0x1968 */
    u16 otherRewardTotal;     /* 0x196a */
} GameState;

extern GameState *data_0204be18;
extern Ov008ParamTable *data_ov008_02090fb0;
extern u32  func_020235d0(int nField, int nBits);                       /* GameState_GetField */
extern int  func_02023588(int nFlag);                                   /* GameState_IsFlagSet */
extern void func_020235a8(int nFlag);                                   /* GameState_SetFlag */
extern int  func_ov008_0208a55c(int nItemId);                           /* Ov008_GetItemParamWord */
extern void func_02025668(void *pBits, u32 nBit);                       /* BitArray_ClearBit */

Ov008RewardRecord *func_ov008_0208b55c(void)
{
    u16 nRank;
    int i;
    u16 aTotal[LIST_COUNT];
    int nList;
    int j;
    int nFlagBase;
    Ov008RewardRecord *pRecord;

    nRank = func_020235d0(FIELD_RANK, 3);
    i = 0;
    aTotal[0] = data_0204be18->otherRewardTotal;
    aTotal[1] = data_0204be18->mode8RewardTotal;
    nFlagBase = FLAG_REWARD_BASE;
    do {
        nList = i + LIST_FIRST;
        for (j = 0; j < data_ov008_02090fb0->aCount[nList]; j++) {
            if (func_02023588(nFlagBase + j) == 0
                && (data_ov008_02090fb0->apRecords[nList][j].pItemDef == 0
                    || func_ov008_0208a55c(data_ov008_02090fb0->apRecords[nList][j].pItemDef->nItemId) != 0)) {
                pRecord = &data_ov008_02090fb0->apRecords[nList][j];
                if (pRecord->nLevel <= nRank && pRecord->nPrice <= aTotal[i]) {
                    func_020235a8(nFlagBase + j);
                    if (j < SUMMARY_BITS) {
                        func_02025668(&data_0204be18->aUnlockSummary[i], j);
                    }
                    return &data_ov008_02090fb0->apRecords[nList][j];
                }
            }
        }
        nFlagBase += FLAGS_PER_LIST;
        i++;
    } while (i < LIST_COUNT);
    return 0;
}
