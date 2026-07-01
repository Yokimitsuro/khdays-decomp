extern void FX_Sqrt(void);
extern void VEC_DotProduct(void);
extern void VEC_Subtract(void);
extern void data_02042258(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_02023eb4(void);
extern void func_0202f384(void);
extern void func_0203c634(void);
extern void func_ov124_020d0e64(void);

asm void func_ov124_020d08c4(void)
{
    dcd     0xe92d40f0
    dcd     0xe24dd01c
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe28d1000
    dcd     0xe5940000
    bl      func_ov124_020d0e64
    dcd     0xe3500000
    dcd     0x028dd01c
    dcd     0xe5840024
    dcd     0x08bd80f0
    dcd     0xe5951000
    dcd     0xe3a0001e
    dcd     0xe591102c
    dcd     0xe59f21a8
    dcd     0xe0030091
    dcd     0xe1a00fa3
    dcd     0xe0c31392
    dcd     0xe08031c3
    dcd     0xe5843020
    dcd     0xe5946024
    dcd     0xe59d0000
    dcd     0xe5947000
    bl      FX_Sqrt
    dcd     0xe5962080
    dcd     0xe5971080
    dcd     0xe0400002
    dcd     0xe0401001
    dcd     0xe58d1000
    dcd     0xe5940000
    dcd     0xe59002d8
    dcd     0xe1510000
    dcd     0xa28dd01c
    dcd     0xa8bd80f0
    dcd     0xe5940024
    dcd     0xe5941010
    dcd     0xe28d2010
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe28d0010
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe5941000
    dcd     0xe59f2138
    dcd     0xe28d0004
    dcd     0xe28110a0
    bl      func_0202f384
    dcd     0xe59d0000
    dcd     0xe3500a01
    dcd     0xaa000021
    dcd     0xe28d0004
    dcd     0xe28d1010
    bl      VEC_DotProduct
    dcd     0xe3500c0e
    dcd     0xba00001c
    dcd     0xe59d0010
    dcd     0xe59d1018
    bl      func_020050b4
    dcd     0xe584001c
    dcd     0xe5941000
    dcd     0xe5910394
    dcd     0xe1d006b0
    dcd     0xe1a00c00
    dcd     0xe1a00c20
    dcd     0xe3100001
    dcd     0x128dd01c
    dcd     0x18bd80f0
    dcd     0xe5916224
    dcd     0xe5910228
    dcd     0xe0500006
    dcd     0x42600000
    dcd     0xe2800001
    bl      func_02023eb4
    dcd     0xe0860000
    dcd     0xe5840028
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd01c
    dcd     0xe8bd80f0
    dcd     0xe59d0010
    dcd     0xe59d1018
    bl      func_020050b4
    dcd     0xe584001c
    dcd     0xe5940000
    dcd     0xe5900394
    dcd     0xe1d006b0
    dcd     0xe1a00c00
    dcd     0xe1a00c20
    dcd     0xe3100001
    dcd     0x128dd01c
    dcd     0x18bd80f0
    dcd     0xe5950000
    dcd     0xe5941028
    dcd     0xe590002c
    dcd     0xe0410000
    dcd     0xe3500000
    dcd     0xc28dd01c
    dcd     0xe5840028
    dcd     0xc8bd80f0
    dcd     0xe5940000
    dcd     0xe5906224
    dcd     0xe5900228
    dcd     0xe0500006
    dcd     0x42600000
    dcd     0xe2800001
    bl      func_02023eb4
    dcd     0xe0860000
    dcd     0xe5840028
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd01c
    dcd     0xe8bd80f0
    dcd     0x66666667
    dcd     data_02042258
}
