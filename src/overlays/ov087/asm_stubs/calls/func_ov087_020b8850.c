extern char data_ov087_020b9be0[];
extern void func_ov087_020b8a8c(void);
extern void func_ov087_020b8ce0(void);

asm void func_ov087_020b8850(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340fc
    dcd     0xe2841b0b
    bl      func_ov087_020b8a8c
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov087_020b8ce0
    dcd     0xe8bd8038
    dcd     data_ov087_020b9be0
}
