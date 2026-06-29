extern char data_ov054_020b74a0[];
extern void func_ov054_020b6314(void);
extern void func_ov054_020b6324(void);

asm void func_ov054_020b5fec(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340a4
    dcd     0xe2841b0b
    bl      func_ov054_020b6314
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov054_020b6324
    dcd     0xe8bd8038
    dcd     data_ov054_020b74a0
}
