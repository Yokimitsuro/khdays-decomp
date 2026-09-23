/* func_ov025_0209338c -- Ov025_PreviewDropSummary: preview the grid with the
 * lifted record (+0x19b4) dropped at the cursor (+0x64 / +0x66) and show the
 * stat deltas on page B.  A copy of the three page grids (item ids of the
 * slots +0x19c4) is taken; the cells of the node under the drag home
 * (020922fc at +0x68 / +0x6c / +0x6e, while lifted +0x50) are cleared on the
 * drag page, the cells of the lifted record's shape (+0x2080 by +0x24, less
 * its offsets +0x28 / +0x29, except the cursor cell) on the visible page
 * (+0x18), the home cell when a cell is current (+0x1848); the cursor cell
 * takes the lifted id and the attached records (+0x19b8: record, dx, dy)
 * theirs.  A summary is built from the copy (020871d4 / 020874dc /
 * 02087260 with a 40-slot list) and the node covering the cursor gives the
 * subitem set shown on widget 100.  The weapon records (ov002 020522c8 by the
 * local member kind, 0 when that is 0 or 0x13 -- no +0x2c fallback here, alternate stat
 * by +0x30) and the level rows (02035730 by the slot config kind) of the
 * context summary (+0x1f78) and the preview feed the page-B widgets: level
 * (2), HP (3: 1 when +0x34 is set, else total + row max), strength / magic /
 * defence / word / stat E (7 / 9 / 0xb / 0xc / 0xd: weapon + total + row),
 * entries (5: 020877e0) and header A (6).  Every tracked node (+0x1e7c) on
 * the visible page matching a summary node's anchor gets that node's
 * subitem set (020887c0) and its entry frame (02088928).  The summary is
 * released (0208772c / 02087254).  Codegen: the hit pointer stays in r0
 * through the copy loops; the 64-bit cell masks are tested with the
 * natural `1ULL << n`; the hit rows are a guarded do / while with an
 * explicit bit index (a for loop puts its init before the entry test), the
 * drop rows a for loop whose `nRow * 8` is strength-reduced; the summary
 * node of the inner loop is not reset per tracked node and both list walks
 * are while loops on the next call (a for inner loop rotates the outer);
 * kind 3 passes the old HP twice.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef short              s16;

#define GRID_PAGES  3
#define GRID_ROWS   8
#define GRID_COLS   5
#define GRID_CELLS  (GRID_ROWS * GRID_COLS)
#define KIND_NONE   0
#define KIND_DEFAULT 0x13
#define WIDGET_SUBITEM 100

typedef struct NNSFndList {
    u8 pad[12];
} NNSFndList;

typedef struct Ov025Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    u8  pad_18[0x24 - 0x18];
    int nPlacedSlot;          /* 0x24: -1 = not placed */
    u8  nOffsetCol;           /* 0x28 */
    u8  nOffsetRow;           /* 0x29 */
} Ov025Message15Record;

typedef struct Ov025ShapeEntry {
    u8  pad_00[0xc];
    int nFrame;               /* 0x0c */
    u64 nCellMask;            /* 0x10: bit col + 8*row */
} Ov025ShapeEntry;

typedef struct Ov025ShapeDef {
    u8  pad_00[0x10];
    u64 nCellMask;            /* 0x10 */
} Ov025ShapeDef;

typedef struct Ov025TrackedNode {
    u8  pad_00[4];
    int nSubitemSet;          /* 0x04 */
    u8  pad_08[2];
    u16 nPage;                /* 0x0a */
    u16 nLeft;                /* 0x0c */
    u16 nTop;                 /* 0x0e */
    u16 nAnchorCol;           /* 0x10 */
    u16 nAnchorRow;           /* 0x12 */
    u16 nWidth;               /* 0x14 */
    u16 nHeight;              /* 0x16 */
    u8  pad_18[0x20 - 0x18];
    int nSlotId;              /* 0x20 */
    Ov025ShapeEntry *pEntry;  /* 0x24 */
} Ov025TrackedNode;

typedef struct Ov025LiftedLink {
    Ov025Message15Record *pRecord; /* 0x00 */
    int nDx;                  /* 0x04 */
    int nDy;                  /* 0x08 */
} Ov025LiftedLink;

typedef struct Ov025GridSummary {
    int nHeaderA;             /* 0x00 */
    int nHeaderB;             /* 0x04 */
    NNSFndList listA;         /* 0x08 */
    NNSFndList listB;         /* 0x14 */
    NNSFndList listC;         /* 0x20 */
    int bNoCharacter;         /* 0x2c: weapon kind 0x13 instead of 0 */
    int bAltStat;             /* 0x30: use the weapon's alternate stat */
    int bHpFixed;             /* 0x34: HP shown as 1 */
    int aAppeared[14];        /* 0x38 */
    u8  pad_70[4];
    int nWeaponId;            /* 0x74 */
    int aTotal[7];            /* 0x78: level, HP, strength, magic, defence, word, stat E */
    int aCount[14];           /* 0x94 */
    u8  pad_cc[0x100 - 0xcc];
} Ov025GridSummary;

