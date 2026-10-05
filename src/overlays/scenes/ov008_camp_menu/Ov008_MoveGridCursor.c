/* Ov008_MoveGridCursor -- Ov008_MoveGridCursor: put the grid cursor on cell
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

#include "nitro/types.h"

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

extern int   Ov008_GetContext(void);                                          /* Ov008_GetContext */
extern void *Ov008_FindEntryById(int nCtx, int nId);                             /* FindEntryById */
extern void  Ov008_ApplyOffsetSum(int nCtx, void *pEntry, UiLayoutPos *pPos);     /* Ov008_ApplyOffsetSum */
extern UiLayoutPos *Ov008_GetEntryPos(int nCtx, void *pEntry);                 /* Ov008_GetEntryPos */
extern void  Ov008_SetEntryPos(int nCtx, void *pEntry, UiLayoutPos *pPos);     /* Ov008_SetEntryPos */
extern void  Ov008_RepaintTextRow(Ov008MenuContext *pCtx, int nRow, void *pText, int nColour); /* Ov008_RepaintTextRow */
extern void *Ov008_GetItemDescriptionForMember(int *pList, Ov008Message15Record *pRecord);     /* text of a record */
extern void *Ov008_FindGridHit(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow); /* Ov008_FindGridHit */
extern int   Ov008_DrawCardCountAndIcons(Ov008MenuContext *pCtx, Ov008ShapeEntry *pEntry, void *pHit, int nDx, int nDy); /* Ov008_DrawCardCountAndIcons */
extern void  Ov008_SetEntrySlotsVisible(int nCtx, void *pEntry, int bVisible);          /* SetEntrySlotsVisible */
extern void  Ov008_PreviewDropSummary(Ov008MenuContext *pCtx);                        /* rebuild the grid */
extern void  Ov008_RebuildGridHits(Ov008MenuContext *pCtx);                        /* Ov008_RebuildGridHits */
extern void  Ov008_DisableRowBlock(void);                                          /* Ov008_DisableRowBlock */
extern void  Ov008_RefreshEquipPanel(void *pSummary);                                /* Ov008_RefreshEquipPanel */
extern int Ov008_DrawPageBElement(int param_1, int param_2, ...); /* cursor mode request */
extern int   Ov008_CanFillNodeGap(Ov008MenuContext *pCtx);                        /* the cursor cell can be filled */
extern void  Ov008_PageB_UploadSurface154(void);                                          /* grid refresh */
extern void  Ov008_ReleaseTwoSlotsEx(int nCtx, void *pEntry, int nFrame);            /* Ov008_ReleaseTwoSlotsEx */

int Ov008_MoveGridCursor(Ov008MenuContext *pCtx, int nCol, int nRow, int nStep)
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
    nCtx = Ov008_GetContext();
    pAnchor = Ov008_FindEntryById(nCtx, WIDGET_ANCHOR);
    pos.nX = nCol << 16;
    pos.nY = nRow << 16;
    if (pCtx->nBusyWord != 0 && !(pCtx->menuState == STATE_GRID && pCtx->bHolding == 0)) {
        pos.nX += 0x2000;
        pos.nY += 0x2000;
    }
    Ov008_ApplyOffsetSum(nCtx, pAnchor, &pos);
    pAnchorPos = Ov008_GetEntryPos(nCtx, pAnchor);
    pos.nX = pAnchorPos->nX + 0x6000;
    pos.nY = pAnchorPos->nY - 0xd000;
    Ov008_SetEntryPos(nCtx, Ov008_FindEntryById(nCtx, WIDGET_CURSOR_A), &pos);
    Ov008_SetEntryPos(nCtx, Ov008_FindEntryById(nCtx, WIDGET_CURSOR_B), &pos);
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
            Ov008_RepaintTextRow(pCtx, 0, 0, COLOUR_ACTIVE);
        } else {
            Ov008_RepaintTextRow(pCtx, 0, Ov008_GetItemDescriptionForMember(pCtx->textList, pRecord), COLOUR_ACTIVE);
        }
    }
    if (nPlacedSlot >= 0) {
        pShape = &pCtx->pShapeEntries[nPlacedSlot];
        if (pCtx->bLifted != 0) {
            pHit = Ov008_FindGridHit(pCtx, pCtx->nDragPage, pCtx->nHomeCol, pCtx->nHomeRow);
        }
    }
    /* Without a list node nDx and nDy are never set: the ROM passes whatever r6 and their stack
     * slot hold, as this C does. It is harmless: Ov008_DrawCardCountAndIcons reads them only with a
     * shape, and that path has none (pShape stays 0, nPlacedSlot -1). Setting them would add code
     * the ROM does not have. */
    if (Ov008_DrawCardCountAndIcons(pCtx, pShape, pHit, nDx, nDy) != 0) {
        Ov008_SetEntrySlotsVisible(nCtx, Ov008_FindEntryById(nCtx, WIDGET_CURSOR_B), 0);
        Ov008_RepaintTextRow(pCtx, 0, Ov008_GetItemDescriptionForMember(pCtx->textList, pCtx->pListNode), COLOUR_ACTIVE);
        if (pCtx->nBusyWord == 0) {
            Ov008_PreviewDropSummary(pCtx);
        }
    } else {
        if (nStep != 0 && pCtx->pListNode != 0) {
            if (pCtx->pCountText != 0) {
                Ov008_RepaintTextRow(pCtx, 0, pCtx->pCountText, COLOUR_COUNT);
            }
            Ov008_SetEntrySlotsVisible(nCtx, Ov008_FindEntryById(nCtx, WIDGET_CURSOR_A), 0);
            Ov008_SetEntrySlotsVisible(nCtx, Ov008_FindEntryById(nCtx, WIDGET_CURSOR_B), 1);
        }
        Ov008_RebuildGridHits(pCtx);
        Ov008_DisableRowBlock();
        Ov008_RefreshEquipPanel(pCtx->summary);
    }
    if (pCtx->pListNode != 0) {
        Ov008_DrawPageBElement(CURSOR_MODE_DRAG, 0, 2);
    } else if (Ov008_CanFillNodeGap(pCtx) != 0) {
        Ov008_DrawPageBElement(CURSOR_MODE_DRAG, 0, 1);
    } else {
        Ov008_DrawPageBElement(CURSOR_MODE_DRAG, 0, 0);
    }
    Ov008_PageB_UploadSurface154();
    pRecord = pCtx->pListNode;
    if (pRecord == 0) {
        pRecord = pCtx->apPageSlot[pCtx->nVisiblePage][nCol + nRow * GRID_COLS];
    }
    pSlotWidget = Ov008_FindEntryById(nCtx, WIDGET_SLOT);
    if (pRecord != 0 && pRecord->nPlacedSlot >= 0) {
        Ov008_SetEntrySlotsVisible(nCtx, pSlotWidget, 1);
        Ov008_ReleaseTwoSlotsEx(nCtx, pSlotWidget, (u16)pRecord->nPlacedSlot);
    } else {
        Ov008_SetEntrySlotsVisible(nCtx, pSlotWidget, 0);
    }
    return 1;
}
