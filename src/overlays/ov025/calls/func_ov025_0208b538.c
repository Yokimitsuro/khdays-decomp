/* func_ov025_0208b538 -- Ov025_Hub_SetupGraphics: bring both engines up for the records hub.
 * After GX_Init the texture bank is 2 and the OBJ palette loads at 0x60; DISP3DCNT loses bits
 * 1, 2, 12..13 for bit 3 and the 3D clear colour is white (0x7fff, alpha 0x3f); the sprite layer
 * is reset (02010f08, 02010e80 1 / 1, 0201133c, 02011174 with 0x8000) with OBJ bank 1 and no
 * OBJ extended palette; DISPCNT takes bits 4 and 21 and, after BG bank 0x10 with no extended
 * palette and graphics mode 1 / 0 / 1 (020056b4), shows BG0..BG3 and OBJ.  The sub engine gets
 * BG bank 4, OBJ bank 8, no extended palettes and the same DISPCNT bits; POWCNT1 bit 15 is set,
 * BG1..BG3 get their control words (0x4604 / 0x4c00 / 0x4e00 over the two preserved bits), the
 * 95d0 mode becomes 1 (02084ab4) and the first BG1 character tile is cleared. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct DisplayRegisters {
    volatile u32 dispcnt;     /* 0x00 */
    u8   pad_04[4];
    volatile u16 bg0cnt;      /* 0x08 */
    volatile u16 bg1cnt;      /* 0x0a */
    volatile u16 bg2cnt;      /* 0x0c */
    volatile u16 bg3cnt;      /* 0x0e */
} DisplayRegisters;

static volatile DisplayRegisters *const MAIN_DISPLAY = (volatile DisplayRegisters *)0x04000000;
static volatile DisplayRegisters *const SUB_DISPLAY = (volatile DisplayRegisters *)0x04001000;
static volatile u16 *const REG_DISP3DCNT = (volatile u16 *)0x04000060;
static volatile u16 *const REG_POWCNT1 = (volatile u16 *)0x04000304;

extern void  func_0201e1d0(void);                                   /* GX_Init */
extern void  GX_SetBankForTex(int nBank);
extern void  GX_BeginLoadOBJExtPltt(int nOffset);
extern void  G3X_SetClearColor(int nColour, int nAlpha, int nDepth, int nPolyId, int bFog);
extern void  func_02010f08(void);
extern void  func_02010e80(int nA, int nB);
extern void  func_0201133c(void);
extern void  func_02011174(int nA, int nB);
extern void  GX_SetBankForOBJExtPltt(int nBank);
extern void  GX_SetBankForOBJ(int nBank);
extern void  GX_SetBankForBG(int nBank);
extern void  GX_SetBankForBGExtPltt(int nBank);
extern void  func_020056b4(int nMode, int nBgMode, int nBg0Mode);   /* GX_SetGraphicsMode */
extern void  GX_SetBankForSubBG(int nBank);
extern void  GX_SetBankForSubBGExtPltt(int nBank);
extern void  GX_SetBankForSubOBJ(int nBank);
extern void  GX_SetBankForSubOBJExtPltt(int nBank);
extern void  func_ov025_02084ab4(int nMode);                        /* Ov025_SetMode95d0 */
extern void *G2_GetBG1CharPtr(void);
extern void  MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);

void func_ov025_0208b538(void)
{
    u32 mask;

    func_0201e1d0();
    GX_SetBankForTex(2);
    GX_BeginLoadOBJExtPltt(0x60);
    mask = 0xffffcffd;
    *REG_DISP3DCNT = *REG_DISP3DCNT & mask;
    *REG_DISP3DCNT = *REG_DISP3DCNT & 0xcffb;
    *REG_DISP3DCNT = (*REG_DISP3DCNT & ~0x3000) | 8;
    G3X_SetClearColor(0, 0, mask >> 0x11, 0x3f, 0);
    func_02010f08();
    func_02010e80(1, 1);
    func_0201133c();
    func_02011174(0x8000, 1);
    GX_SetBankForOBJExtPltt(0);
    GX_SetBankForOBJ(1);
    MAIN_DISPLAY->dispcnt = (MAIN_DISPLAY->dispcnt & 0xffcfffef) | 0x200010;
    GX_SetBankForBG(0x10);
    GX_SetBankForBGExtPltt(0);
    func_020056b4(1, 0, 1);
    MAIN_DISPLAY->dispcnt = (MAIN_DISPLAY->dispcnt & 0xffffe0ff) | 0x1f00;
    GX_SetBankForSubBG(4);
    GX_SetBankForSubBGExtPltt(0);
    GX_SetBankForSubOBJ(8);
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & 0xffcfffef) | 0x200010;
    GX_SetBankForSubOBJExtPltt(0);
    *REG_POWCNT1 |= 0x8000;
    MAIN_DISPLAY->bg1cnt = (MAIN_DISPLAY->bg1cnt & 0x43) | 0x4604;
    MAIN_DISPLAY->bg2cnt = (MAIN_DISPLAY->bg2cnt & 0x43) | 0x4c00;
    MAIN_DISPLAY->bg3cnt = (MAIN_DISPLAY->bg3cnt & 0x43) | 0x4e00;
    func_ov025_02084ab4(1);
    MIi_CpuClearFast(0, G2_GetBG1CharPtr(), 0x20);
}
