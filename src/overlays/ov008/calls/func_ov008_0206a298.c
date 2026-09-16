/* func_ov008_0206a298 -- Ov008_SetupGridMenuDisplay: configure the video
 * hardware for the panel grid menu.  The 3D pipeline is reset, the main BG1..3
 * screen maps cleared, banks A/B assigned to BG/OBJ with no BG extended
 * palette, the main DISPCNT set to display mode 1 with BG mode 1 (2D +
 * 3D on BG0, engine mode 1/0/1), BG3 at priority 3 and BG1 at priority 0,
 * then the main display mode bits set to 0x1a; the sub engine gets banks
 * C/D for BG/OBJ, display mode with every layer on (0x1f) and the sub LCD
 * powered; the layer control words are then set (main BG1 0x4410, main BG3
 * 0x4008, sub BG0 0x4080, BG1 0x4290, BG2 0x4490, BG3 0x4690), the render
 * mode word set to 1 and the first main BG1 character cleared.
 *
 * MMIO through held volatile register pointers as in Ov008_MainMenu_SetupDisplay.
 * Codegen (this function only, under `opt_propagation off`): the main BG3CNT
 * address is a pointer local that mwcc keeps in r4 across the four sub-bank
 * calls and derives BG1CNT from (`sub r3, r4, #4` in the first group, then
 * `sub ip, r4, #4` for the second group's own BG1CNT pointer local, whose
 * +2 / +0x800 halfwords are main BG3CNT and sub BG1CNT); the other registers
 * are plain literals or struct fields; and the clear routine is declared
 * with an int result, which is what keeps the group-2 pointer derivation
 * out of the sub-DISPCNT load's delay slot.
 */
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

static volatile DisplayRegisters *const MAIN_DISPLAY = (volatile DisplayRegisters *)0x04000000;
static volatile DisplayRegisters *const SUB_DISPLAY  = (volatile DisplayRegisters *)0x04001000;
static volatile u16 *const REG_POWCNT1 = (volatile u16 *)0x04000304;

#define REG_BG1CNT_ADDR     0x0400000a
#define REG_BG3CNT_ADDR     0x0400000e
#define REG_DB_BG1CNT_ADDR  0x0400100a

extern void  func_0201e1d0(void);                                         /* GX_Init */
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void *G2_GetBG1CharPtr(void);
extern int   MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);    /* declared with a result: see Codegen */
extern void  GX_SetBankForBG(int nBank);
extern void  GX_SetBankForOBJ(int nBank);
extern void  GX_SetBankForBGExtPltt(int nBank);
extern void  func_020056b4(int nMode, int nBgMode, int nBg0Mode);         /* GX_SetGraphicsMode */
extern void  GX_SetBankForSubBG(int nBank);
extern void  GX_SetBankForSubOBJ(int nBank);
extern void  GX_SetBankForSubBGExtPltt(int nBank);
extern void  GX_SetBankForSubOBJExtPltt(int nBank);
extern void  func_ov008_02050c8c(int nMode);                              /* Ov008_SetRenderModeWord */

#pragma push
#pragma opt_propagation off
void func_ov008_0206a298(void)
{
    volatile u16 *pBg3;
    volatile u16 *pBg1;

    func_0201e1d0();
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    GX_SetBankForBG(1);
    GX_SetBankForOBJ(2);
    GX_SetBankForBGExtPltt(0);
    MAIN_DISPLAY->dispcnt = (MAIN_DISPLAY->dispcnt & 0xffcfffef) | 0x200010;
    func_020056b4(1, 0, 1);
    pBg3 = (volatile u16 *)REG_BG3CNT_ADDR;
    *pBg3 = (*pBg3 & ~3) | 3;
    *(volatile u16 *)REG_BG1CNT_ADDR = *(volatile u16 *)REG_BG1CNT_ADDR & ~3;
    MAIN_DISPLAY->dispcnt = (MAIN_DISPLAY->dispcnt & ~0x1f00) | 0x1a00;
    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
    GX_SetBankForSubBGExtPltt(0);
    GX_SetBankForSubOBJExtPltt(0);
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & 0xffcfffef) | 0x200010;
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & ~0x1f00) | 0x1f00;
    *REG_POWCNT1 |= 0x8000;
    pBg1 = (volatile u16 *)REG_BG1CNT_ADDR;
    *pBg1 = (*pBg1 & 0x43) | 0x4410;
    pBg1[2] = (pBg1[2] & 0x43) | 0x4008;
    SUB_DISPLAY->bg0cnt = (SUB_DISPLAY->bg0cnt & 0x43) | 0x4080;
    *(volatile u16 *)REG_DB_BG1CNT_ADDR = (*(volatile u16 *)REG_DB_BG1CNT_ADDR & 0x43) | 0x4290;
    SUB_DISPLAY->bg2cnt = (SUB_DISPLAY->bg2cnt & 0x43) | 0x4490;
    SUB_DISPLAY->bg3cnt = (SUB_DISPLAY->bg3cnt & 0x43) | 0x4690;
    func_ov008_02050c8c(1);
    MIi_CpuClearFast(0, G2_GetBG1CharPtr(), 0x20);
}
#pragma pop
