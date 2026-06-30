extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);
extern void func_ov151_020ce930(void);

asm void func_ov151_020ce864(void) {

    dcd 0xe92d4030
    dcd 0xe24dd00c
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe3a01000
    dcd 0xe5940000
    bl func_ov107_020cab14
    dcd 0xe5840004
    dcd 0xe3500000
    dcd 0x1a000008
    dcd 0xe5940000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d512d0
    dcd 0xe1a00005
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8030
    dcd 0xe5941040
    dcd 0xe28d2000
    dcd 0xe2800e19
    bl VEC_Subtract
    dcd 0xe28d0000
    dcd 0xe3a02000
    dcd 0xe1a01000
    dcd 0xe58d2004
    bl func_01ff8d18
    dcd 0xe59d0000
    dcd 0xe59d1008
    bl func_020050b4
    dcd 0xe584000c
    dcd 0xe3a00000
    dcd 0xe5840038
    dcd 0xe5951000
    dcd 0xe3a0001e
    dcd 0xe591102c
    dcd 0xe59f2028
    dcd 0xe0030091
    dcd 0xe1a00fa3
    dcd 0xe0c31392
    dcd 0xe08030c3
    dcd 0xe5843010
    dcd 0xe1d512d0
    dcd 0xe59f2010
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8030
    dcd 0x66666667
    dcd func_ov151_020ce930
}
