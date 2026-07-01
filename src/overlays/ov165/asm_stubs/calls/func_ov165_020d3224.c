extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov165_020d3294(void);

asm void func_ov165_020d3224(void) {

    dcd 0xe92d4030
    dcd 0xe24dd00c
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe3a01003
    dcd 0xe5940000
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe5940048
    dcd 0xe3500000
    dcd 0x0a000009
    dcd 0xe5941000
    dcd 0xe28d2000
    dcd 0xe2800e19
    dcd 0xe28110b0
    bl VEC_Subtract
    dcd 0xe59d0000
    dcd 0xe59d1008
    bl func_020050b4
    dcd 0xe5840010
    dcd 0xe584000c
    dcd 0xe1d512d0
    dcd 0xe59f200c
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8030
    dcd func_ov165_020d3294
}
