extern char data_ov076_020b9d00[];
extern void func_ov076_020b9240(void);
extern void func_ov076_020b943c(void);

asm void func_ov076_020b8610(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe283402c
    dcd     0xe2841b0b
    bl      func_ov076_020b9240
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov076_020b943c
    dcd     0xe8bd8038
    dcd     data_ov076_020b9d00
}
