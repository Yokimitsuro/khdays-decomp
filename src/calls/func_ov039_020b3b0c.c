extern void func_ov022_02095554(void);
extern void func_ov022_020ad114(void);
extern void func_ov022_020ad0c0(void);
extern void VEC_Subtract(void);
extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void FX_Atan2(void);
extern void func_0202af1c(void);
extern void func_ov039_020b4820(void);
extern void data_ov039_020b5600(void);
extern void func_ov039_020b4b20(void);
extern void func_ov039_020b4f0c(void);
extern void func_ov039_020b51b4(void);

asm void func_ov039_020b3b0c(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe59f217c
    dcd     0xe3a04000
    dcd     0xe5922000
    dcd     0xe1a05000
    dcd     0xe28220d4
    dcd     0xe3510021
    dcd     0xe2822b0b
    dcd     0x0a000004
    dcd     0xe3510022
    dcd     0x0a000033
    dcd     0xe3510023
    dcd     0x0a00004b
    dcd     0xea000050
    dcd     0xe2850fbe
    dcd     0xe5824008
    dcd     0xe5824014
    dcd     0xe2800a02
    dcd     0xe59f413c
    bl      func_ov022_02095554
    dcd     0xe3500000
    dcd     0xe5952664
    dcd     0xe1a00005
    dcd     0x1a000002
    dcd     0xe3a0102f
    dcd     0xe12fff32
    dcd     0xea000001
    dcd     0xe3a01032
    dcd     0xe12fff32
    dcd     0xe1a00005
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x0a00003d
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
    dcd     0x1a000025
    dcd     0xe2800902
    dcd     0xe1c208b0
    dcd     0xe1d200b4
    dcd     0xe3800020
    dcd     0xe1c200b4
    dcd     0xea00001f
    dcd     0xe5824004
    dcd     0xe3a01001
    dcd     0xe582100c
    dcd     0xe5921000
    dcd     0xe59f407c
    dcd     0xe3510000
    dcd     0xe5952664
    dcd     0x0a000002
    dcd     0xe3a01031
    dcd     0xe12fff32
    dcd     0xea000001
    dcd     0xe3a01030
    dcd     0xe12fff32
    dcd     0xe5951000
    dcd     0xe5950004
    dcd     0xe3811000
    dcd     0xe5851000
    dcd     0xe3800802
    dcd     0xe5850004
    dcd     0xe5951020
    dcd     0xe5910000
    dcd     0xe3100020
    dcd     0x1a000008
    dcd     0xe2810004
    bl      func_0202af1c
    dcd     0xea000005
    dcd     0xe59f4028
    bl      func_ov039_020b4820
    dcd     0xe5952664
    dcd     0xe1a00005
    dcd     0xe3a01033
    dcd     0xe12fff32
    dcd     0xe1a00004
    dcd     0xe28dd00c
    dcd     0xe8bd8030
    dcd     data_ov039_020b5600
    dcd     func_ov039_020b4b20
    dcd     func_ov039_020b4f0c
    dcd     func_ov039_020b51b4
}
