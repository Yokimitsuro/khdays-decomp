extern void func_0203d194(void);
extern void func_0203d15c(void);
extern void MI_CpuCopy8(void);
extern void func_ov262_020d3ec8(void);
extern void func_ov262_020d3ee8(void);
extern void func_ov262_020d3f08(void);
extern void func_ov262_020d3f28(void);

asm void func_ov262_020d3e4c(void)
{
    dcd     0xe92d4070
    dcd     0xe1a06000
    dcd     0xe59603a0
    dcd     0xe1a05001
    dcd     0xe1a04002
    dcd     0xe3500000
    dcd     0x0a000003
    bl      func_0203d194
    mov r0, #0
    dcd     0xe58603a0
    dcd     0xe586039c
    dcd     0xe1a00005
    bl      func_0203d15c
    dcd     0xe58603a0
    dcd     0xe1a01000
    dcd     0xe1a00004
    dcd     0xe1a02005
    bl      MI_CpuCopy8
    dcd     0xe59f101c
    dcd     0xe59f001c
    dcd     0xe5841004
    dcd     0xe5840008
    dcd     0xe59f1014
    dcd     0xe59f0014
    dcd     0xe584100c
    dcd     0xe5840010
    dcd     0xe8bd8070
    dcd     func_ov262_020d3ec8
    dcd     func_ov262_020d3ee8
    dcd     func_ov262_020d3f08
    dcd     func_ov262_020d3f28
}
