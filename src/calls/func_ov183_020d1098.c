extern void func_ov107_020cab14(void);
extern void func_0203c634(void);
extern void FX_Sqrt(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_0202f384(void);
extern void func_01ffa724(void);
extern void func_ov107_020c9264(void);
extern void data_02042258(void);
extern void func_ov183_020d11b8(void);

asm void func_ov183_020d1098(void)
{
    dcd     0xe92d40f8
    dcd     0xe24dd010
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe28d1000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe1b07000
    dcd     0xe5840010
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd80f8
    dcd     0xe5946000
    dcd     0xe59d0000
    bl      FX_Sqrt
    dcd     0xe5973080
    dcd     0xe5962080
    dcd     0xe3a0101e
    dcd     0xe0832002
    dcd     0xe0400002
    dcd     0xe58d0000
    dcd     0xe5950000
    dcd     0xe59f3098
    dcd     0xe590002c
    dcd     0xe28d2004
    dcd     0xe0010190
    dcd     0xe1a00fa1
    dcd     0xe0cc1193
    dcd     0xe080c14c
    dcd     0xe584c020
    dcd     0xe5940010
    dcd     0xe5941008
    dcd     0xe2800074
    bl      VEC_Subtract
    dcd     0xe59d0004
    dcd     0xe59d100c
    bl      func_020050b4
    dcd     0xe5840018
    dcd     0xe5940000
    dcd     0xe59f2058
    dcd     0xe28010a0
    dcd     0xe2840054
    bl      func_0202f384
    dcd     0xe2841054
    dcd     0xe3a00c01
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe594000c
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x128dd010
    dcd     0x18bd80f8
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe1d512d0
    dcd     0xe59f2014
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd80f8
    dcd     0x66666667
    dcd     data_02042258
    dcd     func_ov183_020d11b8
}
