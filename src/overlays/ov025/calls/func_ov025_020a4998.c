/* func_ov025_020a4998 -- Ov008_TouchScrollGauge: start a scroll-gauge drag from
 * a touch on page B's scroll menu.  Ignored while the scene state is 2 or the
 * menu's own state (+0x44) is 1, or with something pending (+8).  A touch whose
 * y lies outside the knob (top + 8 .. top + 8 + scale) recentres the knob on it
 * (clamped to [0, 0x80 - scale]), redraws the list window at the knob row
 * (knob offset / 16 - 4, at least 0) and keeps the selection (+0x50) within the
 * eight visible rows; the row flag (+4) is raised.  Widget 5 is hidden and the
 * drag flag (+0) set.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov008ScrollMenu {
    int bDragging;            /* 0x000 */
    int bRowMoved;            /* 0x004 */
    int nPending;             /* 0x008 */
    u8  pad_00c[0x40 - 0xc];
    int nKnobOffset;          /* 0x040 */
    int nState;               /* 0x044 */
    int nKnobTop;             /* 0x048 */
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
extern int  OS_IsThreadAvailable_0x02085850(void);                        /* scene state */
extern int  func_ov025_02084a64(void);                                    /* Ov008_GetCtxBlock954c */
extern void func_ov025_02089834(int nBlock, void *pOut);                  /* copy the touch record */
extern void func_ov025_020a2448(Ov008ScrollMenu *pMenu, int nPos);        /* Ov008_SetScrollGaugePos */
extern int  func_ov025_020a1d24(Ov008ScrollMenu *pMenu, int nCenter, int bFinalize, int bReport); /* Ov008_DrawListWindow */
extern void *func_ov025_0208843c(int nBlock, int nId);                    /* FindEntryById */
extern void func_ov025_0208884c(int nBlock, void *pEntry, int bVisible);  /* SetEntrySlotsVisible */

void func_ov025_020a4998(void)
{
    int nBlock;
    Ov008ScrollMenu *pMenu;
    Ov008TouchState touch;
    int nKnobTop;
    int nPos;
    int nMax;
    int nRow;

    nBlock = func_ov025_02084a8c();
    pMenu = func_ov025_02084b14();
    if (OS_IsThreadAvailable_0x02085850() == 2 || pMenu->nState == 1) {
        return;
    }
    if (pMenu->nPending != 0) {
        return;
    }
    func_ov025_02089834(func_ov025_02084a64(), &touch);
    nKnobTop = pMenu->nKnobTop + KNOB_PAD;
    if (touch.nY < nKnobTop || nKnobTop + pMenu->nGaugeScale < touch.nY) {
        nPos = touch.nY - pMenu->nGaugeScale / 2 - KNOB_PAD;
        if (nPos < 0) {
            nPos = 0;
        }
        nMax = GAUGE_SPAN - pMenu->nGaugeScale;
        if (nPos > nMax) {
            nPos = nMax;
        }
        func_ov025_020a2448(pMenu, nPos);
        nRow = pMenu->nKnobOffset / 16 - 4;
        if (nRow < 0) {
            nRow = 0;
        }
        func_ov025_020a1d24(pMenu, nRow, 0, 0);
        if (pMenu->nSelectedRow >= nRow + ROWS_VISIBLE) {
            pMenu->nSelectedRow = nRow + ROWS_VISIBLE - 1;
        }
        if (pMenu->nSelectedRow < nRow) {
            pMenu->nSelectedRow = nRow;
        }
        pMenu->bRowMoved = 1;
    }
    func_ov025_0208884c(nBlock, func_ov025_0208843c(nBlock, WIDGET_SCROLL_HINT), 0);
    pMenu->bDragging = 1;
}
