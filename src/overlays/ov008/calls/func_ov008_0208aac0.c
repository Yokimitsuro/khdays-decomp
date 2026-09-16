/* func_ov008_0208aac0 -- Ov008_BuildSellList: collect the sell records
 * (table +0x14, count +0x0) the player can sell under category nCategory
 * (-1 = all) into the table's sorted pointer array (+0x38).  The owned
 * counts of item ids 1.. (GameState 0x811) are copied into a heap buffer;
 * a record qualifies when its copy is owned, its item is sellable
 * (0208a5e8) and, with a category filter, the item's category (+0x18)
 * matches.  The count goes to *pCount; with none the array is not touched
 * and 0 returned.  Otherwise the old array is freed, one pointer per record
 * allocated and filled, the owned copy freed and the array sorted by item
 * order (Ov008_SortParamRecordsByItemOrder).  Returns the array.
 * Codegen: the listed count and the loop counter are u32 (the counter is
 * shared by both loops) and the owned buffer is declared after the output
 * index -- that declaration order is what gives the buffer r6 above the
 * table address r5.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define CATEGORY_ANY (-1)

typedef struct Ov008ItemDef {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    int nCategory;            /* 0x18 */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8  pad_00[0xc];
    Ov008ItemDef *pItemDef;   /* 0x0c */
    u8  pad_10[0x34 - 0x10];
} Ov008ParamRecord;

typedef struct Ov008ParamTable {
    u32 nSellCount;           /* 0x00 */
    u8  pad_04[0x14 - 0x4];
    Ov008ParamRecord *pSellRecords; /* 0x14 */
    u8  pad_18[0x38 - 0x18];
    Ov008ParamRecord **apSorted;    /* 0x38 */
} Ov008ParamTable;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern Ov008ParamTable *data_ov008_02090fb0;
extern GameState *data_0204be18;
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);                /* AllocDefault */
extern void  MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);
extern int   func_ov008_0208a5e8(int nItemId);                          /* item is sellable */
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void  func_ov008_0208a4b0(Ov008ParamRecord **apRecords, int nCount); /* Ov008_SortParamRecordsByItemOrder */

Ov008ParamRecord **func_ov008_0208aac0(int nCategory, int *pCount)
{
    u32 nListed;
    u32 i;
    int nOut;
    u8 *aOwned;
    Ov008ParamRecord *pRecord;

    aOwned = NNSi_FndAllocFromDefaultExpHeap(data_ov008_02090fb0->nSellCount);
    MI_CpuCopy8(&data_0204be18->aItemCount[1], aOwned, data_ov008_02090fb0->nSellCount);
    nListed = 0;
    for (i = 0; i < data_ov008_02090fb0->nSellCount; i++) {
        if (aOwned[i] != 0 && func_ov008_0208a5e8(data_ov008_02090fb0->pSellRecords[i].pItemDef->nItemId) != 0
            && (nCategory == CATEGORY_ANY || nCategory == data_ov008_02090fb0->pSellRecords[i].pItemDef->nCategory)) {
            nListed++;
        }
    }
    *pCount = nListed;
    if (nListed == 0) {
        return 0;
    }
    if (data_ov008_02090fb0->apSorted != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov008_02090fb0->apSorted);
        data_ov008_02090fb0->apSorted = 0;
    }
    data_ov008_02090fb0->apSorted = NNSi_FndAllocFromDefaultExpHeap(nListed * sizeof(Ov008ParamRecord *));
    nOut = 0;
    for (i = 0; i < data_ov008_02090fb0->nSellCount; i++) {
        if (aOwned[i] != 0 && func_ov008_0208a5e8(data_ov008_02090fb0->pSellRecords[i].pItemDef->nItemId) != 0
            && (nCategory == CATEGORY_ANY || nCategory == data_ov008_02090fb0->pSellRecords[i].pItemDef->nCategory)) {
            data_ov008_02090fb0->apSorted[nOut] = &data_ov008_02090fb0->pSellRecords[i];
            nOut++;
        }
    }
    NNSi_FndFreeFromDefaultHeap(aOwned);
    func_ov008_0208a4b0(data_ov008_02090fb0->apSorted, nListed);
    return data_ov008_02090fb0->apSorted;
}
