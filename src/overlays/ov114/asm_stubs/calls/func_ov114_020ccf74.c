extern void func_ov107_020cab14(void);
extern void FX_Sqrt(void);
extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_01ff8d18(void);
extern void VEC_CrossProduct(void);
extern void func_01ffa724(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void data_02042264(void);

asm void func_ov114_020ccf74(void)
{
    dcd     0xe92d40f8
    dcd     0xe24dd010
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe28d1000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe1b07000
    dcd     0x028dd010
    dcd     0xe5840010
    dcd     0x08bd80f8
    dcd     0xe5946000
    dcd     0xe59d0000
    bl      FX_Sqrt
    dcd     0xe5972080
    dcd     0xe5961080
    dcd     0xe0821001
    dcd     0xe0401001
    dcd     0xe58d1000
    dcd     0xe5940000
    dcd     0xe59002d8
    dcd     0xe1510000
    dcd     0xc28dd010
    dcd     0xc8bd80f8
    dcd     0xe5940010
    dcd     0xe5941004
    dcd     0xe28d2004
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe59d0004
    dcd     0xe59d100c
    bl      func_020050b4
    dcd     0xe5840018
    dcd     0xe28d0004
    dcd     0xe3a02000
    dcd     0xe1a01000
    dcd     0xe58d2008
    bl      func_01ff8d18
    dcd     0xe59f10f8
    dcd     0xe28d0004
    dcd     0xe2842050
    bl      VEC_CrossProduct
    dcd     0xe1d404d8
    dcd     0xe2841050
    dcd     0xe1a02001
    dcd     0xe1a00300
    bl      func_01ffa724
    dcd     0xe59f00d8
    bl      func_02023eb4
    dcd     0xe2900000
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01006
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd80f8
    dcd     0xe59d1000
    dcd     0xe3510901
    dcd     0xda000010
    dcd     0xe59f0098
    bl      func_02023eb4
    dcd     0xe2900000
    dcd     0x0a000003
    dcd     0xe594004c
    dcd     0xe3500000
    dcd     0xc28dd010
    dcd     0xc8bd80f8
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd80f8
    dcd     0xe594004c
    dcd     0xe3500000
    dcd     0xc28dd010
    dcd     0xc8bd80f8
    dcd     0xe3510b02
    dcd     0xe5940000
    dcd     0xe3a02000
    dcd     0xda000006
    dcd     0xe3a0100a
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd80f8
    dcd     0xe3a01009
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd80f8
    dcd     data_02042264
    dcd     0x00000101
}
