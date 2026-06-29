extern void FX_Sqrt(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);

asm void func_ov284_020ccbfc(void)
{
    dcd     0xe92d40f8
    dcd     0xe24dd010
    dcd     0xe1a04000
    dcd     0xe5945004
    dcd     0xe28d1000
    dcd     0xe5950000
    bl      func_ov107_020cab14
    dcd     0xe585000c
    dcd     0xe3500000
    dcd     0x0a000007
    dcd     0xe5951004
    dcd     0xe28d2004
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe59d0004
    dcd     0xe59d100c
    bl      func_020050b4
    dcd     0xe5850014
    dcd     0xe595600c
    dcd     0xe59d0000
    dcd     0xe5957000
    bl      FX_Sqrt
    dcd     0xe5962080
    dcd     0xe5971080
    dcd     0xe0400002
    dcd     0xe0400001
    dcd     0xe58d0000
    dcd     0xe5950020
    dcd     0xe3500000
    dcd     0xc28dd010
    dcd     0xc8bd80f8
    dcd     0xe5950000
    dcd     0xe3a01007
    dcd     0xe5c011c7
    dcd     0xe1d412d0
    dcd     0xe1a00004
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd80f8
}
