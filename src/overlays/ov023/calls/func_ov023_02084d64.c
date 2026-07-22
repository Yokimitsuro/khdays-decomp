/* func_ov023_02084d64 -- ov023 teardown. In global mode 4 only: hand the screens back
 * (func_020056b4), map VRAM bank 8 to the LCDC, wipe 0xa4000 bytes of it from 0x06800000, and
 * release the sound mutex. Then drop the scene request (func_02023560(0)). */
extern int func_02020a9c(void);
extern void func_020056b4(int a, int b, int c);
extern void GX_SetBankForLCDC(int bank);
extern void MIi_CpuClearFast(int value, void *dst, int size);
extern void SNDi_UnlockMutex_0x020065d4(void);
extern void func_02023560(int a);

void func_ov023_02084d64(void) {
    if (func_02020a9c() == 4) {
        func_020056b4(1, 0, 1);
        GX_SetBankForLCDC(8);
        MIi_CpuClearFast(0, (void *)0x06800000, 0xa4000);
        SNDi_UnlockMutex_0x020065d4();
    }
    func_02023560(0);
}
