extern void func_ov107_020cab14(void);
extern void func_0203c634(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_0202f384(void);
extern void func_ov107_020c5af8(void);
extern void func_ov155_020d3d94(void);
extern void data_02042258(void);

asm void func_ov155_020d5744(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd018
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe5840018
    dcd     0xe3500000
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd8038
    dcd     0xe5941004
    dcd     0xe28d200c
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe59d000c
    dcd     0xe59d1014
    bl      func_020050b4
    dcd     0xe5840014
    dcd     0xe5951000
    dcd     0xe3a0001e
    dcd     0xe591102c
    dcd     0xe59f20c0
    dcd     0xe0030091
    dcd     0xe1a00fa3
    dcd     0xe0c31392
    dcd     0xe0803243
    dcd     0xe5843020
    dcd     0xe5950000
    dcd     0xe594101c
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe584001c
    dcd     0xe5d40024
    dcd     0xe3500000
    dcd     0x1a000015
    dcd     0xe594001c
    dcd     0xe15009a2
    dcd     0xba000012
    mov r0, #1
    dcd     0xe5c40024
    dcd     0xe5941000
    dcd     0xe59f2074
    dcd     0xe28d0000
    dcd     0xe28110a0
    bl      func_0202f384
    dcd     0xe5940000
    dcd     0xe3a01f4f
    dcd     0xe590338c
    dcd     0xe3a02004
    dcd     0xe2833014
    bl      func_ov107_020c5af8
    dcd     0xe5940000
    dcd     0xe28d2000
    dcd     0xe590138c
    dcd     0xe5900398
    dcd     0xe2811014
    bl      func_ov155_020d3d94
    dcd     0xe594000c
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x128dd018
    dcd     0x18bd8038
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd8038
    dcd     0x66666667
    dcd     data_02042258
}
