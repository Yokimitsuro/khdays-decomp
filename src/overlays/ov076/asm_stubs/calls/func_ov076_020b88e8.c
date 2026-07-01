extern void func_ov022_0209145c(void);
extern void func_ov076_020b8908(void);

asm void func_ov076_020b88e8(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe2840a02
    dcd     0xe5900644
    bl      func_ov022_0209145c
    dcd     0xe1a00004
    bl      func_ov076_020b8908
    dcd     0xe8bd8010
}
