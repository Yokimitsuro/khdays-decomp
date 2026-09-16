/* NOT MATCHING -- 269 of 300 bytes, 66 of 75 instructions aligned.
 *
 * Exact size, exact instruction count and exact relocations. The residue is one
 * register swap in the loop: the ROM keeps the counter in r8 and the record
 * byte-offset induction variable in sl; build 139 colours them the other way
 * round (this source, with an explicit `nOffset += sizeof(record)` declared
 * before nKind in a guarded do-while, already gives nKind its ROM register sb
 * and the preheader copy -- the plain for-loop form also rotates nKind).
 *
 * The matched shop-list twin Ov008_BuildShopList (0208a91c) has the same loop
 * shape and build 139 colours its induction variable below the counter there,
 * exactly as that ROM function; this function's ROM wants the counter below.
 *
 * Swept: 1800 + 1920 + 960 + 720 declaration-order cells crossed with the
 * counter / kind / count / rank types and the rank cast, explicit offset
 * variables (compound and plain, pointer-typed, initialised before / inside the
 * guard, block- and for-scoped), the nList parameter reused as counter or
 * offset, real pre-loop uses of the counter, dead loop-carried dummies,
 * register hints (186), callee prototype / return types, argument casts, 49
 * optimisation pragmas, the C++ lane, a 2400-cell random cross product over 16
 * axes, and every mwccarm build in tools/mwccarm. Left for decomp.me.
 */
/* func_ov008_0208af90 -- Ov008_BuildRewardList: rebuild the table's sorted
 * pointer array (+0x38) for reward list nList (param table entries 3 + nList):
 * free the old array, allocate one pointer per record and fill it with
 * pointers into the list's 0x34-byte records, marking each record locked
 * (+0x20 = 1) when its rank requirement (+0x10) is above the player's rank
 * (GameState field 0x44e, 3 bits) or its item (+0xc, when set) has a zero
 * parameter word; otherwise unlocked.  The count goes to *pCount; returns the
 * array.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define FIELD_RANK 0x44e
#define LIST_FIRST 3

typedef struct Ov008ItemDef {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
} Ov008ItemDef;

typedef struct Ov008RewardRecord {
    u8            pad_00[0xc];
    Ov008ItemDef *pItemDef;     /* 0x0c */
    u16           nLevel;       /* 0x10: rank required */
    u8            pad_12[0x20 - 0x12];
    int           bLocked;      /* 0x20 */
    u8            pad_24[0x34 - 0x24];
} Ov008RewardRecord;

typedef struct Ov008ParamTable {
    u32                 aCount[5];      /* 0x00 */
    Ov008RewardRecord  *apRecords[5];   /* 0x14 */
    u8                  pad_28[0x38 - 0x28];
    Ov008RewardRecord **apSorted;       /* 0x38 */
} Ov008ParamTable;

extern Ov008ParamTable *data_ov008_02090fb0;
extern u32  func_020235d0(int nField, int nBits);                       /* GameState_GetField */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);                /* AllocDefault */
extern int  func_ov008_0208a55c(int nItemId);                           /* Ov008_GetItemParamWord */

Ov008RewardRecord **func_ov008_0208af90(int nList, u32 *pCount)
{
    u32 nOffset;
    int nKind;
    u16 nRank;
    u32 i;
    u32 nCount;
    Ov008RewardRecord *pRecord;

    nKind = nList + LIST_FIRST;
    nRank = func_020235d0(FIELD_RANK, 3);
    if (data_ov008_02090fb0->apSorted != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov008_02090fb0->apSorted);
        data_ov008_02090fb0->apSorted = 0;
    }
    data_ov008_02090fb0->apSorted = NNSi_FndAllocFromDefaultExpHeap(data_ov008_02090fb0->aCount[nKind] * sizeof(Ov008RewardRecord *));
    nOffset = 0;
    i = 0;
    if (i < (nCount = data_ov008_02090fb0->aCount[nKind])) {
        do {
            data_ov008_02090fb0->apSorted[i] = (Ov008RewardRecord *)((u8 *)data_ov008_02090fb0->apRecords[nKind] + nOffset);
            pRecord = (Ov008RewardRecord *)((u8 *)data_ov008_02090fb0->apRecords[nKind] + nOffset);
            if (pRecord->nLevel <= nRank
                && (pRecord->pItemDef == 0 || func_ov008_0208a55c(pRecord->pItemDef->nItemId) != 0)) {
                data_ov008_02090fb0->apSorted[i]->bLocked = 0;
            } else {
                data_ov008_02090fb0->apSorted[i]->bLocked = 1;
            }
            nOffset += sizeof(Ov008RewardRecord);
            i++;
        } while (i < (nCount = data_ov008_02090fb0->aCount[nKind]));
    }
    *pCount = nCount;
    return data_ov008_02090fb0->apSorted;
}
