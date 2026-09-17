/* func_ov025_0209ffd0 -- Ov025_Reports_PageDown: scroll the reports window (+0 of the page) down
 * by ten records, or to the last window, the cursor (+2) with it, while no row number is held
 * (+0x25c), the window is not at the end (count - 9) and neither L nor R (bits 6-7 of
 * data_0204c18c) is held.  With A held (bit 0) in read-variant mode (+0xc0, reports only) the
 * cursor then settles on the nearest record of the new window that has a read variant (+0xc),
 * searching outward up to ten rows, and the page turn is abandoned when there is none.  A moved
 * window resets the row base (+0x5c) and plays the cursor sound (02033b78); the rows are
 * highlighted (Ov025_Reports_HighlightRows 020a0a14) in read-variant mode, the record (or its
 * read variant, +0x40) marked owned (Ov025_QueryItemFlags 0209e820) when it has nothing pending,
 * and, when the window moved, the rows refresh (020a076c) and +0x22c is cleared.  Codegen as
 * Ov025_Reports_PageUp (s16 old window position, nTop / nCursor / nOldTop order, d before nLast). */
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
    int  bReadVariants;       /* 0x0c0: the read variants can be browsed with A held */
    int  nFieldc4;            /* 0x0c4 */
    int  nState;              /* 0x0c8 */
    int  nFieldcc;            /* 0x0cc: the row press sound was played */
    u8   aRow[10][0x1c];      /* 0x0d0 */
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
} Ov025ReportsPage;

extern Ov025ReportsPage *func_ov025_02084afc(void);                 /* Ov008_GetPageA */
extern u16   data_0204c18c;                                         /* held keys */
extern void  func_ov025_020a0a14(void);                             /* Ov025_Reports_HighlightRows */
extern u32   func_ov025_0209e820(u32 nItem, u32 bSet);              /* Ov025_QueryItemFlags */
extern void  func_02033b78(int nSound, int nArg);                   /* PlaySound */
extern void  func_ov025_020a076c(void);                             /* Ov025_Reports_RefreshRows */

void func_ov025_0209ffd0(void)
{
    Ov025ReportsPage *pPage;
    int nCount;
    int nTop;
    int nCursor;
    s16 nOldTop;
    int nMaxTop;
    int d;
    int nLast;
    int bMoved;
    int nMode;
    int nItem;

    pPage = func_ov025_02084afc();
    nCount = pPage->nCount;
    nMaxTop = nCount - 9;
    nOldTop = pPage->nTop;
    nCursor = pPage->nCursor;
    if (pPage->pHeldEntry != 0) {
        return;
    }
    if (nOldTop >= nMaxTop) {
        return;
    }
    if (data_0204c18c & 0xc0) {
        return;
    }
    if (nOldTop < nMaxTop - 10) {
        nTop = nOldTop + 10;
        nCursor += 10;
    } else {
        nCursor += nMaxTop - nOldTop - 1;
        nTop = nMaxTop - 1;
    }
    if (pPage->bReadVariants != 0 && (data_0204c18c & 1) && pPage->bMissionMode == 0) {
        nLast = nTop + 9;
        if (nCount <= nLast) {
            nLast = nCount - 1;
        }
        for (d = 0; d < 10; d++) {
            if (nTop <= nCursor - d && pPage->pEntries[nCursor - d].pRead != 0) {
                nCursor = nCursor - d;
                break;
            }
            if (nCursor + d <= nLast && pPage->pEntries[nCursor + d].pRead != 0) {
                nCursor = nCursor + d;
                break;
            }
        }
        if (nCursor - d < nTop && nLast < nCursor + d) {
            return;
        }
    }
    bMoved = nOldTop != nTop;
    if (bMoved) {
        pPage->list.nRowBase = 0;
        func_02033b78(0, 0);
    }
    pPage->nTop = nTop;
    pPage->nCursor = nCursor;
    if (pPage->bReadVariants != 0) {
        func_ov025_020a0a14();
    }
    nMode = pPage->bMissionMode;
    if (nMode == 0 || pPage->pEntries[pPage->nCursor].nPending == 0) {
        if (nMode == 0 && pPage->bReadVariants != 0 && (data_0204c18c & 1)) {
            nItem = 0x40;
        } else {
            nItem = 0;
        }
        func_ov025_0209e820(pPage->nCursor + nItem, 1);
    }
    if (!bMoved) {
        return;
    }
    func_ov025_020a076c();
    pPage->nField22c = 0;
}
