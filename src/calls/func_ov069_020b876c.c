extern void MI_CpuFill8(void);
extern void func_ov069_020b8704(void);
extern void func_020235d0(void);
extern void func_0201e470(void);
extern void func_ov214_020cc64c(void);
extern void func_ov123_020cc718(void);
extern void func_ov256_020cc6dc(void);
extern void func_ov302_020cc6ac(void);
extern void func_0201e4a8(void);
extern void data_ov069_020ba7ec(void);

asm void func_ov069_020b876c(void)
{
    dcd     0xe92d4ff8
    dcd     0xe24dd030
    dcd     0xe59f113c
    dcd     0xe28d3000
    dcd     0xe1a0a000
    dcd     0xe8910007
    dcd     0xe8830007
    dcd     0xe1a0000a
    dcd     0xe3a01000
    dcd     0xe3a02014
    bl      MI_CpuFill8
    bl      func_ov069_020b8704
    dcd     0xe3500000
    dcd     0xe3a00000
    dcd     0x028dd030
    dcd     0x058a0010
    dcd     0x08bd8ff8
    dcd     0xe3a02001
    dcd     0xe3a01009
    dcd     0xe58a2010
    bl      func_020235d0
    dcd     0xe1a04000
    dcd     0xe59f10f0
    dcd     0xe3a00000
    bl      func_0201e470
    dcd     0xe28d000c
    dcd     0xe28d1000
    dcd     0xe58d4004
    bl      func_ov214_020cc64c
    dcd     0xe28d000c
    bl      func_ov123_020cc718
    dcd     0xe58a000c
    dcd     0xe28d000c
    dcd     0xe3a01000
    bl      func_ov256_020cc6dc
    dcd     0xe1b09000
    dcd     0x0a000026
    dcd     0xe3a06000
    dcd     0xe3a07001
    dcd     0xe3a05003
    dcd     0xe1a0b006
    dcd     0xe1a04007
    dcd     0xe5d9000c
    dcd     0xe3500000
    dcd     0x1a000002
    dcd     0xe5d90014
    dcd     0xe3100002
    dcd     0x0a000001
    dcd     0xe1a08007
    dcd     0xea000000
    dcd     0xe1a08006
    dcd     0xe59a0004
    dcd     0xe1a01005
    dcd     0xe0800008
    dcd     0xe58a0004
    dcd     0xe1d900b2
    dcd     0xe0800080
    dcd     0xe28000e4
    dcd     0xe2800b0a
    bl      func_020235d0
    dcd     0xe3500002
    dcd     0x21a00004
    dcd     0x31a0000b
    dcd     0xe3500000
    dcd     0x0a000005
    dcd     0xe59a0008
    dcd     0xe2800001
    dcd     0xe58a0008
    dcd     0xe59a0000
    dcd     0xe0800008
    dcd     0xe58a0000
    dcd     0xe28d000c
    dcd     0xe1a01009
    bl      func_ov256_020cc6dc
    dcd     0xe1b09000
    dcd     0x1affffdd
    dcd     0xe28d000c
    bl      func_ov302_020cc6ac
    dcd     0xe59f1010
    dcd     0xe3a00000
    bl      func_0201e4a8
    dcd     0xe28dd030
    dcd     0xe8bd8ff8
    dcd     data_ov069_020ba7ec
    dcd     0x0000012e
}
