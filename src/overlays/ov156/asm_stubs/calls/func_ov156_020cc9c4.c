extern void VEC_Add(void);
extern void func_01ffd144(void);
extern void func_01fff888(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);

asm void func_ov156_020cc9c4(void)
{
    dcd     0xe92d4070
    dcd     0xe24dd020
    dcd     0xe1a04000
    dcd     0xe5942000
    dcd     0xe3a03000
    dcd     0xe5920398
    dcd     0xe5925004
    dcd     0xe28de014
    dcd     0xe2800014
    dcd     0xe1a06001
    dcd     0xe8900007
    dcd     0xe88e0007
    dcd     0xe59d0018
    dcd     0xe243ca03
    dcd     0xe2800c02
    dcd     0xe58d0018
    dcd     0xe89e0007
    dcd     0xe8860007
    dcd     0xe58d3008
    dcd     0xe58dc00c
    dcd     0xe58d3010
    dcd     0xe595007c
    dcd     0xe28d2008
    dcd     0xe1a0100e
    bl      func_01fff888
    dcd     0xe3500000
    dcd     0x0a00000a
    dcd     0xe28d1008
    dcd     0xe590000c
    dcd     0xe1a02001
    bl      func_01ffd144
    dcd     0xe59d100c
    dcd     0xe28d0014
    dcd     0xe2813c02
    dcd     0xe28d1008
    dcd     0xe1a02000
    dcd     0xe58d300c
    bl      VEC_Add
    dcd     0xe3a01000
    dcd     0xe28d0014
    dcd     0xe58d1004
    dcd     0xe24d3008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    dcd     0xe5940000
    dcd     0xe59f1014
    dcd     0xe5903398
    dcd     0xe3a02007
    dcd     0xe2833014
    bl      func_ov107_020c5af8
    dcd     0xe28dd020
    dcd     0xe8bd8070
    dcd     0x0000013d
}
