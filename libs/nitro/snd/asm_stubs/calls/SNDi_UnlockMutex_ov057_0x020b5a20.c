extern void srand_0x0208875c(void);
extern void func_ov057_020b7334(void);

asm void SNDi_UnlockMutex_ov057_0x020b5a20(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov057_020b7334
}
