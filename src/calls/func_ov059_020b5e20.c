extern char data_ov059_020b7320[];
extern void func_ov059_020b61c0(void);
extern void func_ov059_020b61fc(void);

asm void func_ov059_020b5e20(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe2834ec5
    dcd     0xe2841a02
    bl      func_ov059_020b61c0
    dcd     0xe1a00005
    dcd     0xe2841a02
    bl      func_ov059_020b61fc
    dcd     0xe8bd8038
    dcd     data_ov059_020b7320
}
