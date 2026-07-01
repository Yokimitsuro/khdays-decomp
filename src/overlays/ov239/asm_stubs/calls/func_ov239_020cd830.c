extern void func_01ffa724(void);
extern void func_0203c634(void);

asm void func_ov239_020cd830(void)
{
    dcd     0xe92d4038
    dcd     0xe1a04000
    dcd     0xe5945004
    dcd     0xe285c020
    dcd     0xe2853014
    dcd     0xe89c0007
    dcd     0xe8830007
    dcd     0xe1a0100c
    dcd     0xe1a0200c
    dcd     0xe3a00c0b
    bl      func_01ffa724
    dcd     0xe5950004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x18bd8038
    dcd     0xe5950000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d412d0
    dcd     0xe1a00004
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8038
}
