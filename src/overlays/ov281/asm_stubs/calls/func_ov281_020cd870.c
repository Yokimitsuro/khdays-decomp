extern void func_ov107_020c0b90(void);
extern void func_ov281_020ccae4(void);
extern void func_ov107_020cab14(void);
extern void func_0203c634(void);
extern void data_02041dc8(void);

asm void func_ov281_020cd870(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd008
    dcd     0xe1a05000
    dcd     0xe8950011
    dcd     0xe5941018
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe5840018
    dcd     0xe5d4003c
    dcd     0xe3500000
    dcd     0x1a00000f
    dcd     0xe5941018
    dcd     0xe59f00dc
    dcd     0xe1510000
    dcd     0xba00000b
    dcd     0xe3a01000
    dcd     0xe59f00d0
    dcd     0xe58d1004
    dcd     0xe24d3008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940000
    dcd     0xe3a01001
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    mov r0, #1
    dcd     0xe5c4003c
    dcd     0xe5941018
    dcd     0xe59f009c
    dcd     0xe1510000
    dcd     0xba000008
    dcd     0xe3a00b02
    dcd     0xe58d0000
    dcd     0xe5940000
    dcd     0xe3a01000
    dcd     0xe59033ac
    dcd     0xe1a00004
    dcd     0xe1a02001
    dcd     0xe2833014
    bl      func_ov281_020ccae4
    dcd     0xe5940000
    dcd     0xe3a01000
    bl      func_ov107_020cab14
    dcd     0xe5840008
    dcd     0xe3500000
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd008
    dcd     0xe8bd8038
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x128dd008
    dcd     0x18bd8038
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd008
    dcd     0xe8bd8038
    dcd     0x00000555
    dcd     data_02041dc8
}
