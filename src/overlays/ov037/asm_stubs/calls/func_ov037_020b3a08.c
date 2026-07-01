extern void func_ov022_0209145c(void);
extern void func_ov037_020b3a28(void);

asm void func_ov037_020b3a08(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe2840a02
    dcd     0xe5900644
    bl      func_ov022_0209145c
    dcd     0xe1a00004
    bl      func_ov037_020b3a28
    dcd     0xe8bd8010
}
