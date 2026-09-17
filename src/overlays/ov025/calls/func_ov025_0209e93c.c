/* func_ov025_0209e93c -- Ov025_Reports_SetupDisplay: configure the video hardware for the
 * reports / enemy profiles page.  The 3D pipeline is reset (GX_Init) and the three main BG
 * screens blanked (0x800 bytes each); VRAM bank A goes to the main BGs, B to the main OBJs, no
 * BG extended palette; the main DISPCNT gets its display mode (bit 4, bit 21) and graphics
 * mode 1 / 0 / 1 (020056b4); BG3 takes priority 3, BG1 priority 0 and DISPCNT shows BG1 / BG3
 * and OBJs (0x1a00).  The sub engine takes banks C (BG) and D (OBJ), no extended palettes,
 * the same display mode, graphics mode 0 (GXS_SetGraphicsMode), layers BG1..BG3 and OBJs
 * (0x1e00) with priorities 1 / 2 / 3, and its LCD is powered off (POWCNT1 bit 15).  The main
 * BG1 / BG3 control words become 0x410 / 8 and the sub BG0..BG3 ones 0 / 0x210 / 0x10c / 4
 * over the two preserved bits; the render mode word is cleared (02084ab4) and the first BG1
 * tile blanked. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct DisplayRegisters {
    volatile u32 dispcnt;      /* +0x00 */
    u8 pad_04[4];
    volatile u16 bg0cnt;       /* +0x08 */
    volatile u16 bg1cnt;       /* +0x0a */
    volatile u16 bg2cnt;       /* +0x0c */
    volatile u16 bg3cnt;       /* +0x0e */
} DisplayRegisters;

static volatile u32 *const REG_DISPCNT = (volatile u32 *)0x04000000;
static volatile u16 *const REG_BG1CNT = (volatile u16 *)0x0400000a;
static volatile u16 *const REG_BG3CNT = (volatile u16 *)0x0400000e;
static volatile u16 *const REG_POWCNT1 = (volatile u16 *)0x04000304;
static volatile DisplayRegisters *const SUB_DISPLAY = (volatile DisplayRegisters *)0x04001000;

extern void  func_0201e1d0(void);                                   /* GX_Init */
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void *G2_GetBG1CharPtr(void);
extern void  MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern void  GX_SetBankForBG(int nBank);
extern void  GX_SetBankForOBJ(int nBank);
extern void  GX_SetBankForBGExtPltt(int nBank);
extern void  func_020056b4(int nMode, int nBgMode, int nBg0Mode);   /* GX_SetGraphicsMode */
extern void  GX_SetBankForSubBG(int nBank);
extern void  GX_SetBankForSubOBJ(int nBank);
extern void  GX_SetBankForSubBGExtPltt(int nBank);
extern void  GX_SetBankForSubOBJExtPltt(int nBank);
extern void  GXS_SetGraphicsMode(int nMode);
extern void  func_ov025_02084ab4(int nMode);                        /* Ov008_SetRenderModeWord */

void func_ov025_0209e93c(void)
{
    func_0201e1d0();
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    GX_SetBankForBG(1);
    GX_SetBankForOBJ(2);
    GX_SetBankForBGExtPltt(0);
    *REG_DISPCNT = (*REG_DISPCNT & 0xffcfffef) | 0x10 | 0x200000;
    func_020056b4(1, 0, 1);
    *REG_BG3CNT = (*REG_BG3CNT & ~3) | 3;
    *REG_BG1CNT = *REG_BG1CNT & ~3;
    *REG_DISPCNT = (*REG_DISPCNT & ~0x1f00) | 0x1a00;
    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
    GX_SetBankForSubBGExtPltt(0);
    GX_SetBankForSubOBJExtPltt(0);
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & 0xffcfffef) | 0x10 | 0x200000;
    GXS_SetGraphicsMode(0);
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & ~0x1f00) | 0x1e00;
    SUB_DISPLAY->bg1cnt = (SUB_DISPLAY->bg1cnt & ~3) | 1;
    SUB_DISPLAY->bg2cnt = (SUB_DISPLAY->bg2cnt & ~3) | 2;
    SUB_DISPLAY->bg3cnt = (SUB_DISPLAY->bg3cnt & ~3) | 3;
    *REG_POWCNT1 = *REG_POWCNT1 & ~0x8000;
    *REG_BG1CNT = (*REG_BG1CNT & 0x43) | 0x410;
    *REG_BG3CNT = (*REG_BG3CNT & 0x43) | 8;
    SUB_DISPLAY->bg0cnt = SUB_DISPLAY->bg0cnt & 0x43;
    SUB_DISPLAY->bg1cnt = (SUB_DISPLAY->bg1cnt & 0x43) | 0x210;
    SUB_DISPLAY->bg2cnt = (SUB_DISPLAY->bg2cnt & 0x43) | 0x10c;
    SUB_DISPLAY->bg3cnt = (SUB_DISPLAY->bg3cnt & 0x43) | 4;
    func_ov025_02084ab4(0);
    MIi_CpuClearFast(0, G2_GetBG1CharPtr(), 0x20);
}
