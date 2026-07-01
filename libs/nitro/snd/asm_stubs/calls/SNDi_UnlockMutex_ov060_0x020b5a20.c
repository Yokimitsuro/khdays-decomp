extern void func_ov060_020b73f4(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov060_0x020b5a20(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov060_020b73f4
}
