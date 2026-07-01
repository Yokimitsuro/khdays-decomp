extern void func_ov002_020766e0(void);

asm void func_ov017_0207fdb4(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd010
    dcd     0xe1a04000
    dcd     0xe5d424da
    dcd     0xe3520000
    dcd     0x1a00000d
    dcd     0xe3a02001
    dcd     0xe5cd2000
    dcd     0xe5d1300c
    dcd     0xe28d1000
    dcd     0xe3a02010
    dcd     0xe5cd3004
    bl      func_ov002_020766e0
    dcd     0xe3500000
    dcd     0x0a000004
    mov r0, #1
    dcd     0xe5c404da
    dcd     0xe28dd010
    mov r0, #0
    dcd     0xe8bd8010
    dcd     0xe3a00008
    dcd     0xe28dd010
    dcd     0xe8bd8010
}
