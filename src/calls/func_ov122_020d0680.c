extern char data_02041dc8[];
extern char data_02042264[];
extern void func_0202f188(void);
extern void func_0203c9d0(void);
extern void func_0203d040(void);

asm void func_ov122_020d0680(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd010
    dcd     0xe5904004
    dcd     0xe3a03000
    dcd     0xe5940010
    dcd     0xe5941014
    dcd     0xe5942018
    bl      func_0203d040
    dcd     0xe59f1044
    dcd     0xe5840010
    dcd     0xe1a02000
    dcd     0xe28d0000
    bl      func_0202f188
    dcd     0xe5940000
    dcd     0xe28d1000
    dcd     0xe28000a0
    bl      func_0203c9d0
    dcd     0xe5940000
    dcd     0xe284c01c
    dcd     0xe28030f0
    dcd     0xe89c0007
    dcd     0xe8830007
    dcd     0xe59f0010
    dcd     0xe8900007
    dcd     0xe88c0007
    dcd     0xe28dd010
    dcd     0xe8bd8010
    dcd     data_02042264
    dcd     data_02041dc8
}
