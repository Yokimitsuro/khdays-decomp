extern void func_ov048_020b3be0(void);
extern void func_ov048_020b3df0(void);
extern void func_ov048_020b3fcc(void);

asm void func_ov048_020b3a94(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a02f82
    dcd     0xe1b02fa2
    dcd     0x08bd8038
    bl      func_ov048_020b3be0
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov048_020b3df0
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov048_020b3fcc
    dcd     0xe8bd8038
}
