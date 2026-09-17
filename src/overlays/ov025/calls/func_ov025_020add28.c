/* func_ov025_020add28 -- Ov025_ScrollList_PlaceKnobBar: place the scroll bar entries of the
 * 4a80 block (02084a8c).  Entries 4..0x13 (the bar segments) keep entry 2's x
 * (Ov008_GetEntryPos 02088544) and go 8 pixels apart from 16 below the knob top (+0x2dc of
 * the list, plus 16); entry 2 (the knob's top cap) sits at the knob top and entry 3 (its bottom
 * cap) at the top plus the knob height (+0x2e0) less 16 (Ov008_SetEntryPos 02088500). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct UiLayoutPos {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} UiLayoutPos;

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

extern int   func_ov025_02084a8c(void);                             /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern UiLayoutPos *func_ov025_02088544(int nCtx, void *pEntry);    /* Ov008_GetEntryPos */
extern void  func_ov025_02088500(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */

void func_ov025_020add28(Ov025ScrollList *pList)
{
    int nCtx = func_ov025_02084a8c();
    UiLayoutPos pos = {0, 0};
    int nTop;
    int i;
    int nY;

    pos.x = func_ov025_02088544(nCtx, func_ov025_0208843c(nCtx, 2))->x;
    nTop = pList->nKnob + 0x10;
    for (i = 4; i <= 0x13; i++) {
        nY = (i - 4) * 8 + 0x10;
        pos.y = (nY + nTop) << 12;
        func_ov025_02088500(nCtx, func_ov025_0208843c(nCtx, i), &pos);
    }
    pos.y = nTop << 12;
    func_ov025_02088500(nCtx, func_ov025_0208843c(nCtx, 2), &pos);
    pos.y = (nTop + pList->nKnobHeight - 0x10) << 12;
    func_ov025_02088500(nCtx, func_ov025_0208843c(nCtx, 3), &pos);
}
