extern void FX_Atan2(void);
extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern char data_ov056_020b7620[];
extern void func_01ff8d18(void);
extern void func_01fff774(void);
extern void func_ov022_020a2954(void);
extern void func_ov022_020ad0c0(void);
extern void func_ov022_020ad114(void);
extern void func_ov056_020b6508(void);
extern void func_ov056_020b6904(void);

asm void func_ov056_020b5ff8(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe59f2120
    dcd     0xe1a05000
    dcd     0xe5922000
    dcd     0xe3510021
    dcd     0xe282202c
    dcd     0xe2822b0b
    dcd     0xe3a04000
    dcd     0x0a000002
    dcd     0xe3510022
    dcd     0x0a000006
    dcd     0xea00003b
    dcd     0xe5824110
    dcd     0xe5952664
    dcd     0xe3a0102f
    dcd     0xe12fff32
    dcd     0xe59f40e8
    dcd     0xea000035
    dcd     0xe59f40e4
    bl      func_ov022_020a2954
    dcd     0xe5952664
    dcd     0xe1a00005
    dcd     0xe3a01030
    dcd     0xe12fff32
    dcd     0xe5950020
    dcd     0xe3a01000
    dcd     0xe2800004
    dcd     0xe3a02a27
    bl      func_01fff774
    dcd     0xe3a00a27
    dcd     0xe58507b0
    dcd     0xe5951000
    dcd     0xe5950004
    dcd     0xe3811202
    dcd     0xe5851000
    dcd     0xe3801000
    dcd     0xe1a00005
    dcd     0xe5851004
    dcd     0xe3a01b06
    dcd     0xe1c516b4
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
    dcd     0xe8bd8030
    dcd     data_ov056_020b7620
    dcd     func_ov056_020b6508
    dcd     func_ov056_020b6904
}
