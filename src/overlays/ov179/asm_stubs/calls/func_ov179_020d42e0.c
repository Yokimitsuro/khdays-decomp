extern void func_ov107_020c5c54(void);
extern void func_ov107_020c6980(void);

asm void func_ov179_020d42e0(void) {

    dcd 0xe92d4038
    dcd 0xe1a05000
    dcd 0xe5952388
    dcd 0xe1a04001
    dcd 0xe28210b0
    bl func_ov107_020c5c54
    dcd 0xe1a00005
    dcd 0xe1a01004
    bl func_ov107_020c6980
    dcd 0xe8bd8038
}
