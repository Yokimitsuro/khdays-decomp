extern void func_ov065_020b7240(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov065_0x020b5a20(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov065_020b7240
}
