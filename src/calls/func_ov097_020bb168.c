extern void func_ov097_020bb224(void);
extern void func_ov097_020bb39c(void);
extern void func_ov097_020bb698(void);
extern void func_ov097_020bb8c0(void);

asm void func_ov097_020bb168(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe1a05001
    dcd     0xe1a04002
    bl      func_ov097_020bb224
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov097_020bb39c
    dcd     0xe1a00006
    dcd     0xe1a02004
    dcd     0xe2851e11
    bl      func_ov097_020bb698
    dcd     0xe1a00006
    dcd     0xe1a02004
    dcd     0xe2851e22
    bl      func_ov097_020bb8c0
    dcd     0xe8bd8070
}
