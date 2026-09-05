extern void func_0201e374(int level);
extern void func_0201e3cc(int level);
extern void func_0201e1d0(void);
extern void func_ov024_0208462c(int doMain, int doSub);
extern void func_020056b4(int a, int b, int c);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForBGExtPltt(int bank);

void func_ov012_0205ad1c(void) {
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    func_0201e1d0();
    func_ov024_0208462c(0, 1);
    func_020056b4(1, 0, 0);
    GX_SetBankForBG(3);
    GX_SetBankForBGExtPltt(0);
    {
        volatile unsigned short *bg = (volatile unsigned short *)0x04000008;

        bg[0] = bg[0] & 0x43 | 0x84;
        bg[1] = bg[1] & 0x43 | 0x290;
        bg[2] = bg[2] & 0x43 | 0x4a0;
        *(volatile unsigned int *)0x04000000 &= ~0x1f00;
        bg[0] = bg[0] & ~3 | 2;
        bg[1] = bg[1] & ~3 | 1;
        bg[2] = bg[2] & ~3;
        *(volatile unsigned short *)0x04000304 &= ~0x8000;
    }
}
