extern char data_ov093_020bc3c0[];
extern void func_ov093_020bb900(void);
extern void func_ov093_020bbafc(void);

asm void func_ov093_020bacd0(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe283402c
    dcd     0xe2841b0b
    bl      func_ov093_020bb900
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov093_020bbafc
    dcd     0xe8bd8038
    dcd     data_ov093_020bc3c0
}
