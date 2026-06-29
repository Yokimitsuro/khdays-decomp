extern char data_0203d210[];
extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Add(void);
extern void func_0202aa9c(void);
extern void func_ov022_020ad44c(void);

asm void func_ov068_020b6600(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd03c
    dcd     0xe1a03000
    dcd     0xe5d30694
    dcd     0xe1a05001
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x028dd03c
    dcd     0x08bd8030
    dcd     0xe1d500d0
    dcd     0xe3500005
    dcd     0x908ff100
    dcd     0xea000035
    dcd     0xea000034
    dcd     0xea000033
    dcd     0xea000002
    dcd     0xea000001
    dcd     0xea000000
    dcd     0xeaffffff
    dcd     0xe5931020
    dcd     0xe28d0030
    dcd     0xe1d128b0
    dcd     0xe1a01003
    dcd     0xe2422902
    dcd     0xe1a02802
    dcd     0xe1a04822
    bl      func_ov022_020ad44c
    dcd     0xe5950118
    dcd     0xe3500000
    dcd     0x1a000019
    dcd     0xe1a00244
    dcd     0xe1a01080
    dcd     0xe2810001
    dcd     0xe59f2088
    dcd     0xe1a01081
    dcd     0xe19210f1
    dcd     0xe1a00080
    dcd     0xe19220f0
    dcd     0xe59fc078
    dcd     0xe3e0e06e
    dcd     0xe3a03029
    dcd     0xe28d0000
    dcd     0xe2611000
    dcd     0xe2622000
    dcd     0xe58de024
    dcd     0xe58dc028
    dcd     0xe58d302c
    bl      MTX_RotY33_
    dcd     0xe28d0024
    dcd     0xe28d1000
    dcd     0xe1a02000
    bl      MTX_MultVec33
    dcd     0xe28d0030
    dcd     0xe28d1024
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe2840902
    dcd     0xe1c508b0
    dcd     0xe1d510b4
    dcd     0xe28d0030
    dcd     0xe28530a8
    dcd     0xe3811020
    dcd     0xe1c510b4
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe2850004
    bl      func_0202aa9c
    dcd     0xe28dd03c
    dcd     0xe8bd8030
    dcd     data_0203d210
    dcd     0x00001768
}
