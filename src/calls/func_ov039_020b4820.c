extern void func_ov022_020ad44c(void);
extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void data_ov039_020b5600(void);
extern void data_0203d210(void);

asm void func_ov039_020b4820(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd03c
    dcd     0xe59f1154
    dcd     0xe1a06000
    dcd     0xe5910000
    dcd     0xe3a01001
    dcd     0xe28000d4
    dcd     0xe2804b0b
    dcd     0xe5940014
    dcd     0xe3500001
    dcd     0x0a000004
    dcd     0xe3500002
    dcd     0x0a000007
    dcd     0xe3500003
    dcd     0x0a00000a
    dcd     0xea00000f
    dcd     0xe5841338
    dcd     0xe3a00000
    dcd     0xe5840318
    dcd     0xe3a05006
    dcd     0xea00000b
    dcd     0xe3a00000
    dcd     0xe5840338
    dcd     0xe5840318
    dcd     0xe3a05003
    dcd     0xea000006
    dcd     0xe3a00000
    dcd     0xe5840338
    dcd     0xe3a00a06
    dcd     0xe1a05001
    dcd     0xe5840318
    dcd     0xea000000
    dcd     0xe3a01000
    dcd     0xe3510000
    dcd     0x028dd03c
    dcd     0x08bd8078
    dcd     0xe28d0000
    dcd     0xe1a01006
    bl      func_ov022_020ad44c
    dcd     0xe28d0000
    dcd     0xe2843fc7
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5960020
    dcd     0xe59f20b0
    dcd     0xe1d018b0
    dcd     0xe28d000c
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
    dcd     0xe3a01000
    dcd     0xe28d0030
    dcd     0xe58d1030
    dcd     0xe58d1034
    dcd     0xe3a01a01
    dcd     0xe58d1038
    dcd     0xe28d100c
    dcd     0xe1a02000
    bl      MTX_MultVec33
    dcd     0xe28d0030
    bl      VEC_Mag
    dcd     0xe3500000
    dcd     0xe28d0030
    dcd     0x1a000003
    dcd     0xe2843fca
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xea000001
    dcd     0xe2841fca
    bl      func_01ff8d18
    dcd     0xe5845308
    dcd     0xe3a00000
    dcd     0xe584030c
    dcd     0xe1d616f6
    dcd     0xe3a00001
    dcd     0xe5c41334
    dcd     0xe5840310
    dcd     0xe28dd03c
    dcd     0xe8bd8078
    dcd     data_ov039_020b5600
    dcd     data_0203d210
}
