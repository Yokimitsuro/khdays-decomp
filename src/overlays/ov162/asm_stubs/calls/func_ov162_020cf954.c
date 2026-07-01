extern void VEC_CrossProduct(void);
extern void VEC_Subtract(void);
extern void data_0203d210(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020cab14(void);

asm void func_ov162_020cf954(void) {

    dcd 0xe92d47f8
    dcd 0xe24dd024
    dcd 0xe1a06000
    dcd 0xe5964004
    dcd 0xe3a01000
    dcd 0xe5940000
    bl func_ov107_020cab14
    dcd 0xe5840008
    dcd 0xe3500000
    dcd 0x1a000008
    dcd 0xe5940000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d612d0
    dcd 0xe1a00006
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd024
    dcd 0xe8bd87f8
    dcd 0xe5941000
    dcd 0xe28d2018
    dcd 0xe2800e19
    dcd 0xe28110b0
    bl VEC_Subtract
    mov r0, #0
    dcd 0xe58d001c
    dcd 0xe28d0018
    dcd 0xe5945000
    dcd 0xe5947008
    dcd 0xe1a01000
    bl func_01ff8d18
    dcd 0xe5973080
    dcd 0xe5952080
    dcd 0xe59d1020
    dcd 0xe0832002
    dcd 0xe0405002
    dcd 0xe59d0018
    bl func_020050b4
    dcd 0xe5840010
    dcd 0xe1d415dc
    mov r0, #0
    dcd 0xe59fc134
    dcd 0xe1a01601
    dcd 0xe58d1004
    dcd 0xe58d0000
    dcd 0xe58d0008
    dcd 0xe594800c
    dcd 0xe59f3120
    dcd 0xe1a07fc8
    dcd 0xe089a398
    dcd 0xe0299c98
    dcd 0xe0299397
    dcd 0xe29a3000
    dcd 0xe2a93b02
    dcd 0xe1a03203
    dcd 0xe1a03823
    dcd 0xe1a03243
    dcd 0xe1a07083
    dcd 0xe58d0010
    dcd 0xe28d000c
    dcd 0xe59fe0f0
    dcd 0xe1a03087
    dcd 0xe19ec0f3
    dcd 0xe2873001
    dcd 0xe1a03083
    dcd 0xe19e30f3
    dcd 0xe28d1000
    dcd 0xe1a02000
    dcd 0xe58dc00c
    dcd 0xe58d3014
    bl VEC_CrossProduct
    dcd 0xe594003c
    dcd 0xe28d100c
    dcd 0xe2842018
    bl func_01ffa724
    dcd 0xe5940034
    dcd 0xe3500000
    dcd 0xca00001d
    dcd 0xe5940000
    dcd 0xe5905224
    dcd 0xe5900228
    dcd 0xe0500005
    dcd 0x42600000
    dcd 0xe2800001
    bl func_02023eb4
    dcd 0xe0851000
    dcd 0xe3a00065
    dcd 0xe5841034
    bl func_02023eb4
    dcd 0xe2800000
    dcd 0xe3500050
    dcd 0xe5940000
    dcd 0xe3a02000
    dcd 0xca000006
    dcd 0xe3a01006
    dcd 0xe5c011c7
    dcd 0xe1d612d0
    dcd 0xe1a00006
    bl func_0203c634
    dcd 0xe28dd024
    dcd 0xe8bd87f8
    dcd 0xe3a01007
    dcd 0xe5c011c7
    dcd 0xe1d612d0
    dcd 0xe1a00006
    bl func_0203c634
    dcd 0xe28dd024
    dcd 0xe8bd87f8
    dcd 0xe3550a05
    dcd 0xb28dd024
    dcd 0xb8bd87f8
    dcd 0xe5940000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d612d0
    dcd 0xe1a00006
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd024
    dcd 0xe8bd87f8
    dcd 0x000028be
    dcd 0x60db9391
    dcd data_0203d210
}
