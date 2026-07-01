extern void func_ov044_020b4c14(void);

asm void func_ov044_020b3a90(void)
{
    ldr ip, [pc, #8]
    dcd     0xe28000a8
    dcd     0xe2800b0b
    bx  ip
    dcd     func_ov044_020b4c14
}
