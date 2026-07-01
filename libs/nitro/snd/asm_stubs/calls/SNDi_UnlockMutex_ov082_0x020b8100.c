extern void func_ov082_020b8998(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov082_0x020b8100(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov082_020b8998
}
