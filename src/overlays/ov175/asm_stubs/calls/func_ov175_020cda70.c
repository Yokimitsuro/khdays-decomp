extern void func_ov107_020cab14(void);
extern void func_0203c634(void);
extern void func_ov175_020cca9c(void);
extern void func_01ffa724(void);
extern void VEC_CrossProduct(void);
extern void func_01ff8d18(void);
extern void VEC_Add(void);
extern void func_02023eb4(void);
extern void func_ov175_020ccb34(void);
extern void data_02042264(void);

asm void func_ov175_020cda70(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd018
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a01000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe584000c
    dcd     0xe3500000
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd8038
    dcd     0xe28d100c
    dcd     0xe1a00005
    bl      func_ov175_020cca9c
    dcd     0xe3500c01
    dcd     0xc3a00d06
    dcd     0xe28d100c
    dcd     0xe2842020
    bl      func_01ffa724
    dcd     0xe59f0104
    dcd     0xe28d100c
    dcd     0xe28d2000
    bl      VEC_CrossProduct
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe5942060
    dcd     0xe3a00d06
    dcd     0xe0000092
    dcd     0xe28d1000
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe2840020
    dcd     0xe28d1000
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe594100c
    dcd     0xe5940008
    dcd     0xe5911078
    dcd     0xe5900004
    dcd     0xe0512000
    dcd     0x42622000
    dcd     0xe3520080
    dcd     0xda000005
    dcd     0xe1510000
    dcd     0xe5940024
    dcd     0xb2400060
    dcd     0xb5840024
    dcd     0xa2800060
    dcd     0xa5840024
    dcd     0xe5950000
    dcd     0xe594105c
    dcd     0xe590002c
    dcd     0xe0410000
    dcd     0xe3500000
    dcd     0xc28dd018
    dcd     0xe584005c
    dcd     0xc8bd8038
    dcd     0xe3a00065
    bl      func_02023eb4
    dcd     0xe2801000
    mov r0, #0
    dcd     0xe584005c
    dcd     0xe351003c
    dcd     0xaa000004
    dcd     0xe1a00005
    bl      func_ov175_020ccb34
    dcd     0xe3500000
    dcd     0x13a02008
    dcd     0x1a000000
    dcd     0xe3a02005
    dcd     0xe5940000
    dcd     0xe3e01000
    dcd     0xe5c021c7
    dcd     0xe5940000
    dcd     0xe2800c01
    dcd     0xe1d00cd7
    dcd     0xe1500001
    dcd     0x028dd018
    dcd     0x08bd8038
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd8038
    dcd     data_02042264
}
