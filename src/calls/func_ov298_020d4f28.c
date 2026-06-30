extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void VEC_DotProduct(void);
extern void func_020050b4(void);
extern void func_02023eb4(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void data_0203d210(void);
extern void func_ov298_020d5034(void);

asm void func_ov298_020d4f28(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd018
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a00c09
    dcd     0xe5840050
    dcd     0xe594000c
    dcd     0xe3500000
    dcd     0x0a000027
    dcd     0xe594202c
    dcd     0xe59f00cc
    dcd     0xe59f10cc
    dcd     0xe083c092
    dcd     0xe0233192
    dcd     0xe1a01fc2
    dcd     0xe0233091
    dcd     0xe29c0000
    dcd     0xe2a30b02
    dcd     0xe1a00200
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a02080
    dcd     0xe2820001
    dcd     0xe3a01000
    dcd     0xe59f309c
    dcd     0xe1a02082
    dcd     0xe1a00080
    dcd     0xe19320f2
    dcd     0xe19300f0
    dcd     0xe58d1010
    dcd     0xe58d200c
    dcd     0xe58d0014
    dcd     0xe594000c
    dcd     0xe5941000
    dcd     0xe28d2000
    dcd     0xe2800074
    dcd     0xe2811074
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe28d000c
    dcd     0xe28d1000
    bl      VEC_DotProduct
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5840030
    dcd     0xe584002c
    dcd     0xe5944000
    dcd     0xe3a00002
    bl      func_02023eb4
    dcd     0xe1a01000
    dcd     0xe1a00004
    dcd     0xe2811005
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe1d512d0
    dcd     0xe59f2018
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd8038
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
    dcd     func_ov298_020d5034
}
