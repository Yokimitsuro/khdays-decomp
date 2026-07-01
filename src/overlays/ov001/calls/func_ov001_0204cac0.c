extern int GX_SetBankForLCDC();
extern int MIi_CpuClearFast();
extern int SNDi_UnlockMutex_0x020065d4();

void func_ov001_0204cac0(void) {
    GX_SetBankForLCDC(0x1ff);
    MIi_CpuClearFast(0, (void *)0x06800000, 0xa4000);
    SNDi_UnlockMutex_0x020065d4();
    MIi_CpuClearFast(0xc0, (void *)0x07000000, 0x400);
    MIi_CpuClearFast(0xc0, (void *)0x07000400, 0x400);
    MIi_CpuClearFast(0, (void *)0x05000000, 0x400);
    MIi_CpuClearFast(0, (void *)0x05000400, 0x400);
}
