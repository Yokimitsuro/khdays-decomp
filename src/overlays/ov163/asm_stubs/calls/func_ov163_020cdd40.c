extern void func_ov107_020c2f7c(void);
extern void func_ov163_020cdd58(void);

asm void func_ov163_020cdd40(void) {

    ldr ip, [pc, #8]
    ldr r1, [pc, #8]
    dcd 0xe3a00019
    bx  ip
    dcd func_ov107_020c2f7c
    dcd func_ov163_020cdd58
}
