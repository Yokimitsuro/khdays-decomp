extern void data_ov132_020d0d8c(void);
extern void func_01ffa724(void);
extern void func_0202f384(void);
extern void func_0203c634(void);
extern void func_ov107_020c9264(void);
extern void func_ov107_020c9f48(void);
extern void func_ov132_020cf7c4(void);

asm void func_ov132_020cf6f8(void)
{
    dcd     0xe92d4070
    dcd     0xe24dd010
    dcd     0xe1a05000
    dcd     0xe5954004
    dcd     0xe28d1004
    dcd     0xe5940000
    dcd     0xe59003c8
    bl      func_ov107_020c9f48
    dcd     0xe5941000
    dcd     0xe1a06000
    dcd     0xe28d2004
    dcd     0xe2840018
    dcd     0xe28110a0
    bl      func_0202f384
    dcd     0xe2841018
    dcd     0xe1a00006
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe5940048
    dcd     0xe5d00000
    dcd     0xe3500000
    dcd     0x128dd010
    dcd     0x18bd8070
    dcd     0xe59f0060
    dcd     0xe28d1000
    dcd     0xe1d020b2
    dcd     0xe1d000b0
    dcd     0xe1cd20b2
    dcd     0xe1cd00b0
    dcd     0xe5940000
    dcd     0xe5903024
    dcd     0xe3530000
    dcd     0x0a000001
    dcd     0xe3a02004
    dcd     0xe12fff33
    dcd     0xe5940000
    dcd     0xe3a0100a
    dcd     0xe3a02001
    bl      func_ov107_020c9264
    mov r0, #0
    dcd     0xe5840054
    dcd     0xe3a00c03
    dcd     0xe584003c
    dcd     0xe1d512d0
    dcd     0xe59f2010
    dcd     0xe1a00005
    bl      func_0203c634
    dcd     0xe28dd010
    dcd     0xe8bd8070
    dcd     data_ov132_020d0d8c
    dcd     func_ov132_020cf7c4
}
