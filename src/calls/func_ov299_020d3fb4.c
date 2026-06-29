extern void OS_IsThreadAvailable_0x020c9848(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_0203c960(void);
extern void func_0203ca30(void);
extern void func_ov107_020c0794(void);
extern void func_ov107_020c0b14(void);
extern void func_ov107_020c7500(void);

asm void func_ov299_020d3fb4(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd054
    dcd     0xe1a05001
    dcd     0xe5d51002
    dcd     0xe1a06000
    dcd     0xe1a04002
    dcd     0xe3510005
    dcd     0x1a000047
    dcd     0xe5d52005
    dcd     0xe5d50007
    dcd     0xe5d51006
    dcd     0xe5cd2007
    dcd     0xe5cd0005
    dcd     0xe5cd1006
    dcd     0xe59d1004
    dcd     0xe28d0028
    dcd     0xe1a01441
    dcd     0xe58d101c
    dcd     0xe5d53008
    dcd     0xe5d52009
    dcd     0xe5d5100a
    dcd     0xe5cd300b
    dcd     0xe5cd200a
    dcd     0xe5cd1009
    dcd     0xe59d1008
    dcd     0xe1a01441
    dcd     0xe58d1020
    dcd     0xe5d5300b
    dcd     0xe5d5200c
    dcd     0xe5d5100d
    dcd     0xe5cd300f
    dcd     0xe5cd200e
    dcd     0xe5cd100d
    dcd     0xe59d100c
    dcd     0xe1a01441
    dcd     0xe58d1024
    bl      func_0203c960
    dcd     0xe28d0028
    dcd     0xe28d101c
    bl      func_0203ca30
    dcd     0xe5d51003
    dcd     0xe3510000
    dcd     0x13510001
    dcd     0x13510002
    dcd     0x1a000022
    dcd     0xe3510000
    dcd     0x13a02002
    dcd     0xe28d0028
    dcd     0x03a02000
    dcd     0xe58d0000
    dcd     0xe0861181
    dcd     0xe3822015
    dcd     0xe596003c
    dcd     0xe5911394
    dcd     0xe20220ff
    dcd     0xe3a03000
    bl      func_ov107_020c0794
    dcd     0xe5d51003
    dcd     0xe0861181
    dcd     0xe5810398
    dcd     0xe5d50003
    dcd     0xe3500001
    dcd     0x1a000010
    bl      OS_IsThreadAvailable_0x020c9848
    dcd     0xe3500000
    dcd     0x15900000
    dcd     0x13500000
    dcd     0x0a00000b
    dcd     0xe28d101c
    dcd     0xe28d2010
    dcd     0xe2800088
    bl      VEC_Subtract
    dcd     0xe28d0010
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe3500a0a
    dcd     0xca000002
    dcd     0xe1a00006
    dcd     0xe3a01001
    bl      func_ov107_020c0b14
    dcd     0xe1a00006
    dcd     0xe1a01005
    dcd     0xe1a02004
    bl      func_ov107_020c7500
    dcd     0xe28dd054
    dcd     0xe8bd8078
}
