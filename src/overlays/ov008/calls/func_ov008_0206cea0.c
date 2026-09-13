/* func_ov008_0206cea0 -- Ov008_InitStatusPanelSurfaces: create the six tile
 * surfaces of the status panel (+0x64, 0x3c each) from the templates
 * data_ov008_0208f6b0 / f6d8 / f700 / f728 / f750 / f688 copied to the stack.
 * The first five share the VRAM target of slot 0x18 and the pixel buffer of
 * context block 968c; the sixth (f688) uses slot 0x1a with the same buffer.
 * The first surface's word at +0x28 is set to 5, slot 0x18 is marked used and
 * the panel's text loader (+0x58) is pointed at "UI/cm/str/status_&.s.z".
 *
 * NOTE: compiled with #pragma opt_common_subs off (push/pop scoped): with CSE on
 * mwcc schedules the third upload's arguments the other way round (add r0 before
 * add r1); no source form changed that, the pragma reproduces the ROM.
 */
typedef unsigned char  u8;
typedef unsigned int   u32;

#define SURFACE_COUNT 6
#define VRAM_SLOT_MAIN 0x18
#define VRAM_SLOT_LAST 0x1a

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
    u8  pad_00[0x28];
    int bDirty;               /* 0x28 */
    u8  pad_2c[0x3c - 0x2c];
} TileSurface;

typedef struct Ov008StatusPanel {
    u8  pad_00[0x58];
    u8  textLoader[0xc];      /* 0x58 */
    TileSurface aSurface[SURFACE_COUNT]; /* 0x64 */
} Ov008StatusPanel;

extern const TileSurfaceCfg data_ov008_0208f6b0;
extern const TileSurfaceCfg data_ov008_0208f6d8;
extern const TileSurfaceCfg data_ov008_0208f700;
extern const TileSurfaceCfg data_ov008_0208f728;
extern const TileSurfaceCfg data_ov008_0208f750;
extern const TileSurfaceCfg data_ov008_0208f688;
extern const char data_ov008_020907f0[];                                  /* "UI/cm/str/status_&.s.z" */
extern int   func_ov008_02050c7c(int nSlot);                              /* Ov008_ResetEntry: slot handle */
extern void *func_ov008_02050e74(void);                                   /* Ov008_GetCtxBlock968c */
extern void  func_0202ff98(TileSurface *pSurface, const TileSurfaceCfg *pCfg); /* TileSurface_InitAndUpload8bpp */
extern void  func_ov008_02050b3c(int nSlot);                              /* Ov008_MarkSlotUsed */
extern void  func_ov008_02055c4c(void *pLoader, const char *pPath);       /* Ov008_Set_5c4c */

#pragma opt_common_subs off
#pragma push
#pragma opt_common_subs off
void func_ov008_0206cea0(Ov008StatusPanel *pPanel)
{
    TileSurfaceCfg cfg0;
    TileSurfaceCfg cfg1;
    TileSurfaceCfg cfg2;
    TileSurfaceCfg cfg3;
    TileSurfaceCfg cfg4;
    TileSurfaceCfg cfg5;

    cfg0 = data_ov008_0208f6b0;
    cfg1 = data_ov008_0208f6d8;
    cfg2 = data_ov008_0208f700;
    cfg3 = data_ov008_0208f728;
    cfg4 = data_ov008_0208f750;
    cfg5 = data_ov008_0208f688;
    cfg4.nVramTarget = func_ov008_02050c7c(VRAM_SLOT_MAIN);
    cfg3.nVramTarget = cfg4.nVramTarget;
    cfg2.nVramTarget = cfg4.nVramTarget;
    cfg1.nVramTarget = cfg4.nVramTarget;
    cfg0.nVramTarget = cfg4.nVramTarget;
    cfg4.pPixels = func_ov008_02050e74();
    cfg3.pPixels = cfg4.pPixels;
    cfg2.pPixels = cfg4.pPixels;
    cfg1.pPixels = cfg4.pPixels;
    cfg0.pPixels = cfg4.pPixels;
    cfg5.nVramTarget = func_ov008_02050c7c(VRAM_SLOT_LAST);
    cfg5.pPixels = func_ov008_02050e74();
    func_0202ff98(&pPanel->aSurface[0], &cfg0);
    func_0202ff98(&pPanel->aSurface[1], &cfg1);
    func_0202ff98(&pPanel->aSurface[2], &cfg2);
    func_0202ff98(&pPanel->aSurface[3], &cfg3);
    func_0202ff98(&pPanel->aSurface[4], &cfg4);
    func_0202ff98(&pPanel->aSurface[5], &cfg5);
    pPanel->aSurface[0].bDirty = 5;
    func_ov008_02050b3c(VRAM_SLOT_MAIN);
    func_ov008_02055c4c(pPanel->textLoader, data_ov008_020907f0);
}
#pragma pop
