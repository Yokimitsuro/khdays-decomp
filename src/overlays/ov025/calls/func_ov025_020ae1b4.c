/* func_ov025_020ae1b4 -- Ov025_ScrollList_Flush: the per-frame upload of the scrolling list
 * (page B).  The sub BG2 / BG3 vertical offsets take the previous pixel scroll (+0x2d4) modulo
 * a row less 16, then the previous scroll catches up with the current one (+0x2d0).  A dirty
 * marker screen (+0x18) reloads VRAM slot 0x1b into the sub BG3 screen (02084aa4 /
 * GXS_LoadBG3Scr); dirty rows (+0x14) reload slot 0x1a into the sub BG2 screen and flush and
 * upload each of the eleven row surfaces' current tiles (+0x30, 0x3c bytes each: the block's
 * data at +0x18 / +0x20, size +0xc, character offset +0x10; GXS_LoadBG2Char).  Returns 1. */
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

static volatile u32 *const REG_DB_BG2OFS = (volatile u32 *)0x04001018;
static volatile u32 *const REG_DB_BG3OFS = (volatile u32 *)0x0400101c;

extern Ov025ScrollList *func_ov025_02084b14(void);                  /* Ov025_GetPageB */
extern int   func_ov025_02084aa4(int nSlot);                        /* Ov008_ResetEntry: slot handle */
extern void  GXS_LoadBG3Scr(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG2Scr(const void *pSrc, u32 nOffset, u32 nSize);
extern void  DC_FlushRange(const void *pAddress, u32 nSize);
extern void  GXS_LoadBG2Char(const void *pSrc, u32 nOffset, u32 nSize);

int func_ov025_020ae1b4(void)
{
    Ov025ScrollList *pList;
    int i;
    TileSurface *pSurface;
    u32  nOffset;

    pList = func_ov025_02084b14();
    nOffset = ((pList->nPrevScroll % 16 - 0x10) << 16) & 0x1ff0000;
    *REG_DB_BG2OFS = nOffset;
    *REG_DB_BG3OFS = nOffset;
    pList->nPrevScroll = pList->nScroll;
    if (pList->bMarkersDirty != 0) {
        GXS_LoadBG3Scr((void *)func_ov025_02084aa4(0x1b), 0, 0x800);
        pList->bMarkersDirty = 0;
    }
    if (pList->bRowsDirty != 0) {
        GXS_LoadBG2Scr((void *)func_ov025_02084aa4(0x1a), 0, 0x800);
        pSurface = pList->aSurface;
        for (i = 0; i < 11; i++) {
            DC_FlushRange(pSurface->current->pData, pSurface->totalBytes);
            GXS_LoadBG2Char(pSurface->current->pData, pSurface->rowBytes, pSurface->totalBytes);
            pSurface++;
        }
        pList->bRowsDirty = 0;
    }
    return 1;
}
