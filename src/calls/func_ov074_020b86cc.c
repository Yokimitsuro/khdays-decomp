extern char data_ov074_020b9b80[];
extern void func_ov074_020b89f4(void);
extern void func_ov074_020b8a04(void);

asm void func_ov074_020b86cc(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340a4
    dcd     0xe2841b0b
    bl      func_ov074_020b89f4
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov074_020b8a04
    dcd     0xe8bd8038
    dcd     data_ov074_020b9b80
}
