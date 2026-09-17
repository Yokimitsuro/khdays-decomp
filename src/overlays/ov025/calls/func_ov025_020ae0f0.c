/* func_ov025_020ae0f0 -- Ov025_ScrollList_Confirm: accept the cursor row (+0x2c8 of the list).
 * A cursor other than the remembered one (game field 0x35c5, 8 bits) clears fields 0x35cd and
 * 0x35df; the cursor and the pixel scroll (+0x2d0) are stored in fields 0x35c5 / 0x35d5
 * (GameState_SetField 020235e8), the row's mission and day (16-byte records at +4) become the
 * context selection (Ov025_SetCtxFields9638And963a 02084e50), entry 1 is set up
 * (Ov025_SetGlobalConfigAndInit 02084830) and the confirm sound plays (02033b78 0 / 1). */
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

extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */
extern void  func_020235e8(int nField, int nBits, int nValue);      /* GameState_SetField */
extern void  func_ov025_02084e50(s16 nMission, s16 nDay);           /* Ov025_SetCtxFields9638And963a */
extern void  func_ov025_02084830(int nEntry);                       /* Ov025_SetGlobalConfigAndInit */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */

void func_ov025_020ae0f0(Ov025ScrollList *pList)
{
    Ov025ScrollRow *pRow;

    if (pList->nCursor < 0) {
        return;
    }
    pRow = &pList->pRows[pList->nCursor];
    if (pList->nCursor != func_020235d0(0x35c5, 8)) {
        func_020235e8(0x35cd, 8, 0);
        func_020235e8(0x35df, 8, 0);
    }
    func_020235e8(0x35c5, 8, pList->nCursor & 0xffff);
    func_020235e8(0x35d5, 10, pList->nScroll & 0xffff);
    func_ov025_02084e50(pRow->nMission, pRow->nDay);
    func_ov025_02084830(1);
    func_02033b78(0, 1);
}
