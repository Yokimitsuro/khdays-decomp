extern void srand_0x0208875c(void);
extern void func_ov031_020b4c2c(void);

asm void SNDi_UnlockMutex_ov031_0x020b3220(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov031_020b4c2c
}
