/* func_ov025_020ac994 -- Ov008_InitMissionMenuSurfaces: create the mission
 * menu's five tile surfaces (+0xc, 0x3c each).  The first (template
 * data_ov025_020b474c) is created on slot 0x1a with block 968c's pixels and
 * its base cell (+0x138) and two fresh cells (+0x13c, +0x140) recorded.  The
 * other four share slot 0x18: the second (faec, 968c pixels) at character
 * base 0x160, the third (fb14, e5c pixels) at 0x188, the fourth at 0x1ac
 * from template fa4c (e5c pixels, no transfer) or fa74 (transfer, +0x150),
 * and the fifth (fac4, 968c pixels) at 0x1b0 or 0x1b6 accordingly.
 */
typedef unsigned char  u8;
typedef unsigned int   u32;

#define SURFACE_COUNT 5
#define SLOT_FIRST    0x1a
#define SLOT_ROWS     0x18
#define CHAR_BASE_ROWS 0x160

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

typedef struct TileSurface {
    u8 pad[0x3c];
} TileSurface;

typedef struct Ov008MissionMenu {
    u8  pad_000[0xc];
    TileSurface aSurface[SURFACE_COUNT]; /* 0x00c */
    void *pBaseCell;          /* 0x138 */
    void *pCellA;             /* 0x13c */
    void *pCellB;             /* 0x140 */
    u8  pad_144[0x150 - 0x144];
    int bTransfer;            /* 0x150 */
} Ov008MissionMenu;

extern const TileSurfaceCfg data_ov025_020b474c;
extern const TileSurfaceCfg data_ov025_020b479c;
extern const TileSurfaceCfg data_ov025_020b47c4;
extern const TileSurfaceCfg data_ov025_020b46fc;
extern const TileSurfaceCfg data_ov025_020b4724;
extern const TileSurfaceCfg data_ov025_020b4774;
extern void *func_ov025_02084c84(void);                                   /* Ov008_GetCtxBlock968c */
extern void *func_ov025_02084c6c(void);                                   /* pixel buffer */
extern int   func_ov025_02084aa4(int nSlot);                              /* Ov008_ResetEntry: slot handle */
extern void  func_0202ff98(TileSurface *pSurface, const TileSurfaceCfg *pCfg); /* TileSurface_InitAndUpload8bpp */
extern void *func_020303b4(TileSurface *pSurface);                        /* base cell */
extern void *func_0202fff8(TileSurface *pSurface, int nArg);              /* new cell */

void func_ov025_020ac994(Ov008MissionMenu *pMenu)
{
    TileSurfaceCfg cfgFirst;
    TileSurfaceCfg cfgA;
    TileSurfaceCfg cfgB;
    TileSurfaceCfg cfgC;
    TileSurfaceCfg cfgD;
    TileSurfaceCfg cfgE;
    int nCharBase;
    int nVram;

    cfgFirst = data_ov025_020b474c;
    cfgFirst.pPixels = func_ov025_02084c84();
    cfgFirst.nVramTarget = func_ov025_02084aa4(SLOT_FIRST);
    func_0202ff98(&pMenu->aSurface[0], &cfgFirst);
    pMenu->pBaseCell = func_020303b4(&pMenu->aSurface[0]);
    pMenu->pCellA = func_0202fff8(&pMenu->aSurface[0], 0);
    pMenu->pCellB = func_0202fff8(&pMenu->aSurface[0], 0);
    cfgA = data_ov025_020b479c;
    cfgB = data_ov025_020b47c4;
    cfgC = data_ov025_020b46fc;
    cfgD = data_ov025_020b4724;
    cfgE = data_ov025_020b4774;
    cfgA.pPixels = func_ov025_02084c84();
    cfgB.pPixels = func_ov025_02084c6c();
    cfgC.pPixels = func_ov025_02084c6c();
    cfgD.pPixels = func_ov025_02084c6c();
    cfgE.pPixels = func_ov025_02084c84();
    nVram = func_ov025_02084aa4(SLOT_ROWS);
    nCharBase = CHAR_BASE_ROWS;
    cfgA.nCharBase = nCharBase;
    cfgA.nVramTarget = nVram;
    cfgB.nVramTarget = nVram;
    cfgC.nVramTarget = nVram;
    cfgD.nVramTarget = nVram;
    cfgE.nVramTarget = nVram;
    func_0202ff98(&pMenu->aSurface[1], &cfgA);
    cfgB.nCharBase = 0x188;
    func_0202ff98(&pMenu->aSurface[3], &cfgB);
    if (pMenu->bTransfer == 0) {
        cfgC.nCharBase = 0x1ac;
        nCharBase += 0x50;
        func_0202ff98(&pMenu->aSurface[2], &cfgC);
    } else {
        cfgD.nCharBase = 0x1ac;
        nCharBase += 0x56;
        func_0202ff98(&pMenu->aSurface[2], &cfgD);
    }
    cfgE.nCharBase = nCharBase;
    func_0202ff98(&pMenu->aSurface[4], &cfgE);
}
