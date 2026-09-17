/* func_ov025_020a0a9c -- Ov025_Reports_HandleInput: the stylus and A-button handling of the
 * reports page, once it is running (+0xc8).  Outside read-variant mode (+0xc0): a fresh press
 * (+0xbc latches it) on the scroll bar box (data_ov025_020b421c; Ov025_PointInBox 0209e880)
 * starts the knob drag (+0x60 of the list; Ov025_Reports_DragKnob 0209f668) and a press on one
 * of the ten visible rows (x 16..0xdf, y from 16, 16 pixels a row) moves the cursor (+2) to it,
 * marks the record owned when it has nothing pending (Ov025_QueryItemFlags 0209e820), plays the
 * press sound once (+0xcc) and refreshes the rows (020a076c); a held press keeps dragging the
 * knob.  On release the drag ends and a held row number (+0x25c) copies its record into the
 * detail record (+0x1ec), highlights the rows (020a0a14) and redraws the row texts (020a0300).
 * Then, with the stylus up, A held enters read-variant mode: the cursor's read variant (+0xc)
 * becomes the detail record, its item is marked owned (+0x40 for reports) and the rows refresh;
 * A released leaves it, restoring the record itself and redrawing the row texts.  Codegen: the
 * row search keeps the window top as an s16 local (it lands in ip and leaves r5 to the touch y)
 * with the running topic and the count as ints, declared nRow, nY, nTopic, nCount, nTop; the
 * held entry and the records are read through the page, not copied. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025TouchPoint {
    u16  wX;                  /* 0x00 */
    u16  wY;                  /* 0x02 */
} Ov025TouchPoint;

typedef struct Ov025TouchInput {
    u16  wX;                  /* 0x00 */
    u16  wY;                  /* 0x02 */
    u16  wHeld;               /* 0x04 */
    u16  wPad;                /* 0x06 */
} Ov025TouchInput;

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

typedef struct Ov025ReportsRow {
    void *pTitle;             /* 0x00: entry 0x33 + row */
    void *apDigit[3];         /* 0x04: entries 0x3d / 0x47 / 0x51 + row: the report number */
    void *pMark;              /* 0x10: entry 0x5b + row */
    void *pBadge;             /* 0x14: entry 0x6f + row: the owned / seen badge */
    void *pNumber;            /* 0x18: entry 0x65 + row: the read-variant mark */
} Ov025ReportsRow;            /* 0x1c */

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
    int  bPressed;            /* 0x0bc: the stylus is down */
    int  bReadVariants;       /* 0x0c0: the read variants are shown (A held) */
    int  nFieldc4;            /* 0x0c4 */
    int  nState;              /* 0x0c8 */
    int  bPressSound;         /* 0x0cc: the row press sound was played */
    Ov025ReportsRow aRow[10]; /* 0x0d0 */
    Ov025ReportsEntry *pEntries; /* 0x1e8: the per-report records */
    Ov025ReportsEntry current; /* 0x1ec: the record shown in the detail area */
    u8   nField22c;           /* 0x22c */
    u8   pad_22d[0x258 - 0x22d];
    int  bMissionMode;        /* 0x258: enemy profiles rather than reports */
    void *pHeldEntry;         /* 0x25c: the row number entry under the stylus */
} Ov025ReportsPage;

extern Ov025ReportsPage *func_ov025_02084afc(void);                 /* Ov008_GetPageA */
extern void  func_ov025_020899dc(Ov025TouchInput *pTouch);          /* Ov008_ReadTouch */
extern int   func_ov025_0209e880(const Ov025TouchInput *pPos, const u8 *pBox); /* Ov025_PointInBox */
extern void  func_ov025_0209f668(const Ov025TouchPoint *pTouch);    /* Ov025_Reports_DragKnob */
extern u32   func_ov025_0209e820(u32 nItem, u32 bSet);              /* Ov025_QueryItemFlags */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern void  func_ov025_020a076c(void);                             /* Ov025_Reports_RefreshRows */
extern void  func_ov025_020a0a14(void);                             /* Ov025_Reports_HighlightRows */
extern void  func_ov025_020a0300(void);                             /* Ov025_Reports_DrawRowTexts */
extern u16   data_0204c18c;                                         /* held keys */
extern const u8 data_ov025_020b421c[];                              /* the scroll bar box */

