/* func_ov008_0208b368 -- Ov008_QueryRecordUnlock: unlock state of record
 * nIndex of a record pointer list, optionally marking it pending first.
 * Shop / item-list / recipe records (kind != 3) use the param table's two
 * pending / committed bit arrays (list 1 for recipes, 0 otherwise) at the
 * record's bit index (+0x4).  Reward records (kind 3) are done once the game
 * flag 0x8db + 0x28 * list + index is set (returns 2); otherwise they use the
 * table's pending summary words and the game state's unlock summary words
 * (bit index & 0x1f).  Returns bit 0 = pending, bit 1 = unlocked.  The bSet
 * argument is reused for the pending bit on the way out.
 * NOTE: compiled with #pragma opt_lifetimes off (push/pop scoped): the ROM keeps
 * one register web per variable across both branches (nList r5, nBit r4); with
 * lifetime splitting the reward branch colours them the other way round.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define RECORD_KIND_RECIPE 2
#define RECORD_KIND_REWARD 3
#define FLAG_REWARD_BASE   0x8db
#define FLAGS_PER_LIST     0x28
#define BIT_ARRAY_COUNT    2

typedef struct Ov008ParamRecord {
    int nKind;                /* 0x00 */
    u32 nUnlockBit;           /* 0x04 */
} Ov008ParamRecord;

typedef struct Ov008RewardRecord {
    int nKind;                /* 0x00 */
    u16 nIndex;               /* 0x04 */
    u16 nRewardList;          /* 0x06: 0 = db 0x18 list, 1 = db 0x17 list */
} Ov008RewardRecord;

typedef struct Ov008ParamTable {
    u8   pad_0000[0x28];
    u32 *apPendingBits[BIT_ARRAY_COUNT];   /* 0x28 */
    u32 *apUnlockBits[BIT_ARRAY_COUNT];    /* 0x30 */
    u8   pad_0038[0x13c - 0x38];
    u32  aPendingSummary[BIT_ARRAY_COUNT]; /* 0x13c */
} Ov008ParamTable;

typedef struct GameState {
    u8  pad_0000[0x1160];
    u32 aUnlockSummary[BIT_ARRAY_COUNT];   /* 0x1160 */
} GameState;

extern Ov008ParamTable *data_ov008_02090fb0;
extern GameState *data_0204be18;
extern void func_02025640(void *pBits, u32 nBit);                        /* BitArray_SetBit */
extern int  func_02025694(void *pBits, u32 nBit);                        /* BitArray_TestBit */
extern int  func_02023588(int nFlag);                                    /* GameState_IsFlagSet */

#pragma push
#pragma opt_lifetimes off
u32 func_ov008_0208b368(Ov008ParamRecord **apRecords, int nIndex, u32 bSet)
{
    Ov008ParamRecord *pRecord;
    Ov008RewardRecord *pReward;
    u32 nList;
    u32 nBit;

    pRecord = apRecords[nIndex];
    if (pRecord->nKind != RECORD_KIND_REWARD) {
        nList = pRecord->nKind == RECORD_KIND_RECIPE;
        nBit = pRecord->nUnlockBit;
        if (bSet != 0) {
            func_02025640(data_ov008_02090fb0->apPendingBits[nList], nBit);
        }
        bSet = func_02025694(data_ov008_02090fb0->apPendingBits[nList], nBit) != 0;
        return bSet | (func_02025694(data_ov008_02090fb0->apUnlockBits[nList], nBit) != 0) << 1;
    }
    pReward = (Ov008RewardRecord *)pRecord;
    nList = pReward->nRewardList;
    nBit = pReward->nIndex;
    if (func_02023588(nList * FLAGS_PER_LIST + FLAG_REWARD_BASE + nBit) != 0) {
        return 2;
    }
    nBit &= 0x1f;
    if (bSet != 0) {
        func_02025640(&data_ov008_02090fb0->aPendingSummary[nList], nBit);
    }
    bSet = func_02025694(&data_ov008_02090fb0->aPendingSummary[nList], nBit) != 0;
    return bSet | (func_02025694(&data_0204be18->aUnlockSummary[nList], nBit) != 0) << 1;
}

#pragma pop
