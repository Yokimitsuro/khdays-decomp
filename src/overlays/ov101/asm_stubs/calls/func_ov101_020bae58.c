extern char data_ov101_020bc0e0[];
extern void func_ov101_020bb628(void);
extern void func_ov101_020bb6e4(void);

asm void func_ov101_020bae58(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe59f2020
    dcd     0xe2851c2a
    dcd     0xe5924000
    dcd     0xe1d12bfa
    dcd     0xe2841db2
    bl      func_ov101_020bb628
    dcd     0xe1a00005
    dcd     0xe2841db2
    bl      func_ov101_020bb6e4
    dcd     0xe8bd8038
    dcd     data_ov101_020bc0e0
}
