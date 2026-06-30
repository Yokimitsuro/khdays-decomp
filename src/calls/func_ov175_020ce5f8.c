extern void func_01ffa724(void);
extern void func_0202ed60(void);
extern void func_0203c9d0(void);
extern void data_02042258(void);
extern void data_02041dc8(void);

asm void func_ov175_020ce5f8(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd010
    dcd     0xe5904004
    dcd     0xe5940000
    dcd     0xe2800c01
    dcd     0xe1d00cd6
    dcd     0xe3500001
    dcd     0x1a00000c
    dcd     0xe2841014
    dcd     0xe2842008
    dcd     0xe3a00c06
    bl      func_01ffa724
    dcd     0xe59f1048
    dcd     0xe28d0000
    dcd     0xe2842014
    bl      func_0202ed60
    dcd     0xe5940000
    dcd     0xe28d1000
    dcd     0xe28000a0
    bl      func_0203c9d0
    dcd     0xea000003
    dcd     0xe59f0028
    dcd     0xe2843008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5941000
    dcd     0xe2840008
    dcd     0xe28130f0
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe28dd010
    dcd     0xe8bd8010
    dcd     data_02042258
    dcd     data_02041dc8
}
