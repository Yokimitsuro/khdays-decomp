extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Add(void);
extern void VEC_Mag(void);
extern char data_0203d210[];
extern char data_ov076_020b9be4[];
extern void func_01ff8d18(void);
extern void func_ov022_02091324(void);

asm void func_ov076_020b891c(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd05c
    dcd     0xe1a06000
    dcd     0xe5961000
    dcd     0xe5960004
    dcd     0xe2011302
    dcd     0xe2000000
    dcd     0xe3500000
    dcd     0xe1a05002
    dcd     0xe1a04003
    dcd     0x03510000
    dcd     0x1a000045
    dcd     0xe59f011c
    dcd     0xe28d3024
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5960020
    dcd     0xe59f210c
    dcd     0xe1d018b0
    dcd     0xe28d0000
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
    dcd     0xe28d1000
    dcd     0xe28d2024
    dcd     0xe285001c
    bl      MTX_MultVec33
    dcd     0xe5951000
    dcd     0xe286008c
    dcd     0xe1cd14b2
    dcd     0xe2800b01
    dcd     0xe28d1024
    dcd     0xe28d2030
    bl      VEC_Add
    dcd     0xe2850028
    dcd     0xe28d1000
    dcd     0xe28d2024
    bl      MTX_MultVec33
    dcd     0xe28d0024
    bl      VEC_Mag
    dcd     0xe3500000
    dcd     0x0a000002
    dcd     0xe28d0024
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59d1028
    dcd     0xe59d002c
    dcd     0xe59d2024
    dcd     0xe1cd13be
    dcd     0xe1cd04b0
    dcd     0xe1cd23bc
    dcd     0xe1d521d9
    mov r0, #0
    dcd     0xe3a01002
    dcd     0xe58d1048
    dcd     0xe58d2044
    dcd     0xe58d004c
    dcd     0xe58d0050
    dcd     0xe58d0058
    dcd     0xe58d0054
    dcd     0xe3540000
    dcd     0x13800002
    dcd     0x158d0050
    dcd     0xe5d50014
    dcd     0xe28d1030
    dcd     0xe1a00f00
    dcd     0xe1b00fa0
    dcd     0x159d0050
    dcd     0x13800001
    dcd     0x158d0050
    dcd     0xe1a00006
    bl      func_ov022_02091324
    mov r0, #0
    dcd     0xe28dd05c
    dcd     0xe8bd8078
    dcd     data_ov076_020b9be4
    dcd     data_0203d210
}
