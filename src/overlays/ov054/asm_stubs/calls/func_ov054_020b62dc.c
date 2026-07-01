extern char data_ov054_020b74a0[];
extern void func_0202a7dc(void);
extern void func_ov054_020b6a3c(void);

asm void func_ov054_020b62dc(void)
{
    dcd     0xe92d4010
    dcd     0xe59f101c
    dcd     0xe1a04000
    dcd     0xe5910000
    dcd     0xe28000b8
    dcd     0xe2800b0b
    bl      func_0202a7dc
    dcd     0xe1a00004
    bl      func_ov054_020b6a3c
    dcd     0xe8bd8010
    dcd     data_ov054_020b74a0
}
