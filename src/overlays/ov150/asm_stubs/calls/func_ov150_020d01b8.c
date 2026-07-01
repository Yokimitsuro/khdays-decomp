extern void func_ov107_020c2b38(void);
extern void func_ov107_020c7c1c(void);

asm void func_ov150_020d01b8(void) {

    dcd 0xe92d4038
    dcd 0xe1a05000
    dcd 0xe1a04001
    dcd 0xe59513c8
    dcd 0xe1a00004
    bl func_ov107_020c2b38
    dcd 0xe1a00005
    dcd 0xe1a01004
    bl func_ov107_020c7c1c
    dcd 0xe8bd8038
}
