/* func_0202e620 -- set up the display capture that feeds the sub screen, MAIN. The main engine goes
 * to the upper LCD (GX_SetDispSelect), the graphics mode depends on whether a blend is wanted (EVA
 * +0xc below 16: func_020056b4 0xe/4/1, else 1/0/1), sub BG takes VRAM C and LCDC takes VRAM D, and
 * the capture is armed: with flag 1 a 256x192 A+B blend (source A +4, EVA/EVB = +0xc/16-EVA),
 * otherwise a plain capture of source A. The main screen shows the +8 layer mask and the sub screen
 * shows BG3 as a 256x256 direct-colour bitmap (base 0 with blending, else 0x08000) at priority 0,
 * mosaic off. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef volatile u16 REGType16v;
typedef volatile u32 REGType32v;

#define reg_GX_DISPCNT      (*(REGType32v *)0x04000000)
#define reg_GX_DISPCAPCNT   (*(REGType32v *)0x04000064)
#define reg_GX_POWCNT       (*(REGType16v *)0x04000304)
#define reg_GXS_DB_DISPCNT  (*(REGType32v *)0x04001000)
#define reg_G2S_DB_BG3CNT   (*(REGType16v *)0x0400100e)

#define REG_GX_DISPCNT_DISPLAY_SHIFT        8
#define REG_GX_DISPCNT_DISPLAY_MASK         0x00001f00
#define REG_GXS_DB_DISPCNT_DISPLAY_SHIFT    8
#define REG_GXS_DB_DISPCNT_DISPLAY_MASK     0x00001f00
#define REG_GX_POWCNT_DSEL_SHIFT            15
#define REG_GX_POWCNT_DSEL_MASK             0x8000
#define REG_G2S_DB_BG3CNT_PRIORITY_SHIFT    0
#define REG_G2S_DB_BG3CNT_PRIORITY_MASK     0x0003
#define REG_G2S_DB_BG3CNT_MOSAIC_MASK       0x0040
#define REG_G2S_DB_BG3CNT_SCREENBASE_SHIFT  8
#define REG_G2S_DB_BG3CNT_AREAOVER_SHIFT    13
#define REG_G2S_DB_BG3CNT_SCREENSIZE_SHIFT  14
#define REG_GX_DISPCAPCNT_E_MASK            0x80000000
#define REG_GX_DISPCAPCNT_MOD_SHIFT         29
#define REG_GX_DISPCAPCNT_SRCB_SHIFT        25
#define REG_GX_DISPCAPCNT_SRCA_SHIFT        24
#define REG_GX_DISPCAPCNT_WSIZE_SHIFT       20
#define REG_GX_DISPCAPCNT_DEST_SHIFT        16
#define REG_GX_DISPCAPCNT_EVB_SHIFT         8
#define REG_GX_DISPCAPCNT_EVA_SHIFT         0
#define GX_BG_EXTMODE_DCBITMAP              0x0084

#define GX_DISP_SELECT_MAIN_SUB     1
#define GX_PLANEMASK_BG3            0x08
#define GX_VRAM_SUB_BG_128_C        4
#define GX_VRAM_LCDC_D              8
#define GX_CAPTURE_SIZE_256x192     3
#define GX_CAPTURE_MODE_A           0
#define GX_CAPTURE_MODE_AB          2
#define GX_CAPTURE_SRCB_VRAM_0x00000 0
#define GX_CAPTURE_DEST_VRAM_D_0x00000 3
#define GX_BG_SCRSIZE_DCBMP_256x256 1
#define GX_BG_AREAOVER_XLU          0
#define GX_BG_BMPSCRBASE_0x00000    0
#define GX_BG_BMPSCRBASE_0x08000    2

static inline void GX_SetDispSelect(int sel)
{
    reg_GX_POWCNT = (u16)((reg_GX_POWCNT & ~REG_GX_POWCNT_DSEL_MASK) | (sel << REG_GX_POWCNT_DSEL_SHIFT));
}

static inline void GX_SetVisiblePlane(int plane)
{
    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT & ~REG_GX_DISPCNT_DISPLAY_MASK) | (plane << REG_GX_DISPCNT_DISPLAY_SHIFT));
}

static inline void GXS_SetVisiblePlane(int plane)
{
    reg_GXS_DB_DISPCNT = (u32)((reg_GXS_DB_DISPCNT & ~REG_GXS_DB_DISPCNT_DISPLAY_MASK) |
                               (plane << REG_GXS_DB_DISPCNT_DISPLAY_SHIFT));
}

static inline void GX_SetCapture(int sz, int mode, int a, int b, int dest, int eva, int evb)
{
    reg_GX_DISPCAPCNT = (REG_GX_DISPCAPCNT_E_MASK |
                         (mode << REG_GX_DISPCAPCNT_MOD_SHIFT) |
                         (b << REG_GX_DISPCAPCNT_SRCB_SHIFT) |
                         (a << REG_GX_DISPCAPCNT_SRCA_SHIFT) |
                         (sz << REG_GX_DISPCAPCNT_WSIZE_SHIFT) |
                         (dest << REG_GX_DISPCAPCNT_DEST_SHIFT) |
                         (evb << REG_GX_DISPCAPCNT_EVB_SHIFT) |
                         (eva << REG_GX_DISPCAPCNT_EVA_SHIFT));
}

static inline void G2S_SetBG3ControlDCBmp(int screenSize, int areaOver, int screenBase)
{
    reg_G2S_DB_BG3CNT =
        (u16)((reg_G2S_DB_BG3CNT & (REG_G2S_DB_BG3CNT_PRIORITY_MASK | REG_G2S_DB_BG3CNT_MOSAIC_MASK)) |
              (screenSize << REG_G2S_DB_BG3CNT_SCREENSIZE_SHIFT) | GX_BG_EXTMODE_DCBITMAP |
              (screenBase << REG_G2S_DB_BG3CNT_SCREENBASE_SHIFT) | (areaOver << REG_G2S_DB_BG3CNT_AREAOVER_SHIFT));
}

static inline void G2S_SetBG3Priority(int priority)
{
    reg_G2S_DB_BG3CNT = (u16)((reg_G2S_DB_BG3CNT & ~REG_G2S_DB_BG3CNT_PRIORITY_MASK) |
                              (priority << REG_G2S_DB_BG3CNT_PRIORITY_SHIFT));
}

static inline void G2S_BG3Mosaic(BOOL enable)
{
    if (enable) {
        reg_G2S_DB_BG3CNT |= REG_G2S_DB_BG3CNT_MOSAIC_MASK;
    } else {
        reg_G2S_DB_BG3CNT &= ~REG_G2S_DB_BG3CNT_MOSAIC_MASK;
    }
}

typedef struct {
    u32 flags;          /* 0x00: bit 0 = blend the capture */
    u32 srcA;           /* 0x04 */
    u32 layers;         /* 0x08 */
    u32 eva;            /* 0x0c */
} CaptureCfg;

