extern void func_ov022_02091474(void);

asm void func_ov037_020b3a28(void)
{
    ldr ip, [pc, #8]
    dcd     0xe2800a02
    dcd     0xe5900644
    bx  ip
    dcd     func_ov022_02091474
}
