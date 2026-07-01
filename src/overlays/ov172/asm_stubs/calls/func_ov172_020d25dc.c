extern void VEC_Mag(void);
extern void VEC_Subtract(void);
extern void data_02042258(void);
extern void func_01ff8d18(void);
extern void func_01fff888(void);
extern void func_01fff8b8(void);
extern void func_01fff8e8(void);
extern void func_0202ed60(void);
extern void func_0202f384(void);
extern void func_0202f55c(void);
extern void func_0203c634(void);
extern void func_ov022_020ad8e0(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c8eb8(void);
extern void func_ov107_020ca918(void);
extern void func_ov107_020cab14(void);
extern void func_ov172_020d2954(void);

asm void func_ov172_020d25dc(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd040
    dcd     0xe1a0a000
    dcd     0xe59a7004
    dcd     0xe3a01000
    dcd     0xe5976000
    dcd     0xe1a00006
    bl      func_ov107_020cab14
    dcd     0xe3500000
    dcd     0x0a00001f
    dcd     0xe5971008
    dcd     0xe28d2034
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe28d0034
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59f1320
    dcd     0xe28d0014
    dcd     0xe28d2034
    bl      func_0202ed60
    dcd     0xe59a2000
    dcd     0xe3a01f4b
    dcd     0xe592202c
    dcd     0xe59f3308
    dcd     0xe0040192
    dcd     0xe0c12493
    dcd     0xe1a02fa4
    dcd     0xe2870020
    dcd     0xe08212c1
    dcd     0xe1a02000
    dcd     0xe28d3014
    bl      func_0202f55c
    mov r0, #0
    dcd     0xe5870030
    dcd     0xe5870034
    dcd     0xe3a00c05
    dcd     0xe5870038
    dcd     0xe2870030
    dcd     0xe2871020
    dcd     0xe1a02000
    bl      func_0202f384
    dcd     0xe5970000
    dcd     0xe28d2024
    dcd     0xe590038c
    dcd     0xe2861074
    bl      func_ov107_020c8eb8
    dcd     0xe1a09000
    dcd     0xe3590000
    dcd     0xe3a08000
    dcd     0xda000046
    dcd     0xe28d5024
    dcd     0xe28d4008
    dcd     0xe1a0b008
    dcd     0xe7950108
    dcd     0xe1a02004
    dcd     0xe2800074
    dcd     0xe2861074
    bl      VEC_Subtract
    dcd     0xe58db00c
    dcd     0xe1a00004
    dcd     0xe1a01004
    bl      func_01ff8d18
    dcd     0xe5971000
    dcd     0xe3a00c02
    dcd     0xe58d4000
    dcd     0xe58d0004
    dcd     0xe7950108
    dcd     0xe591238c
    dcd     0xe3a03000
    bl      func_ov107_020ca918
    dcd     0xe3500000
    dcd     0x0a00002d
    dcd     0xe5971000
    mov r0, #0
    dcd     0xe591438c
    dcd     0xe24d3008
    dcd     0xe58d0004
    dcd     0xe28400b0
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe1a00004
    dcd     0xe3a01002
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    dcd     0xe5970000
    dcd     0xe5973008
    dcd     0xe3a01d05
    dcd     0xe3a02006
    bl      func_ov107_020c5af8
    dcd     0xe28d5024
    dcd     0xe7950108
    dcd     0xe2874010
    dcd     0xe2800074
    dcd     0xe890000f
    dcd     0xe884000f
    dcd     0xe7950108
    dcd     0xe590018c
    dcd     0xe587000c
    dcd     0xe3500000
    dcd     0x0a000009
    dcd     0xe3a01001
    bl      func_ov022_020ad8e0
    mov r0, #0
    dcd     0xe587004c
    dcd     0xe1da12d0
    dcd     0xe59f21c4
    dcd     0xe1a0000a
    bl      func_0203c634
    dcd     0xe28dd040
    dcd     0xe8bd8ff8
    dcd     0xe5970000
    dcd     0xe3a02000
    dcd     0xe5c021c7
    dcd     0xe1da12d0
    dcd     0xe1a0000a
    bl      func_0203c634
    dcd     0xe28dd040
    dcd     0xe8bd8ff8
    dcd     0xe2888001
    dcd     0xe1580009
    dcd     0xbaffffbb
    dcd     0xe5970008
    dcd     0xe28d2034
    dcd     0xe287103c
    bl      VEC_Subtract
    dcd     0xe5970000
    dcd     0xe3a03001
    dcd     0xe5d0117a
    dcd     0xe1a04003
    dcd     0xe1a02f81
    dcd     0xe1b02fa2
    dcd     0x1a000002
    dcd     0xe1a01f01
    dcd     0xe1b01fa1
    dcd     0x03a04000
    dcd     0xe3540000
    dcd     0x1a000003
    dcd     0xe5d0117a
    dcd     0xe1a01e01
    dcd     0xe1b01fa1
    dcd     0x03a03000
    dcd     0xe5971048
    dcd     0xe3510000
    dcd     0x1a00001b
    dcd     0xe3530000
    dcd     0xe5904004
    dcd     0x1a000005
    dcd     0xe594007c
    dcd     0xe28d2034
    dcd     0xe287103c
    dcd     0xe3a03000
    bl      func_01fff888
    dcd     0xe1a03000
    dcd     0xe3530000
    dcd     0x1a000005
    dcd     0xe594007c
    dcd     0xe28d2034
    dcd     0xe287103c
    dcd     0xe3a03000
    bl      func_01fff8b8
    dcd     0xe1a03000
    dcd     0xe3530000
    dcd     0x1a000008
    mov r0, #0
    dcd     0xe58d0000
    dcd     0xe5971000
    dcd     0xe594007c
    dcd     0xe5913080
    dcd     0xe28d2034
    dcd     0xe287103c
    bl      func_01fff8e8
    dcd     0xe1a03000
    dcd     0xe5970008
    dcd     0xe287403c
    dcd     0xe8900007
    dcd     0xe8840007
    dcd     0xe3530000
    dcd     0x0a000017
    mov r0, #0
    dcd     0xe58d0004
    dcd     0xe5970008
    dcd     0xe24d3008
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5970000
    dcd     0xe3a01001
    dcd     0xe590038c
    dcd     0xe893000c
    bl      func_ov107_020c0b90
    dcd     0xe5970000
    dcd     0xe5973008
    dcd     0xe3a01d05
    dcd     0xe3a02007
    bl      func_ov107_020c5af8
    dcd     0xe5970000
    dcd     0xe3a02000
    dcd     0xe5c021c7
    dcd     0xe1da12d0
    dcd     0xe1a0000a
    bl      func_0203c634
    dcd     0xe28dd040
    dcd     0xe8bd8ff8
    dcd     0xe28d0034
    bl      VEC_Mag
    dcd     0xe5971048
    dcd     0xe0810000
    dcd     0xe3500a15
    dcd     0xb28dd040
    dcd     0xe5870048
    dcd     0xb8bd8ff8
    dcd     0xe5970000
    dcd     0xe3a02000
    dcd     0xe5c021c7
    dcd     0xe1da12d0
    dcd     0xe1a0000a
    bl      func_0203c634
    dcd     0xe28dd040
    dcd     0xe8bd8ff8
    dcd     data_02042258
    dcd     0x51eb851f
    dcd     func_ov172_020d2954
}
