/* func_ov008_0208a91c -- Ov008_BuildShopList: collect the shop records listed
 * for page nSlot under the category filter nCategory (Ov008_IsShopRecordShown,
 * 0208a764) into the table's sorted pointer array (+0x38): count them, then
 * (unless none) free the old array, allocate one pointer per listed record
 * and fill it.  Each listed record's price (+0x8) restarts from its base
 * (+0x10); a record with a divisor (+0x26), exponent (+0x14) and price cap
 * (+0x18) gets the level-scaled price (Ov008_ComputeRecordPrice) capped;
 * its "reached" word (+0x28) is set when it has a level requirement (+0x20)
 * met by the level slot (+0x4) in the game state (0x1168 + 2 * slot).  The
 * count goes to *pCount; returns the array (0 when empty).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008ParamRecord {
    u8  pad_00[4];
    int nLevelField;          /* 0x04 */
    u32 nPrice;               /* 0x08 */
    u8  pad_0c[4];
    u32 nBasePrice;           /* 0x10 */
    int nExponent;            /* 0x14 */
    u32 nMaxPrice;            /* 0x18 */
    u8  pad_1c[4];
    u32 nLevelReq;            /* 0x20 */
    u8  pad_24[2];
    u8  nDivisor;             /* 0x26 */
    u8  pad_27;
    int bLevelReached;        /* 0x28 */
    u8  pad_2c[0x34 - 0x2c];
} Ov008ParamRecord;

typedef struct Ov008ParamTable {
    u8  pad_00[4];
    u32 nShopCount;           /* 0x04 */
    u8  pad_08[0x18 - 0x8];
    Ov008ParamRecord *pShopRecords; /* 0x18 */
    u8  pad_1c[0x38 - 0x1c];
    Ov008ParamRecord **apSorted;    /* 0x38 */
} Ov008ParamTable;

typedef struct GameState {
    u8  pad_0000[0x1168];
    u16 aLevel[1];            /* 0x1168 */
} GameState;

extern Ov008ParamTable *data_ov008_02090fb0;
extern GameState *data_0204be18;
extern int  func_ov008_0208a764(int nSlot, int nCategory, u32 nIndex);   /* Ov008_IsShopRecordShown */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);                /* AllocDefault */
extern u32  func_ov008_02089dc4(int nIndex);                            /* Ov008_ComputeRecordPrice */

Ov008ParamRecord **func_ov008_0208a91c(int nSlot, int nCategory, int *pCount)
{
    int nListed = 0;
    u32 i;
    int nOut;
    Ov008ParamRecord *pRecord;
    int bReached;

    for (i = 0; i < data_ov008_02090fb0->nShopCount; i++) {
        if (func_ov008_0208a764(nSlot, nCategory, i) != 0) {
            nListed++;
        }
    }
    if (nListed == 0) {
        *pCount = 0;
        return 0;
    }
    if (data_ov008_02090fb0->apSorted != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov008_02090fb0->apSorted);
        data_ov008_02090fb0->apSorted = 0;
    }
    data_ov008_02090fb0->apSorted = NNSi_FndAllocFromDefaultExpHeap(nListed * sizeof(Ov008ParamRecord *));
    nOut = 0;
    for (i = 0; i < data_ov008_02090fb0->nShopCount; i++) {
        if (func_ov008_0208a764(nSlot, nCategory, i) != 0) {
            pRecord = &data_ov008_02090fb0->pShopRecords[i];
            data_ov008_02090fb0->apSorted[nOut] = pRecord;
            pRecord->nPrice = pRecord->nBasePrice;
            if (pRecord->nDivisor != 0 && pRecord->nExponent != 0 && pRecord->nMaxPrice != 0) {
                pRecord->nPrice = func_ov008_02089dc4(nOut);
                if (pRecord->nPrice > pRecord->nMaxPrice) {
                    pRecord->nPrice = pRecord->nMaxPrice;
                }
            }
            bReached = 0;
            if (pRecord->nLevelReq != 0 && data_0204be18->aLevel[pRecord->nLevelField] >= pRecord->nLevelReq) {
                bReached = 1;
            }
            pRecord->bLevelReached = bReached != 0;
            nOut++;
        }
    }
    *pCount = nOut;
    return data_ov008_02090fb0->apSorted;
}
