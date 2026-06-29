extern char data_ov104_020bc2a0[];
extern void func_ov104_020bb14c(void);
extern void func_ov104_020bb3a0(void);

asm void func_ov104_020baf10(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340fc
    dcd     0xe2841b0b
    bl      func_ov104_020bb14c
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov104_020bb3a0
    dcd     0xe8bd8038
    dcd     data_ov104_020bc2a0
}