void func_ov025_020a0a9c(void)
{
    Ov025ReportsPage *pPage;
    Ov025TouchInput touch;
    int nRow;
    int nY;
    int nTopic;
    int nCount;
    s16 nTop;
    int i;
    Ov025ReportsEntry *pRead;

    pPage = func_ov025_02084afc();
    pPage->bPressSound = 0;
    if (pPage->nState == 0) {
        return;
    }
    if (pPage->bReadVariants == 0) {
        func_ov025_020899dc(&touch);
        if (touch.wHeld != 0) {
            if (pPage->bPressed == 0) {
                pPage->bPressed = 1;
                if (pPage->list.bDragging == 0 && pPage->pHeldEntry == 0 && func_ov025_0209e880(&touch, data_ov025_020b421c) != 0) {
                    pPage->list.bDragging = 1;
                    func_ov025_0209f668((Ov025TouchPoint *)&touch);
                } else if (touch.wX >= 0x10 && touch.wX < 0xe0) {
                    if (touch.wY >= 0x10) {
                        nTop = pPage->nTop;
                        nCount = pPage->nCount;
                        nY = 0x20;
                        nTopic = nTop;
                        for (nRow = 0; nRow < 10; nRow++, nTopic++, nY += 0x10) {
                            if (nTopic >= nCount) {
                                break;
                            }
                            if (touch.wY < nY) {
                                pPage->nCursor = nTop + nRow;
                                if (pPage->bMissionMode == 0 || pPage->pEntries[pPage->nCursor].nPending == 0) {
                                    func_ov025_0209e820(pPage->nCursor, 1);
                                }
                                if (pPage->bPressSound == 0) {
                                    func_02033b78(0, 0);
                                    pPage->bPressSound = 1;
                                }
                                func_ov025_020a076c();
                                pPage->nField22c = 0;
                                break;
                            }
                        }
                    }
                }
            } else if (pPage->list.bDragging != 0) {
                func_ov025_0209f668((Ov025TouchPoint *)&touch);
            }
        } else {
            pPage->bPressed = 0;
            if (pPage->list.bDragging != 0) {
                pPage->list.bDragging = 0;
            }
            if (pPage->pHeldEntry != 0) {
                for (i = 0; i < 10; i++) {
                    if (pPage->aRow[i].pNumber == pPage->pHeldEntry) {
                        pPage->current = pPage->pEntries[pPage->nTop + i];
                        pPage->nField22c = 0;
                        break;
                    }
                }
                pPage->pHeldEntry = 0;
                func_ov025_020a0a14();
                func_02033b78(0, 0);
                func_ov025_020a0300();
            }
        }
    }
    if (pPage->bPressed != 0) {
        return;
    }
    if (data_0204c18c & 1) {
        if (pPage->bReadVariants != 0) {
            return;
        }
        pPage->bReadVariants = 1;
        pRead = pPage->pEntries[pPage->nCursor].pRead;
        if (pRead == 0) {
            return;
        }
        if (pPage->pEntries[pPage->nCursor].nPending != 0) {
            return;
        }
        pPage->current = *pRead;
        pPage->nField22c = 0;
        func_ov025_020a0a14();
        func_ov025_0209e820(pPage->nCursor + (pPage->bMissionMode == 0 ? 0x40 : 0), 1);
        func_02033b78(0, 0);
        func_ov025_020a076c();
    } else {
        if (pPage->bReadVariants == 0) {
            return;
        }
        pPage->bReadVariants = 0;
        if (pPage->pEntries[pPage->nCursor].pRead == 0) {
            return;
        }
        if (pPage->pEntries[pPage->nCursor].nPending != 0) {
            return;
        }
        pPage->current = pPage->pEntries[pPage->nCursor];
        pPage->nField22c = 0;
        func_ov025_020a0a14();
        func_ov025_020a0300();
        func_02033b78(0, 0);
    }
}
