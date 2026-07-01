extern void func_ov022_02083f90(void);
extern void func_ov022_020893f4(void);
extern void func_ov022_0208954c(void);
extern void func_ov022_0209fc48(void);
extern void func_ov022_0209fc78(void);
extern void func_ov030_020b564c(void);
extern int data_02041dc8;
extern int data_ov030_020b5a00;

asm void func_ov030_020b3d18(void)
{
    dcd     0xe92d4038
    dcd     0xe59f20f8
    dcd     0xe3a01001
    dcd     0xe1a05000
    dcd     0xe5924000
    bl      func_ov022_0209fc78
    dcd     0xe3500000
    dcd     0x0a000032
    dcd     0xe1a00005
    dcd     0xe3a01001
    bl      func_ov022_0209fc48
    dcd     0xe3500000
    dcd     0x1a00002d
    dcd     0xe2841a02
    dcd     0xe5910cac
    dcd     0xe3500000
    dcd     0x0a000029
    dcd     0xe5911ca8
    dcd     0xe3510102
    dcd     0x1a000012
    dcd     0xe5952464
    dcd     0xe5951468
    dcd     0xe2022501
    dcd     0xe2011000
    dcd     0xe3510000
    dcd     0x03520000
    dcd     0xe3a02000
    dcd     0x0a00000a
    dcd     0xe59f1090
    bl      func_ov022_020893f4
    dcd     0xe1b01000
    dcd     0x4a000006
    dcd     0xe2840a02
    dcd     0xe3a02a03
    dcd     0xe5802ca8
    dcd     0xe2852f56
    dcd     0xe5900cac
    dcd     0xe2822b01
    bl      func_ov022_0208954c
    dcd     0xe2840a02
    dcd     0xe5900ca8
    dcd     0xe3500102
    dcd     0x0a00000f
    bl      func_ov022_02083f90
    dcd     0xe2841a02
    dcd     0xe5912ca8
    dcd     0xe0420000
    dcd     0xe5810ca8
    dcd     0xe3500000
    dcd     0xca000008
    dcd     0xe2850c0f
    dcd     0xe1d000dd
    dcd     0xe3a01102
    dcd     0xe3500000
    dcd     0x15d50f0c
    dcd     0x13800001
    dcd     0x15c50f0c
    dcd     0xe2840a02
    dcd     0xe5801ca8
    dcd     0xe2850c2a
    dcd     0xe1d01bfa
    dcd     0xe2840ecb
    dcd     0xe2800a02
    bl      func_ov030_020b564c
    dcd     0xe8bd8038
    dcd     data_ov030_020b5a00
    dcd     data_02041dc8
}
