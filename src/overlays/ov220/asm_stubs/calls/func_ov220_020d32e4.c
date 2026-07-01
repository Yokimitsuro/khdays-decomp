extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov220_020d2448(void);
extern void func_ov220_020d333c(void);

asm void func_ov220_020d32e4(void) {

    dcd 0xe92d4038
    dcd 0xe1a05000
    dcd 0xe5954004
    bl func_ov220_020d2448
    dcd 0xe3500000
    dcd 0xe3a02000
    dcd 0xaa000003
    dcd 0xe1d512d0
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe8bd8038
    dcd 0xe5940010
    dcd 0xe3a01006
    dcd 0xe584000c
    dcd 0xe5940000
    bl func_ov107_020c9264
    dcd 0xe1d512d0
    dcd 0xe59f2008
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe8bd8038
    dcd func_ov220_020d333c
}
