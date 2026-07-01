extern void func_ov086_020b8a90(void);
extern void func_ov086_020b8b94(void);
extern void func_ov086_020b8d68(void);

asm void func_ov086_020b893c(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe1a05001
    dcd     0xe1a04002
    bl      func_ov086_020b8a90
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov086_020b8b94
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov086_020b8d68
    dcd     0xe8bd8070
}
