extern void func_ov107_020cab14(void);
extern void func_0203c634(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void VEC_DotProduct(void);
extern void func_ov107_020c9f48(void);
extern void func_01ffa724(void);
extern void data_0203d210(void);

asm void func_ov195_020d11b8(void)
{
    dcd     0xe92d4070
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
    dcd     0xe8bd8070
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
    dcd     0xe594200c
    dcd     0xe59f00fc
    dcd     0xe59f10fc
    dcd     0xe083c092
    dcd     0xe0233192
    dcd     0xe1a02fc2
    dcd     0xe0233092
    dcd     0xe29c0000
    dcd     0xe2a30b02
    dcd     0xe1a00200
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a03080
    dcd     0xe3a01000
    dcd     0xe2830001
    dcd     0xe58d1004
    dcd     0xe59f20c8
    dcd     0xe1a01083
    dcd     0xe19230f1
    dcd     0xe1a00080
    dcd     0xe19220f0
    dcd     0xe28d0000
    dcd     0xe28d100c
    dcd     0xe58d3000
    dcd     0xe58d2008
    bl      VEC_DotProduct
    dcd     0xe1b06000
    dcd     0xe5940000
    dcd     0x42666000
    dcd     0xe3560000
    dcd     0xe59003d0
    dcd     0xb3a06000
    dcd     0xe3a01000
    bl      func_ov107_020c9f48
    dcd     0xe0c12690
    dcd     0xe2920b02
    dcd     0xe2a12000
    dcd     0xe1a00620
    dcd     0xe1800a02
    dcd     0xe28d1000
    dcd     0xe2842018
    bl      func_01ffa724
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x128dd018
    dcd     0x18bd8070
    dcd     0xe5940044
    dcd     0xe3a02000
    dcd     0xe3500000
    dcd     0xe5940000
    dcd     0xda000006
    dcd     0xe3a01007
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd8070
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd8070
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
}
