extern void func_ov097_020bb168(void);
extern void func_ov097_020bb1b0(void);

asm void func_ov097_020bac0c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe1d12bfa
    dcd     0xe2854084
    dcd     0xe2841b0b
    bl      func_ov097_020bb168
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov097_020bb1b0
    dcd     0xe8bd8038
}
