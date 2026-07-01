extern void func_ov107_020c9264(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov114_020cd8f8(void);

asm void func_ov114_020cd8a8(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01008
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe594005c
    dcd     0xe5941064
    bl      func_020050b4
    dcd     0xe2800f91
    dcd     0xe2800a03
    dcd     0xe5840018
    dcd     0xe5840014
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov114_020cd8f8
}
