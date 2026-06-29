extern char data_ov073_020ba540[];
extern void func_ov073_020ba1fc(void);
extern void func_ov073_020ba370(void);

asm void func_ov073_020b8b50(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2028
    dcd     0xe1a05000
    dcd     0xe2851c2a
    dcd     0xe5923000
    dcd     0xe1d12bfa
    dcd     0xe28340e4
    dcd     0xe2841b0b
    bl      func_ov073_020ba1fc
    dcd     0xe1a00005
    dcd     0xe2841b0b
    bl      func_ov073_020ba370
    dcd     0xe8bd8038
    dcd     data_ov073_020ba540
}
