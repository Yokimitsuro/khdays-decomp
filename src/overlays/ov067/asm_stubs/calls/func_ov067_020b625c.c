extern void func_ov067_020b63b0(void);
extern void func_ov067_020b64b4(void);
extern void func_ov067_020b6688(void);

asm void func_ov067_020b625c(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe1a05001
    dcd     0xe1a04002
    bl      func_ov067_020b63b0
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov067_020b64b4
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov067_020b6688
    dcd     0xe8bd8070
}
