/* func_ov008_0208af90 -- list the records of shop tier nTier (count table +0x0 and record table
 * +0x14, indexed from slot 3) into the sorted pointer array (+0x38): the old array is freed, one
 * pointer per record allocated, and each record is marked locked (+0x20 = 1) when its required
 * level (+0x10) is above the player's (GameState field 0x44e, 3 bits) or its item (+0xc) fails
 * 0208a55c; the count goes to *pCount and the array is returned. */
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov008ItemDef {
    char pad_00[0x14];
    int nItemId;                    /* 0x14 */
} Ov008ItemDef;

typedef struct Ov008ShopRecord {
    char pad_00[0xc];
    Ov008ItemDef *pItemDef;         /* 0x0c */
    u16 nLevel;                     /* 0x10 */
    char pad_12[0x20 - 0x12];
    int bLocked;                    /* 0x20 */
    char pad_24[0x34 - 0x24];
} Ov008ShopRecord;

typedef struct Ov008ShopTable {
    u32 anCount[5];                 /* 0x00 */
    Ov008ShopRecord *apRecords[9];  /* 0x14 */
    Ov008ShopRecord **apSorted;     /* 0x38 */
} Ov008ShopTable;

extern Ov008ShopTable *data_ov008_02090fb0;
extern u32 func_020235d0(int nField, int nBits);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern int func_ov008_0208a55c(int nItemId);

Ov008ShopRecord **func_ov008_0208af90(int nTier, u32 *pCount)
{
    unsigned long i;
    int slot = nTier + 3;
    u16 nLevel = func_020235d0(0x44e, 3);
    u32 n;

    if (data_ov008_02090fb0->apSorted != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov008_02090fb0->apSorted);
        data_ov008_02090fb0->apSorted = 0;
    }
    data_ov008_02090fb0->apSorted = NNSi_FndAllocFromDefaultExpHeap(data_ov008_02090fb0->anCount[slot] << 2);
    for (i = 0; i < (n = data_ov008_02090fb0->anCount[slot]); i++) {
        data_ov008_02090fb0->apSorted[i] = &data_ov008_02090fb0->apRecords[slot][i];
        if (data_ov008_02090fb0->apRecords[slot][i].nLevel <= nLevel &&
            (data_ov008_02090fb0->apRecords[slot][i].pItemDef == 0 ||
             func_ov008_0208a55c(data_ov008_02090fb0->apRecords[slot][i].pItemDef->nItemId) != 0)) {
            data_ov008_02090fb0->apSorted[i]->bLocked = 0;
        } else {
            data_ov008_02090fb0->apSorted[i]->bLocked = 1;
        }
    }
    *pCount = n;
    return data_ov008_02090fb0->apSorted;
}
