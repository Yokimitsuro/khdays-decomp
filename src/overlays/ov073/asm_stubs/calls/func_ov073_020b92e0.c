extern void VEC_Add(void);
extern void func_02030788(void);
extern void func_ov022_0209fe20(void);
extern void func_ov022_020a35f4(void);

asm void func_ov073_020b92e0(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd018
    dcd     0xe1a05000
    dcd     0xe3a04000
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe2850064
    dcd     0xe5952464
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe5852464
    dcd     0xe3811000
    dcd     0xe5801404
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x1a000006
    dcd     0xe285006c
    dcd     0xe595246c
    dcd     0xe5901404
    dcd     0xe3822801
    dcd     0xe585246c
    dcd     0xe3811000
    dcd     0xe5801404
    dcd     0xe28d100c
    dcd     0xe1a00005
    bl      func_ov022_0209fe20
    dcd     0xe5950024
    dcd     0xe3100004
    dcd     0x1a000007
    dcd     0xe5951000
    dcd     0xe5950004
    dcd     0xe3811000
    dcd     0xe5851000
    dcd     0xe3800901
    dcd     0xe5850004
    mov r0, #0
    dcd     0xe5850058
    dcd     0xe28d000c
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    mov r0, #0
    dcd     0xe2852098
    dcd     0xe58d0004
    dcd     0xe2820b01
    dcd     0xe1a01003
    dcd     0xe2822b01
    bl      VEC_Add
    dcd     0xe5951668
    dcd     0xe1a00005
    dcd     0xe12fff31
    dcd     0xe5d51694
    dcd     0xe20000ff
    dcd     0xe1a00f80
    dcd     0xe3c11002
    dcd     0xe1810f20
    dcd     0xe5c50694
    dcd     0xe59507b0
    dcd     0xe3500a0b
    dcd     0xda000003
    dcd     0xe1a00005
    dcd     0xe3a01023
    bl      func_ov022_020a35f4
    dcd     0xe1a04000
    dcd     0xe1a00004
    dcd     0xe28dd018
    dcd     0xe8bd8038
}
