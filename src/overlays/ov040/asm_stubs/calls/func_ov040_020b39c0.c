extern void func_ov040_020b3a54(void);
extern void func_ov040_020b3c6c(void);
extern void func_ov040_020b3dd8(void);

asm void func_ov040_020b39c0(void)
{
    dcd     0xe92d4070
    dcd     0xe1a05001
    dcd     0xe1a06000
    dcd     0xe1a04002
    dcd     0xe2851008
    bl      func_ov040_020b3a54
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov040_020b3c6c
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov040_020b3dd8
    dcd     0xe8bd8070
}
