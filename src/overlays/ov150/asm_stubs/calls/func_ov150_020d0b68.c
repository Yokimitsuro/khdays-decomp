extern void FX_Inv(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020cab14(void);
extern void func_ov150_020d0d04(void);

asm void func_ov150_020d0b68(void) {

    dcd 0xe92d40f0
    dcd 0xe24dd00c
    dcd 0xe1a07000
    dcd 0xe5975004
    dcd 0xe3a01000
    dcd 0xe5950000
    bl func_ov107_020cab14
    dcd 0xe5850004
    dcd 0xe3500000
    dcd 0x1a000008
    dcd 0xe5950000
    dcd 0xe3a01002
    dcd 0xe5c011c7
    dcd 0xe1d712d0
    dcd 0xe1a00007
    dcd 0xe3a02000
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd80f0
    dcd 0xe5951040
    dcd 0xe28d2000
    dcd 0xe2800074
    bl VEC_Subtract
    dcd 0xe28d0000
    dcd 0xe3a02000
    dcd 0xe1a01000
    dcd 0xe58d2004
    bl func_01ff8d18
    dcd 0xe8950006
    dcd 0xe5922080
    dcd 0xe5911080
    dcd 0xe0400002
    dcd 0xe0400001
    dcd 0xe3a01a0f
    bl FX_Inv
    dcd 0xe1a01080
    dcd 0xe3a00a01
    dcd 0xe2416a01
    dcd 0xe2600000
    dcd 0xe1560000
    dcd 0xb1a06000
    dcd 0xe3560a01
    dcd 0xc3a06a01
    dcd 0xe3560000
    dcd 0xb2660000
    dcd 0xa1a00006
    dcd 0xe2604a01
    dcd 0xe1b00084
    dcd 0x42600000
    dcd 0xe2800001
    bl func_02023eb4
    dcd 0xe2800000
    dcd 0xe0402004
    dcd 0xe59f00b4
    dcd 0xe1a01fc2
    dcd 0xe0834092
    dcd 0xe2942b02
    dcd 0xe0233091
    dcd 0xe2a30000
    dcd 0xe1a04622
    dcd 0xe3560000
    dcd 0xe1844a00
    dcd 0xda000008
    dcd 0xe59d0000
    dcd 0xe59d1008
    dcd 0xe2600000
    dcd 0xe2611000
    bl func_020050b4
    dcd 0xe2800f91
    dcd 0xe2800a03
    dcd 0xe0400004
    dcd 0xea000005
    dcd 0xe59d0000
    dcd 0xe59d1008
    bl func_020050b4
    dcd 0xe2800f91
    dcd 0xe2800a03
    dcd 0xe0840000
    dcd 0xe585000c
    dcd 0xe5970000
    dcd 0xe59f304c
    dcd 0xe590202c
    dcd 0xe3a0001e
    dcd 0xe0040092
    dcd 0xe1a00fa4
    dcd 0xe0c42493
    dcd 0xe08040c4
    dcd 0xe5854010
    dcd 0xe3a01001
    dcd 0xe5950000
    dcd 0xe1a02001
    bl func_ov107_020c9264
    mov r0, #0
    dcd 0xe5c50048
    dcd 0xe1d712d0
    dcd 0xe59f2014
    dcd 0xe1a00007
    bl func_0203c634
    dcd 0xe28dd00c
    dcd 0xe8bd80f0
    dcd 0x00003244
    dcd 0x66666667
    dcd func_ov150_020d0d04
}
