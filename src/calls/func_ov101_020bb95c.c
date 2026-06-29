extern void func_01fff774(void);
extern void func_0202accc(void);

asm void func_ov101_020bb95c(void)
{
    dcd     0xe92d4038
    dcd     0xe3a04000
    dcd     0xe1a05001
    dcd     0xe1a02004
    dcd     0xe2803f4a
    dcd     0xe5901128
    dcd     0xe2822001
    dcd     0xe3510000
    dcd     0x01a04003
    dcd     0xe3520006
    dcd     0xe2800e12
    dcd     0xe2833e12
    dcd     0xbafffff7
    dcd     0xe3540000
    dcd     0x08bd8038
    dcd     0xe3a00001
    dcd     0xe3a01000
    dcd     0xe5840000
    dcd     0xe1a03001
    dcd     0xe2840004
    dcd     0xe28420e4
    dcd     0xe584110c
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
    dcd     0xe3a01000
    dcd     0xe1a02001
    dcd     0xe2840004
    bl      func_01fff774
    dcd     0xe28430a8
    dcd     0xe8950007
    dcd     0xe8830007
    dcd     0xe8bd8038
}
