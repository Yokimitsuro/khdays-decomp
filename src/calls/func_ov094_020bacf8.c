extern void func_ov094_020baf3c(void);
extern void func_ov094_020bb00c(void);
extern void data_ov094_020bc240(void);

asm void func_ov094_020bacf8(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe283402c
    dcd     0xe2841b0b
    bl      func_ov094_020baf3c
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov094_020bb00c
    dcd     0xe8bd8038
    dcd     data_ov094_020bc240
}
