extern void func_ov107_020c5af8(void);
extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void func_ov239_020cc9f0(void);
extern void data_0203d210(void);
extern void func_ov239_020cd54c(void);

asm void func_ov239_020cd3a0(void)
{
    dcd     0xe92d4038
    dcd     0xe24dd028
    dcd     0xe1a05000
    dcd     0xe8950011
    dcd     0xe594102c
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe584002c
    dcd     0xe5d40032
    dcd     0xe3100001
    dcd     0x1a00000a
    dcd     0xe594002c
    dcd     0xe3500088
    dcd     0xba000007
    dcd     0xe5940000
    dcd     0xe5943008
    dcd     0xe3a01f4e
    dcd     0xe3a02007
    bl      func_ov107_020c5af8
    dcd     0xe5d40032
    dcd     0xe3800001
    dcd     0xe5c40032
    dcd     0xe5d40032
    dcd     0xe3100002
    dcd     0x1a00000a
    dcd     0xe594002c
    dcd     0xe3500eff
    dcd     0xba000007
    dcd     0xe5940000
    dcd     0xe5943008
    dcd     0xe3a01f4e
    dcd     0xe3a02008
    bl      func_ov107_020c5af8
    dcd     0xe5d40032
    dcd     0xe3800002
    dcd     0xe5c40032
    dcd     0xe5942010
    dcd     0xe59f0100
    dcd     0xe59f1100
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
    dcd     0xe59f20d4
    dcd     0xe1a01081
    dcd     0xe1a00080
    dcd     0xe19210f1
    dcd     0xe19220f0
    dcd     0xe28d0004
    bl      MTX_RotY33_
    dcd     0xe5940000
    dcd     0xe28d1004
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
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x128dd028
    dcd     0x18bd8038
    dcd     0xe5940000
    dcd     0xe3a02000
    dcd     0xe2801c01
    dcd     0xe1d13abe
    dcd     0xe59fc034
    dcd     0xe1a00005
    dcd     0xe3c33001
    dcd     0xe1c13abe
    dcd     0xe584202c
    dcd     0xe3a01006
    dcd     0xe3a02002
    dcd     0xe3a03001
    dcd     0xe58dc000
    bl      func_ov239_020cc9f0
    dcd     0xe28dd028
    dcd     0xe8bd8038
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
    dcd     func_ov239_020cd54c
}
