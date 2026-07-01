extern void VEC_Subtract(void);
extern void data_02041dc8(void);
extern void data_02042264(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_0202ea48(void);
extern void func_0203c634(void);
extern void func_0203cd7c(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020cab14(void);
extern void func_ov179_020d3a0c(void);

asm void func_ov179_020d38e8(void) {

    dcd 0xe92d4078
    dcd 0xe24dd02c
    dcd 0xe1a06000
    dcd 0xe5965004
    dcd 0xe3a01000
    dcd 0xe5950000
    bl func_ov107_020cab14
    dcd 0xe1b04000
    dcd 0xe585000c
    dcd 0x1a000008
    dcd 0xe5950000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d612d0
    dcd 0xe1a00006
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd02c
    dcd 0xe8bd8078
    dcd 0xe5952008
    dcd 0xe59f30bc
    dcd 0xe28d0008
    dcd 0xe2841074
    bl func_0203cd7c
    dcd 0xe28d1008
    dcd 0xe2850074
    bl func_0202ea48
    dcd 0xe2850074
    dcd 0xe285c064
    dcd 0xe890000f
    dcd 0xe88c000f
    dcd 0xe5960000
    dcd 0xe5952048
    dcd 0xe590102c
    dcd 0xe59f0088
    dcd 0xe0821001
    dcd 0xe1510000
    dcd 0xb28dd02c
    dcd 0xe5851048
    dcd 0xb8bd8078
    dcd 0xe5951008
    dcd 0xe2840074
    dcd 0xe2852038
    bl VEC_Subtract
    dcd 0xe2850038
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe2851038
    dcd 0xe1a02001
    dcd 0xe3a00c03
    bl func_01ffa724
    dcd 0xe3a00001
    dcd 0xe58d0004
    dcd 0xe59f0040
    dcd 0xe24d3008
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xe5950000
    dcd 0xe893000c
    dcd 0xe3a01008
    bl func_ov107_020c0b90
    dcd 0xe3a00000
    dcd 0xe5c50086
    dcd 0xe1d612d0
    dcd 0xe59f2018
    dcd 0xe1a00006
    bl func_0203c634
    dcd 0xe28dd02c
    dcd 0xe8bd8078
    dcd data_02042264
    dcd 0x0000219a
    dcd data_02041dc8
    dcd func_ov179_020d3a0c
}
