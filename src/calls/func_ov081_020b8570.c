extern void FX_Atan2(void);
extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_ov022_02095554(void);
extern void func_ov022_020ad0c0(void);
extern void func_ov022_020ad114(void);
extern void func_ov081_020b87b4(void);

asm void func_ov081_020b8570(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd00c
    dcd     0xe1a05000
    dcd     0xe3510021
    dcd     0xe3a04000
    dcd     0x1a000033
    dcd     0xe2850fbe
    dcd     0xe285102c
    dcd     0xe2800a02
    dcd     0xe2816b0b
    dcd     0xe59f40c4
    bl      func_ov022_02095554
    dcd     0xe3500000
    dcd     0xe5952664
    dcd     0xe1a00005
    dcd     0x0a000002
    dcd     0xe3a01030
    dcd     0xe12fff32
    dcd     0xea000001
    dcd     0xe3a0102f
    dcd     0xe12fff32
    dcd     0xe3a01000
    dcd     0xe5861004
    dcd     0xe586100c
    dcd     0xe1a00005
    dcd     0xe5861010
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x0a00001c
    dcd     0xe1a00005
    bl      func_ov022_020ad0c0
    dcd     0xe285108c
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
    dcd     0xe5952020
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
    dcd     0xe28dd00c
    dcd     0xe8bd8078
    dcd     func_ov081_020b87b4
}
