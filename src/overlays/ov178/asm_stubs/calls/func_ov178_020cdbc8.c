extern void VEC_Add(void);
extern void VEC_CrossProduct(void);
extern void data_02042264(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);
extern void func_ov178_020ccaf4(void);
extern void func_ov178_020ccb8c(void);

asm void func_ov178_020cdbc8(void) {

    dcd 0xe92d4070
    dcd 0xe24dd018
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe3a01000
    dcd 0xe5940000
    bl func_ov107_020cab14
    dcd 0xe584000c
    dcd 0xe3500000
    dcd 0x1a000008
    dcd 0xe5940000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d512d0
    dcd 0xe1a00005
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd8070
    dcd 0xe28d100c
    dcd 0xe1a00005
    bl func_ov178_020ccaf4
    dcd 0xe3500c01
    dcd 0xc3a00c02
    dcd 0xe28d100c
    dcd 0xe2842020
    bl func_01ffa724
    dcd 0xe59f0170
    dcd 0xe28d100c
    dcd 0xe28d2000
    bl VEC_CrossProduct
    dcd 0xe28d0000
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe5942060
    dcd 0xe3a00d06
    dcd 0xe0000092
    dcd 0xe28d1000
    dcd 0xe1a02001
    bl func_01ffa724
    dcd 0xe2840020
    dcd 0xe28d1000
    dcd 0xe1a02000
    bl VEC_Add
    dcd 0xe594100c
    dcd 0xe5940008
    dcd 0xe5911078
    dcd 0xe5900004
    dcd 0xe0512000
    dcd 0x42622000
    dcd 0xe3520080
    dcd 0xda000005
    dcd 0xe1510000
    dcd 0xe5940024
    dcd 0xb2400080
    dcd 0xb5840024
    dcd 0xa2800080
    dcd 0xa5840024
    dcd 0xe5950000
    dcd 0xe594205c
    dcd 0xe590102c
    dcd 0xe1a00005
    dcd 0xe0421001
    dcd 0xe584105c
    bl func_ov178_020ccb8c
    dcd 0xe3500000
    dcd 0x1a000008
    dcd 0xe5940000
    dcd 0xe5906224
    dcd 0xe5900228
    dcd 0xe0500006
    dcd 0x42600000
    dcd 0xe2800001
    bl func_02023eb4
    dcd 0xe0860000
    dcd 0xe584005c
    dcd 0xe594005c
    dcd 0xe3500000
    dcd 0xc28dd018
    dcd 0xc8bd8070
    dcd 0xe3a00065
    bl func_02023eb4
    dcd 0xe2806000
    mov r0, #0
    dcd 0xe584005c
    dcd 0xe3560028
    dcd 0xaa000007
    dcd 0xe1a00005
    bl func_ov178_020ccb8c
    dcd 0xe3500000
    dcd 0x0a000003
    dcd 0xe5940000
    dcd 0xe3a01009
    dcd 0xe5c011c7
    dcd 0xea00000c
    dcd 0xe356003c
    dcd 0xaa000007
    dcd 0xe1a00005
    bl func_ov178_020ccb8c
    dcd 0xe3500000
    dcd 0x0a000003
    dcd 0xe5940000
    dcd 0xe3a01008
    dcd 0xe5c011c7
    dcd 0xea000002
    dcd 0xe5940000
    dcd 0xe3a01005
    dcd 0xe5c011c7
    dcd 0xe5940000
    dcd 0xe3e01000
    dcd 0xe2800c01
    dcd 0xe1d00cd7
    dcd 0xe1500001
    dcd 0x028dd018
    dcd 0x08bd8070
    dcd 0xe1d512d0
    dcd 0xe1a00005
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd8070
    dcd data_02042264
}
