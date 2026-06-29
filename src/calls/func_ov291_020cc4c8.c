extern void func_0203c7e8(void);
extern void func_0203d194(void);
extern void func_ov107_020c68ec(void);
extern void func_ov107_020c9eac(void);

asm void func_ov291_020cc4c8(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe59403a0
    dcd     0xe3500000
    dcd     0x0a000000
    bl      func_0203d194
    dcd     0xe5940384
    bl      func_0203c7e8
    dcd     0xe5940394
    bl      func_ov107_020c9eac
    dcd     0xe5940388
    bl      func_0203c7e8
    dcd     0xe5940398
    bl      func_0203c7e8
    dcd     0xe1a00004
    bl      func_ov107_020c68ec
    dcd     0xe8bd8010
}
