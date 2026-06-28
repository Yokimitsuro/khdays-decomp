extern void func_ov022_020a4490(void);
extern void func_0202accc(void);
extern void func_01fff774(void);
extern void MTX_Identity33_(void);
extern void MTX_RotY33_(void);
extern void MTX_Concat33(void);
extern void func_020307f4(void);
extern void MTX_RotX33_(void);
extern void MTX_RotZ33_(void);
extern void MI_Copy36B(void);
extern char data_ov033_020b4b80[];
extern char data_0203d210[];

asm void func_ov033_020b4804(void)
{
    dcd     0xe92d41f0
    dcd     0xe24dd090
    dcd     0xe59f4210
    dcd     0xe1a08000
    dcd     0xe5940000
    dcd     0xe3a04000
    dcd     0xe280502c
    dcd     0xe285cb0b
    dcd     0xe1a06002
    dcd     0xe1a05003
    dcd     0xe1a07001
    dcd     0xe1a03004
    dcd     0xe1a0200c
    dcd     0xe5921118
    dcd     0xe3510000
    dcd     0x1a000003
    dcd     0xe28c2f46
    dcd     0xe0831203
    dcd     0xe0824201
    dcd     0xea000003
    dcd     0xe2833001
    dcd     0xe3530006
    dcd     0xe2822e11
    dcd     0xbafffff4
    dcd     0xe3540000
    dcd     0x028dd090
    dcd     0x08bd81f0
    dcd     0xe3560002
    dcd     0xe3a010ca
    dcd     0x1a000002
    dcd     0xe3a02001
    bl      func_ov022_020a4490
    dcd     0xea000001
    dcd     0xe3a02000
    bl      func_ov022_020a4490
    dcd     0xe1a01806
    dcd     0xe3a0c001
    dcd     0xe1a03841
    dcd     0xe2840008
    dcd     0xe28420e8
    dcd     0xe3a01000
    dcd     0xe584c000
    bl      func_0202accc
    dcd     0xe1a01806
    dcd     0xe1a03841
    dcd     0xe2840008
    dcd     0xe28420e8
    dcd     0xe3a01001
    bl      func_0202accc
    dcd     0xe1a01806
    dcd     0xe1a03841
    dcd     0xe2840008
    dcd     0xe3a01002
    dcd     0xe28420e8
    bl      func_0202accc
    dcd     0xe3a01000
    dcd     0xe2840008
    dcd     0xe1a02001
    bl      func_01fff774
    dcd     0xe2840008
    dcd     0xe3a01001
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe2840008
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe28430ac
    dcd     0xe8980007
    dcd     0xe8830007
    dcd     0xe28d006c
    bl      MTX_Identity33_
    dcd     0xe2870902
    dcd     0xe1a00800
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a01080
    dcd     0xe1a06081
    dcd     0xe2811001
    dcd     0xe59f30e0
    dcd     0xe1a02081
    dcd     0xe19310f6
    dcd     0xe19320f2
    dcd     0xe28d0000
    bl      MTX_RotY33_
    dcd     0xe28d106c
    dcd     0xe28d0000
    dcd     0xe1a02001
    bl      MTX_Concat33
    dcd     0xe3550000
    dcd     0x1a000027
    dcd     0xe59f00b4
    bl      func_020307f4
    dcd     0xe59f10b0
    dcd     0xe59f20a4
    dcd     0xe0800001
    dcd     0xe1a00800
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a01080
    dcd     0xe2810001
    dcd     0xe1a01081
    dcd     0xe1a00080
    dcd     0xe19210f1
    dcd     0xe19220f0
    dcd     0xe28d0048
    bl      MTX_RotX33_
    dcd     0xe28d106c
    dcd     0xe28d0048
    dcd     0xe1a02001
    bl      MTX_Concat33
    dcd     0xe59f0064
    bl      func_020307f4
    dcd     0xe59f1060
    dcd     0xe59f3054
    dcd     0xe0800001
    dcd     0xe1a00800
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a02080
    dcd     0xe1a01082
    dcd     0xe2822001
    dcd     0xe1a02082
    dcd     0xe19310f1
    dcd     0xe19320f2
    dcd     0xe28d0024
    bl      MTX_RotZ33_
    dcd     0xe28d106c
    dcd     0xe28d0024
    dcd     0xe1a02001
    bl      MTX_Concat33
    dcd     0xe28d006c
    dcd     0xe2841088
    bl      MI_Copy36B
    dcd     0xe28dd090
    dcd     0xe8bd81f0
    dcd     data_ov033_020b4b80
    dcd     data_0203d210
    dcd     0x00002aaa
    dcd     0xffffeaab
}
