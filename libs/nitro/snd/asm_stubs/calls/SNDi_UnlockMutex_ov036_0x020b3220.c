extern void srand_0x0208875c(void);
extern void func_ov036_020b4df0(void);

asm void SNDi_UnlockMutex_ov036_0x020b3220(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov036_020b4df0
}
