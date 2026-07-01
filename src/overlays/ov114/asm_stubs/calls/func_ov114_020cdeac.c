extern void FX_Inv(void);
extern void func_0203c634(void);

asm void func_ov114_020cdeac(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe8950011
    dcd     0xe5941044
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe5840044
    dcd     0xe3500b01
    dcd     0xba00000a
    dcd     0xe59f1060
    dcd     0xe2400b01
    bl      FX_Inv
    dcd     0xe5941000
    dcd     0xe2600a01
    dcd     0xe5810390
    dcd     0xe5941000
    dcd     0xe5910390
    dcd     0xe35000cc
    dcd     0xb3a000cc
    dcd     0xb5810390
    dcd     0xe594000c
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x18bd8038
    dcd     0xe5940000
    dcd     0xe3a010cc
    dcd     0xe5801390
    dcd     0xe5940000
    dcd     0xe3a0100c
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0x000002aa
}
