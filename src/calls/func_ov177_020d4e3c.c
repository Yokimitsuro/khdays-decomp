extern void func_ov107_020c9264(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov177_020d4e80(void);

asm void func_ov177_020d4e3c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01001
    dcd     0xe5940000
    dcd     0xe1a02001
    bl      func_ov107_020c9264
    dcd     0xe3a00001
    bl      func_02023eb4
    dcd     0xe2800078
    dcd     0xe5840054
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov177_020d4e80
}
