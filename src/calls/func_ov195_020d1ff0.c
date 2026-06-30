extern void func_ov107_020cab14(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c9ee8(void);
extern void func_0203c634(void);
extern void func_ov195_020d20a0(void);

asm void func_ov195_020d1ff0(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe1a04000
    dcd     0xe5941000
    dcd     0xe3a0001e
    dcd     0xe591202c
    dcd     0xe59f1088
    dcd     0xe0030092
    dcd     0xe0c20391
    dcd     0xe5945004
    dcd     0xe0822fa3
    dcd     0xe5852014
    dcd     0xe5950000
    dcd     0xe3a01000
    bl      func_ov107_020cab14
    dcd     0xe5850008
    dcd     0xe3500000
    dcd     0x0a000008
    dcd     0xe5951000
    dcd     0xe28d2000
    dcd     0xe2800e19
    dcd     0xe28110b0
    bl      VEC_Subtract
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5850010
    dcd     0xe5950000
    dcd     0xe3a0100a
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5950000
    dcd     0xe3a01002
    dcd     0xe59003d0
    dcd     0xe3a02000
    bl      func_ov107_020c9ee8
    dcd     0xe1d412d0
    dcd     0xe59f2010
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8030
    dcd     0x55555556
    dcd     func_ov195_020d20a0
}
