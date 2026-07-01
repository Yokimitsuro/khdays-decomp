extern void func_ov107_020cab14(void);
extern void FX_Sqrt(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov117_020cc5c0(void);
extern void func_0202f384(void);
extern void VEC_CrossProduct(void);
extern void func_01ffa724(void);
extern char data_02042258[];
extern char data_02042264[];

asm void func_ov117_020cccb4(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe28d1000
    dcd     0xe5940000
    bl      func_ov107_020cab14
    dcd     0xe1b07000
    dcd     0xe5840004
    dcd     0x08bd80f8
    dcd     0xe5946000
    dcd     0xe59d0000
    bl      FX_Sqrt
    dcd     0xe5972080
    dcd     0xe5961080
    dcd     0xe0821001
    dcd     0xe0402001
    dcd     0xe58d2000
    dcd     0xe5941000
    dcd     0xe59102d8
    dcd     0xe1520000
    dcd     0xc8bd80f8
    dcd     0xe5940040
    dcd     0xe3500000
    dcd     0xca00000f
    dcd     0xe5916224
    dcd     0xe5910228
    dcd     0xe0500006
    dcd     0x42600000
    dcd     0xe2800001
    bl      func_02023eb4
    dcd     0xe0860000
    dcd     0xe5840040
    dcd     0xe5940000
    dcd     0xe3a01006
    dcd     0xe5c011c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd80f8
    dcd     0xe3520a02
    dcd     0xca00000f
    dcd     0xe1a00004
    dcd     0xe2841018
    bl      func_ov117_020cc5c0
    dcd     0xe59f2048
    dcd     0xe284002c
    dcd     0xe2841008
    bl      func_0202f384
    dcd     0xe284002c
    dcd     0xe59f1038
    dcd     0xe1a02000
    bl      VEC_CrossProduct
    dcd     0xe284102c
    dcd     0xe594005c
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe8bd80f8
    dcd     0xe3a00004
    dcd     0xe5c101c7
    dcd     0xe1d512d0
    dcd     0xe1a00005
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe8bd80f8
    dcd     data_02042258
    dcd     data_02042264
}
