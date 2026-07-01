extern char data_ov079_020b9a00[];
extern void func_01fff774(void);
extern void func_0202accc(void);
extern void func_ov022_020a4490(void);

asm void func_ov079_020b8aac(void)
{
    dcd     0xe92d4038
    dcd     0xe59f2090
    dcd     0xe1a04001
    dcd     0xe5921000
    dcd     0xe3a05000
    dcd     0xe2811a02
    dcd     0xe5911c50
    dcd     0xe3510000
    dcd     0xe3a010ce
    dcd     0x0a000003
    dcd     0xe3a02002
    dcd     0xe3a05001
    bl      func_ov022_020a4490
    dcd     0xea000001
    dcd     0xe3a02003
    bl      func_ov022_020a4490
    dcd     0xe1a01805
    dcd     0xe3a0c001
    dcd     0xe2840f4a
    dcd     0xe2842f82
    dcd     0xe1a03841
    dcd     0xe3a01000
    dcd     0xe584c124
    bl      func_0202accc
    dcd     0xe1a01805
    dcd     0xe2840f4a
    dcd     0xe2842f82
    dcd     0xe1a03841
    dcd     0xe3a01002
    bl      func_0202accc
    dcd     0xe3a01000
    dcd     0xe1a02001
    dcd     0xe2840f4a
    bl      func_01fff774
    dcd     0xe2840f4a
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe8bd8038
    dcd     data_ov079_020b9a00
}
