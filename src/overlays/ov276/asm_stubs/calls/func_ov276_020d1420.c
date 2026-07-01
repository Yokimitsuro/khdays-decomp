extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void data_0203d210(void);
extern void func_0203c634(void);

asm void func_ov276_020d1420(void) {

    dcd 0xe92d4018
    dcd 0xe24dd024
    dcd 0xe5904004
    dcd 0xe5941000
    dcd 0xe1d136b0
    dcd 0xe1a02c03
    dcd 0xe1a02c22
    dcd 0xe3120080
    dcd 0x1a000008
    dcd 0xe1a02803
    dcd 0xe1a02c22
    dcd 0xe3c2200e
    dcd 0xe1a02802
    dcd 0xe1a02822
    dcd 0xe3c33cff
    dcd 0xe1a02c02
    dcd 0xe1832822
    dcd 0xe1c126b0
    dcd 0xe5901000
    dcd 0xe594204c
    dcd 0xe591102c
    dcd 0xe0821001
    dcd 0xe584104c
    dcd 0xe3510e11
    dcd 0xba00000a
    dcd 0xe5943000
    dcd 0xe1d326b0
    dcd 0xe1a01802
    dcd 0xe1a01c21
    dcd 0xe3c11080
    dcd 0xe1a01801
    dcd 0xe1a01821
    dcd 0xe3c22cff
    dcd 0xe1a01c01
    dcd 0xe1821821
    dcd 0xe1c316b0
    dcd 0xe5941004
    dcd 0xe5d110ad
    dcd 0xe3510000
    dcd 0x1a000007
    dcd 0xe5941000
    dcd 0xe3a02002
    dcd 0xe5c121c7
    dcd 0xe1d012d0
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd024
    dcd 0xe8bd8018
    dcd 0xe5942040
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
    dcd 0xe28dd024
    dcd 0xe8bd8018
    dcd 0x60db9391
    dcd 0x000028be
    dcd data_0203d210
}
