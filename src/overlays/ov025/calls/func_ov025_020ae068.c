/* func_ov025_020ae068 -- Ov025_ScrollList_PageStep: move the cursor (+0x2c8 of the list) ten
 * rows down (nDir > 0, capped at the last of +8 rows) or up (floored at 0).  When it moves, the
 * pixel scroll (+0x2d0) follows by 16 a row within 0..+0x2d8, the knob (+0x2dc) is placed
 * proportionally over its range (+0x2e4; the 64-bit divide 02020400; 020adfb0 without cursor
 * clamping) and the cursor sound plays (02033b78 0 / 0). */
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

void func_ov025_020ae068(Ov025ScrollList *pList, int nDir)
{
    int nNew;
    int nOld;
    int nScroll;

    nOld = pList->nCursor;
    if (nDir > 0) {
        nNew = nOld + 10;
        if (nNew >= pList->nCount) {
            nNew = pList->nCount - 1;
        }
    } else {
        nNew = nOld - 10;
        if (nNew < 0) {
            nNew = 0;
        }
    }
    if (nNew != nOld) {
        nScroll = pList->nScroll + (nNew - nOld) * 16;
        pList->nCursor = nNew;
        if (nScroll < 0) {
            nScroll = 0;
        }
        if (nScroll > pList->nScrollMax) {
            nScroll = pList->nScrollMax;
        }
        func_ov025_020adfb0(pList, func_02020400(pList->nKnobMax * nScroll, pList->nScrollMax), nScroll, 0);
        func_02033b78(0, 0);
    }
}
