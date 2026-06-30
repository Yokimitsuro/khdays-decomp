extern void func_ov022_020ad114(void);
extern void func_ov022_020ad0c0(void);
extern void VEC_Subtract(void);
extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_0202c33c(void);
extern void func_01ffd0e8(void);
extern void VEC_Add(void);
extern void func_ov039_020b498c(void);

asm void func_ov039_020b4168(void)
{
    dcd     0xe92d40f0
    dcd     0xe24dd00c
    dcd     0xe1a05001
    dcd     0xe5951008
    dcd     0xe1a06000
    dcd     0xe3510000
    dcd     0xe1a04002
    dcd     0x028dd00c
    dcd     0x08bd80f0
    dcd     0xe5d5102c
    dcd     0xe1d606f6
    dcd     0xe1510000
    dcd     0x13a00000
    dcd     0x15850008
    dcd     0xe1a00006
    bl      func_ov022_020ad114
    dcd     0xe3500000
    dcd     0x0a00000d
    dcd     0xe1a00006
    bl      func_ov022_020ad0c0
    dcd     0xe28d2000
    dcd     0xe2851014
    bl      VEC_Subtract
    dcd     0xe595700c
    dcd     0xe28d0000
    bl      VEC_Mag
    dcd     0xe1500007
    dcd     0xca000008
    dcd     0xe28d0000
    bl      VEC_Mag
    dcd     0xe1a07000
    dcd     0xea000004
    dcd     0xe2850020
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe595700c
    dcd     0xe28d0000
    bl      VEC_Mag
    dcd     0xe3500000
    dcd     0x0a000002
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe28dc000
    dcd     0xe2853020
    dcd     0xe89c0007
    dcd     0xe8830007
    dcd     0xe1a00007
    dcd     0xe1a0100c
    dcd     0xe1a0200c
    bl      func_01ffa724
    dcd     0xe5d5002c
    dcd     0xe28d2000
    dcd     0xe2851014
    dcd     0xe3a03b02
    bl      func_0202c33c
    dcd     0xe3500000
    dcd     0xe28d1000
    dcd     0x0a000004
    dcd     0xe2852014
    dcd     0xe590000c
    dcd     0xe1a03002
    bl      func_01ffd0e8
    dcd     0xea000002
    dcd     0xe2850014
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe5950010
    dcd     0xe0800004
    dcd     0xe3500a06
    dcd     0xb28dd00c
    dcd     0xe5850010
    dcd     0xb8bd80f0
    dcd     0xe3a04000
    dcd     0xe5854010
    dcd     0xe5950004
    dcd     0xe2801001
    dcd     0xe5851004
    dcd     0xe5950000
    dcd     0xe1510000
    dcd     0xa3a04001
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov039_020b498c
    dcd     0xe3540000
    dcd     0x13a00000
    dcd     0x15850008
    dcd     0xe28dd00c
    dcd     0xe8bd80f0
}
