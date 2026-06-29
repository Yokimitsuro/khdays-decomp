extern void func_01fff774(void);
extern void func_0202a818(void);
extern void func_0202accc(void);

asm void func_ov035_020b3b5c(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04001
    dcd     0xe5940000
    dcd     0xe3500001
    dcd     0x0a000002
    dcd     0xe3500002
    dcd     0x0a00001d
    dcd     0xe8bd8010
    dcd     0xe594010c
    dcd     0xe0801002
    dcd     0xe584110c
    dcd     0xe5940110
    dcd     0xe1510000
    dcd     0xb8bd8010
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
    dcd     0xe3a00002
    dcd     0xe5840000
    dcd     0xe3a00000
    dcd     0xe584010c
    dcd     0xe8bd8010
    dcd     0xe594010c
    dcd     0xe1a01002
    dcd     0xe0802002
    dcd     0xe2840004
    dcd     0xe584210c
    bl      func_0202a818
    dcd     0xe3500000
    dcd     0x13a00000
    dcd     0x15840000
    dcd     0xe8bd8010
}
