extern void func_ov067_020b63e0(void);
extern void func_ov067_020b65f0(void);
extern void func_ov067_020b67cc(void);

asm void func_ov067_020b6294(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5d52694
    dcd     0xe1a04001
    dcd     0xe1a02f82
    dcd     0xe1b02fa2
    dcd     0x08bd8038
    bl      func_ov067_020b63e0
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov067_020b65f0
    dcd     0xe1a00005
    dcd     0xe1a01004
    bl      func_ov067_020b67cc
    dcd     0xe8bd8038
}
