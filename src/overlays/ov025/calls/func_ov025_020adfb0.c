/* func_ov025_020adfb0 -- Ov025_ScrollList_SetKnob: put the scroll knob (+0x2dc of the list) at
 * nKnob within 0..+0x2e4.  The pixel scroll (+0x2d0) becomes nScroll, or, for 0x7fffffff, the
 * knob's share of the scroll range (+0x2d8 * knob / +0x2e4; the 64-bit divide 02020400).  With
 * bClampCursor the cursor (+0x2c8) is pulled into the ten rows now in view (the scroll plus
 * 8 pixels, 16 a row; Ov025_ScrollList_SelectRow 020adee0 without sound).  The list is marked
 * dirty (+0x2c4) and the knob bar redrawn (020adc7c). */
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
extern void  func_ov025_020adee0(Ov025ScrollList *pList, int nRow, int bSound); /* Ov025_ScrollList_SelectRow */
extern void  func_ov025_020adc7c(Ov025ScrollList *pList);           /* Ov025_ScrollList_DrawKnob */

void func_ov025_020adfb0(Ov025ScrollList *pList, int nKnob, int nScroll, int bClampCursor)
{
    int nCursor;
    int nTop;
    int nBottom;

    if (nKnob < 0) {
        nKnob = 0;
    }
    if (nKnob > pList->nKnobMax) {
        nKnob = pList->nKnobMax;
    }
    pList->nKnob = nKnob;
    if (nScroll != 0x7fffffff) {
        pList->nScroll = nScroll;
    }
    if (nScroll == 0x7fffffff) {
        pList->nScroll = func_02020400(pList->nScrollMax * pList->nKnob, pList->nKnobMax);
    }
    if (bClampCursor != 0) {
        nCursor = pList->nCursor;
        nTop = (pList->nScroll + 8) / 16;
        nBottom = nTop + 9;
        if (nCursor < nTop) {
            func_ov025_020adee0(pList, nTop, 0);
        }
        if (nCursor > nBottom) {
            func_ov025_020adee0(pList, nBottom, 0);
        }
    }
    pList->bDirty = 1;
    func_ov025_020adc7c(pList);
}
