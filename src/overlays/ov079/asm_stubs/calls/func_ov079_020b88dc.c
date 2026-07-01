extern void func_ov079_020b8a38(void);
extern void func_ov079_020b8b80(void);
extern void func_ov079_020b8ea0(void);

asm void func_ov079_020b88dc(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a01f82
    dcd     0xe1b01fa1
    dcd     0x08bd8038
    dcd     0xe2841008
    bl      func_ov079_020b8a38
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov079_020b8b80
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov079_020b8ea0
    dcd     0xe8bd8038
}
