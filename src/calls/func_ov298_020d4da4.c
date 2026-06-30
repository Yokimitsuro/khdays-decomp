extern void func_01ffa724(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov298_020d4e1c(void);

asm void func_ov298_020d4da4(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe284c01c
    dcd     0xe2843010
    dcd     0xe89c0007
    dcd     0xe8830007
    dcd     0xe594004c
    dcd     0xe1a0100c
    dcd     0xe5840014
    dcd     0xe594004c
    dcd     0xe1a0200c
    dcd     0xe2400080
    dcd     0xe584004c
    dcd     0xe3a00c0e
    bl      func_01ffa724
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x18bd8038
    dcd     0xe5940000
    dcd     0xe3a01003
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe1d512d0
    dcd     0xe59f2008
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov298_020d4e1c
}
