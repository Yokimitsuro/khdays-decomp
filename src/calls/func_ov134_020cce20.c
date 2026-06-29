extern void FX_Sqrt(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);

asm void func_ov134_020cce20(void)
{
    dcd     0xe92d40f8
    dcd     0xe24dd010
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe28d1000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe1b07000
    dcd     0x028dd010
    dcd     0xe5840008
    dcd     0x08bd80f8
    dcd     0xe5946000
    dcd     0xe59d0000
    bl      FX_Sqrt
    dcd     0xe5972080
    dcd     0xe5961080
    dcd     0xe0821001
    dcd     0xe0402001
    dcd     0xe58d2000
    dcd     0xe5941000
    dcd     0xe59102d8
    dcd     0xe1520000
    dcd     0xc28dd010
    dcd     0xc8bd80f8
    dcd     0xe5940008
    dcd     0xe28d2004
    dcd     0xe2800e19
    dcd     0xe28110b0
    bl      VEC_Subtract
    dcd     0xe59d0004
    dcd     0xe59d100c
    bl      func_020050b4
    dcd     0xe5840010
    dcd     0xe5d40042
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x0a000008
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd80f8
    dcd     0xe59d2000
    dcd     0xe3520a03
    dcd     0xaa000018
    dcd     0xe5950000
    dcd     0xe5941030
    dcd     0xe590002c
    dcd     0xe0510000
    dcd     0x528dd010
    dcd     0xe5840030
    dcd     0x58bd80f8
    dcd     0xe5940000
    dcd     0xe5906224
    dcd     0xe5900228
    dcd     0xe0500006
    dcd     0x42600000
    dcd     0xe2800001
    bl      func_02023eb4
    dcd     0xe0860000
    dcd     0xe5840030
    dcd     0xe5940000
    dcd     0xe3a01006
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd80f8
    dcd     0xe3520a06
    dcd     0xd28dd010
    dcd     0xd8bd80f8
    dcd     0xe5941000
    dcd     0xe59102d8
    dcd     0xe1520000
    dcd     0xa28dd010
    dcd     0xa8bd80f8
    dcd     0xe3a00004
    dcd     0xe5c101c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd80f8
}
