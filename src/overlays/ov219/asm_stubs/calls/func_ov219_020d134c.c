extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c0b90(void);
extern void func_0203c634(void);
extern void data_0203d210(void);
extern void data_02041dc8(void);
extern void func_ov219_020d14dc(void);

asm void func_ov219_020d134c(void)
{
    dcd     0xe92d40f0
    dcd     0xe24dd02c
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe59f1164
    dcd     0xe594300c
    dcd     0xe59f0160
    dcd     0xe1a02fc3
    dcd     0xe0867093
    dcd     0xe0266193
    dcd     0xe0266092
    dcd     0xe2970000
    dcd     0xe2a60b02
    dcd     0xe1a00200
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a01080
    dcd     0xe2810001
    dcd     0xe59f2134
    dcd     0xe1a01081
    dcd     0xe1a00080
    dcd     0xe19210f1
    dcd     0xe19220f0
    dcd     0xe28d0008
    bl      MTX_RotY33_
    dcd     0xe5940000
    dcd     0xe28d1008
    dcd     0xe5900394
    dcd     0xe2842024
    dcd     0xe280002c
    bl      MTX_MultVec33
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x128dd02c
    dcd     0x18bd80f0
    dcd     0xe5940000
    dcd     0xe3a01007
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    dcd     0xe3a01000
    dcd     0xe59f00dc
    dcd     0xe58d1004
    dcd     0xe24d3008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    dcd     0xe5941000
    dcd     0xe2810c01
    dcd     0xe1d00cd6
    dcd     0xe3500008
    dcd     0x03a00a07
    dcd     0x05840014
    dcd     0x0a00001d
    dcd     0xe2810c02
    dcd     0xe1d001fa
    dcd     0xe3500000
    dcd     0xc3a00a03
    dcd     0xc5840014
    dcd     0xca000017
    dcd     0xe3a00a4b
    dcd     0xe5840014
    dcd     0xe5941018
    mov r0, #0
    dcd     0xe3510000
    dcd     0xda000011
    dcd     0xe1a02000
    dcd     0xe3a01b06
    dcd     0xe1a0c000
    dcd     0xe3a03b02
    dcd     0xe594e014
    dcd     0xe2800001
    dcd     0xe086719e
    dcd     0xe026629e
    dcd     0xe1a0efce
    dcd     0xe0977003
    dcd     0xe026619e
    dcd     0xe0a6600c
    dcd     0xe1a07627
    dcd     0xe1877a06
    dcd     0xe5847014
    dcd     0xe594e018
    dcd     0xe150000e
    dcd     0xbafffff1
    mov r0, #0
    dcd     0xe5c4003e
    dcd     0xe1d512d0
    dcd     0xe59f201c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd02c
    dcd     0xe8bd80f0
    dcd     0x000028be
    dcd     0x60db9391
    dcd     data_0203d210
    dcd     data_02041dc8
    dcd     func_ov219_020d14dc
}
