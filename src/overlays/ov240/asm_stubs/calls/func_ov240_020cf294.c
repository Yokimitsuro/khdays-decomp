extern void func_ov107_020c5af8(void);
extern void func_ov107_020c9264(void);
extern void func_ov240_020ce8d4(void);
extern void func_0203c634(void);
extern void func_ov240_020cf334(void);

asm void func_ov240_020cf294(void)
{
    dcd     0xe92d4038
    dcd     0xe1a05000
    dcd     0xe8950011
    dcd     0xe5941038
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe5840038
    dcd     0xe5d4003e
    dcd     0xe3500000
    dcd     0x1a000009
    dcd     0xe5940038
    dcd     0xe3500d11
    dcd     0xba000006
    dcd     0xe5940000
    dcd     0xe5943008
    dcd     0xe59f1054
    dcd     0xe3a02004
    bl      func_ov107_020c5af8
    mov r0, #1
    dcd     0xe5c4003e
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x18bd8038
    dcd     0xe5940000
    dcd     0xe3a01006
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    dcd     0xe5940000
    dcd     0xe3a01001
    bl      func_ov240_020ce8d4
    mov r0, #0
    dcd     0xe5840038
    dcd     0xe1d512d0
    dcd     0xe59f200c
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     0x00000139
    dcd     func_ov240_020cf334
}
