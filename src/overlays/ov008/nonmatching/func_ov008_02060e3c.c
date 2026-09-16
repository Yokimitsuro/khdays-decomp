/* NOT MATCHING -- 1863 of 1952 bytes, 452 of 488 instructions aligned.
 *
 * Exact size, exact instruction count and exact relocations. Everything is
 * byte identical except the five weapon-stat sums for widgets 7 / 9 / 0xb / 0xc
 * / 0xd: the ROM writes the inner `total + row` sum into the row's register
 * (the right operand, `add r2, r3, r2`) and the buffer halfword then takes the
 * freed r3; build 139 writes it into the total's register (`add r3, r3, r2`)
 * and the following four instructions of each block follow that choice.
 *
 * Swept: the six operand orders x (int / u32 / s16) casts x old / new statement
 * order (48), named row / total locals x orders (96), compound accumulations
 * (18), single-expression deltas (30), u32 sums and totals, a delta local,
 * variadic / K&R draw prototypes, callee return types (163), argument casts
 * (319), a type mask over the scalars (256), 49 pragmas. Left for decomp.me.
 */
/* func_ov008_02060e3c -- Ov008_PreviewDropSummary: preview the grid with the
 * lifted record (+0x19b4) dropped at the cursor (+0x64 / +0x66) and show the
 * stat deltas on page B.  A copy of the three page grids (item ids of the
 * slots +0x19c4) is taken; the cells of the node under the drag home
 * (0205fdac at +0x68 / +0x6c / +0x6e, while lifted +0x50) are cleared on the
 * drag page, the cells of the lifted record's shape (+0x2080 by +0x24, less
 * its offsets +0x28 / +0x29, except the cursor cell) on the visible page
 * (+0x18), the home cell when a cell is current (+0x1848); the cursor cell
 * takes the lifted id and the attached records (+0x19b8: record, dx, dy)
 * theirs.  A summary is built from the copy (020533e4 / 020536ec /
 * 02053470 with a 40-slot list) and the node covering the cursor gives the
 * subitem set shown on widget 100.  The weapon records (0208b890 by the
 * local member kind, 0x13 / 0 by the summaries' flags +0x2c, alternate stat
 * by +0x30) and the level rows (02035730 by the slot config kind) of the
 * context summary (+0x1f78) and the preview feed the page-B widgets: level
 * (2), HP (3: 1 when +0x34 is set, else total + row max), strength / magic /
 * defence / word / stat E (7 / 9 / 0xb / 0xc / 0xd: weapon + total + row),
 * entries (5: 020539f0) and header A (6).  Every tracked node (+0x1e7c) on
 * the visible page matching a summary node's anchor gets that node's
 * subitem set (02054b18) and its entry frame (02054c80).  The summary is
 * released (0205393c / 02053464).  Codegen: the hit pointer stays in r0
 * through the copy loops; the 64-bit cell masks are tested with the
 * natural `1ULL << n`; the hit rows are a guarded do / while with an
 * explicit bit index (a for loop puts its init before the entry test), the
 * drop rows a for loop whose `nRow * 8` is strength-reduced; the summary
 * node of the inner loop is not reset per tracked node and both list walks
 * are while loops on the next call (a for inner loop rotates the outer);
 * kind 3 passes the old HP twice.  HELD: the five weapon-stat sums differ
 * in scratch-register choice only (ROM: the first add lands in the row's
 * register and the new weapon stat takes the freed total register).
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

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    u8  pad_18[0x24 - 0x18];
    int nPlacedSlot;          /* 0x24: -1 = not placed */
    u8  nOffsetCol;           /* 0x28 */
    u8  nOffsetRow;           /* 0x29 */
} Ov008Message15Record;

typedef struct Ov008ShapeEntry {
    u8  pad_00[0xc];
    int nFrame;               /* 0x0c */
    u64 nCellMask;            /* 0x10: bit col + 8*row */
} Ov008ShapeEntry;

typedef struct Ov008ShapeDef {
    u8  pad_00[0x10];
    u64 nCellMask;            /* 0x10 */
} Ov008ShapeDef;

typedef struct Ov008TrackedNode {
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
    Ov008ShapeEntry *pEntry;  /* 0x24 */
} Ov008TrackedNode;

typedef struct Ov008LiftedLink {
    Ov008Message15Record *pRecord; /* 0x00 */
    int nDx;                  /* 0x04 */
    int nDy;                  /* 0x08 */
} Ov008LiftedLink;

