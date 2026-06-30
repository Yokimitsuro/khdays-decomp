extern void func_ov107_020c2b38(void);
extern void func_ov107_020c7c1c(void);

asm void func_ov192_020d2004(void) {

    dcd 0xe92d4070
    dcd 0xe1a06000
    dcd 0xe1a05001
    dcd 0xe3a04000
    dcd 0xe59613a4
    dcd 0xe1a00005
    dcd 0xe7911104
    bl func_ov107_020c2b38
    dcd 0xe2844001
    dcd 0xe3540004
    dcd 0xbafffff8
    dcd 0xe1a00006
    dcd 0xe1a01005
    bl func_ov107_020c7c1c
    dcd 0xe8bd8070
}
