extern char data_ov060_020b749c[];
extern void func_ov022_020b14a4(void);
extern void func_ov022_020b15b0(void);
extern void func_ov022_020b1cec(void);

asm void func_ov060_020b5e98(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe2850fbe
    dcd     0xe2804a02
    dcd     0xe3a00000
    dcd     0xe5c40334
    dcd     0xe5d50009
    dcd     0xe3a01001
    bl      func_ov022_020b15b0
    dcd     0xe5952020
    dcd     0xe5d51009
    dcd     0xe2823004
    dcd     0xe59f0024
    dcd     0xe3a02000
    bl      func_ov022_020b14a4
    dcd     0xe5840340
    dcd     0xe2850eda
    dcd     0xe3a010d7
    bl      func_ov022_020b1cec
    dcd     0xe5d40334
    dcd     0xe3800009
    dcd     0xe5c40334
    dcd     0xe8bd8038
    dcd     data_ov060_020b749c
}
