extern void func_0203c7ac(void);
extern void func_ov107_020c5c54(void);
extern void func_ov147_020ce068(void);

asm void func_ov147_020cdc9c(void) {

    dcd 0xe92d4038
    dcd 0xe1a05000
    dcd 0xe1a04002
    bl func_ov107_020c5c54
    dcd 0xe5950040
    dcd 0xe1a00f00
    dcd 0xe1b00fc0
    dcd 0x1595200c
    dcd 0x13520000
    dcd 0x0a000002
    dcd 0xe1a00005
    dcd 0xe3a01000
    dcd 0xe12fff32
    dcd 0xe5950384
    dcd 0xe3a01000
    bl func_0203c7ac
    mov r0, #1
    dcd 0xe585038c
    dcd 0xe5950050
    dcd 0xe3500001
    dcd 0x18bd8038
    dcd 0xe5950214
    dcd 0xe1a01004
    bl func_ov147_020ce068
    dcd 0xe8bd8038
}
