/* func_ov008_0206245c -- Ov008_MoveGridCursor: put the grid cursor on cell
 * (nCol, nRow) of the visible page (+0x18); returns 0 when the cell is off
 * the 5 x 8 page, else 1.  The cursor widgets 100 / 0x60 follow widget 3
 * offset by the cell (16.16, plus half a cell while the busy word +0x30 is
 * set outside "grid state with nothing held", +0x34) and (6, -13); the
 * cursor cell (+0x64 / +0x66) is stored.  With a lifted record (+0x19b4)
 * its placed slot (+0x24) and the cursor's offset from its anchor (+0x28 /
 * +0x29) are taken, and a placed record's shape entry (+0x2080, 0x18 each)
 * with, while lifted (+0x50), the node under the drag home (+0x68, +0x6c /
 * +0x6e); otherwise the text row shows the cell record's text (+0x1e68) or
 * nothing.  When the shape preview (020621f8) draws, widget 0x60 hides, the
 * lifted record's text is shown and, without the busy word, the grid is
 * rebuilt; otherwise (with nStep and a lifted record) the count text
 * (+0x2078) is shown in colour 0xf1 and widget 100 hides / 0x60 shows,
 * then the grid hits are rebuilt, the row block disabled and the equip
 * panel refreshed.  Cursor mode 0x14 is requested with 2 (lifted), 1 (the
 * cursor cell can be filled, 020642a8) or 0, the grid refreshed, and widget
 * 0x4a shows with the placed slot of the lifted / cell record as its frame
 * (hidden when there is none).  Codegen: the offset pair is a {0, 0}
 * initialiser (zeroed through a pointer register); declaration order pos,
 * pAnchor, nDx, pHit (stack) then nCtx, nPlacedSlot, nDy, pShape (r4..r7);
 * the "lifted" branches come first; the record local is reused for the
 * cell record.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GRID_COLS      5
#define GRID_ROWS      8
#define STATE_GRID     1
#define COLOUR_ACTIVE  0xf3
#define COLOUR_COUNT   0xf1
#define WIDGET_ANCHOR  3
#define WIDGET_CURSOR_A 100
#define WIDGET_CURSOR_B 0x60
#define WIDGET_SLOT    0x4a
#define CURSOR_MODE_DRAG 0x14

typedef struct UiLayoutPos {
    int nX;                   /* 16.16 */
    int nY;
} UiLayoutPos;

typedef struct Ov008Message15Record {
    u8  pad_00[0x24];
    int nPlacedSlot;          /* 0x24: -1 = not placed */
    u8  nOffsetCol;           /* 0x28 */
    u8  nOffsetRow;           /* 0x29 */
} Ov008Message15Record;

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x18];
} Ov008ShapeEntry;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x10];
    int menuState;            /* 0x0010 */
    u8  pad_0014[4];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x30 - 0x1c];
    int nBusyWord;            /* 0x0030 */
    int bHolding;             /* 0x0034 */
    u8  pad_0038[0x50 - 0x38];
    int bLifted;              /* 0x0050 */
    u8  pad_0054[0x64 - 0x54];
    u16 nCursorCol;           /* 0x0064 */
    u16 nCursorRow;           /* 0x0066 */
    u32 nDragPage;            /* 0x0068 */
    u16 nHomeCol;             /* 0x006c */
    u16 nHomeRow;             /* 0x006e */
    u8  pad_0070[0x19b4 - 0x70];
    Ov008Message15Record *pListNode; /* 0x19b4 */
    u8  pad_19b8[0x19c4 - 0x19b8];
    Ov008Message15Record *apPageSlot[3][GRID_ROWS * GRID_COLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e68 - 0x1ba4];
    int textList[4];          /* 0x1e68 */
    u8  pad_1e78[0x1f78 - 0x1e78];
    u8  summary[0x2078 - 0x1f78]; /* 0x1f78 */
    void *pCountText;         /* 0x2078 */
    u8  pad_207c[4];
    Ov008ShapeEntry *pShapeEntries; /* 0x2080 */
} Ov008MenuContext;

extern int   func_ov008_02050c54(void);                                          /* Ov008_GetContext */
extern void *func_ov008_02054788(int nCtx, int nId);                             /* FindEntryById */
extern void  func_ov008_020548bc(int nCtx, void *pEntry, UiLayoutPos *pPos);     /* Ov008_ApplyOffsetSum */
extern UiLayoutPos *func_ov008_02054820(int nCtx, void *pEntry);                 /* Ov008_GetEntryPos */
extern void  func_ov008_02054858(int nCtx, void *pEntry, UiLayoutPos *pPos);     /* Ov008_SetEntryPos */
extern void  func_ov008_0205eafc(Ov008MenuContext *pCtx, int nRow, void *pText, int nColour); /* Ov008_RepaintTextRow */
extern void *func_ov008_0208e66c(int *pList, Ov008Message15Record *pRecord);     /* text of a record */
extern void *func_ov008_0205fdac(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow); /* Ov008_FindGridHit */
extern int   func_ov008_020621f8(Ov008MenuContext *pCtx, Ov008ShapeEntry *pEntry, void *pHit, int nDx, int nDy); /* Ov008_DrawCardCountAndIcons */
extern void  func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);          /* SetEntrySlotsVisible */
extern void  func_ov008_02060e3c(Ov008MenuContext *pCtx);                        /* rebuild the grid */
extern void  func_ov008_02060ae8(Ov008MenuContext *pCtx);                        /* Ov008_RebuildGridHits */
extern void  func_ov008_0206ebd8(void);                                          /* Ov008_DisableRowBlock */
extern void  func_ov008_0206ed7c(void *pSummary);                                /* Ov008_RefreshEquipPanel */
extern int   func_ov008_0206eb64(int nMode, int nA, int nB);                     /* cursor mode request */
extern int   func_ov008_020642a8(Ov008MenuContext *pCtx);                        /* the cursor cell can be filled */
extern void  func_ov008_0206f384(void);                                          /* grid refresh */
extern void  func_ov008_02054c80(int nCtx, void *pEntry, int nFrame);            /* Ov008_ReleaseTwoSlotsEx */

