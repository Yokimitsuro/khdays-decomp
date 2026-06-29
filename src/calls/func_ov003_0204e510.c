extern char data_0203d210[];
extern char data_ov003_0204f9a0[];
extern void MTX_Concat33(void);
extern void MTX_RotY33_(void);

asm void func_ov003_0204e510(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd024
    dcd     0xe1a01241
    dcd     0xe1a02081
    dcd     0xe2821001
    dcd     0xe1a04082
    dcd     0xe59f3078
    dcd     0xe1a02081
    dcd     0xe1a05000
    dcd     0xe19310f4
    dcd     0xe19320f2
    dcd     0xe28d0000
    bl      MTX_RotY33_
    dcd     0xe3a00f42
    dcd     0xe0040095
    dcd     0xe59f1058
    dcd     0xe5910000
    dcd     0xe28d1000
    dcd     0xe2802e29
    dcd     0xe0820004
    dcd     0xe0822004
    bl      MTX_Concat33
    dcd     0xe59f003c
    dcd     0xe28d1000
    dcd     0xe5900000
    dcd     0xe2802ead
    dcd     0xe0820004
    dcd     0xe0822004
    bl      MTX_Concat33
    dcd     0xe59f0020
    dcd     0xe28d1000
    dcd     0xe5900000
    dcd     0xe2802eef
    dcd     0xe0820004
    dcd     0xe0822004
    bl      MTX_Concat33
    dcd     0xe28dd024
    dcd     0xe8bd8030
    dcd     data_0203d210
    dcd     data_ov003_0204f9a0
}
