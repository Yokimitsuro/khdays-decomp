extern char data_ov046_020b4b40[];
extern void func_ov046_020b4088(void);
extern void func_ov046_020b4144(void);

asm void func_ov046_020b38b8(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe59f2020
    dcd     0xe2851c2a
    dcd     0xe5924000
    dcd     0xe1d12bfa
    dcd     0xe2841db2
    bl      func_ov046_020b4088
    dcd     0xe1a00005
    dcd     0xe2841db2
    bl      func_ov046_020b4144
    dcd     0xe8bd8038
    dcd     data_ov046_020b4b40
}
