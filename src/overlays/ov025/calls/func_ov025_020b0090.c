/* func_ov025_020b0090 -- Ov025_ReportDetail_SetupSurface: build the text surface at +4 of the
 * report detail view of page B (Ov025_GetPageB 02084b14) from the template data_ov025_020b4978
 * with the shared tile pixel buffer (02084c84) and VRAM slot 0x19 (02084aa4), uploaded as 4bpp
 * tiles (0202ff8c).  Part of the detail screen setup 020b00f0. */
typedef unsigned char  u8;
typedef unsigned int   u32;

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

typedef struct Ov025ReportDetailPage {
    int  nField00;            /* 0x00 */
    u8   surface[0x3c];       /* 0x04: the text surface (TileSurface) */
} Ov025ReportDetailPage;

extern Ov025ReportDetailPage *func_ov025_02084b14(void);            /* Ov025_GetPageB */
extern void *func_ov025_02084c84(void);                             /* Ov025_GetCtxBlock968c */
extern int   func_ov025_02084aa4(int nSlot);                        /* Ov025_ResetEntry: slot handle */
extern void  func_0202ff8c(void *pSurface, TileSurfaceCfg *pCfg);   /* TileSurface_InitAndUpload4bpp */
extern TileSurfaceCfg data_ov025_020b4978;

void func_ov025_020b0090(void)
{
    TileSurfaceCfg cfg;
    Ov025ReportDetailPage *pPage;

    cfg = data_ov025_020b4978;
    pPage = func_ov025_02084b14();
    cfg.pPixels = func_ov025_02084c84();
    cfg.nVramTarget = func_ov025_02084aa4(0x19);
    func_0202ff8c(pPage->surface, &cfg);
}
