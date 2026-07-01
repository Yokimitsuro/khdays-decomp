extern void func_01ffa724(void);
extern void VEC_Mag(void);
extern void func_0203c634(void);

asm void func_ov293_020d2bfc(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe284c034
    dcd     0xe284301c
    dcd     0xe89c0007
    dcd     0xe8830007
    dcd     0xe1a0100c
    dcd     0xe1a0200c
    dcd     0xe3a00c0a
    bl      func_01ffa724
    dcd     0xe594004c
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x18bd8038
    dcd     0xe5941000
    dcd     0xe5d1017a
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x1a000003
    dcd     0xe5d1017c
    dcd     0xe1a00f80
    dcd     0xe1b00fa0
    dcd     0x08bd8038
    dcd     0xe2840034
    bl      VEC_Mag
    dcd     0xe3500010
    dcd     0xc8bd8038
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8038
}
