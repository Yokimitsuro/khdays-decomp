extern void func_ov099_020bb058(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov099_0x020ba7c0(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov099_020bb058
}
