extern void func_01fff774(void);
extern void func_0202accc(void);
extern void func_02030788(void);
extern void func_ov022_020ad44c(void);

asm void func_ov103_020bb070(void)
{
    dcd     0xe92d4030
    dcd     0xe24dd00c
    dcd     0xe1a04001
    dcd     0xe3a01000
    dcd     0xe1a05000
    dcd     0xe1a03001
    dcd     0xe2840e12
    dcd     0xe2842c02
    bl      func_0202accc
    dcd     0xe2840e12
    dcd     0xe2842c02
    dcd     0xe3a01002
    dcd     0xe3a03000
    bl      func_0202accc
    dcd     0xe3a01000
    dcd     0xe1a02001
    dcd     0xe2840e12
    bl      func_01fff774
    dcd     0xe2840e12
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe28d0000
    dcd     0xe1a01005
    bl      func_ov022_020ad44c
    dcd     0xe5950020
    dcd     0xe2841c01
    dcd     0xe1d008b0
    dcd     0xe28d2000
    dcd     0xe284cf71
    dcd     0xe2400902
    dcd     0xe1a00800
    dcd     0xe1a00820
    dcd     0xe2800902
    dcd     0xe1c109bc
    dcd     0xe1d102b0
    dcd     0xe3a03001
    dcd     0xe3800020
    dcd     0xe1c102b0
    dcd     0xe8920007
    dcd     0xe88c0007
    dcd     0xe584311c
    bl      func_02030788
    dcd     0xe3500000
    dcd     0x128dd00c
    dcd     0x18bd8030
    dcd     0xe5950000
    dcd     0xe3100801
    dcd     0x128dd00c
    dcd     0x18bd8030
    dcd     0xe3a00003
    dcd     0xe5c5047a
    dcd     0xe3a00001
    dcd     0xe5c5047b
    dcd     0xe28dd00c
    dcd     0xe8bd8030
}
