extern void func_ov099_020bc1b4(void);

asm void func_ov099_020bb030(void)
{
    ldr ip, [pc, #8]
    dcd     0xe28000a8
    dcd     0xe2800b0b
    bx  ip
    dcd     func_ov099_020bc1b4
}
