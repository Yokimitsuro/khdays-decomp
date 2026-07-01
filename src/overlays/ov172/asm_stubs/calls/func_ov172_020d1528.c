extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov172_020d1598(void);

asm void func_ov172_020d1528(void)
{
    dcd     0xe92d4070
    dcd     0xe1a04000
    dcd     0xe5945004
    dcd     0xe3a01001
    dcd     0xe5950000
    dcd     0xe1a02001
    bl      func_ov107_020c9264
    dcd     0xe3a00002
    bl      func_02023eb4
    dcd     0xe3500000
    dcd     0x03e00000
    dcd     0x13a00001
    dcd     0xe5850060
    dcd     0xe5950000
    dcd     0xe5906224
    dcd     0xe5900228
    dcd     0xe0500006
    dcd     0x42600000
    dcd     0xe2800001
    bl      func_02023eb4
    dcd     0xe0860000
    dcd     0xe585005c
    dcd     0xe1d412d0
    dcd     0xe59f2008
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe8bd8070
    dcd     func_ov172_020d1598
}
