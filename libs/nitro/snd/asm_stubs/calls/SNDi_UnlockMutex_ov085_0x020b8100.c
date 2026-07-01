extern void srand_0x0208875c(void);
extern void func_ov085_020b90d4(void);

asm void SNDi_UnlockMutex_ov085_0x020b8100(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov085_020b90d4
}
