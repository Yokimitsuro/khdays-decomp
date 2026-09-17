/* func_ov025_0209f548 -- Ov025_Reports_SetupList: size the reports list (+8 of the page) for
 * nTotal reports.  All 17 row entries are hidden (0208884c), the total kept, the scroll, the
 * row base and the drag flag cleared; the visible row count (+0x60) is 20 for up to 10 reports,
 * otherwise 0xa0 / nTotal clamped to 4..20 (the 64-bit divide 02020400), and the loop bound
 * (+0x54) is that count less four.  The header and footer entries are shown and the rows are
 * placed from the top (Ov025_Reports_PlaceRows 0209f488 with row 0). */
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

extern Ov025ReportsPage *func_ov025_02084afc(void);                 /* Ov008_GetPageA */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern int   func_02020400(int nNum, int nDen);                     /* _s32_div_f */
extern void  func_ov025_0209f488(int nRow);                         /* Ov025_Reports_PlaceRows */

void func_ov025_0209f548(int nTotal)
{
    Ov025ReportsPage *pPage;
    Ov025ReportsList *pList;
    int i;

    pPage = func_ov025_02084afc();
    pList = &pPage->list;
    for (i = 0; i < 17; i++) {
        func_ov025_0208884c(pPage->nCtx, pList->apRow[i], 0);
    }
    pList->nTotal = nTotal;
    pList->nScroll = 0;
    pList->bDragging = 0;
    pList->nRowBase = 0;
    if (nTotal <= 10) {
        pList->nRows = 0x14;
    } else {
        pList->nRows = func_02020400(0xa0, nTotal);
        if (pList->nRows < 4) {
            pList->nRows = 4;
        }
        if (pList->nRows > 0x14) {
            pList->nRows = 0x14;
        }
    }
    pList->nVisible = pList->nRows - 4;
    func_ov025_0208884c(pPage->nCtx, pList->pHeader, 1);
    func_ov025_0208884c(pPage->nCtx, pList->pFooter, 1);
    func_ov025_0209f488(0);
}
