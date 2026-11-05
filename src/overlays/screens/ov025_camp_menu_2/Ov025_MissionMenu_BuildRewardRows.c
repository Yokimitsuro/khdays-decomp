/* Ov025_MissionMenu_BuildRewardRows -- Ov008_BuildMissionRows: fill the mission menu's
 * 13 text rows (+0x188, 0x48 each: an "available" word and a 33-glyph
 * UTF-16 text at +0x6) for the listed mission entry.  The mission's reward
 * record (db 0x19, the first of 0x67 whose +0x10 matches the entry's first
 * word) is copied to a local block; its five item words (+0x20, low
 * halves) become one row each -- item ids 2 .. 0x276 only -- with the item
 * name (db 0x15, +0xc) and an availability from the mission's status field
 * (0x28e4 + 3 * id: below 2 for slots 0 / 1, not 3 for slot 2, always for
 * the rest), after a first row holding variable text 0x22 when present.
 * Then a separator row (02090978) and a row with text 0x23 follow, and the
 * five bonus words (+0x34, ids 1 .. 0x1f) fetch db 0x1a records (0x54 bytes)
 * whose eight item pairs (+0x14, stride 8) append the item names not yet
 * listed, comma-separated (0209097c), opening a new unavailable row when the
 * joined text would pass 25 glyphs; the ids are remembered in a 40-entry
 * list.  A final separator row closes the list.  All row indices and
 * counters are u16 (the record scan index is u32); the menu pointer, the
 * bonus index and the row base are spilled.  Codegen: the record scan is a
 * do / while on the copied word; every row is reached through a row
 * pointer (the bonus loop uses its own, pDst, coloured before the pair
 * index: a shared pointer coloured last); the fetched record is copied to a
 * register local (pItem) for the length test; the two status tests are
 * bools negated in a second step; the seen-list search is a for loop.
 */

#include "nitro/types.h"

#define ROW_COUNT       13
#define ROW_TEXT_MAX    0x19
#define ITEM_ID_LIMIT   0x277
#define BONUS_ID_LIMIT  0x20
#define REWARD_RECORDS  0x67
#define SLOT_COUNT      5
#define BONUS_PAIRS     8
#define SEEN_MAX        40
#define FIELD_MISSION_STATUS 0x28e4
#define TEXT_HEADER     0x22
#define TEXT_FOOTER     0x23
#define DB_REWARD       0x19
#define DB_BONUS        0x1a
#define DB_ITEM         0x15
#define DB_SLOT         0xe

typedef struct Ov008MissionRow {
    int bAvailable;           /* 0x00 */
    u16 pad_04;
    u16 aText[0x21];          /* 0x06 */
} Ov008MissionRow;

typedef struct Ov008MissionMenu {
    u8  pad_000[0x188];
    Ov008MissionRow aRow[ROW_COUNT]; /* 0x188 */
    u8  pad_530[0x530 - 0x188 - ROW_COUNT * 0x48];
    u8  records[0xc];         /* 0x530: variable text records */
} Ov008MissionMenu;

typedef struct Ov008MissionRewardRecord {
    u8  pad_00[0x10];
    u32 nWord;                /* 0x10: matched against the entry's first word */
    u8  pad_14[0xc];
    u32 aItem[SLOT_COUNT];    /* 0x20: item id in the low half */
    u32 aBonus[SLOT_COUNT];   /* 0x34: bonus set id in the low half */
} Ov008MissionRewardRecord;

typedef struct Ov008BonusPair {
    u32 nItem;                /* 0x00: item id in the low half */
    u32 nCount;               /* 0x04 */
} Ov008BonusPair;

typedef struct Ov008BonusRecord {
    u8  pad_00[0x14];
    Ov008BonusPair aPair[BONUS_PAIRS]; /* 0x14 */
} Ov008BonusRecord;

typedef struct Ov008ItemRecord {
    u8   pad_00[0xc];
    u16 *pName;               /* 0x0c */
} Ov008ItemRecord;

typedef struct Ov008MissionListEntry {
    u16 nFileNumber;                /* 0x00: the mission's file (mi/mi/<number>) */
    u16 missionId;            /* 0x02 */
} Ov008MissionListEntry;

extern const u16 data_ov025_020b545c[];                                  /* separator row text */
extern const u16 data_ov025_020b5460[];                                  /* item name separator */
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern void  MIi_CpuCopy16(const void *pSrc, void *pDst, u32 nSize);
extern void  MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);
extern void  MsgDb_FetchRecord(void *ppRecord, int nDb, u32 nIndex, int nSlot); /* MsgDb_FetchRecord */
extern void  DispatchByNodeKind(void *ppRecord);                              /* release a raw db record */
extern u16  *Ov025_GetVarRecordByIndex(void *pRecords, int nIndex);            /* GetVarRecordByIndex */
extern void  STD_WStrCat(u16 *pDst, const u16 *pSrc);                  /* STD_WStrCat */
extern void  StrCopy16(u16 *pDst, const u16 *pSrc);                  /* StrCopy16 */
extern int   Wcslen(const u16 *pStr);                             /* Wcslen */
extern u32   GameState_GetField(int nField, int nBits);                       /* GameState_GetField */

