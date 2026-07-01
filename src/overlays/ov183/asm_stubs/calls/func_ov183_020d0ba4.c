extern void func_ov107_020cab14(void);
extern void FX_Sqrt(void);
extern void VEC_Subtract(void);
extern void func_01ffa724(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void VEC_CrossProduct(void);
extern void VEC_Add(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void data_02042264(void);

asm void func_ov183_020d0ba4(void)
{
    dcd     0xe92d40f0
    dcd     0xe24dd01c
    dcd     0xe1a05000
    dcd     0xe5951000
    dcd     0xe3a0001e
    dcd     0xe591102c
    dcd     0xe59f221c
    dcd     0xe0030091
    dcd     0xe1a00fa3
    dcd     0xe0c31392
    dcd     0xe5954004
    dcd     0xe08031c3
    dcd     0xe5843020
    dcd     0xe5940000
    dcd     0xe28d1000
    bl      func_ov107_020cab14
    dcd     0xe1b07000
    dcd     0x028dd01c
    dcd     0xe5840010
    dcd     0x08bd80f0
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
    dcd     0xc28dd01c
    dcd     0xc8bd80f0
    dcd     0xe5940010
    dcd     0xe5941004
    dcd     0xe28d2010
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe3a00a01
    dcd     0xe28d1010
    dcd     0xe28d2004
    dcd     0xe2600000
    bl      func_01ffa724
    dcd     0xe28d0004
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe28d1004
    dcd     0xe3a00080
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe59d0010
    dcd     0xe59d1018
    bl      func_020050b4
    dcd     0xe5840018
    mov r0, #0
    dcd     0xe58d0014
    dcd     0xe28d0010
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59f114c
    dcd     0xe28d0010
    dcd     0xe2842054
    bl      VEC_CrossProduct
    dcd     0xe2840054
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe5940084
    dcd     0xe2841054
    dcd     0xe1a00380
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe59d0000
    dcd     0xe3500a06
    dcd     0xaa000003
    dcd     0xe2840054
    dcd     0xe28d1004
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe59f0104
    bl      func_02023eb4
    dcd     0xe2900000
    dcd     0x1a000008
    dcd     0xe5940000
    dcd     0xe3a01005
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd01c
    dcd     0xe8bd80f0
    dcd     0xe59d1000
    dcd     0xe3510a07
    dcd     0xda000010
    dcd     0xe59f00c4
    bl      func_02023eb4
    dcd     0xe2900000
    dcd     0x0a000003
    dcd     0xe5940074
    dcd     0xe3500000
    dcd     0xc28dd01c
    dcd     0xc8bd80f0
    dcd     0xe5940000
    dcd     0xe3a01004
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd01c
    dcd     0xe8bd80f0
    dcd     0xe5940074
    dcd     0xe3500000
    dcd     0xc28dd01c
    dcd     0xc8bd80f0
    dcd     0xe3510a03
    dcd     0xe3a02000
    dcd     0xda000007
    dcd     0xe5940000
    dcd     0xe3a01009
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd01c
    dcd     0xe8bd80f0
    dcd     0xe3510a01
    dcd     0xe5940000
    dcd     0xda000006
    dcd     0xe3a01008
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd01c
    dcd     0xe8bd80f0
    dcd     0xe3a01007
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd01c
    dcd     0xe8bd80f0
    dcd     0x66666667
    dcd     data_02042264
    dcd     0x00000101
}
