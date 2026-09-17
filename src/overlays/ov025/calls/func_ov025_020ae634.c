/* func_ov025_020ae634 -- Ov025_ScrollList_TouchKnob: follow the stylus on the scroll bar.  The
 * touch state of the 4a80 block (02084a8c; 02088b1c) is read: unless its phase is 1 the touch
 * flag (+0xc of the list) clears and the cursor row (+0x2c8) is re-selected (020adee0); while
 * the stylus is still down (word +6 zero) the knob (+0x2dc) follows the touch row less half the
 * knob height (+0x2e0) and 16, within 0..+0x2e4, keeping the pixel scroll (0x7fffffff) and
 * clamping the cursor into view (Ov025_ScrollList_SetKnob 020adfb0). */
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

typedef struct Ov025TouchState {
    u16  nX;                  /* 0x00 */
    u16  nY;                  /* 0x02 */
    u16  nTouching;           /* 0x04 */
    u16  nPhase;              /* 0x06 */
} Ov025TouchState;

extern int   func_ov025_02084a8c(void);                             /* Ov008_GetCtxBlock4a80 */
extern void  func_ov025_02088b1c(int nBlock, Ov025TouchState *pOut); /* copy the touch state */
extern void  func_ov025_020adee0(Ov025ScrollList *pList, int nRow, int nMode); /* Ov025_ScrollList_SelectRow */
extern void  func_ov025_020adfb0(Ov025ScrollList *pList, int nKnob, int nScroll, int bClampCursor); /* Ov025_ScrollList_SetKnob */

void func_ov025_020ae634(Ov025ScrollList *pList)
{
    Ov025TouchState touch;
    int nKnob;

    func_ov025_02088b1c(func_ov025_02084a8c(), &touch);
    if (touch.nTouching == 1) {
        if (touch.nPhase == 0) {
            nKnob = touch.nY - pList->nKnobHeight / 2 - 0x10;
            if (nKnob < 0) {
                nKnob = 0;
            }
            if (nKnob > pList->nKnobMax) {
                nKnob = pList->nKnobMax;
            }
            func_ov025_020adfb0(pList, nKnob, 0x7fffffff, 1);
        }
    } else {
        pList->bTouching = 0;
        func_ov025_020adee0(pList, pList->nCursor, 0);
    }
}
