extern void func_ov035_020b3b5c(void);

asm void func_ov035_020b3b14(void)
{
    ldr ip, [pc, #4]
    dcd     0xe2811010
    bx  ip
    dcd     func_ov035_020b3b5c
}
