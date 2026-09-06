typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void func_0201e1d0(void);
extern void GX_SetBankForTex(int bank);
extern void GX_BeginLoadOBJExtPltt(int bank);
extern void G2x_SetBlendAlpha_(volatile u16 *reg, int firstTarget,
                              int secondTarget, int eva, int evb);
extern void G3X_SetClearColor(int red, int green, int blue, int alpha,
                             int polygonId);
extern void func_02010f08(void);
extern void func_02010e80(int mode, int enable);
extern void func_0201133c(void);
extern void func_02011174(int value, int enable);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void GX_SetBankForOBJ(int bank);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void func_020056b4(int displayMode, int bgMode, int bg0Mode);
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForSubBGExtPltt(int bank);
extern void GX_SetBankForSubOBJ(int bank);
extern void GX_SetBankForSubOBJExtPltt(int bank);
extern void func_ov008_02050c8c(int mode);
extern void *G2_GetBG1CharPtr(void);
extern void MIi_CpuClearFast(u32 value, void *destination, u32 size);

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_DISP3DCNT (*(volatile u16 *)0x04000060)
#define REG_DISPCNT_SUB (*(volatile u32 *)0x04001000)
#define REG_POWCNT1 (*(volatile u16 *)0x04000304)

typedef struct DisplayRegisters {
    volatile u32 dispcnt;
    u8 pad_04[4];
    volatile u16 bg0cnt;
    volatile u16 bg1cnt;
    volatile u16 bg2cnt;
    volatile u16 bg3cnt;
    u8 pad_10[0x30];
    volatile u16 win0h;
    volatile u16 win1h;
    volatile u16 win0v;
    volatile u16 win1v;
    volatile u16 winIn;
    volatile u16 winOut;
} DisplayRegisters;

static volatile DisplayRegisters *const MAIN_DISPLAY =
    (volatile DisplayRegisters *)0x04000000;
static volatile DisplayRegisters *const SUB_DISPLAY =
    (volatile DisplayRegisters *)0x04001000;

void func_ov008_020590b4(void)
{
    void *bg1CharData;

    func_0201e1d0();
    GX_SetBankForTex(2);
    GX_BeginLoadOBJExtPltt(0x60);

    REG_DISP3DCNT = REG_DISP3DCNT & 0xffffcffd;
    REG_DISP3DCNT = REG_DISP3DCNT & 0xcffb;
    REG_DISP3DCNT = (REG_DISP3DCNT & ~0x3000) | 8;
    G2x_SetBlendAlpha_((volatile u16 *)0x04000050, 1, 10, 0, 0x10);
    G3X_SetClearColor(0, 0, 0x7fff, 0x3f, 0);

    func_02010f08();
    func_02010e80(1, 1);
    func_0201133c();
    func_02011174(0x8000, 1);

    GX_SetBankForOBJExtPltt(0);
    GX_SetBankForOBJ(1);
    MAIN_DISPLAY->dispcnt =
        (MAIN_DISPLAY->dispcnt & 0xffcfffef) | 0x200010;
    GX_SetBankForBG(0x10);
    GX_SetBankForBGExtPltt(0);
    func_020056b4(1, 0, 1);
    MAIN_DISPLAY->dispcnt =
        (MAIN_DISPLAY->dispcnt & ~0x1f00) | 0x1f00;

    GX_SetBankForSubBG(4);
    GX_SetBankForSubBGExtPltt(0);
    GX_SetBankForSubOBJ(8);
    SUB_DISPLAY->dispcnt =
        (SUB_DISPLAY->dispcnt & 0xffcfffef) | 0x200010;
    GX_SetBankForSubOBJExtPltt(0);
    REG_POWCNT1 |= 0x8000;

    MAIN_DISPLAY->bg1cnt = (MAIN_DISPLAY->bg1cnt & 0x43) | 0x4604;
    MAIN_DISPLAY->bg2cnt = (MAIN_DISPLAY->bg2cnt & 0x43) | 0x4c00;
    MAIN_DISPLAY->bg3cnt = (MAIN_DISPLAY->bg3cnt & 0x43) | 0x4e00;

    func_ov008_02050c8c(1);
    bg1CharData = G2_GetBG1CharPtr();
    MIi_CpuClearFast(0, bg1CharData, 0x20);

    MAIN_DISPLAY->winIn = (MAIN_DISPLAY->winIn & ~0x3f) | 0x1f;
    MAIN_DISPLAY->winOut = (MAIN_DISPLAY->winOut & ~0x3f) | 0x1e;
    MAIN_DISPLAY->win0h = 0x76ca;
    MAIN_DISPLAY->win0v = 0x1e82;
    MAIN_DISPLAY->dispcnt =
        (MAIN_DISPLAY->dispcnt & ~0xe000) | 0x2000;
}
