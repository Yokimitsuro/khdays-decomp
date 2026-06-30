extern void func_ov058_020b668c(void);
extern void func_ov058_020b66d8(void);
extern void data_ov058_020b7e00(void);

asm void func_ov058_020b62d4(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340d4
    dcd     0xe2841b0b
    bl      func_ov058_020b668c
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov058_020b66d8
    dcd     0xe8bd8038
    dcd     data_ov058_020b7e00
}
