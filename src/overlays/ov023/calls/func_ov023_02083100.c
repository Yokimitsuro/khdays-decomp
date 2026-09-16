/* func_ov023_02083100 -- Ov023_SetupMainBackgrounds: bring the main engine up for the event
 * scene.  All VRAM goes to the LCDC (GX_SetBankForLCDC 0x1ff) and 0xa4000 bytes from
 * 0x06800000 are cleared, the sound mutex released (020065d4), then the banks are handed out:
 * texture 7, OBJ palette at 0x20 with bank 0x40 for sprites in a session (bits 1 / 2 of
 * data_0204c240) or 0x60 otherwise, BG 0x10, no BG extended palette; graphics mode 1 / 0 / 1
 * (020056b4).  BG1 / BG2 get their control words (0x1f08 / 0x1e04 over the two preserved
 * bits), DISPCNT shows BG0..BG2 (bits 8..10), the priorities become BG0 3, BG3 2, BG2 1,
 * BG1 0 and DISP3DCNT loses bits 1, 2, 12..13 for bit 3.  Both OAMs are cleared to 0xc0 and
 * both palettes to 0 (MIi_CpuClearFast), the sprite layer reset (02010f08, 02010e80 3 / 1,
 * 0201133c, 02011174 with 0x4000 in a session or 0x8000 otherwise), the LCD enabled
 * (POWCNT bit 15) and the game mode set to 0 (02023c30). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

static volatile u32 *const REG_DISPCNT = (volatile u32 *)0x04000000;
static volatile u16 *const REG_BG0CNT = (volatile u16 *)0x04000008;
static volatile u16 *const REG_BG1CNT = (volatile u16 *)0x0400000a;
static volatile u16 *const REG_BG2CNT = (volatile u16 *)0x0400000c;
static volatile u16 *const REG_BG3CNT = (volatile u16 *)0x0400000e;
static volatile u16 *const REG_DISP3DCNT = (volatile u16 *)0x04000060;
static volatile u16 *const REG_POWCNT = (volatile u16 *)0x04000304;

extern void GX_SetBankForLCDC(int nBanks);
extern void MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern void SNDi_UnlockMutex_0x020065d4(void);
extern void GX_SetBankForTex(int nBank);
extern void GX_BeginLoadOBJExtPltt(int nOffset);
extern void GX_SetBankForOBJ(int nBank);
extern void GX_SetBankForBG(int nBank);
extern void GX_SetBankForBGExtPltt(int nBank);
extern void func_020056b4(int nMode, int nBgMode, int nBg0Mode);    /* GX_SetGraphicsMode */
extern void func_02010f08(void);
extern void func_02010e80(int nA, int nB);
extern void func_0201133c(void);
extern void func_02011174(int nA, int nB);
extern void func_02023c30(int nMode);                               /* SetGameMode */
extern u8   data_0204c240;                                          /* session bits */

void func_ov023_02083100(void)
{
    int bSession;

    GX_SetBankForLCDC(0x1ff);
    MIi_CpuClearFast(0, (void *)0x06800000, 0xa4000);
    SNDi_UnlockMutex_0x020065d4();
    GX_SetBankForTex(7);
    if ((data_0204c240 & 4) || (data_0204c240 & 2)) {
        GX_BeginLoadOBJExtPltt(0x20);
        GX_SetBankForOBJ(0x40);
    } else {
        GX_BeginLoadOBJExtPltt(0x60);
    }
    GX_SetBankForBG(0x10);
    GX_SetBankForBGExtPltt(0);
    func_020056b4(1, 0, 1);
    *REG_BG1CNT = (*REG_BG1CNT & 0x43) | 0x1f08;
    *REG_BG2CNT = (*REG_BG2CNT & 0x43) | 0x1e04;
    *REG_DISPCNT = (*REG_DISPCNT & 0xffffe0ff) | 0x700;
    *REG_BG0CNT = (*REG_BG0CNT & ~3) | 3;
    *REG_BG3CNT = (*REG_BG3CNT & ~3) | 2;
    *REG_BG2CNT = (*REG_BG2CNT & ~3) | 1;
    *REG_BG1CNT &= ~3;
    *REG_DISP3DCNT &= 0xffffcffd;
    *REG_DISP3DCNT &= 0xcffb;
    *REG_DISP3DCNT = (*REG_DISP3DCNT & ~0x3000) | 8;
    MIi_CpuClearFast(0xc0, (void *)0x07000000, 0x400);
    MIi_CpuClearFast(0xc0, (void *)0x07000400, 0x400);
    MIi_CpuClearFast(0, (void *)0x05000000, 0x400);
    MIi_CpuClearFast(0, (void *)0x05000400, 0x400);
    func_02010f08();
    func_02010e80(3, 1);
    func_0201133c();
    bSession = 1;
    if (!(data_0204c240 & 4) && !(data_0204c240 & 2)) {
        bSession = 0;
    }
    func_02011174((bSession ? 1 : 2) << 14, 1);
    *REG_POWCNT |= 0x8000;
    func_02023c30(0);
}
