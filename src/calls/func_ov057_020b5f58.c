extern void func_ov057_020b619c(void);
extern void func_ov057_020b626c(void);
extern void data_ov057_020b74a0(void);

asm void func_ov057_020b5f58(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe283402c
    dcd     0xe2841b0b
    bl      func_ov057_020b619c
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov057_020b626c
    dcd     0xe8bd8038
    dcd     data_ov057_020b74a0
}
