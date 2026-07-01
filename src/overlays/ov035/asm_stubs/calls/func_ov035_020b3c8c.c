extern void MTX_MultVec33(void);
extern void MTX_RotY33_(void);
extern void VEC_Add(void);
extern char data_0203d210[];
extern char data_ov035_020b4ca0[];

asm void func_ov035_020b3c8c(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd03c
    dcd     0xe1a05001
    dcd     0xe285108c
    dcd     0xe28d3030
    dcd     0xe2811b01
    dcd     0xe1a04000
    dcd     0xe8910007
    dcd     0xe8830007
    dcd     0xe5951020
    dcd     0xe59f0080
    dcd     0xe1d118b0
    dcd     0xe5900000
    dcd     0xe59fc078
    dcd     0xe2411902
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe2811902
    dcd     0xe28030a4
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe1a01241
    dcd     0xe1a02081
    dcd     0xe2821001
    dcd     0xe1a0e082
    dcd     0xe1a02081
    dcd     0xe19c10fe
    dcd     0xe19c20f2
    dcd     0xe28d0000
    dcd     0xe2835b0b
    bl      MTX_RotY33_
    dcd     0xe28d1000
    dcd     0xe28d2024
    dcd     0xe2850f49
    bl      MTX_MultVec33
    dcd     0xe28d1030
    dcd     0xe28d0024
    dcd     0xe1a02001
    bl      VEC_Add
    dcd     0xe28d0030
    dcd     0xe8900007
    dcd     0xe8840007
    dcd     0xe28dd03c
    dcd     0xe8bd8030
    dcd     data_ov035_020b4ca0
    dcd     data_0203d210
}
