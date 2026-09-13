/* func_ov008_0205f6f8 -- Ov008_InitGridMenuSurfaces: create the grid menu's
 * text surfaces.  The templates data_ov008_0208f248 / f270 / f298 and the
 * five row templates data_ov008_0208f420 are copied to the stack; the text
 * loader (+0x28c) is pointed at data_ov008_020903f0; the two panel surfaces
 * (+0xac, +0xe8) are created and uploaded with slot 10's VRAM target and the
 * pixel buffer of context block 968c, the second with word +0x28 = 4; the
 * cursor surface (+0x124) is created (not uploaded) on slot 9 with word +0x28
 * = 2.  The character block of slot member 0x1e is copied into a fresh heap
 * buffer (+0x2f4, size at +0x2ec).  Then the five row surfaces (+0x160, 0x3c
 * each) are created on slot 9 and their text rows drawn.
 */
typedef unsigned char  u8;
typedef unsigned int   u32;

#define ROW_COUNT   5
#define SLOT_PANEL  10
#define SLOT_ROWS   9
#define HEAP_FILE   0xe
#define ARCHIVE_MEMBER_FONT 0x1e

typedef struct TileSurfaceCfg {
    int   nId;                /* 0x00 */
    int   nUnk04;             /* 0x04 */
    int   nWidthTiles;        /* 0x08 */
    int   nHeightTiles;       /* 0x0c */
    int   nCharBase;          /* 0x10 */
    int   nPaletteIndex;      /* 0x14 */
    int   nVramTarget;        /* 0x18 */
    int   nUnk1c;             /* 0x1c */
    void *pPixels;            /* 0x20 */
    int   nUnk24;             /* 0x24 */
} TileSurfaceCfg;

typedef struct Ov008RowSurfaceCfgs {
    TileSurfaceCfg aCfg[ROW_COUNT];
} Ov008RowSurfaceCfgs;

typedef struct TileSurface {
    u8  pad_00[0x28];
    int bDirty;               /* 0x28 */
    u8  pad_2c[0x3c - 0x2c];
} TileSurface;

typedef struct Ov008CharacterBlock {
    u8    pad_00[0x10];
    u32   nSize;              /* 0x10 */
    void *pData;              /* 0x14 */
} Ov008CharacterBlock;

typedef struct Ov008MenuContext {
    u8  pad_0000[0xac];
    TileSurface panelSurfaceA;   /* 0x0ac */
    TileSurface panelSurfaceB;   /* 0x0e8 */
    TileSurface cursorSurface;   /* 0x124 */
    TileSurface aRowSurface[ROW_COUNT]; /* 0x160 */
    u8  records[0x2ec - 0x28c];  /* 0x28c: variable text records / loader */
    u32 nFontSize;               /* 0x2ec */
    u8  pad_02f0[4];
    void *pFontChars;            /* 0x2f4 */
} Ov008MenuContext;

extern const TileSurfaceCfg data_ov008_0208f248;
extern const TileSurfaceCfg data_ov008_0208f270;
extern const TileSurfaceCfg data_ov008_0208f298;
extern const Ov008RowSurfaceCfgs data_ov008_0208f420;
extern const char data_ov008_020903f0[];
extern void  func_ov008_02055c4c(void *pLoader, const char *pPath);       /* Ov008_Set_5c4c */
extern int   func_ov008_02050c7c(int nSlot);                              /* Ov008_ResetEntry: slot handle */
extern void *func_ov008_02050e74(void);                                   /* Ov008_GetCtxBlock968c */
extern void  func_0202ff98(TileSurface *pSurface, const TileSurfaceCfg *pCfg); /* TileSurface_InitAndUpload8bpp */
extern void  func_0202ffb0(TileSurface *pSurface, const TileSurfaceCfg *pCfg); /* TileSurface_Init8bpp */
extern u32   func_ov008_02050f08(int nMember);                            /* Ov008_PackSlotTag */
extern void *func_0201ef9c(u32 nArchiveId, int nHeap);                    /* Archive_LoadFile */
extern void  func_02011988(void *pFile, Ov008CharacterBlock **ppBlock);   /* GetResourceSubBlock_CHAR */
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);                  /* AllocDefault */
extern void  MIi_CpuCopyFast(const void *pSrc, void *pDst, u32 nSize);
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void  func_ov008_0205f5c8(Ov008MenuContext *pCtx, void *pRecords, int nRow); /* Ov008_DrawTextRow */

void func_ov008_0205f6f8(Ov008MenuContext *pCtx)
{
    Ov008RowSurfaceCfgs rows;
    TileSurfaceCfg cfgPanelA;
    TileSurfaceCfg cfgPanelB;
    TileSurfaceCfg cfgCursor;
    Ov008CharacterBlock *pChar;
    void *pFile;
    int i;
    TileSurfaceCfg *pCfg;
    TileSurface *pSurface;

    cfgPanelA = data_ov008_0208f248;
    cfgPanelB = data_ov008_0208f270;
    cfgCursor = data_ov008_0208f298;
    rows = data_ov008_0208f420;
    func_ov008_02055c4c(pCtx->records, data_ov008_020903f0);
    cfgPanelA.nVramTarget = func_ov008_02050c7c(SLOT_PANEL);
    cfgPanelA.pPixels = func_ov008_02050e74();
    func_0202ff98(&pCtx->panelSurfaceA, &cfgPanelA);
    cfgPanelB.nVramTarget = func_ov008_02050c7c(SLOT_PANEL);
    cfgPanelB.pPixels = func_ov008_02050e74();
    func_0202ff98(&pCtx->panelSurfaceB, &cfgPanelB);
    pCtx->panelSurfaceB.bDirty = 4;
    cfgCursor.nVramTarget = func_ov008_02050c7c(SLOT_ROWS);
    cfgCursor.pPixels = func_ov008_02050e74();
    func_0202ffb0(&pCtx->cursorSurface, &cfgCursor);
    pCtx->cursorSurface.bDirty = 2;
    pFile = func_0201ef9c(func_ov008_02050f08(ARCHIVE_MEMBER_FONT), HEAP_FILE);
    func_02011988(pFile, &pChar);
    pCtx->nFontSize = pChar->nSize;
    pCtx->pFontChars = NNSi_FndAllocFromDefaultExpHeap(pChar->nSize);
    MIi_CpuCopyFast(pChar->pData, pCtx->pFontChars, pChar->nSize);
    if (pFile != 0) {
        NNSi_FndFreeFromDefaultHeap(pFile);
    }
    pCfg = rows.aCfg;
    pSurface = pCtx->aRowSurface;
    for (i = 0; i < ROW_COUNT; i++) {
        pCfg->nVramTarget = func_ov008_02050c7c(SLOT_ROWS);
        pCfg->pPixels = func_ov008_02050e74();
        func_0202ffb0(pSurface, pCfg);
        func_ov008_0205f5c8(pCtx, pCtx->records, i);
        pCfg++;
        pSurface++;
    }
}
