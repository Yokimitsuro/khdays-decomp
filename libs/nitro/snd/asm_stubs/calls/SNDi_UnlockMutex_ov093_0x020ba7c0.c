extern void func_ov093_020bc28c(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov093_0x020ba7c0(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov093_020bc28c
}
