extern void func_ov180_020d6268(void);

asm void func_ov180_020d5fc0(void) {

    dcd 0xe92d4008
    dcd 0xe5901050
    dcd 0xe3510001
    dcd 0x18bd8008
    dcd 0xe5900214
    bl func_ov180_020d6268
    dcd 0xe8bd8008
}
