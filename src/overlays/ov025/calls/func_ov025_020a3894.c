/* func_ov025_020a3894 -- Ov008_DragScrollGauge: continue a scroll-gauge drag on
 * page B's scroll menu.  While the pen is down and moving (touch phase 0) the
 * knob follows the touch y (recentred, clamped to [0, 0x80 - scale]), the list
 * window is redrawn at the knob row and the selection kept within the eight
 * rows starting at the knob's row (offset + 8) / 16; the row flag is raised.
 * When the pen is up, widget 5 is reset to frame 0 and shown and the drag flag
 * cleared.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov008ScrollMenu {
    int bDragging;            /* 0x000 */
    int bRowMoved;            /* 0x004 */
    u8  pad_008[0x40 - 0x8];
    int nKnobOffset;          /* 0x040 */
    u8  pad_044[8];
    int nGaugeScale;          /* 0x04c */
    int nSelectedRow;         /* 0x050 */
} Ov008ScrollMenu;

typedef struct Ov008TouchState {
    u16 nX;                   /* 0x00 */
    u16 nY;                   /* 0x02 */
    u16 nTouching;            /* 0x04 */
    u16 nPhase;               /* 0x06 */
} Ov008TouchState;

#define KNOB_PAD    8
#define GAUGE_SPAN  0x80
#define ROWS_VISIBLE 8
#define WIDGET_SCROLL_HINT 5

extern int  func_ov025_02084a8c(void);                                    /* Ov008_GetCtxBlock4a80 */
extern Ov008ScrollMenu *func_ov025_02084b14(void);                        /* Ov008_GetPageB */
extern int  func_ov025_02084a64(void);                                    /* Ov008_GetCtxBlock954c */
extern void func_ov025_02089834(int nBlock, void *pOut);                  /* copy the touch record */
extern void func_ov025_020a2448(Ov008ScrollMenu *pMenu, int nPos);        /* Ov008_SetScrollGaugePos */
extern int  func_ov025_020a1d24(Ov008ScrollMenu *pMenu, int nCenter, int bFinalize, int bReport); /* Ov008_DrawListWindow */
extern void *func_ov025_0208843c(int nBlock, int nId);                    /* FindEntryById */
extern void func_ov025_02088928(int nBlock, void *pEntry, int nFrame);    /* Ov008_ReleaseTwoSlotsEx */
extern void func_ov025_0208884c(int nBlock, void *pEntry, int bVisible);  /* SetEntrySlotsVisible */

void func_ov025_020a3894(Ov008ScrollMenu *pDrag)
{
    int nBlock;
    Ov008ScrollMenu *pMenu;
    Ov008TouchState touch;
    int nPos;
    int nMax;
    int nRow;

    nBlock = func_ov025_02084a8c();
    pMenu = func_ov025_02084b14();
    func_ov025_02089834(func_ov025_02084a64(), &touch);
    if (touch.nTouching == 1) {
        if (touch.nPhase != 0) {
            return;
        }
        nPos = touch.nY - pMenu->nGaugeScale / 2 - KNOB_PAD;
        if (nPos < 0) {
            nPos = 0;
        }
        nMax = GAUGE_SPAN - pMenu->nGaugeScale;
        if (nPos > nMax) {
            nPos = nMax;
        }
        func_ov025_020a2448(pMenu, nPos);
        nRow = pMenu->nKnobOffset / 16;
        if (nRow < 0) {
            nRow = 0;
        }
        func_ov025_020a1d24(pMenu, nRow, 0, 0);
        nRow = (pMenu->nKnobOffset + KNOB_PAD) / 16;
        if (pMenu->nSelectedRow >= nRow + ROWS_VISIBLE) {
            pMenu->nSelectedRow = nRow + ROWS_VISIBLE - 1;
        }
        if (pMenu->nSelectedRow < nRow) {
            pMenu->nSelectedRow = nRow;
        }
        pDrag->bRowMoved = 1;
    } else {
        func_ov025_02088928(nBlock, func_ov025_0208843c(nBlock, WIDGET_SCROLL_HINT), 0);
        func_ov025_0208884c(nBlock, func_ov025_0208843c(nBlock, WIDGET_SCROLL_HINT), 1);
        pDrag->bDragging = 0;
    }
}
