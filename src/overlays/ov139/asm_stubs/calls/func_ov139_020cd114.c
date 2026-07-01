extern void func_ov107_020cab14(void);
extern void func_0203c634(void);
extern void FX_Sqrt(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_ov107_020c9f48(void);
extern void func_0202f384(void);
extern void func_01ffa724(void);
extern void func_ov139_020cd224(void);

asm void func_ov139_020cd114(void)
{
    dcd     0xe92d40f0
    dcd     0xe24dd01c
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe28d1000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe1b07000
    dcd     0xe5840004
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd01c
    dcd     0xe8bd80f0
    dcd     0xe5946000
    dcd     0xe59d0000
    bl      FX_Sqrt
    dcd     0xe5973080
    dcd     0xe5961080
    dcd     0xe28d2010
    dcd     0xe0831001
    dcd     0xe0400001
    dcd     0xe58d0000
    dcd     0xe5940004
    dcd     0xe594104c
    dcd     0xe2800074
    bl      VEC_Subtract
    dcd     0xe59d0010
    dcd     0xe59d1018
    bl      func_020050b4
    dcd     0xe584000c
    dcd     0xe5940000
    dcd     0xe28d1004
    dcd     0xe5900390
    bl      func_ov107_020c9f48
    dcd     0xe5941000
    dcd     0xe1a06000
    dcd     0xe2840014
    dcd     0xe28d2004
    dcd     0xe28110a0
    bl      func_0202f384
    dcd     0xe2841014
    dcd     0xe1a00006
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe5942000
    dcd     0xe59d1000
    dcd     0xe59202d8
    dcd     0xe1510000
    dcd     0xaa000002
    dcd     0xe3510a03
    dcd     0xc28dd01c
    dcd     0xc8bd80f0
    dcd     0xe5920384
    dcd     0xe3a01000
    dcd     0xe5c010a8
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd01c
    dcd     0xe8bd80f0
    dcd     func_ov139_020cd224
}
