extern void func_ov107_020c5af8(void);
extern void func_01fff948(void);
extern void func_01ffd144(void);
extern void func_01fff888(void);
extern void VEC_Add(void);
extern void func_ov107_020c5c54(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c0b90(void);
extern void func_0203c634(void);
extern void func_ov240_020cf208(void);

asm void func_ov240_020cf0c8(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd014
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
    dcd     0xe3500d22
    dcd     0xba000006
    dcd     0xe5940000
    dcd     0xe5943008
    dcd     0xe59f10f0
    dcd     0xe3a0200a
    bl      func_ov107_020c5af8
    mov r0, #1
    dcd     0xe5c4003e
    dcd     0xe5940004
    dcd     0xe5d000ad
    dcd     0xe3500000
    dcd     0x128dd014
    dcd     0x18bd8078
    dcd     0xe5941000
    dcd     0xe2842020
    dcd     0xe5916004
    dcd     0xe5913080
    dcd     0xe596007c
    dcd     0xe2811074
    bl      func_01fff948
    dcd     0xe3500000
    dcd     0x0a000003
    dcd     0xe2841020
    dcd     0xe590000c
    dcd     0xe1a02001
    bl      func_01ffd144
    dcd     0xe5941000
    dcd     0xe596007c
    dcd     0xe2811074
    dcd     0xe2842020
    dcd     0xe3a03000
    bl      func_01fff888
    dcd     0xe3500000
    dcd     0x0a000003
    dcd     0xe2841020
    dcd     0xe590000c
    dcd     0xe1a02001
    bl      func_01ffd144
    dcd     0xe5940008
    dcd     0xe28d2008
    dcd     0xe2841020
    bl      VEC_Add
    dcd     0xe5940000
    dcd     0xe28d1008
    bl      func_ov107_020c5c54
    dcd     0xe5940000
    dcd     0xe3a01005
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    mov r0, #0
    dcd     0xe58d0004
    dcd     0xe28d0008
    dcd     0xe24d3008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    dcd     0xe1d512d0
    dcd     0xe59f2010
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd014
    dcd     0xe8bd8078
    dcd     0x00000139
    dcd     func_ov240_020cf208
}
