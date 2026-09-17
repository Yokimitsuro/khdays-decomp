/* func_ov025_020ae28c -- Ov025_ScrollList_SetupSurfaces: build the eleven row text surfaces
 * (+0x30 of the list, 0x3c bytes each) from the template data_ov025_020b481c with the shared
 * tile pixel buffer (02084c84) and VRAM slot 0x1a (02084aa4): row i starts at tile row 0x120 +
 * 0x22 * i with id 2 * i and is uploaded as 8bpp tiles (TileSurface_InitAndUpload8bpp
 * 0202ff98). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct TileSurfaceCfg {
    u32  nUnk00;
    u32  nUnk04;
    u32  nWidthTiles;
    u32  nHeightTiles;
    u32  nRowTiles;
    u32  nPaletteIndex;
    u32  nVramTarget;
    u32  nUnk1c;
    void *pPixels;
    u32  nUnk24;
} TileSurfaceCfg;

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

extern void *func_ov025_02084c84(void);                             /* Ov008_GetCtxBlock968c */
extern int   func_ov025_02084aa4(int nSlot);                        /* Ov008_ResetEntry: slot handle */
extern void  func_0202ff98(void *pSurface, TileSurfaceCfg *pCfg);   /* TileSurface_InitAndUpload8bpp */
extern TileSurfaceCfg data_ov025_020b481c;

void func_ov025_020ae28c(Ov025ScrollList *pList)
{
    TileSurfaceCfg cfg;
    int i;
    u32  nRow;
    u32  nId;
    TileSurface *pSurface;

    cfg = data_ov025_020b481c;
    cfg.pPixels = func_ov025_02084c84();
    cfg.nVramTarget = func_ov025_02084aa4(0x1a);
    i = 0;
    pSurface = pList->aSurface;
    nId = 0;
    nRow = 0x120;
    for (; i < 11; i++) {
        cfg.nRowTiles = nRow;
        cfg.nUnk00 = nId;
        nRow += 0x22;
        func_0202ff98(pSurface, &cfg);
        nId += 2;
        pSurface++;
    }
}
