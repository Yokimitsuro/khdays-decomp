extern char data_ov083_020b9b00[];
extern void func_ov022_020a35f4(void);

asm void func_ov083_020b8b0c(void)
{
    dcd     0xe59f2020
    dcd     0xe59fc020
    dcd     0xe5922000
    dcd     0xe3a03000
    dcd     0xe2822edf
    dcd     0xe2822a02
    dcd     0xe5821114
    dcd     0xe3a01021
    dcd     0xe5823118
    bx  ip
    dcd     data_ov083_020b9b00
    dcd     func_ov022_020a35f4
}
