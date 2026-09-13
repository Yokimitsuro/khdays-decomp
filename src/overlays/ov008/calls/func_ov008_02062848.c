/* func_ov008_02062848 -- Ov008_DropLiftedNode: drop the lifted node
 * (+0x19b4) at the cursor (+0x64 / +0x66) on the visible page (+0x18).  A
 * summary snapshot is built first.  The node found at the drag home (+0x68,
 * +0x6c / +0x6e) must accept the move to the cursor minus the node's anchor
 * offset (+0x28 / +0x29) and the lifted record must fit at the cursor; then
 * both the target and the home cells are cleaned, the record placed at the
 * cursor with its row counter bumped, and every lifted cell (+0x19b8) placed
 * at the cursor plus its offset likewise.  An unplaced record (+0x24 < 0)
 * that is not category 6 arms the hold count (+0x44) and, while more copies
 * are owned (GameState 0x810) than are on the grid and no scroll (+0x2c) is
 * running, sets the busy words (+0x30 / +0x34) and steps the cursor; any
 * other case resets the drag, an already placed record also clearing the
 * tracked cells.  The grid hits are rebuilt, the surface (+0xac) queued,
 * the summary (+0x1f78) rebuilt, the row block disabled, the equip panel
 * refreshed and the change set against the snapshot computed (tag 0x48
 * trigger, page-1 mission row when any change word is set).  Returns 1 on a
 * completed drop, 0 otherwise; the snapshot is released either way.
 * Codegen: both inner conditions are written with the reset case first.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define CATEGORY_FIXED 6

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    int nCategory;            /* 0x18 */
    u8  pad_1c[8];
    int nPlacedSlot;          /* 0x24: -1 = not placed */
    u8  nOffsetCol;           /* 0x28 */
    u8  nOffsetRow;           /* 0x29 */
} Ov008Message15Record;

typedef struct Ov008LiftedCell {
    Ov008Message15Record *pRecord; /* 0x00 */
    int nColOffset;           /* 0x04: from the anchor */
    int nRowOffset;           /* 0x08 */
    u8  pad_0c[0x18 - 0xc];
} Ov008LiftedCell;

typedef struct Ov008GridSummary {
    u8 pad[0x100];
} Ov008GridSummary;

typedef struct Ov008GridChanges {
    u8  pad_00[8];
    int aChanged[4];          /* 0x08 */
    u8  pad_18[0xb8 - 0x18];
} Ov008GridChanges;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x18];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x2c - 0x1c];
    int bScroll;              /* 0x002c */
    int nBusyWord;            /* 0x0030 */
    int bHolding;           /* 0x0034: still holding a copy to place */
    u8  pad_0038[0x44 - 0x38];
    int nHoldCount;           /* 0x0044 */
    u8  pad_0048[0x64 - 0x48];
    u16 nCursorCol;           /* 0x0064 */
    u16 nCursorRow;           /* 0x0066 */
    u32 nDragPage;            /* 0x0068: home page of the lifted node */
    u16 nHomeCol;             /* 0x006c */
    u16 nHomeRow;             /* 0x006e */
    u8  pad_0070[0xac - 0x70];
    u8  gridSurface[0x19b4 - 0xac]; /* 0x00ac */
    Ov008Message15Record *pListNode; /* 0x19b4 */
    u8  liftedList[0xc];      /* 0x19b8 */
    u8  apPageSlot[0x1e7c - 0x19c4]; /* 0x19c4 */
    u8  trackedNodeList[0xc]; /* 0x1e7c */
    u8  pad_1e88[0x1f78 - 0x1e88];
    Ov008GridSummary summary; /* 0x1f78 */
    u8  pad_2078[0x2090 - 0x2078];
    u8  summaryHooks[8];      /* 0x2090 */
} Ov008MenuContext;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern GameState *data_0204be18;
extern void  func_ov008_020533e4(Ov008GridSummary *pSummary, void *pHooks);        /* init a summary */
extern void  func_ov008_02053470(Ov008GridSummary *pSummary, void *pSlots, void *pList); /* RebuildViewAndCountCells */
extern void *func_ov008_0205fdac(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow); /* Ov008_FindGridHit */
extern int   func_ov008_020604e4(Ov008MenuContext *pCtx, void *pNode, u32 nPage, int nCol, int nRow, int nArg); /* move the node */
extern int   func_ov008_02060068(Ov008MenuContext *pCtx, Ov008Message15Record *pRecord, u32 nPage, u32 nCol, u32 nRow, int nArg); /* record fits */
extern void  func_ov008_02061ee8(Ov008MenuContext *pCtx, u16 nPage, u32 nCol, u32 nRow); /* Ov008_ProcessAndCleanup */
extern int   func_ov008_02060d38(Ov008MenuContext *pCtx, Ov008Message15Record *pRecord, u32 nPage, u32 nCol, u16 nRow); /* place at cell */
extern void  func_ov008_0205e790(Ov008MenuContext *pCtx, int nItemId, char nDelta); /* Ov008_BumpRowCounter */
extern Ov008LiftedCell *NNS_FndGetNextListObject(void *pList, void *pObject);
extern void  func_ov008_020615dc(Ov008MenuContext *pCtx, int nArg);              /* Ov008_ResetGridDrag */
extern void  func_ov008_0205cb08(Ov008MenuContext *pCtx);                        /* Ov008_ClearTrackedGridCells */
extern char  func_ov008_0205e734(Ov008MenuContext *pCtx, int nItemId);           /* Ov008_CountGridEntriesForOwner */
extern int   func_ov008_0206245c(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep); /* move the cursor */
extern void  func_ov008_02060ae8(Ov008MenuContext *pCtx);                        /* Ov008_RebuildGridHits */
extern void  func_020300f8(void *pSurface);                                      /* EnqueueObjGfxCommand */
extern void  func_ov008_0206ebd8(void);                                          /* Ov008_DisableRowBlock */
extern void  func_ov008_0206ed7c(Ov008GridSummary *pSummary);                    /* Ov008_RefreshEquipPanel */
extern int   func_ov008_0205eb6c(Ov008GridChanges *pOut, Ov008GridSummary *pOld, Ov008GridSummary *pNew);
extern void  func_ov008_0206f694(void);                                          /* Ov008_TriggerTag48IfState0 */
extern void  func_ov008_0206f644(void);                                          /* Ov008_EnableMissionRowOnPage1 */
extern void  WM_EndKeySharing_0x02053464(Ov008GridSummary *pSummary);            /* release a summary */