extern void func_020056b4(int a, int b, int c);
extern void SNDi_UnlockMutex_0x020063f8(void);
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForLCDC(int bank);

void func_0202e620(CaptureCfg *cfg)
{
    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
    if (cfg->eva != 0x10) {
        func_020056b4(0xe, 4, 1);
    } else {
        func_020056b4(1, 0, 1);
    }
    SNDi_UnlockMutex_0x020063f8();
    GX_SetBankForSubBG(GX_VRAM_SUB_BG_128_C);
    GX_SetBankForLCDC(GX_VRAM_LCDC_D);
    if (cfg->flags & 1) {
        /* GX_SetCapture(256x192, AB, srcA, VRAM, VRAM_D, eva, 16 - eva), built in two steps like
         * Gfx_SetupBlendCapture: the single expression schedules the EVB term differently */
        u32 dispcapcnt = (REG_GX_DISPCAPCNT_E_MASK |
                          (GX_CAPTURE_MODE_AB << REG_GX_DISPCAPCNT_MOD_SHIFT) |
                          (GX_CAPTURE_SRCB_VRAM_0x00000 << REG_GX_DISPCAPCNT_SRCB_SHIFT) |
                          (GX_CAPTURE_SIZE_256x192 << REG_GX_DISPCAPCNT_WSIZE_SHIFT) |
                          (GX_CAPTURE_DEST_VRAM_D_0x00000 << REG_GX_DISPCAPCNT_DEST_SHIFT)) |
                         (cfg->srcA << REG_GX_DISPCAPCNT_SRCA_SHIFT);
        dispcapcnt = (cfg->eva << REG_GX_DISPCAPCNT_EVA_SHIFT) |
                     (dispcapcnt | ((0x10 - cfg->eva) << REG_GX_DISPCAPCNT_EVB_SHIFT));
        reg_GX_DISPCAPCNT = dispcapcnt;
    } else {
        GX_SetCapture(GX_CAPTURE_SIZE_256x192, GX_CAPTURE_MODE_A, cfg->srcA, GX_CAPTURE_SRCB_VRAM_0x00000,
                      GX_CAPTURE_DEST_VRAM_D_0x00000, 0x10, 0);
    }
    GX_SetVisiblePlane(cfg->layers);
    GXS_SetVisiblePlane(GX_PLANEMASK_BG3);
    if (cfg->flags & 1) {
        G2S_SetBG3ControlDCBmp(GX_BG_SCRSIZE_DCBMP_256x256, GX_BG_AREAOVER_XLU, GX_BG_BMPSCRBASE_0x00000);
    } else {
        G2S_SetBG3ControlDCBmp(GX_BG_SCRSIZE_DCBMP_256x256, GX_BG_AREAOVER_XLU, GX_BG_BMPSCRBASE_0x08000);
    }
    G2S_SetBG3Priority(0);
    G2S_BG3Mosaic(0);
}
