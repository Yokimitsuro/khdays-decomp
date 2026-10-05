/* Ov025_EnterMenuState -- Ov008_EnterMenuState: put the grid menu into state
 * nState (+0x10, the previous state kept at +0x14 for state 1).  State 0
 * (list): widget 3 goes to (9.0, 32.0) fx32 and the cursor is moved to the
 * cursor cell (+0x64/+0x66) with step 1.  State 1 (grid): the same unless the
 * previous state was 0 or 1, in which case the grid is only reset; widget 3's
 * sub-item set 0 is pushed and the grid refreshed.  State 2 (drag), only with
 * a secondary panel (+0x4c): widget 3 goes to (104.0, 32.0); a lifted node
 * (+0x19b4 with +0x50) is removed from its home cell (+0x68, +0x6c/+0x6e);
 * the grid is reset and, in menu mode 0 (+0x8), the selected page (+0x9c) is
 * switched to -- on failure row 0 is highlighted and the selection cleared --
 * and cursor mode 0x14 with 0 requested; then the grid is refreshed.
 */

#include "nitro/types.h"

#define STATE_LIST   0
#define STATE_GRID   1
#define STATE_DRAG   2
#define WIDGET_DRAG  3
#define CURSOR_MODE_DRAG 0x14
#define POS_LIST_X   0x9000
#define POS_DRAG_X   0x68000
#define POS_Y        0x20000

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x8];
    int menuMode;             /* 0x0008 */
    u8  pad_000c[4];
    int menuState;            /* 0x0010 */
    int prevMenuState;        /* 0x0014 */
    u8  pad_0018[0x4c - 0x18];
    int bSecondaryPanel;      /* 0x004c */
    int bLifted;              /* 0x0050 */
    u8  pad_0054[0x64 - 0x54];
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u32 nDragNode;            /* 0x0068: home page of the lifted node */
    u16 nHomeCol;             /* 0x006c */
    u16 nHomeRow;             /* 0x006e */
    u8  pad_0070[0x9c - 0x70];
    int nSelectedRow;         /* 0x009c */
    u8  pad_00a0[0x19b4 - 0xa0];
    void *pListNode;          /* 0x19b4 */
} Ov008MenuContext;

extern int  Ov025_GetContext(void);                                    /* Ov008_GetContext */
extern void *Ov025_FindEntryById(int nCtx, int nId);                      /* FindEntryById */
extern void Ov025_Widget_SetPoint(int nCtx, void *pEntry, UiLayoutPos *pPos); /* set the base position */
extern int  Ov025_MoveGridCursor(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep); /* move the cursor */
extern void Ov025_ResetGridDrag(Ov008MenuContext *pCtx, int nArg);        /* grid reset */
extern void Ov025_PushSubitemSet(int nCtx, void *pEntry, int nValue);      /* Ov008_PushSubitemSet */
extern void Ov025_PageB_UploadSurface154(void);                                    /* grid refresh */
extern int  Ov025_RemoveGridNode(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow, int bSilent); /* Ov008_RemoveGridNode */
extern int  Ov025_SelectListRow(Ov008MenuContext *pCtx, int nPage);       /* switch page */
extern void Ov025_HighlightListRow(Ov008MenuContext *pCtx, int nRow);        /* highlight a visible row */
extern int Ov025_DrawPageBElement(int param_1, int param_2, ...); /* cursor mode request */

void Ov025_EnterMenuState(Ov008MenuContext *pCtx, int nState)
{
    UiLayoutPos pos = { 0, 0 };
    int nCtx;
    void *pEntry;
    int nPrev;

    nCtx = Ov025_GetContext();
    pEntry = Ov025_FindEntryById(nCtx, WIDGET_DRAG);
    nPrev = pCtx->menuState;
    pCtx->menuState = nState;
    switch (nState) {
    case STATE_LIST:
        pos.nX = POS_LIST_X;
        pos.nY = POS_Y;
        Ov025_Widget_SetPoint(nCtx, pEntry, &pos);
        Ov025_MoveGridCursor(pCtx, pCtx->nColumn, pCtx->nRowSel, 1);
        break;
    case STATE_GRID:
        if (nPrev != STATE_LIST && nPrev != STATE_GRID) {
            pos.nX = POS_LIST_X;
            pos.nY = POS_Y;
            Ov025_Widget_SetPoint(nCtx, pEntry, &pos);
            Ov025_MoveGridCursor(pCtx, pCtx->nColumn, pCtx->nRowSel, 1);
        } else {
            Ov025_ResetGridDrag(pCtx, 0);
        }
        Ov025_PushSubitemSet(nCtx, pEntry, 0);
        pCtx->prevMenuState = nPrev;
        Ov025_PageB_UploadSurface154();
        break;
    case STATE_DRAG:
        if (pCtx->bSecondaryPanel == 0) {
            return;
        }
        pos.nX = POS_DRAG_X;
        pos.nY = POS_Y;
        Ov025_Widget_SetPoint(nCtx, pEntry, &pos);
        if (pCtx->pListNode != 0 && pCtx->bLifted != 0) {
            Ov025_RemoveGridNode(pCtx, pCtx->nDragNode, pCtx->nHomeCol, pCtx->nHomeRow, 0);
        }
        Ov025_ResetGridDrag(pCtx, 0);
        if (pCtx->menuMode == 0) {
            if (Ov025_SelectListRow(pCtx, pCtx->nSelectedRow) == 0) {
                Ov025_HighlightListRow(pCtx, 0);
                pCtx->nSelectedRow = 0;
            }
            Ov025_DrawPageBElement(CURSOR_MODE_DRAG, 0, 0);
        }
        Ov025_PageB_UploadSurface154();
        break;
    }
}
