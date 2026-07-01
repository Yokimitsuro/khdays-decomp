extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c9264(void);
extern void func_ov214_020cdac0(void);

asm void func_ov214_020cda04(void) {

    dcd 0xe92d4030
    dcd 0xe24dd00c
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe5943008
    dcd 0xe5941000
    dcd 0xe3530000
    dcd 0x1a000006
    dcd 0xe3a02002
    dcd 0xe5c121c7
    dcd 0xe1d512d0
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8030
    dcd 0xe28d2000
    dcd 0xe2830e19
    dcd 0xe28110b0
    bl VEC_Subtract
    dcd 0xe28d0000
    dcd 0xe3a02000
    dcd 0xe1a01000
    dcd 0xe58d2004
    bl func_01ff8d18
    dcd 0xe5840048
    dcd 0xe59d0000
    dcd 0xe59d1008
    bl func_020050b4
    dcd 0xe584004c
    dcd 0xe5840044
    dcd 0xe5940000
    dcd 0xe3a01003
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe5943010
    dcd 0xe59f101c
    dcd 0xe3a02006
    bl func_ov107_020c5af8
    dcd 0xe1d512d0
    dcd 0xe59f2010
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8030
    dcd 0x00000129
    dcd func_ov214_020cdac0
}
