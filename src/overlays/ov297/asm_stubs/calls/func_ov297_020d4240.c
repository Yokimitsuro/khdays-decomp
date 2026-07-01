extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void data_0203d210(void);

asm void func_ov297_020d4240(void)
{
    dcd     0xe92d4018
    dcd     0xe24dd024
    dcd     0xe5904004
    dcd     0xe3a01a01
    dcd     0xe5841010
    mov r0, #0
    dcd     0xe5840014
    dcd     0xe5841018
    dcd     0xe5942034
    dcd     0xe59f0090
    dcd     0xe59f1090
    dcd     0xe083c092
    dcd     0xe0233192
    dcd     0xe1a01fc2
    dcd     0xe0233091
    dcd     0xe29c0000
    dcd     0xe2a30b02
    dcd     0xe1a00200
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a01080
    dcd     0xe2810001
    dcd     0xe59f2064
    dcd     0xe1a01081
    dcd     0xe1a00080
    dcd     0xe19210f1
    dcd     0xe19220f0
    dcd     0xe28d0000
    bl      MTX_RotY33_
    dcd     0xe2840010
    dcd     0xe28d1000
    dcd     0xe1a02000
    bl      MTX_MultVec33
    dcd     0xe2840010
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe2841010
    dcd     0xe3a00d11
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe5940010
    dcd     0xe5941018
    bl      func_020050b4
    dcd     0xe5840030
    dcd     0xe584002c
    dcd     0xe28dd024
    dcd     0xe8bd8018
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
}
