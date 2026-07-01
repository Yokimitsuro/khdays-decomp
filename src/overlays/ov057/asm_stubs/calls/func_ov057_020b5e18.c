extern void func_ov022_020a2954(void);
extern void func_ov022_020ad114(void);
extern void func_ov022_020ad0c0(void);
extern void VEC_Subtract(void);
extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void FX_Atan2(void);
extern void data_ov057_020b74a0(void);
extern void func_ov057_020b6f94(void);
extern void func_ov057_020b7140(void);

asm void func_ov057_020b5e18(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe59f2124
    dcd     0xe3a03000
    dcd     0xe5922000
    dcd     0xe1a05000
    dcd     0xe282202c
    dcd     0xe1a04003
    dcd     0xe3510021
    dcd     0xe2822b0b
    dcd     0x0a000002
    dcd     0xe3510022
    dcd     0x0a000005
    dcd     0xea00003b
    dcd     0xe5952664
    dcd     0xe3a01031
    dcd     0xe59f40f0
    dcd     0xe12fff32
    dcd     0xea000036
    dcd     0xe5920228
    dcd     0xe59f40e4
    dcd     0xe3500002
    dcd     0x0a000006
    dcd     0xe3500003
    dcd     0x0a000007
    dcd     0xe3500004
    dcd     0x03a00002
    dcd     0x05820004
    dcd     0x03a01030
    dcd     0xea000005
    dcd     0xe5823004
    dcd     0xe3a0102f
    dcd     0xea000002
    dcd     0xe3a00001
    dcd     0xe5820004
    dcd     0xe3a01032
    dcd     0xe5952664
    dcd     0xe1a00005
    dcd     0xe12fff32
    dcd     0xe1a00005
    bl      func_ov022_020a2954
    dcd     0xe1a00005
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
    dcd     data_ov057_020b74a0
    dcd     func_ov057_020b6f94
    dcd     func_ov057_020b7140
}
