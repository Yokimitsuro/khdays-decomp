extern void func_ov022_0209145c(void);
extern void func_ov056_020b6228(void);

asm void func_ov056_020b6208(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe2840a02
    dcd     0xe5900644
    bl      func_ov022_0209145c
    dcd     0xe1a00004
    bl      func_ov056_020b6228
    dcd     0xe8bd8010
}
