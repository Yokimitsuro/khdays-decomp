/* func_ov025_0209d720 -- Ov025_Tutorial_SetupDisplay: configure the video hardware for the
 * tutorial page.  The 3D pipeline is reset (0201e1d0) and the three main BG screens blanked
 * (0x800 bytes each); VRAM bank A goes to the main BGs, B to the main OBJs, no BG extended
 * palette; the main DISPCNT gets its display mode (bit 4, bit 21) and graphics mode 1 / 0 / 1
 * (020056b4); BG3 takes priority 3, BG1 priority 0 and DISPCNT shows BG1 / BG3 and OBJs
 * (0x1a00).  The sub engine takes banks C (BG) and D (OBJ), no extended palettes, the same
 * display mode, all layers (0x1f00) and its LCD is powered off (POWCNT1 bit 15).  BG1 / BG3 of
 * the main engine get their control words (0x4410 / 0x4008 over the two preserved bits),
 * the shared entry contexts are reset (02084ab4) and the first BG1 tile cleared. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct DisplayRegisters {
    volatile u32 dispcnt;      /* +0x00 */
    u8 pad_04[4];
    volatile u16 bg0cnt;       /* +0x08 */
    volatile u16 bg1cnt;       /* +0x0a */
    volatile u16 bg2cnt;       /* +0x0c */
    volatile u16 bg3cnt;       /* +0x0e */
} DisplayRegisters;
typedef short          s16;

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
extern int   MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern void  GX_SetBankForBG(int nBank);
extern void  GX_SetBankForOBJ(int nBank);
extern void  GX_SetBankForBGExtPltt(int nBank);
extern void  func_020056b4(int nMode, int nBgMode, int nBg0Mode);   /* GX_SetGraphicsMode */
extern void  GX_SetBankForSubBG(int nBank);
extern void  GX_SetBankForSubOBJ(int nBank);
extern void  GX_SetBankForSubBGExtPltt(int nBank);
extern void  GX_SetBankForSubOBJExtPltt(int nBank);
extern void  func_ov025_02084ab4(int nMode);                         /* Ov008_ResetEntryContexts */

void func_ov025_0209d720(void)
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
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & ~0x1f00) | 0x1f00;
    *REG_POWCNT1 = *REG_POWCNT1 & ~0x8000;
    *REG_BG1CNT = (*REG_BG1CNT & 0x43) | 0x410 | 0x4000;
    *REG_BG3CNT = (*REG_BG3CNT & 0x43) | 8 | 0x4000;
    func_ov025_02084ab4(1);
    MIi_CpuClearFast(0, G2_GetBG1CharPtr(), 0x20);
}

