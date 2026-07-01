extern void MI_CpuCopy8(void);
extern void func_0203d15c(void);
extern void func_0203d194(void);

asm void func_ov243_020d3bdc(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5950398
    dcd     0xe1a04002
    dcd     0xe3500000
    dcd     0x0a000002
    bl      func_0203d194
    mov r0, #0
    dcd     0xe5850398
    dcd     0xe5941008
    dcd     0xe3a00014
    dcd     0xe0000091
    bl      func_0203d15c
    dcd     0xe5850398
    dcd     0xe5941008
    dcd     0xe3a00014
    dcd     0xe0020091
    dcd     0xe5951398
    dcd     0xe284000c
    bl      MI_CpuCopy8
    dcd     0xe5940008
    dcd     0xe585039c
    dcd     0xe5940000
    dcd     0xe58503a8
    dcd     0xe5940004
    dcd     0xe58503ac
    dcd     0xe8bd8038
}
