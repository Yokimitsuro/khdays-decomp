extern void func_ov107_020c9264(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_0203c634(void);
extern void func_ov240_020cedbc(void);

asm void func_ov240_020ced2c(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd008
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01000
    dcd     0xe5940000
    dcd     0xe1a02001
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe3a0c000
    dcd     0xe2800c01
    dcd     0xe1d01abe
    dcd     0xe24d3008
    dcd     0xe3811001
    dcd     0xe1c01abe
    dcd     0xe58dc004
    dcd     0xe5940008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940000
    dcd     0xe1a0100c
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    dcd     0xe5940000
    dcd     0xe59f1020
    dcd     0xe3a0200b
    dcd     0xe2803074
    bl      func_ov107_020c5af8
    dcd     0xe1a00005
    dcd     0xe1d512d0
    dcd     0xe59f200c
    bl      func_0203c634
    dcd     0xe28dd008
    dcd     0xe8bd8038
    dcd     0x00000139
    dcd     func_ov240_020cedbc
}
