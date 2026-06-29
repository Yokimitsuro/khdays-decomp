extern void func_ov080_020b8c64(void);
extern void func_ov080_020b8fbc(void);
extern void func_ov080_020b9104(void);
extern void func_ov080_020b927c(void);

asm void func_ov080_020b8af0(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a07000
    dcd     0xe5d72694
    dcd     0xe1a06001
    dcd     0xe1a02f82
    dcd     0xe1b02fa2
    dcd     0x08bd80f8
    bl      func_ov080_020b8c64
    dcd     0xe2865e33
    dcd     0xe3a04000
    dcd     0xe1a00007
    dcd     0xe1a01005
    bl      func_ov080_020b8fbc
    dcd     0xe2844001
    dcd     0xe3540003
    dcd     0xe2855e11
    dcd     0xbafffff8
    dcd     0xe1a00007
    dcd     0xe2861e11
    bl      func_ov080_020b9104
    dcd     0xe1a00007
    dcd     0xe2861e22
    bl      func_ov080_020b927c
    dcd     0xe8bd80f8
}
