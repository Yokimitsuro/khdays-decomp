extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_01fff948(void);

asm void func_ov144_020cc8e4(void)
{
    dcd     0xe92d000f
    dcd     0xe92d4010
    dcd     0xe24dd018
    dcd     0xe5900000
    dcd     0xe28d3000
    dcd     0xe5904004
    dcd     0xe2800074
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe28d0024
    dcd     0xe28d200c
    dcd     0xe1a01003
    bl      VEC_Subtract
    dcd     0xe28d000c
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59d1030
    dcd     0xe0400001
    dcd     0xe28d100c
    dcd     0xe3500000
    dcd     0xd3a00001
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe594007c
    dcd     0xe28d1000
    dcd     0xe28d200c
    dcd     0xe3a03040
    bl      func_01fff948
    dcd     0xe3500000
    dcd     0x13a00000
    dcd     0x03a00001
    dcd     0xe28dd018
    dcd     0xe8bd4010
    dcd     0xe28dd010
    dcd     0xe12fff1e
}
