extern void func_ov101_020bbfe0(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov101_0x020ba7c0(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov101_020bbfe0
}
