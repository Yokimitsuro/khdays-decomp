extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Add(void);
extern void VEC_Mag(void);
extern char data_0203d210[];
extern char data_ov091_020bc10c[];
extern char data_ov091_020bc240[];
extern void func_01ff8d18(void);
extern void func_0203084c(void);
extern void func_ov022_02091324(void);
extern void func_ov022_020ad114(void);

asm void func_ov091_020bb2e4(void)
{
    dcd     0xe92d4070
    dcd     0xe24dd068
    dcd     0xe59f118c
    dcd     0xe59f218c
    dcd     0xe5911000
    dcd     0xe28d6030
    dcd     0xe2813f72
    dcd     0xe1a05000
    dcd     0xe8920007
    dcd     0xe8860007
    dcd     0xe2833b0b
    dcd     0xe28d4024
    dcd     0xe8930007
    dcd     0xe8840007
    dcd     0xe5950020
    dcd     0xe59f2160
    dcd     0xe1d018b0
    dcd     0xe28d0000
    dcd     0xe2411902
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe1a01241
    dcd     0xe1a03081
    dcd     0xe2831001
    dcd     0xe1a03083
    dcd     0xe1a01081
    dcd     0xe19230f3
    dcd     0xe19220f1
    dcd     0xe2631000
    dcd     0xe2622000
    bl      MTX_RotY33_
    dcd     0xe1a00004
    dcd     0xe28d1000
    dcd     0xe28d203c
    bl      MTX_MultVec33
    dcd     0xe28d003c
    dcd     0xe285108c
    dcd     0xe2811b01
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe59f4100
    dcd     0xe1a00005
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x13a04b06
    bl      func_0203084c
    dcd     0xe2400b02
    dcd     0xe0c01094
    dcd     0xe2911b02
    dcd     0xe2a00000
    dcd     0xe1a01621
    dcd     0xe59d2030
    dcd     0xe1811a00
    dcd     0xe0820001
    dcd     0xe58d0030
    bl      func_0203084c
    dcd     0xe2400b02
    dcd     0xe0c01094
    dcd     0xe2911b02
    dcd     0xe2a00000
    dcd     0xe1a01621
    dcd     0xe1811a00
    dcd     0xe59d2034
    dcd     0xe28d0030
    dcd     0xe0821001
    dcd     0xe58d1034
    bl      VEC_Mag
    dcd     0xe3500000
    dcd     0x0a000002
    dcd     0xe28d0030
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe28d0030
    dcd     0xe28d1000
    dcd     0xe1a02000
    bl      MTX_MultVec33
    dcd     0xe3a04000
    dcd     0xe59d6030
    dcd     0xe59de034
    dcd     0xe59dc038
    dcd     0xe3a03007
    dcd     0xe3a02b06
    dcd     0xe28d103c
    dcd     0xe1a00005
    dcd     0xe1cd64b8
    dcd     0xe1cde4ba
    dcd     0xe1cdc4bc
    dcd     0xe58d4050
    dcd     0xe58d4058
    dcd     0xe58d405c
    dcd     0xe58d3054
    dcd     0xe58d4060
    dcd     0xe58d4064
    dcd     0xe1cd24be
    bl      func_ov022_02091324
    dcd     0xe5951000
    dcd     0xe1a00004
    dcd     0xe3110801
    dcd     0x03a01003
    dcd     0x05c5147a
    dcd     0x05c5047b
    dcd     0xe28dd068
    dcd     0xe8bd8070
    dcd     data_ov091_020bc240
    dcd     data_ov091_020bc10c
    dcd     data_0203d210
    dcd     0x00000266
}
