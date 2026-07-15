/* func_ov000_0204f7d0 -- arm the logo auto-advance timer, ov000. Sets the pending mode
 * (@+0x6a44 = 2 if func_ov000_02054f1c reports active, else 0) and latches the deadline
 * ((tick*64)/0x82ea + 0x5dc) into the scene block @+0x6a58. */
extern int func_ov000_02054f1c(void);
extern unsigned long long func_020031d4(void);
extern unsigned long long func_02020368(unsigned long long value, unsigned int divisor, int arg3);
extern char *data_ov000_0205ac24;
void func_ov000_0204f7d0(void) {
    *(int *)(data_ov000_0205ac24 + 0x6a44) = (func_ov000_02054f1c() != 0) ? 2 : 0;
    *(int *)(data_ov000_0205ac24 + 0x6a58) =
        (unsigned int)(func_02020368(func_020031d4() << 6, 0x82ea, 0) + 0x5dc);
}
