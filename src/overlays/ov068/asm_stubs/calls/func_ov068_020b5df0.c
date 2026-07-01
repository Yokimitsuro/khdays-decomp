extern char data_0204c240[];
extern void FX_Atan2(void);
extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void func_ov068_020b61a8(void);
extern void func_ov068_020b6e00(void);
extern void func_ov068_020b6fe0(void);

asm void func_ov068_020b5df0(void)
{
    dcd     0xe92d4018
    dcd     0xe24dd00c
    dcd     0xe59f2118
    dcd     0xe1a04000
    dcd     0xe5d22000
    dcd     0xe28400fc
    dcd     0xe280cb0b
    dcd     0xe3120004
    mov r0, #0
    dcd     0x1a000006
    dcd     0xe5943000
    dcd     0xe5942004
    dcd     0xe2033c01
    dcd     0xe0022000
    dcd     0xe1520000
    dcd     0x01530000
    dcd     0x13a01021
    dcd     0xe3510021
    dcd     0x0a000005
    dcd     0xe3510022
    dcd     0x0a000027
    dcd     0xe28dd00c
    dcd     0xe3510023
    dcd     0x059f00c8
    dcd     0xe8bd8018
    dcd     0xe5942664
    dcd     0xe1a00004
    dcd     0xe3a0101b
    dcd     0xe12fff32
    dcd     0xe284007c
    dcd     0xe3a0c000
    dcd     0xe28d3000
    dcd     0xe584c058
    dcd     0xe2800b01
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe1a00003
    dcd     0xe58dc004
    bl      VEC_Mag
    dcd     0xe3500000
    dcd     0x0a000002
    dcd     0xe28d0000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59d0000
    dcd     0xe59d1008
    bl      FX_Atan2
    dcd     0xe5942020
    dcd     0xe1a00800
    dcd     0xe5921000
    dcd     0xe1a00820
    dcd     0xe3110020
    dcd     0x1a000004
    dcd     0xe2800902
    dcd     0xe1c208b0
    dcd     0xe1d200b4
    dcd     0xe3800020
    dcd     0xe1c200b4
    dcd     0xe28dd00c
    dcd     0xe59f003c
    dcd     0xe8bd8018
    dcd     0xe59c0118
    dcd     0xe5942664
    dcd     0xe3500000
    dcd     0xe1a00004
    dcd     0x0a000002
    dcd     0xe3a01030
    dcd     0xe12fff32
    dcd     0xea000001
    dcd     0xe3a0102f
    dcd     0xe12fff32
    dcd     0xe59f0010
    dcd     0xe28dd00c
    dcd     0xe8bd8018
    dcd     data_0204c240
    dcd     func_ov068_020b6fe0
    dcd     func_ov068_020b61a8
    dcd     func_ov068_020b6e00
}
