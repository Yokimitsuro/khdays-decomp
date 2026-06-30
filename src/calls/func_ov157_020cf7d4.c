extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov157_020cf820(void);

asm void func_ov157_020cf7d4(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01004
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe3a00000
    dcd     0xe584002c
    dcd     0xe5c40038
    dcd     0xe5d41039
    dcd     0xe59f2014
    dcd     0xe1a00005
    dcd     0xe3c11002
    dcd     0xe5c41039
    dcd     0xe1d512d0
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov157_020cf820
}
