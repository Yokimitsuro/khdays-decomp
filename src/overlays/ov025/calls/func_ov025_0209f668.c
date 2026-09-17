/* func_ov025_0209f668 -- Ov025_Reports_DragKnob: follow a touch on the scroll bar.  The touch
 * row (word +2 of the point) is taken from the top of the bar (0x10 + 4 * the row count, +0x60
 * of the page) and clamped to the bar's track (0xa0 - 8 * rows); it maps to the window's top
 * report (+0) over the scrollable range (count +4 less ten), and while the range is shorter
 * than the track the remainder becomes the row base (+0x64).  The cursor (+2) is kept within
 * the ten visible rows and the list scrolled (Ov025_Reports_ScrollTo 0209f60c).  When the
 * cursor moved, the report under it is marked read (0209e820) -- an enemy profile only once
 * its record (0x40 bytes at +0x1e8, bits 6..15 of its first word) has no pending count -- and
 * the byte at +0x22c cleared; when the window moved the rows are refreshed (020a076c). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025ReportsList {
    void *pHeader;            /* 0x00 */
    void *pFooter;            /* 0x04 */
    void *apRow[17];          /* 0x08 */
    int  nVisible;            /* 0x4c: rows placed by Ov025_Reports_PlaceRows */
    int  nTotal;              /* 0x50 */
    int  nScroll;             /* 0x54 */
    int  nRows;               /* 0x58: 4..20 */
    int  nRowBase;            /* 0x5c: the row offset the entries are placed from */
    int  bDragging;           /* 0x60: the scroll knob follows the stylus */
} Ov025ReportsList;           /* 0x64 */

typedef struct Ov025ReportsRow {
    void *pTitle;             /* 0x00: entry 0x33 + row */
    void *pMark1;             /* 0x04: entry 0x3d + row */
    void *pMark2;             /* 0x08: entry 0x47 + row */
    void *pMark3;             /* 0x0c: entry 0x51 + row */
    void *pMark4;             /* 0x10: entry 0x5b + row */
    void *pBadge;             /* 0x14: entry 0x6f + row */
    void *pNumber;            /* 0x18: entry 0x65 + row */
} Ov025ReportsRow;            /* 0x1c */

typedef struct Ov025ReportsEntry {
    u16  nId : 9;             /* 0x00 bits 0-8 */
    u16  nFlag9 : 1;          /* 0x00 bit 9 */
    u16  nPending : 6;        /* 0x00 bits 10-15: enemies still to defeat */
    u8   pad_02[0xa];
    struct Ov025ReportsEntry *pRead; /* 0x0c: the read variant of the record, if any */
    u8   pad_10[0x40 - 0x10];
} Ov025ReportsEntry;          /* 0x40 */

typedef struct Ov025ReportsPage {
    s16  nTop;                /* 0x000: the first visible report */
    s16  nCursor;             /* 0x002 */
    s16  nCount;              /* 0x004 */
    s16  nField06;            /* 0x006 */
    Ov025ReportsList list;    /* 0x008 */
    u8   text[0xc];           /* 0x06c: the report / enemy strings */
    u8   surface[0x3c];       /* 0x078 */
    int  nTracker;            /* 0x0b4: the tag tracker */
    int  nCtx;                /* 0x0b8: the entry context */
    int  nFieldbc;            /* 0x0bc */
    int  nFieldc0;            /* 0x0c0 */
    int  nFieldc4;            /* 0x0c4 */
    int  nState;              /* 0x0c8 */
    int  nFieldcc;            /* 0x0cc: the row press sound was played */
    Ov025ReportsRow aRow[10]; /* 0x0d0 */
    Ov025ReportsEntry *pEntries; /* 0x1e8: the per-report records */
    Ov025ReportsEntry current; /* 0x1ec: the record shown in the detail area */
    u8   nField22c;           /* 0x22c */
    u8   pad_22d[0x230 - 0x22d];
    void *pTable;             /* 0x230: the report table file */
    void *pSpriteFile;        /* 0x234: the report sprite file */
    u8   pad_238[0x248 - 0x238];
    u16  aSeen[8];            /* 0x248: the seen bits per group */
    int  bMissionMode;        /* 0x258: enemy profiles rather than reports */
    void *pHeldEntry;         /* 0x25c: the row number entry under the stylus */
    void *pCell3;             /* 0x260 */
    void *pCell4;             /* 0x264 */
    void *pSelectCell;        /* 0x268 */
    void *pUpArrow;           /* 0x26c */
    void *pDownArrow;         /* 0x270 */
    void *pKnob;              /* 0x274 */
} Ov025ReportsPage;           /* 0x278: a view of page A (Ov008_GetPageA) */

typedef struct Ov025TouchPoint {
    u16  wX;                  /* 0x00 */
    u16  wY;                  /* 0x02 */
} Ov025TouchPoint;

extern Ov025ReportsPage *func_ov025_02084afc(void);                 /* Ov008_GetPageA */
extern int   func_02020400(int nNum, int nDen);                     /* _s32_div_f */
extern void  func_ov025_0209f60c(int nRow);                         /* Ov025_Reports_ScrollTo */
extern u32   func_ov025_0209e820(u32 nReport, u32 bMark);           /* Ov025_Reports_QueryFlags */
extern void  func_ov025_020a076c(int nTop);                         /* Ov025_Reports_RefreshRows */

void func_ov025_0209f668(const Ov025TouchPoint *pTouch)
{
    Ov025ReportsPage *pPage;
    int nOffset;
    int nTrack;
    int nRange;
    int nOldCursor;
    int nOldTop;

    pPage = func_ov025_02084afc();
    nOffset = pTouch->wY - (pPage->list.nRows * 4 + 0x10);
    nTrack = 0xa0 - pPage->list.nRows * 8;
    nRange = pPage->nCount - 10;
    nOldCursor = pPage->nCursor;
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
    } else if (pPage->nTop + 9 < pPage->nCursor) {
        pPage->nCursor = pPage->nTop + 9;
    }
    func_ov025_0209f60c(pPage->nTop);
    if (nOldCursor != pPage->nCursor) {
        if (pPage->bMissionMode == 0 || ((Ov025ReportsEntry *)pPage->pEntries)[pPage->nCursor].nPending == 0) {
            func_ov025_0209e820(pPage->nCursor, 1);
        }
        pPage->nField22c = 0;
    }
    if (nOldTop != pPage->nTop) {
        func_ov025_020a076c(pPage->nTop);
    }
}
