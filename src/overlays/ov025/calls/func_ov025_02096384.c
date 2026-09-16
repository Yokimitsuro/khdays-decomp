/* func_ov025_02096384 -- Ov008_FindSpareItemOfKind: pick a spare record for
 * tracked node pNode whose anchor record pAnchor names a kind (+0x22).  The
 * dynamic records (+0x208c, 0x3e0 each) are searched from 49 down to 1 for
 * the one of that kind (+0x18); without it 0 is returned.  The node's box
 * (+0xc / +0xe, +0x14 x +0x16, cells of the entry mask) is tallied: for every
 * record on the visible page (+0x18, slots +0x19c4) the count of its kind
 * (up to nine kinds, 12-byte tally rows) is bumped.  Then the record's 23
 * item lists (+0x40, 0x28 apart, until a negative id; db 0x16 slot 0xe) are
 * walked: an item with spare copies (grid count 0205e734 below GameState
 * 0x810) whose list id is not tallied, or whose tallied spares (+0x4) now
 * exceed its grid count (+0x8), is the answer (records +0x207c, 0x9c each).
 * Failing that the first item id (from 1) with a spare copy is returned, or
 * 0.  The fetched list is released on every exit.  Codegen: pResult = 0 is
 * the first zero (pList = 0 reloads it); the page slot is re-read for the new
 * tally row; the dynamic record loop keeps `pFound = pRec` before the test.
 * Codegen: the phase-2 list index reuses the phase-1 column variable -- mwcc
 * numbers a variable's register by its first definition in the function, and
 * a fresh counter created at the list loop colours below the item id (sb / sl
 * swapped); an older variable keeps the id below it.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef short              s16;
typedef unsigned long long u64;

#define GRID_COLS      5
#define DB_ITEM_LISTS  0x16
#define DB_SLOT_LISTS  0xe
#define TALLY_ROWS     9
#define DYNAMIC_LAST   49
#define LIST_SLOTS     0x18
#define ITEM_ID_COUNT  0x277

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x10];
    u64 nCellMask;            /* 0x10: bit col + 8*row */
} Ov008ShapeEntry;

typedef struct Ov008TrackedNode {
    u8  pad_00[0xc];
    u16 nLeft;                /* 0x0c */
    u16 nTop;                 /* 0x0e */
    u8  pad_10[4];
    u16 nWidth;               /* 0x14 */
    u16 nHeight;              /* 0x16 */
    u8  pad_18[0x24 - 0x18];
    Ov008ShapeEntry *pEntry;  /* 0x24 */
} Ov008TrackedNode;

typedef struct Ov008Message15Record {
    u8  pad_00[0x22];
    s16 nKind;                /* 0x22 */
    u8  pad_24[0x9c - 0x24];
} Ov008Message15Record;

typedef struct Ov008ItemListRecord {
    u8   pad_00[0x10];
    u32  nCount;              /* 0x10 */
    int *aItemId;             /* 0x14 */
} Ov008ItemListRecord;

typedef struct Ov008DynamicRow {
    u8  pad_00[0x18];
    int nListId;              /* 0x18: row 0 names the record's kind; -1 ends the table */
    u8  pad_1c[0x28 - 0x1c];
} Ov008DynamicRow;

typedef struct Ov008DynamicRecord {
    Ov008DynamicRow aRow[LIST_SLOTS]; /* 0x00 */
    u8  pad_3c0[0x3e0 - 0x3c0];
} Ov008DynamicRecord;

typedef struct Ov008KindTally {
    s16 nKind;                /* 0x00 */
    u8  pad_02[2];
    int nSpare;               /* 0x04: spare copies seen in the lists */
    int nCount;               /* 0x08: records of the kind in the box */
} Ov008KindTally;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x18];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x19c4 - 0x1c];
    Ov008Message15Record *apPageSlot[3][40]; /* 0x19c4 */
    u8  pad_1ba4[0x207c - 0x1ba4];
    Ov008Message15Record *pRecords; /* 0x207c */
    u8  pad_2080[0xc];
    Ov008DynamicRecord *pDynamicRecords; /* 0x208c */
} Ov008MenuContext;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern GameState *data_0204be18;
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern void  func_020342e8(Ov008ItemListRecord **ppRecord, int nDbId, int nIndex, int nSlot); /* MsgDb_FetchRecord */
extern void  func_020343cc(Ov008ItemListRecord **ppRecord);             /* release the record */
extern char  func_ov025_02090ca8(Ov008MenuContext *pCtx, int nItemId);  /* Ov008_CountGridEntriesForOwner */

