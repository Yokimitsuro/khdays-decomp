extern void func_ov022_02095524(void);
extern void func_ov081_020b9508(void);

asm void func_ov081_020b9268(void)
{
    dcd     0xe92d4070
    dcd     0xe1a05001
    dcd     0xe5951000
    dcd     0xe1a04002
    dcd     0xe3510000
    dcd     0x0a00000c
    dcd     0xe5902464
    dcd     0xe5901468
    dcd     0xe2022801
    dcd     0xe2011000
    dcd     0xe3510000
    dcd     0x03520000
    dcd     0x1a000005
    dcd     0xe2800fbe
    dcd     0xe2800a02
    bl      func_ov022_02095524
    dcd     0xe3500000
    dcd     0x03a00000
    dcd     0x05850000
    dcd     0xe2856014
    dcd     0xe3a05000
    dcd     0xe1a00006
    dcd     0xe1a01004
    bl      func_ov081_020b9508
    dcd     0xe2855001
    dcd     0xe3550007
    dcd     0xe2866f43
    dcd     0xbafffff8
    dcd     0xe8bd8070
}
