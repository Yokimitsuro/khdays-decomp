extern void func_0202accc(void);
extern void func_01fff774(void);

asm void func_ov057_020b6600(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04001
    dcd     0xe3a01000
    dcd     0xe3a0c001
    dcd     0xe1a03001
    dcd     0xe2840004
    dcd     0xe28420e4
    dcd     0xe584c000
    bl      func_0202accc
    dcd     0xe2840004
    dcd     0xe28420e4
    dcd     0xe3a01002
    dcd     0xe3a03000
    bl      func_0202accc
    dcd     0xe3a01000
    dcd     0xe1a02001
    dcd     0xe2840004
    bl      func_01fff774
    dcd     0xe2840004
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe8bd8010
}
