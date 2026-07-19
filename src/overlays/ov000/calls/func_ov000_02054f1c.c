extern void func_02020904(void);
extern void CARD_UnlockBackup(unsigned short lock);
extern int func_ov000_02054914(int a, int *out, int b);
extern void MI_CpuFill8(void *dst, int value, unsigned size);
extern int func_ov000_0205493c(int off, void *buf, unsigned size);
extern void func_0200e164(unsigned short lock);
extern void OS_WaitVBlankIntr(void);
extern void func_020208f0(void);
extern unsigned short data_0204be10;
extern void *data_0204be14;

/* Writes both copies of one save slot's header. Returns 0 if the card refuses at any point. */
int func_ov000_02054f1c(int slot) {
    int scratch;
    func_02020904();
    CARD_UnlockBackup(data_0204be10);
    if (func_ov000_02054914(0, &scratch, 1) == 0) {
        MI_CpuFill8(data_0204be14, 0, 0x2018);
        slot *= 2;
        if (func_ov000_0205493c(slot * 0x2018 + 0x20, data_0204be14, 0x20) == 0) {
            func_0200e164(data_0204be10);
            OS_WaitVBlankIntr();
            CARD_UnlockBackup(data_0204be10);
            if (func_ov000_0205493c((slot + 1) * 0x2018 + 0x20, data_0204be14, 0x20) == 0) {
                func_0200e164(data_0204be10);
                func_020208f0();
                return 1;
            }
        }
    }
    func_0200e164(data_0204be10);
    func_020208f0();
    return 0;
}
