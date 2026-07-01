extern void func_01fff774(void);
extern void func_0202accc(void);

asm void func_ov083_020b90a8(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04001
    dcd     0xe1d400d0
    dcd     0xe3500000
    dcd     0x0a000005
    dcd     0xe2400004
    dcd     0xe1a00c00
    dcd     0xe1a00c40
    dcd     0xe20000ff
    dcd     0xe3500001
    dcd     0x88bd8010
    dcd     0xe3a01000
    dcd     0xe1a03001
    dcd     0xe2840004
    dcd     0xe28420e4
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
    dcd     0xe3a00000
    dcd     0xe584010c
    dcd     0xe5840110
    dcd     0xe3a00001
    dcd     0xe5c40000
    dcd     0xe8bd8010
}
