extern void func_0203c7e8(void);
extern void func_0203d194(void);
extern void func_ov107_020c68ec(void);
extern void func_ov107_020c9eac(void);

asm void func_ov243_020d3b18(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe5940384
    bl      func_0203c7e8
    dcd     0xe5940390
    bl      func_ov107_020c9eac
    dcd     0xe5940388
    bl      func_0203c7e8
    dcd     0xe5940394
    bl      func_0203c7e8
    dcd     0xe5940398
    dcd     0xe3500000
    dcd     0x0a000002
    bl      func_0203d194
    mov r0, #0
    dcd     0xe5840398
    dcd     0xe1a00004
    bl      func_ov107_020c68ec
    dcd     0xe8bd8010
}
