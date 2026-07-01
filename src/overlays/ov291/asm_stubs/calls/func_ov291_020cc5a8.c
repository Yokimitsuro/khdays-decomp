extern void OS_IsThreadAvailable_0x020c9848(void);

asm void func_ov291_020cc5a8(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe2840c01
    dcd     0xe1d02cd7
    dcd     0xe3e01000
    dcd     0xe1520001
    dcd     0x18bd8010
    dcd     0xe1d00cd6
    dcd     0xe3500000
    dcd     0x13500006
    dcd     0x08bd8010
    dcd     0xe3a00006
    dcd     0xe5c401c7
    bl      OS_IsThreadAvailable_0x020c9848
    dcd     0xe3500000
    dcd     0x1590002c
    dcd     0x03a00000
    dcd     0xe58403ac
    dcd     0xe8bd8010
}
