extern void FX_Atan2(void);
extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern char data_ov103_020bc120[];
extern void func_01ff8d18(void);
extern void func_01fff774(void);
extern void func_02023c40(void);
extern void func_ov022_020a2954(void);
extern void func_ov022_020ad0c0(void);
extern void func_ov022_020ad114(void);
extern void func_ov103_020bb948(void);
extern void func_ov103_020bbb2c(void);
extern void func_ov103_020bbde8(void);

asm void func_ov103_020babac(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd00c
    dcd     0xe59f2220
    dcd     0xe2413021
    dcd     0xe5922000
    dcd     0xe3a0c000
    dcd     0xe282202c
    dcd     0xe1a06000
    dcd     0xe1a0500c
    dcd     0xe3530003
    dcd     0xe2824b0b
    dcd     0x908ff103
    dcd     0xea00007b
    dcd     0xea000002
    dcd     0xea000006
    dcd     0xea00006f
    dcd     0xea00006e
    dcd     0xe5962664
    dcd     0xe3a0102f
    dcd     0xe59f51e0
    dcd     0xe12fff32
    dcd     0xea000072
    dcd     0xe5940358
    dcd     0xe59f51d4
    dcd     0xe3500002
    dcd     0x0a000004
    dcd     0xe3500003
    dcd     0x0a000006
    dcd     0xe3500004
    dcd     0x0a000009
    dcd     0xea00000c
    dcd     0xe584c360
    dcd     0xe3a00a06
    dcd     0xe584036c
    dcd     0xea000008
    mov r0, #1
    dcd     0xe5840360
    dcd     0xe3a00a15
    dcd     0xe584036c
    dcd     0xea000003
    dcd     0xe3a00002
    dcd     0xe5840360
    dcd     0xe3a00a27
    dcd     0xe584036c
    dcd     0xe1a00006
    bl      func_ov022_020a2954
    dcd     0xe5940358
    dcd     0xe5962664
    dcd     0xe3500004
    dcd     0xe1a00006
    dcd     0x1a000002
    dcd     0xe3a01033
    dcd     0xe12fff32
    dcd     0xea000001
    dcd     0xe3a01032
    dcd     0xe12fff32
    dcd     0xe5960020
    dcd     0xe3a01000
    dcd     0xe2800004
    dcd     0xe3a02a09
    bl      func_01fff774
    dcd     0xe3a00a09
    dcd     0xe58607b0
    dcd     0xe5961000
    dcd     0xe5960004
    dcd     0xe3811202
    dcd     0xe5861000
    dcd     0xe3800000
    dcd     0xe5860004
    mov r0, #0
    dcd     0xe5840364
    bl      func_02023c40
    dcd     0xe3500001
    dcd     0x03a00b03
    dcd     0x13a00b02
    dcd     0xe5840368
    dcd     0xe5940358
    dcd     0xe3500004
    dcd     0x1a000009
    dcd     0xe5942368
    dcd     0xe59f00f4
    dcd     0xe1a01fc2
    dcd     0xe083c092
    dcd     0xe29c2b02
    dcd     0xe0233091
    dcd     0xe2a30000
    dcd     0xe1a01622
    dcd     0xe1811a00
    dcd     0xe5841368
    bl      func_02023c40
    dcd     0xe3500001
    dcd     0x03a01d09
    dcd     0x13a01d06
    dcd     0xe1a00006
    dcd     0xe58614b0
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x0a000026
    dcd     0xe1a00006
    bl      func_ov022_020ad0c0
    dcd     0xe286108c
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
    dcd     0xe5962020
    dcd     0xe1a00800
    dcd     0xe5921000
    dcd     0xe1a00820
    dcd     0xe3110020
    dcd     0x1a00000e
    dcd     0xe2800902
    dcd     0xe1c208b0
    dcd     0xe1d200b4
    dcd     0xe3800020
    dcd     0xe1c200b4
    dcd     0xea000008
    dcd     0xe3510024
    dcd     0xe59f5034
    dcd     0xe5962664
    dcd     0x1a000002
    dcd     0xe3a01030
    dcd     0xe12fff32
    dcd     0xea000001
    dcd     0xe3a01031
    dcd     0xe12fff32
    dcd     0xe1a00005
    dcd     0xe28dd00c
    dcd     0xe8bd8078
    dcd     data_ov103_020bc120
    dcd     func_ov103_020bb948
    dcd     func_ov103_020bbb2c
    dcd     0x00001333
    dcd     func_ov103_020bbde8
}
