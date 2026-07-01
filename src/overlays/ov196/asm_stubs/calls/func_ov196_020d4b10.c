extern void func_01ffa724(void);
extern void func_0203c634(void);

asm void func_ov196_020d4b10(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe284c024
    dcd     0xe2843018
    dcd     0xe89c0007
    dcd     0xe8830007
    dcd     0xe1a0100c
    dcd     0xe1a0200c
    dcd     0xe3a00c0b
    bl      func_01ffa724
    dcd     0xe5940004
    dcd     0xe5d000ad
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
    dcd     0xe3a00003
    dcd     0xe5840044
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8038
}
