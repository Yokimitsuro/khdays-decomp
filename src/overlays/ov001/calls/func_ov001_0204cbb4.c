extern void func_020163cc(void);
extern void G3X_InitMtxStack(void);
extern void GX_SetBankForTex(int bank);
extern void GX_BeginLoadOBJExtPltt(int offset);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void func_020056b4(int a, int b, int c);
extern void func_ov001_0204cb30(void);
extern void func_0200566c(void);

void func_ov001_0204cbb4(void) {
    volatile unsigned int *reg_dispcnt = (volatile unsigned int *)0x04000000;
    volatile unsigned short *reg_bg0cnt = (volatile unsigned short *)0x04000008;
    volatile unsigned short *reg_bg1cnt = (volatile unsigned short *)0x0400000a;
    volatile unsigned short *reg_bldcnt = (volatile unsigned short *)0x04000050;
    volatile unsigned short *reg_disp3dcnt = (volatile unsigned short *)0x04000060;
    volatile unsigned int *reg_swap_buffers = (volatile unsigned int *)0x04000540;
    volatile unsigned int *reg_viewport = (volatile unsigned int *)0x04000580;
    volatile unsigned int *reg_04001000 = (volatile unsigned int *)0x04001000;

    func_020163cc();
    G3X_InitMtxStack();
    GX_SetBankForTex(7);
    GX_BeginLoadOBJExtPltt(0x60);
    GX_SetBankForBG(0x10);
    GX_SetBankForBGExtPltt(0);
    func_020056b4(1, 0, 1);

    *reg_dispcnt = (*reg_dispcnt & ~0x1f00) | 0x300;
    *reg_dispcnt &= ~0x7000000;
    *reg_dispcnt &= ~0x38000000;

    *reg_bg1cnt = (unsigned short)((*reg_bg1cnt & 0x43) | 0x400);
    *reg_bg0cnt = (unsigned short)((*reg_bg0cnt & ~3) | 1);
    *reg_bg1cnt = (unsigned short)(*reg_bg1cnt & ~3);
    *reg_disp3dcnt = (unsigned short)(*reg_disp3dcnt & ~0x3002);
    *reg_disp3dcnt = (unsigned short)((*reg_disp3dcnt & ~0x3000) | 0x10);
    *reg_bldcnt = 0;
    *reg_swap_buffers = 2;
    *reg_disp3dcnt = (unsigned short)(*reg_disp3dcnt & 0xcffb);
    *reg_disp3dcnt = (unsigned short)((*reg_disp3dcnt & ~0x3000) | 8);
    *reg_viewport = 0xbfff0000;

    func_ov001_0204cb30();
    func_0200566c();
    *reg_04001000 |= 0x10000;
}
