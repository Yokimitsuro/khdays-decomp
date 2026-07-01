extern void func_ov107_020c9ec8(void);
extern void func_ov107_020c6980(void);

asm void func_ov190_020d3c90(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe59503c0
    dcd     0xe1a04001
    bl      func_ov107_020c9ec8
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov107_020c6980
    dcd     0xe8bd8038
}
