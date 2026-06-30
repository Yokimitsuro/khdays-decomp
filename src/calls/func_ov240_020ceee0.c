extern void func_ov107_020cab14(void);
extern void func_0203c634(void);
extern void func_ov240_020ce8e8(void);
extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void func_ov240_020ce804(void);
extern void data_0203d210(void);

asm void func_ov240_020ceee0(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd024
    dcd     0xe1a06000
    dcd     0xe5965004
    dcd     0xe3a01000
    dcd     0xe5950000
    bl      func_ov107_020cab14
    dcd     0xe5951000
    dcd     0xe5810394
    dcd     0xe5951000
    dcd     0xe5910394
    dcd     0xe3500000
    dcd     0x1a000007
    dcd     0xe3a00002
    dcd     0xe5c101c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd024
    dcd     0xe8bd8078
    dcd     0xe1a00006
    bl      func_ov240_020ce8e8
    dcd     0xe1b04000
    dcd     0x5a000005
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd024
    dcd     0xe8bd8078
    dcd     0xe5952010
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
    dcd     0xe5950000
    dcd     0xe28d1000
    dcd     0xe5900398
    dcd     0xe2852014
    dcd     0xe280002c
    bl      MTX_MultVec33
    dcd     0xe1a00006
    dcd     0xe1a01004
    bl      func_ov240_020ce804
    dcd     0xe3500000
    dcd     0x028dd024
    dcd     0x08bd8078
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd024
    dcd     0xe8bd8078
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
}
