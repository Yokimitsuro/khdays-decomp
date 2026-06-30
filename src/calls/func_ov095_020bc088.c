extern void func_ov022_020a35f4(void);
extern void data_ov095_020bcba0(void);

asm void func_ov095_020bc088(void)
{
    dcd     0xe92d4008
    dcd     0xe59f1028
    dcd     0xe3a02000
    dcd     0xe5911000
    dcd     0xe2811a02
    dcd     0xe5911fe4
    dcd     0xe3510000
    dcd     0x1a000002
    dcd     0xe3a01021
    bl      func_ov022_020a35f4
    dcd     0xe1a02000
    dcd     0xe1a00002
    dcd     0xe8bd8008
    dcd     data_ov095_020bcba0
}
