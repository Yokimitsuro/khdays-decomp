extern void func_0203c634(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c9264(void);
extern void func_ov284_020ccb30(void);

asm void func_ov284_020ccad8(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01002
    dcd     0xe5940000
    dcd     0xe3a02000
    dcd     0xe2800c01
    dcd     0xe1d03abe
    dcd     0xe3833001
    dcd     0xe1c03abe
    dcd     0xe5940000
    bl      func_ov107_020c9264
    dcd     0xe3a01f5b
    dcd     0xe3a02007
    dcd     0xe8940009
    bl      func_ov107_020c5af8
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov284_020ccb30
}
