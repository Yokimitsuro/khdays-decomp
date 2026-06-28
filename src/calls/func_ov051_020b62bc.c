extern void func_02030788(void);
extern void func_02023c40(void);
extern void func_ov022_020ad114(void);
extern void func_ov022_020ad0c0(void);
extern void VEC_Subtract(void);
extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void FX_Atan2(void);
extern void func_ov022_020a35f4(void);

asm void func_ov051_020b62bc(void)
{
    dcd     0xe92d4018
    dcd     0xe24dd00c
    dcd     0xe1a04000
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe2840064
    dcd     0xe5942464
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe5842464
    dcd     0xe3811000
    dcd     0xe5801404
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe284006c
    dcd     0xe594246c
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe584246c
    dcd     0xe3811000
    dcd     0xe5801404
    bl      func_02023c40
    dcd     0xe3500001
    dcd     0x03a01d09
    dcd     0x13a01d06
    dcd     0xe1a00004
    dcd     0xe58414b0
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x0a00001c
    dcd     0xe1a00004
    bl      func_ov022_020ad0c0
    dcd     0xe284108c
    dcd     0xe28d2000
    dcd     0xe2811b01
    bl      VEC_Subtract
    dcd     0xe28d0000
    bl      VEC_Mag
    dcd     0xe3500000
    dcd     0x0a000002
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59d0000
    dcd     0xe59d1008
    dcd     0xe2600000
    dcd     0xe2611000
    bl      FX_Atan2
    dcd     0xe5942020
    dcd     0xe1a00800
    dcd     0xe5921000
    dcd     0xe1a00820
    dcd     0xe3110020
    dcd     0x1a000004
    dcd     0xe2800902
    dcd     0xe1c208b0
    dcd     0xe1d200b4
    dcd     0xe3800020
    dcd     0xe1c200b4
    dcd     0xe1a00004
    dcd     0xe3a01021
    bl      func_ov022_020a35f4
    dcd     0xe28dd00c
    dcd     0xe8bd8018
}
