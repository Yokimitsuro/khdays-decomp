extern void func_ov107_020c9264(void);
extern void func_ov107_020c0b90(void);
extern void func_0203c634(void);
extern void data_02041dc8(void);
extern void func_ov281_020cde7c(void);

asm void func_ov281_020cde14(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd008
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a0100b
    dcd     0xe5940000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe3a01000
    dcd     0xe59f0034
    dcd     0xe58d1004
    dcd     0xe24d3008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940000
    dcd     0xe3a01005
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    dcd     0xe1d512d0
    dcd     0xe59f2010
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd008
    dcd     0xe8bd8038
    dcd     data_02041dc8
    dcd     func_ov281_020cde7c
}
