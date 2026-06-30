extern void FX_Sqrt(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);

asm void func_ov142_020d0ad8(void) {

    dcd 0xe92d40f8
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe28d1000
    dcd 0xe5940000
    bl func_ov107_020cab14
    dcd 0xe1b07000
    dcd 0xe5840004
    dcd 0x08bd80f8
    dcd 0xe5946000
    dcd 0xe59d0000
    bl FX_Sqrt
    dcd 0xe5972080
    dcd 0xe5961080
    dcd 0xe0821001
    dcd 0xe0401001
    dcd 0xe58d1000
    dcd 0xe5940000
    dcd 0xe59002d8
    dcd 0xe1510000
    dcd 0xc8bd80f8
    dcd 0xe5950000
    dcd 0xe5941034
    dcd 0xe590002c
    dcd 0xe0510000
    dcd 0xe5840034
    dcd 0x58bd80f8
    dcd 0xe5940000
    dcd 0xe3a01004
    dcd 0xe5c011c7
    dcd 0xe1d512d0
    dcd 0xe1a00005
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe8bd80f8
}
