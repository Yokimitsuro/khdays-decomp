extern void func_ov107_020cab14(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov182_020cecac(void);

asm void func_ov182_020cebe4(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe5840010
    dcd     0xe3500000
    dcd     0x0a000008
    dcd     0xe5941004
    dcd     0xe28d2000
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5840018
    dcd     0xe5840014
    dcd     0xe3a01000
    dcd     0xe5940000
    dcd     0xe1a02001
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe3a01001
    dcd     0xe5801394
    dcd     0xe5940000
    dcd     0xe3a03000
    dcd     0xe2801c01
    dcd     0xe1d1cabe
    dcd     0xe59f2044
    dcd     0xe1a00005
    dcd     0xe38cc001
    dcd     0xe1c1cabe
    dcd     0xe5941000
    dcd     0xe591e388
    dcd     0xe59ec008
    dcd     0xe1a01c0c
    dcd     0xe1a01c21
    dcd     0xe3c11001
    dcd     0xe3ccc0ff
    dcd     0xe20110ff
    dcd     0xe18c1001
    dcd     0xe58e1008
    dcd     0xe584301c
    dcd     0xe1d512d0
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8030
    dcd     func_ov182_020cecac
}
