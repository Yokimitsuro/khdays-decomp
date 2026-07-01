extern void func_ov107_020c9264(void);
extern void func_02023eb4(void);
extern void func_0203c634(void);
extern void func_ov195_020d1994(void);

asm void func_ov195_020d191c(void)
{
    dcd     0xe92d4038
    dcd     0xe1a04000
    dcd     0xe5945004
    dcd     0xe3a01009
    dcd     0xe5950000
    dcd     0xe3a02000
    bl      func_ov107_020c9264
    mov r0, #0
    dcd     0xe5c50050
    dcd     0xe5850030
    dcd     0xe5950044
    dcd     0xe3500000
    dcd     0xc2400001
    dcd     0xc5850044
    dcd     0xe3a00004
    bl      func_02023eb4
    dcd     0xe2900000
    dcd     0x03a00003
    dcd     0x13a00001
    dcd     0xe585004c
    mov r0, #0
    dcd     0xe5c50051
    dcd     0xe5c50053
    dcd     0xe5850054
    dcd     0xe1d412d0
    dcd     0xe59f2008
    dcd     0xe1a00004
    bl      func_0203c634
    dcd     0xe8bd8038
    dcd     func_ov195_020d1994
}
