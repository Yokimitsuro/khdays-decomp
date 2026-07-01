extern void func_ov107_020c7a90(void);

asm void func_ov145_020ce3e8(void)
{
    dcd     0xe5d13002
    dcd     0xe3530000
    dcd     0x1a000006
    dcd     0xe2803c01
    dcd     0xe1d33cd6
    dcd     0xe5c13024
    dcd     0xe59033f4
    dcd     0xe5c13026
    dcd     0xe59033bc
    dcd     0xe5c13025
    ldr ip, [pc, #0]
    bx  ip
    dcd     func_ov107_020c7a90
}
