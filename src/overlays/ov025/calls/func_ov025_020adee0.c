/* func_ov025_020adee0 -- Ov025_ScrollList_SelectRow: make row nRow (0..+8 of the list) the
 * cursor (+0x2c8).  When the list scrolls (+0x2d8 > 0) the view follows: a row above the
 * scrolled rows (+0x2d0 pixels, 16 a row) or below the ninth visible row moves the pixel scroll
 * to that row and the knob (+0x2dc) proportionally over its range (+0x2e4 / +0x2d8; the 64-bit
 * divide 02020400; Ov025_ScrollList_SetKnob 020adfb0).  With bSound the cursor sound plays
 * (02033b78 0 / 0); the markers are re-placed (020ade68) and the list and its marker screen
 * marked dirty (+0x2c4, +0x18). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct TileBlock {
    u8   pad_00[0x20];
    void *pData;              /* 0x20 */
} TileBlock;

typedef struct TileSurface {
    void *pixels;             /* 0x00 */
    int  width;               /* 0x04 */
    int  height;              /* 0x08 */
    int  totalBytes;          /* 0x0c */
    int  rowBytes;            /* 0x10 */
    int  unknown14;           /* 0x14 */
    TileBlock *current;       /* 0x18 */
    void *currentData;        /* 0x1c */
    u8   pad_20[0x3c - 0x20];
} TileSurface;                /* 0x3c */

typedef struct Ov025ScrollRow {
    int  nMission;            /* 0x00 */
    int  nDay;                /* 0x04 */
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
    TileSurface aSurface[11]; /* 0x030: one text surface per row */
    int  bDirty;              /* 0x2c4 */
    int  nCursor;             /* 0x2c8 */
    int  nField2cc;           /* 0x2cc */
    int  nScroll;             /* 0x2d0: in pixels, 16 per row */
    int  nPrevScroll;         /* 0x2d4 */
    int  nScrollMax;          /* 0x2d8 */
    int  nKnob;               /* 0x2dc */
    int  nKnobHeight;         /* 0x2e0 */
    int  nKnobMax;            /* 0x2e4 */
} Ov025ScrollList;            /* 0x2e8: the day list view of page B (Ov025_GetPageB) */

extern int   func_02020400(int nNum, int nDen);                     /* _s32_div_f */
extern void  func_ov025_020adfb0(Ov025ScrollList *pList, int nKnob, int nScroll, int bClampCursor); /* Ov025_ScrollList_SetKnob */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern void  func_ov025_020ade68(Ov025ScrollList *pList);           /* Ov025_ScrollList_PlaceMarkers */

void func_ov025_020adee0(Ov025ScrollList *pList, int nRow, int bSound)
{
    int nTop;
    int nBottom;
    int nScroll;

    if (nRow < 0) {
        return;
    }
    if (nRow >= pList->nCount) {
        return;
    }
    pList->nCursor = nRow;
    if (pList->nScrollMax > 0) {
        nTop = pList->nScroll / 16;
        nBottom = nTop + 9;
        if (nRow <= nTop) {
            nScroll = nRow * 16;
            func_ov025_020adfb0(pList, func_02020400(pList->nKnobMax * nScroll, pList->nScrollMax), nScroll, 0);
        }
        if (nRow >= nBottom) {
            nScroll = (nRow - 9) * 16;
            func_ov025_020adfb0(pList, func_02020400(pList->nKnobMax * nScroll, pList->nScrollMax), nScroll, 0);
        }
    }
    if (bSound != 0) {
        func_02033b78(0, 0);
    }
    func_ov025_020ade68(pList);
    pList->bDirty = 1;
    pList->bMarkersDirty = 1;
}
