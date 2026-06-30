extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov269_020d2960(void);

asm void func_ov269_020d292c(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5940004
    dcd     0xe3a01001
    dcd     0xe5900000
    dcd     0xe1a02001
    bl      func_ov107_020c9264
    dcd     0xe1d412d0
    dcd     0xe59f2008
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe8bd8010
    dcd     func_ov269_020d2960
}
