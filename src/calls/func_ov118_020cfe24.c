extern void func_ov107_020c7500(void);
extern void func_ov107_020cb040(void);
extern void func_ov118_020cfe08(void);

asm void func_ov118_020cfe24(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd004
    dcd     0xe1a05001
    dcd     0xe5d51002
    dcd     0xe1a06000
    dcd     0xe1a04002
    dcd     0xe3510005
    dcd     0x1a00000e
    dcd     0xe5d51003
    dcd     0xe3510000
    dcd     0x1a00000b
    dcd     0xe5961390
    dcd     0xe3510000
    dcd     0x1a000007
    dcd     0xe28610a0
    dcd     0xe58d1000
    dcd     0xe3a01e12
    dcd     0xe3a02005
    dcd     0xe3a03001
    bl      func_ov107_020cb040
    dcd     0xe5860390
    dcd     0xea000000
    bl      func_ov118_020cfe08
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov107_020c7500
    dcd     0xe28dd004
    dcd     0xe8bd8078
}
