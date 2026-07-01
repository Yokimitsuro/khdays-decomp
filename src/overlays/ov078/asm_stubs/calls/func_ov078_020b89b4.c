extern void func_ov078_020b8d6c(void);
extern void func_ov078_020b8db8(void);
extern void data_ov078_020ba4e0(void);

asm void func_ov078_020b89b4(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340d4
    dcd     0xe2841b0b
    bl      func_ov078_020b8d6c
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov078_020b8db8
    dcd     0xe8bd8038
    dcd     data_ov078_020ba4e0
}
