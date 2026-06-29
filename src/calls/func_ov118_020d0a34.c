extern void FX_Sqrt(void);
extern char data_02042258[];
extern void func_01ffa724(void);
extern void func_02023eb4(void);
extern void func_0202f384(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);
extern void func_ov118_020d0200(void);

asm void func_ov118_020d0a34(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe28d1000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe5840004
    dcd     0xe3500000
    dcd     0x1a000007
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd80f8
    dcd     0xe5951000
    dcd     0xe3a0001e
    dcd     0xe591102c
    dcd     0xe59f20e4
    dcd     0xe0030091
    dcd     0xe1a00fa3
    dcd     0xe0c31392
    dcd     0xe08031c3
    dcd     0xe5843028
    dcd     0xe59d0000
    dcd     0xe89400c0
    bl      FX_Sqrt
    dcd     0xe5973080
    dcd     0xe5962080
    dcd     0xe2841018
    dcd     0xe0832002
    dcd     0xe0402002
    dcd     0xe1a00004
    dcd     0xe58d2000
    bl      func_ov118_020d0200
    dcd     0xe59f20a4
    dcd     0xe284002c
    dcd     0xe2841008
    bl      func_0202f384
    dcd     0xe284102c
    dcd     0xe1a02001
    dcd     0xe3a00c01
    bl      func_01ffa724
    dcd     0xe59d2000
    dcd     0xe3520a01
    dcd     0xda000003
    dcd     0xe5941000
    dcd     0xe59102d8
    dcd     0xe1520000
    dcd     0xba000007
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd80f8
    dcd     0xe5940040
    dcd     0xe3500000
    dcd     0xc8bd80f8
    dcd     0xe5916224
    dcd     0xe5910228
    dcd     0xe0500006
    dcd     0x42600000
    dcd     0xe2800001
    bl      func_02023eb4
    dcd     0xe0860000
    dcd     0xe5840040
    dcd     0xe5940000
    dcd     0xe3a01006
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd80f8
    dcd     0x66666667
    dcd     data_02042258
}
