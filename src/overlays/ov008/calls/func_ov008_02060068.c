/* func_ov008_02060068 -- Ov008_CanPlaceRecord: may record pRecord go to
 * cell (nCol, nRow) of page nPage?  Returns 1 / 0 and, when refused, points
 * the context's "count" text (+0x2078) at the reason (records +0x28c).  The
 * drag home itself (+0x50, +0x68, +0x6c / +0x6e) is always allowed.  A
 * locked cell (grid +0x1e88 == 0xff) refuses with text 0x22.  A placed
 * record (+0x24) only checks the panel: item ids 0xbf .. 0xf0 want no
 * reaction card (0205ffe8) when bStrict and nothing is lifted, others of
 * category 5 / 6 want no card of their kind (0205ff4c) likewise.  An
 * unplaced record on an empty cell does the same for ids 0xbf .. 0xf0, and
 * otherwise by category: 4 allows a category-4 record at the anchor of the
 * node with the cell's id (text 0x1c), 5 refuses (text 0x1c), 6 allows a
 * category-6 record in the cell or, when bStrict and nothing is lifted, no
 * card of its kind (text 0x1f), anything else is allowed.  On an occupied
 * cell (text 0x1d) a category-6 record is refused; otherwise the node owning
 * the id must exist (0 without it), its anchor cell is refused (text 0x21)
 * and elsewhere the anchor record must share the category (1 / 4) or kind
 * (+0x22), failing which the kind table (+0x2084, 0x58 each, 0x18 entries:
 * kind +0x20, five allowed kinds from +0x28, -1 ends) must list the record's
 * kind under the anchor's.  Codegen: nCol / nRow are u16 parameters (the
 * fourth is homed to the stack at entry); the locked / placed / unplaced
 * branches are laid out with the locked case last; the category switch
 * lists 5, 6, 4, default; the node's page is re-read (no local); the kind
 * test is a bool assigned in an if/else; the table walk uses an explicit
 * entry pointer declared after k and j, with the anchor kind declared last;
 * the table hit sets the result and jumps to the end.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_COLS  5
#define GRID_ID_LOCKED 0xff
#define ITEM_REACTION_FIRST 0xbf
#define ITEM_REACTION_LAST  0xf0
#define KIND_TABLE_ENTRIES 0x18
#define ALLOWED_PER_KIND 5

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    int nCategory;            /* 0x18 */
    u8  pad_1c[6];
    s16 nKind;                /* 0x22 */
    int nPlacedSlot;          /* 0x24: -1 = not placed */
} Ov008Message15Record;

typedef struct Ov008TrackedNode {
    u8  nId;                  /* 0x00 */
    u8  pad_01[9];
    u16 nPage;                /* 0x0a */
    u8  pad_0c[4];
    u16 nAnchorCol;           /* 0x10 */
    u16 nAnchorRow;           /* 0x12 */
} Ov008TrackedNode;

typedef struct Ov008AllowedKind {
    int nKind;                /* 0x00: -1 ends the list */
    int nPad;                 /* 0x04 */
} Ov008AllowedKind;

typedef struct Ov008KindEntry {
    u8  pad_00[0x20];
    int nKind;                /* 0x20 */
    u8  pad_24[4];
    Ov008AllowedKind aAllowed[ALLOWED_PER_KIND]; /* 0x28 */
    u8  pad_50[8];
} Ov008KindEntry;

typedef struct Ov008MenuContext {
    u8    pad_0000[0x50];
    int   bLifted;                                        /* 0x0050 */
    u8    pad_0054[0x68 - 0x54];
    u32   nDragPage;                                      /* 0x0068 */
    u16   nHomeCol;                                       /* 0x006c */
    u16   nHomeRow;                                       /* 0x006e */
    u8    pad_0070[0x28c - 0x70];
    u8    records[0x19c4 - 0x28c];                        /* 0x028c: variable text records */
    Ov008Message15Record *apPageSlot[GRID_PAGES][GRID_ROWS * GRID_COLS]; /* 0x19c4 */
    u8    pad_1ba4[0x1e7c - 0x1ba4];
    u8    trackedNodeList[0xc];                           /* 0x1e7c */
    u8    aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS];        /* 0x1e88 */
    u8    pad_1f00[0x2078 - 0x1f00];
    void *pCountText;                                     /* 0x2078 */
    u8    pad_207c[8];
    Ov008KindEntry *pKindTable;                           /* 0x2084 */
} Ov008MenuContext;

extern int   func_ov008_0205ffe8(Ov008MenuContext *pCtx);               /* Ov008_FindReactionCard */
extern int   func_ov008_0205ff4c(Ov008MenuContext *pCtx, int nKind);    /* Ov008_FindPanelCardOfKind */
extern Ov008TrackedNode *NNS_FndGetNextListObject(void *pList, void *pObject);
extern void *func_ov008_02055c84(void *pRecords, int nIndex);           /* GetVarRecordByIndex */

