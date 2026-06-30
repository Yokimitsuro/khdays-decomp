extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void VEC_Add(void);
extern void data_ov039_020b5600(void);
extern void data_ov039_020b5390(void);
extern void data_ov039_020b53b0(void);
extern void data_0203d210(void);

asm void func_ov039_020b4050(void)
{
    dcd     0xe92d43f8
    dcd     0xe24dd048
    dcd     0xe59f30f8
    dcd     0xe59f90f8
    dcd     0xe59f80f8
    dcd     0xe28d7000
    dcd     0xe28d6018
    dcd     0xe593e000
    dcd     0xe1a05000
    dcd     0xe1a0c001
    dcd     0xe1a04002
    dcd     0xe8990007
    dcd     0xe8860007
    dcd     0xe1a06007
    dcd     0xe8b8000f
    dcd     0xe8a7000f
    dcd     0xe8980003
    dcd     0xe28e2a02
    dcd     0xe8870003
    dcd     0xe5920cd4
    dcd     0xe3500000
    dcd     0x1a000005
    dcd     0xe59d0018
    dcd     0xe5840000
    dcd     0xe59d001c
    dcd     0xe5840004
    dcd     0xe59d0020
    dcd     0xea000008
    dcd     0xe3a0000c
    dcd     0xe002009c
    dcd     0xe7961002
    dcd     0xe28d0004
    dcd     0xe5841000
    dcd     0xe7901002
    dcd     0xe28d0008
    dcd     0xe5841004
    dcd     0xe7900002
    dcd     0xe5840008
    dcd     0xe5950020
    dcd     0xe59f2070
    dcd     0xe1d018b0
    dcd     0xe28d0024
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
    dcd     0xe28d1024
    dcd     0xe1a00004
    dcd     0xe1a02004
    bl      MTX_MultVec33
    dcd     0xe285008c
    dcd     0xe1a01004
    dcd     0xe1a02004
    dcd     0xe2800b01
    bl      VEC_Add
    dcd     0xe28dd048
    dcd     0xe8bd83f8
    dcd     data_ov039_020b5600
    dcd     data_ov039_020b5390
    dcd     data_ov039_020b53b0
    dcd     data_0203d210
}
