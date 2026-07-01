extern void FX_Inv(void);
extern void VEC_Subtract(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void func_0202f384(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c9f48(void);
extern void func_ov107_020cab14(void);
extern void func_ov205_020d6d20(void);
extern void func_ov205_020d6d54(void);

asm void func_ov205_020d6c34(void) {

    dcd 0xe92d4070
    dcd 0xe24dd018
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe28d100c
    dcd 0xe5940000
    dcd 0xe5900390
    bl func_ov107_020c9f48
    dcd 0xe5941000
    dcd 0xe1a06000
    dcd 0xe28d200c
    dcd 0xe2840008
    dcd 0xe28110a0
    bl func_0202f384
    dcd 0xe2841008
    dcd 0xe1a00006
    dcd 0xe1a02001
    bl func_01ffa724
    dcd 0xe1a00004
    bl func_ov205_020d6d54
    dcd 0xe5940000
    dcd 0xe3a01000
    bl func_ov107_020cab14
    dcd 0xe5840004
    dcd 0xe3500000
    dcd 0x0a000007
    dcd 0xe5941024
    dcd 0xe28d2000
    dcd 0xe2800074
    bl VEC_Subtract
    dcd 0xe59d0000
    dcd 0xe59d1008
    bl func_020050b4
    dcd 0xe5840038
    dcd 0xe1a00006
    dcd 0xe3a01a03
    bl FX_Inv
    dcd 0xe3500c02
    dcd 0xc3a00c02
    dcd 0xe584003c
    dcd 0xe594002c
    dcd 0xe0800006
    dcd 0xe584002c
    dcd 0xe5940028
    dcd 0xe5d00000
    dcd 0xe3500000
    dcd 0x128dd018
    dcd 0x18bd8070
    dcd 0xe5940000
    dcd 0xe3a01012
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe1d512d0
    dcd 0xe59f200c
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd8070
    dcd func_ov205_020d6d20
}
