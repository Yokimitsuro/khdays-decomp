extern void MTX_RotY33_(void);
extern void func_02020400(void);
extern void MTX_MultVec33(void);
extern void VEC_Add(void);
extern void func_020307f4(void);
extern void func_ov022_02091324(void);
extern char data_ov085_020b912c[];
extern char data_ov085_020b9260[];
extern char data_ov085_020b915c[];
extern char data_0203d210[];

asm void func_ov085_020b8b34(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd0f8
    dcd     0xe59f61c0
    dcd     0xe28d5000
    dcd     0xe1a0a000
    dcd     0xe8b6000f
    dcd     0xe8a5000f
    dcd     0xe8b6000f
    dcd     0xe8a5000f
    dcd     0xe896000f
    dcd     0xe59f41a4
    dcd     0xe885000f
    dcd     0xe5940000
    dcd     0xe59f719c
    dcd     0xe2800ec5
    dcd     0xe28d6098
    dcd     0xe2805a02
    dcd     0xe3a04006
    dcd     0xe8b7000f
    dcd     0xe8a6000f
    dcd     0xe2544001
    dcd     0x1afffffb
    dcd     0xe59a0020
    dcd     0xe59f2178
    dcd     0xe1d018b0
    dcd     0xe28d0030
    dcd     0xe2411902
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe1a01241
    dcd     0xe1a03081
    dcd     0xe2831001
    dcd     0xe1a03083
    dcd     0xe1a01081
    dcd     0xe19230f3
    dcd     0xe19220f1
    dcd     0xe2631000
    dcd     0xe2622000
    bl      MTX_RotY33_
    dcd     0xe28a008c
    dcd     0xe2800b01
    dcd     0xe28d3054
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5950000
    dcd     0xe3500000
    dcd     0x128d9098
    dcd     0x13a08008
    dcd     0x13a07002
    dcd     0x1a000002
    dcd     0xe3a08004
    dcd     0xe28d9000
    dcd     0xe3a07001
    dcd     0xe3570000
    dcd     0xe3a06000
    dcd     0xd28dd0f8
    dcd     0xd8bd8ff8
    dcd     0xe28db06c
    dcd     0xe28d4060
    mov r0, #0
    dcd     0xe1cd07bc
    dcd     0xe1a00000
    dcd     0xe1cd07ba
    dcd     0xe1cd07b8
    dcd     0xe5950124
    dcd     0xe1a01008
    bl      func_02020400
    dcd     0xe3a0000c
    dcd     0xe0209091
    dcd     0xe28d1030
    dcd     0xe1a02004
    bl      MTX_MultVec33
    dcd     0xe28d0054
    dcd     0xe1a01004
    dcd     0xe1a0200b
    bl      VEC_Add
    mov r0, #0
    dcd     0xe58d0080
    mov r0, #1
    dcd     0xe58d0088
    mov r0, #0
    dcd     0xe58d008c
    dcd     0xe3a00007
    dcd     0xe58d0084
    dcd     0xe3a00003
    bl      func_020307f4
    dcd     0xe58d0090
    mov r0, #0
    dcd     0xe58d0094
    dcd     0xe3a00b05
    dcd     0xe1cd07be
    dcd     0xe5950000
    dcd     0xe3500000
    dcd     0x0a000003
    mov r0, #1
    dcd     0xe58d0094
    dcd     0xe3a00c0d
    dcd     0xe1cd07be
    dcd     0xe1a0000a
    dcd     0xe1a0100b
    bl      func_ov022_02091324
    dcd     0xe59a1000
    dcd     0xe3110801
    dcd     0x1a000003
    dcd     0xe3a00003
    dcd     0xe5ca047a
    mov r0, #0
    dcd     0xe5ca047b
    dcd     0xe5950124
    dcd     0xe2866001
    dcd     0xe2800001
    dcd     0xe5850124
    dcd     0xe1560007
    dcd     0xbaffffc8
    dcd     0xe28dd0f8
    dcd     0xe8bd8ff8
    dcd     data_ov085_020b912c
    dcd     data_ov085_020b9260
    dcd     data_ov085_020b915c
    dcd     data_0203d210
}
