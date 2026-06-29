extern void func_ov079_020b8934(void);
extern void func_ov079_020b8b4c(void);
extern void func_ov079_020b8cb8(void);

asm void func_ov079_020b88a0(void)
{
    dcd     0xe92d4070
    dcd     0xe1a05001
    dcd     0xe1a06000
    dcd     0xe1a04002
    dcd     0xe2851008
    bl      func_ov079_020b8934
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov079_020b8b4c
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov079_020b8cb8
    dcd     0xe8bd8070
}
