extern void FX_Atan2(void);
extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern char data_ov091_020bc240[];
extern void func_01ff8d18(void);
extern void func_01fff774(void);
extern void func_ov022_02095554(void);
extern void func_ov022_020ad0c0(void);
extern void func_ov022_020ad114(void);
extern void func_ov091_020bba74(void);
extern void func_ov091_020bbdcc(void);

asm void func_ov091_020badc4(void)
{
    dcd     0xe92d4018
    dcd     0xe24dd00c
    dcd     0xe59f2168
    dcd     0xe1a04000
    dcd     0xe5922000
    dcd     0xe3510021
    dcd     0xe28220a4
    dcd     0xe2822b0b
    dcd     0xe3a03000
    dcd     0x0a000002
    dcd     0xe3510022
    dcd     0x0a000039
    dcd     0xea00004d
    dcd     0xe2840fbe
    dcd     0xe2800a02
    dcd     0xe5823008
    bl      func_ov022_02095554
    dcd     0xe3500000
    dcd     0xe5942664
    dcd     0xe1a00004
    dcd     0x1a000009
    dcd     0xe3a0102f
    dcd     0xe12fff32
    dcd     0xe5940020
    dcd     0xe3a01000
    dcd     0xe2800004
    dcd     0xe3a02a0f
    bl      func_01fff774
    dcd     0xe3a00a0f
    dcd     0xe58407b0
    dcd     0xea000001
    dcd     0xe3a01032
    dcd     0xe12fff32
    dcd     0xe1a00004
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x0a00001e
    dcd     0xe1a00004
    bl      func_ov022_020ad0c0
    dcd     0xe284108c
    dcd     0xe28d2000
    dcd     0xe2811b01
    bl      VEC_Subtract
    dcd     0xe3a01000
    dcd     0xe28d0000
    dcd     0xe58d1004
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
    dcd     0xe59f3064
    dcd     0xea000014
    dcd     0xe5823004
    dcd     0xe5c2300c
    dcd     0xe5921000
    dcd     0xe3510000
    dcd     0x1a000009
    dcd     0xe5920008
    dcd     0xe3a01030
    dcd     0xe3500002
    dcd     0x03a00006
    dcd     0x13a00003
    dcd     0xe5c2000d
    dcd     0xe5942664
    dcd     0xe1a00004
    dcd     0xe12fff32
    dcd     0xea000004
    dcd     0xe3a01001
    dcd     0xe5c2100d
    dcd     0xe5942664
    dcd     0xe3a01031
    dcd     0xe12fff32
    dcd     0xe59f3010
    dcd     0xe1a00003
    dcd     0xe28dd00c
    dcd     0xe8bd8018
    dcd     data_ov091_020bc240
    dcd     func_ov091_020bba74
    dcd     func_ov091_020bbdcc
}
