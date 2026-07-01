extern void func_ov041_020b4bf4(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov041_0x020b3220(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov041_020b4bf4
}
