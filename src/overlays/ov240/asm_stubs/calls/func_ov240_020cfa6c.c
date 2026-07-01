extern void VEC_Subtract(void);
extern void func_020050b4(void);
extern void func_01ff8d18(void);
extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void func_0203c634(void);
extern void data_0203d210(void);

asm void func_ov240_020cfa6c(void)
{
    dcd     0xe92d41f0
    dcd     0xe24dd030
    dcd     0xe1a06000
    dcd     0xe5964004
    dcd     0xe28d2024
    dcd     0xe5940000
    dcd     0xe5941008
    dcd     0xe2800e19
    bl      VEC_Subtract
    dcd     0xe59d0024
    dcd     0xe59d102c
    bl      func_020050b4
    dcd     0xe5840010
    dcd     0xe28d0024
    dcd     0xe5945000
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe5951080
    dcd     0xe594e010
    dcd     0xe0405001
    dcd     0xe59f1090
    dcd     0xe59f2090
    dcd     0xe087819e
    dcd     0xe027729e
    dcd     0xe1a0cfce
    dcd     0xe027719c
    dcd     0xe2981000
    dcd     0xe2a71b02
    dcd     0xe1a01201
    dcd     0xe1a01821
    dcd     0xe1a01241
    dcd     0xe1a02081
    dcd     0xe1a01082
    dcd     0xe59f3064
    dcd     0xe2822001
    dcd     0xe1a02082
    dcd     0xe19310f1
    dcd     0xe19320f2
    dcd     0xe28d0000
    bl      MTX_RotY33_
    dcd     0xe5940000
    dcd     0xe28d1000
    dcd     0xe5900398
    dcd     0xe2842014
    dcd     0xe280002c
    bl      MTX_MultVec33
    dcd     0xe3550a02
    dcd     0xa28dd030
    dcd     0xa8bd81f0
    dcd     0xe5940000
    dcd     0xe3a01002
    dcd     0xe5c011c7
    dcd     0xe1d612d0
    dcd     0xe1a00006
    dcd     0xe3a02000
    bl      func_0203c634
    dcd     0xe28dd030
    dcd     0xe8bd81f0
    dcd     0x60db9391
    dcd     0x000028be
    dcd     data_0203d210
}
