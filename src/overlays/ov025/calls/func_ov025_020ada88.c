/* func_ov025_020ada88 -- Ov025_ScrollList_DrawRow: draw day row nRow of the scrolling list on
 * row surface nSurface (+0x30, eleven of 0x3c).  The row's first day is shown with the digit
 * cells of the shared tag tracker (02084a64): tags 0x514 + digit in columns 5 / 6 / 7 at y
 * (nSurface % 11) * 2 (Ov025_DayList_PlaceDigit 020ada10), leading zeros placed blank
 * (Ov025_DayList_PlaceBlank 020ada44); the dash cell 0x51e (column 8) shows for a span of more
 * than one day, always for day 355 and never for day 358.  The surface is cleared (02030158),
 * the row name drawn at (0, 3) in colour 0xf1 with a shadow (Text_DrawWithShadow 02030278) and
 * VRAM slot 0x1a marked (Ov025_MarkSlotUsed 02084964). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025ScrollRow {
    int  nFirstDay;           /* 0x00: the day span of the row */
    int  nLastDay;            /* 0x04 */
    const u16 *pName;         /* 0x08 */
    int  nField0c;            /* 0x0c */
} Ov025ScrollRow;             /* 0x10 */

typedef struct Ov025ScrollList {
    int  nField000;           /* 0x000 */
    Ov025ScrollRow *pRows;    /* 0x004: the day rows */
    int  nCount;              /* 0x008 */
    int  bTouching;           /* 0x00c: the stylus holds the scroll bar */
    int  bPressed;            /* 0x010 */
    int  bRowsDirty;          /* 0x014: re-upload the row surfaces */
    int  bMarkersDirty;       /* 0x018: re-upload the marker screen */
    u8   strings[0x10];       /* 0x01c: the row name strings */
    void *pNode;              /* 0x02c: the shared UI list node */
    u8   aSurface[11][0x3c];  /* 0x030: one text surface per row (TileSurface) */
} Ov025ScrollList;

extern int   func_ov025_02084a64(void);                             /* Ov025_GetCtxBlock954c: the tag tracker */
extern void  func_ov025_020ada10(int nTracker, int nTag, s16 nColumn, s16 nY); /* Ov025_DayList_PlaceDigit */
extern void  func_ov025_020ada44(int nTracker, int nTag, s16 nColumn, s16 nY); /* Ov025_DayList_PlaceBlank */
extern void  func_02030158(void *pSurface);                         /* TileSurface_Clear */
extern void  func_02030278(void *pSurface, int nX, int nY, int nColour, const u16 *pText, int nShadow); /* Text_DrawWithShadow */
extern void  func_ov025_02084964(int nSlot);                        /* Ov025_MarkSlotUsed */

void func_ov025_020ada88(Ov025ScrollList *pList, int nSurface, int nRow)
{
    int nTracker;
    int nHundreds;
    int nValue;
    int nY;
    Ov025ScrollRow *pRow;
    Ov025ScrollRow *pRows;
    int nTens;
    int bDash;

    if (nRow >= pList->nCount) {
        return;
    }
    pRows = pList->pRows;
    pRow = &pRows[nRow];
    nTracker = func_ov025_02084a64();
    nY = (nSurface % 11) * 2;
    nValue = pRows[nRow].nFirstDay;
    nHundreds = nValue / 100;
    nValue = nValue % 100;
    if (nHundreds != 0) {
        func_ov025_020ada10(nTracker, 0x514 + nHundreds, 5, nY);
    } else {
        func_ov025_020ada44(nTracker, 0x514 + nHundreds, 5, nY);
    }
    nTens = nValue / 10;
    nValue = nValue % 10;
    if (nHundreds != 0 || nTens != 0) {
        func_ov025_020ada10(nTracker, 0x514 + nTens, 6, nY);
    } else {
        func_ov025_020ada44(nTracker, 0x514 + nTens, 6, nY);
    }
    func_ov025_020ada10(nTracker, 0x514 + nValue, 7, nY);
    bDash = 0;
    if (pRow->nFirstDay != pRow->nLastDay) {
        bDash = 1;
    }
    if (pRow->nFirstDay == 355) {
        bDash = 1;
    }
    if (pRow->nFirstDay == 358) {
        bDash = 0;
    }
    if (bDash) {
        func_ov025_020ada10(nTracker, 0x51e, 8, nY);
    } else {
        func_ov025_020ada44(nTracker, 0x51e, 8, nY);
    }
    func_02030158(pList->aSurface[nSurface]);
    func_02030278(pList->aSurface[nSurface], 0, 3, 0xf1, pRow->pName, 1);
    func_ov025_02084964(0x1a);
}
