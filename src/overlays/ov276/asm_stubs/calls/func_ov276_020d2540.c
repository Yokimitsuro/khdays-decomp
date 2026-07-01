extern void VEC_Subtract(void);
extern void data_0203d210(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);
extern void func_ov107_020c5c54(void);
extern void func_ov107_020c9264(void);
extern void func_ov276_020d0cdc(void);
extern void func_ov276_020d2644(void);

asm void func_ov276_020d2540(void) {

    dcd 0xe92d4030
    dcd 0xe24dd00c
    dcd 0xe1a05000
    dcd 0xe5954004
    dcd 0xe5940008
    dcd 0xe3500000
    dcd 0x0a000025
    dcd 0xe5942040
    dcd 0xe59f00cc
    dcd 0xe59f10cc
    dcd 0xe083c092
    dcd 0xe0233192
    dcd 0xe1a01fc2
    dcd 0xe0233091
    dcd 0xe29c0000
    dcd 0xe2a30b02
    dcd 0xe1a00200
    dcd 0xe1a00820
    dcd 0xe1a00240
    dcd 0xe1a03080
    dcd 0xe2830001
    dcd 0xe3a02000
    dcd 0xe59fc09c
    dcd 0xe1a03083
    dcd 0xe1a00080
    dcd 0xe19c30f3
    dcd 0xe19c00f0
    dcd 0xe58d2004
    dcd 0xe28d1000
    dcd 0xe58d3000
    dcd 0xe58d0008
    dcd 0xe5940000
    dcd 0xe1a02001
    dcd 0xe5900480
    bl func_01ffa724
    dcd 0xe5940008
    dcd 0xe28d1000
    dcd 0xe2800e19
    dcd 0xe1a02001
    bl VEC_Subtract
    dcd 0xe5940000
    dcd 0xe28d1000
    bl func_ov107_020c5c54
    mov r0, #0
    dcd 0xe5840008
    dcd 0xe5940000
    dcd 0xe3a01013
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a0100d
    bl func_ov276_020d0cdc
    mov r0, #0
    dcd 0xe584004c
    dcd 0xe5c40061
    dcd 0xe1d512d0
    dcd 0xe59f2018
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd8030
    dcd 0x60db9391
    dcd 0x000028be
    dcd data_0203d210
    dcd func_ov276_020d2644
}
