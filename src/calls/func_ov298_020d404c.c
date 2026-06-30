extern void func_ov107_020cab14(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);

asm void func_ov298_020d404c(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe5904004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe5941000
    dcd     0xe5810394
    dcd     0xe5941000
    dcd     0xe5910394
    dcd     0xe3500000
    dcd     0x1a000004
    dcd     0xe3a00002
    dcd     0xe5c101c7
    dcd     0xe28dd00c
    dcd     0xe2400003
    dcd     0xe8bd8030
    dcd     0xe28d2000
    dcd     0xe2800e19
    dcd     0xe28110b0
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe5941000
    dcd     0xe5912394
    dcd     0xe5911080
    dcd     0xe5922080
    dcd     0xe0821001
    dcd     0xe0505001
    dcd     0xe59d0000
    dcd     0xe59d1008
    dcd     0x43a05000
    bl      func_020050b4
    dcd     0xe5840030
    dcd     0xe1a00005
    dcd     0xe28dd00c
    dcd     0xe8bd8030
}
