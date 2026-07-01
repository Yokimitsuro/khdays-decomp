extern void func_ov081_020b9558(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov081_0x020b8100(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov081_020b9558
}
