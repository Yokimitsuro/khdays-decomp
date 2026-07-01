extern void func_ov035_020b4b48(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov035_0x020b3220(void)
{
    dcd     0xe59fc004
    dcd     0xe59f0004
    dcd     0xe12fff1c
    dcd     srand_0x0208875c
    dcd     func_ov035_020b4b48
}