int func_ov008_02060068(Ov008MenuContext *pCtx, Ov008Message15Record *pRecord, u32 nPage, u16 nCol, u16 nRow, int bStrict)
{
    int bOk;
    u8 nId;
    Ov008TrackedNode *pNode;
    Ov008Message15Record *pOther;
    int bSame;
    int k;
    int j;
    Ov008KindEntry *pEntry;
    int nKind;
    int nAllowed;

    bOk = 0;
    if (pRecord == 0) {
        return 0;
    }
    if (pCtx->bLifted != 0 && pCtx->nDragPage == nPage && pCtx->nHomeCol == nCol && pCtx->nHomeRow == nRow) {
        return 1;
    }
    nId = pCtx->aGrid[nPage][nRow][nCol];
    if (nId != GRID_ID_LOCKED) {
        if (pRecord->nPlacedSlot >= 0) {
            if (pRecord->nItemId >= ITEM_REACTION_FIRST && pRecord->nItemId <= ITEM_REACTION_LAST) {
                if (bStrict != 0 && pCtx->bLifted == 0) {
                    bOk = func_ov008_0205ffe8(pCtx) == 0;
                } else {
                    bOk = 1;
                }
            } else {
                if (pCtx->bLifted == 0 && bStrict != 0 && (pRecord->nCategory == 5 || pRecord->nCategory == 6)) {
                    bOk = func_ov008_0205ff4c(pCtx, pRecord->nKind) == 0;
                } else {
                    bOk = 1;
                }
            }
        } else {
            for (pNode = NNS_FndGetNextListObject(pCtx->trackedNodeList, 0); pNode != 0;
                 pNode = NNS_FndGetNextListObject(pCtx->trackedNodeList, pNode)) {
                if (pNode->nId == nId) {
                    break;
                }
            }
            if (nId == 0) {
                if (pRecord->nItemId >= ITEM_REACTION_FIRST && pRecord->nItemId <= ITEM_REACTION_LAST) {
                    if (bStrict != 0 && pCtx->bLifted == 0) {
                        bOk = func_ov008_0205ffe8(pCtx) == 0;
                    } else {
                        bOk = 1;
                    }
                } else {
                    switch (pRecord->nCategory) {
                    case 5:
                        pCtx->pCountText = func_ov008_02055c84(pCtx->records, 0x1c);
                        break;
                    case 6:
                        pOther = pCtx->apPageSlot[nPage][nCol + nRow * GRID_COLS];
                        if (pOther != 0 && pOther->nCategory == 6) {
                            bOk = 1;
                        } else if (bStrict != 0 && pCtx->bLifted == 0) {
                            bOk = func_ov008_0205ff4c(pCtx, pRecord->nKind) == 0;
                        } else {
                            bOk = 1;
                        }
                        pCtx->pCountText = func_ov008_02055c84(pCtx->records, 0x1f);
                        break;
                    case 4:
                        if (pNode != 0) {
                            pOther = pCtx->apPageSlot[nPage][pNode->nAnchorCol + pNode->nAnchorRow * GRID_COLS];
                            if (pOther != 0 && pOther->nCategory == 4) {
                                bOk = 1;
                            }
                        }
                        pCtx->pCountText = func_ov008_02055c84(pCtx->records, 0x1c);
                        break;
                    default:
                        bOk = 1;
                        break;
                    }
                }
            } else {
                if (pRecord->nCategory == 6) {
                    pCtx->pCountText = func_ov008_02055c84(pCtx->records, 0x1d);
                } else {
                    pCtx->pCountText = func_ov008_02055c84(pCtx->records, 0x1d);
                    if (pNode == 0) {
                        return 0;
                    }
                    pOther = pCtx->apPageSlot[pNode->nPage][pNode->nAnchorCol + pNode->nAnchorRow * GRID_COLS];
                    if (nPage == pNode->nPage && nCol == pNode->nAnchorCol && nRow == pNode->nAnchorRow) {
                        pCtx->pCountText = func_ov008_02055c84(pCtx->records, 0x21);
                    } else {
                        if (pOther->nCategory == 1 || pOther->nCategory == 4) {
                            bSame = pRecord->nCategory == pOther->nCategory;
                        } else {
                            bSame = pOther->nKind == pRecord->nKind;
                        }
                        if (bSame) {
                            bOk = 1;
                        } else {
                            nKind = pOther->nKind;
                            pEntry = pCtx->pKindTable;
                            for (k = 0; k < KIND_TABLE_ENTRIES; k++, pEntry++) {
                                if (nKind == pEntry->nKind) {
                                    for (j = 0; j < ALLOWED_PER_KIND; j++) {
                                        nAllowed = pEntry->aAllowed[j].nKind;
                                        if (nAllowed < 0) {
                                            break;
                                        }
                                        if (pRecord->nKind == nAllowed) {
                                            bOk = 1;
                                            goto done;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        pCtx->pCountText = func_ov008_02055c84(pCtx->records, 0x22);
    }
done:
    return bOk;
}
