extern void func_01fff774(void);
extern void func_0202accc(void);

asm void func_ov037_020b459c(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04001
    dcd     0xe3a01000
    dcd     0xe3a0c002
    dcd     0xe1a03001
    dcd     0xe2840e12
    dcd     0xe2842c02
    dcd     0xe584c11c
    bl      func_0202accc
    dcd     0xe2840e12
    dcd     0xe2842c02
    dcd     0xe3a01002
    dcd     0xe3a03000
    bl      func_0202accc
    dcd     0xe2840e12
    dcd     0xe2842c02
    dcd     0xe3a01001
    dcd     0xe3a03000
    bl      func_0202accc
    dcd     0xe3a01000
    dcd     0xe2840e12
    dcd     0xe1a02001
    bl      func_01fff774
    dcd     0xe2840e12
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe2840e12
    dcd     0xe3a01001
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe8bd8010
}
