extern void func_ov261_020d0348(void);
extern void func_0202f384(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void VEC_DotProduct(void);
extern void func_ov107_020c5af8(void);
extern void func_0203c634(void);
extern void data_02042258(void);
extern void func_ov261_020d0cd8(void);

asm void func_ov261_020d0c0c(void)
{
    dcd     0xe92d4070
    dcd     0xe24dd018
    dcd     0xe1a05000
    dcd     0xe8950011
    dcd     0xe590102c
    dcd     0xe3a0001e
    dcd     0xe0030091
    dcd     0xe59f2098
    dcd     0xe1a00fa3
    dcd     0xe0c61392
    dcd     0xe0836006
    dcd     0xe08061c6
    dcd     0xe584603c
    dcd     0xe8940005
    dcd     0xe59063a8
    dcd     0xe284001c
    dcd     0xe2861074
    bl      func_ov261_020d0348
    dcd     0xe59f2070
    dcd     0xe28d000c
    dcd     0xe284100c
    bl      func_0202f384
    dcd     0xe5941004
    dcd     0xe28d2000
    dcd     0xe2860074
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe28d000c
    dcd     0xe28d1000
    bl      VEC_DotProduct
    dcd     0xe3500c0f
    dcd     0xd28dd018
    dcd     0xd8bd8070
    mov r0, #0
    dcd     0xe5840040
    dcd     0xe59f1028
    dcd     0xe3a02004
    dcd     0xe8940009
    bl      func_ov107_020c5af8
    dcd     0xe1d512d0
    dcd     0xe59f2018
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd8070
    dcd     0x88888889
    dcd     data_02042258
    dcd     0x00000179
    dcd     func_ov261_020d0cd8
}
