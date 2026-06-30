extern void func_ov107_020c7ca4(void);
extern void func_ov107_020cb100(void);

asm void func_ov179_020d4410(void) {

    dcd 0xe92d4010
    dcd 0xe1a04000
    dcd 0xe2840c01
    dcd 0xe1d00cd6
    dcd 0xe3500001
    dcd 0x1594038c
    dcd 0x13500000
    dcd 0x0a000002
    bl func_ov107_020cb100
    dcd 0xe3a00000
    dcd 0xe584038c
    dcd 0xe1a00004
    bl func_ov107_020c7ca4
    dcd 0xe8bd8010
}
