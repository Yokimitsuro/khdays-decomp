extern void func_ov080_020b8aa8(void);
extern void func_ov080_020b8af0(void);

asm void func_ov080_020b854c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe1d12bfa
    dcd     0xe2854084
    dcd     0xe2841b0b
    bl      func_ov080_020b8aa8
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov080_020b8af0
    dcd     0xe8bd8038
}
