extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void data_0203d210(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov276_020d0cdc(void);
extern void func_ov276_020d0cf0(void);
extern void func_ov276_020d198c(void);

asm void func_ov276_020d1808(void) {

    dcd 0xe92d4030
    dcd 0xe24dd024
    dcd 0xe1a05000
    dcd 0xe5954004
    bl func_ov276_020d0cf0
    dcd 0xe3500000
    dcd 0xaa000005
    dcd 0xe1d512d0
    dcd 0xe1a00005
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd024
    dcd 0xe8bd8030
    dcd 0xe5940004
    dcd 0xe5d000ad
    dcd 0xe3500000
    dcd 0x1a00002e
    dcd 0xe594005c
    dcd 0xe3500000
    dcd 0x0a000004
    dcd 0xe3500002
    dcd 0x0a00000a
    dcd 0xe3500003
    dcd 0x0a000010
    dcd 0xea000017
    dcd 0xe5940000
    dcd 0xe3a01003
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a01002
    bl func_ov276_020d0cdc
    dcd 0xea000018
    dcd 0xe5940000
    dcd 0xe3a01009
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a01007
    bl func_ov276_020d0cdc
    dcd 0xea000010
    dcd 0xe5940000
    dcd 0xe3a01006
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a01005
    bl func_ov276_020d0cdc
    dcd 0xea000008
    dcd 0xe5940000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d512d0
    dcd 0xe1a00005
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd024
    dcd 0xe8bd8030
    dcd 0xe1d512d0
    dcd 0xe59f2080
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd024
    dcd 0xe8bd8030
    dcd 0xe5942040
    dcd 0xe59f006c
    dcd 0xe59f106c
    dcd 0xe083c092
    dcd 0xe0233192
    dcd 0xe1a01fc2
    dcd 0xe0233091
    dcd 0xe29c0000
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
    dcd func_ov276_020d198c
    dcd 0x60db9391
    dcd 0x000028be
    dcd data_0203d210
}
