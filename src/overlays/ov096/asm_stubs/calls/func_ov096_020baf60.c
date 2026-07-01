extern void func_ov096_020baff4(void);
extern void func_ov096_020bb20c(void);
extern void func_ov096_020bb378(void);

asm void func_ov096_020baf60(void)
{
    dcd     0xe92d4070
    dcd     0xe1a05001
    dcd     0xe1a06000
    dcd     0xe1a04002
    dcd     0xe2851008
    bl      func_ov096_020baff4
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov096_020bb20c
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov096_020bb378
    dcd     0xe8bd8070
}
