extern void VEC_CrossProduct(void);
extern char data_02042264[];
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov118_020d13cc(void);

asm void func_ov118_020d12d8(void)
{
    dcd     0xe92d40f8
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe3a0101e
    dcd     0xe594c000
    dcd     0xe59f00c8
    dcd     0xe1dc36b0
    dcd     0xe1a02803
    dcd     0xe1a02c22
    dcd     0xe3822006
    dcd     0xe3c33cff
    dcd     0xe1a02c02
    dcd     0xe1832822
    dcd     0xe1cc26b0
    dcd     0xe5952000
    dcd     0xe592202c
    dcd     0xe0010192
    dcd     0xe5841028
    bl      func_02023eb4
    dcd     0xe2406a01
    dcd     0xe59f008c
    bl      func_02023eb4
    dcd     0xe2407a01
    dcd     0xe59f0080
    bl      func_02023eb4
    dcd     0xe2400a01
    dcd     0xe5840078
    dcd     0xe2840078
    dcd     0xe584707c
    dcd     0xe1a01000
    dcd     0xe5846080
    bl      func_01ff8d18
    dcd     0xe59f1060
    dcd     0xe2840078
    dcd     0xe2842084
    bl      VEC_CrossProduct
    dcd     0xe2841084
    dcd     0xe2840078
    dcd     0xe1a02001
    bl      VEC_CrossProduct
    dcd     0xe59f0044
    bl      func_02023eb4
    dcd     0xe2841084
    dcd     0xe2800c05
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe3a03000
    dcd     0xe5843060
    dcd     0xe5941074
    dcd     0xe59f2024
    dcd     0xe591118c
    dcd     0xe1a00005
    dcd     0xe5841090
    dcd     0xe5843038
    dcd     0xe1d512d0
    bl      func_0203c634
    dcd     0xe8bd80f8
    dcd     0x00002001
    dcd     data_02042264
    dcd     0x00000501
    dcd     func_ov118_020d13cc
}
