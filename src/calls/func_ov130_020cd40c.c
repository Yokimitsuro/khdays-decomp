extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern char data_0203d210[];
extern void func_0203c634(void);

asm void func_ov130_020cd40c(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd024
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe59f109c
    dcd     0xe5943024
    dcd     0xe59f0098
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
    dcd     0xe59f206c
    dcd     0xe1a01081
    dcd     0xe1a00080
    dcd     0xe19210f1
    dcd     0xe19220f0
    dcd     0xe28d0000
    bl      MTX_RotY33_
    dcd     0xe5940000
    dcd     0xe28d1000
    dcd     0xe5900390
    dcd     0xe2842018
    dcd     0xe280002c
    bl      MTX_MultVec33
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x128dd024
    dcd     0x18bd8030
    dcd     0xe5940000
    dcd     0xe3a01008
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
