extern void srand_0x0208875c(void);
extern void func_ov088_020bc1cc(void);

asm void SNDi_UnlockMutex_ov088_0x020ba7c0(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov088_020bc1cc
}
