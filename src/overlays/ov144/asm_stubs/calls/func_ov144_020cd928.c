extern void func_ov144_020cca50(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov107_020c5af8(void);
extern void func_ov144_020cd9ac(void);

asm void func_ov144_020cd928(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe1a00004
    bl      func_ov144_020cca50
    dcd     0xe5940000
    dcd     0xe2801c01
    dcd     0xe1d11cd6
    dcd     0xe3510007
    dcd     0x1a000007
    dcd     0xe3a01000
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe1d512d0
    dcd     0xe59f203c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0xe3a01008
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe5943008
    dcd     0xe59f101c
    dcd     0xe3a02004
    bl      func_ov107_020c5af8
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov144_020cd9ac
    dcd     0x00000123
}