typedef struct Ov008GridSummary {
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
} Ov008GridSummary;

/* weapon-stat record filled by Ov008_LoadCharacterWeapon (0208b890) */
typedef struct Ov008WeaponBuf {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    int w8;
    s16 hc;
    s16 he;
    u8  pad_10[16];
} Ov008WeaponBuf;

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

typedef struct Ov008MenuContext {
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
    Ov008Message15Record *pListNode; /* 0x19b4: the lifted record */
    NNSFndList liftedList;    /* 0x19b8: Ov008LiftedLink */
    Ov008Message15Record *apPageSlot[GRID_PAGES][GRID_CELLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e7c - 0x1ba4];
    NNSFndList trackedNodeList; /* 0x1e7c: Ov008TrackedNode */
    u8  pad_1e88[0x1f78 - 0x1e88];
    Ov008GridSummary summary; /* 0x1f78 */
    u8  pad_2078[8];
    Ov008ShapeDef *pShapeEntries; /* 0x2080: 0x18 each */
    u8  pad_2084[0x2090 - 0x2084];
    u8  summaryHooks[8];      /* 0x2090 */
} Ov008MenuContext;

extern int   func_ov008_02050c54(void);                                 /* Ov008_GetContext */
extern Ov008TrackedNode *func_ov008_0205fdac(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow); /* Ov008_FindGridHit */
extern void *NNS_FndGetNextListObject(NNSFndList *pList, void *pObject);
extern void  NNS_FndInitList(NNSFndList *pList, int nLinkOffset);
extern void  func_ov008_020533e4(Ov008GridSummary *pSummary, void *pHooks); /* init a summary */
extern void  func_ov008_020536ec(Ov008GridSummary *pSummary, u32 *pCells, NNSFndList *pList, u16 *pGrid); /* fill the summary from a grid */
extern void  func_ov008_02053470(Ov008GridSummary *pSummary, u32 *pCells, NNSFndList *pList); /* RebuildViewAndCountCells */
extern u32   func_02030788(void);                                       /* Session_GetLocalPlayerIndex */
extern SessionSlotInfo *func_020315c0(int nSlot);                       /* Slot4_GetIfOccupied */
extern void  func_ov008_0208b890(Ov008WeaponBuf *pOut, int nKind, int nWeaponId); /* Ov008_LoadCharacterWeapon */
extern void  func_ov008_0205c580(int *pOutValue, int *pOutKind);        /* read the player's slot config */
extern void  func_02035730(int nKind, int nLevel, Ov002MissionMemberBody *pOut); /* StatTable_GetLevelRow */
extern void  func_ov008_0206ebd8(void);                                 /* Ov008_DisableRowBlock */
extern void  func_ov008_0206ec2c(int nKind, int nArg, ...);             /* Ov008_DrawPageBWidget */
extern int   func_ov008_020539f0(Ov008GridSummary *pSummary);           /* count the entries */
extern void  func_ov008_0206f334(void);
extern void  func_ov008_0206f35c(void);
extern void *func_ov008_02054788(int nCtx, int nId);                    /* FindEntryById */
extern void  func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov008_02054b18(int nCtx, void *pEntry, int nSet);     /* Ov008_PushSubitemSet */
extern void  func_ov008_02054c80(int nCtx, void *pEntry, int nFrame);   /* Ov008_ReleaseTwoSlotsEx */
extern void  func_ov008_0205393c(Ov008GridSummary *pSummary, u32 *pCells, NNSFndList *pList); /* release the summary lists */
extern void  WM_EndKeySharing_0x02053464(Ov008GridSummary *pSummary);   /* Veneer_02053464 */

