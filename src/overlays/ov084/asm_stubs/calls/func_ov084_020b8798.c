extern char data_ov084_020b9a20[];
extern void func_ov084_020b8f68(void);
extern void func_ov084_020b9024(void);

asm void func_ov084_020b8798(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe59f2020
    dcd     0xe2851c2a
    dcd     0xe5924000
    dcd     0xe1d12bfa
    dcd     0xe2841db2
    bl      func_ov084_020b8f68
    dcd     0xe1a00005
    dcd     0xe2841db2
    bl      func_ov084_020b9024
    dcd     0xe8bd8038
    dcd     data_ov084_020b9a20
}
