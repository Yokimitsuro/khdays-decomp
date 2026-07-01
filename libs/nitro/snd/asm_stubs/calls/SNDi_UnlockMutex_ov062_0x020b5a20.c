extern void srand_0x0208875c(void);
extern void func_ov050_020b742c(void);

asm void SNDi_UnlockMutex_ov062_0x020b5a20(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov050_020b742c
}
