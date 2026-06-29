extern void func_ov107_020c7da4(void);
extern void func_ov118_020cfe08(void);

asm void func_ov118_020cfe98(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    bl      func_ov118_020cfe08
    dcd     0xe1a00004
    bl      func_ov107_020c7da4
    dcd     0xe8bd8010
}
