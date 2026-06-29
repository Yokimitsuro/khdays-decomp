extern void func_ov060_020b6484(void);
extern void func_ov060_020b65fc(void);
extern void func_ov060_020b68f8(void);
extern void func_ov060_020b6b20(void);

asm void func_ov060_020b63c8(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe1a05001
    dcd     0xe1a04002
    bl      func_ov060_020b6484
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov060_020b65fc
    dcd     0xe1a00006
    dcd     0xe1a02004
    dcd     0xe2851e11
    bl      func_ov060_020b68f8
    dcd     0xe1a00006
    dcd     0xe1a02004
    dcd     0xe2851e22
    bl      func_ov060_020b6b20
    dcd     0xe8bd8070
}
