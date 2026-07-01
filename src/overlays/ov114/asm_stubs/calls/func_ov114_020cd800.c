extern void FX_Inv(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);

asm void func_ov114_020cd800(void)
{
    dcd     0xe92d4070
    dcd     0xe1a05000
    dcd     0xe8950011
    dcd     0xe5942044
    dcd     0xe590002c
    dcd     0xe59f1088
    dcd     0xe0820000
    dcd     0xe5840044
    bl      FX_Inv
    dcd     0xe5941000
    dcd     0xe28000cc
    dcd     0xe5810390
    dcd     0xe5941000
    dcd     0xe5910390
    dcd     0xe3500a01
    dcd     0xc3a00a01
    dcd     0xc5810390
    dcd     0xe594000c
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x18bd8070
    dcd     0xe5940000
    dcd     0xe3a01a01
    dcd     0xe5801390
    dcd     0xe5940000
    dcd     0xe5906224
    dcd     0xe5900228
    dcd     0xe0500006
    dcd     0x42600000
    dcd     0xe2800001
    bl      func_02023eb4
    dcd     0xe0860000
    dcd     0xe584004c
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8070
    dcd     0x000002aa
}
