extern void func_ov063_020b7414(void);

asm void func_ov063_020b6290(void)
{
    ldr ip, [pc, #8]
    dcd     0xe28000a8
    dcd     0xe2800b0b
    bx  ip
    dcd     func_ov063_020b7414
}
