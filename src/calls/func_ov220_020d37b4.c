extern void func_0203c634(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c9264(void);
extern void func_ov220_020d2434(void);
extern void func_ov220_020d380c(void);

asm void func_ov220_020d37b4(void) {

    dcd 0xe92d4038
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe3a0100a
    dcd 0xe5940000
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a01001
    bl func_ov220_020d2434
    dcd 0xe5940000
    dcd 0xe5943008
    dcd 0xe59f1018
    dcd 0xe3a02006
    bl func_ov107_020c5af8
    dcd 0xe1d512d0
    dcd 0xe1a00005
    dcd 0xe59f2008
    bl func_0203c634
    dcd 0xe8bd8038
    dcd 0x00000137
    dcd func_ov220_020d380c
}
