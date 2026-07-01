extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov152_020d5b78(void);

asm void func_ov152_020d5b30(void) {

    dcd 0xe92d4010
    dcd 0xe1a04000
    dcd 0xe5941004
    dcd 0xe5910014
    dcd 0xe3500080
    dcd 0xa8bd8010
    dcd 0xe3a00000
    dcd 0xe5810030
    dcd 0xe5910000
    dcd 0xe3a01002
    dcd 0xe3a02001
    bl func_ov107_020c9264
    dcd 0xe1d412d0
    dcd 0xe59f2008
    dcd 0xe1a00004
    bl func_0203c634
    dcd 0xe8bd8010
    dcd func_ov152_020d5b78
}
