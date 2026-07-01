extern void srand_0x0208875c(void);
extern void func_ov078_020ba258(void);

asm void SNDi_UnlockMutex_ov078_0x020b8100(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov078_020ba258
}
