extern void MI_CpuCopy8(void);
extern void func_0203d15c(void);
extern void func_0203d194(void);

asm void func_ov291_020cc550(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe59603a0
    dcd     0xe1a05001
    dcd     0xe1a04002
    dcd     0xe3500000
    dcd     0x0a000002
    bl      func_0203d194
    dcd     0xe3a00000
    dcd     0xe58603a0
    dcd     0xe1a00005
    bl      func_0203d15c
    dcd     0xe58603a0
    dcd     0xe1a01000
    dcd     0xe1a00004
    dcd     0xe1a02005
    bl      MI_CpuCopy8
    dcd     0xe5940000
    dcd     0xe58603a4
    dcd     0xe5940004
    dcd     0xe58603a8
    dcd     0xe8bd8070
}
