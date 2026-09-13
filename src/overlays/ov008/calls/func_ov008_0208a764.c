/* func_ov008_0208a764 -- Ov008_IsShopRecordShown: whether shop record nIndex
 * appears on page nSlot under category nCategory.  Its item must have a
 * non-zero parameter word and the record itself must be listed
 * (Ov008_IsShopRecordListed).  A record that shares its item with the NEXT
 * record hides while that one is listed, unless it has a level requirement
 * (+0x20) already met by its record id (+0x4, GameState 0x1168); a record
 * that shares its item with the PREVIOUS record shows only when the previous
 * one has a level requirement already met.  Returns 1 / 0.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008ItemDef {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8            pad_00[4];
    int           nUnlockBit;  /* 0x04: record id; also indexes GameState aLevel */
    u8            pad_08[4];
    Ov008ItemDef *pItemDef;     /* 0x0c */
    u8            pad_10[0x10];
    u32           nLevelReq;    /* 0x20 */
    u8            pad_24[0x34 - 0x24];
} Ov008ParamRecord;

typedef struct Ov008ParamTable {
    u8  pad_00[4];
    u32 nShopCount;           /* 0x04 */
    u8  pad_08[0x18 - 0x8];
    Ov008ParamRecord *pShopRecords; /* 0x18 */
} Ov008ParamTable;

typedef struct GameState {
    u8  pad_0000[0x1168];
    u16 aLevel[1];            /* 0x1168 */
} GameState;

extern Ov008ParamTable *data_ov008_02090fb0;
extern GameState *data_0204be18;
extern int func_ov008_0208a55c(int nItemId);                            /* Ov008_GetItemParamWord */
extern int func_ov008_0208a640(Ov008ParamRecord *pRecord, int nSlot, int nCategory, u32 nIndex); /* Ov008_IsShopRecordListed */

int func_ov008_0208a764(int nSlot, int nCategory, u32 nIndex)
{
    Ov008ParamRecord *pRecords;
    Ov008ParamRecord *pRecord;
    Ov008ParamRecord *pNext;
    Ov008ParamRecord *pPrev;
    int nShown;
    int bPassB;
    int bPassA;
    int bOk;
    int bNextHidden;
    int bReached;

    pRecords = data_ov008_02090fb0->pShopRecords;
    pRecord = &pRecords[nIndex];
    pNext = nIndex < data_ov008_02090fb0->nShopCount - 1 ? &pRecords[nIndex + 1] : 0;
    pPrev = (int)nIndex > 0 ? &pRecords[nIndex - 1] : 0;
    nShown = 0;
    if (func_ov008_0208a55c(pRecord->pItemDef->nItemId) != 0) {
        bPassB = 0;
        bPassA = 0;
        if (func_ov008_0208a640(pRecord, nSlot, nCategory, nIndex) != 0) {
            bOk = 1;
            bNextHidden = 1;
            if (nIndex != data_ov008_02090fb0->nShopCount - 1
                && pRecord->pItemDef->nItemId == pNext->pItemDef->nItemId) {
                bReached = 0;
                if (pRecord->nLevelReq != 0
                    && data_0204be18->aLevel[pRecord->nUnlockBit] >= pRecord->nLevelReq) {
                    bReached = 1;
                }
                if (bReached) {
                    bNextHidden = 0;
                }
            }
            if (!bNextHidden && func_ov008_0208a640(pNext, nSlot, nCategory, nIndex) != 0) {
                bOk = 0;
            }
            if (bOk) {
                bPassA = 1;
            }
        }
        if (bPassA) {
            bOk = 1;
            if (nIndex != 0 && pRecord->pItemDef->nItemId == pPrev->pItemDef->nItemId) {
                bReached = 0;
                if (pPrev->nLevelReq != 0
                    && data_0204be18->aLevel[pPrev->nUnlockBit] >= pPrev->nLevelReq) {
                    bReached = 1;
                }
                if (!bReached) {
                    bOk = 0;
                }
            }
            if (bOk) {
                bPassB = 1;
            }
        }
        if (bPassB) {
            nShown = 1;
        }
    }
    return nShown;
}
