/* func_ov025_0209eea8 -- Ov025_Reports_SetupSurface: prepare the report page's text.  The
 * string file "UI/cm/str/%s_&.s.z" (data_ov025_020b523c) is named after the page's mode word
 * (+0x258; data_ov025_020b4220: "rpt" for the story reports, "enm" for the enemy profiles) and
 * loaded into the text at +0x6c (0208985c); the 32 x 24 text surface at +0x78 is built from the
 * template data_ov025_020b4250 with the shared tile pixel buffer (02084c84) and VRAM slot 9
 * (02084aa4) and uploaded as 4bpp tiles (0202ff8c). */
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

typedef struct Ov025ReportsPage {
    u8   pad_000[0x6c];
    u8   text[0xc];           /* 0x06c: the report / enemy strings */
    u8   surface[0x3c];       /* 0x078 */
    u8   pad_0b4[0xc8 - 0xb4];
    int  nState;              /* 0x0c8 */
    u8   pad_0cc[0x248 - 0xcc];
    u16  aSeen[8];            /* 0x248: the seen bits per group */
    int  bMissionMode;        /* 0x258: enemy profiles rather than reports */
    u8   pad_25c[0x278 - 0x25c];
} Ov025ReportsPage;           /* 0x278: a view of page A (Ov008_GetPageA) */

extern Ov025ReportsPage *func_ov025_02084afc(void);                 /* Ov008_GetPageA */
extern void  OS_SNPrintf(char *pBuffer, int nSize, const char *pFormat, ...);
extern void  func_ov025_0208985c(void *pText, const char *pszPath); /* Ov008_Set_5c4c */
extern void *func_ov025_02084c84(void);                             /* Ov008_GetCtxBlock968c */
extern int   func_ov025_02084aa4(int nSlot);                        /* Ov008_ResetEntry: slot handle */
extern void  func_0202ff8c(void *pSurface, TileSurfaceCfg *pCfg);   /* TileSurface_InitAndUpload4bpp */
extern TileSurfaceCfg data_ov025_020b4250;
extern const char *data_ov025_020b4220[];                           /* "rpt", "enm" */
extern char  data_ov025_020b523c[];                                 /* "UI/cm/str/%s_&.s.z" */

void func_ov025_0209eea8(void)
{
    char szPath[0x20];
    TileSurfaceCfg cfg;
    Ov025ReportsPage *pPage;

    cfg = data_ov025_020b4250;
    pPage = func_ov025_02084afc();
    OS_SNPrintf(szPath, 0x20, data_ov025_020b523c, data_ov025_020b4220[pPage->bMissionMode]);
    func_ov025_0208985c(pPage->text, szPath);
    cfg.pPixels = func_ov025_02084c84();
    cfg.nVramTarget = func_ov025_02084aa4(9);
    func_0202ff8c(pPage->surface, &cfg);
}
