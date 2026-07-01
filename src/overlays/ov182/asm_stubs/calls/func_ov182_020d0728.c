extern void FX_Inv(void);
extern void func_0203c634(void);

asm void func_ov182_020d0728(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe8950011
    dcd     0xe594201c
    dcd     0xe590002c
    dcd     0xe59f1058
    dcd     0xe0820000
    dcd     0xe584001c
    bl      FX_Inv
    dcd     0xe5941000
    dcd     0xe2600a01
    dcd     0xe5810394
    dcd     0xe5941000
    dcd     0xe5910394
    dcd     0xe35000cc
    dcd     0xb3a000cc
    dcd     0xb5810394
    dcd     0xe594101c
    dcd     0xe59f0024
    dcd     0xe1510000
    dcd     0xb8bd8038
    dcd     0xe5940000
    dcd     0xe3a0100c
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0x00000555
}
