extern void func_ov107_020c6980(void);
extern void func_ov107_020c9ec8(void);

asm void func_ov243_020d3b64(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5950390
    dcd     0xe1a04001
    bl      func_ov107_020c9ec8
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov107_020c6980
    dcd     0xe595038c
    dcd     0xe285e0a0
    dcd     0xe280c010
    dcd     0xe8be000f
    dcd     0xe8ac000f
    dcd     0xe8be000f
    dcd     0xe8ac000f
    dcd     0xe89e0007
    dcd     0xe88c0007
    dcd     0xe8bd8038
}
