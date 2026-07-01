extern char data_ov065_020b7340[];
extern void func_ov065_020b6888(void);
extern void func_ov065_020b6944(void);

asm void func_ov065_020b60b8(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe59f2020
    dcd     0xe2851c2a
    dcd     0xe5924000
    dcd     0xe1d12bfa
    dcd     0xe2841db2
    bl      func_ov065_020b6888
    dcd     0xe1a00005
    dcd     0xe2841db2
    bl      func_ov065_020b6944
    dcd     0xe8bd8038
    dcd     data_ov065_020b7340
}
