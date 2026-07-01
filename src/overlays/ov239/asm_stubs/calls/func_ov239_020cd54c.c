extern void func_ov239_020cca38(void);
extern void func_0203c634(void);
extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void func_ov239_020cc778(void);
extern void func_01ff8d18(void);
extern void func_ov239_020cc9f0(void);
extern void data_0203d210(void);
extern void func_ov239_020cd6c8(void);

asm void func_ov239_020cd54c(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd034
    dcd     0xe1a05000
    dcd     0xe5954004
    bl      func_ov239_020cca38
    dcd     0xe3500000
    dcd     0xaa000005
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd034
    dcd     0xe8bd8030
    dcd     0xe5942010
    dcd     0xe59f012c
    dcd     0xe59f112c
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
    dcd     0xe59f2100
    dcd     0xe1a01081
    dcd     0xe1a00080
    dcd     0xe19210f1
    dcd     0xe19220f0
    dcd     0xe28d0010
    bl      MTX_RotY33_
    dcd     0xe5940000
    dcd     0xe28d1010
    dcd     0xe5900398
    dcd     0xe2842014
    dcd     0xe280002c
    bl      MTX_MultVec33
    dcd     0xe5942000
    dcd     0xe5920394
    dcd     0xe3500000
    dcd     0x0a00000c
    dcd     0xe5901194
    dcd     0xe59200b4
    dcd     0xe0411000
    dcd     0xe5841018
    dcd     0xe3510c02
    dcd     0xc3a01c02
    dcd     0xca000003
    dcd     0xe3a00c02
    dcd     0xe2600000
    dcd     0xe1510000
    dcd     0xb1a01000
    dcd     0xe5841018
    dcd     0xea000001
    mov r0, #0
    dcd     0xe5840018
    dcd     0xe1a00004
    dcd     0xe3a01001
    dcd     0xe3a02000
    bl      func_ov239_020cc778
    dcd     0xe5940000
    dcd     0xe28d1004
    dcd     0xe5900398
    dcd     0xe280002c
    bl      func_01ff8d18
    dcd     0xe594102c
    dcd     0xe0810000
    dcd     0xe584002c
    dcd     0xe3500801
    dcd     0xaa000008
    dcd     0xe5d40030
    dcd     0xe3500000
    dcd     0x1a000005
    dcd     0xe5940000
    dcd     0xe5d0017a
    dcd     0xe1a00f00
    dcd     0xe1b00fa0
    dcd     0x028dd034
    dcd     0x08bd8030
    dcd     0xe59f4028
    dcd     0xe1a00005
    dcd     0xe3a01007
    dcd     0xe3a02003
    dcd     0xe3a03000
    dcd     0xe58d4000
    bl      func_ov239_020cc9f0
    dcd     0xe28dd034
    dcd     0xe8bd8030
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
    dcd     func_ov239_020cd6c8
}
