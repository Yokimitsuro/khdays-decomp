extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov243_020d43c4(void);

asm void func_ov243_020d4370(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe8940005
    dcd     0xe592102c
    dcd     0xe590002c
    dcd     0xe0410000
    dcd     0xe582002c
    dcd     0xe5920000
    dcd     0xe5901384
    dcd     0xe5d110ad
    dcd     0xe3510000
    dcd     0x18bd8010
    dcd     0xe3a01006
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe1d412d0
    dcd     0xe59f2008
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe8bd8010
    dcd     func_ov243_020d43c4
}
