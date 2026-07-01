extern void FX_Atan2(void);
extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void func_ov030_020b38a4(void);
extern void func_ov030_020b3e44(void);
extern void func_ov030_020b3e64(void);
extern void func_ov030_020b54dc(void);
extern int data_0204c240;

asm void func_ov030_020b375c(void)
{
    dcd     0xe92d4018
    dcd     0xe24dd00c
    dcd     0xe59f2128
    dcd     0xe1a04000
    dcd     0xe5d23000
    dcd     0xe2842ecb
    mov r0, #0
    dcd     0xe3130004
    dcd     0x1a000006
    dcd     0xe594c000
    dcd     0xe5943004
    dcd     0xe20ccc01
    dcd     0xe0033000
    dcd     0xe1530000
    dcd     0x015c0000
    dcd     0x13a01021
    dcd     0xe3510021
    dcd     0x0a000005
    dcd     0xe3510022
    dcd     0x0a00002d
    dcd     0xe3510023
    dcd     0x0a000031
    dcd     0xe28dd00c
    dcd     0xe8bd8018
    dcd     0xe5942664
    dcd     0xe1a00004
    dcd     0xe3a0101b
    dcd     0xe12fff32
    mov r0, #0
    dcd     0xe5840058
    dcd     0xe594047c
    dcd     0xe3500000
    dcd     0x05940484
    dcd     0x03500000
    dcd     0x0a00001b
    dcd     0xe284007c
    dcd     0xe2800b01
    dcd     0xe28d3000
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe3a01000
    dcd     0xe1a00003
    dcd     0xe58d1004
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
    dcd     0xe59f0034
    dcd     0xe8bd8018
    dcd     0xe2820a02
    dcd     0xe3a01022
    bl      func_ov030_020b54dc
    dcd     0xe28dd00c
    dcd     0xe59f0020
    dcd     0xe8bd8018
    dcd     0xe2820a02
    dcd     0xe3a01023
    bl      func_ov030_020b54dc
    dcd     0xe59f0010
    dcd     0xe28dd00c
    dcd     0xe8bd8018
    dcd     data_0204c240
    dcd     func_ov030_020b38a4
    dcd     func_ov030_020b3e64
    dcd     func_ov030_020b3e44
}
