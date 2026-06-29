extern void func_ov059_020b6358(void);
extern void func_ov059_020b64a0(void);
extern void func_ov059_020b67c0(void);

asm void func_ov059_020b61fc(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a01f82
    dcd     0xe1b01fa1
    dcd     0x08bd8038
    dcd     0xe2841008
    bl      func_ov059_020b6358
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov059_020b64a0
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov059_020b67c0
    dcd     0xe8bd8038
}
