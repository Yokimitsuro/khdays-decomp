extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void VEC_Add(void);
extern void func_ov022_02091324(void);
extern void data_0203d210(void);

asm void func_ov055_020b74c4(void)
{
    dcd     0xe92d41f8
    dcd     0xe24dd05c
    dcd     0xe1a08000
    dcd     0xe5981000
    dcd     0xe5980004
    dcd     0xe2011302
    dcd     0xe2000000
    dcd     0xe3500000
    dcd     0xe1a07002
    dcd     0xe1a06003
    dcd     0x03510000
    dcd     0x1a00003a
    dcd     0xe5980020
    dcd     0xe59f30ec
    dcd     0xe1d018b0
    dcd     0xe28d0000
    dcd     0xe2411902
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe1a01241
    dcd     0xe1a04081
    dcd     0xe2841001
    dcd     0xe1a02081
    dcd     0xe1a01084
    dcd     0xe19320f2
    dcd     0xe19310f1
    dcd     0xe2625000
    dcd     0xe2614000
    dcd     0xe1a01004
    dcd     0xe1a02005
    bl      MTX_RotY33_
    dcd     0xe28d1000
    dcd     0xe28d2024
    dcd     0xe287001c
    bl      MTX_MultVec33
    dcd     0xe5972000
    dcd     0xe288008c
    dcd     0xe1cd24b2
    dcd     0xe28d1024
    dcd     0xe28d2030
    dcd     0xe2800b01
    bl      VEC_Add
    dcd     0xe3a01000
    dcd     0xe58d4024
    dcd     0xe58d502c
    dcd     0xe58d1028
    dcd     0xe1cd43bc
    dcd     0xe1cd13be
    dcd     0xe1cd54b0
    dcd     0xe1d701d9
    dcd     0xe3560000
    dcd     0xe58d0044
    dcd     0xe58d1048
    dcd     0xe58d104c
    dcd     0xe58d1050
    dcd     0xe58d1058
    dcd     0xe58d1054
    dcd     0x0a000003
    dcd     0xe3810002
    dcd     0xe3a01001
    dcd     0xe58d1048
    dcd     0xe58d0050
    dcd     0xe5d70014
    dcd     0xe28d1030
    dcd     0xe1a00f00
    dcd     0xe1b00fa0
    dcd     0x159d0050
    dcd     0x13800001
    dcd     0x158d0050
    dcd     0xe1a00008
    bl      func_ov022_02091324
    dcd     0xe3a00000
    dcd     0xe28dd05c
    dcd     0xe8bd81f8
    dcd     data_0203d210
}
