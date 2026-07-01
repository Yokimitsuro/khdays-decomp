extern char data_ov079_020b9a00[];
extern void func_01fff774(void);
extern void func_0202a818(void);
extern void func_0202accc(void);
extern void func_ov022_020a4490(void);

asm void func_ov079_020b8934(void)
{
    dcd     0xe92d4038
    dcd     0xe59f30f4
    dcd     0xe1a04001
    dcd     0xe5931000
    dcd     0xe5943000
    dcd     0xe2811ec5
    dcd     0xe3530001
    dcd     0xe281ca02
    dcd     0x0a000002
    dcd     0xe3530002
    dcd     0x0a00002a
    dcd     0xe8bd8038
    dcd     0xe5941110
    dcd     0xe0812002
    dcd     0xe5842110
    dcd     0xe5941114
    dcd     0xe1520001
    dcd     0xb8bd8038
    dcd     0xe59c1000
    dcd     0xe3510000
    dcd     0xe3a010ce
    dcd     0x1a000003
    dcd     0xe3a05000
    dcd     0xe1a02005
    bl      func_ov022_020a4490
    dcd     0xea000002
    dcd     0xe3a05001
    dcd     0xe1a02005
    bl      func_ov022_020a4490
    dcd     0xe1a01805
    dcd     0xe1a03841
    dcd     0xe594210c
    dcd     0xe2840004
    dcd     0xe3a01000
    bl      func_0202accc
    dcd     0xe1a01805
    dcd     0xe1a03841
    dcd     0xe594210c
    dcd     0xe2840004
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
    dcd     0xe3a00002
    dcd     0xe5840000
    mov r0, #0
    dcd     0xe5840110
    dcd     0xe8bd8038
    dcd     0xe5940110
    dcd     0xe1a01002
    dcd     0xe0802002
    dcd     0xe2840004
    dcd     0xe5842110
    bl      func_0202a818
    dcd     0xe3500000
    dcd     0x13a00000
    dcd     0x15840000
    dcd     0xe8bd8038
    dcd     data_ov079_020b9a00
}
