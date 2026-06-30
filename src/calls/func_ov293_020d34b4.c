extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov293_020d34f8(void);

asm void func_ov293_020d34b4(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5941004
    dcd     0xe591004c
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x18bd8010
    dcd     0xe5910000
    dcd     0xe3a0100a
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe1d412d0
    dcd     0xe59f2008
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe8bd8010
    dcd     func_ov293_020d34f8
}
