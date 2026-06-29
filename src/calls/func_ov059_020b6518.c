extern void func_01fff774(void);
extern void func_0202accc(void);

asm void func_ov059_020b6518(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04001
    dcd     0xe3a00001
    dcd     0xe3a01000
    dcd     0xe5840234
    dcd     0xe1a03001
    dcd     0xe2840f8e
    dcd     0xe2842fc6
    dcd     0xe5841230
    bl      func_0202accc
    dcd     0xe2840f8e
    dcd     0xe2842fc6
    dcd     0xe3a01002
    dcd     0xe3a03000
    bl      func_0202accc
    dcd     0xe3a01000
    dcd     0xe1a02001
    dcd     0xe2840f8e
    bl      func_01fff774
    dcd     0xe2840f8e
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe8bd8010
}
