extern void func_020235d0(void);
extern void func_020235e8(void);
extern void func_ov002_020767ec(void);

asm void func_ov014_020801d0(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    bl      func_ov002_020767ec
    dcd     0xe1d401b4
    dcd     0xe5d41016
    bl      func_020235d0
    dcd     0xe1a02000
    dcd     0xe59f1038
    dcd     0xe1d401b4
    dcd     0xe0021001
    dcd     0xe3811002
    dcd     0xe1a02801
    dcd     0xe5d41016
    dcd     0xe1a02822
    bl      func_020235e8
    dcd     0xe1d421b2
    dcd     0xe3a01001
    dcd     0xe3a00003
    dcd     0xe3c22008
    dcd     0xe1c421b2
    dcd     0xe5c41135
    dcd     0xe5c40134
    dcd     0xe8bd8010
    dcd     0xffff0001
}
