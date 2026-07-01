extern void FX_Sqrt(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);

asm void func_ov161_020cd7c0(void) {

    dcd 0xe92d40f8
    dcd 0xe1a04000
    dcd 0xe5945004
    dcd 0xe28d1000
    dcd 0xe5950000
    bl func_ov107_020cab14
    dcd 0xe1b07000
    dcd 0xe5850008
    dcd 0x08bd80f8
    dcd 0xe5956000
    dcd 0xe59d0000
    bl FX_Sqrt
    dcd 0xe5972080
    dcd 0xe5961080
    dcd 0xe0821001
    dcd 0xe0402001
    dcd 0xe58d2000
    dcd 0xe5951000
    dcd 0xe59102d8
    dcd 0xe1520000
    dcd 0xc8bd80f8
    dcd 0xe3a00004
    dcd 0xe5c101c7
    dcd 0xe1d412d0
    dcd 0xe1a00004
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe8bd80f8
}
