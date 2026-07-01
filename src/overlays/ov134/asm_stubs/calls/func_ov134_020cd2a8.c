extern void VEC_DotProduct(void);
extern void VEC_Subtract(void);
extern char data_0203d210[];
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9f48(void);
extern void func_ov107_020cab14(void);

asm void func_ov134_020cd2a8(void)
{
    dcd     0xe92d41f0
    dcd     0xe24dd018
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe5840008
    dcd     0xe3500000
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd81f0
    dcd     0xe5941000
    dcd     0xe28d200c
    dcd     0xe2800e19
    dcd     0xe28110b0
    bl      VEC_Subtract
    dcd     0xe28d000c
    dcd     0xe3a02000
    dcd     0xe1a01000
    dcd     0xe58d2010
    bl      func_01ff8d18
    dcd     0xe59d000c
    dcd     0xe59d1014
    bl      func_020050b4
    dcd     0xe5840010
    dcd     0xe594600c
    dcd     0xe59f20dc
    dcd     0xe59f30dc
    dcd     0xe0878296
    dcd     0xe0277396
    dcd     0xe1a0efc6
    dcd     0xe027729e
    dcd     0xe2982000
    dcd     0xe2a72b02
    dcd     0xe1a02202
    dcd     0xe1a02822
    dcd     0xe1a02242
    dcd     0xe1a06082
    dcd     0xe3a00000
    dcd     0xe58d0004
    dcd     0xe59fc0ac
    dcd     0xe1a02086
    dcd     0xe19c30f2
    dcd     0xe2862001
    dcd     0xe1a02082
    dcd     0xe19c20f2
    dcd     0xe28d0000
    dcd     0xe28d100c
    dcd     0xe58d3000
    dcd     0xe58d2008
    bl      VEC_DotProduct
    dcd     0xe5940000
    dcd     0xe3a01000
    dcd     0xe59003a0
    bl      func_ov107_020c9f48
    dcd     0xe28d1000
    dcd     0xe2842018
    bl      func_01ffa724
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x128dd018
    dcd     0x18bd81f0
    dcd     0xe5d40042
    dcd     0xe3a02000
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0xe5940000
    dcd     0x0a000006
    dcd     0xe3a01007
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd81f0
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd81f0
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
}
