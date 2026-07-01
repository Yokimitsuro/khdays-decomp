extern void func_ov041_020b4bf4(void);
extern void srand_0x0208875c(void);

asm void SNDi_UnlockMutex_ov041_0x020b3220(void)
{
    ldr ip, [pc, #4]
    dcd     0xe59f0004
    bx  ip
    dcd     srand_0x0208875c
    dcd     func_ov041_020b4bf4
}
