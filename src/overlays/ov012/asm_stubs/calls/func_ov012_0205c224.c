extern void func_ov012_0205c048(void);
extern void func_ov012_0205c0e0(void);
extern void func_ov012_0205c1d4(void);

asm void func_ov012_0205c224(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5841074
    bl      func_ov012_0205c048
    dcd     0xe1a00004
    bl      func_ov012_0205c1d4
    dcd     0xe3500000
    dcd     0x0a000005
    dcd     0xe1a00004
    bl      func_ov012_0205c0e0
    dcd     0xe1a00004
    bl      func_ov012_0205c1d4
    dcd     0xe3500000
    dcd     0x1afffff9
    mov r0, #0
    dcd     0xe5840074
    dcd     0xe5840064
    dcd     0xe584006c
    mov r0, #1
    dcd     0xe5840050
    dcd     0xe8bd8010
}
