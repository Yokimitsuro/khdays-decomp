extern void func_ov048_020b4a34(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov048_0x020b3220(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov048_020b4a34
}
