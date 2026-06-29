extern void func_020235d0(void);
extern void func_0202b930(void);
extern void func_0202bedc(void);
extern void func_ov002_0206da70(void);
extern void func_ov014_0207fa40(void);

asm void func_ov014_0207fb04(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe1d401b2
    dcd     0xe5942008
    dcd     0xe3801004
    dcd     0xe2820058
    dcd     0xe1c411b2
    bl      func_ov002_0206da70
    dcd     0xe1a01000
    dcd     0xe284002c
    dcd     0xe3a02001
    dcd     0xe3a03004
    bl      func_0202b930
    dcd     0xe5940038
    dcd     0xe1d411b8
    dcd     0xe3100020
    dcd     0x1a000003
    dcd     0xe1c41bb8
    dcd     0xe1d403bc
    dcd     0xe3800020
    dcd     0xe1c403bc
    dcd     0xe5d411b3
    dcd     0xe1a00004
    bl      func_ov014_0207fa40
    dcd     0xe1d401b4
    dcd     0xe5d41016
    bl      func_020235d0
    dcd     0xe3100001
    dcd     0x13a01001
    dcd     0x03a01000
    dcd     0xe284002c
    bl      func_0202bedc
    dcd     0xe8bd8010
}
