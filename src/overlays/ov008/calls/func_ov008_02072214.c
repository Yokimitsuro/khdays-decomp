/* func_ov008_02072214 -- Ov008_InitMissionListRowSurfaces: create the three
 * tile surfaces of each of the six mission list rows (name +0x84, info
 * +0x1ec, extra +0x354; 0x3c each) from the four configuration templates
 * data_ov008_0208f988 / f910 / f938 / f960 copied to the stack.  The info
 * template is 0xf tiles wide while the entry gate (+0x40) is set, or 0x12
 * tiles when context objects 9630 and 9634 both exist.  Pixel buffers come
 * from context blocks 968c (name) and e5c (the rest), the VRAM target from
 * slot 0x1a.  Character bases are handed out sequentially from 0x120: row
 * name (id 2 + 4 * row), then 0x28 later the info surface (id 4 * row,
 * width x height tiles), then the extra surface: template f938 (+4) while
 * the gate is clear, template f960 (+10) while it is set.
 */
typedef unsigned char  u8;
typedef unsigned int   u32;

#define ROW_COUNT       6
#define CHAR_BASE_FIRST 0x120
#define NAME_TILES      0x28
#define EXTRA_TILES_A   4
#define EXTRA_TILES_B   10
#define INFO_WIDTH_GATED 0xf
#define INFO_WIDTH_WIDE  0x12
#define VRAM_SLOT       0x1a

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

typedef struct Ov008MissionList {
    u8  pad_000[0x40];
    int bEntryGate;           /* 0x040 */
    u8  pad_044[0x84 - 0x44];
    TileSurface aRowNameSurface[ROW_COUNT];   /* 0x084 */
    TileSurface aRowInfoSurface[ROW_COUNT];   /* 0x1ec */
    TileSurface aRowExtraSurface[ROW_COUNT];  /* 0x354 */
} Ov008MissionList;

extern const TileSurfaceCfg data_ov008_0208f988;
extern const TileSurfaceCfg data_ov008_0208f910;
extern const TileSurfaceCfg data_ov008_0208f938;
extern const TileSurfaceCfg data_ov008_0208f960;
extern int   func_ov008_02050ff8(void);                                   /* Ov008_GetCtxObject9630 */
extern int   func_ov008_02051028(void);                                   /* Ov008_GetCtxObject9634 */
extern void *func_ov008_02050e74(void);                                   /* Ov008_GetCtxBlock968c */
extern void *func_ov008_02050e5c(void);                                   /* pixel buffer */
extern int   func_ov008_02050c7c(int nSlot);                              /* Ov008_ResetEntry: slot handle */
extern void  func_0202ff98(TileSurface *pSurface, const TileSurfaceCfg *pCfg); /* TileSurface_InitAndUpload8bpp */

void func_ov008_02072214(Ov008MissionList *pList)
{
    TileSurfaceCfg cfgName;
    TileSurfaceCfg cfgInfo;
    TileSurfaceCfg cfgExtraA;
    TileSurfaceCfg cfgExtraB;
    int i;
    int nCharBase;
    int nVram;

    cfgName = data_ov008_0208f988;
    cfgInfo = data_ov008_0208f910;
    cfgExtraA = data_ov008_0208f938;
    cfgExtraB = data_ov008_0208f960;
    if (pList->bEntryGate == 0) {
        if (func_ov008_02050ff8() != 0 && func_ov008_02051028() != 0) {
            cfgInfo.nWidthTiles = INFO_WIDTH_WIDE;
        }
    } else {
        cfgInfo.nWidthTiles = INFO_WIDTH_GATED;
    }
    cfgName.pPixels = func_ov008_02050e74();
    cfgInfo.pPixels = func_ov008_02050e5c();
    cfgExtraA.pPixels = func_ov008_02050e5c();
    cfgExtraB.pPixels = func_ov008_02050e5c();
    nVram = func_ov008_02050c7c(VRAM_SLOT);
    cfgInfo.nVramTarget = nVram;
    cfgName.nVramTarget = nVram;
    cfgExtraA.nVramTarget = nVram;
    cfgExtraB.nVramTarget = nVram;
    nCharBase = CHAR_BASE_FIRST;
    for (i = 0; i < ROW_COUNT; i++) {
        cfgName.nCharBase = nCharBase;
        cfgName.nId = 2 + 4 * i;
        nCharBase += NAME_TILES;
        func_0202ff98(&pList->aRowNameSurface[i], &cfgName);
        cfgInfo.nCharBase = nCharBase;
        nCharBase += cfgInfo.nWidthTiles * cfgInfo.nHeightTiles;
        cfgInfo.nId = 4 * i;
        func_0202ff98(&pList->aRowInfoSurface[i], &cfgInfo);
        if (pList->bEntryGate == 0) {
            cfgExtraA.nCharBase = nCharBase;
            cfgExtraA.nId = 4 * i;
            nCharBase += EXTRA_TILES_A;
            func_0202ff98(&pList->aRowExtraSurface[i], &cfgExtraA);
        } else {
            cfgExtraB.nCharBase = nCharBase;
            cfgExtraB.nId = 4 * i;
            nCharBase += EXTRA_TILES_B;
            func_0202ff98(&pList->aRowExtraSurface[i], &cfgExtraB);
        }
    }
}