int func_ov008_02062848(Ov008MenuContext *pCtx)
{
    Ov008GridSummary snapshot;
    Ov008GridChanges changes;
    int bDone;
    int nLeft;
    int nTop;
    void *pNode;
    Ov008LiftedCell *pCell;
    int nItemId;

    bDone = 0;
    func_ov008_020533e4(&snapshot, pCtx->summaryHooks);
    func_ov008_02053470(&snapshot, pCtx->apPageSlot, pCtx->trackedNodeList);
    nLeft = pCtx->nCursorCol - pCtx->pListNode->nOffsetCol;
    nTop = pCtx->nCursorRow - pCtx->pListNode->nOffsetRow;
    pNode = func_ov008_0205fdac(pCtx, pCtx->nDragPage, pCtx->nHomeCol, pCtx->nHomeRow);
    if (pNode == 0 || func_ov008_020604e4(pCtx, pNode, pCtx->nVisiblePage, nLeft, nTop, 1) != 0) {
        if (func_ov008_02060068(pCtx, pCtx->pListNode, pCtx->nVisiblePage, pCtx->nCursorCol, pCtx->nCursorRow, 0) != 0) {
            func_ov008_02061ee8(pCtx, pCtx->nVisiblePage, pCtx->nCursorCol, pCtx->nCursorRow);
            func_ov008_02061ee8(pCtx, pCtx->nDragPage, pCtx->nHomeCol, pCtx->nHomeRow);
            func_ov008_02060d38(pCtx, pCtx->pListNode, pCtx->nVisiblePage, pCtx->nCursorCol, pCtx->nCursorRow);
            func_ov008_0205e790(pCtx, pCtx->pListNode->nItemId, 1);
            for (pCell = NNS_FndGetNextListObject(pCtx->liftedList, 0); pCell != 0;
                 pCell = NNS_FndGetNextListObject(pCtx->liftedList, pCell)) {
                func_ov008_02060d38(pCtx, pCell->pRecord, pCtx->nVisiblePage, (u16)(pCtx->nCursorCol + pCell->nColOffset), pCtx->nCursorRow + pCell->nRowOffset);
                func_ov008_0205e790(pCtx, pCell->pRecord->nItemId, 1);
            }
            if (pCtx->pListNode->nPlacedSlot >= 0 || pCtx->pListNode->nCategory == CATEGORY_FIXED) {
                func_ov008_020615dc(pCtx, 0);
                func_ov008_0205cb08(pCtx);
            } else {
                pCtx->nHoldCount = 1;
                nItemId = pCtx->pListNode->nItemId;
                if ((u32)func_ov008_0205e734(pCtx, nItemId) >= data_0204be18->aItemCount[nItemId] || pCtx->bScroll != 0) {
                    func_ov008_020615dc(pCtx, 0);
                } else {
                    pCtx->bHolding = 1;
                    pCtx->nBusyWord = 1;
                    func_ov008_0206245c(pCtx, pCtx->nCursorCol, pCtx->nCursorRow, 1);
                }
            }
            func_ov008_02060ae8(pCtx);
            func_020300f8(pCtx->gridSurface);
            func_ov008_02053470(&pCtx->summary, pCtx->apPageSlot, pCtx->trackedNodeList);
            func_ov008_0206ebd8();
            func_ov008_0206ed7c(&pCtx->summary);
            if (func_ov008_0205eb6c(&changes, &snapshot, &pCtx->summary) != 0) {
                func_ov008_0206f694();
            }
            if (changes.aChanged[0] != 0 || changes.aChanged[1] != 0 || changes.aChanged[2] != 0 || changes.aChanged[3] != 0) {
                func_ov008_0206f644();
            }
            bDone = 1;
        }
    }
    WM_EndKeySharing_0x02053464(&snapshot);
    return bDone;
}
