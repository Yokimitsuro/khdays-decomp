extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov144_020cda9c(void);

asm void func_ov144_020cda44(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe5940000
    dcd     0xe5901384
    dcd     0xe5d110ad
    dcd     0xe3510000
    dcd     0x18bd8038
    dcd     0xe3a01004
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe5941000
    dcd     0xe5940048
    dcd     0xe59f2018
    dcd     0xe0810100
    dcd     0xe59013d4
    dcd     0xe1a00005
    dcd     0xe5841038
    dcd     0xe1d512d0
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov144_020cda9c
}
