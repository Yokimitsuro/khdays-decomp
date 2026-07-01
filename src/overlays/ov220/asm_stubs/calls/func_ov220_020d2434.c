extern void func_ov107_020c9ee8(void);

asm void func_ov220_020d2434(void) {

    ldr ip, [pc, #8]
    dcd 0xe5900394
    dcd 0xe3a02001
    bx  ip
    dcd func_ov107_020c9ee8
}
