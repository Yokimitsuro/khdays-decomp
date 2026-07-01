extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void VEC_DotProduct(void);
extern void func_ov261_020d0348(void);
extern void func_ov015_02080c00(void);
extern void func_0203c634(void);
extern void VEC_CrossProduct(void);
extern void FX_Inv(void);
extern void func_01ffa724(void);
extern void VEC_Add(void);
extern void data_02042264(void);
extern void data_02042258(void);
extern void data_02041dc8(void);

asm void func_ov261_020d122c(void)
{
    dcd     0xe92d40f8
    dcd     0xe24dd018
    dcd     0xe1a07000
    dcd     0xe5974004
    dcd     0xe3a00024
    dcd     0xe5941000
    dcd     0xe5d42048
    dcd     0xe59133a0
    dcd     0xe5941004
    dcd     0xe2833018
    dcd     0xe0253092
    dcd     0xe28d200c
    dcd     0xe2850014
    bl      VEC_Subtract
    dcd     0xe28d000c
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe5941040
    dcd     0xe1a06000
    dcd     0xe3510000
    dcd     0x1a00000f
    dcd     0xe59f11d4
    dcd     0xe28d000c
    bl      VEC_DotProduct
    dcd     0xe3500000
    dcd     0xb2600000
    dcd     0xe3500b03
    dcd     0xda000008
    dcd     0xe59f01b8
    dcd     0xe2843074
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe59f01ac
    dcd     0xe28d300c
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe3a06b02
    dcd     0xe5970000
    dcd     0xe5941040
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe5840040
    dcd     0xe3500a02
    dcd     0xe28d100c
    dcd     0xba000014
    dcd     0xe59f217c
    dcd     0xe284001c
    bl      func_ov261_020d0348
    dcd     0xe5941000
    dcd     0xe3a02000
    dcd     0xe59103a0
    dcd     0xe5d113ad
    dcd     0xe5900000
    dcd     0xe1a03002
    bl      func_ov015_02080c00
    dcd     0xe2850014
    dcd     0xe584002c
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d712d0
    dcd     0xe1a00007
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd018
    dcd     0xe8bd80f8
    dcd     0xe28d2000
    dcd     0xe2840074
    bl      VEC_CrossProduct
    dcd     0xe3560b06
    dcd     0xba000015
    dcd     0xe2460b06
    dcd     0xe3a01b02
    bl      FX_Inv
    dcd     0xe1a05000
    dcd     0xe3550a01
    dcd     0xc3a05a01
    dcd     0xca000001
    dcd     0xe3550000
    dcd     0xb3a05000
    dcd     0xe28d1000
    dcd     0xe2650a01
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe28d100c
    dcd     0xe1a00005
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe28d0000
    dcd     0xe28d100c
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xea00001b
    dcd     0xe3560b02
    dcd     0xaa000019
    dcd     0xe2660b02
    dcd     0xe3a01b02
    bl      FX_Inv
    dcd     0xe1a05000
    dcd     0xe3550a01
    dcd     0xc3a05a01
    dcd     0xca000001
    dcd     0xe3550000
    dcd     0xb3a05000
    dcd     0xe28d100c
    dcd     0xe3a00a01
    dcd     0xe1a02001
    dcd     0xe2600000
    bl      func_01ffa724
    dcd     0xe28d1000
    dcd     0xe2650a01
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe28d100c
    dcd     0xe1a00005
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe28d0000
    dcd     0xe28d100c
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe28d1000
    dcd     0xe2842030
    dcd     0xe3a00b02
    bl      func_01ffa724
    dcd     0xe5971000
    dcd     0xe3a0001e
    dcd     0xe591202c
    dcd     0xe59f1034
    dcd     0xe0030092
    dcd     0xe0c50391
    dcd     0xe1a00fa3
    dcd     0xe08050c5
    dcd     0xe59f201c
    dcd     0xe28d1000
    dcd     0xe284001c
    dcd     0xe584503c
    bl      func_ov261_020d0348
    dcd     0xe28dd018
    dcd     0xe8bd80f8
    dcd     data_02042264
    dcd     data_02042258
    dcd     data_02041dc8
    dcd     0x66666667
}
