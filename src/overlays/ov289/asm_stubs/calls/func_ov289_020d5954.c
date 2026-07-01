extern void func_ov107_020c7a90(void);

asm void func_ov289_020d5954(void)
{
    dcd     0xe5d13002
    ldr ip, [pc, #12]
    dcd     0xe3530000
    dcd     0x05903394
    dcd     0x05c13024
    bx  ip
    dcd     func_ov107_020c7a90
}
