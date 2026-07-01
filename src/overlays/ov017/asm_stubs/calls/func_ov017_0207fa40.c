extern void func_ov002_0207c618(void);
extern void func_0202af1c(void);

asm void func_ov017_0207fa40(void)
{
    dcd     0xe92d4010
    dcd     0xe59dc008
    dcd     0xe58034cc
    dcd     0xe580c4c8
    dcd     0xe1d001b2
    dcd     0xe1a04001
    dcd     0xe3100004
    dcd     0x08bd8010
    dcd     0xe1a01002
    dcd     0xe1a00004
    dcd     0xe3a02000
    bl      func_ov002_0207c618
    dcd     0xe1a00004
    bl      func_0202af1c
    dcd     0xe8bd8010
}
