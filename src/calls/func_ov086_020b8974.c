extern void func_ov086_020b8ac0(void);
extern void func_ov086_020b8cd0(void);
extern void func_ov086_020b8eac(void);

asm void func_ov086_020b8974(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a02f82
    dcd     0xe1b02fa2
    dcd     0x08bd8038
    bl      func_ov086_020b8ac0
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov086_020b8cd0
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov086_020b8eac
    dcd     0xe8bd8038
}
