/* Black both screens, clear VRAM, and configure the overlay's graphics banks. */
extern void func_0201e374(int);
extern void func_0201e3cc(int);
extern void func_0201e1d0(void);
extern void GX_SetBankForLCDC(int);
extern void MIi_CpuClearFast(unsigned int,void *,unsigned int);
extern void SNDi_UnlockMutex_0x020065d4(void);
extern void func_ov005_02051408(void);
extern void func_ov005_02051440(void);
extern void func_ov005_020514ec(void);
void func_ov005_02051560(void) {
    func_0201e374(-16);
    func_0201e3cc(-16);
    func_0201e1d0();
    GX_SetBankForLCDC(0x1ff);
    MIi_CpuClearFast(0,(void *)0x06800000,0xa4000);
    SNDi_UnlockMutex_0x020065d4();
    func_ov005_02051408();
    func_ov005_02051440();
    func_ov005_020514ec();
    *(volatile unsigned short *)0x04000304 &= ~0x8000;
    *(volatile unsigned int *)0x04000000 &= ~0x1f00;
    *(volatile unsigned int *)0x04001000 &= ~0x1f00;
}
