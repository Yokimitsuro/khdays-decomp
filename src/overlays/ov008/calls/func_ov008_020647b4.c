/* func_ov008_020647b4 -- Ov008_UpdateKnobDrag: one step of dragging the
 * inventory list's scroll knob with the stylus.  On release menu button 5 is
 * refreshed, states 0 / 1 re-step the cursor cell (0206245c with the cursor
 * column / row, step 1), state 2 requests cursor mode 0x14 and a grid refresh,
 * and the drag flag (+0x24) is cleared.  While the pen is down, list mode 0
 * scrolls the page list (0205f388: knob position = pen y - knob / 2 - 0x18,
 * clamped to 0 .. 0x7f - knob; base +0x78, 8 rows, range 0x7f) and then keeps
 * the selected row (+0x9c) inside the eight visible rows from +0x74, moving
 * the highlight (0205f084) to the row's slot; mode 1 only clears the drag flag.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

#define LIST_MODE_PAGE 0
#define LIST_MODE_BUSY 1
#define KNOB_RANGE     0x7f
#define VISIBLE_ROWS   8
#define KNOB_TOP       0x18
#define CURSOR_MODE_DRAG 0x14

typedef struct Ov008TouchRecord {
    u16 nX;                   /* 0x00 */
    u16 nY;                   /* 0x02 */
    u16 nTouching;            /* 0x04 */
} Ov008TouchRecord;

typedef struct Ov008MenuContext {
    u8  pad_0000[8];
    int nListMode;            /* 0x0008 */
    u8  pad_000c[4];
    int menuState;            /* 0x0010 */
    u8  pad_0014[0x24 - 0x14];
    int bDrag;                /* 0x0024 */
    u8  pad_0028[0x64 - 0x28];
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u8  pad_0068[0x74 - 0x68];
    int nScrollRow;           /* 0x0074 */
    int nPageCount;           /* 0x0078 */
    u8  pad_007c[0x9c - 0x7c];
    int nSelectedRow;         /* 0x009c */
    u8  pad_00a0[0x2f8 - 0xa0];
    int nKnobLength;          /* 0x02f8 */
} Ov008MenuContext;

typedef void (*Ov008RowHighlightFn)(Ov008MenuContext *pCtx, int nRow);

extern void func_ov008_02055dcc(void *pOut);                              /* touch record */
extern void func_ov008_0205f388(Ov008MenuContext *pCtx, int nPos, int nBase, int nRows, int nRange); /* eased scroll */
extern void func_ov008_0205f084(Ov008MenuContext *pCtx, int nRow);        /* highlight a visible row */
extern void func_ov008_0206f7b0(int nArg);                                /* Ov008_UpdateMenuButton5 */
extern int  func_ov008_0206245c(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep);
extern int  func_ov008_0206eb64(int nMode, int nA, int nB);               /* cursor mode request */
extern void func_ov008_0206f384(void);                                    /* grid refresh */

void func_ov008_020647b4(Ov008MenuContext *pCtx)
{
    Ov008TouchRecord touch;
    int nRange;
    int nBase;
    int nRows;
    int nFirst;
    int *pSelected;
    Ov008RowHighlightFn pfnHighlight;
    int nPos;
    int nSelected;

    pSelected = 0;
    func_ov008_02055dcc(&touch);
    if (touch.nTouching != 0) {
        switch (pCtx->nListMode) {
        case LIST_MODE_PAGE:
            pSelected = &pCtx->nSelectedRow;
            nBase = pCtx->nPageCount;
            nRange = KNOB_RANGE;
            nRows = VISIBLE_ROWS;
            pfnHighlight = func_ov008_0205f084;
            break;
        case LIST_MODE_BUSY:
            pCtx->bDrag = 0;
            return;
        }
        nPos = touch.nY - pCtx->nKnobLength / 2 - KNOB_TOP;
        if (nPos < 0) {
            nPos = 0;
        }
        if (nPos > nRange - pCtx->nKnobLength) {
            nPos = nRange - pCtx->nKnobLength;
        }
        func_ov008_0205f388(pCtx, nPos, nBase, nRows, nRange);
        nSelected = *pSelected;
        switch (pCtx->nListMode) {
        case LIST_MODE_PAGE:
            nFirst = pCtx->nScrollRow;
            break;
        }
        if (nFirst <= nSelected && nSelected < nFirst + nRows) {
            pfnHighlight(pCtx, nSelected - nFirst);
        } else if (nSelected < nFirst) {
            pfnHighlight(pCtx, 0);
            *pSelected = nFirst;
        } else {
            pfnHighlight(pCtx, nRows - 1);
            *pSelected = nFirst + (nRows - 1);
        }
        return;
    }
    func_ov008_0206f7b0(1);
    switch (pCtx->menuState) {
    case 2:
        func_ov008_0206eb64(CURSOR_MODE_DRAG, 0, 0);
        func_ov008_0206f384();
        break;
    case 0:
    case 1:
        func_ov008_0206245c(pCtx, pCtx->nColumn, pCtx->nRowSel, 1);
        break;
    }
    pCtx->bDrag = 0;
}
