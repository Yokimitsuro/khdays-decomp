extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov194_020ce2c8(void);

asm void func_ov194_020ce27c(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe8940005
    dcd     0xe5921030
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe5820030
    dcd     0xe3500a03
    dcd     0xb8bd8010
    dcd     0xe5920000
    dcd     0xe3a01008
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe1d412d0
    dcd     0xe59f2008
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe8bd8010
    dcd     func_ov194_020ce2c8
}