int func_ov008_0206245c(Ov008MenuContext *pCtx, int nCol, int nRow, int nStep)
{
    UiLayoutPos pos = {0, 0};
    void *pAnchor;
    int nDx;
    void *pHit;
    int nCtx;
    int nPlacedSlot;
    int nDy;
    Ov008ShapeEntry *pShape;
    UiLayoutPos *pAnchorPos;
    Ov008Message15Record *pRecord;
    void *pSlotWidget;

    pShape = 0;
    pHit = 0;
    nPlacedSlot = -1;
    if (nCol < 0 || nCol >= GRID_COLS) {
        return 0;
    }
    if (nRow < 0 || nRow >= GRID_ROWS) {
        return 0;
    }
    nCtx = func_ov008_02050c54();
    pAnchor = func_ov008_02054788(nCtx, WIDGET_ANCHOR);
    pos.nX = nCol << 16;
    pos.nY = nRow << 16;
    if (pCtx->nBusyWord != 0 && !(pCtx->menuState == STATE_GRID && pCtx->bHolding == 0)) {
        pos.nX += 0x2000;
        pos.nY += 0x2000;
    }
    func_ov008_020548bc(nCtx, pAnchor, &pos);
    pAnchorPos = func_ov008_02054820(nCtx, pAnchor);
    pos.nX = pAnchorPos->nX + 0x6000;
    pos.nY = pAnchorPos->nY - 0xd000;
    func_ov008_02054858(nCtx, func_ov008_02054788(nCtx, WIDGET_CURSOR_A), &pos);
    func_ov008_02054858(nCtx, func_ov008_02054788(nCtx, WIDGET_CURSOR_B), &pos);
    pCtx->nCursorCol = nCol;
    pCtx->nCursorRow = nRow;
    pRecord = pCtx->pListNode;
    if (pRecord != 0) {
        nPlacedSlot = pRecord->nPlacedSlot;
        nDx = nCol - pRecord->nOffsetCol;
        nDy = nRow - pRecord->nOffsetRow;
    } else {
        pRecord = pCtx->apPageSlot[pCtx->nVisiblePage][nCol + nRow * GRID_COLS];
        if (pRecord == 0) {
            func_ov008_0205eafc(pCtx, 0, 0, COLOUR_ACTIVE);
        } else {
            func_ov008_0205eafc(pCtx, 0, func_ov008_0208e66c(pCtx->textList, pRecord), COLOUR_ACTIVE);
        }
    }
    if (nPlacedSlot >= 0) {
        pShape = &pCtx->pShapeEntries[nPlacedSlot];
        if (pCtx->bLifted != 0) {
            pHit = func_ov008_0205fdac(pCtx, pCtx->nDragPage, pCtx->nHomeCol, pCtx->nHomeRow);
        }
    }
    if (func_ov008_020621f8(pCtx, pShape, pHit, nDx, nDy) != 0) {
        func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_CURSOR_B), 0);
        func_ov008_0205eafc(pCtx, 0, func_ov008_0208e66c(pCtx->textList, pCtx->pListNode), COLOUR_ACTIVE);
        if (pCtx->nBusyWord == 0) {
            func_ov008_02060e3c(pCtx);
        }
    } else {
        if (nStep != 0 && pCtx->pListNode != 0) {
            if (pCtx->pCountText != 0) {
                func_ov008_0205eafc(pCtx, 0, pCtx->pCountText, COLOUR_COUNT);
            }
            func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_CURSOR_A), 0);
            func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_CURSOR_B), 1);
        }
        func_ov008_02060ae8(pCtx);
        func_ov008_0206ebd8();
        func_ov008_0206ed7c(pCtx->summary);
    }
    if (pCtx->pListNode != 0) {
        func_ov008_0206eb64(CURSOR_MODE_DRAG, 0, 2);
    } else if (func_ov008_020642a8(pCtx) != 0) {
        func_ov008_0206eb64(CURSOR_MODE_DRAG, 0, 1);
    } else {
        func_ov008_0206eb64(CURSOR_MODE_DRAG, 0, 0);
    }
    func_ov008_0206f384();
    pRecord = pCtx->pListNode;
    if (pRecord == 0) {
        pRecord = pCtx->apPageSlot[pCtx->nVisiblePage][nCol + nRow * GRID_COLS];
    }
    pSlotWidget = func_ov008_02054788(nCtx, WIDGET_SLOT);
    if (pRecord != 0 && pRecord->nPlacedSlot >= 0) {
        func_ov008_02054ba4(nCtx, pSlotWidget, 1);
        func_ov008_02054c80(nCtx, pSlotWidget, (u16)pRecord->nPlacedSlot);
    } else {
        func_ov008_02054ba4(nCtx, pSlotWidget, 0);
    }
    return 1;
}
