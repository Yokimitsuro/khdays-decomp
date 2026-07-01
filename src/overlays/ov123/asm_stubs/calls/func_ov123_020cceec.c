extern void VEC_Subtract(void);
extern void data_02042258(void);
extern void func_01ff8d18(void);
extern void func_0202f384(void);
extern void func_0203c634(void);
extern void func_ov123_020cd224(void);
extern void func_ov123_020cd484(void);

asm void func_ov123_020cceec(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd00c
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov123_020cd224
    dcd     0xe5840024
    dcd     0xe3500000
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8078
    dcd     0xe5950000
    dcd     0xe5941028
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe5840028
    dcd     0xe594002c
    dcd     0xe3500000
    dcd     0x1a00001f
    dcd     0xe5941028
    dcd     0xe59f00ac
    dcd     0xe1510000
    dcd     0xba00001b
    dcd     0xe5940000
    dcd     0xe5943024
    dcd     0xe5901390
    dcd     0xe28d2000
    dcd     0xe2830074
    dcd     0xe2811014
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59d6004
    dcd     0xe3a00001
    dcd     0xe584002c
    dcd     0xe5941000
    dcd     0xe59f206c
    dcd     0xe28d0000
    dcd     0xe28110a0
    bl      func_0202f384
    dcd     0xe28d0000
    dcd     0xe58d6004
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe5941000
    dcd     0xe28d2000
    dcd     0xe5910394
    dcd     0xe5911390
    dcd     0xe2811014
    bl      func_ov123_020cd484
    dcd     0xe5940030
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x128dd00c
    dcd     0x18bd8078
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8078
    dcd     0x00000ccc
    dcd     data_02042258
}
