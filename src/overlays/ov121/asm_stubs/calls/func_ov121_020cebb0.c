extern void VEC_DotProduct(void);
extern void VEC_Subtract(void);
extern char data_0203d210[];
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);

asm void func_ov121_020cebb0(void)
{
    dcd     0xe92d40f8
    dcd     0xe24dd018
    dcd     0xe1a06000
    dcd     0xe5964004
    dcd     0xe3a01000
    dcd     0xe5841018
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe3500000
    dcd     0x028dd018
    dcd     0xe5840008
    dcd     0x08bd80f8
    dcd     0xe5941000
    dcd     0xe28d200c
    dcd     0xe2800e19
    dcd     0xe28110b0
    bl      VEC_Subtract
    mov r0, #0
    dcd     0xe58d0010
    dcd     0xe28d000c
    dcd     0xe5945008
    dcd     0xe1a01000
    dcd     0xe5947000
    bl      func_01ff8d18
    dcd     0xe5951080
    dcd     0xe5972080
    dcd     0xe0403001
    dcd     0xe59d000c
    dcd     0xe59d1014
    dcd     0xe0435002
    bl      func_020050b4
    dcd     0xe5840014
    dcd     0xe5940000
    dcd     0xe59002d8
    dcd     0xe1550000
    dcd     0xc28dd018
    dcd     0xc8bd80f8
    dcd     0xe5960000
    dcd     0xe5941040
    dcd     0xe590002c
    dcd     0xe0410000
    dcd     0xe3500000
    dcd     0xc28dd018
    dcd     0xe5840040
    dcd     0xc8bd80f8
    dcd     0xe5942010
    dcd     0xe59f00ac
    dcd     0xe59f10ac
    dcd     0xe083c092
    dcd     0xe0233192
    dcd     0xe1a01fc2
    dcd     0xe0233091
    dcd     0xe29c0000
    dcd     0xe2a30b02
    dcd     0xe1a00200
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a02080
    dcd     0xe2820001
    dcd     0xe3a01000
    dcd     0xe59f307c
    dcd     0xe1a02082
    dcd     0xe1a00080
    dcd     0xe19320f2
    dcd     0xe19300f0
    dcd     0xe58d1004
    dcd     0xe58d2000
    dcd     0xe58d0008
    dcd     0xe3550a03
    dcd     0xca000004
    dcd     0xe28d0000
    dcd     0xe28d100c
    bl      VEC_DotProduct
    dcd     0xe3500b02
    dcd     0xca000003
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe5c011c7
    dcd     0xea000005
    dcd     0xe5940000
    dcd     0xe3550c0a
    dcd     0xd3a01006
    dcd     0xd5c011c7
    dcd     0xc3a01007
    dcd     0xc5c011c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd80f8
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
}