/* weapon-stat record filled by Ov025_LoadCharacterWeapon (0208b890) */
typedef struct Ov025WeaponBuf {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    int w8;
    s16 hc;
    s16 he;
    u8  pad_10[16];
} Ov025WeaponBuf;

typedef struct Ov002MissionMemberBody {
    u16 nStrength;            /* 0x00 */
    u16 nMagic;               /* 0x02 */
    u16 nDefense;             /* 0x04 */
    u16 nHpMax;               /* 0x06 */
    u16 nStatE;               /* 0x08 */
    u8  pad_0a[2];
    int nStatWord;            /* 0x0c */
} Ov002MissionMemberBody;

typedef struct SessionSlotInfo {
    int bOccupied;            /* 0x00 */
    int nMemberKind;          /* 0x04 */
} SessionSlotInfo;

typedef struct Ov025MenuContext {
    u8  pad_0000[0x18];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x50 - 0x1c];
    int bLifted;              /* 0x0050 */
    u8  pad_0054[0x64 - 0x54];
    u16 nCursorCol;           /* 0x0064 */
    u16 nCursorRow;           /* 0x0066 */
    u32 nDragPage;            /* 0x0068 */
    u16 nHomeCol;             /* 0x006c */
    u16 nHomeRow;             /* 0x006e */
    u8  pad_0070[0x1848 - 0x70];
    void *pCurrentCell;       /* 0x1848 */
    u8  pad_184c[0x19b4 - 0x184c];
    Ov025Message15Record *pListNode; /* 0x19b4: the lifted record */
    NNSFndList liftedList;    /* 0x19b8: Ov025LiftedLink */
    Ov025Message15Record *apPageSlot[GRID_PAGES][GRID_CELLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e7c - 0x1ba4];
    NNSFndList trackedNodeList; /* 0x1e7c: Ov025TrackedNode */
    u8  pad_1e88[0x1f78 - 0x1e88];
    Ov025GridSummary summary; /* 0x1f78 */
    u8  pad_2078[8];
    Ov025ShapeDef *pShapeEntries; /* 0x2080: 0x18 each */
    u8  pad_2084[0x2090 - 0x2084];
    u8  summaryHooks[8];      /* 0x2090 */
} Ov025MenuContext;

extern int   func_ov025_02084a7c(void);                                 /* Ov025_GetContext */
extern Ov025TrackedNode *func_ov025_020922fc(Ov025MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow); /* Ov025_FindGridHit */
extern void *NNS_FndGetNextListObject(NNSFndList *pList, void *pObject);
extern void  NNS_FndInitList(NNSFndList *pList, int nLinkOffset);
extern void  func_ov025_020871d4(Ov025GridSummary *pSummary, void *pHooks); /* init a summary */
extern void  func_ov025_020874dc(Ov025GridSummary *pSummary, u32 *pCells, NNSFndList *pList, u16 *pGrid); /* fill the summary from a grid */
extern void  func_ov025_02087260(Ov025GridSummary *pSummary, u32 *pCells, NNSFndList *pList); /* RebuildViewAndCountCells */
extern u32   func_02030788(void);                                       /* Session_GetLocalPlayerIndex */
extern SessionSlotInfo *func_020315c0(int nSlot);                       /* Slot4_GetIfOccupied */
extern void  func_ov002_020522c8(Ov025WeaponBuf *pOut, int nKind, int nWeaponId); /* Ov025_LoadCharacterWeapon */
extern void  func_ov025_0208eb14(int *pOutValue, int *pOutKind);        /* read the player's slot config */
extern void  func_02035730(int nKind, int nLevel, Ov002MissionMemberBody *pOut); /* StatTable_GetLevelRow */
extern void  func_ov025_020a4264(void);                                 /* Ov025_DisableRowBlock */
extern void  func_ov025_020a42b8(int nKind, int nArg, ...);             /* Ov025_DrawPageBWidget */
extern int   func_ov025_020877e0(Ov025GridSummary *pSummary);           /* count the entries */
extern void  func_ov025_020a4920(void);
extern void  func_ov025_020a4948(void);
extern void *func_ov025_0208843c(int nCtx, int nId);                    /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov025_020887c0(int nCtx, void *pEntry, int nSet);     /* Ov025_PushSubitemSet */
extern void  func_ov025_02088928(int nCtx, void *pEntry, int nFrame);   /* Ov025_ReleaseTwoSlotsEx */
extern void  func_ov025_0208772c(Ov025GridSummary *pSummary, u32 *pCells, NNSFndList *pList); /* release the summary lists */
extern void  WM_EndKeySharing_0x02087254(Ov025GridSummary *pSummary);   /* Veneer_02053464 */

