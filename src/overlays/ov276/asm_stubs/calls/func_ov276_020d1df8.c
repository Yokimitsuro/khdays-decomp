extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void data_0203d210(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov276_020d0cdc(void);
extern void func_ov276_020d1ee4(void);

asm void func_ov276_020d1df8(void) {

    dcd 0xe92d4030
    dcd 0xe24dd024
    dcd 0xe1a05000
    dcd 0xe8950011
    dcd 0xe594204c
    dcd 0xe590002c
    dcd 0xe59f10bc
    dcd 0xe0820000
    dcd 0xe584004c
    dcd 0xe5943040
    dcd 0xe59f00b0
    dcd 0xe1a02fc3
    dcd 0xe08ce093
    dcd 0xe02cc193
    dcd 0xe02cc092
    dcd 0xe29e0000
    dcd 0xe2ac0b02
    dcd 0xe1a00200
    dcd 0xe1a00820
    dcd 0xe1a00240
    dcd 0xe1a01080
    dcd 0xe2810001
    dcd 0xe59f2084
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
    dcd 0xe5940004
    dcd 0xe5d000ad
    dcd 0xe3500000
    dcd 0x128dd024
    dcd 0x18bd8030
    dcd 0xe5940000
    dcd 0xe3a0100e
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a0100b
    bl func_ov276_020d0cdc
    dcd 0xe3a00000
    dcd 0xe5c40062
    dcd 0xe1d512d0
    dcd 0xe59f2018
    dcd 0xe1a00005
    bl func_0203c634
    dcd 0xe28dd024
    dcd 0xe8bd8030
    dcd 0x000028be
    dcd 0x60db9391
    dcd data_0203d210
    dcd func_ov276_020d1ee4
}
