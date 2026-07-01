extern void func_ov107_020cab14(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);

asm void func_ov240_020ce8e8(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe5905004
    dcd     0xe5950000
    dcd     0xe5903394
    dcd     0xe3530000
    dcd     0x1a00000c
    dcd     0xe3a01000
    bl      func_ov107_020cab14
    dcd     0xe5951000
    dcd     0xe5810394
    dcd     0xe5951000
    dcd     0xe5913394
    dcd     0xe3530000
    dcd     0x1a000004
    dcd     0xe3a00002
    dcd     0xe5c101c7
    dcd     0xe28dd00c
    dcd     0xe2400003
    dcd     0xe8bd8030
    dcd     0xe5951008
    dcd     0xe28d2000
    dcd     0xe2830e19
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe3a02000
    dcd     0xe1a01000
    dcd     0xe58d2004
    bl      func_01ff8d18
    dcd     0xe1a04000
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5850010
    dcd     0xe1a00004
    dcd     0xe28dd00c
    dcd     0xe8bd8030
}
