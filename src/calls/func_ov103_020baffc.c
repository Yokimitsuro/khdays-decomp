extern void func_ov103_020bb150(void);
extern void func_ov103_020bb254(void);
extern void func_ov103_020bb428(void);

asm void func_ov103_020baffc(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe1a05001
    dcd     0xe1a04002
    bl      func_ov103_020bb150
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov103_020bb254
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov103_020bb428
    dcd     0xe8bd8070
}
