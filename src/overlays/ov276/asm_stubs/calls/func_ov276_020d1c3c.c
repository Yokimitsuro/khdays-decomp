extern void VEC_Subtract(void);
extern void data_02041dc8(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c9264(void);
extern void func_ov276_020d0cdc(void);
extern void func_ov276_020d1d14(void);

asm void func_ov276_020d1c3c(void) {

    dcd 0xe92d4030
    dcd 0xe24dd014
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe5943008
    dcd 0xe3530000
    dcd 0x0a00000d
    dcd 0xe5d401c4
    dcd 0xe3100002
    dcd 0x1a00000a
    dcd 0xe594100c
    dcd 0xe28d2008
    dcd 0xe2830e19
    bl VEC_Subtract
    dcd 0xe59d0008
    dcd 0xe59d1010
    bl func_020050b4
    dcd 0xe5840044
    dcd 0xe5840040
    mov r0, #0
    dcd 0xe5840008
    dcd 0xe5940000
    dcd 0xe3a0100c
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a01009
    bl func_ov276_020d0cdc
    dcd 0xe3a01000
    dcd 0xe59f0054
    dcd 0xe58d1004
    dcd 0xe24d3008
    dcd 0xe8900007
    dcd 0xe8830007
    dcd 0xe893000c
    dcd 0xe5940000
    dcd 0xe3a01002
    bl func_ov107_020c0b90
    dcd 0xe5940000
    dcd 0xe3a01f59
    dcd 0xe3a02004
    dcd 0xe594300c
    bl func_ov107_020c5af8
    mov r0, #0
    dcd 0xe584004c
    dcd 0xe5c40061
    dcd 0xe1a00005
    dcd 0xe1d512d0
    dcd 0xe59f200c
    bl func_0203c634
    dcd 0xe28dd014
    dcd 0xe8bd8030
    dcd data_02041dc8
    dcd func_ov276_020d1d14
}
