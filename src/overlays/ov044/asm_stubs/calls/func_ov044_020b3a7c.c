extern void func_ov044_020b4884(void);

asm void func_ov044_020b3a7c(void)
{
    ldr ip, [pc, #8]
    dcd     0xe28000a8
    dcd     0xe2800b0b
    bx  ip
    dcd     func_ov044_020b4884
}
