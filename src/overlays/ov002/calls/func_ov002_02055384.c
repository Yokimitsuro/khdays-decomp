extern int func_0201e428(void);
extern void func_0201e374(int nValue);
extern void func_0201e3cc(int nValue);
extern void GX_SetBankForBG(int nBank);
extern void GX_SetBankForBGExtPltt(int nBank);
extern void GX_SetBankForSubBG(int nBank);
extern void func_020056b4(int a, int b, int c);

/* Bring up the background layers for this scene: claim the VRAM banks and give
 * BG0 the lowest priority with BG1..3 in front of it. */
void func_ov002_02055384(void)
{
    volatile unsigned short *reg_bg0cnt = (volatile unsigned short *)0x04000008;
    volatile unsigned short *reg_bg1cnt = (volatile unsigned short *)0x0400000a;
    volatile unsigned short *reg_bg2cnt = (volatile unsigned short *)0x0400000c;
    volatile unsigned short *reg_bg3cnt = (volatile unsigned short *)0x0400000e;

    if (func_0201e428() != 0x10) {
        func_0201e374(~0xf);
        func_0201e3cc(~0xf);
    }

    GX_SetBankForBG(0x10);
    func_020056b4(1, 0, 1);
    GX_SetBankForBGExtPltt(0);
    GX_SetBankForSubBG(6 << 6);

    *reg_bg0cnt = (*reg_bg0cnt & ~3) | 3;
    *reg_bg1cnt = *reg_bg1cnt & ~3;
    *reg_bg2cnt = (*reg_bg2cnt & ~3) | 1;
    *reg_bg3cnt = (*reg_bg3cnt & ~3) | 2;
}
