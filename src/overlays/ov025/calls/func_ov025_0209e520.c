/* func_ov025_0209e520 -- Ov025_Tutorial_DragKnob: follow a touch on the scroll bar.  The touch
 * row (word +2 of the point) is taken from the top of the bar (0x20 + 4 * the row count, +0x60
 * of the page) and clamped to the bar's track (0x90 - 8 * rows); it maps to the window's top
 * topic (+0) over the scrollable range (count +4 less nine), and while the range is shorter
 * than the track the remainder becomes the row base (+0x64).  The cursor (+2) is kept within
 * the nine visible rows, the list scrolled (Ov025_Tutorial_ScrollTo 0209dcd0) and, when the
 * window moved, the rows refreshed (0209e3f8). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025TutorialList {
    void *pHeader;            /* 0x00 */
    void *pFooter;            /* 0x04 */
    void *apRow[15];          /* 0x08 */
    int  nVisible;            /* 0x44: rows placed by Ov025_Tutorial_PlaceRows */
    int  nTotal;              /* 0x48 */
    int  nScroll;             /* 0x4c: the row requested by Ov025_Tutorial_ScrollTo */
    int  nRows;               /* 0x50: 4..18 */
    int  nRowBase;            /* 0x54: the row offset the entries are placed from */
    int  bDragging;           /* 0x58: the scroll knob follows the stylus */
} Ov025TutorialList;          /* 0x5c */

typedef struct Ov025TutorialTopic {
    const u16 *pName;         /* 0x00 */
    int  nId;                 /* 0x04 */
} Ov025TutorialTopic;

typedef struct Ov025TutorialPage {
    s16  nTop;                /* 0x000: the first visible topic */
    s16  nCursor;             /* 0x002 */
    s16  nCount;              /* 0x004 */
    s16  nField06;            /* 0x006 */
    s16  nShown;              /* 0x008: the topic open in the text viewer */
    s16  nField0a;            /* 0x00a */
    int  nPhase : 2;          /* 0x00c bits 0-1: 1 = cursor moved, redraw */
    int  nTouch : 2;          /* 0x00c bits 2-3: the stylus state */
    int  nActive : 4;         /* 0x00c bits 4-7 */
    Ov025TutorialList list;   /* 0x010 */
    u8   textTitle[0xc];      /* 0x06c: "UI/cm/str/ttl_&.s.z" */
    u8   textTopics[0xc];     /* 0x078: "UI/tutorial/root_&.s.z" */
    u8   surface[0x3c];       /* 0x084: the text surface */
    int  nField0c0;           /* 0x0c0 */
    int  nTracker;            /* 0x0c4: the tag tracker (markers) */
    int  nCtx;                /* 0x0c8: the entry context (rows, arrows, knob) */
    Ov025TutorialTopic aTopic[58]; /* 0x0cc: the unlocked topics in display order */
    void *pMarkerCell;        /* 0x29c */
    void *pMarkerLitCell;     /* 0x2a0 */
    void *pUpArrow;           /* 0x2a4 */
    void *pDownArrow;         /* 0x2a8 */
    void *pKnob;              /* 0x2ac */
} Ov025TutorialPage;          /* 0x2b0: a view of page A (Ov008_GetPageA) */

typedef struct Ov025TouchPoint {
    u16  wX;                  /* 0x00 */
    u16  wY;                  /* 0x02 */
} Ov025TouchPoint;

extern Ov025TutorialPage *func_ov025_02084afc(void);                /* Ov008_GetPageA */
extern int   func_02020400(int nNum, int nDen);                     /* _s32_div_f */
extern void  func_ov025_0209dcd0(int nRow);                         /* Ov025_Tutorial_ScrollTo */
extern void  func_ov025_0209e3f8(void);                             /* Ov025_Tutorial_RefreshRows */

void func_ov025_0209e520(const Ov025TouchPoint *pTouch)
{
    Ov025TutorialPage *pPage;
    int nOldTop;
    int nOffset;
    int nTrack;
    int nRange;

    pPage = func_ov025_02084afc();
    nOffset = pTouch->wY - (pPage->list.nRows * 4 + 0x20);
    nTrack = 0x90 - pPage->list.nRows * 8;
    nRange = pPage->nCount - 9;
    nOldTop = pPage->nTop;
    pPage->list.nRowBase = 0;
    if (nOffset < 0) {
        nOffset = 0;
    } else if (nOffset >= nTrack) {
        nOffset = nTrack;
    } else if (nRange < nTrack) {
        pPage->list.nRowBase = nOffset - func_02020400(nTrack * func_02020400(nOffset * nRange, nTrack), nRange);
    }
    pPage->nTop = func_02020400(nOffset * nRange, nTrack);
    if (pPage->nCursor < pPage->nTop) {
        pPage->nCursor = pPage->nTop;
    } else if (pPage->nTop + 8 < pPage->nCursor) {
        pPage->nCursor = pPage->nTop + 8;
    }
    func_ov025_0209dcd0(pPage->nTop);
    if (nOldTop != pPage->nTop) {
        func_ov025_0209e3f8();
    }
}
