extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Subtract(void);
extern void data_0203d210(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov276_020d0cdc(void);

asm void func_ov276_020d2a60(void) {

    dcd 0xe92d4070
    dcd 0xe24dd030
    dcd 0xe1a06000
    dcd 0xe5964004
    dcd 0xe28d2024
    dcd 0xe5940000
    dcd 0xe594100c
    dcd 0xe2800e19
    bl VEC_Subtract
    dcd 0xe59d0024
    dcd 0xe59d102c
    bl func_020050b4
    dcd 0xe5840044
    dcd 0xe28d0024
    dcd 0xe5945000
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe5951480
    dcd 0xe0400001
    dcd 0xe3500a02
    dcd 0xaa000007
    dcd 0xe3a00002
    dcd 0xe5c501c7
    dcd 0xe1d612d0
    dcd 0xe1a00006
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd030
    dcd 0xe8bd8070
    dcd 0xe5940004
    dcd 0xe5d000ad
    dcd 0xe3500000
    dcd 0x1a000008
    dcd 0xe1a00005
    dcd 0xe3a01003
    dcd 0xe3a02000
    bl func_ov107_020c9264
    dcd 0xe5940000
    dcd 0xe3a01002
    bl func_ov276_020d0cdc
    dcd 0xe28dd030
    dcd 0xe8bd8070
    dcd 0xe5942044
    dcd 0xe59f0068
    dcd 0xe59f1068
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
    dcd 0xe59f203c
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
    dcd 0xe28dd030
    dcd 0xe8bd8070
    dcd 0x60db9391
    dcd 0x000028be
    dcd data_0203d210
}
