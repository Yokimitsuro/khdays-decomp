extern void func_ov145_020ce618(void);
extern void func_01ffa724(void);
extern void VEC_Add(void);
extern void func_01fffd70(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void VEC_DotProduct(void);
extern void func_ov145_020ce700(void);
extern void func_01fffde0(void);
extern void func_01fffd8c(void);
extern void data_0203d210(void);
extern void data_02042258(void);

asm void func_ov145_020ce950(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd048
    dcd     0xe5907004
    mov r0, #0
    dcd     0xe58d0008
    dcd     0xe59d2008
    dcd     0xe5973000
    dcd     0xe242b106
    dcd     0xe5932004
    dcd     0xe1a00007
    dcd     0xe3a01001
    dcd     0xe58d2004
    bl      func_ov145_020ce618
    dcd     0xe1b09000
    dcd     0x428dd048
    dcd     0x43a00000
    dcd     0x48bd8ff8
    dcd     0xe5972030
    dcd     0xe59f0208
    dcd     0xe59f1208
    dcd     0xe0845092
    dcd     0xe0244192
    dcd     0xe1a01fc2
    dcd     0xe0244091
    dcd     0xe2950000
    dcd     0xe2a40b02
    dcd     0xe1a00200
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a02080
    dcd     0xe2820001
    dcd     0xe3a03000
    dcd     0xe59f11d8
    dcd     0xe1a02082
    dcd     0xe19140f2
    dcd     0xe1a00080
    dcd     0xe19100f0
    dcd     0xe28d103c
    dcd     0xe28d2024
    dcd     0xe58d0044
    dcd     0xe58d403c
    dcd     0xe58d3040
    dcd     0xe2430b0a
    bl      func_01ffa724
    dcd     0xe5971000
    dcd     0xe28d0024
    dcd     0xe2811074
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe59d0004
    dcd     0xe28000a8
    bl      func_01fffd70
    dcd     0xe3500000
    dcd     0x03a0a000
    dcd     0x1590a000
    dcd     0xe35a0000
    dcd     0x0a000059
    dcd     0xe59f0178
    dcd     0xe28d300c
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe28d5030
    dcd     0xe28d6018
    dcd     0xe3a04000
    dcd     0xe59a0040
    dcd     0xe1a00f00
    dcd     0xe1b00fc0
    dcd     0x0a000046
    dcd     0xe1da06b0
    dcd     0xe1a00c00
    dcd     0xe1a00c20
    dcd     0xe3100001
    dcd     0x0a000041
    dcd     0xe28a0074
    dcd     0xe8900007
    dcd     0xe8860007
    dcd     0xe5971000
    dcd     0xe1a00006
    dcd     0xe1a02005
    dcd     0xe2811074
    bl      VEC_Subtract
    mov r0, #0
    dcd     0xe58d0034
    dcd     0xe1a00005
    dcd     0xe1a01005
    bl      func_01ff8d18
    dcd     0xe1a08000
    dcd     0xe1a00006
    dcd     0xe28d1024
    dcd     0xe1a02005
    bl      VEC_Subtract
    mov r0, #0
    dcd     0xe58d0034
    dcd     0xe1a00005
    dcd     0xe1a01005
    bl      func_01ff8d18
    dcd     0xe3500000
    dcd     0x028d000c
    dcd     0x08900007
    dcd     0x08850007
    dcd     0xe3580b0a
    dcd     0xda000009
    dcd     0xe3590000
    dcd     0xda000022
    dcd     0xe1580009
    dcd     0xca000020
    dcd     0xe1a00005
    dcd     0xe28d103c
    bl      VEC_DotProduct
    dcd     0xe59f10ac
    dcd     0xe1500001
    dcd     0xba00001a
    dcd     0xe59a1080
    dcd     0xe1a00007
    dcd     0xe58d1000
    dcd     0xe896000e
    bl      func_ov145_020ce700
    dcd     0xe3500000
    dcd     0x0a000013
    dcd     0xe5da01b4
    bl      func_01fffde0
    dcd     0xe5902000
    dcd     0xe5901004
    mov r0, #0
    dcd     0xe0011000
    dcd     0xe2022801
    dcd     0xe1510000
    dcd     0x01520004
    dcd     0x0a000006
    dcd     0xe5971000
    dcd     0xe59123a8
    dcd     0xe3520000
    dcd     0x0a000005
    dcd     0xe5da01b4
    dcd     0xe12fff32
    dcd     0xea000002
    dcd     0xe158000b
    dcd     0xb1a0b008
    dcd     0xb58da008
    dcd     0xe59d0004
    dcd     0xe28000a8
    bl      func_01fffd8c
    dcd     0xe3500000
    dcd     0x03a0a000
    dcd     0x1590a000
    dcd     0xe35a0000
    dcd     0x1affffac
    dcd     0xe59d0008
    dcd     0xe28dd048
    dcd     0xe8bd8ff8
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
    dcd     data_02042258
    dcd     0x00000f74
}
