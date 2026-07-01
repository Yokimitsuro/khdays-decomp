extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void func_ov022_020a1064(void);
extern void func_ov022_020a23a4(void);
extern void func_ov022_020a4490(void);

asm void func_ov044_020b4044(void)
{
    dcd     0xe92d4070
    dcd     0xe24dd050
    dcd     0xe1a0c001
    dcd     0xe5904db4
    dcd     0xe28c00a4
    dcd     0xe28d6034
    dcd     0xe8900007
    dcd     0xe8860007
    dcd     0xe8960007
    dcd     0xe28d5028
    dcd     0xe8850007
    dcd     0xe59d102c
    dcd     0xe3a00b03
    dcd     0xe2811b1e
    dcd     0xe58d102c
    dcd     0xe58d0044
    dcd     0xe1a06003
    dcd     0xe5dc315c
    dcd     0xe3a05000
    dcd     0xe59f10cc
    dcd     0xe28c2e16
    dcd     0xe1a00006
    dcd     0xe58d3040
    dcd     0xe58d2048
    dcd     0xe58d504c
    dcd     0xe58d500c
    dcd     0xe58d1008
    bl      VEC_Mag
    dcd     0xe3500000
    dcd     0x1a000003
    dcd     0xe28d3014
    dcd     0xe8960007
    dcd     0xe8830007
    dcd     0xea000002
    dcd     0xe28d1014
    dcd     0xe1a00006
    bl      func_01ff8d18
    dcd     0xe5dd0025
    dcd     0xe3a0e001
    dcd     0xe3a06000
    dcd     0xe3c00001
    dcd     0xe20000ff
    dcd     0xe3c0c002
    dcd     0xe28d2000
    dcd     0xe28d3004
    dcd     0xe1a00004
    dcd     0xe3a01d4b
    dcd     0xe58de020
    dcd     0xe5cdc025
    dcd     0xe5cd6010
    bl      func_ov022_020a23a4
    dcd     0xe28d1028
    dcd     0xe28d2000
    dcd     0xe1a00004
    bl      func_ov022_020a1064
    dcd     0xe3500000
    dcd     0x13a05001
    dcd     0x1a000003
    dcd     0xe2840a02
    dcd     0xe5d006c4
    dcd     0xe3500004
    dcd     0x03a05001
    dcd     0xe3550000
    dcd     0x028dd050
    dcd     0x08bd8070
    dcd     0xe2840c07
    dcd     0xe1d01afa
    dcd     0xe1a00004
    dcd     0xe3a02001
    bl      func_ov022_020a4490
    dcd     0xe28dd050
    dcd     0xe8bd8070
    dcd     0x00000625
}
