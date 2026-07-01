extern void VEC_DotProduct(void);
extern void VEC_Subtract(void);
extern void data_0203d210(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);
extern void func_ov264_020cd0e8(void);

asm void func_ov264_020cd8ac(void) {

    dcd 0xe92d43f8
    dcd 0xe24dd018
    dcd 0xe1a06000
    dcd 0xe5965004
    dcd 0xe3a01000
    dcd 0xe5950000
    bl func_ov107_020cab14
    dcd 0xe5850008
    dcd 0xe3500000
    dcd 0x1a000008
    dcd 0xe5950000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d612d0
    dcd 0xe1a00006
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd83f8
    dcd 0xe5951000
    dcd 0xe28d200c
    dcd 0xe2800e19
    dcd 0xe28110b0
    bl VEC_Subtract
    dcd 0xe59d200c
    dcd 0xe3a03000
    dcd 0xe2624000
    dcd 0xe59d1014
    dcd 0xe28d000c
    dcd 0xe2612000
    dcd 0xe1a01000
    dcd 0xe58d400c
    dcd 0xe58d2014
    dcd 0xe58d3010
    bl func_01ff8d18
    dcd 0xe1a04000
    dcd 0xe59d000c
    dcd 0xe59d1014
    bl func_020050b4
    dcd 0xe585004c
    dcd 0xe5957044
    dcd 0xe59f20a0
    dcd 0xe59f30a0
    dcd 0xe0889297
    dcd 0xe3a00000
    dcd 0xe58d0004
    dcd 0xe0288397
    dcd 0xe1a0efc7
    dcd 0xe028829e
    dcd 0xe2992000
    dcd 0xe2a82b02
    dcd 0xe1a02202
    dcd 0xe1a02822
    dcd 0xe1a02242
    dcd 0xe1a07082
    dcd 0xe59fc070
    dcd 0xe1a02087
    dcd 0xe19c30f2
    dcd 0xe2872001
    dcd 0xe1a02082
    dcd 0xe19c20f2
    dcd 0xe28d0000
    dcd 0xe28d100c
    dcd 0xe58d3000
    dcd 0xe58d2008
    bl VEC_DotProduct
    dcd 0xe5950000
    dcd 0xe2852020
    dcd 0xe5900430
    dcd 0xe28d1000
    bl func_01ffa724
    dcd 0xe1a01004
    dcd 0xe1a00006
    bl func_ov264_020cd0e8
    dcd 0xe3500000
    dcd 0x028dd018
    dcd 0x08bd83f8
    dcd 0xe1d612d0
    dcd 0xe1a00006
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd018
    dcd 0xe8bd83f8
    dcd 0x60db9391
    dcd 0x000028be
    dcd data_0203d210
}