void func_ov008_02060e3c(Ov008MenuContext *pCtx)
{
    u32 aCells[GRID_PAGES * GRID_CELLS];
    u16 aGrid[GRID_PAGES][GRID_CELLS];
    Ov008GridSummary summary;
    NNSFndList list;
    Ov002MissionMemberBody rowOld;
    Ov002MissionMemberBody rowNew;
    Ov008WeaponBuf bufOld;
    Ov008WeaponBuf bufNew;
    int nKind;
    int nSubitemSet;
    int nCtx;
    Ov008TrackedNode *pHit;
    Ov008Message15Record *pLifted;
    Ov008LiftedLink *pLink;
    Ov008TrackedNode *pNode;
    Ov008TrackedNode *pTracked;
    Ov008GridSummary *pOld;
    Ov008GridSummary *pNew;
    void *pEntry;
    int nPage;
    int i;
    int nCursorCell;
    int nBit;
    int nRow;
    int nCol;
    int nLeft;
    int nTop;
    Ov008ShapeDef *pShape;
    u32 nCursorCol;
    u32 nCursorRow;
    int nY;
    int nKindOld;
    int nKindNew;
    int nOld;
    int nNew;

    nSubitemSet = 0;
    nCtx = func_ov008_02050c54();
    pHit = func_ov008_0205fdac(pCtx, pCtx->nDragPage, pCtx->nHomeCol, pCtx->nHomeRow);
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
    func_ov008_020533e4(&summary, pCtx->summaryHooks);
    func_ov008_020536ec(&summary, aCells, &list, aGrid[0]);
    func_ov008_02053470(&summary, aCells, &list);
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
        nKindOld = pOld->bNoCharacter != 0 ? KIND_DEFAULT : KIND_NONE;
        nKindNew = pNew->bNoCharacter != 0 ? KIND_DEFAULT : KIND_NONE;
    } else {
        nKindOld = nKindNew;
    }
    func_ov008_0208b890(&bufOld, nKindOld, pOld->nWeaponId);
    func_ov008_0208b890(&bufNew, nKindNew, pNew->nWeaponId);
    if (pOld->bAltStat != 0) {
        bufOld.h2 = bufOld.he;
    }
    if (pNew->bAltStat != 0) {
        bufNew.h2 = bufNew.he;
    }
    func_ov008_0205c580(0, &nKind);
    func_02035730(nKind, pOld->aTotal[0], &rowOld);
    func_02035730(nKind, pNew->aTotal[0], &rowNew);
    func_ov008_0206ebd8();
    func_ov008_0206ec2c(2, pNew->aTotal[0] - pOld->aTotal[0], pOld->aTotal[0] + 1);
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
    func_ov008_0206ec2c(3, nNew - nOld, nOld, nOld);
    nOld = pOld->aTotal[2] + rowOld.nStrength + bufOld.h2;
    nNew = pNew->aTotal[2] + rowNew.nStrength + bufNew.h2;
    func_ov008_0206ec2c(7, nNew - nOld);
    nOld = pOld->aTotal[3] + rowOld.nMagic + bufOld.h4;
    nNew = pNew->aTotal[3] + rowNew.nMagic + bufNew.h4;
    func_ov008_0206ec2c(9, nNew - nOld);
    nOld = pOld->aTotal[4] + rowOld.nDefense + bufOld.h6;
    nNew = pNew->aTotal[4] + rowNew.nDefense + bufNew.h6;
    func_ov008_0206ec2c(0xb, nNew - nOld);
    nOld = pOld->aTotal[5] + rowOld.nStatWord + bufOld.w8;
    nNew = pNew->aTotal[5] + rowNew.nStatWord + bufNew.w8;
    func_ov008_0206ec2c(0xc, nNew - nOld);
    nOld = pOld->aTotal[6] + rowOld.nStatE + bufOld.hc;
    nNew = pNew->aTotal[6] + rowNew.nStatE + bufNew.hc;
    func_ov008_0206ec2c(0xd, nNew - nOld);
    nOld = func_ov008_020539f0(pOld);
    nNew = func_ov008_020539f0(pNew);
    func_ov008_0206ec2c(5, nNew - nOld, nOld);
    func_ov008_0206ec2c(6, pNew->nHeaderA - pOld->nHeaderA, pOld->nHeaderA);
    func_ov008_0206f334();
    func_ov008_0206f35c();
    func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_SUBITEM), nSubitemSet);
    pTracked = 0;
    pNode = 0;
    while ((pTracked = NNS_FndGetNextListObject(&pCtx->trackedNodeList, pTracked)) != 0) {
        while ((pNode = NNS_FndGetNextListObject(&list, pNode)) != 0) {
            if (pCtx->nVisiblePage == pTracked->nPage && pTracked->nPage == pNode->nPage
                && pTracked->nAnchorCol == pNode->nAnchorCol && pTracked->nAnchorRow == pNode->nAnchorRow) {
                pEntry = func_ov008_02054788(nCtx, pTracked->nSlotId);
                func_ov008_02054b18(nCtx, pEntry, pNode->nSubitemSet);
                func_ov008_02054c80(nCtx, pEntry, (u16)pTracked->pEntry->nFrame);
            }
        }
    }
    func_ov008_0205393c(&summary, aCells, &list);
    WM_EndKeySharing_0x02053464(&summary);
}
