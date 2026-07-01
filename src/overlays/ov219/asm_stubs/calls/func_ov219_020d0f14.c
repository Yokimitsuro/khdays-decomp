extern void func_ov219_020d05f0(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c5af8(void);
extern void func_ov219_020d0f88(void);

asm void func_ov219_020d0f14(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    bl      func_ov219_020d05f0
    dcd     0xe3500000
    dcd     0xe3a02000
    dcd     0xaa000003
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0xe5940000
    dcd     0xe3a01003
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe5943008
    dcd     0xe59f1024
    dcd     0xe3a02004
    bl      func_ov107_020c5af8
    dcd     0xe3a00000
    dcd     0xe5840014
    dcd     0xe5c4003c
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0x00000136
    dcd     func_ov219_020d0f88
}
