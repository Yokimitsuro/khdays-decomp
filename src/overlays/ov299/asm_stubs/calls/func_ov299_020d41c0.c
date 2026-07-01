extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);

asm void func_ov299_020d41c0(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe5904214
    dcd     0xe1a05001
    dcd     0xe5940030
    dcd     0xe3500000
    dcd     0x128dd00c
    dcd     0x13a00000
    dcd     0x18bd8030
    dcd     0xe28d1000
    dcd     0xe2820004
    bl      func_01ff8d18
    dcd     0xe3500000
    dcd     0x1a000017
    dcd     0xe3550000
    dcd     0x0a000008
    dcd     0xe5940004
    dcd     0xe28d2000
    dcd     0xe2851e19
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe3a02000
    dcd     0xe1a01000
    dcd     0xe58d2004
    bl      func_01ff8d18
    dcd     0xe3500000
    dcd     0x1a00000a
    dcd     0xe5942014
    dcd     0xe594100c
    dcd     0xe262c000
    dcd     0xe2613000
    dcd     0xe28d0000
    dcd     0xe3a02000
    dcd     0xe1a01000
    dcd     0xe58d3000
    dcd     0xe58d2004
    dcd     0xe58dc008
    bl      func_01ff8d18
    dcd     0xe28d1000
    dcd     0xe284200c
    dcd     0xe3a00c06
    bl      func_01ffa724
    dcd     0xe5941010
    mov r0, #1
    dcd     0xe2811c05
    dcd     0xe5841010
    dcd     0xe5840030
    dcd     0xe28dd00c
    dcd     0xe8bd8030
}
