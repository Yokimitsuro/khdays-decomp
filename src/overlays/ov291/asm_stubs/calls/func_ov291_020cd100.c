extern void VEC_DotProduct(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void func_0202f384(void);
extern void func_0203bec0(void);
extern void func_0203c634(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c9ee8(void);
extern void func_ov107_020c9f48(void);
extern void func_ov291_020cd2d0(void);

asm void func_ov291_020cd100(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd024
    dcd     0xe1a06000
    dcd     0xe5964004
    dcd     0xe28d1018
    dcd     0xe5940000
    dcd     0xe5900394
    bl      func_ov107_020c9f48
    dcd     0xe5941000
    dcd     0xe1a05000
    dcd     0xe28d0018
    dcd     0xe28110a0
    dcd     0xe1a02000
    bl      func_0202f384
    dcd     0xe5d40028
    dcd     0xe3500000
    dcd     0x1a00000d
    dcd     0xe5940000
    dcd     0xe3a01000
    dcd     0xe5900384
    bl      func_0203bec0
    dcd     0xe3500901
    dcd     0xba000020
    dcd     0xe5940000
    dcd     0xe594300c
    dcd     0xe59f115c
    dcd     0xe3a02004
    bl      func_ov107_020c5af8
    mov r0, #1
    dcd     0xe5c40028
    dcd     0xea000018
    dcd     0xe3500001
    dcd     0x1a00000d
    dcd     0xe5940000
    dcd     0xe3a01000
    dcd     0xe5900384
    bl      func_0203bec0
    dcd     0xe3500a15
    dcd     0xba000010
    dcd     0xe5940000
    dcd     0xe594300c
    dcd     0xe59f111c
    dcd     0xe3a02005
    bl      func_ov107_020c5af8
    dcd     0xe3a00002
    dcd     0xe5c40028
    dcd     0xea000008
    dcd     0xe3500002
    dcd     0x1a000006
    dcd     0xe5940000
    dcd     0xe3a01000
    dcd     0xe5900384
    bl      func_0203bec0
    dcd     0xe3500a15
    dcd     0xb3a00000
    dcd     0xb5c40028
    dcd     0xe5941000
    dcd     0xe5940024
    dcd     0xe59113a0
    dcd     0xe28d300c
    dcd     0xe0810200
    dcd     0xe2800010
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe594100c
    dcd     0xe28d2000
    dcd     0xe1a00003
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe1500005
    dcd     0xb1a050c0
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5840008
    dcd     0xe28d0000
    dcd     0xe28d1018
    bl      VEC_DotProduct
    dcd     0xe3500000
    dcd     0xb3a00000
    dcd     0xe0c01095
    dcd     0xe2911b02
    dcd     0xe1a02621
    dcd     0xe2a00000
    dcd     0xe1822a00
    dcd     0xe1a000c2
    dcd     0xe28d1018
    dcd     0xe2842010
    bl      func_01ffa724
    dcd     0xe3a02000
    dcd     0xe584201c
    dcd     0xe5940020
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x128dd024
    dcd     0x18bd8078
    dcd     0xe5940000
    dcd     0xe3a01003
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5900394
    dcd     0xe3a02000
    bl      func_ov107_020c9ee8
    mov r0, #0
    dcd     0xe5c40028
    dcd     0xe1d612d0
    dcd     0xe59f2010
    dcd     0xe1a00006
    bl      func_0203c634
    dcd     0xe28dd024
    dcd     0xe8bd8078
    dcd     0x0000016f
    dcd     func_ov291_020cd2d0
}
