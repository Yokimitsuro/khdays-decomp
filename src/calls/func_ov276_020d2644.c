extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void data_0203d210(void);
extern void func_0203c634(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c9264(void);
extern void func_ov276_020d275c(void);

asm void func_ov276_020d2644(void) {

    dcd 0xe92d4030
    dcd 0xe24dd024
    dcd 0xe1a05000
    dcd 0xe8950011
    dcd 0xe594104c
    dcd 0xe590002c
    dcd 0xe0810000
    dcd 0xe584004c
    dcd 0xe5d40061
    dcd 0xe3500000
    dcd 0x1a000009
    dcd 0xe594004c
    dcd 0xe3500e55
    dcd 0xba000006
    dcd 0xe5940000
    dcd 0xe594300c
    dcd 0xe3a01f59
    dcd 0xe3a02010
    bl func_ov107_020c5af8
    dcd 0xe3a00001
    dcd 0xe5c40061
    dcd 0xe5940004
    dcd 0xe5d000ad
    dcd 0xe3500000
    dcd 0x1a00000b
    dcd 0xe5940000
    dcd 0xe3a01014
    dcd 0xe3a02001
    bl func_ov107_020c9264
    dcd 0xe5940058
    dcd 0xe59f2088
    dcd 0xe584004c
    dcd 0xe1d512d0
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd024
    dcd 0xe8bd8030
    dcd 0xe5942040
    dcd 0xe59f006c
    dcd 0xe59f106c
    dcd 0xe0835092
    dcd 0xe0233192
    dcd 0xe1a01fc2
    dcd 0xe0233091
    dcd 0xe2950000
    dcd 0xe2a30b02
    dcd 0xe1a00200
    dcd 0xe1a00820
    dcd 0xe1a00240
    dcd 0xe1a01080
    dcd 0xe2810001
    dcd 0xe59f2040
    dcd 0xe1a01081
    dcd 0xe1a00080
    dcd 0xe19210f1
    dcd 0xe19220f0
    dcd 0xe28d0000
    bl MTX_RotY33_
    dcd 0xe5940000
    dcd 0xe28d1000
    dcd 0xe5900470
    dcd 0xe2842010
    dcd 0xe280002c
    bl MTX_MultVec33
    dcd 0xe28dd024
    dcd 0xe8bd8030
    dcd func_ov276_020d275c
    dcd 0x60db9391
    dcd 0x000028be
    dcd data_0203d210
}
