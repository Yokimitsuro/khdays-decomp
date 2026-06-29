extern char data_ov061_020b7000[];
extern void FX_Atan2(void);
extern void func_01fff774(void);
extern void func_0202accc(void);

asm void func_ov061_020b6ce8(void)
{
    dcd     0xe92d41f0
    dcd     0xe59f212c
    dcd     0xe1a08000
    dcd     0xe5922000
    dcd     0xe3a05000
    dcd     0xe282002c
    dcd     0xe2804b0b
    dcd     0xe1a07001
    dcd     0xe1a02005
    dcd     0xe1a01004
    dcd     0xe5910014
    dcd     0xe3500000
    dcd     0x1a000003
    dcd     0xe2841014
    dcd     0xe3a00f43
    dcd     0xe0251092
    dcd     0xea000003
    dcd     0xe2822001
    dcd     0xe3520007
    dcd     0xe2811f43
    dcd     0xbafffff4
    dcd     0xe3550000
    dcd     0x08bd81f0
    dcd     0xe594300c
    dcd     0xe59f10d4
    dcd     0xe3a02003
    dcd     0xe0c60391
    dcd     0xe0866fa3
    dcd     0xe0c10692
    dcd     0xe0436000
    dcd     0xe1a01806
    dcd     0xe3a0c001
    dcd     0xe2850004
    dcd     0xe28520e4
    dcd     0xe1a03841
    dcd     0xe3a01000
    dcd     0xe585c000
    bl      func_0202accc
    dcd     0xe1a01806
    dcd     0xe2850004
    dcd     0xe28520e4
    dcd     0xe1a03841
    dcd     0xe3a01002
    bl      func_0202accc
    dcd     0xe1a00806
    dcd     0xe1a03840
    dcd     0xe2850004
    dcd     0xe3a01001
    dcd     0xe28520e4
    bl      func_0202accc
    dcd     0xe2850004
    dcd     0xe3a01000
    dcd     0xe1a02001
    bl      func_01fff774
    dcd     0xe2850004
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe2850004
    dcd     0xe3a01001
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe28530a8
    dcd     0xe8980007
    dcd     0xe8830007
    dcd     0xe5970000
    dcd     0xe5971008
    dcd     0xe2600000
    dcd     0xe2611000
    bl      FX_Atan2
    dcd     0xe1c508b0
    dcd     0xe1d500b4
    dcd     0xe3800020
    dcd     0xe1c500b4
    dcd     0xe594000c
    dcd     0xe2800001
    dcd     0xe584000c
    dcd     0xe8bd81f0
    dcd     data_ov061_020b7000
    dcd     0x55555556
}
