extern void VEC_Subtract(void);
extern void data_02042264(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void func_02023eb4(void);
extern void func_0202f188(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);
extern void func_ov169_020ccacc(void);

asm void func_ov169_020cd7cc(void)
{
    dcd     0xe92d40f0
    dcd     0xe24dd00c
    dcd     0xe1a06000
    dcd     0xe5964004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe1b01000
    dcd     0xe584000c
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd80f0
    dcd     0xe5940008
    dcd     0xe28d2000
    dcd     0xe2811074
    bl      VEC_Subtract
    mov r0, #0
    dcd     0xe58d0004
    dcd     0xe28d0000
    dcd     0xe594500c
    dcd     0xe1a01000
    dcd     0xe5947000
    bl      func_01ff8d18
    dcd     0xe5951080
    dcd     0xe5972080
    dcd     0xe0403001
    dcd     0xe59d0000
    dcd     0xe59d1008
    dcd     0xe0435002
    bl      func_020050b4
    dcd     0xe1a02000
    dcd     0xe59f1124
    dcd     0xe2840074
    bl      func_0202f188
    dcd     0xe3a00c03
    dcd     0xe28d1000
    dcd     0xe2842020
    bl      func_01ffa724
    dcd     0xe5940088
    dcd     0xe59f1108
    dcd     0xe3500000
    dcd     0x0594000c
    dcd     0x15943018
    dcd     0x05900078
    dcd     0xe3a02b06
    dcd     0x02803b0f
    dcd     0xe5940008
    dcd     0xe5900004
    dcd     0xe0433000
    dcd     0xe0cc0391
    dcd     0xe083c00c
    dcd     0xe1a00fa3
    dcd     0xe080c24c
    dcd     0xe081329c
    dcd     0xe1a00fcc
    dcd     0xe0211290
    dcd     0xe2933b02
    dcd     0xe2a10000
    dcd     0xe1a01623
    dcd     0xe5942024
    dcd     0xe1811a00
    dcd     0xe0820001
    dcd     0xe5840024
    dcd     0xe3550a03
    dcd     0xda000017
    dcd     0xe3a00003
    bl      func_02023eb4
    dcd     0xe3500000
    dcd     0x1a000013
    dcd     0xe1a00006
    bl      func_ov169_020ccacc
    dcd     0xe3500000
    dcd     0xe5940000
    dcd     0xe3a02000
    dcd     0x0a000006
    dcd     0xe3a01008
    dcd     0xe5c011c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd80f0
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd80f0
    dcd     0xe5960000
    dcd     0xe5941048
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe3500a03
    dcd     0xb28dd00c
    dcd     0xe5840048
    dcd     0xb8bd80f0
    dcd     0xe5940000
    dcd     0xe3a01006
    dcd     0xe5c011c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd80f0
    dcd     data_02042264
    dcd     0x88888889
}
