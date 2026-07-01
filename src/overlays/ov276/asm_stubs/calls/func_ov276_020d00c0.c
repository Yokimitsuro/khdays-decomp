extern void func_0202a440(void);
extern void func_0203c7e8(void);
extern void func_ov107_020c68ec(void);
extern void func_ov107_020c9eac(void);

asm void func_ov276_020d00c0(void) {

    dcd 0xe92d4038
    dcd 0xe1a05000
    dcd 0xe2850fe1
    bl func_0202a440
    dcd 0xe3a00000
    dcd 0xe5850390
    dcd 0xe59503a8
    bl func_0203c7e8
    dcd 0xe5950470
    bl func_ov107_020c9eac
    dcd 0xe3a04000
    dcd 0xe0850184
    dcd 0xe5900488
    dcd 0xe3500000
    dcd 0x0a000000
    bl func_0203c7e8
    dcd 0xe2844001
    dcd 0xe3540006
    dcd 0xbafffff7
    dcd 0xe1a00005
    bl func_ov107_020c68ec
    dcd 0xe8bd8038
}