void func_ov025_0209338c(Ov025MenuContext *pCtx)
{
    u32 aCells[GRID_PAGES * GRID_CELLS];
    u16 aGrid[GRID_PAGES][GRID_CELLS];
    Ov025GridSummary summary;
    NNSFndList list;
    Ov002MissionMemberBody rowOld;
    Ov002MissionMemberBody rowNew;
    Ov025WeaponBuf bufOld;
    Ov025WeaponBuf bufNew;
    int nKind;
    int nSubitemSet;
    int nCtx;
    Ov025TrackedNode *pHit;
    Ov025Message15Record *pLifted;
    Ov025LiftedLink *pLink;
    Ov025TrackedNode *pNode;
    Ov025TrackedNode *pTracked;
    Ov025GridSummary *pOld;
    Ov025GridSummary *pNew;
    void *pEntry;
    int nPage;
    int i;
    int nCursorCell;
    int nBit;
    int nRow;
    int nCol;
    int nLeft;
    int nTop;
    Ov025ShapeDef *pShape;
    u32 nCursorCol;
    u32 nCursorRow;
    int nY;
    int nKindNew;
    int nOld;
    int nNew;

    nSubitemSet = 0;
    nCtx = func_ov025_02084a7c();
    pHit = func_ov025_020922fc(pCtx, pCtx->nDragPage, pCtx->nHomeCol, pCtx->nHomeRow);
    for (nPage = 0; nPage < GRID_PAGES; nPage++) {
        for (i = 0; i < GRID_CELLS; i++) {
            aGrid[nPage][i] = pCtx->apPageSlot[nPage][i] != 0 ? pCtx->apPageSlot[nPage][i]->nItemId : 0;
        }
    }
    nCursorCell = pCtx->nCursorCol + pCtx->nCursorRow * GRID_COLS;
    if (pCtx->pListNode == 0) {
        return;
    }
    if (pHit != 0 && pCtx->bLifted != 0) {
        nRow = 0;
        if (nRow < pHit->nHeight) {
            nBit = 0;
            do {
                for (nCol = 0; nCol < pHit->nWidth; nCol++) {
                    if ((pHit->pEntry->nCellMask & (1ULL << (nCol + nBit))) != 0) {
                        aGrid[pCtx->nDragPage][pHit->nLeft + nCol + (pHit->nTop + nRow) * GRID_COLS] = 0;
                    }
                }
                nRow++;
                nBit += 8;
            } while (nRow < pHit->nHeight);
        }
    }
    pLifted = pCtx->pListNode;
    if (pLifted->nPlacedSlot >= 0) {
        pShape = &pCtx->pShapeEntries[pLifted->nPlacedSlot];
        nCursorCol = pCtx->nCursorCol;
        nCursorRow = pCtx->nCursorRow;
        nLeft = nCursorCol - pLifted->nOffsetCol;
        nTop = nCursorRow - pLifted->nOffsetRow;
        for (nRow = 0; nRow < GRID_ROWS; nRow++) {
            nY = nTop + nRow;
            for (nCol = 0; nCol < GRID_COLS; nCol++) {
                if ((pShape->nCellMask & (1ULL << (nCol + nRow * 8))) != 0
                    && (nCursorCol != nLeft + nCol || nCursorRow != nY)) {
                    aGrid[pCtx->nVisiblePage][nLeft + nY * GRID_COLS + nCol] = 0;
                }
            }
        }
    }
    if (pCtx->pCurrentCell != 0) {
        aGrid[pCtx->nDragPage][pCtx->nHomeCol + pCtx->nHomeRow * GRID_COLS] = 0;
    }
    aGrid[pCtx->nVisiblePage][nCursorCell] = pCtx->pListNode->nItemId;
    for (pLink = NNS_FndGetNextListObject(&pCtx->liftedList, 0); pLink != 0;
         pLink = NNS_FndGetNextListObject(&pCtx->liftedList, pLink)) {
        aGrid[pCtx->nVisiblePage][pCtx->nCursorCol + pLink->nDx + (pCtx->nCursorRow + pLink->nDy) * GRID_COLS] = pLink->pRecord->nItemId;
    }
    NNS_FndInitList(&list, 0x28);
    func_ov025_020871d4(&summary, pCtx->summaryHooks);
    func_ov025_020874dc(&summary, aCells, &list, aGrid[0]);
    func_ov025_02087260(&summary, aCells, &list);
    for (pNode = NNS_FndGetNextListObject(&list, 0); pNode != 0; pNode = NNS_FndGetNextListObject(&list, pNode)) {
        if (pNode->nPage == pCtx->nVisiblePage && pCtx->nCursorCol >= pNode->nLeft && pCtx->nCursorRow >= pNode->nTop) {
            nBit = (pCtx->nCursorCol - pNode->nLeft) + (pCtx->nCursorRow - pNode->nTop) * 8;
            if ((pNode->pEntry->nCellMask & (1ULL << nBit)) != 0) {
                nSubitemSet = pNode->nSubitemSet;
                break;
            }
        }
    }
    pOld = &pCtx->summary;
    pNew = &summary;
    nKindNew = func_020315c0(func_02030788())->nMemberKind;
    if (nKindNew == KIND_NONE || nKindNew == KIND_DEFAULT) {
        nKindNew = KIND_NONE;
    }
    func_ov002_020522c8(&bufOld, nKindNew, pOld->nWeaponId);
    func_ov002_020522c8(&bufNew, nKindNew, pNew->nWeaponId);
    if (pOld->bAltStat != 0) {
        bufOld.h2 = bufOld.he;
    }
    if (pNew->bAltStat != 0) {
        bufNew.h2 = bufNew.he;
    }
    func_ov025_0208eb14(0, &nKind);
    func_02035730(nKind, pOld->aTotal[0], &rowOld);
    func_02035730(nKind, pNew->aTotal[0], &rowNew);
    func_ov025_020a4264();
    func_ov025_020a42b8(2, pNew->aTotal[0] - pOld->aTotal[0], pOld->aTotal[0] + 1);
    if (pOld->bHpFixed != 0) {
        nOld = 1;
    } else {
        nOld = pOld->aTotal[1] + rowOld.nHpMax;
    }
    if (pNew->bHpFixed != 0) {
        nNew = 1;
    } else {
        nNew = pNew->aTotal[1] + rowNew.nHpMax;
    }
    func_ov025_020a42b8(3, nNew - nOld, nOld, nOld);
    nOld = pOld->aTotal[2] + rowOld.nStrength + bufOld.h2;
    nNew = pNew->aTotal[2] + rowNew.nStrength + bufNew.h2;
    func_ov025_020a42b8(7, nNew - nOld, nOld);
    nOld = pOld->aTotal[3] + rowOld.nMagic + bufOld.h4;
    nNew = pNew->aTotal[3] + rowNew.nMagic + bufNew.h4;
    func_ov025_020a42b8(9, nNew - nOld, nOld);
    nOld = pOld->aTotal[4] + rowOld.nDefense + bufOld.h6;
    nNew = pNew->aTotal[4] + rowNew.nDefense + bufNew.h6;
    func_ov025_020a42b8(0xb, nNew - nOld, nOld);
    nOld = pOld->aTotal[5] + rowOld.nStatWord + bufOld.w8;
    nNew = pNew->aTotal[5] + rowNew.nStatWord + bufNew.w8;
    func_ov025_020a42b8(0xc, nNew - nOld, nOld);
    nOld = pOld->aTotal[6] + rowOld.nStatE + bufOld.hc;
    nNew = pNew->aTotal[6] + rowNew.nStatE + bufNew.hc;
    func_ov025_020a42b8(0xd, nNew - nOld, nOld);
    nOld = func_ov025_020877e0(pOld);
    nNew = func_ov025_020877e0(pNew);
    func_ov025_020a42b8(5, nNew - nOld, nOld);
    func_ov025_020a42b8(6, pNew->nHeaderA - pOld->nHeaderA, pOld->nHeaderA);
    func_ov025_020a4920();
    func_ov025_020a4948();
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, WIDGET_SUBITEM), nSubitemSet);
    pTracked = 0;
    pNode = 0;
    while ((pTracked = NNS_FndGetNextListObject(&pCtx->trackedNodeList, pTracked)) != 0) {
        while ((pNode = NNS_FndGetNextListObject(&list, pNode)) != 0) {
            if (pCtx->nVisiblePage == pTracked->nPage && pTracked->nPage == pNode->nPage
                && pTracked->nAnchorCol == pNode->nAnchorCol && pTracked->nAnchorRow == pNode->nAnchorRow) {
                pEntry = func_ov025_0208843c(nCtx, pTracked->nSlotId);
                func_ov025_020887c0(nCtx, pEntry, pNode->nSubitemSet);
                func_ov025_02088928(nCtx, pEntry, (u16)pTracked->pEntry->nFrame);
            }
        }
    }
    func_ov025_0208772c(&summary, aCells, &list);
    WM_EndKeySharing_0x02087254(&summary);
}