Ov008Message15Record *func_ov025_02096384(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode, Ov008Message15Record *pAnchor)
{
    Ov008KindTally aTally[TALLY_ROWS];
    Ov008ItemListRecord *pList;
    Ov008DynamicRecord *pFound;
    Ov008Message15Record *pResult;
    int k;
    int nIndex;                 /* column in the box tally, then list index */
    int nBit;
    Ov008KindTally *pTally;
    int nRow;
    Ov008DynamicRecord *pRec;
    int nCell;
    int i;
    Ov008DynamicRow *pRow;
    int nItemId;
    int nListId;
    Ov008KindTally *pT;

    pResult = 0;
    pList = 0;
    MI_CpuFill8(aTally, 0, sizeof(aTally));
    pRec = &pCtx->pDynamicRecords[DYNAMIC_LAST];
    for (k = DYNAMIC_LAST; k > 0; k--, pRec--) {
        pFound = pRec;
        if (pRec != 0) {
            if (pRec->aRow[0].nListId == pAnchor->nKind) {
                break;
            }
            pFound = 0;
        }
    }
    nRow = 0;
    if (nRow < pNode->nHeight) {
        pTally = aTally;
        nBit = 0;
        do {
        for (nIndex = 0; nIndex < pNode->nWidth; nIndex++) {
            if ((pNode->pEntry->nCellMask & (1ULL << (nIndex + nBit))) != 0) {
                nCell = (nIndex + pNode->nLeft) + (nRow + pNode->nTop) * GRID_COLS;
                if (pCtx->apPageSlot[pCtx->nVisiblePage][nCell] != 0) {
                    for (i = 0; i < TALLY_ROWS; i++) {
                        if (aTally[i].nKind == pCtx->apPageSlot[pCtx->nVisiblePage][nCell]->nKind) {
                            aTally[i].nCount++;
                            break;
                        }
                    }
                    if (i == TALLY_ROWS) {
                        pTally->nKind = pCtx->apPageSlot[pCtx->nVisiblePage][nCell]->nKind;
                        pTally->nCount = 1;
                        pTally++;
                    }
                }
            }
        }
        nRow++;
        nBit += 8;
        } while (nRow < pNode->nHeight);
    }
    if (pFound == 0) {
        return 0;
    }
    for (k = 1, pRow = &pFound->aRow[1]; k < LIST_SLOTS; k++, pRow++) {
        nListId = pRow->nListId;
        if (nListId < 0) {
            goto done;
        }
        func_020342e8(&pList, DB_ITEM_LISTS, nListId, DB_SLOT_LISTS);
        for (nIndex = 0; nIndex < pList->nCount; nIndex++) {
            nItemId = pList->aItemId[nIndex];
            if ((u32)func_ov025_02090ca8(pCtx, nItemId) < data_0204be18->aItemCount[nItemId]) {
                for (i = 0, pT = aTally; i < TALLY_ROWS; i++, pT++) {
                    if (pT->nKind == pRow->nListId) {
                        aTally[i].nSpare++;
                        if (aTally[i].nCount < aTally[i].nSpare) {
                            pResult = &pCtx->pRecords[nItemId];
                            goto done;
                        }
                        break;
                    }
                }
                if (i == TALLY_ROWS) {
                    pResult = &pCtx->pRecords[nItemId];
                    goto done;
                }
            }
        }
        func_020343cc(&pList);
    }
    pResult = 0;
    for (nItemId = 1; nItemId < ITEM_ID_COUNT; nItemId++) {
        if ((u32)func_ov025_02090ca8(pCtx, nItemId) < data_0204be18->aItemCount[nItemId]) {
            pResult = &pCtx->pRecords[nItemId];
            break;
        }
    }
done:
    if (pList != 0) {
        func_020343cc(&pList);
    }
    return pResult;
}
