extern void srand_0x0208875c(void);
extern void func_ov094_020bc0d4(void);

asm void SNDi_UnlockMutex_ov094_0x020ba7c0(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov094_020bc0d4
}
