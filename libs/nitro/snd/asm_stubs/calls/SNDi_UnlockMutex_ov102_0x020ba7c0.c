extern void srand_0x0208875c(void);
extern void func_ov102_020bb794(void);

asm void SNDi_UnlockMutex_ov102_0x020ba7c0(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov102_020bb794
}
