extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_0203cd7c(void);
extern void func_0202ea48(void);
extern void data_02042258(void);
extern void data_02041dc8(void);
extern void data_02042264(void);

asm void func_ov262_020d3f88(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd030
    dcd     0xe1a04000
    dcd     0xe1a00001
    dcd     0xe1a01002
    dcd     0xe28d2000
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe3500000
    dcd     0x1a000003
    dcd     0xe59f0060
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe59d1004
    dcd     0xe3510b02
    dcd     0xc3a01b02
    dcd     0xca000003
    dcd     0xe3a00b02
    dcd     0xe2600000
    dcd     0xe1510000
    dcd     0xb1a01000
    dcd     0xe28d0000
    dcd     0xe58d1004
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59f2024
    dcd     0xe59f3024
    dcd     0xe28d000c
    dcd     0xe28d1000
    bl      func_0203cd7c
    dcd     0xe28d100c
    dcd     0xe1a00004
    bl      func_0202ea48
    dcd     0xe28dd030
    dcd     0xe8bd8010
    dcd     data_02042258
    dcd     data_02041dc8
    dcd     data_02042264
}
