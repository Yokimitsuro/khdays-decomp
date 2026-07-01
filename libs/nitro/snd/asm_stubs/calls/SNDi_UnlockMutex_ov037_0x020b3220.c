extern void func_ov037_020b4cec(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov037_0x020b3220(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov037_020b4cec
}
