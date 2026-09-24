/* func_ov026_0208de40 -- list the records of shop tier nTier (count table +0x0 and record table
 * +0x14, indexed from slot 3) into the sorted pointer array (+0x38): the old array is freed, one
 * pointer per record allocated, and each record is marked locked (+0x20 = 1) when its required
 * level (+0x10) is above the player's (GameState field 0x44e, 3 bits) or its item (+0xc) fails
 * 0208d40c; the count goes to *pCount and the array is returned. */
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov026ItemDef {
    char pad_00[0x14];
    int nItemId;                    /* 0x14 */
} Ov026ItemDef;

typedef struct Ov026ShopRecord {
    char pad_00[0xc];
    Ov026ItemDef *pItemDef;         /* 0x0c */
    u16 nLevel;                     /* 0x10 */
    char pad_12[0x20 - 0x12];
    int bLocked;                    /* 0x20 */
    char pad_24[0x34 - 0x24];
} Ov026ShopRecord;

typedef struct Ov026ShopTable {
    u32 anCount[5];                 /* 0x00 */
    Ov026ShopRecord *apRecords[9];  /* 0x14 */
    Ov026ShopRecord **apSorted;     /* 0x38 */
} Ov026ShopTable;

extern Ov026ShopTable *data_ov026_0209136c;
extern u32 func_020235d0(int nField, int nBits);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern int func_ov026_0208d40c(int nItemId);

Ov026ShopRecord **func_ov026_0208de40(int nTier, u32 *pCount)
{
    unsigned long i;
    int slot = nTier + 3;
    u16 nLevel = func_020235d0(0x44e, 3);
    u32 n;

    if (data_ov026_0209136c->apSorted != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov026_0209136c->apSorted);
        data_ov026_0209136c->apSorted = 0;
    }
    data_ov026_0209136c->apSorted = NNSi_FndAllocFromDefaultExpHeap(data_ov026_0209136c->anCount[slot] << 2);
    for (i = 0; i < (n = data_ov026_0209136c->anCount[slot]); i++) {
        data_ov026_0209136c->apSorted[i] = &data_ov026_0209136c->apRecords[slot][i];
        if (data_ov026_0209136c->apRecords[slot][i].nLevel <= nLevel &&
            (data_ov026_0209136c->apRecords[slot][i].pItemDef == 0 ||
             func_ov026_0208d40c(data_ov026_0209136c->apRecords[slot][i].pItemDef->nItemId) != 0)) {
            data_ov026_0209136c->apSorted[i]->bLocked = 0;
        } else {
            data_ov026_0209136c->apSorted[i]->bLocked = 1;
        }
    }
    *pCount = n;
    return data_ov026_0209136c->apSorted;
}
