extern void VEC_Subtract(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020cab14(void);
extern void func_ov198_020d05f4(void);
extern void func_ov198_020d10d8(void);

asm void func_ov198_020d1000(void) {

    dcd 0xe92d4070
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe3a01000
    dcd 0xe5940000
    bl func_ov107_020cab14
    dcd 0xe5941000
    dcd 0xe3a02000
    dcd 0xe5810394
    dcd 0xe5940000
    dcd 0xe5901394
    dcd 0xe3510000
    dcd 0xe3a01002
    dcd 0x1a000004
    dcd 0xe5c011c7
    dcd 0xe1d512d0
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe8bd8070
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a01000
    bl func_ov198_020d05f4
    dcd 0xe5951000
    dcd 0xe3a0001e
    dcd 0xe591102c
    dcd 0xe59f2060
    dcd 0xe0030091
    dcd 0xe1a00fa3
    dcd 0xe0c31392
    dcd 0xe0803143
    dcd 0xe584303c
    dcd 0xe5940000
    dcd 0xe5906224
    dcd 0xe5900228
    dcd 0xe0500006
    dcd 0x42600000
    dcd 0xe2800001
    bl func_02023eb4
    dcd 0xe0860000
    dcd 0xe5840040
    dcd 0xe5940000
    dcd 0xe594100c
    dcd 0xe5900394
    dcd 0xe2842028
    dcd 0xe2800e19
    bl VEC_Subtract
    dcd 0xe1d512d0
    dcd 0xe59f200c
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe8bd8070
    dcd 0x66666667
    dcd func_ov198_020d10d8
}
