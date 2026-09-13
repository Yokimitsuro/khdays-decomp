/* func_ov008_0208a640 -- Ov008_IsShopRecordListed: whether shop record pRecord
 * is offered in shop page nSlot under the category filter nCategory (-1 = all).
 * The record's day (+0x24) must not exceed the page's day cap
 * (data_ov008_0208ff78[nSlot]); day 0 and the final day (0x165) are only listed
 * when the table's show-all flag is on.  The tier byte (+0x27) is 0 or
 * (tier + 1) against GameState field 0x40a, the item category must match, and
 * when the record names a prerequisite level slot (+0x1c != -1) that level
 * (GameState 0x1168 + 2 * slot) must reach the required value (+0x20) of the
 * record at that slot.  Returns 1 when listed.  nIndex (the record's index,
 * passed by Ov008_IsShopRecordShown) is unused.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define CATEGORY_ANY   -1
#define DAY_FINAL      0x165
#define NO_PREREQ      -1
#define FIELD_TIER     0x40a

typedef struct Ov008ItemDef {
    u8  pad_00[0x18];
    int nCategory;            /* 0x18 */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8            pad_00[0xc];
    Ov008ItemDef *pItemDef;     /* 0x0c */
    u8            pad_10[0xc];
    int           nPrereqSlot;  /* 0x1c: level slot that gates this record, or -1 */
    u32           nLevelReq;    /* 0x20: level the prerequisite slot must reach */
    u16           nDay;         /* 0x24 */
    u8            pad_26;
    u8            nTierReq;     /* 0x27: 0 = any, else tier + 1 */
    u8            pad_28[0xc];
} Ov008ParamRecord;

typedef struct Ov008ParamTable {
    u8                pad_00[0x18];
    Ov008ParamRecord *pShopRecords;    /* 0x18 */
    u8                pad_1c[0x128];
    int               bShowAll;        /* 0x144 */
} Ov008ParamTable;

typedef struct GameState {
    u8  pad_0000[0x1168];
    u16 aLevel[1];            /* 0x1168 */
} GameState;

extern const u16 data_ov008_0208ff78[];                                 /* day cap per shop page */
extern Ov008ParamTable *data_ov008_02090fb0;
extern GameState *data_0204be18;
extern int func_020235d0(int nField, int nBits);                       /* GameState_GetField */

int func_ov008_0208a640(Ov008ParamRecord *pRecord, int nSlot, int nCategory, u32 nIndex)
{
    u32 nDay;
    u32 nCap;
    int nPrereq;
    int nListed;
    int bDayOk;
    int bCategoryOk;
    int bTierOk;
    int bOk;

    nDay = pRecord->nDay;
    nListed = 0;
    nCap = data_ov008_0208ff78[nSlot];
    bCategoryOk = 0;
    bTierOk = 0;
    bDayOk = 0;
    if (nDay <= nCap) {
        if ((nDay != 0 && nDay != DAY_FINAL) || data_ov008_02090fb0->bShowAll != 0) {
            bDayOk = 1;
        }
    }
    if (bDayOk) {
        if (pRecord->nTierReq == 0 || pRecord->nTierReq - 1 == func_020235d0(FIELD_TIER, 2)) {
            bTierOk = 1;
        }
    }
    if (bTierOk) {
        if (nCategory == CATEGORY_ANY || nCategory == pRecord->pItemDef->nCategory) {
            bCategoryOk = 1;
        }
    }
    if (bCategoryOk) {
        bOk = 1;
        nPrereq = pRecord->nPrereqSlot;
        if (nPrereq != NO_PREREQ
            && data_0204be18->aLevel[nPrereq] < data_ov008_02090fb0->pShopRecords[nPrereq].nLevelReq) {
            bOk = 0;
        }
        if (bOk) {
            nListed = 1;
        }
    }
    return nListed;
}
