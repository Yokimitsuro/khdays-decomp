extern char data_ov048_020b4b80[];
extern void func_ov048_020b3a5c(void);
extern void func_ov048_020b3a94(void);

asm void func_ov048_020b3850(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe283402c
    dcd     0xe2841b0b
    bl      func_ov048_020b3a5c
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov048_020b3a94
    dcd     0xe8bd8038
    dcd     data_ov048_020b4b80
}
