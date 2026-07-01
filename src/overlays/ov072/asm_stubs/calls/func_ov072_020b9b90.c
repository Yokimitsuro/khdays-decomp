extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Add(void);
extern char data_0203d210[];
extern void func_0202aa9c(void);

asm void func_ov072_020b9b90(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd030
    dcd     0xe1a04001
    dcd     0xe5d41114
    dcd     0xe1a05000
    dcd     0xe3510000
    dcd     0x028dd030
    dcd     0x08bd8038
    dcd     0xe5d50694
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x028dd030
    dcd     0x08bd8038
    dcd     0xe3510002
    dcd     0x13510004
    dcd     0x128dd030
    dcd     0x18bd8038
    dcd     0xe5953488
    dcd     0xe59f2098
    dcd     0xe1a00243
    dcd     0xe1a01080
    dcd     0xe2830902
    dcd     0xe1c408b8
    dcd     0xe2810001
    dcd     0xe1a01081
    dcd     0xe19210f1
    dcd     0xe1a00080
    dcd     0xe19220f0
    dcd     0xe1d430bc
    dcd     0xe59fc070
    dcd     0xe3a0ef52
    dcd     0xe3830020
    dcd     0xe1c400bc
    dcd     0xe59f3064
    dcd     0xe28d000c
    dcd     0xe2611000
    dcd     0xe2622000
    dcd     0xe58de000
    dcd     0xe58dc004
    dcd     0xe58d3008
    bl      MTX_RotY33_
    dcd     0xe28d0000
    dcd     0xe28d100c
    dcd     0xe1a02000
    bl      MTX_MultVec33
    dcd     0xe28d0000
    dcd     0xe285108c
    dcd     0xe1a02000
    dcd     0xe2811b01
    bl      VEC_Add
    dcd     0xe28d0000
    dcd     0xe28430b0
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe284000c
    bl      func_0202aa9c
    dcd     0xe28dd030
    dcd     0xe8bd8038
    dcd     data_0203d210
    dcd     0x00001429
    dcd     0x000006e1
}
