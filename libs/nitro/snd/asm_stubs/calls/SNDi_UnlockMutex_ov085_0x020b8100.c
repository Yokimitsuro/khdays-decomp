extern void srand_0x0208875c(void);
extern void func_ov085_020b90d4(void);

asm void SNDi_UnlockMutex_ov085_0x020b8100(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov085_020b90d4
}
