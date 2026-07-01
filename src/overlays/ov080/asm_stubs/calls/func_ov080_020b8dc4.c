extern char data_0203d210[];
extern void MI_Copy36B(void);
extern void VEC_MultAdd(void);
extern void MTX_Identity33_(void);
extern void MTX_RotY33_(void);
extern void MTX_RotZ33_(void);
extern void MTX_Concat33(void);
extern void func_01fff774(void);
extern void func_0202accc(void);
extern void func_ov022_020ad44c(void);

asm void func_ov080_020b8dc4(void)
{
    dcd     0xe92d40f0
    dcd     0xe24dd084
    dcd     0xe3a04000
    dcd     0xe1a06002
    dcd     0xe1a05003
    dcd     0xe1a07000
    dcd     0xe1a02004
    dcd     0xe1a03001
    dcd     0xe5930330
    dcd     0xe3500000
    dcd     0x1a000003
    dcd     0xe2811e33
    dcd     0xe0820202
    dcd     0xe0814200
    dcd     0xea000003
    dcd     0xe2822001
    dcd     0xe3520003
    dcd     0xe2833e11
    dcd     0xbafffff4
    dcd     0xe3540000
    dcd     0x028dd084
    dcd     0x08bd80f0
    dcd     0xe1a01805
    dcd     0xe3a0c002
    dcd     0xe1a03841
    dcd     0xe2840004
    dcd     0xe28420e4
    dcd     0xe3a01000
    dcd     0xe584c000
    bl      func_0202accc
    dcd     0xe1a01805
    dcd     0xe1a03841
    dcd     0xe2840004
    dcd     0xe28420e4
    dcd     0xe3a01002
    bl      func_0202accc
    dcd     0xe3a01000
    dcd     0xe1a02001
    dcd     0xe2840004
    bl      func_01fff774
    dcd     0xe2840004
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe5970020
    dcd     0xe1a01007
    dcd     0xe1d028b0
    mov r0, #0
    dcd     0xe59f30fc
    dcd     0xe58d0070
    dcd     0xe2420902
    dcd     0xe1a00800
    dcd     0xe1a05820
    dcd     0xe1a00245
    dcd     0xe1a07080
    dcd     0xe1a00087
    dcd     0xe19320f0
    dcd     0xe2870001
    dcd     0xe1a00080
    dcd     0xe19300f0
    dcd     0xe2622000
    dcd     0xe58d206c
    dcd     0xe2600000
    dcd     0xe58d0074
    dcd     0xe28d0078
    bl      func_ov022_020ad44c
    dcd     0xe28d2078
    dcd     0xe3a00a01
    dcd     0xe28d106c
    dcd     0xe1a03002
    bl      VEC_MultAdd
    dcd     0xe28d0078
    dcd     0xe28430a8
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe28d0048
    bl      MTX_Identity33_
    dcd     0xe2850902
    dcd     0xe1a00800
    dcd     0xe1a00820
    dcd     0xe1a00240
    dcd     0xe1a01080
    dcd     0xe1a05081
    dcd     0xe2811001
    dcd     0xe59f306c
    dcd     0xe1a02081
    dcd     0xe19310f5
    dcd     0xe19320f2
    dcd     0xe28d0000
    bl      MTX_RotY33_
    dcd     0xe28d1048
    dcd     0xe28d0000
    dcd     0xe1a02001
    bl      MTX_Concat33
    dcd     0xe1a00246
    dcd     0xe1a01080
    dcd     0xe2810001
    dcd     0xe59f2038
    dcd     0xe1a01081
    dcd     0xe1a00080
    dcd     0xe19210f1
    dcd     0xe19220f0
    dcd     0xe28d0024
    bl      MTX_RotZ33_
    dcd     0xe28d1048
    dcd     0xe28d0024
    dcd     0xe1a02001
    bl      MTX_Concat33
    dcd     0xe28d0048
    dcd     0xe2841084
    bl      MI_Copy36B
    dcd     0xe28dd084
    dcd     0xe8bd80f0
    dcd     data_0203d210
}
