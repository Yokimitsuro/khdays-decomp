extern void srand_0x0208875c(void);
extern void func_ov031_020b4c2c(void);

asm void SNDi_UnlockMutex_ov031_0x020b3220(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov031_020b4c2c
}
