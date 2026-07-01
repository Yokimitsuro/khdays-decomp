extern char data_ov086_020b9a60[];
extern void func_ov086_020b893c(void);
extern void func_ov086_020b8974(void);

asm void func_ov086_020b8730(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe283402c
    dcd     0xe2841b0b
    bl      func_ov086_020b893c
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov086_020b8974
    dcd     0xe8bd8038
    dcd     data_ov086_020b9a60
}
