extern void func_ov107_020c5c54(void);
extern void func_ov299_020d410c(void);

asm void func_ov299_020d3d68(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe1a05002
    dcd     0xe1a04003
    bl      func_ov107_020c5c54
    dcd     0xe5960050
    dcd     0xe3500001
    dcd     0x18bd8070
    dcd     0xe5960214
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov299_020d410c
    dcd     0xe8bd8070
}