void Ov025_MissionMenu_BuildRewardRows(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry)
{
    Ov008MissionRewardRecord reward;
    u16 aSeen[SEEN_MAX];
    Ov008BonusRecord bonus;
    Ov008MissionRewardRecord *pReward;
    Ov008ItemRecord *pRecItem;
    Ov008ItemRecord *pItem;
    Ov008BonusRecord *pBonus;
    Ov008ItemRecord *pItemB;
    Ov008MissionRow *pRows;
    u16 j;
    u32 i;
    u16 nRow;
    u16 nSeen;
    u16 k;
    u16 nItem;
    u16 *pText;
    Ov008MissionRow *pRow;
    Ov008MissionRow *pDst;
    u16 m;
    u16 nId;
    u16 n;
    int nLen;
    int nAdd;
    int bLocked;

    MI_CpuFill8(&reward, 0, sizeof(reward));
    i = 0;
    do {
        pReward = 0;
        MsgDb_FetchRecord(&pReward, DB_REWARD, i, DB_SLOT);
        if (pReward != 0) {
            if (pReward->nWord == pEntry->nFileNumber) {
                MIi_CpuCopy16(pReward, &reward, sizeof(reward));
            }
            DispatchByNodeKind(&pReward);
        }
    } while (reward.nWord == 0 && ++i < REWARD_RECORDS);
    MI_CpuFill8(pMenu->aRow, 0, sizeof(pMenu->aRow));
    nSeen = 0;
    nRow = 0;
    pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_HEADER);
    if (pText != 0) {
        pRow = &pMenu->aRow[0];
        pRow->aText[0] = 0;
        STD_WStrCat(pRow->aText, pText);
        pRow->bAvailable = 1;
        nRow++;
    }
    for (k = 0; k < SLOT_COUNT; k++) {
        nItem = reward.aItem[k];
        pRow = &pMenu->aRow[nRow];
        if (nItem == 0 || nItem >= ITEM_ID_LIMIT || nItem == 1) {
            continue;
        }
        pRow->aText[0] = 0;
        pRecItem = 0;
        MsgDb_FetchRecord(&pRecItem, DB_ITEM, nItem, DB_SLOT);
        if (pRecItem != 0) {
            StrCopy16(pRow->aText, pRecItem->pName);
            DispatchByNodeKind(&pRecItem);
        }
        switch (k) {
        case 0:
        case 1:
            bLocked = GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
            pRow->bAvailable = bLocked == 0;
            break;
        case 2:
            bLocked = GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) == 3;
            pRow->bAvailable = bLocked == 0;
            break;
        case 3:
        case 4:
        case 5:
            pRow->bAvailable = 1;
            break;
        }
        nRow++;
    }
    pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_FOOTER);
    if (nRow < ROW_COUNT) {
        pRow = &pMenu->aRow[nRow];
        pRow->aText[0] = 0;
        StrCopy16(pRow->aText, data_ov025_020b545c);
        pRow->bAvailable = 1;
        nRow++;
    }
    if (nRow < ROW_COUNT) {
        pRow = &pMenu->aRow[nRow];
        pRow->aText[0] = 0;
        STD_WStrCat(pRow->aText, pText);
        pRow->bAvailable = 1;
        nRow++;
    }
    for (j = 0; j < SLOT_COUNT; j++) {
        nItem = reward.aBonus[j];
        pDst = &pMenu->aRow[nRow];
        if (nRow >= ROW_COUNT) {
            break;
        }
        if (nRow == 0) {
            pDst->aText[0] = 0;
        }
        if (nItem != 0 && nItem < BONUS_ID_LIMIT) {
            pBonus = 0;
            MsgDb_FetchRecord(&pBonus, DB_BONUS, nItem, DB_SLOT);
            if (pBonus != 0) {
                MI_CpuCopy8(pBonus, &bonus, sizeof(bonus));
                DispatchByNodeKind(&pBonus);
                pRows = pMenu->aRow;
                for (m = 0; m < BONUS_PAIRS; m++) {
                    nId = bonus.aPair[m].nItem;
                    if (nId == 0 || nId >= ITEM_ID_LIMIT || nId == 1) {
                        continue;
                    }
                    for (n = 0; n < nSeen; n++) {
                        if (nId == aSeen[n]) {
                            break;
                        }
                    }
                    if (n < nSeen) {
                        continue;
                    }
                    pItemB = 0;
                    MsgDb_FetchRecord(&pItemB, DB_ITEM, nId, DB_SLOT);
                    pItem = pItemB;
                    if (pItem == 0) {
                        continue;
                    }
                    if (nSeen != 0) {
                        nLen = Wcslen(pDst->aText);
                        nAdd = Wcslen(pItem->pName);
                        if ((u32)(nLen + 1 + nAdd) > ROW_TEXT_MAX) {
                            nRow++;
                            if (nRow >= ROW_COUNT) {
                                break;
                            }
                            pDst = &pRows[nRow];
                            pDst->aText[0] = 0;
                            pRows[nRow].bAvailable = 0;
                        }
                    }
                    if (nSeen != 0) {
                        STD_WStrCat(pDst->aText, data_ov025_020b5460);
                    }
                    STD_WStrCat(pDst->aText, pItemB->pName);
                    pDst->bAvailable = 1;
                    aSeen[nSeen] = nId;
                    nSeen++;
                    DispatchByNodeKind(&pItemB);
                }
            }
        }
    }
    nRow++;
    if (nRow < ROW_COUNT) {
        pRow = &pMenu->aRow[nRow];
        pRow->aText[0] = 0;
        StrCopy16(pRow->aText, data_ov025_020b545c);
        pRow->bAvailable = 1;
    }
}
