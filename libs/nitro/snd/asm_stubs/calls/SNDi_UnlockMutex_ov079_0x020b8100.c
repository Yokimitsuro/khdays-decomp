extern void func_ov079_020b98cc(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov079_0x020b8100(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov079_020b98cc
}
