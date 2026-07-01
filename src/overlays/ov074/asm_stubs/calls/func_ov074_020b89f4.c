extern void func_ov074_020b8a3c(void);

asm void func_ov074_020b89f4(void)
{
    ldr ip, [pc, #4]
    dcd     0xe2811010
    bx  ip
    dcd     func_ov074_020b8a3c
}
