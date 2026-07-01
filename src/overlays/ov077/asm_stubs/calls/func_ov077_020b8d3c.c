extern void func_ov022_020a4490(void);
extern void func_ov077_020b91d4(void);
extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void VEC_Add(void);
extern void func_0202a818(void);
extern void data_ov077_020b9b80(void);
extern void data_0203d210(void);

asm void func_ov077_020b8d3c(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd03c
    dcd     0xe59f3158
    dcd     0xe1a05001
    dcd     0xe5931000
    dcd     0xe5953000
    dcd     0xe281102c
    dcd     0xe1a04000
    dcd     0xe3530001
    dcd     0xe2816b0b
    dcd     0x1a000003
    dcd     0xe59406bc
    dcd     0xe3500030
    dcd     0x13a00000
    dcd     0x15850000
    dcd     0xe5950000
    dcd     0xe3500001
    dcd     0x0a000003
    dcd     0xe3500002
    dcd     0x0a00003d
    dcd     0xe28dd03c
    dcd     0xe8bd8078
    dcd     0xe59407b0
    dcd     0xe3500a1b
    dcd     0xb28dd03c
    dcd     0xb8bd8078
    dcd     0xe1a00004
    dcd     0xe3a010c8
    dcd     0xe3a02001
    bl      func_ov022_020a4490
    dcd     0xe1a00004
    dcd     0xe2861f46
    bl      func_ov077_020b91d4
    dcd     0xe284008c
    dcd     0xe3a0cf52
    dcd     0xe3a02000
    dcd     0xe3a01b06
    dcd     0xe28d3030
    dcd     0xe58dc024
    dcd     0xe58d2028
    dcd     0xe58d102c
    dcd     0xe2800b01
    dcd     0xe8900007
    dcd     0xe8830007
    dcd     0xe5940020
    dcd     0xe59f30b0
    dcd     0xe1d018b0
    dcd     0xe28d0000
    dcd     0xe2411902
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe2811902
    dcd     0xe1a01801
    dcd     0xe1a04821
    dcd     0xe1a01244
    dcd     0xe1a02081
    dcd     0xe1a01082
    dcd     0xe2822001
    dcd     0xe1a02082
    dcd     0xe19310f1
    dcd     0xe19320f2
    bl      MTX_RotY33_
    dcd     0xe28d0024
    dcd     0xe28d1000
    dcd     0xe1a02000
    bl      MTX_MultVec33
    dcd     0xe28d0030
    dcd     0xe28d1024
    dcd     0xe1a02000
    bl      VEC_Add
    dcd     0xe1c548b0
    dcd     0xe1d510b4
    dcd     0xe28d0030
    dcd     0xe28540a8
    dcd     0xe3811020
    dcd     0xe1c510b4
    dcd     0xe8900007
    dcd     0xe8840007
    dcd     0xe3a03002
    dcd     0xe28dd03c
    dcd     0xe5853000
    dcd     0xe8bd8078
    dcd     0xe1a01002
    dcd     0xe2850004
    bl      func_0202a818
    dcd     0xe3500000
    dcd     0x13a00000
    dcd     0x15850000
    dcd     0xe28dd03c
    dcd     0xe8bd8078
    dcd     data_ov077_020b9b80
    dcd     data_0203d210
}
