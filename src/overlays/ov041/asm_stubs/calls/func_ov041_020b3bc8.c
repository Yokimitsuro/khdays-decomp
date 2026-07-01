extern void func_ov041_020b3c84(void);
extern void func_ov041_020b3dfc(void);
extern void func_ov041_020b40f8(void);
extern void func_ov041_020b4320(void);

asm void func_ov041_020b3bc8(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe1a05001
    dcd     0xe1a04002
    bl      func_ov041_020b3c84
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov041_020b3dfc
    dcd     0xe1a00006
    dcd     0xe1a02004
    dcd     0xe2851e11
    bl      func_ov041_020b40f8
    dcd     0xe1a00006
    dcd     0xe1a02004
    dcd     0xe2851e22
    bl      func_ov041_020b4320
    dcd     0xe8bd8070
}
