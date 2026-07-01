extern void FX_Sqrt(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov193_020d581c(void);

asm void func_ov193_020d4cd0(void) {

    dcd 0xe92d40f8
    dcd 0xe24dd010
    dcd 0xe1a05000
    dcd 0xe5951000
    dcd 0xe3a0001e
    dcd 0xe591102c
    dcd 0xe59f2120
    dcd 0xe0030091
    dcd 0xe1a00fa3
    dcd 0xe0c31392
    dcd 0xe5954004
    dcd 0xe08031c3
    dcd 0xe5843030
    dcd 0xe5940000
    dcd 0xe28d1000
    bl func_ov193_020d581c
    dcd 0xe1b07000
    dcd 0x028dd010
    dcd 0xe5840018
    dcd 0x08bd80f8
    dcd 0xe59d0000
    dcd 0xe5946000
    bl FX_Sqrt
    dcd 0xe5972080
    dcd 0xe5961080
    dcd 0xe0400002
    dcd 0xe0401001
    dcd 0xe58d1000
    dcd 0xe5940000
    dcd 0xe59002d8
    dcd 0xe1510000
    dcd 0xa28dd010
    dcd 0xa8bd80f8
    dcd 0xe5940018
    dcd 0xe5941008
    dcd 0xe28d2004
    dcd 0xe2800e19
    bl VEC_Subtract
    dcd 0xe59d0004
    dcd 0xe59d100c
    bl func_020050b4
    dcd 0xe5840014
    dcd 0xe5940034
    dcd 0xe3500000
    dcd 0xc28dd010
    dcd 0xc8bd80f8
    dcd 0xe59d0000
    dcd 0xe3500a02
    dcd 0xaa000008
    dcd 0xe5940000
    dcd 0xe3a01006
    dcd 0xe5c011c7
    dcd 0xe1d512d0
    dcd 0xe1a00005
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd010
    dcd 0xe8bd80f8
    dcd 0xe5943000
    dcd 0xe3a01000
    dcd 0xe59323a4
    dcd 0xe7920101
    dcd 0xe1d006b0
    dcd 0xe1a00c00
    dcd 0xe1a00c20
    dcd 0xe3100001
    dcd 0x1a000007
    dcd 0xe3a00004
    dcd 0xe5c301c7
    dcd 0xe1d512d0
    dcd 0xe1a00005
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd010
    dcd 0xe8bd80f8
    dcd 0xe2811001
    dcd 0xe3510004
    dcd 0xbaffffee
    dcd 0xe28dd010
    dcd 0xe8bd80f8
    dcd 0x66666667
}
