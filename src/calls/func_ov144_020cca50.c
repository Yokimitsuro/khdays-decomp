extern void VEC_Subtract(void);
extern void func_020050b4(void);

asm void func_ov144_020cca50(void)
{
    dcd     0xe92d4018
    dcd     0xe24dd00c
    dcd     0xe1a04000
    dcd     0xe594004c
    dcd     0xe3500000
    dcd     0x0a000005
    dcd     0xe5941000
    dcd     0xe28d2000
    dcd     0xe2840018
    dcd     0xe2811074
    bl      VEC_Subtract
    dcd     0xea000008
    dcd     0xe5940004
    dcd     0xe3500000
    dcd     0x028dd00c
    dcd     0x08bd8018
    dcd     0xe5941000
    dcd     0xe28d2000
    dcd     0xe2800074
    dcd     0xe2811074
    bl      VEC_Subtract
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      func_020050b4
    dcd     0xe5840034
    dcd     0xe28dd00c
    dcd     0xe8bd8018
}
