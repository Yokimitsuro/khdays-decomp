extern void func_ov022_020a2954(void);
extern void func_ov080_020b9358(void);
extern void func_ov080_020b9700(void);

asm void func_ov080_020b85d8(void)
{
    dcd     0xe92d4010
    dcd     0xe1a04000
    dcd     0xe2842084
    dcd     0xe3510021
    dcd     0xe2822b0b
    dcd     0xe3a03000
    dcd     0x0a000002
    dcd     0xe3510022
    dcd     0x0a00000a
    dcd     0xea00000e
    dcd     0xe5823660
    dcd     0xe5942664
    dcd     0xe3a0102f
    dcd     0xe12fff32
    dcd     0xe3a01a02
    dcd     0xe1a00004
    dcd     0xe1c416b4
    bl      func_ov022_020a2954
    dcd     0xe59f301c
    dcd     0xea000004
    dcd     0xe5823660
    dcd     0xe5942664
    dcd     0xe3a01030
    dcd     0xe12fff32
    dcd     0xe59f3008
    dcd     0xe1a00003
    dcd     0xe8bd8010
    dcd     func_ov080_020b9358
    dcd     func_ov080_020b9700
}
