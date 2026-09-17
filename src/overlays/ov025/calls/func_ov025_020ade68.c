/* func_ov025_020ade68 -- Ov025_ScrollList_PlaceMarkers: put the eleven row markers (cell 0xc of
 * the shared tag tracker, Ov008_GetCtxBlock954c 02084a64) at column 2, rows 0, 2, .. 20
 * (020ada10) and the cursor marker (cell 0xd) at column 2 on the cursor's row: the cursor
 * (+0x2c8 of the list) less the scrolled rows (+0x2d0 pixels, 16 a row), doubled. */
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

extern int   func_ov025_02084a64(void);                             /* Ov008_GetCtxBlock954c */
extern void  func_ov025_020ada10(int nTracker, int nTag, s16 nX, s16 nY); /* Ov008_TagTracker_MoveCell */

void func_ov025_020ade68(Ov025ScrollList *pList)
{
    int nTracker;
    int i;
    int nY;

    nTracker = func_ov025_02084a64();
    i = 0;
    nY = 0;
    for (; i < 11; i++) {
        func_ov025_020ada10(nTracker, 0xc, 2, (s16)nY);
        nY += 2;
    }
    func_ov025_020ada10(nTracker, 0xd, 2, (pList->nCursor - pList->nScroll / 16) * 2);
}
