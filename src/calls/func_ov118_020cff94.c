extern void func_ov107_020c7ca4(void);
extern void func_ov118_020cfe08(void);

asm void func_ov118_020cff94(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe1d406b0
    dcd     0xe1a00c00
    dcd     0xe1a00c20
    dcd     0xe3100080
    dcd     0x1a000001
    dcd     0xe3100001
    dcd     0x1a000001
    dcd     0xe1a00004
    bl      func_ov118_020cfe08
    dcd     0xe1a00004
    bl      func_ov107_020c7ca4
    dcd     0xe8bd8010
}
