extern void func_020235d0(void);
extern void func_020235e8(void);
extern void func_ov002_02073ed0(void);
extern void func_ov002_02074460(void);
extern void func_ov002_0207687c(void);
extern void func_ov002_0207c618(void);
extern void func_ov002_0207c67c(void);
extern void func_ov002_0207cea4(void);

asm void func_ov014_0207fef4(void)
{
    dcd     0xe92d4038
    dcd     0xe1a04000
    bl      func_ov002_0207687c
    dcd     0xe5d411b1
    dcd     0xe3a05000
    dcd     0xe3110002
    dcd     0x0a00002e
    dcd     0xe59411cc
    dcd     0xe0810000
    dcd     0xe3500909
    dcd     0xe58401cc
    dcd     0xa3a00909
    dcd     0xa58401cc
    dcd     0xe1d401b2
    dcd     0xa3a05001
    dcd     0xe3100004
    dcd     0x0a000002
    dcd     0xe59411cc
    dcd     0xe284003c
    bl      func_ov002_0207c67c
    dcd     0xe3550000
    dcd     0x0a00001f
    dcd     0xe3a01002
    dcd     0xe5c411b3
    dcd     0xe284003c
    dcd     0xe3a02000
    bl      func_ov002_0207c618
    dcd     0xe5d411b1
    dcd     0xe2840c01
    dcd     0xe3c11002
    dcd     0xe5c411b1
    dcd     0xe1d00df0
    bl      func_ov002_02074460
    dcd     0xe3500000
    dcd     0xba000004
    dcd     0xe2840c01
    dcd     0xe1d00df0
    dcd     0xe3a01001
    dcd     0xe2412002
    bl      func_ov002_02073ed0
    dcd     0xe1d401b4
    dcd     0xe5d41016
    bl      func_020235d0
    dcd     0xe1a02000
    dcd     0xe59f1028
    dcd     0xe1d401b4
    dcd     0xe0021001
    dcd     0xe3811004
    dcd     0xe1a02801
    dcd     0xe5d41016
    dcd     0xe1a02822
    bl      func_020235e8
    dcd     0xe59f000c
    dcd     0xe8bd8038
    mov r0, #0
    dcd     0xe8bd8038
    dcd     0xffff0001
    dcd     func_ov002_0207cea4
}
