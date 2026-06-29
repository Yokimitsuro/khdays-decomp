extern void VEC_DotProduct(void);
extern void VEC_Subtract(void);
extern char data_02042258[];
extern void func_01ff8d18(void);
extern void func_01fff8e8(void);
extern void func_01fff920(void);
extern void func_01fffd70(void);
extern void func_01fffd8c(void);
extern void func_0202f384(void);

asm void func_ov291_020cc670(void)
{
    dcd     0xe92d4ff0
    dcd     0xe24dd01c
    dcd     0xe1a0a000
    dcd     0xe59a8004
    dcd     0xe3a07000
    dcd     0xe28800a8
    bl      func_01fffd70
    dcd     0xe3500000
    dcd     0x01a09007
    dcd     0x15909000
    dcd     0xe3590000
    dcd     0x0a00004d
    dcd     0xe3a0b000
    dcd     0xe28d6004
    dcd     0xe28d5010
    dcd     0xe1a0400b
    dcd     0xe5990040
    dcd     0xe1a00f00
    dcd     0xe1b00fc0
    dcd     0x0a00003e
    dcd     0xe1d906b0
    dcd     0xe1a00c00
    dcd     0xe1a00c20
    dcd     0xe3100001
    dcd     0x0a000039
    dcd     0xe59a1388
    dcd     0xe59f2104
    dcd     0xe1a00006
    dcd     0xe2811030
    bl      func_0202f384
    dcd     0xe59a1388
    dcd     0xe2890074
    dcd     0xe1a02005
    dcd     0xe2811040
    bl      VEC_Subtract
    dcd     0xe59d0014
    dcd     0xe3500000
    dcd     0xb2600000
    dcd     0xe3500b0e
    dcd     0xca00002a
    dcd     0xe1a00005
    dcd     0xe1a01005
    dcd     0xe58d4014
    bl      func_01ff8d18
    dcd     0xe5991080
    dcd     0xe0400001
    dcd     0xe3500a0a
    dcd     0xca000022
    dcd     0xe3500b06
    dcd     0xba000004
    dcd     0xe1a00006
    dcd     0xe1a01005
    bl      VEC_DotProduct
    dcd     0xe3500b02
    dcd     0xba00001b
    dcd     0xe598007c
    dcd     0xe3500000
    dcd     0x0a000017
    dcd     0xe1a02005
    dcd     0xe2890074
    dcd     0xe28a1074
    bl      VEC_Subtract
    dcd     0xe58db000
    dcd     0xe598007c
    dcd     0xe28a1074
    dcd     0xe1a02005
    dcd     0xe3a03c03
    bl      func_01fff8e8
    dcd     0xe3500000
    dcd     0x0a000002
    dcd     0xe5900008
    dcd     0xe3500000
    dcd     0x0a000009
    dcd     0xe598007c
    dcd     0xe1a02005
    dcd     0xe28a1074
    bl      func_01fff920
    dcd     0xe3500000
    dcd     0x0a000002
    dcd     0xe5900008
    dcd     0xe3500000
    dcd     0x0a000000
    dcd     0xe1a07009
    dcd     0xe28800a8
    bl      func_01fffd8c
    dcd     0xe3500000
    dcd     0x03a09000
    dcd     0x15909000
    dcd     0xe3590000
    dcd     0x1affffb5
    dcd     0xe1a00007
    dcd     0xe28dd01c
    dcd     0xe8bd8ff0
    dcd     data_02042258
}
