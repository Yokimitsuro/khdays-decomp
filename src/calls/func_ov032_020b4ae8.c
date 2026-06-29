extern void func_01fff774(void);
extern void func_0202accc(void);
extern void func_ov022_0209560c(void);
extern void func_ov022_020a4490(void);

asm void func_ov032_020b4ae8(void)
{
    dcd     0xe92d4070
    dcd     0xe1a05001
    dcd     0xe5d51114
    dcd     0xe1a06000
    dcd     0xe28110ff
    dcd     0xe20110ff
    dcd     0xe3510001
    dcd     0x88bd8070
    dcd     0xe3a01004
    dcd     0xe5c51114
    dcd     0xe3520000
    dcd     0xe3a010c5
    dcd     0x1a000003
    dcd     0xe3a02000
    dcd     0xe3a04001
    bl      func_ov022_020a4490
    dcd     0xea000002
    dcd     0xe3a02001
    dcd     0xe3a04002
    bl      func_ov022_020a4490
    dcd     0xe2860fbe
    dcd     0xe2800a02
    bl      func_ov022_0209560c
    dcd     0xe1a01804
    dcd     0xe1a02000
    dcd     0xe285000c
    dcd     0xe1a03841
    dcd     0xe3a01000
    bl      func_0202accc
    dcd     0xe2860fbe
    dcd     0xe2800a02
    bl      func_ov022_0209560c
    dcd     0xe1a02000
    dcd     0xe285000c
    dcd     0xe3a01002
    dcd     0xe1a03804
    dcd     0xe1a03843
    bl      func_0202accc
    dcd     0xe2860fbe
    dcd     0xe2800a02
    bl      func_ov022_0209560c
    dcd     0xe1a01804
    dcd     0xe1a03841
    dcd     0xe1a02000
    dcd     0xe285000c
    dcd     0xe3a01001
    bl      func_0202accc
    dcd     0xe285000c
    dcd     0xe3a01000
    dcd     0xe1a02001
    bl      func_01fff774
    dcd     0xe285000c
    dcd     0xe3a01002
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe285000c
    dcd     0xe3a01001
    dcd     0xe3a02000
    bl      func_01fff774
    dcd     0xe8bd8070
}
