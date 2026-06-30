extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Add(void);
extern void VEC_Subtract(void);
extern void data_0203d210(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_01ffd144(void);
extern void func_01fff888(void);
extern void func_01fff948(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov174_020d1acc(void);

asm void func_ov174_020d190c(void)
{
    dcd     0xe92d41f8
    dcd     0xe24dd03c
    dcd     0xe1a07000
    dcd     0xe8970011
    dcd     0xe5941048
    dcd     0xe590002c
    dcd     0xe0810000
    dcd     0xe3500c06
    dcd     0xb28dd03c
    dcd     0xe5840048
    dcd     0xb8bd81f8
    dcd     0xe5940010
    dcd     0xe3500000
    dcd     0x0a000056
    dcd     0xe59f016c
    bl      func_02023eb4
    dcd     0xe3e01ec9
    dcd     0xe5946000
    dcd     0xe0805001
    dcd     0xe5943010
    dcd     0xe2861074
    dcd     0xe28d2000
    dcd     0xe2830074
    dcd     0xe5966004
    bl      VEC_Subtract
    dcd     0xe3a02000
    dcd     0xe28d0000
    dcd     0xe28d100c
    dcd     0xe58d2004
    bl      func_01ff8d18
    dcd     0xe5941010
    dcd     0xe5940000
    dcd     0xe5912080
    dcd     0xe5900080
    dcd     0xe28d100c
    dcd     0xe0820000
    dcd     0xe2800a01
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe59f110c
    dcd     0xe59f210c
    dcd     0xe08e8195
    dcd     0xe02ee295
    dcd     0xe1a0cfc5
    dcd     0xe02ee19c
    dcd     0xe2981000
    dcd     0xe2ae1b02
    dcd     0xe1a01201
    dcd     0xe1a01821
    dcd     0xe1a01241
    dcd     0xe1a02081
    dcd     0xe1a01082
    dcd     0xe59f30e0
    dcd     0xe2822001
    dcd     0xe1a02082
    dcd     0xe19310f1
    dcd     0xe19320f2
    dcd     0xe28d0018
    bl      MTX_RotY33_
    dcd     0xe28d000c
    dcd     0xe28d1018
    dcd     0xe2842020
    bl      MTX_MultVec33
    dcd     0xe2840020
    dcd     0xe28d1000
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe2840020
    dcd     0xe28d100c
    bl      func_01ff8d18
    dcd     0xe3500b1e
    dcd     0xda000003
    dcd     0xe28d100c
    dcd     0xe2842020
    dcd     0xe3a00b1e
    bl      func_01ffa724
    dcd     0xe5942000
    dcd     0xe596007c
    dcd     0xe5941008
    dcd     0xe5923080
    dcd     0xe2842020
    bl      func_01fff948
    dcd     0xe3500000
    dcd     0x0a000003
    dcd     0xe2841020
    dcd     0xe590000c
    dcd     0xe1a02001
    bl      func_01ffd144
    dcd     0xe596007c
    dcd     0xe5941008
    dcd     0xe2842020
    dcd     0xe3a03000
    bl      func_01fff888
    dcd     0xe3500000
    dcd     0x0a000003
    dcd     0xe2841020
    dcd     0xe590000c
    dcd     0xe1a02001
    bl      func_01ffd144
    dcd     0xe3a00000
    dcd     0xe5840010
    dcd     0xe1d712d0
    dcd     0xe59f201c
    dcd     0xe1a00007
    bl      func_0203c634
    dcd     0xe28dd03c
    dcd     0xe8bd81f8
    dcd     0x00001923
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
    dcd     func_ov174_020d1acc
}
