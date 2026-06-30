extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_ov281_020ccae4(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void data_0203d210(void);
extern void data_02041dc8(void);
extern void func_ov281_020cdb9c(void);

asm void func_ov281_020cda08(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd03c
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe59f1164
    dcd     0xe5943010
    dcd     0xe59f0160
    dcd     0xe1a02fc3
    dcd     0xe08ce093
    dcd     0xe02cc193
    dcd     0xe02cc092
    dcd     0xe29e0000
    dcd     0xe2ac0b02
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
    dcd     0xe28d0018
    bl      MTX_RotY33_
    dcd     0xe5940000
    dcd     0xe28d1018
    dcd     0xe59003c0
    dcd     0xe2842020
    dcd     0xe280002c
    bl      MTX_MultVec33
    dcd     0xe5950000
    dcd     0xe5941018
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe5840018
    dcd     0xe5d4003c
    dcd     0xe3500000
    dcd     0x1a000013
    dcd     0xe5940018
    dcd     0xe3500faa
    dcd     0xba000010
    dcd     0xe3a01001
    dcd     0xe59f00d4
    dcd     0xe5c4103c
    dcd     0xe3a01000
    dcd     0xe58d1004
    dcd     0xe24d3008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    dcd     0xe5940000
    dcd     0xe594300c
    dcd     0xe59f10a4
    dcd     0xe3a02004
    bl      func_ov107_020c5af8
    dcd     0xe5940018
    dcd     0xe3500eff
    dcd     0xba000011
    dcd     0xe5940000
    dcd     0xe28de008
    dcd     0xe2800074
    dcd     0xe890000f
    dcd     0xe88e000f
    dcd     0xe3a0ca01
    dcd     0xe1a00004
    dcd     0xe1a0200e
    dcd     0xe3a01001
    dcd     0xe3a03000
    dcd     0xe58dc000
    bl      func_ov281_020ccae4
    dcd     0xe3500000
    dcd     0x0a000003
    dcd     0xe59f0050
    dcd     0xe2843020
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x128dd03c
    dcd     0x18bd8030
    dcd     0xe5940000
    dcd     0xe3a01006
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe1d512d0
    dcd     0xe59f2020
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd03c
    dcd     0xe8bd8030
    dcd     0x000028be
    dcd     0x60db9391
    dcd     data_0203d210
    dcd     data_02041dc8
    dcd     0x00000169
    dcd     func_ov281_020cdb9c
}
