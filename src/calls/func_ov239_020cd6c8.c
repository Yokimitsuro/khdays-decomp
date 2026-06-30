extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void func_0203c634(void);
extern void data_0203d210(void);

asm void func_ov239_020cd6c8(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd024
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe59f10c8
    dcd     0xe5943010
    dcd     0xe59f00c4
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
    dcd     0xe59f2098
    dcd     0xe1a01081
    dcd     0xe1a00080
    dcd     0xe19210f1
    dcd     0xe19220f0
    dcd     0xe28d0000
    bl      MTX_RotY33_
    dcd     0xe5940000
    dcd     0xe28d1000
    dcd     0xe5900398
    dcd     0xe2842014
    dcd     0xe280002c
    bl      MTX_MultVec33
    dcd     0xe5942000
    dcd     0xe1d216b0
    dcd     0xe1a00801
    dcd     0xe1a00c20
    dcd     0xe3c00040
    dcd     0xe1a00800
    dcd     0xe1a00820
    dcd     0xe3c11cff
    dcd     0xe1a00c00
    dcd     0xe1810820
    dcd     0xe1c206b0
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x128dd024
    dcd     0x18bd8030
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd024
    dcd     0xe8bd8030
    dcd     0x000028be
    dcd     0x60db9391
    dcd     data_0203d210
}
