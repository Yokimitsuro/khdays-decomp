extern char data_ov096_020bc0c0[];
extern void func_ov096_020baf60(void);
extern void func_ov096_020baf9c(void);

asm void func_ov096_020babc0(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe2834ec5
    dcd     0xe2841a02
    bl      func_ov096_020baf60
    dcd     0xe1a00005
    dcd     0xe2841a02
    bl      func_ov096_020baf9c
    dcd     0xe8bd8038
    dcd     data_ov096_020bc0c0
}
