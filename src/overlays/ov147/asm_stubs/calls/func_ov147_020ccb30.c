extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Subtract(void);
extern void data_0203d210(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_0202f384(void);

asm void func_ov147_020ccb30(void) {

    dcd 0xe92d000f
    dcd 0xe92d4038
    dcd 0xe24dd030
    dcd 0xe1a05000
    dcd 0xe5950000
    dcd 0xe5900394
    dcd 0xe3500000
    dcd 0x0a000007
    dcd 0xe595100c
    dcd 0xe28d2000
    dcd 0xe2800e19
    bl VEC_Subtract
    dcd 0xe59d0000
    dcd 0xe59d1008
    bl func_020050b4
    dcd 0xe5850038
    dcd 0xe28d0044
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe1a04000
    dcd 0xe59d0044
    dcd 0xe59d104c
    bl func_020050b4
    dcd 0xe59f1090
    dcd 0xe59f2090
    dcd 0xe083c190
    dcd 0xe0233290
    dcd 0xe1a00fc0
    dcd 0xe0233190
    dcd 0xe29c0000
    dcd 0xe2a30b02
    dcd 0xe1a00200
    dcd 0xe1a00820
    dcd 0xe1a00240
    dcd 0xe1a01080
    dcd 0xe2810001
    dcd 0xe59f2064
    dcd 0xe1a01081
    dcd 0xe1a00080
    dcd 0xe19210f1
    dcd 0xe19220f0
    dcd 0xe28d000c
    bl MTX_RotY33_
    dcd 0xe5950000
    dcd 0xe28d100c
    dcd 0xe2800e3b
    dcd 0xe2852010
    bl MTX_MultVec33
    dcd 0xe59d0050
    dcd 0xe3500000
    dcd 0x0a000004
    dcd 0xe5951000
    dcd 0xe2850010
    dcd 0xe2811d0f
    dcd 0xe1a02000
    bl func_0202f384
    dcd 0xe1a00004
    dcd 0xe28dd030
    dcd 0xe8bd4038
    dcd 0xe28dd010
    dcd 0xe12fff1e
    dcd 0x60db9391
    dcd 0x000028be
    dcd data_0203d210
}
