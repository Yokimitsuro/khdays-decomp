typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern void  func_0201e1d0(void);
extern void  func_02010f08(void);
extern void  func_02010e80(int a, int b);
extern void  func_0201133c(void);
extern void  func_02011174(int a, int b);
extern void  GX_SetBankForOBJ(int bank);
extern void  GX_SetBankForBG(int bank);
extern void  GX_SetBankForBGExtPltt(int bank);
extern void  func_020056b4(int a, int b, int c);
extern void  GX_SetBankForSubBG(int bank);
extern void  GX_SetBankForSubOBJ(int bank);
extern void  GX_SetBankForSubBGExtPltt(int bank);
extern void  GX_SetBankForSubOBJExtPltt(int bank);
extern void  func_ov008_02050c8c(int arg);
extern void *G2_GetBG1CharPtr(void);
extern void  MIi_CpuClearFast(u32 value, void *dst, u32 size);

typedef struct DisplayRegisters {
    volatile u32 dispcnt;
    u8 pad_04[4];
    volatile u16 bg0cnt;
    volatile u16 bg1cnt;
    volatile u16 bg2cnt;
    volatile u16 bg3cnt;
} DisplayRegisters;

static volatile DisplayRegisters *const MAIN_DISPLAY =
    (volatile DisplayRegisters *)0x04000000;
static volatile DisplayRegisters *const SUB_DISPLAY =
    (volatile DisplayRegisters *)0x04001000;
static volatile u16 *const REG_POWCNT1 = (volatile u16 *)0x04000304;

void func_ov008_02067c04(void)
{
    void *charData;

    func_0201e1d0();
    func_02010f08();
    func_02010e80(1, 1);
    func_0201133c();
    func_02011174(0x10000, 1);

    MAIN_DISPLAY->dispcnt =
        (MAIN_DISPLAY->dispcnt & 0xffcfffef) | 0x10 | 0x200000;
    GX_SetBankForOBJ(1);
    GX_SetBankForBG(2);
    GX_SetBankForBGExtPltt(0);
    func_020056b4(1, 0, 1);
    MAIN_DISPLAY->dispcnt =
        (MAIN_DISPLAY->dispcnt & ~0x1f00) | 0x1e00;

    SUB_DISPLAY->dispcnt =
        (SUB_DISPLAY->dispcnt & 0xffcfffef) | 0x10 | 0x200000;
    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
    GX_SetBankForSubBGExtPltt(0);
    GX_SetBankForSubOBJExtPltt(0);
    SUB_DISPLAY->dispcnt =
        (SUB_DISPLAY->dispcnt & ~0x1f00) | 0x1f00;

    *REG_POWCNT1 |= 0x8000;

    MAIN_DISPLAY->bg1cnt = (MAIN_DISPLAY->bg1cnt & 0x43) | 0x410;
    MAIN_DISPLAY->bg2cnt = (MAIN_DISPLAY->bg2cnt & 0x43) | 0x4008;
    MAIN_DISPLAY->bg3cnt = (MAIN_DISPLAY->bg3cnt & 0x43) | 0x208;
    SUB_DISPLAY->bg0cnt = (SUB_DISPLAY->bg0cnt & 0x43) | 0x4080;
    SUB_DISPLAY->bg1cnt = (SUB_DISPLAY->bg1cnt & 0x43) | 0x4290;
    SUB_DISPLAY->bg2cnt = (SUB_DISPLAY->bg2cnt & 0x43) | 0x4490;
    SUB_DISPLAY->bg3cnt = (SUB_DISPLAY->bg3cnt & 0x43) | 0x4690;

    func_ov008_02050c8c(1);
    charData = G2_GetBG1CharPtr();
    MIi_CpuClearFast(0, charData, 0x20);
}
