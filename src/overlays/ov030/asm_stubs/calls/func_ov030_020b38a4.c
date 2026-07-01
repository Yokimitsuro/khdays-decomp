extern void VEC_Add(void);
extern void func_0202af1c(void);
extern void func_02030788(void);
extern void func_ov022_0209fe20(void);

asm void func_ov030_020b38a4(void)
{
    dcd     0xe92d4010
    dcd     0xe24dd018
    dcd     0xe1a04000
    dcd     0xe5942024
    dcd     0xe28d100c
    dcd     0xe3c22080
    dcd     0xe5842024
    bl      func_ov022_0209fe20
    dcd     0xe59d1010
    dcd     0xe28d000c
    dcd     0xe5841058
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    mov r0, #0
    dcd     0xe2842098
    dcd     0xe58d0004
    dcd     0xe2820b01
    dcd     0xe1a01003
    dcd     0xe2822b01
    bl      VEC_Add
    dcd     0xe5941668
    dcd     0xe1a00004
    dcd     0xe12fff31
    dcd     0xe5d41694
    dcd     0xe20000ff
    dcd     0xe1a00f80
    dcd     0xe3c11002
    dcd     0xe1811f20
    dcd     0xe20100ff
    dcd     0xe1a00f00
    dcd     0xe5c41694
    dcd     0xe1b00fa0
    dcd     0x0a000015
    dcd     0xe5941000
    dcd     0xe5940004
    dcd     0xe3811000
    dcd     0xe5841000
    dcd     0xe3800802
    dcd     0xe5840004
    dcd     0xe5941020
    dcd     0xe5910000
    dcd     0xe3100020
    dcd     0x1a000001
    dcd     0xe2810004
    bl      func_0202af1c
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe2840064
    dcd     0xe5942464
    dcd     0xe5901404
    dcd     0xe3822002
    dcd     0xe5842464
    dcd     0xe3811000
    dcd     0xe5801404
    mov r0, #0
    dcd     0xe28dd018
    dcd     0xe8bd8010
}
