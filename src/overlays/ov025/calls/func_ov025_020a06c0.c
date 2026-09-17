/* func_ov025_020a06c0 -- Ov025_Reports_PlaceMarkers: place the ten row markers of the reports
 * list down the left column.  The marker under the cursor (row = cursor +2 - top +0 of the
 * page) uses cell 4 (+0x264); a row whose report (records of 0x40 bytes at +0x1e8, below the
 * count +4) has been read (word +0xc) uses the selection cell (+0x268), the others cell 3
 * (+0x260); each is put at column 1, row 2 + 2 * i in the page's tag tracker (+0xb4; 0208951c)
 * and its callback invoked (Ov008_TagTracker_InvokeCallback 02089544). */
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
extern void  func_ov025_0208951c(int nTracker, void *pCell, s16 nX, s16 nY); /* Ov008_TagTracker_SetCellPos */
extern void  func_ov025_02089544(int nTracker, void *pCell);        /* Ov008_TagTracker_InvokeCallback */

void func_ov025_020a06c0(void)
{
    Ov025ReportsPage *pPage;
    int i;
    int nRow;
    s16 nY;
    void *pCell;
    int bRead;

    pPage = func_ov025_02084afc();
    nRow = pPage->nCursor - pPage->nTop;
    nY = 2;
    for (i = 0; i < 10; i++) {
        if (nRow == i) {
            pCell = pPage->pCell4;
        } else {
            bRead = 0;
            if (pPage->nTop + i < pPage->nCount && ((Ov025ReportsEntry *)pPage->pEntries)[pPage->nTop + i].pRead != 0) {
                bRead = 1;
            }
            if (bRead) {
                pCell = pPage->pSelectCell;
            } else {
                pCell = pPage->pCell3;
            }
        }
        func_ov025_0208951c(pPage->nTracker, pCell, 1, nY);
        func_ov025_02089544(pPage->nTracker, pCell);
        nY += 2;
    }
}
