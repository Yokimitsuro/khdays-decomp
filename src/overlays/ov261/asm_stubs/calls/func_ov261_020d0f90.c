extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_ov261_020d0348(void);
extern void func_0202f384(void);
extern void VEC_DotProduct(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);
extern void data_02041dc8(void);
extern void data_02042258(void);
extern void func_ov261_020d110c(void);

asm void func_ov261_020d0f90(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd024
    dcd     0xe1a06000
    dcd     0xe8960011
    dcd     0xe590102c
    dcd     0xe3a0001e
    dcd     0xe0030091
    dcd     0xe59f2144
    dcd     0xe594c000
    dcd     0xe0c51392
    dcd     0xe1a00fa3
    dcd     0xe0835005
    dcd     0xe0805245
    dcd     0xe59c23a0
    dcd     0xe3a00024
    dcd     0xe584503c
    dcd     0xe594106c
    dcd     0xe28d3018
    dcd     0xe0841001
    dcd     0xe5d11049
    dcd     0xe0202091
    dcd     0xe280002c
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5941004
    dcd     0xe28d200c
    dcd     0xe1a00003
    bl      VEC_Subtract
    dcd     0xe28d000c
    dcd     0xe3a02000
    dcd     0xe1a01000
    dcd     0xe58d2010
    bl      func_01ff8d18
    dcd     0xe1a05000
    dcd     0xe59f20dc
    dcd     0xe284001c
    dcd     0xe28d100c
    bl      func_ov261_020d0348
    dcd     0xe59f20d0
    dcd     0xe28d0000
    dcd     0xe284100c
    bl      func_0202f384
    dcd     0xe28d0000
    dcd     0xe28d100c
    bl      VEC_DotProduct
    dcd     0xe3500000
    dcd     0xb3a00000
    dcd     0xe1a01fc0
    dcd     0xe1a02481
    dcd     0xe3a01b02
    dcd     0xe1822ba0
    dcd     0xe0910480
    dcd     0xe2a21000
    dcd     0xe1a00620
    dcd     0xe1800a01
    dcd     0xe1550000
    dcd     0xb1a00005
    dcd     0xe28d1000
    dcd     0xe2842030
    bl      func_01ffa724
    dcd     0xe5940000
    dcd     0xe3550a01
    dcd     0xe590013c
    dcd     0xe59f1070
    dcd     0xe2602a02
    dcd     0xe0c30291
    dcd     0xe1a00fa2
    dcd     0xe594c034
    dcd     0xe0803243
    dcd     0xe08c0003
    dcd     0xa28dd024
    dcd     0xe5840034
    dcd     0xa8bd8078
    dcd     0xe594006c
    dcd     0xe0840000
    dcd     0xe5d00049
    dcd     0xe5c40048
    dcd     0xe594006c
    dcd     0xe2801001
    dcd     0xe584106c
    dcd     0xe5940070
    dcd     0xe1510000
    dcd     0xb28dd024
    dcd     0xb8bd8078
    dcd     0xe1d612d0
    dcd     0xe59f201c
    dcd     0xe1a00006
    bl      func_0203c634
    dcd     0xe28dd024
    dcd     0xe8bd8078
    dcd     0x88888889
    dcd     data_02041dc8
    dcd     data_02042258
    dcd     0x51eb851f
    dcd     func_ov261_020d110c
}
