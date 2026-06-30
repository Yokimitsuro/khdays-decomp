extern void func_ov095_020bb42c(void);
extern void func_ov095_020bb478(void);
extern void data_ov095_020bcba0(void);

asm void func_ov095_020bb074(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340d4
    dcd     0xe2841b0b
    bl      func_ov095_020bb42c
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov095_020bb478
    dcd     0xe8bd8038
    dcd     data_ov095_020bcba0
}
