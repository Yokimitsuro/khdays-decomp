extern void GXS_LoadBGPltt(void);
extern void GX_LoadBGPltt(void);
extern void MI_CpuFill8(void);
extern void NNSi_FndGetCurrentRootHeap(void);
extern void data_ov012_0205c2d0(void);
extern void data_ov012_0205cac0(void);
extern void data_ov012_0205cadc(void);
extern void data_ov012_0205cae8(void);
extern void data_ov012_0205caf4(void);
extern void data_ov012_0205cb20(void);
extern void func_0201e470(void);
extern void func_0201ef9c(void);
extern void func_02020aa8(void);
extern void func_02020c7c(void);
extern void func_02024c94(void);
extern void func_02024e5c(void);
extern void func_02024ee8(void);
extern void func_02024fd4(void);
extern void func_0202f7fc(void);
extern void func_ov012_0205ad1c(void);
extern void func_ov012_0205b618(void);

asm void func_ov012_0205ade8(void)
{
    dcd     0xe92d4ff8
    dcd     0xe1a04000
    bl      NNSi_FndGetCurrentRootHeap
    dcd     0xe1a07000
    dcd     0xe59f1204
    dcd     0xe3a00000
    bl      func_0201e470
    bl      func_ov012_0205ad1c
    dcd     0xe59f01f8
    dcd     0xe3a01000
    dcd     0xe5807000
    dcd     0xe1c710b0
    dcd     0xe1c710b2
    dcd     0xe3540000
    dcd     0x01d700b2
    dcd     0xe2873902
    dcd     0xe3a01000
    dcd     0x03800010
    dcd     0x01c700b2
    dcd     0xe3e00000
    dcd     0xe5830be8
    dcd     0xe5831bdc
    dcd     0xe2870f66
    dcd     0xe5831bd8
    dcd     0xe5c31be0
    dcd     0xe59f21b8
    dcd     0xe2800b21
    dcd     0xe5c31bf0
    bl      MI_CpuFill8
    dcd     0xe2870d2d
    dcd     0xe59f11a8
    dcd     0xe2800902
    bl      func_0202f7fc
    dcd     0xe59f01a0
    dcd     0xe3a01e1a
    dcd     0xe3a02020
    bl      GX_LoadBGPltt
    dcd     0xe59f0190
    dcd     0xe3a01e1a
    dcd     0xe3a02020
    bl      GXS_LoadBGPltt
    dcd     0xe2871fd3
    dcd     0xe2812b22
    dcd     0xe2871902
    dcd     0xe58125a4
    dcd     0xe59f0174
    dcd     0xe3a0100e
    bl      func_02024ee8
    dcd     0xe1a04000
    dcd     0xe59f0168
    dcd     0xe2842902
    dcd     0xe0020000
    dcd     0xe1a00380
    dcd     0xe3805102
    dcd     0xe3a0100e
    dcd     0xe1a00005
    bl      func_0201ef9c
    dcd     0xe2871902
    dcd     0xe5810bf8
    bl      func_02024e5c
    dcd     0xe59f2140
    dcd     0xe3a0100e
    dcd     0xe0000002
    dcd     0xe1850000
    bl      func_0201ef9c
    dcd     0xe2871902
    dcd     0xe5810bfc
    dcd     0xe1a00004
    bl      func_02024fd4
    dcd     0xe3a09000
    dcd     0xe1a08009
    dcd     0xe1a0a009
    dcd     0xe2876b23
    dcd     0xe2874902
    dcd     0xe3e05000
    dcd     0xe3a0b00c
    dcd     0xe3a0000c
    dcd     0xe0206099
    dcd     0xe58d8000
    dcd     0xe5941bf8
    dcd     0xe1a0200a
    dcd     0xe1a0300a
    bl      func_02024c94
    dcd     0xe2891001
    dcd     0xe28a2001
    dcd     0xe0206b91
    dcd     0xe58d5000
    dcd     0xe5941bf8
    dcd     0xe1a03002
    dcd     0xe2899002
    bl      func_02024c94
    dcd     0xe358000d
    dcd     0xaa000008
    dcd     0xe3a0000c
    dcd     0xe0000099
    dcd     0xe58d5000
    dcd     0xe5941bfc
    dcd     0xe1a02008
    dcd     0xe1a03008
    dcd     0xe0860000
    dcd     0xe2899001
    bl      func_02024c94
    dcd     0xe2888001
    dcd     0xe358000e
    dcd     0xe28aa002
    dcd     0xbaffffe1
    dcd     0xe59f108c
    dcd     0xe3a00003
    bl      func_02020aa8
    dcd     0xe2872f66
    dcd     0xe59f1080
    dcd     0xe2870004
    dcd     0xe2823b21
    dcd     0xe3a02000
    bl      func_02020c7c
    dcd     0xe1d710b2
    dcd     0xe2872902
    dcd     0xe3a00000
    dcd     0xe3811001
    dcd     0xe1c710b2
    dcd     0xe59f105c
    dcd     0xe5c20be1
    dcd     0xe59f0058
    dcd     0xe1d140b0
    dcd     0xe1d030b0
    dcd     0xe59f1050
    dcd     0xe59f0050
    dcd     0xe1843003
    dcd     0xe0233001
    dcd     0xe0031001
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe2011008
    dcd     0xe5821bec
    dcd     0xe8bd8ff8
    dcd     0x00000018
    dcd     data_ov012_0205cb20
    dcd     0x000005a4
    dcd     data_ov012_0205cac0
    dcd     data_ov012_0205c2d0
    dcd     data_ov012_0205cadc
    dcd     0x00fffffc
    dcd     0x000001ff
    dcd     data_ov012_0205caf4
    dcd     data_ov012_0205cae8
    dcd     0x04000130
    dcd     0x027fffa8
    dcd     0x00002fff
    dcd     func_ov012_0205b618
}
