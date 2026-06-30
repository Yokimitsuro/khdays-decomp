extern void func_ov107_020c7500(void);
extern void func_ov107_020cb040(void);

asm void func_ov180_020d6128(void) {

    dcd 0xe92d4078
    dcd 0xe24dd004
    dcd 0xe1a05001
    dcd 0xe5d51002
    dcd 0xe1a06000
    dcd 0xe1a04002
    dcd 0xe3510005
    dcd 0x1a00000c
    dcd 0xe5d51003
    dcd 0xe3510000
    dcd 0x1a000009
    dcd 0xe596138c
    dcd 0xe3510000
    dcd 0x1a000006
    dcd 0xe59f102c
    dcd 0xe286c0a0
    dcd 0xe3a02004
    dcd 0xe3a03001
    dcd 0xe58dc000
    bl func_ov107_020cb040
    dcd 0xe586038c
    dcd 0xe1a00006
    dcd 0xe1a01005
    dcd 0xe1a02004
    bl func_ov107_020c7500
    dcd 0xe28dd004
    dcd 0xe8bd8078
    dcd 0x00000143
}
