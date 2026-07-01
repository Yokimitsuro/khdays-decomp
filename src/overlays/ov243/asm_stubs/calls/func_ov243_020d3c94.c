extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_01fff8e8(void);
extern void func_01fff920(void);

asm void func_ov243_020d3c94(void)
{
    dcd     0xe92d000f
    dcd     0xe92d4018
    dcd     0xe24dd01c
    dcd     0xe5900000
    dcd     0xe28d3004
    dcd     0xe5904004
    dcd     0xe2800074
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe28d002c
    dcd     0xe28d2010
    dcd     0xe1a01003
    bl      VEC_Subtract
    dcd     0xe28d0010
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59d1038
    dcd     0xe0400001
    dcd     0xe28d1010
    dcd     0xe3500000
    dcd     0xd3a00001
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe3a00000
    dcd     0xe58d0000
    dcd     0xe594007c
    dcd     0xe28d1004
    dcd     0xe28d2010
    dcd     0xe3a03c03
    bl      func_01fff8e8
    dcd     0xe3500000
    dcd     0x0a000006
    dcd     0xe5900008
    dcd     0xe3500000
    dcd     0x028dd01c
    dcd     0x03a00000
    dcd     0x08bd4018
    dcd     0x028dd010
    dcd     0x012fff1e
    dcd     0xe594007c
    dcd     0xe28d1004
    dcd     0xe28d2010
    bl      func_01fff920
    dcd     0xe3500000
    dcd     0x0a000006
    dcd     0xe5900008
    dcd     0xe3500000
    dcd     0x028dd01c
    dcd     0x03a00000
    dcd     0x08bd4018
    dcd     0x028dd010
    dcd     0x012fff1e
    dcd     0xe3a00001
    dcd     0xe28dd01c
    dcd     0xe8bd4018
    dcd     0xe28dd010
    dcd     0xe12fff1e
}
