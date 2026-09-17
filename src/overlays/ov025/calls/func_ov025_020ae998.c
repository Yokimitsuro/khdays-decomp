/* func_ov025_020ae998 -- Ov025_ScrollList_Release: tear the scrolling list down.  Its node
 * leaves the shared UI list (+0x2c; 02084b78), the eleven row surfaces are reset (020ae318),
 * the shared element list cleared (02084a64 / 02089644), entries 0x3e and 0x3f of the 4a80
 * block hidden (0208843c / 0208884c), the sub BG1 / BG3 scroll registers zeroed, the row
 * records (+4) freed and the string set (+0x1c) released (02089884). */
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

static volatile u32 *const REG_DB_BG1OFS = (volatile u32 *)0x04001014;
static volatile u32 *const REG_DB_BG3OFS = (volatile u32 *)0x0400101c;

extern void  func_ov025_02084b78(void *pNode);                      /* Ov008_ListRemoveAndFree */
extern void  func_ov025_020ae318(Ov025ScrollList *pList);           /* Ov025_ScrollList_ResetSurfaces */
extern int  *func_ov025_02084a64(void);                             /* Ov008_GetCtxBlock954c */
extern void  func_ov025_02089644(int *pBlock);                      /* ClearElementList */
extern int   func_ov025_02084a8c(void);                             /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void  func_ov025_02089884(void *pStrings);                   /* release a string set */

void func_ov025_020ae998(Ov025ScrollList *pList)
{
    int nCtx;

    func_ov025_02084b78(pList->pNode);
    func_ov025_020ae318(pList);
    func_ov025_02089644(func_ov025_02084a64());
    nCtx = func_ov025_02084a8c();
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x3e), 0);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x3f), 0);
    *REG_DB_BG1OFS = 0;
    *REG_DB_BG3OFS = 0;
    if (pList->pRows != 0) {
        NNSi_FndFreeFromDefaultHeap(pList->pRows);
        pList->pRows = 0;
    }
    func_ov025_02089884(pList->strings);
}
