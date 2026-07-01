extern void func_ov038_020b4b34(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov038_0x020b3220(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov038_020b4b34
}
