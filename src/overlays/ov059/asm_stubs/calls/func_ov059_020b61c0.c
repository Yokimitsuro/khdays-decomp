extern void func_ov059_020b6254(void);
extern void func_ov059_020b646c(void);
extern void func_ov059_020b65d8(void);

asm void func_ov059_020b61c0(void)
{
    dcd     0xe92d4070
    dcd     0xe1a05001
    dcd     0xe1a06000
    dcd     0xe1a04002
    dcd     0xe2851008
    bl      func_ov059_020b6254
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov059_020b646c
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov059_020b65d8
    dcd     0xe8bd8070
}
