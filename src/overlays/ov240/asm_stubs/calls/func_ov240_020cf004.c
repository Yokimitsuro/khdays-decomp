extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov240_020cf0c8(void);

asm void func_ov240_020cf004(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd00c
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe28d2000
    dcd     0xe5943000
    dcd     0xe5941008
    dcd     0xe5930394
    dcd     0xe5933080
    dcd     0xe590c080
    dcd     0xe2800e19
    dcd     0xe08c6003
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe2841020
    bl      func_01ff8d18
    dcd     0xe0406006
    dcd     0xe2841020
    dcd     0xe1a00006
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe3560000
    dcd     0xe5940000
    dcd     0xe3a02000
    dcd     0xca000006
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8078
    dcd     0xe2800c01
    dcd     0xe1d03abe
    dcd     0xe3a01004
    dcd     0xe3833001
    dcd     0xe1c03abe
    dcd     0xe5940000
    bl      func_ov107_020c9264
    mov r0, #0
    dcd     0xe5840038
    dcd     0xe5c4003e
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd00c
    dcd     0xe8bd8078
    dcd     func_ov240_020cf0c8
}
