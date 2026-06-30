extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020cab14(void);
extern void func_ov162_020cf520(void);

asm void func_ov162_020cf458(void) {

    dcd 0xe92d4030
    dcd 0xe24dd00c
    dcd 0xe1a05000
    dcd 0xe8950011
    dcd 0xe590102c
    dcd 0xe5942030
    dcd 0xe59f00a0
    dcd 0xe0821001
    dcd 0xe1510000
    dcd 0xb28dd00c
    dcd 0xe5841030
    dcd 0xb8bd8030
    dcd 0xe5940000
    dcd 0xe3a01000
    bl func_ov107_020cab14
    dcd 0xe5840008
    dcd 0xe3500000
    dcd 0x0a000008
    dcd 0xe5941044
    dcd 0xe28d2000
    dcd 0xe2800074
    bl VEC_Subtract
    dcd 0xe59d0000
    dcd 0xe59d1008
    bl func_020050b4
    dcd 0xe5840010
    dcd 0xe584000c
    dcd 0xe5940000
    dcd 0xe3a01000
    dcd 0xe1d0c6b0
    dcd 0xe1a02001
    dcd 0xe1a0380c
    dcd 0xe1a03c23
    dcd 0xe3c33082
    dcd 0xe1a03803
    dcd 0xe1a03823
    dcd 0xe3ccccff
    dcd 0xe1a03c03
    dcd 0xe18c3823
    dcd 0xe1c036b0
    dcd 0xe5940000
    bl func_ov107_020c9264
    dcd 0xe1d512d0
    dcd 0xe59f2010
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8030
    dcd 0x000006ee
    dcd func_ov162_020cf520
}
