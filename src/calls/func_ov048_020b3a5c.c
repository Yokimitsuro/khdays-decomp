extern void func_ov048_020b3bb0(void);
extern void func_ov048_020b3cb4(void);
extern void func_ov048_020b3e88(void);

asm void func_ov048_020b3a5c(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe1a05001
    dcd     0xe1a04002
    bl      func_ov048_020b3bb0
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov048_020b3cb4
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov048_020b3e88
    dcd     0xe8bd8070
}
